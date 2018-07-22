// game.cpp : Defines the exported functions for the DLL application.
//#define _DEBUG_WAYPOINTS_
//#define _ENABLE_MIN_DELTA_TIME_

// window
#define SCREEN_WIDTH  226
#define SCREEN_HEIGHT 248

// layers
#define BACKGROUND_LAYER 0
#define DOT_LAYER 1
#define PACMAN_LAYER 2
#define GHOSTS_LAYER 3
#define DEBUG_LAYER 99

// binary directions
#define BINARY_LEFT  0x8
#define BINARY_RIGHT 0x4
#define BINARY_UP    0x2
#define BINARY_DOWN  0x1

#define WAYPOINTS_LENGTH 65
#define DOTS_LENGTH 246

#define INVALID_WAYPOINT_INDEX -1

#include <../include/ldk/ldk.h>


int Vec3ToIntInvertedDir(const ldk::Vec3);
int Vec3ToIntDir(const ldk::Vec3);

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
	ldk::Vec3 desiredDir;
	float desiredAngle;
	int curWaypointIndex;
};

enum EGhostType { Blinky, Inky, Pinky, Clyde };

struct Ghost
{
	EGhostType Type;
	ldk::Sprite sprite;
	ldk::Vec3 direction;
	ldk::Vec3 previousPosition;
	float speed;
};

struct Waypoint
{
	ldk::Vec3 position;
	int allowedDirections;

	Waypoint()  { }

	Waypoint(ldk::Vec3 pPos)
	{
		position = pPos;
		allowedDirections = (BINARY_LEFT | BINARY_RIGHT | BINARY_UP | BINARY_DOWN);
	}
};

struct Dot
{
	ldk::Vec3 position;
	bool isSpecial;
	bool isEnabled;

	Dot() { }

	Dot(ldk::Vec3 pPosition, bool pIsSpecial) :
		isEnabled(true)
	{
		position = pPosition;
		isSpecial = pIsSpecial;
	}
};

struct GameState
{
	ldk::Material spritesheet;
	ldk::Sprite background;
	ldk::Sprite dotSprite;
	int playerPoints = 0;
	Entity pacman;
    Ghost blinky;
    Ghost pinky;
    Ghost inky;
    Ghost clyde;
} *gameState = nullptr;

Waypoint allWaypoints[WAYPOINTS_LENGTH];
Dot allDots[DOTS_LENGTH];

typedef void (*GhostStrategy)(Ghost&, Waypoint&);

#include "waypoint.cpp"
#include "dot.cpp"
#include "ghosts.cpp"
#include "input.cpp"
#include <iostream>

void ReadInput(const float, Entity&);
void MovePacman(const float, Entity&);

