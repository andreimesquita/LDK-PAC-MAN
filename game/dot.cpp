void initializeDots();
void inline resetDots();
void inline HandleVerticalDots(Entity&);
void inline HandleHorizontalDots(Entity&);
void inline evaluateDot(Dot&);

// depends on waypoints initialization
void initializeDots()
{
	ldk::Vec3 xOffset = { 7.9f, 0, 0 };
	ldk::Vec3 yOffset = { 0, -7.9f, 0 };

	int index = 0;
    
	// 1st column - 1st line (horizontal)
	allDots[index++] = Dot(allWaypoints[0].position, false);
	allDots[index++] = Dot(allDots[index-1].position + xOffset, false);
	allDots[index++] = Dot(allDots[index-1].position + xOffset, false);
	allDots[index++] = Dot(allDots[index-1].position + xOffset, false);
	allDots[index++] = Dot(allDots[index-1].position + xOffset, false);
	// 1st column - 1st line (vertical)
	allDots[index++] = Dot(allWaypoints[0].position + yOffset, false);
	allDots[index++] = Dot(allDots[index-1].position + yOffset, true);
	allDots[index++] = Dot(allDots[index-1].position + yOffset, false);


	// 2nd column - 1st line (vertical)
	allDots[index++] = Dot(allWaypoints[9].position, false);
	allDots[index++] = Dot(allDots[index-1].position + xOffset, false);
	allDots[index++] = Dot(allDots[index-1].position + xOffset, false);
	allDots[index++] = Dot(allDots[index-1].position + xOffset, false);
	allDots[index++] = Dot(allDots[index-1].position + xOffset, false);
	allDots[index++] = Dot(allDots[index-1].position + xOffset, false);
	// 2nd column - 1st line (vertical)
	allDots[index++] = Dot(allWaypoints[9].position + yOffset, false);
	allDots[index++] = Dot(allDots[index-1].position + yOffset, false);
	allDots[index++] = Dot(allDots[index-1].position + yOffset, false);


	// 3rd column - 1st line (vertical)
	allDots[index++] = Dot(allWaypoints[24].position, false);
	allDots[index++] = Dot(allDots[index-1].position + yOffset, false);
	allDots[index++] = Dot(allDots[index-1].position + yOffset, false);
	allDots[index++] = Dot(allDots[index-1].position + yOffset, false);


	// 1st column - 2 line (horizontal)
	allDots[index++] = Dot(allWaypoints[1].position, false);
	allDots[index++] = Dot(allDots[index-1].position + xOffset, false);
	allDots[index++] = Dot(allDots[index-1].position + xOffset, false);
	allDots[index++] = Dot(allDots[index-1].position + xOffset, false);
	allDots[index++] = Dot(allDots[index-1].position + xOffset, false);
	// 1st column - 2 line (vertical)
	allDots[index++] = Dot(allWaypoints[1].position + yOffset, false);
	allDots[index++] = Dot(allDots[index-1].position + yOffset, false);


	// 2nd column - 2nd line (horizontal)
	allDots[index++] = Dot(allWaypoints[10].position, false);
	allDots[index++] = Dot(allDots[index-1].position + xOffset, false);
	allDots[index++] = Dot(allDots[index-1].position + xOffset, false);
	// 2nd column - 2nd line (vertical)
	allDots[index++] = Dot(allWaypoints[10].position + yOffset, false);
	allDots[index++] = Dot(allDots[index-1].position + yOffset, false);


	// 3rd column - 2nd line (horizontal)
	allDots[index++] = Dot(allWaypoints[16].position, false);
	allDots[index++] = Dot(allDots[index-1].position + xOffset, false);
	allDots[index++] = Dot(allDots[index-1].position + xOffset, false);
	// 3rd column - 2nd line (vertical)
	allDots[index++] = Dot(allWaypoints[16].position + yOffset, false);
	allDots[index++] = Dot(allDots[index-1].position + yOffset, false);


	// 4th column - 2nd line (horizontal)
	allDots[index++] = Dot(allWaypoints[25].position, false);
	allDots[index++] = Dot(allDots[index-1].position + xOffset, false);


	// 1st column - 3rd line (vertical)
	allDots[index++] = Dot(allWaypoints[2].position, false);
	allDots[index++] = Dot(allDots[index-1].position + xOffset, false);
	allDots[index++] = Dot(allDots[index-1].position + xOffset, false);
	allDots[index++] = Dot(allDots[index-1].position + xOffset, false);
	allDots[index++] = Dot(allDots[index-1].position + xOffset, false);


	// 2nd column - 3rd line (vertical)
	allDots[index++] = Dot(allWaypoints[11].position, false);
	allDots[index++] = Dot(allDots[index-1].position + yOffset, false);
	allDots[index++] = Dot(allDots[index-1].position + yOffset, false);
	allDots[index++] = Dot(allDots[index-1].position + yOffset, false);
	allDots[index++] = Dot(allDots[index-1].position + yOffset, false);
	allDots[index++] = Dot(allDots[index-1].position + yOffset, false);


	// 3rd column - 3 line (horizontal)
	allDots[index++] = Dot(allWaypoints[17].position, false);
	allDots[index++] = Dot(allDots[index-1].position + xOffset, false);
	allDots[index++] = Dot(allDots[index-1].position + xOffset, false);
	allDots[index++] = Dot(allDots[index-1].position + xOffset, false);


	// 2nd column - 4th line (vertical)
	allDots[index++] = Dot(allWaypoints[12].position, false);
	allDots[index++] = Dot(allDots[index-1].position + yOffset, false);
	allDots[index++] = Dot(allDots[index-1].position + yOffset, false);
	allDots[index++] = Dot(allDots[index-1].position + yOffset, false);
	allDots[index++] = Dot(allDots[index-1].position + yOffset, false);
	allDots[index++] = Dot(allDots[index-1].position + yOffset, false);


	// 1st column - 4th line (horizontal)
	allDots[index++] = Dot(allWaypoints[3].position, false);
	allDots[index++] = Dot(allDots[index-1].position + xOffset, false);
	allDots[index++] = Dot(allDots[index-1].position + xOffset, false);
	allDots[index++] = Dot(allDots[index-1].position + xOffset, false);
	allDots[index++] = Dot(allDots[index-1].position + xOffset, false);
	// 1st column - 4th line (vertical)
	allDots[index++] = Dot(allWaypoints[3].position + yOffset, false);
	allDots[index++] = Dot(allDots[index-1].position + yOffset, false);


	// 2nd column - 5th line (horizontal)
	allDots[index++] = Dot(allWaypoints[13].position, false);
	allDots[index++] = Dot(allDots[index-1].position + xOffset, false);
	allDots[index++] = Dot(allDots[index-1].position + xOffset, false);
	// 2nd column - 5th line (vertical)
	allDots[index++] = Dot(allWaypoints[13].position + yOffset, false);
	allDots[index++] = Dot(allDots[index-1].position + yOffset, false);


	// 3rd column - 6th line (horizontal)
	allDots[index++] = Dot(allWaypoints[21].position, false);
	allDots[index++] = Dot(allDots[index-1].position + xOffset, false);
	allDots[index++] = Dot(allDots[index-1].position + xOffset, false);


	// 4th column - 5th line (vertical)
	allDots[index++] = Dot(allWaypoints[28].position, false);
	allDots[index++] = Dot(allDots[index-1].position + yOffset, false);
	allDots[index++] = Dot(allDots[index-1].position + yOffset, false);
	allDots[index++] = Dot(allDots[index-1].position + yOffset, false);


	// 1st column - 5th line (horizontal)
	allDots[index++] = Dot(allWaypoints[4].position, true);
	allDots[index++] = Dot(allDots[index-1].position + xOffset, false);


	// 2nd column - 5th line (vertical)
	allDots[index++] = Dot(allWaypoints[7].position, false);
	allDots[index++] = Dot(allDots[index-1].position + yOffset, false);
	allDots[index++] = Dot(allDots[index-1].position + yOffset, false);


	// 3rd column - 6th line (horizontal)
	allDots[index++] = Dot(allWaypoints[14].position, false);
	allDots[index++] = Dot(allDots[index-1].position + xOffset, false);
	allDots[index++] = Dot(allDots[index-1].position + xOffset, false);
	// 3rd column - 6th line (vertical)
	allDots[index++] = Dot(allWaypoints[14].position + yOffset, false);
	allDots[index++] = Dot(allDots[index-1].position + yOffset, false);
	allDots[index++] = Dot(allDots[index-1].position + yOffset, false);


	// 4th column - 7th line (horizontal)
	allDots[index++] = Dot(allWaypoints[22].position, false);
	allDots[index++] = Dot(allDots[index-1].position + xOffset, false);
	allDots[index++] = Dot(allDots[index-1].position + xOffset, false);
	// 4th column - 7th line (vertical)
	allDots[index++] = Dot(allWaypoints[22].position + yOffset, false);
	allDots[index++] = Dot(allDots[index-1].position + yOffset, false);


	// 1st column - 6th line (horizontal)
	allDots[index++] = Dot(allWaypoints[5].position, false);
	allDots[index++] = Dot(allDots[index-1].position + xOffset, false);
	// 1st column - 6th line (vertical)
	allDots[index++] = Dot(allWaypoints[5].position + yOffset, false);
	allDots[index++] = Dot(allDots[index-1].position + yOffset, false);


	// 2nd column - 2nd line (horizontal)
	allDots[index++] = Dot(allWaypoints[8].position, false);
	allDots[index++] = Dot(allDots[index-1].position + xOffset, false);
	allDots[index++] = Dot(allDots[index-1].position + xOffset, false);


	// 4th column - 8th line (horizontal)
	allDots[index++] = Dot(allWaypoints[23].position, false);
	allDots[index++] = Dot(allDots[index-1].position + xOffset, false);
	allDots[index++] = Dot(allDots[index-1].position + xOffset, false);


	// 5th column - 7th line (vertical)
	allDots[index++] = Dot(allWaypoints[30].position, false);
	allDots[index++] = Dot(allDots[index-1].position + yOffset, false);
	allDots[index++] = Dot(allDots[index-1].position + yOffset, false);


	// 1st column - 7th line (horizontal)
	allDots[index++] = Dot(allWaypoints[6].position, false);
	allDots[index++] = Dot(allDots[index-1].position + xOffset, false);
	allDots[index++] = Dot(allDots[index-1].position + xOffset, false);
	allDots[index++] = Dot(allDots[index-1].position + xOffset, false);
	allDots[index++] = Dot(allDots[index-1].position + xOffset, false);
	allDots[index++] = Dot(allDots[index-1].position + xOffset, false);
	allDots[index++] = Dot(allDots[index-1].position + xOffset, false);
	allDots[index++] = Dot(allDots[index-1].position + xOffset, false);
	allDots[index++] = Dot(allDots[index-1].position + xOffset, false);
	allDots[index++] = Dot(allDots[index-1].position + xOffset, false);
	allDots[index++] = Dot(allDots[index-1].position + xOffset, false);


	// 2nd column - 8th line (horizontal)
	allDots[index++] = Dot(allWaypoints[31].position, false);
	allDots[index++] = Dot(allDots[index-1].position + xOffset, false);
	allDots[index++] = Dot(allDots[index-1].position + xOffset, false);
    
	// Copy all information from the left side to the right side of the map
	int halfallDotsLength = (int)DOTS_LENGTH / 2;
	for (int x = 0; x < halfallDotsLength; x++)
	{
		ldk::Vec3 curPos = allDots[x].position;
		int realIndex = halfallDotsLength + x;
		allDots[realIndex] = Dot({ SCREEN_WIDTH - curPos.x, curPos.y }, allDots[x].isSpecial);
	}
}

