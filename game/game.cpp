// game.cpp : Defines the exported functions for the DLL application.

#include <../include/ldk/ldk.h>
#include "model.hpp"
#include "controller.hpp"
#include <iostream>

void setupSprite();
void InitializeWaypoints();
void ReadInput(float);
int invertAllowedMovements(int);

void gameInit(void* memory)
{
	LDK_ASSERT(WAYPOINTS_LENGTH % 2 == 0, "WAYPOINTS_LENGTH não é par!");
	gameState = (GameState*)memory;

    // Background
	gameState->spritesheet = ldk::render::loadMaterial("./assets/pacman.cfg");
	
    gameState->background.position = {SCREEN_WIDTH*0.5, SCREEN_HEIGHT*0.5, BACKGROUND_LAYER};
	gameState->background.color ={ 1.0, 1.0, 1.0, 1.0 };
	gameState->background.width = SCREEN_WIDTH;
	gameState->background.height = SCREEN_HEIGHT;
	gameState->background.srcRect = { SCREEN_WIDTH + 2, 0, SCREEN_WIDTH - 2, SCREEN_HEIGHT };
	gameState->background.angle = 0;

    // Pacman
    gameState->pacman.sprite.color ={ 1.0, 1.0, 1.0, 1.0 };
	gameState->pacman.sprite.width = 14;
	gameState->pacman.sprite.height = 14;
	gameState->pacman.sprite.srcRect = { 473, 1, 13, 13 };
	gameState->pacman.sprite.angle = 0;
	gameState->pacman.sprite.position = {114, SCREEN_HEIGHT - 140, PACMAN_LAYER};
	gameState->pacman.previousPosition = gameState->pacman.sprite.position;
	gameState->pacman.speed = 60;
    gameState->pacman.direction = {0,0,0};
	gameState->desireAngle = RADIAN(0);
    
	// Waypoint
	gameState->WaypointSprite.color ={ 1.0, 1.0, 1.0, 1.0 };
	gameState->WaypointSprite.width = 2;
	gameState->WaypointSprite.height = 2;
	gameState->WaypointSprite.srcRect = {500,20,1,1};
	gameState->WaypointSprite.angle = 0;
	gameState->WaypointSprite.position = {0, 0, WAYPOINT_LAYER};

	InitializeWaypoints();

	gameState->pacman.sprite.position.y = gameState->Waypoints[20].Position.y;

	ldk::render::spriteBatchInit();
}

void gameStart() { }

void gameStop() { }

void gameUpdate(float deltaTime)
{
	deltaTime = MIN(deltaTime, 0.016f);

	ldk::render::spriteBatchBegin(gameState->spritesheet);
	ldk::render::spriteBatchSubmit(gameState->background);
	
	// pacman
	ReadInput(deltaTime);
	MoveAndCheckWaypoints(deltaTime);
    
    // Check if we need to teleport the pacman
    if (gameState->pacman.sprite.position.x < -5)
    {
        gameState->pacman.sprite.position.x = SCREEN_WIDTH + 4;
    }
    else if (gameState->pacman.sprite.position.x > SCREEN_WIDTH + 5)
    {
        gameState->pacman.sprite.position.x = -5;
    }
    
#if DEBUG_WAYPOINTS
	// waypoints
	ldk::Sprite& waypointSprite = gameState->WaypointSprite;
	Waypoint* waypoints = gameState->Waypoints;
	for(int x = 0; x < WAYPOINTS_LENGTH; x++)
	{
		waypointSprite.position.x = waypoints[x].Position.x;
		waypointSprite.position.y = waypoints[x].Position.y;
		ldk::render::spriteBatchSubmit(gameState->WaypointSprite);
	}
#endif
	ldk::render::spriteBatchSubmit(gameState->pacman.sprite);
	ldk::render::spriteBatchEnd();
}

