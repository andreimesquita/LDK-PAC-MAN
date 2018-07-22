void ReadInput(const float deltaTime, Entity& pacman)
{
	// Control
	if (ldk::input::getKey(LDK_KEY_LEFT))
	{
		gameState->pacman.desiredAngle = RADIAN(180);
		gameState->pacman.desiredDir = LEFT_DIR;
	}
	else if (ldk::input::getKey(LDK_KEY_RIGHT))
	{
		gameState->pacman.desiredAngle = 0;
		gameState->pacman.desiredDir = RIGHT_DIR;
	}
	else if (ldk::input::getKey(LDK_KEY_UP))
	{
		gameState->pacman.desiredAngle = RADIAN(90);
		gameState->pacman.desiredDir = UP_DIR;
	}
	else if (ldk::input::getKey(LDK_KEY_DOWN))
	{
		gameState->pacman.desiredAngle = RADIAN(270);
		gameState->pacman.desiredDir = DOWN_DIR;
	}
	else
	{
		gameState->pacman.desiredDir = ldk::Vec3::zero();
	}

	// Immediately direction change is only allowed on the same line of movement (Horizontally or Vertically)
	if (!(gameState->pacman.desiredDir == ldk::Vec3::zero()))
	{
		// If he's walking
		if (pacman.direction == ldk::Vec3::zero())
		{
			//If we`ve stopped on an Dot
			if (gameState->pacman.curWaypointIndex != INVALID_WAYPOINT_INDEX)
			{
				// Check if this Dot allows us to move in the desired direction we want
				Waypoint& waypoint = allWaypoints[gameState->pacman.curWaypointIndex];
				int desiredDirAsInt = Vec3ToIntDir(gameState->pacman.desiredDir);
				// Check if we can move in the desiredDir
				if ((desiredDirAsInt & waypoint.allowedDirections) == desiredDirAsInt)
				{
					pacman.sprite.angle = gameState->pacman.desiredAngle;
					pacman.direction = gameState->pacman.desiredDir;
				}
			}
		}
		else
		{
			// If the direction you wanna go is the inverse of the direction he is going
			if (pacman.direction == (gameState->pacman.desiredDir * -1))
			{
				pacman.sprite.angle = gameState->pacman.desiredAngle;
				pacman.direction = gameState->pacman.desiredDir;
			}
		}
	}
}