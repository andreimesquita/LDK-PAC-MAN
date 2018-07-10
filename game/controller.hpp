int Vec3ToIntDir(const ldk::Vec3);
void HandleVerticalMovement(Entity&);
void HandleHorizontalMovement(Entity&);

void MoveAndCheckallDots(const float deltaTime, Entity& pacman)
{
	pacman.sprite.position += pacman.direction * pacman.speed * deltaTime;

	if (pacman.direction.x != 0)
	{
		// Pacman`s moving HORIZONTALLY
		HandleHorizontalMovement(pacman);

		if (pacman.direction.x != 0)
		{
			gameState->currentDotIndex = INVALID_WAYPOINT_INDEX;
		}
	}
	else if (gameState->pacman.direction.y != 0)
	{
		// Pacman`s moving VERTICALLY
		HandleVerticalMovement(pacman);

		if (pacman.direction.y != 0)
		{
			gameState->currentDotIndex = INVALID_WAYPOINT_INDEX;
		}
	}
	pacman.previousPosition = pacman.sprite.position;
}

void HandleHorizontalMovement(Entity& pacman)
{
	int desiredDirAsInt = Vec3ToIntDir(gameState->desiredDir);
	int currentDirAsInt = (pacman.direction.x > 0) ? BINARY_RIGHT : BINARY_LEFT;
	Dot* ptrDots = gameState->allDots;

	for (int i = 0; i < DOTS_LENGTH; i++)
	{
		// Only execute the next checks if the Y position is the same as the Pacman
		if (floor(pacman.sprite.position.y) == floor(ptrDots[i].position.y))
		{
			// Check if he has triggered with a Dot
			if (pacman.direction.x > 0)
			{
				// Pacman's moving to the right
				if (pacman.sprite.position.x >= ptrDots[i].position.x
					&& pacman.previousPosition.x < ptrDots[i].position.x)
				{
					if (ptrDots[i].dotType == WaypointDot)
					{
						if (desiredDirAsInt != 0 && gameState->desiredDir.y != 0)
						{
							if ((desiredDirAsInt & ptrDots[i].allowedDirections) == desiredDirAsInt)
							{
								gameState->currentDotIndex = INVALID_WAYPOINT_INDEX;
								pacman.direction = gameState->desiredDir;
								pacman.sprite.angle = gameState->desiredAngle;
								pacman.sprite.position.x = ptrDots[i].position.x;
								continue;
							}
						}

						// Check if we can move on the direction we desire
						if ((currentDirAsInt & ptrDots[i].allowedDirections) == currentDirAsInt)
						{
							// Just keep moving in the same direction
							continue;
						}

						// Pacman hit a wall
						gameState->currentDotIndex = i;
						pacman.direction.x = 0;
						gameState->desiredDir.x = 0;
						pacman.sprite.position.x = ptrDots[i].position.x;
					}
					else if (ptrDots[i].dotType == SimpleDot)
					{
						ptrDots[i].isEnabled = false;
						gameState->playerPoints += 1;
						LogInfo("POINT RECEIVED! total=%i", gameState->playerPoints);
					}
				}
			}
			else
			{
				// Pacman's moving to the left
				if (pacman.sprite.position.x <= ptrDots[i].position.x
					&& pacman.previousPosition.x > ptrDots[i].position.x)
				{
					if (ptrDots[i].dotType == WaypointDot)
					{
						if (desiredDirAsInt != 0 && gameState->desiredDir.y != 0)
						{
							if ((desiredDirAsInt & ptrDots[i].allowedDirections) == desiredDirAsInt)
							{
								gameState->currentDotIndex = INVALID_WAYPOINT_INDEX;
								pacman.direction = gameState->desiredDir;
								pacman.sprite.angle = gameState->desiredAngle;
								pacman.sprite.position.x = ptrDots[i].position.x;
								continue;
							}
						}

						if ((currentDirAsInt & ptrDots[i].allowedDirections) == currentDirAsInt)
						{
							// Just keep moving in the same direction
							continue;
						}

						// Pacman hit a wall
						gameState->currentDotIndex = i;
						pacman.direction.x = 0;
						gameState->desiredDir.x = 0;
						pacman.sprite.position.x = ptrDots[i].position.x;
					}
					else if (ptrDots[i].dotType == SimpleDot)
					{
						ptrDots[i].isEnabled = false;
						gameState->playerPoints += 1;
						LogInfo("POINT RECEIVED! total=%i", gameState->playerPoints);
					}
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
	Dot* ptrDots = gameState->allDots;

	for (int i = 0; i < DOTS_LENGTH; i++)
	{
		// Only execute the next checks if the X position is the same of the pacman
		if (floor(pacman.sprite.position.x) == floor(ptrDots[i].position.x))
		{
			// Check if he has triggered with a Dot
			if (pacman.direction.y > 0) // Moving up
			{
				if (pacman.sprite.position.y >= ptrDots[i].position.y
					&& pacman.previousPosition.y < ptrDots[i].position.y)
				{
					if (desiredDirAsInt != 0 && gameState->desiredDir.x != 0)
					{
						if ((desiredDirAsInt & ptrDots[i].allowedDirections) == desiredDirAsInt)
						{
							gameState->currentDotIndex = INVALID_WAYPOINT_INDEX;
							pacman.direction = gameState->desiredDir;
							pacman.sprite.angle = gameState->desiredAngle;
							pacman.sprite.position.y = ptrDots[i].position.y;
							break;
						}
					}

					if ((currentDirAsInt & ptrDots[i].allowedDirections) == currentDirAsInt)
					{
						// Just keep moving in the same direction
						break;
					}
					// Pacman hit a wall
					gameState->currentDotIndex = i;
					pacman.direction.y = 0;
					gameState->desiredDir.y = 0;
					pacman.sprite.position.y = ptrDots[i].position.y;
					break;
				}
			} 
			else // Moving down
			{
				if (pacman.sprite.position.y <= ptrDots[i].position.y
					&& pacman.previousPosition.y > ptrDots[i].position.y)
				{
					if (desiredDirAsInt != 0 && gameState->desiredDir.x != 0)
					{
						if ((desiredDirAsInt & ptrDots[i].allowedDirections) == desiredDirAsInt)
						{
							gameState->currentDotIndex = INVALID_WAYPOINT_INDEX;
							pacman.direction = gameState->desiredDir;
							pacman.sprite.angle = gameState->desiredAngle;
							pacman.sprite.position.y = ptrDots[i].position.y;
							break;
						}
					}

					if ((currentDirAsInt & ptrDots[i].allowedDirections) == currentDirAsInt)
					{
						// Just keep moving in the same direction
						break;
					}
					// Pacman hit a wall
					gameState->currentDotIndex = i;
					gameState->desiredDir.y = 0;
					pacman.direction.y = 0;
					pacman.sprite.position.y = ptrDots[i].position.y;
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
