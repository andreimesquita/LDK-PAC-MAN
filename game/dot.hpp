#define DOTS_LENGTH 246

struct Dot
{
	ldk::Vec3 position;
	bool isSpecial;
	bool isEnabled;

	Dot() { }

	Dot(ldk::Vec3 pPosition, bool pIsSpecial) :
		isEnabled(true)
	{
		position = pPosition;
		isSpecial = pIsSpecial;
	}
};

Dot allDots[DOTS_LENGTH] = {};

void inline HandleVerticalDots(Entity&);
void inline EvaluateDot(Dot&);
void inline HandleHorizontalDots(Entity&);
void inline ResetDots();

void InitializeDots()
{
	ldk::Vec3 xOffset = { 7.9f, 0, 0 };
	ldk::Vec3 yOffset = { 0, -7.9f, 0 };

	int index = 0;
    
	// 1st column - 1st line (horizontal)
	allDots[index++] = Dot(allWaypoints[0].position, true);
	allDots[index++] = Dot(allDots[index-1].position + xOffset, true);
	allDots[index++] = Dot(allDots[index-1].position + xOffset, true);
	allDots[index++] = Dot(allDots[index-1].position + xOffset, true);
	allDots[index++] = Dot(allDots[index-1].position + xOffset, true);
	// 1st column - 1st line (vertical)
	allDots[index++] = Dot(allWaypoints[0].position + yOffset, true);
	allDots[index++] = Dot(allDots[index-1].position + yOffset, true);
	allDots[index++] = Dot(allDots[index-1].position + yOffset, true);


	// 2nd column - 1st line (vertical)
	allDots[index++] = Dot(allWaypoints[9].position, true);
	allDots[index++] = Dot(allDots[index-1].position + xOffset, true);
	allDots[index++] = Dot(allDots[index-1].position + xOffset, true);
	allDots[index++] = Dot(allDots[index-1].position + xOffset, true);
	allDots[index++] = Dot(allDots[index-1].position + xOffset, true);
	allDots[index++] = Dot(allDots[index-1].position + xOffset, true);
	// 2nd column - 1st line (vertical)
	allDots[index++] = Dot(allWaypoints[9].position + yOffset, true);
	allDots[index++] = Dot(allDots[index-1].position + yOffset, true);
	allDots[index++] = Dot(allDots[index-1].position + yOffset, true);


	// 3rd column - 1st line (vertical)
	allDots[index++] = Dot(allWaypoints[24].position, true);
	allDots[index++] = Dot(allDots[index-1].position + yOffset, true);
	allDots[index++] = Dot(allDots[index-1].position + yOffset, true);
	allDots[index++] = Dot(allDots[index-1].position + yOffset, true);


	// 1st column - 2 line (horizontal)
	allDots[index++] = Dot(allWaypoints[1].position, true);
	allDots[index++] = Dot(allDots[index-1].position + xOffset, true);
	allDots[index++] = Dot(allDots[index-1].position + xOffset, true);
	allDots[index++] = Dot(allDots[index-1].position + xOffset, true);
	allDots[index++] = Dot(allDots[index-1].position + xOffset, true);
	// 1st column - 2 line (vertical)
	allDots[index++] = Dot(allWaypoints[1].position + yOffset, true);
	allDots[index++] = Dot(allDots[index-1].position + yOffset, true);


	// 2nd column - 2nd line (horizontal)
	allDots[index++] = Dot(allWaypoints[10].position, true);
	allDots[index++] = Dot(allDots[index-1].position + xOffset, true);
	allDots[index++] = Dot(allDots[index-1].position + xOffset, true);
	// 2nd column - 2nd line (vertical)
	allDots[index++] = Dot(allWaypoints[10].position + yOffset, true);
	allDots[index++] = Dot(allDots[index-1].position + yOffset, true);


	// 3rd column - 2nd line (horizontal)
	allDots[index++] = Dot(allWaypoints[16].position, true);
	allDots[index++] = Dot(allDots[index-1].position + xOffset, true);
	allDots[index++] = Dot(allDots[index-1].position + xOffset, true);
	// 3rd column - 2nd line (vertical)
	allDots[index++] = Dot(allWaypoints[16].position + yOffset, true);
	allDots[index++] = Dot(allDots[index-1].position + yOffset, true);


	// 4th column - 2nd line (horizontal)
	allDots[index++] = Dot(allWaypoints[25].position, true);
	allDots[index++] = Dot(allDots[index-1].position + xOffset, true);


	// 1st column - 3rd line (vertical)
	allDots[index++] = Dot(allWaypoints[2].position, true);
	allDots[index++] = Dot(allDots[index-1].position + xOffset, true);
	allDots[index++] = Dot(allDots[index-1].position + xOffset, true);
	allDots[index++] = Dot(allDots[index-1].position + xOffset, true);
	allDots[index++] = Dot(allDots[index-1].position + xOffset, true);


	// 2nd column - 3rd line (vertical)
	allDots[index++] = Dot(allWaypoints[11].position, true);
	allDots[index++] = Dot(allDots[index-1].position + yOffset, true);
	allDots[index++] = Dot(allDots[index-1].position + yOffset, true);
	allDots[index++] = Dot(allDots[index-1].position + yOffset, true);
	allDots[index++] = Dot(allDots[index-1].position + yOffset, true);
	allDots[index++] = Dot(allDots[index-1].position + yOffset, true);


	// 3rd column - 3 line (horizontal)
	allDots[index++] = Dot(allWaypoints[17].position, true);
	allDots[index++] = Dot(allDots[index-1].position + xOffset, true);
	allDots[index++] = Dot(allDots[index-1].position + xOffset, true);
	allDots[index++] = Dot(allDots[index-1].position + xOffset, true);


	// 2nd column - 4th line (vertical)
	allDots[index++] = Dot(allWaypoints[12].position, true);
	allDots[index++] = Dot(allDots[index-1].position + yOffset, true);
	allDots[index++] = Dot(allDots[index-1].position + yOffset, true);
	allDots[index++] = Dot(allDots[index-1].position + yOffset, true);
	allDots[index++] = Dot(allDots[index-1].position + yOffset, true);
	allDots[index++] = Dot(allDots[index-1].position + yOffset, true);


	// 1st column - 4th line (horizontal)
	allDots[index++] = Dot(allWaypoints[3].position, true);
	allDots[index++] = Dot(allDots[index-1].position + xOffset, true);
	allDots[index++] = Dot(allDots[index-1].position + xOffset, true);
	allDots[index++] = Dot(allDots[index-1].position + xOffset, true);
	allDots[index++] = Dot(allDots[index-1].position + xOffset, true);
	// 1st column - 4th line (vertical)
	allDots[index++] = Dot(allWaypoints[3].position + yOffset, true);
	allDots[index++] = Dot(allDots[index-1].position + yOffset, true);


	// 2nd column - 5th line (horizontal)
	allDots[index++] = Dot(allWaypoints[13].position, true);
	allDots[index++] = Dot(allDots[index-1].position + xOffset, true);
	allDots[index++] = Dot(allDots[index-1].position + xOffset, true);
	// 2nd column - 5th line (vertical)
	allDots[index++] = Dot(allWaypoints[13].position + yOffset, true);
	allDots[index++] = Dot(allDots[index-1].position + yOffset, true);


	// 3rd column - 6th line (horizontal)
	allDots[index++] = Dot(allWaypoints[21].position, true);
	allDots[index++] = Dot(allDots[index-1].position + xOffset, true);
	allDots[index++] = Dot(allDots[index-1].position + xOffset, true);


	// 4th column - 5th line (vertical)
	allDots[index++] = Dot(allWaypoints[28].position, true);
	allDots[index++] = Dot(allDots[index-1].position + yOffset, true);
	allDots[index++] = Dot(allDots[index-1].position + yOffset, true);
	allDots[index++] = Dot(allDots[index-1].position + yOffset, true);


	// 1st column - 5th line (horizontal)
	allDots[index++] = Dot(allWaypoints[4].position, true);
	allDots[index++] = Dot(allDots[index-1].position + xOffset, true);


	// 2nd column - 5th line (vertical)
	allDots[index++] = Dot(allWaypoints[7].position, true);
	allDots[index++] = Dot(allDots[index-1].position + yOffset, true);
	allDots[index++] = Dot(allDots[index-1].position + yOffset, true);


	// 3rd column - 6th line (horizontal)
	allDots[index++] = Dot(allWaypoints[14].position, true);
	allDots[index++] = Dot(allDots[index-1].position + xOffset, true);
	allDots[index++] = Dot(allDots[index-1].position + xOffset, true);
	// 3rd column - 6th line (vertical)
	allDots[index++] = Dot(allWaypoints[14].position + yOffset, true);
	allDots[index++] = Dot(allDots[index-1].position + yOffset, true);
	allDots[index++] = Dot(allDots[index-1].position + yOffset, true);


	// 4th column - 7th line (horizontal)
	allDots[index++] = Dot(allWaypoints[22].position, true);
	allDots[index++] = Dot(allDots[index-1].position + xOffset, true);
	allDots[index++] = Dot(allDots[index-1].position + xOffset, true);
	// 4th column - 7th line (vertical)
	allDots[index++] = Dot(allWaypoints[22].position + yOffset, true);
	allDots[index++] = Dot(allDots[index-1].position + yOffset, true);


	// 1st column - 6th line (horizontal)
	allDots[index++] = Dot(allWaypoints[5].position, true);
	allDots[index++] = Dot(allDots[index-1].position + xOffset, true);
	// 1st column - 6th line (vertical)
	allDots[index++] = Dot(allWaypoints[5].position + yOffset, true);
	allDots[index++] = Dot(allDots[index-1].position + yOffset, true);


	// 2nd column - 2nd line (horizontal)
	allDots[index++] = Dot(allWaypoints[8].position, true);
	allDots[index++] = Dot(allDots[index-1].position + xOffset, true);
	allDots[index++] = Dot(allDots[index-1].position + xOffset, true);


	// 4th column - 8th line (horizontal)
	allDots[index++] = Dot(allWaypoints[23].position, true);
	allDots[index++] = Dot(allDots[index-1].position + xOffset, true);
	allDots[index++] = Dot(allDots[index-1].position + xOffset, true);


	// 5th column - 7th line (vertical)
	allDots[index++] = Dot(allWaypoints[30].position, true);
	allDots[index++] = Dot(allDots[index-1].position + yOffset, true);
	allDots[index++] = Dot(allDots[index-1].position + yOffset, true);


	// 1st column - 7th line (horizontal)
	allDots[index++] = Dot(allWaypoints[6].position, true);
	allDots[index++] = Dot(allDots[index-1].position + xOffset, true);
	allDots[index++] = Dot(allDots[index-1].position + xOffset, true);
	allDots[index++] = Dot(allDots[index-1].position + xOffset, true);
	allDots[index++] = Dot(allDots[index-1].position + xOffset, true);
	allDots[index++] = Dot(allDots[index-1].position + xOffset, true);
	allDots[index++] = Dot(allDots[index-1].position + xOffset, true);
	allDots[index++] = Dot(allDots[index-1].position + xOffset, true);
	allDots[index++] = Dot(allDots[index-1].position + xOffset, true);
	allDots[index++] = Dot(allDots[index-1].position + xOffset, true);
	allDots[index++] = Dot(allDots[index-1].position + xOffset, true);


	// 2nd column - 8th line (horizontal)
	allDots[index++] = Dot(allWaypoints[31].position, true);
	allDots[index++] = Dot(allDots[index-1].position + xOffset, true);
	allDots[index++] = Dot(allDots[index-1].position + xOffset, true);
    
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
			if (!allDots[i].isEnabled)
			{
				continue;
			}
		
			// Only execute the next checks if the Y position is the same as the Pacman
			if (floor(pacman.sprite.position.y) == floor(allDots[i].position.y))
			{
				// Pacman's moving to the right
				if (pacman.sprite.position.x >= allDots[i].position.x
					&& pacman.previousPosition.x <= allDots[i].position.x)
				{
					EvaluateDot(allDots[i]);
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < DOTS_LENGTH; i++)
		{
			if (!allDots[i].isEnabled)
			{
				continue;
			}
		
			// Only execute the next checks if the Y position is the same as the Pacman
			if (floor(pacman.sprite.position.y) == floor(allDots[i].position.y))
			{
				// Pacman's moving to the left
				if (pacman.sprite.position.x <= allDots[i].position.x
					&& pacman.previousPosition.x >= allDots[i].position.x)
				{
					EvaluateDot(allDots[i]);
				}
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
			// Only execute the next checks if the Y position is the same as the Pacman
			if (floor(pacman.sprite.position.x) == floor(allDots[i].position.x))
			{
				// Pacman's moving to the right
				if (pacman.sprite.position.y >= allDots[i].position.y
					&& pacman.previousPosition.y <= allDots[i].position.y)
				{
					EvaluateDot(allDots[i]);
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < DOTS_LENGTH; i++)
		{
			// Only execute the next checks if the Y position is the same as the Pacman
			if (floor(pacman.sprite.position.x) == floor(allDots[i].position.x))
			{
				// Pacman's moving to the left
				if (pacman.sprite.position.y <= allDots[i].position.y
					&& pacman.previousPosition.y >= allDots[i].position.y)
				{
					if (allDots[i].isEnabled)
					{
						EvaluateDot(allDots[i]);
					}
				}
			}
		}
	}
}

void inline EvaluateDot(Dot& dot)
{
	dot.isEnabled = false;
	gameState->playerPoints += dot.isSpecial ? 20 : 5;
	LogInfo("POINT RECEIVED! total=%i", gameState->playerPoints);
}

void inline ResetDots()
{
	for (int i = 0; i < DOTS_LENGTH; i++)
	{
		allDots[i].isEnabled = true;
	}
}