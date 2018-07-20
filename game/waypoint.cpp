void HandleVerticalWaypoints(Entity& pacman);
void HandleHorizontalWaypoints(Entity& pacman);

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

void initializeWaypoints()
{
	// WAYPOINTS
	// C1 - X 13
	allWaypoints[0] = Waypoint({ 13, SCREEN_HEIGHT - 12, 0 });
	allWaypoints[0].allowedDirections = (BINARY_DOWN | BINARY_RIGHT);
	allWaypoints[1] = Waypoint({ 13, SCREEN_HEIGHT - 43, 0 });
	allWaypoints[1].allowedDirections = (BINARY_DOWN | BINARY_RIGHT | BINARY_UP);
	allWaypoints[2] = Waypoint({ 13, SCREEN_HEIGHT - 67, 0 });
	allWaypoints[2].allowedDirections = (BINARY_RIGHT | BINARY_UP);
	allWaypoints[3] = Waypoint({ 13, SCREEN_HEIGHT - 163, 0 });
	allWaypoints[3].allowedDirections = (BINARY_RIGHT | BINARY_DOWN);
	allWaypoints[4] = Waypoint({ 13, SCREEN_HEIGHT - 187, 0 });
	allWaypoints[4].allowedDirections = (BINARY_RIGHT | BINARY_UP);
	allWaypoints[5] = Waypoint({ 13, SCREEN_HEIGHT - 211, 0 });
	allWaypoints[5].allowedDirections = (BINARY_RIGHT | BINARY_DOWN);
	allWaypoints[6] = Waypoint({ 13, SCREEN_HEIGHT - 235, 0 });
	allWaypoints[6].allowedDirections = (BINARY_RIGHT | BINARY_UP);

	// C2 - X 29
	allWaypoints[7] = Waypoint({ 29, SCREEN_HEIGHT - 187, 0 });
	allWaypoints[7].allowedDirections = (BINARY_LEFT | BINARY_DOWN);
	allWaypoints[8] = Waypoint({ 29, SCREEN_HEIGHT - 211, 0 });
	allWaypoints[8].allowedDirections = (BINARY_RIGHT | BINARY_UP | BINARY_LEFT);

	// C3 - X 53
	allWaypoints[9] = Waypoint({ 53, SCREEN_HEIGHT - 12, 0 });
	allWaypoints[9].allowedDirections = (BINARY_RIGHT | BINARY_LEFT | BINARY_DOWN);
	allWaypoints[10] = Waypoint({ 53, SCREEN_HEIGHT - 43, 0 });
	allWaypoints[10].allowedDirections = (BINARY_RIGHT | BINARY_LEFT | BINARY_DOWN | BINARY_UP);
	allWaypoints[11] = Waypoint({ 53, SCREEN_HEIGHT - 67, 0 });
	allWaypoints[11].allowedDirections = (BINARY_LEFT | BINARY_UP | BINARY_DOWN);
	allWaypoints[12] = Waypoint({ 53, SCREEN_HEIGHT - 115, 0 });
	allWaypoints[12].allowedDirections = (BINARY_LEFT | BINARY_RIGHT | BINARY_UP | BINARY_DOWN);
	allWaypoints[13] = Waypoint({ 53, SCREEN_HEIGHT - 163, 0 });
	allWaypoints[13].allowedDirections = (BINARY_LEFT | BINARY_RIGHT | BINARY_UP | BINARY_DOWN);
	allWaypoints[14] = Waypoint({ 53, SCREEN_HEIGHT - 187, 0 });
	allWaypoints[14].allowedDirections = (BINARY_RIGHT | BINARY_UP | BINARY_DOWN);
	allWaypoints[15] = Waypoint({ 53, SCREEN_HEIGHT - 211, 0 });
	allWaypoints[15].allowedDirections = (BINARY_LEFT | BINARY_UP);

	// C4 - X 77
	allWaypoints[16] = Waypoint({ 77, SCREEN_HEIGHT - 43, 0 });
	allWaypoints[16].allowedDirections = (BINARY_DOWN | BINARY_RIGHT | BINARY_LEFT);
	allWaypoints[17] = Waypoint({ 77, SCREEN_HEIGHT - 67, 0 });
	allWaypoints[17].allowedDirections = (BINARY_UP | BINARY_RIGHT);
	allWaypoints[18] = Waypoint({ 77, SCREEN_HEIGHT - 91, 0 });
	allWaypoints[18].allowedDirections = (BINARY_DOWN | BINARY_RIGHT);
	allWaypoints[19] = Waypoint({ 77, SCREEN_HEIGHT - 115, 0 });
	allWaypoints[19].allowedDirections = (BINARY_DOWN | BINARY_LEFT | BINARY_UP);
	allWaypoints[20] = Waypoint({ 77, SCREEN_HEIGHT - 137, 0 });
	allWaypoints[20].allowedDirections = (BINARY_RIGHT | BINARY_DOWN | BINARY_UP);
	allWaypoints[21] = Waypoint({ 77, SCREEN_HEIGHT - 163, 0 });
	allWaypoints[21].allowedDirections = (BINARY_RIGHT | BINARY_LEFT | BINARY_UP);
	allWaypoints[22] = Waypoint({ 77, SCREEN_HEIGHT - 187, 0 });
	allWaypoints[22].allowedDirections = (BINARY_RIGHT | BINARY_LEFT | BINARY_DOWN);
	allWaypoints[23] = Waypoint({ 77, SCREEN_HEIGHT - 211, 0 });
	allWaypoints[23].allowedDirections = (BINARY_RIGHT | BINARY_UP);

	// C5 - X 101
	allWaypoints[24] = Waypoint({ 101, SCREEN_HEIGHT - 12, 0 });
	allWaypoints[24].allowedDirections = (BINARY_LEFT | BINARY_DOWN);
	allWaypoints[25] = Waypoint({ 101, SCREEN_HEIGHT - 43, 0 });
	allWaypoints[25].allowedDirections = (BINARY_LEFT | BINARY_RIGHT | BINARY_UP);
	allWaypoints[26] = Waypoint({ 101, SCREEN_HEIGHT - 67, 0 });
	allWaypoints[26].allowedDirections = (BINARY_LEFT | BINARY_DOWN);
	allWaypoints[27] = Waypoint({ 101, SCREEN_HEIGHT - 91, 0 });
	allWaypoints[27].allowedDirections = (BINARY_LEFT | BINARY_RIGHT | BINARY_UP);
	allWaypoints[28] = Waypoint({ 101, SCREEN_HEIGHT - 163, 0 });
	allWaypoints[28].allowedDirections = (BINARY_LEFT | BINARY_DOWN);
	allWaypoints[29] = Waypoint({ 101, SCREEN_HEIGHT - 187, 0 });
	allWaypoints[29].allowedDirections = (BINARY_LEFT | BINARY_RIGHT | BINARY_UP);
	allWaypoints[30] = Waypoint({ 101, SCREEN_HEIGHT - 211, 0 });
	allWaypoints[30].allowedDirections = (BINARY_LEFT | BINARY_DOWN);
	allWaypoints[31] = Waypoint({ 101, SCREEN_HEIGHT - 235, 0 });
	allWaypoints[31].allowedDirections = (BINARY_LEFT | BINARY_RIGHT | BINARY_UP);

	// Copy all information from the left side to the right side of the map
	int halfallDotsLength = (int)(WAYPOINTS_LENGTH-1) / 2;
	for (int x = 0; x < halfallDotsLength; x++)
	{
		Waypoint& waypoint = allWaypoints[halfallDotsLength + x];
		waypoint.position = {SCREEN_WIDTH - allWaypoints[x].position.x, allWaypoints[x].position.y, 0};
		waypoint.allowedDirections = InvertHorizontalDirection(allWaypoints[x].allowedDirections);
	}
	
	allWaypoints[WAYPOINTS_LENGTH-1].position.x = 114;
	allWaypoints[WAYPOINTS_LENGTH-1].position.y = allWaypoints[29].position.y;
	allWaypoints[WAYPOINTS_LENGTH-1].allowedDirections = (BINARY_LEFT | BINARY_RIGHT);
}

