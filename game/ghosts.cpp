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

ldk::Vec4 getGhostColor(Ghost& ghost)
{
    switch(ghost.Type)
    {
        case Blinky:
            return { 1.0f, 0.0f, 0.0f, 1.0f };
        case Pinky:
            return { 1.0f, 0.71f, 0.75f, 1.0f };
        case Inky:
            return { 0.0f, 1.0f, 1.0f, 1.0f };
        case Clyde:
            return { 1.0f, 0.41f, 0.0f, 1.0f };
    }
    return { 1.0f, 1.0f, 1.0f, 1.0f };
};

void setGhostTargetPosition(Ghost& ghost)
{
    const int tileSize = 8;
    
    Entity& pacman = gameState->pacman;
    
    switch(ghost.Type)
    {
        case Blinky: //current pacman's position
            ghost.TargetPosition = pacman.sprite.position;
            return;
          
        case Pinky: //four titles in front of pacman's direction
            ghost.TargetPosition = pacman.sprite.position + pacman.previousDirection * (4 * tileSize);
            break;
            
        case Inky:
            ldk::Vec3 forwardOffset = gameState->pacman.direction * 2;
            ldk::Vec3 vector = pacman.sprite.position + forwardOffset - gameState->blinky.sprite.position;
            vector.x = vector.x * 2;
            vector.y = vector.y * 2;
            ghost.TargetPosition = gameState->blinky.sprite.position + vector;
            break;
            
        case Clyde:
            ldk::Vec3 diff = (pacman.sprite.position - ghost.sprite.position);
            float magnitude = fabs(diff.x) + fabs(diff.y);
            if (magnitude < (14 * tileSize))
            {
                ghost.TargetPosition = {0, tileSize * -2, 0};
            }
            else
            {
                ghost.TargetPosition = pacman.sprite.position;
            }
            break;
    }
};

void inline MoveGhost(const float deltaTime, Ghost& ghost)
{
    setGhostTargetPosition(ghost);

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
            ldk::Vec3 diff = (nextPosition - ghost.TargetPosition);
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
    Entity& pacman = gameState -> pacman;
    int movementMask = 0x8;
    for(int x = 0; x < 4; x++)
    {
        // Is this direction allowed?
        if ((filteredDirections & movementMask) == movementMask)
        {
            ldk::Vec3 versor = IntDirToVec3(movementMask);
            const int tileSize = 8;
            ldk::Vec3 nextPosition = ghost.sprite.position + (versor * tileSize);
            ldk::Vec3 diff = (nextPosition - ghost.TargetPosition);
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
            ldk::Vec3 diff = (nextPosition - ghost.TargetPosition);
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
            ldk::Vec3 diff = (nextPosition - ghost.TargetPosition);
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
