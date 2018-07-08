int Vec3ToIntDir(ldk::Vec3);
void MoveAndCheckWaypoints(float);
void HandleVerticalMovement(Entity&);
void HandleHorizontalMovement(Entity&);

void MoveAndCheckWaypoints(float deltaTime)
{
	Entity& pacman = gameState->pacman;
	pacman.sprite.position += pacman.direction * pacman.speed * deltaTime;

	if (pacman.direction.x != 0) // He`s moving HORIZONTALLY
	{
        HandleHorizontalMovement(pacman);
        
        if (pacman.direction.x != 0)
        {
            gameState->currentWaypointIndex = 0;
        }
	}
	else if (gameState->pacman.direction.y != 0) // He`s moving VERTICALLY
	{
		HandleVerticalMovement(pacman);
        
        if (pacman.direction.y != 0)
        {
            gameState->currentWaypointIndex = 0;
        }
	}
	pacman.previousPosition = pacman.sprite.position;
    LogInfo("%i", gameState->currentWaypointIndex);
}

void HandleHorizontalMovement(Entity& pacman)
{
    int currentDirAsInt = (gameState->pacman.direction.x > 0) ? 
        BINARY_RIGHT : BINARY_LEFT;
    Waypoint* waypointsPtr = gameState->Waypoints;

    for (int i = 0; i < WAYPOINTS_LENGTH; i++)
    {
        // Only execute the next checks if the Y position is the same of the pacman
        if (floor(pacman.sprite.position.y) == floor(waypointsPtr[i].Position.y))
        {
            // Check if he has "collided" with one waypoint
            
            // Moving to the right
            if (pacman.direction.x > 0)
            {
                if (pacman.sprite.position.x >= waypointsPtr[i].Position.x
                    && pacman.previousPosition.x < waypointsPtr[i].Position.x)
                {
                    // Check if we can move on the direction we desire
                    if ((currentDirAsInt & waypointsPtr[i].allowedMovements) == currentDirAsInt)
                    {
                        pacman.sprite.position.x = waypointsPtr[i].Position.x;
                        pacman.sprite.angle = gameState->desireAngle;
                        pacman.direction = gameState->desiredDir;
                        break;
                    }

                    // We've hit with a wall
                    gameState->currentWaypointIndex = i;
                    pacman.direction.x = 0;
                    gameState->desiredDir.x = 0;
                    pacman.sprite.position.x = waypointsPtr[i].Position.x;
                }
            }
            else 
            {    
                // Moving to the left
                if (pacman.sprite.position.x <= waypointsPtr[i].Position.x
                    && pacman.previousPosition.x > waypointsPtr[i].Position.x)
                {                        
                    if ((currentDirAsInt & waypointsPtr[i].allowedMovements) == currentDirAsInt)
                    {
                        pacman.sprite.position.x = waypointsPtr[i].Position.x;
                        pacman.sprite.angle = gameState->desireAngle;
                        pacman.direction = gameState->desiredDir;
                        break;
                    }

                    gameState->currentWaypointIndex = i;
                    pacman.direction.x = 0;
                    gameState->desiredDir.x = 0;
                    pacman.sprite.position.x = waypointsPtr[i].Position.x;
                }
            }
        }
    }
}

void HandleVerticalMovement(Entity& pacman)
{
    int desiredDirAsInt = Vec3ToIntDir(gameState->desiredDir);
    int currentDirAsInt = (gameState->pacman.direction.y > 0) ? 
        BINARY_UP : BINARY_DOWN;
	Waypoint* waypointsPtr = gameState->Waypoints;
    
    for (int i = 0; i < WAYPOINTS_LENGTH; i++)
    {
        // Only execute the next checks if the X position is the same of the pacman
        if (floor(pacman.sprite.position.x) == floor(waypointsPtr[i].Position.x))
        {
            // Check if he has "collided" with one waypoint
            
            // Moving upwards
            if (pacman.direction.y > 0)
            {
                if (pacman.sprite.position.y >= waypointsPtr[i].Position.y
                    && pacman.previousPosition.y < waypointsPtr[i].Position.y) // We`re moving up
                {
                    if ((currentDirAsInt & waypointsPtr[i].allowedMovements) == currentDirAsInt)
                    {
                        pacman.sprite.position.y = waypointsPtr[i].Position.y;
                        pacman.sprite.angle = gameState->desireAngle;
                        pacman.direction = gameState->desiredDir;
                        break;
                    }

                    gameState->currentWaypointIndex = i;
                    pacman.direction.y = 0;
                    gameState->desiredDir.y = 0;
                    pacman.sprite.position.y = waypointsPtr[i].Position.y;
                    break;
                }
            }
            else
            {
                // Moving downwards
                if (pacman.sprite.position.y <= waypointsPtr[i].Position.y
                    && pacman.previousPosition.y > waypointsPtr[i].Position.y)
                {
                    if ((currentDirAsInt & waypointsPtr[i].allowedMovements) == currentDirAsInt)
                    {
                        pacman.sprite.position.y = waypointsPtr[i].Position.y;
                        pacman.sprite.angle = gameState->desireAngle;
                        pacman.direction = gameState->desiredDir;
                        break;
                    }

                    gameState->currentWaypointIndex = i;
                    gameState->desiredDir.y = 0;
                    pacman.direction.y = 0;
                    pacman.sprite.position.y = waypointsPtr[i].Position.y;
                    break;
                }
            }
        }
    }
}

int Vec3ToIntDir(ldk::Vec3 direction)
{
    if (direction.x != 0)
    {
        return (direction.x > 0) ? BINARY_RIGHT : BINARY_LEFT;
    }
    return (direction.y > 0) ? BINARY_UP : BINARY_DOWN;
}