void HandleHorizontalWaypoints(Entity& pacman)
{
	int desiredDirAsInt = Vec3ToIntDir(gameState->pacman.desiredDir);
	int currentDirAsInt = (pacman.direction.x > 0) ? BINARY_RIGHT : BINARY_LEFT;
	
	if (pacman.direction.x > 0)
	{
		for (int i = 0; i < WAYPOINTS_LENGTH; i++)
		{
			// Only execute the next checks if the Y position is the same as the Pacman
			if (floor(pacman.sprite.position.y) == floor(allWaypoints[i].position.y))
			{
				// Pacman's moving to the right
				if (pacman.sprite.position.x >= allWaypoints[i].position.x
					&& pacman.previousPosition.x < allWaypoints[i].position.x)
				{
					if (desiredDirAsInt != 0 && gameState->pacman.desiredDir.y != 0)
					{
						if ((desiredDirAsInt & allWaypoints[i].allowedDirections) == desiredDirAsInt)
						{
							gameState->pacman.curWaypointIndex = INVALID_WAYPOINT_INDEX;
							pacman.direction = gameState->pacman.desiredDir;
							pacman.sprite.angle = gameState->pacman.desiredAngle;
							pacman.sprite.position.x = allWaypoints[i].position.x;
							continue;
						}
					}

					// Check if we can move on the direction we desire
					if ((currentDirAsInt & allWaypoints[i].allowedDirections) == currentDirAsInt)
					{
						// Just keep moving in the same direction
						continue;
					}

					// Pacman hit a wall
					gameState->pacman.curWaypointIndex = i;
					pacman.direction.x = 0;
					gameState->pacman.desiredDir.x = 0;
					pacman.sprite.position.x = allWaypoints[i].position.x;
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < WAYPOINTS_LENGTH; i++)
		{
			// Only execute the next checks if the Y position is the same as the Pacman
			if (floor(pacman.sprite.position.y) == floor(allWaypoints[i].position.y))
			{
				// Pacman's moving to the left
				if (pacman.sprite.position.x <= allWaypoints[i].position.x
					&& pacman.previousPosition.x > allWaypoints[i].position.x)
				{
					if (desiredDirAsInt != 0 && gameState->pacman.desiredDir.y != 0)
					{
						if ((desiredDirAsInt & allWaypoints[i].allowedDirections) == desiredDirAsInt)
						{
							gameState->pacman.curWaypointIndex = INVALID_WAYPOINT_INDEX;
							pacman.direction = gameState->pacman.desiredDir;
							pacman.sprite.angle = gameState->pacman.desiredAngle;
							pacman.sprite.position.x = allWaypoints[i].position.x;
							continue;
						}
					}

					if ((currentDirAsInt & allWaypoints[i].allowedDirections) == currentDirAsInt)
					{
						// Just keep moving in the same direction
						continue;
					}

					// Pacman hit a wall
					gameState->pacman.curWaypointIndex = i;
					pacman.direction.x = 0;
					gameState->pacman.desiredDir.x = 0;
					pacman.sprite.position.x = allWaypoints[i].position.x;
				}
			}
		}
	}
}

void HandleVerticalWaypoints(Entity& pacman)
{
	int desiredDirAsInt = Vec3ToIntDir(gameState->pacman.desiredDir);
	int currentDirAsInt = (gameState->pacman.direction.y > 0) ?
		BINARY_UP : BINARY_DOWN;

	for (int i = 0; i < WAYPOINTS_LENGTH; i++)
	{
		// Only execute the next checks if the X position is the same of the pacman
		if (floor(pacman.sprite.position.x) == floor(allWaypoints[i].position.x))
		{
			// Check if he has triggered with a Dot
			if (pacman.direction.y > 0) // Moving up
			{
				if (pacman.sprite.position.y >= allWaypoints[i].position.y
					&& pacman.previousPosition.y < allWaypoints[i].position.y)
				{
					if (desiredDirAsInt != 0 && gameState->pacman.desiredDir.x != 0)
					{
						if ((desiredDirAsInt & allWaypoints[i].allowedDirections) == desiredDirAsInt)
						{
							gameState->pacman.curWaypointIndex = INVALID_WAYPOINT_INDEX;
							pacman.direction = gameState->pacman.desiredDir;
							pacman.sprite.angle = gameState->pacman.desiredAngle;
							pacman.sprite.position.y = allWaypoints[i].position.y;
							break;
						}
					}

					if ((currentDirAsInt & allWaypoints[i].allowedDirections) == currentDirAsInt)
					{
						// Just keep moving in the same direction
						break;
					}
					// Pacman hit a wall
					gameState->pacman.curWaypointIndex = i;
					pacman.direction.y = 0;
					gameState->pacman.desiredDir.y = 0;
					pacman.sprite.position.y = allWaypoints[i].position.y;
					break;
				}
			} 
			else // Moving down
			{
				if (pacman.sprite.position.y <= allWaypoints[i].position.y
					&& pacman.previousPosition.y > allWaypoints[i].position.y)
				{
					if (desiredDirAsInt != 0 && gameState->pacman.desiredDir.x != 0)
					{
						if ((desiredDirAsInt & allWaypoints[i].allowedDirections) == desiredDirAsInt)
						{
							gameState->pacman.curWaypointIndex = INVALID_WAYPOINT_INDEX;
							pacman.direction = gameState->pacman.desiredDir;
							pacman.sprite.angle = gameState->pacman.desiredAngle;
							pacman.sprite.position.y = allWaypoints[i].position.y;
							break;
						}
					}

					if ((currentDirAsInt & allWaypoints[i].allowedDirections) == currentDirAsInt)
					{
						// Just keep moving in the same direction
						break;
					}
					// Pacman hit a wall
					gameState->pacman.curWaypointIndex = i;
					gameState->pacman.desiredDir.y = 0;
					pacman.direction.y = 0;
					pacman.sprite.position.y = allWaypoints[i].position.y;
					break;
				}
			}
		}
	}
}

void HandleHorizontalWaypointsForGhost(Ghost& ghost)
{
	int currentDirAsInt = (pacman.direction.x > 0) ? BINARY_RIGHT : BINARY_LEFT;
	
	if (pacman.direction.x > 0)
	{
		for (int i = 0; i < WAYPOINTS_LENGTH; i++)
		{
			// Only execute the next checks if the Y position is the same as the Pacman
			if (floor(pacman.sprite.position.y) == floor(allWaypoints[i].position.y))
			{
				switch (ghost.Type)
				{
					case EGhostType.Blinky:
						//TODO
						break;
						
					case EGhostType.Inky:
						//TODO
						break;
						
					case EGhostType.Pinky:
						//TODO
						break;
						
					case EGhostType.Clyde:
						//TODO
						break;
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < WAYPOINTS_LENGTH; i++)
		{
			// Only execute the next checks if the Y position is the same as the Pacman
			if (floor(pacman.sprite.position.y) == floor(allWaypoints[i].position.y))
			{
				switch (ghost.Type)
				{
					case EGhostType.Blinky:
						//TODO
						break;
						
					case EGhostType.Inky:
						//TODO
						break;
						
					case EGhostType.Pinky:
						//TODO
						break;
						
					case EGhostType.Clyde:
						//TODO
						break;
				}
			}
		}
	}
}

void HandleVerticalWaypointsForGhost(Ghost& ghost)
{
	int currentDirAsInt = (gameState->pacman.direction.y > 0) ?
		BINARY_UP : BINARY_DOWN;

	for (int i = 0; i < WAYPOINTS_LENGTH; i++)
	{
		// Only execute the next checks if the X position is the same of the pacman
		if (floor(pacman.sprite.position.x) == floor(allWaypoints[i].position.x))
		{
			// Check if he has triggered with a Dot
			if (pacman.direction.y > 0) // Moving up
			{
				if (pacman.sprite.position.y >= allWaypoints[i].position.y
					&& pacman.previousPosition.y < allWaypoints[i].position.y)
				{
					switch (ghost.Type)
					{
						case EGhostType.Blinky:
							//TODO
							break;
							
						case EGhostType.Inky:
							//TODO
							break;
							
						case EGhostType.Pinky:
							//TODO
							break;
							
						case EGhostType.Clyde:
							//TODO
							break;
					}
				}
			} 
			else // Moving down
			{
				if (pacman.sprite.position.y <= allWaypoints[i].position.y
					&& pacman.previousPosition.y > allWaypoints[i].position.y)
				{
					switch (ghost.Type)
					{
						case EGhostType.Blinky:
							//TODO
							break;
							
						case EGhostType.Inky:
							//TODO
							break;
							
						case EGhostType.Pinky:
							//TODO
							break;
							
						case EGhostType.Clyde:
							//TODO
							break;
					}
				}
			}
		}
	}
}