void InitializeWaypoints()
{
	Waypoint* waypointsPtr = gameState->Waypoints;
	
    // X 13
	waypointsPtr[0]  = Waypoint({13, SCREEN_HEIGHT - 12, 0});
	waypointsPtr[0].allowedMovements = (BINARY_DOWN | BINARY_RIGHT);    
    waypointsPtr[1]  = Waypoint({13, SCREEN_HEIGHT - 43, 0});
    waypointsPtr[1].allowedMovements = (BINARY_DOWN | BINARY_RIGHT | BINARY_UP);    
	waypointsPtr[2]  = Waypoint({13, SCREEN_HEIGHT - 67, 0});
    waypointsPtr[2].allowedMovements = (BINARY_RIGHT | BINARY_UP);
	waypointsPtr[3]  = Waypoint({13, SCREEN_HEIGHT - 163, 0});
    waypointsPtr[3].allowedMovements = (BINARY_RIGHT | BINARY_DOWN);    
	waypointsPtr[4]  = Waypoint({13, SCREEN_HEIGHT - 187, 0});
    waypointsPtr[4].allowedMovements = (BINARY_RIGHT | BINARY_UP);    
	waypointsPtr[5]  = Waypoint({13, SCREEN_HEIGHT - 211, 0});
    waypointsPtr[5].allowedMovements = (BINARY_RIGHT | BINARY_DOWN);    
	waypointsPtr[6]  = Waypoint({13, SCREEN_HEIGHT - 235, 0});
    waypointsPtr[6].allowedMovements = (BINARY_RIGHT | BINARY_UP);
    
    // X 29
	waypointsPtr[7]  = Waypoint({29, SCREEN_HEIGHT - 187, 0});
    waypointsPtr[7].allowedMovements = (BINARY_LEFT | BINARY_DOWN);    
	waypointsPtr[8]  = Waypoint({29, SCREEN_HEIGHT - 211, 0});
    waypointsPtr[8].allowedMovements = (BINARY_RIGHT | BINARY_UP | BINARY_LEFT);
	
    // X 53
	waypointsPtr[9]  = Waypoint({53, SCREEN_HEIGHT - 12, 0});
    waypointsPtr[9].allowedMovements = (BINARY_RIGHT | BINARY_LEFT | BINARY_DOWN);
	waypointsPtr[10]  = Waypoint({53, SCREEN_HEIGHT - 43, 0});
    waypointsPtr[10].allowedMovements = (BINARY_RIGHT | BINARY_LEFT | BINARY_DOWN | BINARY_UP);
	waypointsPtr[11]  = Waypoint({53, SCREEN_HEIGHT - 67, 0});    
    waypointsPtr[11].allowedMovements = (BINARY_LEFT | BINARY_UP | BINARY_DOWN);
	waypointsPtr[12]  = Waypoint({53, SCREEN_HEIGHT - 115, 0});
    waypointsPtr[12].allowedMovements = (BINARY_LEFT | BINARY_RIGHT | BINARY_UP | BINARY_DOWN);
	waypointsPtr[13]  = Waypoint({53, SCREEN_HEIGHT - 163, 0});
    waypointsPtr[13].allowedMovements = (BINARY_LEFT | BINARY_RIGHT | BINARY_UP | BINARY_DOWN);
	waypointsPtr[14]  = Waypoint({53, SCREEN_HEIGHT - 187, 0});
    waypointsPtr[14].allowedMovements = (BINARY_RIGHT | BINARY_UP | BINARY_DOWN);
	waypointsPtr[15]  = Waypoint({53, SCREEN_HEIGHT - 211, 0});
    waypointsPtr[15].allowedMovements = (BINARY_LEFT | BINARY_UP);
	
    // X 77
	waypointsPtr[16]  = Waypoint({77, SCREEN_HEIGHT - 43, 0});
    waypointsPtr[16].allowedMovements = (BINARY_DOWN | BINARY_RIGHT | BINARY_LEFT);
	waypointsPtr[17]  = Waypoint({77, SCREEN_HEIGHT - 67, 0});
	waypointsPtr[17].allowedMovements = (BINARY_UP | BINARY_RIGHT);
    waypointsPtr[18]  = Waypoint({77, SCREEN_HEIGHT - 91, 0});
	waypointsPtr[18].allowedMovements = (BINARY_DOWN | BINARY_RIGHT);
    waypointsPtr[19] = Waypoint({77, SCREEN_HEIGHT - 115, 0});
    waypointsPtr[19].allowedMovements = (BINARY_DOWN | BINARY_LEFT | BINARY_UP);
	waypointsPtr[20] = Waypoint({77, SCREEN_HEIGHT - 137, 0});
	waypointsPtr[20].allowedMovements = (BINARY_RIGHT | BINARY_DOWN | BINARY_UP);
	waypointsPtr[21] = Waypoint({77, SCREEN_HEIGHT - 163, 0});
    waypointsPtr[21].allowedMovements = (BINARY_RIGHT | BINARY_LEFT | BINARY_UP);
	waypointsPtr[22] = Waypoint({77, SCREEN_HEIGHT - 187, 0});
    waypointsPtr[22].allowedMovements = (BINARY_RIGHT | BINARY_LEFT | BINARY_DOWN);
	waypointsPtr[23] = Waypoint({77, SCREEN_HEIGHT - 211, 0});
    waypointsPtr[23].allowedMovements = (BINARY_RIGHT | BINARY_UP);
    
	// X 101
	waypointsPtr[24]  = Waypoint({101, SCREEN_HEIGHT - 12, 0});
    waypointsPtr[24].allowedMovements = (BINARY_LEFT | BINARY_DOWN);
	waypointsPtr[25]  = Waypoint({101, SCREEN_HEIGHT - 43, 0});
    waypointsPtr[25].allowedMovements = (BINARY_LEFT | BINARY_RIGHT | BINARY_UP);
	waypointsPtr[26] = Waypoint({101, SCREEN_HEIGHT - 67, 0});
    waypointsPtr[26].allowedMovements = (BINARY_LEFT | BINARY_DOWN);
	waypointsPtr[27] = Waypoint({101, SCREEN_HEIGHT - 91, 0});
    waypointsPtr[27].allowedMovements = (BINARY_LEFT | BINARY_RIGHT | BINARY_UP);
	waypointsPtr[28]  = Waypoint({101, SCREEN_HEIGHT - 163, 0});
    waypointsPtr[28].allowedMovements = (BINARY_LEFT | BINARY_DOWN);
	waypointsPtr[29]  = Waypoint({101, SCREEN_HEIGHT - 187, 0});
    waypointsPtr[29].allowedMovements = (BINARY_LEFT | BINARY_RIGHT | BINARY_UP);
	waypointsPtr[30]  = Waypoint({101, SCREEN_HEIGHT - 211, 0});
    waypointsPtr[30].allowedMovements = (BINARY_LEFT | BINARY_DOWN);
	waypointsPtr[31]  = Waypoint({101, SCREEN_HEIGHT - 235, 0});
    waypointsPtr[31].allowedMovements = (BINARY_LEFT | BINARY_RIGHT | BINARY_UP);

	// Copy information from the left side to the right side
	int halfWaypointsLength = (int) WAYPOINTS_LENGTH / 2;
	for (int x = 0; x < halfWaypointsLength; x++)
	{
		ldk::Vec3 curPos = waypointsPtr[x].Position;
		int realIndex = halfWaypointsLength + x;
		waypointsPtr[realIndex] = Waypoint({SCREEN_WIDTH - curPos.x, curPos.y});
        waypointsPtr[realIndex].allowedMovements = invertAllowedMovements(waypointsPtr[x].allowedMovements);
	}
}

