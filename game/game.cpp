// game.cpp : Defines the exported functions for the DLL application.
//#define DEBUG_WAYPOINT_DOTS

#include <../include/ldk/ldk.h>
#include "model.hpp"
#include "controller.hpp"
#include <iostream>

void setupSprite();
void InitializeallDots();
void ReadInput(const float,Entity&);
int InvertHorizontalDirection(const int);

void gameInit(void* memory)
{
	LDK_ASSERT(DOTS_LENGTH % 2 == 0, "DOTS_LENGTH não é par!");
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

	// Dot
	gameState->dotSprite.color = { 1.0, 1.0, 1.0, 1.0 };
	gameState->dotSprite.width = 2;
	gameState->dotSprite.height = 2;
	gameState->dotSprite.srcRect = { 500,20,1,1 };
	gameState->dotSprite.angle = 0;
	gameState->dotSprite.position = { 0, 0, Dot_LAYER };

	InitializeallDots();

	gameState->pacman.sprite.position.y = gameState->allDots[20].position.y;

	ldk::render::spriteBatchInit();
}

void gameStart()
{
	gameState->pacman.direction = RIGHT_DIR;
}

void gameStop() { }

void gameUpdate(float deltaTime)
{
	deltaTime = MIN(deltaTime, 0.016f);

	ldk::render::spriteBatchBegin(gameState->spritesheet);
	ldk::render::spriteBatchSubmit(gameState->background);

	Entity& pacman = gameState->pacman;
	ReadInput(deltaTime, pacman);
	MoveAndCheckallDots(deltaTime, pacman);

	// Check bounds and teleport pacman, if needed
	if (gameState->pacman.sprite.position.x < -5)
	{
		gameState->pacman.sprite.position.x = SCREEN_WIDTH + 4;
	}
	else if (gameState->pacman.sprite.position.x > SCREEN_WIDTH + 5)
	{
		gameState->pacman.sprite.position.x = -5;
	}

	ldk::Sprite& dotSprite = gameState->dotSprite;
	Dot* allDots = gameState->allDots;

	for (int x = 0; x < DOTS_LENGTH; x++)
	{
		if (allDots[x].isEnabled)
		{
			dotSprite.position.x = allDots[x].position.x;
			dotSprite.position.y = allDots[x].position.y;
			ldk::render::spriteBatchSubmit(gameState->dotSprite);
		}
	}

#ifdef DEBUG_WAYPOINT_DOTS //_LDK_DEBUG_
	// allDots
	for (int x = 0; x < DOTS_LENGTH; x++)
	{
		dotSprite.position.x = allDots[x].position.x;
		dotSprite.position.y = allDots[x].position.y;
		ldk::render::spriteBatchSubmit(gameState->dotSprite);
	}
#endif

	ldk::render::spriteBatchSubmit(gameState->pacman.sprite);
	ldk::render::spriteBatchEnd();
}

