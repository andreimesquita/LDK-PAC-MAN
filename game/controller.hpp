int Vec3ToIntDir(const ldk::Vec3);
void HandleVerticalMovement(Entity&);
void HandleHorizontalMovement(Entity&);

void MoveAndCheckWaypoints(const float deltaTime, Entity& pacman)
{
	pacman.sprite.position += pacman.direction * pacman.speed * deltaTime;

	if (pacman.direction.x != 0)
	{
		// Pacman`s moving HORIZONTALLY
		HandleHorizontalMovement(pacman);

		if (pacman.direction.x != 0)
		{
			gameState->currentWaypointIndex = INVALID_WAYPOINT_INDEX;
		}
	}
	else if (gameState->pacman.direction.y != 0)
	{
		// Pacman`s moving VERTICALLY
		HandleVerticalMovement(pacman);

		if (pacman.direction.y != 0)
		{
			gameState->currentWaypointIndex = INVALID_WAYPOINT_INDEX;
		}
	}
	pacman.previousPosition = pacman.sprite.position;
}

void HandleHorizontalMovement(Entity& pacman)
{
	int desiredDirAsInt = Vec3ToIntDir(gameState->desiredDir);
	int currentDirAsInt = (pacman.direction.x > 0) ? 
		BINARY_RIGHT : BINARY_LEFT;
	Waypoint* waypointsPtr = gameState->waypoints;

	for (int i = 0; i < WAYPOINTS_LENGTH; i++)
	{
		// Only execute the next checks if the Y position is the same as the Pacman
		if (floor(pacman.sprite.position.y) == floor(waypointsPtr[i].position.y))
		{
			// Check if he has triggered with a waypoint
			if (pacman.direction.x > 0) // Moving to the right
			{
				if (pacman.sprite.position.x >= waypointsPtr[i].position.x
					&& pacman.previousPosition.x < waypointsPtr[i].position.x)
				{
					if (desiredDirAsInt != 0 && gameState->desiredDir.y != 0)
					{
						if ((desiredDirAsInt & waypointsPtr[i].allowedDirections) == desiredDirAsInt)
						{
							gameState->currentWaypointIndex = INVALID_WAYPOINT_INDEX;
							pacman.direction = gameState->desiredDir;
							pacman.sprite.angle = gameState->desiredAngle;
							pacman.sprite.position.x = waypointsPtr[i].position.x;
							return;
						}
					}

					// Check if we can move on the direction we desire
					if ((currentDirAsInt & waypointsPtr[i].allowedDirections) == currentDirAsInt)
					{
						// Just keep moving in the same direction
						break;
					}
					// Pacman hit a wall
					gameState->currentWaypointIndex = i;
					pacman.direction.x = 0;
					gameState->desiredDir.x = 0;
					pacman.sprite.position.x = waypointsPtr[i].position.x;
				}


			}
			else // Moving to the left
			{
				if (pacman.sprite.position.x <= waypointsPtr[i].position.x
					&& pacman.previousPosition.x > waypointsPtr[i].position.x)
				{
					if (desiredDirAsInt != 0 && gameState->desiredDir.y != 0)
					{
						if ((desiredDirAsInt & waypointsPtr[i].allowedDirections) == desiredDirAsInt)
						{
							gameState->currentWaypointIndex = INVALID_WAYPOINT_INDEX;
							pacman.direction = gameState->desiredDir;
							pacman.sprite.angle = gameState->desiredAngle;
							pacman.sprite.position.x = waypointsPtr[i].position.x;
							return;
						}
					}

					if ((currentDirAsInt & waypointsPtr[i].allowedDirections) == currentDirAsInt)
					{
						// Just keep moving in the same direction
						break;
					}
					// Pacman hit a wall
					gameState->currentWaypointIndex = i;
					pacman.direction.x = 0;
					gameState->desiredDir.x = 0;
					pacman.sprite.position.x = waypointsPtr[i].position.x;
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
	Waypoint* waypointsPtr = gameState->waypoints;

	for (int i = 0; i < WAYPOINTS_LENGTH; i++)
	{
		// Only execute the next checks if the X position is the same of the pacman
		if (floor(pacman.sprite.position.x) == floor(waypointsPtr[i].position.x))
		{
			// Check if he has triggered with a waypoint
			if (pacman.direction.y > 0) // Moving up
			{
				if (pacman.sprite.position.y >= waypointsPtr[i].position.y
					&& pacman.previousPosition.y < waypointsPtr[i].position.y)
				{
					if (desiredDirAsInt != 0 && gameState->desiredDir.x != 0)
					{
						if ((desiredDirAsInt & waypointsPtr[i].allowedDirections) == desiredDirAsInt)
						{
							gameState->currentWaypointIndex = INVALID_WAYPOINT_INDEX;
							pacman.direction = gameState->desiredDir;
							pacman.sprite.angle = gameState->desiredAngle;
							pacman.sprite.position.y = waypointsPtr[i].position.y;
							break;
						}
					}

					if ((currentDirAsInt & waypointsPtr[i].allowedDirections) == currentDirAsInt)
					{
						// Just keep moving in the same direction
						break;
					}
					// Pacman hit a wall
					gameState->currentWaypointIndex = i;
					pacman.direction.y = 0;
					gameState->desiredDir.y = 0;
					pacman.sprite.position.y = waypointsPtr[i].position.y;
					break;
				}
			} 
			else // Moving down
			{
				if (pacman.sprite.position.y <= waypointsPtr[i].position.y
					&& pacman.previousPosition.y > waypointsPtr[i].position.y)
				{
					if (desiredDirAsInt != 0 && gameState->desiredDir.x != 0)
					{
						if ((desiredDirAsInt & waypointsPtr[i].allowedDirections) == desiredDirAsInt)
						{
							gameState->currentWaypointIndex = INVALID_WAYPOINT_INDEX;
							pacman.direction = gameState->desiredDir;
							pacman.sprite.angle = gameState->desiredAngle;
							pacman.sprite.position.y = waypointsPtr[i].position.y;
							break;
						}
					}

					if ((currentDirAsInt & waypointsPtr[i].allowedDirections) == currentDirAsInt)
					{
						// Just keep moving in the same direction
						break;
					}
					// Pacman hit a wall
					gameState->currentWaypointIndex = i;
					gameState->desiredDir.y = 0;
					pacman.direction.y = 0;
					pacman.sprite.position.y = waypointsPtr[i].position.y;
					break;
				}
			}
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