void gameInit(void* memory)
{
	LDK_ASSERT(WAYPOINTS_LENGTH % 2 == 1, "WAYPOINTS_LENGTH deve ser um número ímpar!");
	LDK_ASSERT(DOTS_LENGTH % 2 == 0, "DOTS_LENGTH deve ser um número par!");
	gameState = (GameState*)memory;

	// Background
	gameState->spritesheet = ldk::render::loadMaterial("./assets/spritesheet.cfg");
	gameState->background.position = { SCREEN_WIDTH*0.5, SCREEN_HEIGHT*0.5, BACKGROUND_LAYER };
	gameState->background.color = { 1.0, 1.0, 1.0, 1.0 };
	gameState->background.width = SCREEN_WIDTH;
	gameState->background.height = SCREEN_HEIGHT;
	gameState->background.srcRect = { SCREEN_WIDTH + 2, 0, SCREEN_WIDTH - 2, SCREEN_HEIGHT };
	gameState->background.angle = 0;

	// Waypoint
	gameState->dotSprite.color = { 1.0, 1.0, 1.0, 1.0 };
	gameState->dotSprite.width = 2;
	gameState->dotSprite.height = 2;
	gameState->dotSprite.srcRect = { 500,20,1,1 };
	gameState->dotSprite.angle = 0;
	gameState->dotSprite.position = { 0, 0, DOT_LAYER };

	initializeWaypoints();
	initializeDots();
    
	// Pacman
	gameState->pacman.sprite.color = { 1.0, 1.0, 1.0, 1.0 };
	gameState->pacman.sprite.width = 14;
	gameState->pacman.sprite.height = 14;
	gameState->pacman.sprite.srcRect = { 473, 1, 13, 13 };
	gameState->pacman.sprite.angle = 0;
	gameState->pacman.sprite.position = { 114, 0, PACMAN_LAYER };
	gameState->pacman.sprite.position.y = allWaypoints[WAYPOINTS_LENGTH-1].position.y;
	gameState->pacman.previousPosition = gameState->pacman.sprite.position;
	gameState->pacman.speed = 60;
	gameState->pacman.direction = { 0,0,0 };
	gameState->pacman.desiredAngle = RADIAN(0);
    
	gameState->pacman.curWaypointIndex = WAYPOINTS_LENGTH - 1;

    // Ghosts
    // [Blinky]
    int waypointIndex = (WAYPOINTS_LENGTH-1)/2;
    gameState->blinky.Type = Blinky;
    gameState->blinky.sprite.color = {1.0, 1.0, 1.0, 1.0};
    gameState->blinky.sprite.width = 14;
    gameState->blinky.sprite.height = 14;
    gameState->blinky.sprite.srcRect = {521, 65, 13, 13};
    gameState->blinky.sprite.angle = 0;
    gameState->blinky.sprite.position = 
        { allWaypoints[waypointIndex].position.x, allWaypoints[waypointIndex].position.y - 1, GHOSTS_LAYER };
    gameState->blinky.previousPosition = allWaypoints[waypointIndex].position;
    gameState->blinky.speed = 60;
    gameState->blinky.direction = {0, -1, 0};
    
    // [Pinky]
    waypointIndex = 0;
    gameState->pinky.sprite.color = {1.0, 1.0, 1.0, 1.0};
    gameState->pinky.Type = Pinky;
    gameState->pinky.sprite.width = 14;
    gameState->pinky.sprite.height = 14;
    gameState->pinky.sprite.srcRect = {521, 81, 13, 13};
    gameState->pinky.sprite.angle = 0;
    gameState->pinky.sprite.position = 
        { allWaypoints[waypointIndex].position.x, allWaypoints[waypointIndex].position.y - 1, GHOSTS_LAYER };
    gameState->pinky.previousPosition = allWaypoints[waypointIndex].position;
    gameState->pinky.speed = 60;
    gameState->pinky.direction = {0, -1, 0};
    
    // [Inky]
    waypointIndex = (WAYPOINTS_LENGTH - 1) / 2 + 6;
    gameState->inky.sprite.color = {1.0, 1.0, 1.0, 1.0};
    gameState->inky.Type = Inky;
    gameState->inky.sprite.width = 14;
    gameState->inky.sprite.height = 14;
    gameState->inky.sprite.srcRect = {521, 97, 13, 13};
    gameState->inky.sprite.angle = 0;
    gameState->inky.sprite.position = 
        { allWaypoints[waypointIndex].position.x, allWaypoints[waypointIndex].position.y + 1, GHOSTS_LAYER };
    gameState->inky.previousPosition = allWaypoints[waypointIndex].position;
    gameState->inky.speed = 60;
    gameState->inky.direction = {0, 1, 0};
    
    // [Clyde]
    waypointIndex = 6;
    gameState->clyde.sprite.color = {1.0, 1.0, 1.0, 1.0};
    gameState->clyde.Type = Clyde;
    gameState->clyde.sprite.width = 14;
    gameState->clyde.sprite.height = 14;
    gameState->clyde.sprite.srcRect = {521, 113, 13, 13};
    gameState->clyde.sprite.angle = 0;
    gameState->clyde.sprite.position = 
        { allWaypoints[waypointIndex].position.x, allWaypoints[waypointIndex].position.y + 1, GHOSTS_LAYER };
    gameState->clyde.previousPosition = allWaypoints[waypointIndex].position;
    gameState->clyde.speed = 60;
    gameState->clyde.direction = {0, 1, 0};
    
	ldk::render::spriteBatchInit();
}

