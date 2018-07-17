// game.cpp : Defines the exported functions for the DLL application.
//#define DEBUG_WAYPOINT_DOTS

#define _ENABLE_MIN_DELTA_TIME_

#define SCREEN_WIDTH  226
#define SCREEN_HEIGHT 248

// Binary directions
#define BINARY_LEFT  0x8
#define BINARY_RIGHT 0x4
#define BINARY_UP    0x2
#define BINARY_DOWN  0x1

// Layers
#define BACKGROUND_LAYER 0
#define DOTS_LAYER 1
#define PACMAN_LAYER 2
#define GHOSTS_LAYER 3
#define DEBUG_LAYER 99

#include <../include/ldk/ldk.h>

const ldk::Vec3 LEFT_DIR  = {-1,  0,  0};
const ldk::Vec3 RIGHT_DIR = { 1,  0,  0};
const ldk::Vec3 DOWN_DIR  = { 0, -1,  0};
const ldk::Vec3 UP_DIR    = { 0,  1,  0};

struct Entity
{
	ldk::Sprite sprite;
	ldk::Vec3 direction;
	ldk::Vec3 previousPosition;
	float speed;
};

struct GameState
{
	ldk::Material spritesheet;
	ldk::Sprite background;
	ldk::Sprite dotSprite;
	int curWaypointIndex;

	int playerPoints = 0;

	ldk::Vec3 desiredDir;
	float desiredAngle;
	Entity pacman;
} *gameState = nullptr;

int InvertHorizontalDirection(const int);
int Vec3ToIntDir(const ldk::Vec3);
void setupSprite();
void InitializeWaypoints();
void InitializeDots();

#include "waypoint.hpp"
#include "dot.hpp"
#include "input.hpp"

void MovePacman(const float,Entity&);
void HandleHorizontalDots(Entity&);
void HandleVerticalDots(Entity&);
void HandleHorizontalWaypoints(Entity&);
void HandleVerticalWaypoints(Entity&);
void inline EvaluateDot(Dot&);

void gameInit(void* memory)
{
	LDK_ASSERT(WAYPOINTS_LENGTH % 2 == 0, "WAYPOINTS_LENGTH deve ser um número par!");
	LDK_ASSERT(DOTS_LENGTH % 2 == 0, "DOTS_LENGTH deve ser um número par!");
	gameState = (GameState*)memory;

	// Background
	gameState->spritesheet = ldk::render::loadMaterial("./assets/pacman.cfg");

	gameState->background.position = { SCREEN_WIDTH*0.5, SCREEN_HEIGHT*0.5, BACKGROUND_LAYER };
	gameState->background.color = { 1.0, 1.0, 1.0, 1.0 };
	gameState->background.width = SCREEN_WIDTH;
	gameState->background.height = SCREEN_HEIGHT;
	gameState->background.srcRect = { SCREEN_WIDTH + 2, 0, SCREEN_WIDTH - 2, SCREEN_HEIGHT };
	gameState->background.angle = 0;

	// Pacman
	gameState->pacman.sprite.color = { 1.0, 1.0, 1.0, 1.0 };
	gameState->pacman.sprite.width = 14;
	gameState->pacman.sprite.height = 14;
	gameState->pacman.sprite.srcRect = { 473, 1, 13, 13 };
	gameState->pacman.sprite.angle = 0;
	gameState->pacman.sprite.position = { 114, SCREEN_HEIGHT - 140, PACMAN_LAYER };
	gameState->pacman.previousPosition = gameState->pacman.sprite.position;
	gameState->pacman.speed = 60;
	gameState->pacman.direction = { 0,0,0 };
	gameState->desiredAngle = RADIAN(0);

	// Waypoint
	gameState->dotSprite.color = { 1.0, 1.0, 1.0, 1.0 };
	gameState->dotSprite.width = 2;
	gameState->dotSprite.height = 2;
	gameState->dotSprite.srcRect = { 500,20,1,1 };
	gameState->dotSprite.angle = 0;
	gameState->dotSprite.position = { 0, 0, DEBUG_LAYER };

	InitializeWaypoints();
	InitializeDots();

	gameState->pacman.sprite.position.y = allWaypoints[20].position.y;

	ldk::render::spriteBatchInit();
}

void ResetGame()
{
	gameState->pacman.sprite.angle = 0;
	gameState->pacman.sprite.position = { 114, SCREEN_HEIGHT - 140, PACMAN_LAYER };
    	gameState->pacman.sprite.position.y =allWaypoints[20].position.y;
	gameState->pacman.previousPosition = gameState->pacman.sprite.position;
	gameState->pacman.direction = { 1,0,0 };
	
	gameState->curWaypointIndex = INVALID_WAYPOINT_INDEX;
	gameState->desiredAngle = RADIAN(0);
	gameState->desiredDir = {1,0,0};
	gameState->playerPoints = 0;

	ResetDots();
}

void gameStart()
{
	gameState->pacman.direction = RIGHT_DIR;
}

void gameStop() { }

