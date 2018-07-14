int Vec3ToIntDir(const ldk::Vec3);
void HandleHorizontalDots(Entity&);
void HandleVerticalDots(Entity&);
void HandleHorizontalWaypoints(Entity&);
void HandleVerticalWaypoints(Entity&);
void inline EvaluateDot(Dot&);

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

void HandleHorizontalDots(Entity& pacman)
{
	Dot* allDotsPtr = gameState->allDots;

	if (pacman.direction.x > 0)
	{
		for (int i = 0; i < DOTS_LENGTH; i++)
		{
			if (!allDotsPtr[i].isEnabled)
			{
				continue;
			}
		
			// Only execute the next checks if the Y position is the same as the Pacman
			if (floor(pacman.sprite.position.y) == floor(allDotsPtr[i].position.y))
			{
				// Pacman's moving to the right
				if (pacman.sprite.position.x >= allDotsPtr[i].position.x
					&& pacman.previousPosition.x <= allDotsPtr[i].position.x)
				{
					EvaluateDot(allDotsPtr[i]);
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < DOTS_LENGTH; i++)
		{
			if (!allDotsPtr[i].isEnabled)
			{
				continue;
			}
		
			// Only execute the next checks if the Y position is the same as the Pacman
			if (floor(pacman.sprite.position.y) == floor(allDotsPtr[i].position.y))
			{
				// Pacman's moving to the left
				if (pacman.sprite.position.x <= allDotsPtr[i].position.x
					&& pacman.previousPosition.x >= allDotsPtr[i].position.x)
				{
					EvaluateDot(allDotsPtr[i]);
				}
			}
		}
	}
}

void HandleVerticalDots(Entity& pacman)
{
	Dot* allDotsPtr = gameState->allDots;

	if (pacman.direction.y > 0)
	{
		for (int i = 0; i < DOTS_LENGTH; i++)
		{
			// Only execute the next checks if the Y position is the same as the Pacman
			if (floor(pacman.sprite.position.x) == floor(allDotsPtr[i].position.x))
			{
				// Pacman's moving to the right
				if (pacman.sprite.position.y >= allDotsPtr[i].position.y
					&& pacman.previousPosition.y <= allDotsPtr[i].position.y)
				{
					EvaluateDot(allDotsPtr[i]);
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < DOTS_LENGTH; i++)
		{
			// Only execute the next checks if the Y position is the same as the Pacman
			if (floor(pacman.sprite.position.x) == floor(allDotsPtr[i].position.x))
			{
				// Pacman's moving to the left
				if (pacman.sprite.position.y <= allDotsPtr[i].position.y
					&& pacman.previousPosition.y >= allDotsPtr[i].position.y)
				{
					if (allDotsPtr[i].isEnabled)
					{
						EvaluateDot(allDotsPtr[i]);
					}
				}
			}
		}
	}
}

void inline EvaluateDot(Dot& dot)
{
	dot.isEnabled = false;
	gameState->playerPoints += dot.isSpecial ? 20 : 5;
	LogInfo("POINT RECEIVED! total=%i", gameState->playerPoints);
}

void HandleHorizontalWaypoints(Entity& pacman)
{
	int desiredDirAsInt = Vec3ToIntDir(gameState->desiredDir);
	int currentDirAsInt = (pacman.direction.x > 0) ? BINARY_RIGHT : BINARY_LEFT;
	Waypoint* allWaypointsPtr = gameState->allWaypoints;

	if (pacman.direction.x > 0)
	{
		for (int i = 0; i < WAYPOINTS_LENGTH; i++)
		{
			// Only execute the next checks if the Y position is the same as the Pacman
			if (floor(pacman.sprite.position.y) == floor(allWaypointsPtr[i].position.y))
			{
				// Pacman's moving to the right
				if (pacman.sprite.position.x >= allWaypointsPtr[i].position.x
					&& pacman.previousPosition.x < allWaypointsPtr[i].position.x)
				{
					if (desiredDirAsInt != 0 && gameState->desiredDir.y != 0)
					{
						if ((desiredDirAsInt & allWaypointsPtr[i].allowedDirections) == desiredDirAsInt)
						{
							gameState->curWaypointIndex = INVALID_WAYPOINT_INDEX;
							pacman.direction = gameState->desiredDir;
							pacman.sprite.angle = gameState->desiredAngle;
							pacman.sprite.position.x = allWaypointsPtr[i].position.x;
							continue;
						}
					}

					// Check if we can move on the direction we desire
					if ((currentDirAsInt & allWaypointsPtr[i].allowedDirections) == currentDirAsInt)
					{
						// Just keep moving in the same direction
						continue;
					}

					// Pacman hit a wall
					gameState->curWaypointIndex = i;
					pacman.direction.x = 0;
					gameState->desiredDir.x = 0;
					pacman.sprite.position.x = allWaypointsPtr[i].position.x;
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < WAYPOINTS_LENGTH; i++)
		{
			// Only execute the next checks if the Y position is the same as the Pacman
			if (floor(pacman.sprite.position.y) == floor(allWaypointsPtr[i].position.y))
			{
				// Pacman's moving to the left
				if (pacman.sprite.position.x <= allWaypointsPtr[i].position.x
					&& pacman.previousPosition.x > allWaypointsPtr[i].position.x)
				{
					if (desiredDirAsInt != 0 && gameState->desiredDir.y != 0)
					{
						if ((desiredDirAsInt & allWaypointsPtr[i].allowedDirections) == desiredDirAsInt)
						{
							gameState->curWaypointIndex = INVALID_WAYPOINT_INDEX;
							pacman.direction = gameState->desiredDir;
							pacman.sprite.angle = gameState->desiredAngle;
							pacman.sprite.position.x = allWaypointsPtr[i].position.x;
							continue;
						}
					}

					if ((currentDirAsInt & allWaypointsPtr[i].allowedDirections) == currentDirAsInt)
					{
						// Just keep moving in the same direction
						continue;
					}

					// Pacman hit a wall
					gameState->curWaypointIndex = i;
					pacman.direction.x = 0;
					gameState->desiredDir.x = 0;
					pacman.sprite.position.x = allWaypointsPtr[i].position.x;
				}
			}
		}
	}
}

void HandleVerticalWaypoints(Entity& pacman)
{
	int desiredDirAsInt = Vec3ToIntDir(gameState->desiredDir);
	int currentDirAsInt = (gameState->pacman.direction.y > 0) ?
		BINARY_UP : BINARY_DOWN;
	Waypoint* allWaypointsPtr = gameState->allWaypoints;

	for (int i = 0; i < WAYPOINTS_LENGTH; i++)
	{
		// Only execute the next checks if the X position is the same of the pacman
		if (floor(pacman.sprite.position.x) == floor(allWaypointsPtr[i].position.x))
		{
			// Check if he has triggered with a Dot
			if (pacman.direction.y > 0) // Moving up
			{
				if (pacman.sprite.position.y >= allWaypointsPtr[i].position.y
					&& pacman.previousPosition.y < allWaypointsPtr[i].position.y)
				{
					if (desiredDirAsInt != 0 && gameState->desiredDir.x != 0)
					{
						if ((desiredDirAsInt & allWaypointsPtr[i].allowedDirections) == desiredDirAsInt)
						{
							gameState->curWaypointIndex = INVALID_WAYPOINT_INDEX;
							pacman.direction = gameState->desiredDir;
							pacman.sprite.angle = gameState->desiredAngle;
							pacman.sprite.position.y = allWaypointsPtr[i].position.y;
							break;
						}
					}

					if ((currentDirAsInt & allWaypointsPtr[i].allowedDirections) == currentDirAsInt)
					{
						// Just keep moving in the same direction
						break;
					}
					// Pacman hit a wall
					gameState->curWaypointIndex = i;
					pacman.direction.y = 0;
					gameState->desiredDir.y = 0;
					pacman.sprite.position.y = allWaypointsPtr[i].position.y;
					break;
				}
			} 
			else // Moving down
			{
				if (pacman.sprite.position.y <= allWaypointsPtr[i].position.y
					&& pacman.previousPosition.y > allWaypointsPtr[i].position.y)
				{
					if (desiredDirAsInt != 0 && gameState->desiredDir.x != 0)
					{
						if ((desiredDirAsInt & allWaypointsPtr[i].allowedDirections) == desiredDirAsInt)
						{
							gameState->curWaypointIndex = INVALID_WAYPOINT_INDEX;
							pacman.direction = gameState->desiredDir;
							pacman.sprite.angle = gameState->desiredAngle;
							pacman.sprite.position.y = allWaypointsPtr[i].position.y;
							break;
						}
					}

					if ((currentDirAsInt & allWaypointsPtr[i].allowedDirections) == currentDirAsInt)
					{
						// Just keep moving in the same direction
						break;
					}
					// Pacman hit a wall
					gameState->curWaypointIndex = i;
					gameState->desiredDir.y = 0;
					pacman.direction.y = 0;
					pacman.sprite.position.y = allWaypointsPtr[i].position.y;
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
