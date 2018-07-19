void ReadInput(const float deltaTime, Entity& pacman)
{
	// Control
	if (ldk::input::getKey(LDK_KEY_LEFT))
	{
		gameState->desiredAngle = RADIAN(180);
		gameState->desiredDir = LEFT_DIR;
	}
	else if (ldk::input::getKey(LDK_KEY_RIGHT))
	{
		gameState->desiredAngle = 0;
		gameState->desiredDir = RIGHT_DIR;
	}
	else if (ldk::input::getKey(LDK_KEY_UP))
	{
		gameState->desiredAngle = RADIAN(90);
		gameState->desiredDir = UP_DIR;
	}
	else if (ldk::input::getKey(LDK_KEY_DOWN))
	{
		gameState->desiredAngle = RADIAN(270);
		gameState->desiredDir = DOWN_DIR;
	}
	else
	{
		gameState->desiredDir = ldk::Vec3::zero();
	}

	// Immediately direction change is only allowed on the same line of movement (Horizontally or Vertically)
	if (!(gameState->desiredDir == ldk::Vec3::zero()))
	{
		// If he's walking
		if (pacman.direction == ldk::Vec3::zero())
		{
			//If we`ve stopped on an Dot
			if (gameState->curWaypointIndex != INVALID_WAYPOINT_INDEX)
			{
				// Check if this Dot allows us to move in the desired direction we want
				Waypoint& waypoint = allWaypoints[gameState->curWaypointIndex];
				int desiredDirAsInt = Vec3ToIntDir(gameState->desiredDir);
				// Check if we can move in the desiredDir
				if ((desiredDirAsInt & waypoint.allowedDirections) == desiredDirAsInt)
				{
					pacman.sprite.angle = gameState->desiredAngle;
					pacman.direction = gameState->desiredDir;
				}
			}
		}
		else
		{
			// If the direction you wanna go is the inverse of the direction he is going
			if (pacman.direction == (gameState->desiredDir * -1))
			{
				pacman.sprite.angle = gameState->desiredAngle;
				pacman.direction = gameState->desiredDir;
			}
		}
	}
}