void gameUpdate(float deltaTime)
{
#ifdef _ENABLE_MIN_DELTA_TIME_
	deltaTime = MIN(deltaTime, 0.016f);
#endif
    
    if (ldk::input::isKeyDown(LDK_KEY_R))
    {
        ResetGame();
    }
    
	ldk::render::spriteBatchBegin(gameState->spritesheet);
	ldk::render::spriteBatchSubmit(gameState->background);

	Entity& pacman = gameState->pacman;
	ReadInput(deltaTime, pacman);
	//TODO Move ghosts
	MovePacman(deltaTime, pacman);

	ldk::Sprite& dotSprite = gameState->dotSprite;

	// draw dots
	for (int x = 0; x < DOTS_LENGTH; x++)
	{
		if (allDots[x].isEnabled)
		{
			dotSprite.position.x = allDots[x].position.x;
			dotSprite.position.y = allDots[x].position.y;
			ldk::render::spriteBatchSubmit(gameState->dotSprite);
		}
	}

#ifdef DEBUG_WAYPOINTS
	Waypoint* allWaypoints = gameState->allWaypoints;
	for (int x = 0; x < WAYPOINTS_LENGTH; x++)
	{
		dotSprite.position.x = allWaypoints[x].position.x;
		dotSprite.position.y = allWaypoints[x].position.y;
		ldk::render::spriteBatchSubmit(gameState->dotSprite);
	}
#endif

	ldk::render::spriteBatchSubmit(gameState->pacman.sprite);
	ldk::render::spriteBatchEnd();
}

void MovePacman(const float deltaTime, Entity& pacman)
{
	pacman.sprite.position += pacman.direction * pacman.speed * deltaTime;

	if (pacman.direction.x != 0)
	{
		// Pacman`s moving HORIZONTALLY
		HandleHorizontalDots(pacman);
		HandleHorizontalWaypoints(pacman);

		if (pacman.direction.x != 0)
		{
			gameState->curWaypointIndex = INVALID_WAYPOINT_INDEX;
		}
	}
	else if (gameState->pacman.direction.y != 0)
	{
		// Pacman`s moving VERTICALLY
		HandleVerticalDots(pacman);
		HandleVerticalWaypoints(pacman);

		if (pacman.direction.y != 0)
		{
			gameState->curWaypointIndex = INVALID_WAYPOINT_INDEX;
		}
	}

	// Check bounds and teleport pacman, if needed
	if (gameState->pacman.sprite.position.x < -5)
	{
		gameState->pacman.sprite.position.x = SCREEN_WIDTH + 4;
	}
	else if (gameState->pacman.sprite.position.x > SCREEN_WIDTH + 5)
	{
		gameState->pacman.sprite.position.x = -5;
	}

	pacman.previousPosition = pacman.sprite.position;
}

void HandleHorizontalWaypoints(Entity& pacman)
{
	Waypoint waypoint;
	int index;
	if (getWaypoint(pacman.previousPosition, pacman.sprite.position, waypoint, index))
	{
		// Is the player trying to change pacman's direction?
		int desiredDirAsInt = Vec3ToIntDir(gameState->desiredDir);
		if (desiredDirAsInt != 0 && gameState->desiredDir.y != 0)
		{
			// Can we change to the desired direction?
			if ((desiredDirAsInt & waypoint.allowedDirections) == desiredDirAsInt)
			{
				gameState->curWaypointIndex = INVALID_WAYPOINT_INDEX;
				pacman.direction = gameState->desiredDir;
				pacman.sprite.angle = gameState->desiredAngle;
				pacman.sprite.position.x = waypoint.position.x;
				return;
			}
		}

		// Check if pacman hit a wall
		int currentDirAsInt = (pacman.direction.x > 0) ? BINARY_RIGHT : BINARY_LEFT;
		if ((currentDirAsInt & waypoint.allowedDirections) != currentDirAsInt)
		{
			// Pacman hit a wall
			gameState->curWaypointIndex = index;
			pacman.direction.x = 0;
			gameState->desiredDir.x = 0;
			pacman.sprite.position.x = waypoint.position.x;
		}
	}
}

void HandleVerticalWaypoints(Entity& pacman)
{
	Waypoint waypoint;
	int index;
	if (getWaypoint(pacman.previousPosition, pacman.sprite.position, waypoint, index))
	{
		// Is the player trying to change pacman's direction?
		int desiredDirAsInt = Vec3ToIntDir(gameState->desiredDir);
		if (desiredDirAsInt != 0 && gameState->desiredDir.x != 0)
		{
			if ((desiredDirAsInt & waypoint.allowedDirections) == desiredDirAsInt)
			{
				gameState->curWaypointIndex = INVALID_WAYPOINT_INDEX;
				pacman.direction = gameState->desiredDir;
				pacman.sprite.angle = gameState->desiredAngle;
				pacman.sprite.position.y = waypoint.position.y;
				return;
			}
		}

		// check if pacman hit a wall
		int currentDirAsInt = (gameState->pacman.direction.y > 0) ? BINARY_UP : BINARY_DOWN;
		if ((currentDirAsInt & waypoint.allowedDirections) != currentDirAsInt)
		{
			gameState->curWaypointIndex = index;
			pacman.direction.y = 0;
			gameState->desiredDir.y = 0;
			pacman.sprite.position.y = waypoint.position.y;
		}
	}
}

int Vec3ToIntDir(const ldk::Vec3 direction)
{
	if (direction.x != 0)
	{
		return (direction.x > 0) ? BINARY_RIGHT : BINARY_LEFT;
	}
	if (direction.y != 0)
	{
		return (direction.y > 0) ? BINARY_UP : BINARY_DOWN;
	}
	return 0;
}

int InvertHorizontalDirection(const int allowedDirections)
{
	int result = allowedDirections & (BINARY_UP | BINARY_DOWN);

	if ((allowedDirections & (BINARY_LEFT | BINARY_RIGHT)) != (BINARY_LEFT | BINARY_RIGHT))
	{
		// Invert L and R
		result |= ~allowedDirections & (BINARY_LEFT | BINARY_RIGHT);
	}
	else
	{
		result |= (BINARY_LEFT | BINARY_RIGHT);
	}

	return result;
}