#define WAYPOINTS_LENGTH 64
#define INVALID_WAYPOINT_INDEX -1

struct Waypoint
{
	ldk::Vec3 position;
	int allowedDirections;
	
	Waypoint() { }
	
	Waypoint(ldk::Vec3 pPos)
	{
		position = pPos;
		allowedDirections = (BINARY_LEFT | BINARY_RIGHT | BINARY_UP | BINARY_DOWN);
	}
};

Waypoint allWaypoints[WAYPOINTS_LENGTH] = {};

bool getWaypoint(const ldk::Vec3 previousPos, const ldk::Vec3 nextPos, Waypoint& waypoint, int& index)
{
	if (nextPos.x != previousPos.x)
	{
		// moving horizontally
		if (nextPos.x > previousPos.x)
		{
			// going to the right
			for (int i = 0; i < WAYPOINTS_LENGTH; i++)
			{
				if (floor(nextPos.y) == floor(allWaypoints[i].position.y)
					&& nextPos.x >= allWaypoints[i].position.x
					&& previousPos.x < allWaypoints[i].position.x)
				{
					waypoint = allWaypoints[i];
					index = i;
					return true;
				}
			}
		}
		else
		{
			// going to the left
			for (int i = 0; i < WAYPOINTS_LENGTH; i++)
			{
				if (floor(nextPos.y) == floor(allWaypoints[i].position.y)
					&& nextPos.x <= allWaypoints[i].position.x
					&& previousPos.x > allWaypoints[i].position.x)
				{
					waypoint = allWaypoints[i];
					index = i;
					return true;
				}
			}
		}
	}
	else if (nextPos.y != previousPos.y)
	{
		// moving vertically
		if (nextPos.y > previousPos.y)
		{
			// going up
			for (int i = 0; i < WAYPOINTS_LENGTH; i++)
			{
				if (floor(nextPos.x) == floor(allWaypoints[i].position.x)
					&& nextPos.y >= allWaypoints[i].position.y
					&& previousPos.y < allWaypoints[i].position.y)
				{
					waypoint = allWaypoints[i];
					index = i;
					return true;
				}
			}
		}
		else
		{
			// going down
			for (int i = 0; i < WAYPOINTS_LENGTH; i++)
			{
				if (floor(nextPos.x) == floor(allWaypoints[i].position.x)
					&& nextPos.y <= allWaypoints[i].position.y
					&& previousPos.y > allWaypoints[i].position.y)
				{
					waypoint = allWaypoints[i];
					index = i;
					return true;
				}
			}
		}
	}
	
	return false;
}

void InitializeWaypoints()
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
	int halfallDotsLength = (int)WAYPOINTS_LENGTH / 2;
	for (int x = 0; x < halfallDotsLength; x++)
	{
		ldk::Vec3 curPos = allWaypoints[x].position;
		int realIndex = halfallDotsLength + x;
		allWaypoints[realIndex] = Waypoint({ SCREEN_WIDTH - curPos.x, curPos.y });
		allWaypoints[realIndex].allowedDirections = InvertHorizontalDirection(allWaypoints[x].allowedDirections);
	}
}