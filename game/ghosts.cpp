void inline MoveGhost(const float, Ghost&);
void BlinkyMovementStrategy(Ghost&, Waypoint&);
void PinkyMovementStrategy(Ghost&, Waypoint&);
void ClydeMovementStrategy(Ghost&, Waypoint&);
void InkyMovementStrategy(Ghost&, Waypoint&);

void MoveGhosts(const float deltaTime)
{
    MoveGhost(deltaTime, gameState->blinky);
    MoveGhost(deltaTime, gameState->pinky);
    MoveGhost(deltaTime, gameState->inky);
    MoveGhost(deltaTime, gameState->clyde);
};

GhostStrategy GetGhostStrategy(EGhostType type)
{
    if (type == Clyde) return ClydeMovementStrategy;
    if (type == Inky) return InkyMovementStrategy;
    if (type == Pinky) return PinkyMovementStrategy;
    return BlinkyMovementStrategy;
};

void inline MoveGhost(const float deltaTime, Ghost& ghost)
{
	ghost.sprite.position += ghost.direction * ghost.speed * deltaTime;

	if (ghost.direction.x != 0) //is moving horizontally?
	{
		HandleHorizontalWaypointsForGhost(ghost, GetGhostStrategy(ghost.Type));
	}
	else if (ghost.direction.y != 0) //is moving vertically?
	{
		HandleVerticalWaypointsForGhost(ghost, GetGhostStrategy(ghost.Type));
	}

	//check bounds of screen and teleport ghost if needed
	if (ghost.sprite.position.x < -5)
	{
		ghost.sprite.position.x = SCREEN_WIDTH + 4;
	}
	else if (ghost.sprite.position.x > SCREEN_WIDTH + 5)
	{
		ghost.sprite.position.x = -5;
	}

	ghost.previousPosition = ghost.sprite.position;
};

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
};

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
};

void ClydeMovementStrategy(Ghost& ghost, Waypoint& waypoint)
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
            ldk::Vec3 targetPos = gameState->pacman.sprite.position;
            ldk::Vec3 diff = (nextPosition - targetPos);
            float magnitude = fabs(diff.x) + fabs(diff.y);
            if (magnitude < (8 * tileSize))
            {
                targetPos = {0, tileSize * -2, 0};
                diff = (nextPosition - targetPos);
                magnitude = fabs(diff.x) + fabs(diff.y);
            }
            
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
};

void InkyMovementStrategy(Ghost& ghost, Waypoint& waypoint)
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
            ldk::Vec3 nextPosition = ghost.sprite.position + (versor * 2 * tileSize);
            ldk::Vec3 targetPos = (((gameState->pacman.sprite.position + 
                (gameState->pacman.direction * 2)) - gameState->blinky.sprite.position) * 2) + 
                gameState->blinky.sprite.position;
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
};