void ResetGame()
{
	gameState->pacman.sprite.angle = 0;
	gameState->pacman.sprite.position = { 114, 0, PACMAN_LAYER };
	gameState->pacman.sprite.position.y = allWaypoints[WAYPOINTS_LENGTH-1].position.y;
	gameState->pacman.previousPosition = gameState->pacman.sprite.position;
	gameState->pacman.speed = 60;
	gameState->pacman.direction = { 0,0,0 };
    
	gameState->pacman.desiredAngle = RADIAN(0);
	gameState->pacman.desiredDir = {1,0,0};
	gameState->pacman.curWaypointIndex = WAYPOINTS_LENGTH - 1;
	gameState->playerPoints = 0;
    
	for (int i = 0; i < DOTS_LENGTH; i++)
	{
		allDots[i].isEnabled = true;
	}
}

void gameStart() { }

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

	Entity& pacman = gameState->pacman;
	ReadInput(deltaTime, pacman);
	MoveGhosts(deltaTime);
	MovePacman(deltaTime, pacman);

	ldk::Sprite& dotSprite = gameState->dotSprite;

	ldk::render::spriteBatchBegin(gameState->spritesheet);
	ldk::render::spriteBatchSubmit(gameState->background);

	// === DRAW ===
	for (int x = 0; x < DOTS_LENGTH; x++)
	{
		if (allDots[x].isEnabled)
		{
			dotSprite.position.x = allDots[x].position.x;
			dotSprite.position.y = allDots[x].position.y;
			dotSprite.width = dotSprite.height = (allDots[x].isSpecial) ? 8 : 2;
			ldk::render::spriteBatchSubmit(dotSprite);
		}
	}

#ifdef _DEBUG_WAYPOINTS_ //_LDK_DEBUG_
	ldk::Vec3 defaultSize = {dotSprite.width, dotSprite.height};
	ldk::Vec4 defaultColor = dotSprite.color;
	int defaultLayer = dotSprite.position.z;
	dotSprite.width = dotSprite.height = 4;
	dotSprite.color = {0, 1, 0, 0.5};
	
	for (int x = 0; x < WAYPOINTS_LENGTH; x++)
	{
		dotSprite.position.x = allWaypoints[x].position.x;
		dotSprite.position.y = allWaypoints[x].position.y;
		dotSprite.position.z = DEBUG_LAYER;
		ldk::render::spriteBatchSubmit(gameState->dotSprite);
	}
    	
	dotSprite.color = defaultColor;
	dotSprite.width = defaultSize.x;
	dotSprite.height = defaultSize.y;
	dotSprite.position.z = defaultLayer;
#endif

	ldk::render::spriteBatchSubmit(gameState->pacman.sprite);
    ldk::render::spriteBatchSubmit(gameState->blinky.sprite);
    ldk::render::spriteBatchSubmit(gameState->pinky.sprite);
    ldk::render::spriteBatchSubmit(gameState->inky.sprite);
    ldk::render::spriteBatchSubmit(gameState->clyde.sprite);
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
			gameState->pacman.curWaypointIndex = INVALID_WAYPOINT_INDEX;
		}
	}
	else if (gameState->pacman.direction.y != 0)
	{
		// Pacman`s moving VERTICALLY
		HandleVerticalDots(pacman);
		HandleVerticalWaypoints(pacman);

		if (pacman.direction.y != 0)
		{
			gameState->pacman.curWaypointIndex = INVALID_WAYPOINT_INDEX;
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

int Vec3ToIntInvertedDir(const ldk::Vec3 vector)
{
    if (vector.x == 1)
    {
        return BINARY_LEFT;
    }
    if (vector.x == -1)
    {
        return BINARY_RIGHT;
    }
    if (vector.y == -1)
    {
        return BINARY_UP;
    }
    return BINARY_DOWN;
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