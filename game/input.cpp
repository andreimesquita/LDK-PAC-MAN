void ReadPlayerInput(const float deltaTime, Entity& pacman)
{
    InputController* controller = gameState -> playerController;
    controller -> getDesiredDir(pacman);
    
	// Immediately direction change is only allowed on the same line of movement (Horizontally or Vertically)
	if (!(pacman.desiredDir == ldk::Vec3::zero()))
	{
		if (isEntityStopped(pacman))
		{
			if (isOnValidWaypoint(pacman))
			{
				int directionAsInt = Vec3ToIntDir(pacman.desiredDir);
				Waypoint& waypoint = getWaypointByIndex(pacman.curWaypointIndex);
				
				if (canMoveOnDirection(waypoint, directionAsInt))
				{
    				pacman.direction = pacman.desiredDir;
					pacman.sprite.angle = directionToAngle(pacman.direction);
				}
			}
		}
		else
		{
			// If the direction you wanna go is the inverse of the direction he is going
			if (pacman.direction == (pacman.desiredDir * -1))
			{
				pacman.direction = pacman.desiredDir;
				pacman.sprite.angle = directionToAngle(pacman.direction);
			}
		}
	}
};