void inline HandleHorizontalDots(Entity& pacman)
{
	if (pacman.direction.x > 0)
	{
		for (int i = 0; i < DOTS_LENGTH; i++)
		{
			if (allDots[i].isEnabled
				&& floor(pacman.sprite.position.y) == floor(allDots[i].position.y)
				&& pacman.sprite.position.x >= allDots[i].position.x
				&& pacman.previousPosition.x <= allDots[i].position.x)
			{
				evaluateDot(allDots[i]);
			}
		}
	}
	else
	{
		for (int i = 0; i < DOTS_LENGTH; i++)
		{
			if (allDots[i].isEnabled
				&& floor(pacman.sprite.position.y) == floor(allDots[i].position.y)
				&& pacman.sprite.position.x <= allDots[i].position.x
				&& pacman.previousPosition.x >= allDots[i].position.x)
			{
				evaluateDot(allDots[i]);
			}
		}
	}
}

void inline HandleVerticalDots(Entity& pacman)
{
	if (pacman.direction.y > 0)
	{
		for (int i = 0; i < DOTS_LENGTH; i++)
		{
			if (allDots[i].isEnabled 
				&& floor(pacman.sprite.position.x) == floor(allDots[i].position.x)
				&& pacman.sprite.position.y >= allDots[i].position.y
				&& pacman.previousPosition.y <= allDots[i].position.y)
			{
				evaluateDot(allDots[i]);
			}
		}
	}
	else
	{
		for (int i = 0; i < DOTS_LENGTH; i++)
		{
			if (allDots[i].isEnabled
				&& floor(pacman.sprite.position.x) == floor(allDots[i].position.x)
				&& pacman.sprite.position.y <= allDots[i].position.y
				&& pacman.previousPosition.y >= allDots[i].position.y)
			{
				evaluateDot(allDots[i]);
			}
		}
	}
}

void inline evaluateDot(Dot& dot)
{
	dot.isEnabled = false;
	gameState->playerPoints += dot.isSpecial ? 20 : 5;
	LogInfo("POINT RECEIVED! total=%i", gameState->playerPoints);
}

// reset all dots to theirs default state
void inline resetDots()
{
	for (int i = 0; i < DOTS_LENGTH; i++)
	{
		allDots[i].isEnabled = true;
	}
}