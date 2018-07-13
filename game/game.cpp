// game.cpp : Defines the exported functions for the DLL application.
//#define DEBUG_WAYPOINT_DOTS

#define _ENABLE_MIN_DELTA_TIME_

#include <../include/ldk/ldk.h>
#include "model.hpp"
#include "controller.hpp"
#include <iostream>

void setupSprite();
void InitializeWaypoints();
void InitializeDots();
void ReadInput(const float,Entity&);
int InvertHorizontalDirection(const int);

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

	gameState->pacman.sprite.position.y = gameState->allWaypoints[20].position.y;

	ldk::render::spriteBatchInit();
}

void InitializeWaypoints()
{
	Waypoint* allWaypointsPtr = gameState->allWaypoints;

	// WAYPOINTS
	// C1 - X 13
	allWaypointsPtr[0] = Waypoint({ 13, SCREEN_HEIGHT - 12, 0 });
	allWaypointsPtr[0].allowedDirections = (BINARY_DOWN | BINARY_RIGHT);
	allWaypointsPtr[1] = Waypoint({ 13, SCREEN_HEIGHT - 43, 0 });
	allWaypointsPtr[1].allowedDirections = (BINARY_DOWN | BINARY_RIGHT | BINARY_UP);
	allWaypointsPtr[2] = Waypoint({ 13, SCREEN_HEIGHT - 67, 0 });
	allWaypointsPtr[2].allowedDirections = (BINARY_RIGHT | BINARY_UP);
	allWaypointsPtr[3] = Waypoint({ 13, SCREEN_HEIGHT - 163, 0 });
	allWaypointsPtr[3].allowedDirections = (BINARY_RIGHT | BINARY_DOWN);
	allWaypointsPtr[4] = Waypoint({ 13, SCREEN_HEIGHT - 187, 0 });
	allWaypointsPtr[4].allowedDirections = (BINARY_RIGHT | BINARY_UP);
	allWaypointsPtr[5] = Waypoint({ 13, SCREEN_HEIGHT - 211, 0 });
	allWaypointsPtr[5].allowedDirections = (BINARY_RIGHT | BINARY_DOWN);
	allWaypointsPtr[6] = Waypoint({ 13, SCREEN_HEIGHT - 235, 0 });
	allWaypointsPtr[6].allowedDirections = (BINARY_RIGHT | BINARY_UP);

	// C2 - X 29
	allWaypointsPtr[7] = Waypoint({ 29, SCREEN_HEIGHT - 187, 0 });
	allWaypointsPtr[7].allowedDirections = (BINARY_LEFT | BINARY_DOWN);
	allWaypointsPtr[8] = Waypoint({ 29, SCREEN_HEIGHT - 211, 0 });
	allWaypointsPtr[8].allowedDirections = (BINARY_RIGHT | BINARY_UP | BINARY_LEFT);

	// C3 - X 53
	allWaypointsPtr[9] = Waypoint({ 53, SCREEN_HEIGHT - 12, 0 });
	allWaypointsPtr[9].allowedDirections = (BINARY_RIGHT | BINARY_LEFT | BINARY_DOWN);
	allWaypointsPtr[10] = Waypoint({ 53, SCREEN_HEIGHT - 43, 0 });
	allWaypointsPtr[10].allowedDirections = (BINARY_RIGHT | BINARY_LEFT | BINARY_DOWN | BINARY_UP);
	allWaypointsPtr[11] = Waypoint({ 53, SCREEN_HEIGHT - 67, 0 });
	allWaypointsPtr[11].allowedDirections = (BINARY_LEFT | BINARY_UP | BINARY_DOWN);
	allWaypointsPtr[12] = Waypoint({ 53, SCREEN_HEIGHT - 115, 0 });
	allWaypointsPtr[12].allowedDirections = (BINARY_LEFT | BINARY_RIGHT | BINARY_UP | BINARY_DOWN);
	allWaypointsPtr[13] = Waypoint({ 53, SCREEN_HEIGHT - 163, 0 });
	allWaypointsPtr[13].allowedDirections = (BINARY_LEFT | BINARY_RIGHT | BINARY_UP | BINARY_DOWN);
	allWaypointsPtr[14] = Waypoint({ 53, SCREEN_HEIGHT - 187, 0 });
	allWaypointsPtr[14].allowedDirections = (BINARY_RIGHT | BINARY_UP | BINARY_DOWN);
	allWaypointsPtr[15] = Waypoint({ 53, SCREEN_HEIGHT - 211, 0 });
	allWaypointsPtr[15].allowedDirections = (BINARY_LEFT | BINARY_UP);

	// C4 - X 77
	allWaypointsPtr[16] = Waypoint({ 77, SCREEN_HEIGHT - 43, 0 });
	allWaypointsPtr[16].allowedDirections = (BINARY_DOWN | BINARY_RIGHT | BINARY_LEFT);
	allWaypointsPtr[17] = Waypoint({ 77, SCREEN_HEIGHT - 67, 0 });
	allWaypointsPtr[17].allowedDirections = (BINARY_UP | BINARY_RIGHT);
	allWaypointsPtr[18] = Waypoint({ 77, SCREEN_HEIGHT - 91, 0 });
	allWaypointsPtr[18].allowedDirections = (BINARY_DOWN | BINARY_RIGHT);
	allWaypointsPtr[19] = Waypoint({ 77, SCREEN_HEIGHT - 115, 0 });
	allWaypointsPtr[19].allowedDirections = (BINARY_DOWN | BINARY_LEFT | BINARY_UP);
	allWaypointsPtr[20] = Waypoint({ 77, SCREEN_HEIGHT - 137, 0 });
	allWaypointsPtr[20].allowedDirections = (BINARY_RIGHT | BINARY_DOWN | BINARY_UP);
	allWaypointsPtr[21] = Waypoint({ 77, SCREEN_HEIGHT - 163, 0 });
	allWaypointsPtr[21].allowedDirections = (BINARY_RIGHT | BINARY_LEFT | BINARY_UP);
	allWaypointsPtr[22] = Waypoint({ 77, SCREEN_HEIGHT - 187, 0 });
	allWaypointsPtr[22].allowedDirections = (BINARY_RIGHT | BINARY_LEFT | BINARY_DOWN);
	allWaypointsPtr[23] = Waypoint({ 77, SCREEN_HEIGHT - 211, 0 });
	allWaypointsPtr[23].allowedDirections = (BINARY_RIGHT | BINARY_UP);

	// C5 - X 101
	allWaypointsPtr[24] = Waypoint({ 101, SCREEN_HEIGHT - 12, 0 });
	allWaypointsPtr[24].allowedDirections = (BINARY_LEFT | BINARY_DOWN);
	allWaypointsPtr[25] = Waypoint({ 101, SCREEN_HEIGHT - 43, 0 });
	allWaypointsPtr[25].allowedDirections = (BINARY_LEFT | BINARY_RIGHT | BINARY_UP);
	allWaypointsPtr[26] = Waypoint({ 101, SCREEN_HEIGHT - 67, 0 });
	allWaypointsPtr[26].allowedDirections = (BINARY_LEFT | BINARY_DOWN);
	allWaypointsPtr[27] = Waypoint({ 101, SCREEN_HEIGHT - 91, 0 });
	allWaypointsPtr[27].allowedDirections = (BINARY_LEFT | BINARY_RIGHT | BINARY_UP);
	allWaypointsPtr[28] = Waypoint({ 101, SCREEN_HEIGHT - 163, 0 });
	allWaypointsPtr[28].allowedDirections = (BINARY_LEFT | BINARY_DOWN);
	allWaypointsPtr[29] = Waypoint({ 101, SCREEN_HEIGHT - 187, 0 });
	allWaypointsPtr[29].allowedDirections = (BINARY_LEFT | BINARY_RIGHT | BINARY_UP);
	allWaypointsPtr[30] = Waypoint({ 101, SCREEN_HEIGHT - 211, 0 });
	allWaypointsPtr[30].allowedDirections = (BINARY_LEFT | BINARY_DOWN);
	allWaypointsPtr[31] = Waypoint({ 101, SCREEN_HEIGHT - 235, 0 });
	allWaypointsPtr[31].allowedDirections = (BINARY_LEFT | BINARY_RIGHT | BINARY_UP);

	// Copy all information from the left side to the right side of the map
	int halfallDotsLength = (int)WAYPOINTS_LENGTH / 2;
	for (int x = 0; x < halfallDotsLength; x++)
	{
		ldk::Vec3 curPos = allWaypointsPtr[x].position;
		int realIndex = halfallDotsLength + x;
		allWaypointsPtr[realIndex] = Waypoint({ SCREEN_WIDTH - curPos.x, curPos.y });
		allWaypointsPtr[realIndex].allowedDirections = InvertHorizontalDirection(allWaypointsPtr[x].allowedDirections);
	}
}

