void HandleVerticalWaypoints(Entity& pacman);
void HandleHorizontalWaypoints(Entity& pacman);

int InvertHorizontalDirection(const int directions)
{
    int upAndDown = (BINARY_UP | BINARY_DOWN);
    int leftAndRight = (BINARY_LEFT | BINARY_RIGHT);
    int result = directions & upAndDown;
	if ((directions & leftAndRight) != leftAndRight)
	{
		// Invert left and right bits
		result |= ~directions & leftAndRight;
	}
	else
	{
		result |= leftAndRight;
	}
	return result;
};

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
};

bool isSameHorizontalPosition(const ldk::Vec3 positionA, const ldk::Vec3 positionB)
{
    return floor(positionA.x) == floor(positionB.x);
};

bool isSameVerticalPosition(const ldk::Vec3 positionA, const ldk::Vec3 positionB)
{
    return floor(positionA.y) == floor(positionB.y);
};

bool hasCrossedVerticalPositionUpwards(const Entity& entity, const ldk::Vec3 targetPosition)
{
    return (entity.sprite.position.y >= targetPosition.y
            && entity.previousPosition.y < targetPosition.y);
};

bool hasCrossedVerticalPositionDownwards(const Entity& entity, const ldk::Vec3 targetPosition)
{
    return (entity.sprite.position.y <= targetPosition.y
           && entity.previousPosition.y > targetPosition.y);
};

bool hasCrossedVerticalWaypoint(const Entity& entity, const Waypoint& waypoint)
{
    if (entity.direction.y > 0)
    {
        return hasCrossedVerticalPositionUpwards(entity, waypoint.position);
    }
    return hasCrossedVerticalPositionDownwards(entity, waypoint.position);
};

bool hasCrossedHorizontalPositionLeftwards(const Entity& entity, const Waypoint& waypoint)
{
    return (entity.sprite.position.x <= waypoint.position.x
            && entity.previousPosition.x > waypoint.position.x);
};

bool hasCrossedHorizontalPositionRightwards(const Entity& entity, const Waypoint& waypoint)
{
    return (entity.sprite.position.x >= waypoint.position.x
            && entity.previousPosition.x < waypoint.position.x);
};

bool hasCrossedHorizontalWaypoint(const Entity& entity, const Waypoint& waypoint)
{
    if (entity.direction.x > 0)
    {
        return hasCrossedHorizontalPositionRightwards(entity, waypoint.position);
    }
    return hasCrossedHorizontalPositionLeftwards(entity, waypoint.position);
};

void HandleVerticalWaypoints(Entity& pacman)
{
	for (int i = 0; i < WAYPOINTS_LENGTH; i++)
	{
	    Waypoint& waypoint = allWaypoints[i];
		if (isSameHorizontalPosition(pacman.sprite.position, waypoint.position))
		{
            if (hasCrossedVerticalWaypoint(pacman, waypoint))
            {
                if (pacman.desiredDir.x != 0) //want moving horizontally
                {
                    int directionAsInt = Vec3ToIntDir(pacman.desiredDir);
                    if (canMoveOnDirection(waypoint, directionAsInt))
                    {
                        pacman.curWaypointIndex = INVALID_WAYPOINT_INDEX;
                        pacman.direction = pacman.desiredDir;
                        pacman.sprite.angle = directionToAngle(pacman.desiredDir);
                        pacman.sprite.position.y = waypoint.position.y;
                        break;
                    }
                }
                
                int currentDirAsInt = Vec3ToIntDir(pacman.direction);
                bool hasHitWall = !canMoveOnDirection(waypoint, currentDirAsInt);
                if (hasHitWall)
                {
                    //pairing vertical movement
                    pacman.desiredDir.y = 0;
                    pacman.direction.y = 0;
                    
                    //update current waypoint index and position
                    pacman.curWaypointIndex = i;
                    pacman.sprite.position.y = waypoint.position.y;
                }
                break;
            }
		}
	}
};

void HandleHorizontalWaypoints(Entity& pacman)
{
    for (int i = 0; i < WAYPOINTS_LENGTH; i++)
    {
        Waypoint& waypoint = allWaypoints[i];
        if (isSameVerticalPosition(pacman.sprite.position, waypoint.position))
        {
            if (hasCrossedHorizontalWaypoint(pacman, waypoint))
            {
                if (pacman.desiredDir.y != 0) //want moving vertically
                {
                    int directionAsInt = Vec3ToIntDir(pacman.desiredDir);
                    if (canMoveOnDirection(waypoint, directionAsInt))
                    {
                        pacman.curWaypointIndex = INVALID_WAYPOINT_INDEX;
                        pacman.direction = pacman.desiredDir;
                        pacman.sprite.angle = directionToAngle(pacman.desiredDir);
                        pacman.sprite.position.x = waypoint.position.x;
                        break;
                    }
                }
                
                int currentDirAsInt = Vec3ToIntDir(pacman.direction);
                bool hasHitWall = !canMoveOnDirection(waypoint, currentDirAsInt);
                if (hasHitWall)
                {
                    //pairing vertical movement
                    pacman.direction.x = 0;
                    pacman.desiredDir.x = 0;
                    
                    //update current waypoint index and position
                    pacman.curWaypointIndex = i;
                    pacman.sprite.position.x = waypoint.position.x;
                }
                break;
            }
        }
    }
};

void HandleHorizontalWaypointsForGhost(Ghost& ghost, GhostStrategy behaviour)
{
    for (int i = 0; i < WAYPOINTS_LENGTH; i++)
    {
        Waypoint& waypoint = allWaypoints[i];
        if (isSameVerticalPosition(ghost.sprite.position, waypoint.position))
        {
            if (hasCrossedHorizontalWaypoint(ghost, waypoint))
            {
                behaviour(ghost, waypoint);
            }
        }
    }
};

void HandleVerticalWaypointsForGhost(Ghost& ghost, GhostStrategy behaviour)
{
    for (int i = 0; i < WAYPOINTS_LENGTH; i++)
    {
        Waypoint& waypoint = allWaypoints[i];
        if (isSameHorizontalPosition(ghost.sprite.position, waypoint.position))
        {
            if (hasCrossedVerticalWaypoint(ghost, waypoint))
            {
                behaviour(ghost, waypoint);
            }
        }
    }
};