int invertAllowedMovements(int allowedMovements)
{
    int result = allowedMovements & (BINARY_UP | BINARY_DOWN);
    
    if ((allowedMovements & (BINARY_LEFT | BINARY_RIGHT)) != (BINARY_LEFT | BINARY_RIGHT))
    {
        // Invert L and R
        result |= ~allowedMovements & (BINARY_LEFT | BINARY_RIGHT);
    }
    else
    {
        result |= (BINARY_LEFT | BINARY_RIGHT);
    }
    
    return result;
}

ldk::Vec3 negateVec3(ldk::Vec3 vector)
{
	ldk::Vec3 inverse;
	inverse.x = -vector.x;
	inverse.y = -vector.y;
	inverse.z = -vector.z;
	return inverse;
}

void ReadInput(float deltaTime)
{
	Entity& pacman = gameState->pacman;

   // Control
	if (ldk::input::isKeyDown(LDK_KEY_LEFT))
	{
   	    gameState->desireAngle = RADIAN(180);
		gameState->desiredDir = LEFT_DIR;
	}
	else if (ldk::input::isKeyDown(LDK_KEY_RIGHT))
	{
   	    gameState->desireAngle = 0;
		gameState->desiredDir = RIGHT_DIR;
	}
	else if (ldk::input::isKeyDown(LDK_KEY_UP))
	{
	    gameState->desireAngle = RADIAN(90);
		gameState->desiredDir = UP_DIR;
	}
	else if (ldk::input::isKeyDown(LDK_KEY_DOWN))
	{
	    gameState->desireAngle = RADIAN(270);
		gameState->desiredDir = DOWN_DIR;
	}

    // Immediately direction change is only allowed on the same line of movement (Horizontally or Vertically)
	ldk::Vec3 blankVec = {0,0,0}; // Just a {0,0,0} vector
	if (!(gameState->desiredDir == blankVec))
	{
        if (!(pacman.direction == blankVec) 
            && !(pacman.direction == negateVec3(gameState->desiredDir)))
        {
            return;
        }
        
        //If we`ve stopped on an Waypoint
        if (gameState->currentWaypointIndex != 0)
        {
            // Check if this waypoint allows us to move in the desired direction we want
            Waypoint& waypoint = gameState->Waypoints[gameState->currentWaypointIndex];
            int desiredDirAsInt = Vec3ToIntDir(gameState->desiredDir);
            if ((desiredDirAsInt & waypoint.allowedMovements) != desiredDirAsInt)
            {
                return;
            }
        }
        
		pacman.sprite.angle = gameState->desireAngle;
		pacman.direction = gameState->desiredDir;
	}
}