void InitializeDots()
{
	Waypoint* allWaypointsPtr = gameState->allWaypoints;
	Dot* allDotsPtr = gameState->allDots;

	ldk::Vec3 xOffset = { 7.7, 0, 0 };
	ldk::Vec3 yOffset = { 0, -7.7, 0 };

	int index = 0;
	allDotsPtr[index++] = Dot(allWaypointsPtr[0].position, true);
	
	// 1st line - 1st column (vertical)	
	for (int i = 0; i < 6; i++)
	{
		allDotsPtr[index++] = Dot(allDotsPtr[index-1].position + yOffset, true);
	}

	// 1st line - 1st column (horizontal)
	for (int i = 0; i < 4; i++)
	{
		allDotsPtr[index++] = Dot(allDotsPtr[index-1].position + xOffset, true);
	}
	
	// 1st line - 2nd column (vertical)
	allDotsPtr[index++] = Dot(allWaypointsPtr[9].position, true);
	for (int i = 0; i < 26; i++)
	{
		allDotsPtr[index++] = Dot(allDotsPtr[index-1].position + yOffset, true);
	}

	// 2nd line - 1st column (horizontal)
	allDotsPtr[index++] = Dot(allWaypointsPtr[1].position + xOffset, true);
	for (int i = 0; i < 3; i++)
	{
		allDotsPtr[index++] = Dot(allDotsPtr[index-1].position + xOffset, true);
	}

	// 3rd line - 1st column (horizontal)
	allDotsPtr[index++] = Dot(allWaypointsPtr[2].position + xOffset, true);
	for (int i = 0; i < 3; i++)
	{
		allDotsPtr[index++] = Dot(allDotsPtr[index-1].position + xOffset, true);
	}	

	// Copy all information from the left side to the right side of the map
	int halfallDotsLength = (int)DOTS_LENGTH / 2;
	for (int x = 0; x < halfallDotsLength; x++)
	{
		ldk::Vec3 curPos = allDotsPtr[x].position;
		int realIndex = halfallDotsLength + x;
		allDotsPtr[realIndex] = Dot({ SCREEN_WIDTH - curPos.x, curPos.y }, allDotsPtr[x].isSpecial);
	}
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

	ldk::render::spriteBatchBegin(gameState->spritesheet);
	ldk::render::spriteBatchSubmit(gameState->background);

	Entity& pacman = gameState->pacman;
	ReadInput(deltaTime, pacman);
	//TODO Move ghosts
	MovePacman(deltaTime, pacman);

	ldk::Sprite& dotSprite = gameState->dotSprite;
	
	Dot* allDotsPtr = gameState->allDots;

	// === DRAW ===
	for (int x = 0; x < DOTS_LENGTH; x++)
	{
		if (allDotsPtr[x].isEnabled)
		{
			dotSprite.position.x = allDotsPtr[x].position.x;
			dotSprite.position.y = allDotsPtr[x].position.y;
			ldk::render::spriteBatchSubmit(gameState->dotSprite);
		}
	}

#ifdef DEBUG_WAYPOINTS //_LDK_DEBUG_
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
			if (gameState->curWaypointIndex != INVALID_WAYPOINT_INDEX)
			{
				// Check if this Dot allows us to move in the desired direction we want
				Waypoint& waypoint = gameState->allWaypoints[gameState->curWaypointIndex];
				int desiredDirAsInt = Vec3ToIntDir(gameState->desiredDir);
				// Check if we can move in the desiredDir
				if ((desiredDirAsInt & waypoint.allowedDirections) == desiredDirAsInt)
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