void InitializeallDots()
{
	Dot* allDotsPtr = gameState->allDots;

	// WAYPOINTS
	// X 13
	allDotsPtr[0] = Dot({ 13, SCREEN_HEIGHT - 12, 0 }, WaypointDot);
	allDotsPtr[0].allowedDirections = (BINARY_DOWN | BINARY_RIGHT);
	allDotsPtr[1] = Dot({ 13, SCREEN_HEIGHT - 43, 0 }, WaypointDot);
	allDotsPtr[1].allowedDirections = (BINARY_DOWN | BINARY_RIGHT | BINARY_UP);
	allDotsPtr[2] = Dot({ 13, SCREEN_HEIGHT - 67, 0 }, WaypointDot);
	allDotsPtr[2].allowedDirections = (BINARY_RIGHT | BINARY_UP);
	allDotsPtr[3] = Dot({ 13, SCREEN_HEIGHT - 163, 0 }, WaypointDot);
	allDotsPtr[3].allowedDirections = (BINARY_RIGHT | BINARY_DOWN);
	allDotsPtr[4] = Dot({ 13, SCREEN_HEIGHT - 187, 0 }, WaypointDot);
	allDotsPtr[4].allowedDirections = (BINARY_RIGHT | BINARY_UP);
	allDotsPtr[5] = Dot({ 13, SCREEN_HEIGHT - 211, 0 }, WaypointDot);
	allDotsPtr[5].allowedDirections = (BINARY_RIGHT | BINARY_DOWN);
	allDotsPtr[6] = Dot({ 13, SCREEN_HEIGHT - 235, 0 }, WaypointDot);
	allDotsPtr[6].allowedDirections = (BINARY_RIGHT | BINARY_UP);

	// X 29
	allDotsPtr[7] = Dot({ 29, SCREEN_HEIGHT - 187, 0 }, WaypointDot);
	allDotsPtr[7].allowedDirections = (BINARY_LEFT | BINARY_DOWN);
	allDotsPtr[8] = Dot({ 29, SCREEN_HEIGHT - 211, 0 }, WaypointDot);
	allDotsPtr[8].allowedDirections = (BINARY_RIGHT | BINARY_UP | BINARY_LEFT);

	// X 53
	allDotsPtr[9] = Dot({ 53, SCREEN_HEIGHT - 12, 0 }, WaypointDot);
	allDotsPtr[9].allowedDirections = (BINARY_RIGHT | BINARY_LEFT | BINARY_DOWN);
	allDotsPtr[10] = Dot({ 53, SCREEN_HEIGHT - 43, 0 }, WaypointDot);
	allDotsPtr[10].allowedDirections = (BINARY_RIGHT | BINARY_LEFT | BINARY_DOWN | BINARY_UP);
	allDotsPtr[11] = Dot({ 53, SCREEN_HEIGHT - 67, 0 }, WaypointDot);
	allDotsPtr[11].allowedDirections = (BINARY_LEFT | BINARY_UP | BINARY_DOWN);
	allDotsPtr[12] = Dot({ 53, SCREEN_HEIGHT - 115, 0 }, WaypointDot);
	allDotsPtr[12].allowedDirections = (BINARY_LEFT | BINARY_RIGHT | BINARY_UP | BINARY_DOWN);
	allDotsPtr[13] = Dot({ 53, SCREEN_HEIGHT - 163, 0 }, WaypointDot);
	allDotsPtr[13].allowedDirections = (BINARY_LEFT | BINARY_RIGHT | BINARY_UP | BINARY_DOWN);
	allDotsPtr[14] = Dot({ 53, SCREEN_HEIGHT - 187, 0 }, WaypointDot);
	allDotsPtr[14].allowedDirections = (BINARY_RIGHT | BINARY_UP | BINARY_DOWN);
	allDotsPtr[15] = Dot({ 53, SCREEN_HEIGHT - 211, 0 }, WaypointDot);
	allDotsPtr[15].allowedDirections = (BINARY_LEFT | BINARY_UP);

	// X 77
	allDotsPtr[16] = Dot({ 77, SCREEN_HEIGHT - 43, 0 }, WaypointDot);
	allDotsPtr[16].allowedDirections = (BINARY_DOWN | BINARY_RIGHT | BINARY_LEFT);
	allDotsPtr[17] = Dot({ 77, SCREEN_HEIGHT - 67, 0 }, WaypointDot);
	allDotsPtr[17].allowedDirections = (BINARY_UP | BINARY_RIGHT);
	allDotsPtr[18] = Dot({ 77, SCREEN_HEIGHT - 91, 0 }, WaypointDot);
	allDotsPtr[18].allowedDirections = (BINARY_DOWN | BINARY_RIGHT);
	allDotsPtr[19] = Dot({ 77, SCREEN_HEIGHT - 115, 0 }, WaypointDot);
	allDotsPtr[19].allowedDirections = (BINARY_DOWN | BINARY_LEFT | BINARY_UP);
	allDotsPtr[20] = Dot({ 77, SCREEN_HEIGHT - 137, 0 }, WaypointDot);
	allDotsPtr[20].allowedDirections = (BINARY_RIGHT | BINARY_DOWN | BINARY_UP);
	allDotsPtr[21] = Dot({ 77, SCREEN_HEIGHT - 163, 0 }, WaypointDot);
	allDotsPtr[21].allowedDirections = (BINARY_RIGHT | BINARY_LEFT | BINARY_UP);
	allDotsPtr[22] = Dot({ 77, SCREEN_HEIGHT - 187, 0 }, WaypointDot);
	allDotsPtr[22].allowedDirections = (BINARY_RIGHT | BINARY_LEFT | BINARY_DOWN);
	allDotsPtr[23] = Dot({ 77, SCREEN_HEIGHT - 211, 0 }, WaypointDot);
	allDotsPtr[23].allowedDirections = (BINARY_RIGHT | BINARY_UP);

	// X 101
	allDotsPtr[24] = Dot({ 101, SCREEN_HEIGHT - 12, 0 }, WaypointDot);
	allDotsPtr[24].allowedDirections = (BINARY_LEFT | BINARY_DOWN);
	allDotsPtr[25] = Dot({ 101, SCREEN_HEIGHT - 43, 0 }, WaypointDot);
	allDotsPtr[25].allowedDirections = (BINARY_LEFT | BINARY_RIGHT | BINARY_UP);
	allDotsPtr[26] = Dot({ 101, SCREEN_HEIGHT - 67, 0 }, WaypointDot);
	allDotsPtr[26].allowedDirections = (BINARY_LEFT | BINARY_DOWN);
	allDotsPtr[27] = Dot({ 101, SCREEN_HEIGHT - 91, 0 }, WaypointDot);
	allDotsPtr[27].allowedDirections = (BINARY_LEFT | BINARY_RIGHT | BINARY_UP);
	allDotsPtr[28] = Dot({ 101, SCREEN_HEIGHT - 163, 0 }, WaypointDot);
	allDotsPtr[28].allowedDirections = (BINARY_LEFT | BINARY_DOWN);
	allDotsPtr[29] = Dot({ 101, SCREEN_HEIGHT - 187, 0 }, WaypointDot);
	allDotsPtr[29].allowedDirections = (BINARY_LEFT | BINARY_RIGHT | BINARY_UP);
	allDotsPtr[30] = Dot({ 101, SCREEN_HEIGHT - 211, 0 }, WaypointDot);
	allDotsPtr[30].allowedDirections = (BINARY_LEFT | BINARY_DOWN);
	allDotsPtr[31] = Dot({ 101, SCREEN_HEIGHT - 235, 0 }, WaypointDot);
	allDotsPtr[31].allowedDirections = (BINARY_LEFT | BINARY_RIGHT | BINARY_UP);

	//SIMPLE DOTS
	allDotsPtr[32] = Dot({ 21, SCREEN_HEIGHT - 12, 0 }, SimpleDot);
	allDotsPtr[33] = Dot({ 29, SCREEN_HEIGHT - 12, 0 }, SimpleDot);
	allDotsPtr[34] = Dot({ 38, SCREEN_HEIGHT - 12, 0 }, SimpleDot);
	allDotsPtr[35] = Dot({ 46, SCREEN_HEIGHT - 12, 0 }, SimpleDot);

	// Copy all information from the left side to the right side of the map
	int halfallDotsLength = (int)DOTS_LENGTH / 2;
	for (int x = 0; x < halfallDotsLength; x++)
	{
		ldk::Vec3 curPos = allDotsPtr[x].position;
		int realIndex = halfallDotsLength + x;
		allDotsPtr[realIndex] = Dot({ SCREEN_WIDTH - curPos.x, curPos.y }, allDotsPtr[realIndex].dotType);
		allDotsPtr[realIndex].allowedDirections = InvertHorizontalDirection(allDotsPtr[x].allowedDirections);
	}
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

void ReadInput(const float deltaTime, Entity& pacman)
{
	// Control
	if (ldk::input::getKey(LDK_KEY_LEFT))
	{
		gameState->desiredAngle = RADIAN(180);
		gameState->desiredDir = LEFT_DIR;
	}
	else if (ldk::input::getKey(LDK_KEY_RIGHT))
	{
		gameState->desiredAngle = 0;
		gameState->desiredDir = RIGHT_DIR;
	}
	else if (ldk::input::getKey(LDK_KEY_UP))
	{
		gameState->desiredAngle = RADIAN(90);
		gameState->desiredDir = UP_DIR;
	}
	else if (ldk::input::getKey(LDK_KEY_DOWN))
	{
		gameState->desiredAngle = RADIAN(270);
		gameState->desiredDir = DOWN_DIR;
	}
	else
	{
		gameState->desiredDir = ldk::Vec3::zero();
	}

	// Immediately direction change is only allowed on the same line of movement (Horizontally or Vertically)
	if (!(gameState->desiredDir == ldk::Vec3::zero()))
	{
		// If he's walking
		if (pacman.direction == ldk::Vec3::zero())
		{
			//If we`ve stopped on an Dot
			if (gameState->currentDotIndex != INVALID_WAYPOINT_INDEX)
			{
				// Check if this Dot allows us to move in the desired direction we want
				Dot& Dot = gameState->allDots[gameState->currentDotIndex];
				int desiredDirAsInt = Vec3ToIntDir(gameState->desiredDir);
				// Check if we can move in the desiredDir
				if ((desiredDirAsInt & Dot.allowedDirections) == desiredDirAsInt)
				{
					pacman.sprite.angle = gameState->desiredAngle;
					pacman.direction = gameState->desiredDir;
				}
			}
		}
		else
		{
			// If the direction you wanna go is the inverse of the direction he is going
			if (pacman.direction == (gameState->desiredDir * -1))
			{
				pacman.sprite.angle = gameState->desiredAngle;
				pacman.direction = gameState->desiredDir;
			}
		}
	}
}
