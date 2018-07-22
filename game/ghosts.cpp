void MoveGhost(const float, Ghost&);
void OnBlinkyMovement(Ghost&, Waypoint&);

void MoveGhosts(const float deltaTime)
{
    MoveGhost(deltaTime, gameState->blinky);
    MoveGhost(deltaTime, gameState->pinky);
    MoveGhost(deltaTime, gameState->inky);
    MoveGhost(deltaTime, gameState->clyde);
}

GhostStrategy GetGhostStrategy(EGhostType type)
{
    switch (type)
    {
        case Blinky:
        case Pinky:
        case Inky:
        case Clyde:
            return OnBlinkyMovement;
    }
    return nullptr;
}

void MoveGhost(const float deltaTime, Ghost& ghost)
{
	ghost.sprite.position += ghost.direction * ghost.speed * deltaTime;

	if (ghost.direction.x != 0)
	{
		HandleHorizontalWaypointsForGhost(ghost, GetGhostStrategy(ghost.Type));
	}
	else if (ghost.direction.y != 0)
	{
		HandleVerticalWaypointsForGhost(ghost, GetGhostStrategy(ghost.Type));
	}

	// Check bounds and teleport pacman, if needed
	if (ghost.sprite.position.x < -5)
	{
		ghost.sprite.position.x = SCREEN_WIDTH + 4;
	}
	else if (ghost.sprite.position.x > SCREEN_WIDTH + 5)
	{
		ghost.sprite.position.x = -5;
	}

	ghost.previousPosition = ghost.sprite.position;
}

ldk::Vec3 GetRandomDir(int dir)
{
    if ((dir & BINARY_UP) == BINARY_UP)
    {
        return {0, 1, 0};
    }
    if ((dir & BINARY_RIGHT) == BINARY_RIGHT)
    {
        return {1, 0, 0};
    }
    if ((dir & BINARY_DOWN) == BINARY_DOWN)
    {
        return {0, -1, 0};
    }
    return {-1, 0, 0};
}

void OnBlinkyMovement(Ghost& ghost, Waypoint& waypoint)
{
    int dirAsInt = Vec3ToIntInvertedDir(ghost.direction);
    ldk::Vec3 randomDir = GetRandomDir(waypoint.allowedDirections & ~dirAsInt);
    if (!(randomDir == ghost.direction))
    {
        ghost.sprite.position.x = waypoint.position.x;
        ghost.sprite.position.y = waypoint.position.y;
        ghost.direction = randomDir;
    }
}