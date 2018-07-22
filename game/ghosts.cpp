void inline MoveGhost(const float, Ghost&);
void BlinkyMovementStrategy(Ghost&, Waypoint&);
void PinkyMovementStrategy(Ghost&, Waypoint&);
void RandomMovementStrategy(Ghost&, Waypoint&);

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
            return BlinkyMovementStrategy;
        case Pinky:
            return PinkyMovementStrategy;
        case Inky:
        case Clyde:
            return RandomMovementStrategy;
    }
    return nullptr;
}

void inline MoveGhost(const float deltaTime, Ghost& ghost)
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

// Meant to be used for tests, only
//TODO(andrei): remove this method when refactoring the system
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

void RandomMovementStrategy(Ghost& ghost, Waypoint& waypoint)
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

ldk::Vec3 IntDirToVec3(int direction)
{
    if (direction == BINARY_LEFT)
        return {-1, 0, 0};
    if (direction == BINARY_RIGHT)
        return {1, 0, 0};
    if (direction == BINARY_UP)
        return {0, 1, 0};
    return {0, -1, 0};
}

void BlinkyMovementStrategy(Ghost& ghost, Waypoint& waypoint)
{
    int dirAsInt = Vec3ToIntInvertedDir(ghost.direction);
    int filteredDirections = (waypoint.allowedDirections & ~dirAsInt);
    
    float bestDirectionValue = 99999;
    ldk::Vec3 bestDirection;
    
    int movementMask = 0x8;
    for(int x = 0; x < 4; x++)
    {
        // Is this direction allowed?
        if ((filteredDirections & movementMask) == movementMask)
        {
            ldk::Vec3 versor = IntDirToVec3(movementMask);
            const int tileSize = 8;
            ldk::Vec3 nextPosition = ghost.sprite.position + (versor * tileSize);
            ldk::Vec3 diff = (nextPosition - gameState->pacman.sprite.position);
            float magnitude = fabs(diff.x) + fabs(diff.y);
            if (magnitude < bestDirectionValue)
            {
                bestDirectionValue = magnitude;
                bestDirection = versor;
            }
        }
        movementMask = (movementMask >> 1);
    }
    
    if (dirAsInt != Vec3ToIntDir(bestDirection))
    {
        ghost.sprite.position.x = waypoint.position.x;
        ghost.sprite.position.y = waypoint.position.y;
        ghost.direction = bestDirection;
    }
}

void PinkyMovementStrategy(Ghost& ghost, Waypoint& waypoint)
{
    int dirAsInt = Vec3ToIntInvertedDir(ghost.direction);
    int filteredDirections = (waypoint.allowedDirections & ~dirAsInt);
    
    float bestDirectionValue = 99999;
    ldk::Vec3 bestDirection;
    
    int movementMask = 0x8;
    for(int x = 0; x < 4; x++)
    {
        // Is this direction allowed?
        if ((filteredDirections & movementMask) == movementMask)
        {
            ldk::Vec3 versor = IntDirToVec3(movementMask);
            const int tileSize = 8;
            ldk::Vec3 nextPosition = ghost.sprite.position + (versor * tileSize);
            ldk::Vec3 targetPos = gameState->pacman.sprite.position + 
                gameState->pacman.direction * (4 * tileSize);
            ldk::Vec3 diff = (nextPosition - targetPos);
            float magnitude = fabs(diff.x) + fabs(diff.y);
            if (magnitude < bestDirectionValue)
            {
                bestDirectionValue = magnitude;
                bestDirection = versor;
            }
        }
        movementMask = (movementMask >> 1);
    }
    
    if (dirAsInt != Vec3ToIntDir(bestDirection))
    {
        ghost.sprite.position.x = waypoint.position.x;
        ghost.sprite.position.y = waypoint.position.y;
        ghost.direction = bestDirection;
    }
}