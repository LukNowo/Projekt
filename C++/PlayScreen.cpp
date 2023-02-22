#include "PlayScreen.h"

PlayScreen::PlayScreen(int numCols, int numRows, sf::Vector2f windowSize)
	: background(windowSize),
	mousePointer(sf::Vector2f(MOUSE_POINTER_SIZE_X, MOUSE_POINTER_SIZE_Y)),
	timerBar(sf::Vector2f(TIMER_BAR_SIZE_X, TIMER_BAR_SIZE_Y)),
	timerBarOutline(sf::Vector2f(TIMER_BAR_SIZE_X + 5.0f, TIMER_BAR_SIZE_Y + 4.0f))
{
	std::srand(time(0));

	turtlesSmashed = 0;
	turtleDeltaTime = 0;
	createTurtleFreq = STARTING_TURTLE_FREQ;

	font.loadFromFile(FONT);

	backgroundTexture.loadFromFile(BACKGROUND_TEXTURE);
	background.setTexture(&backgroundTexture);

	mouseTexture.loadFromFile(MOUSE_TEXTURE);
	mousePointer.setTexture(&mouseTexture);

	timerBarTexture.loadFromFile(TIMERBAR_TEXTURE);
	timerBar.setTexture(&timerBarTexture);
	timerBar.setPosition(sf::Vector2f(TIMER_BAR_POS_X, TIMER_BAR_POS_Y));
	timerBarOutline.setFillColor(sf::Color(sf::Color::White));
	timerBarOutline.setPosition(sf::Vector2f(TIMER_BAR_POS_X - 2.5f, TIMER_BAR_POS_Y - 2.5f));
	timerBarOutline.setOutlineColor(sf::Color::Black);
	timerBarOutline.setOutlineThickness(2.5f);

	turtleHoleSizeX = 600.0f / (float)numCols; //velikost díry
	turtleHoleSizeY = 300.0f / (float)numRows;
	float xOrigin = 450.0f / numCols;
	float yOrigin = 50.0f + (300.0f / numRows);
	float xOffset = (windowSize.x - xOrigin / 2.0f) / (float)numCols;
	float yOffset = (windowSize.y - yOrigin / 2.0f) / (float)numRows;

	turtleHoleTexture.loadFromFile(TURTLE_HOLE_TEXTURE);

	for (int i = 0; i < numCols; i++) // využití matice pro rozmístìní dír 3x3
	{
		for (int j = 0; j < numRows; j++)
		{
			turtleHoles[i][j] = sf::RectangleShape(sf::Vector2f(turtleHoleSizeX, turtleHoleSizeY));
			turtleHoles[i][j].setOrigin(turtleHoleSizeX / 2.0f, turtleHoleSizeY / 2.0f);
			turtleHoles[i][j].setPosition((float)(i * xOffset + xOrigin), (float)(j * yOffset + yOrigin));
			turtleHoles[i][j].setTexture(&turtleHoleTexture);
		}
	}

	for (int i = 0; i < numCols; i++) // matice pro umístìní želv
	{

		for (int j = 0; j < numRows; j++)
		{
			turtles[i][j] = new Turtle(sf::Vector2f(turtleHoleSizeY, turtleHoleSizeY), i, j);
			turtles[i][j]->setOrigin(turtleHoleSizeY / 2.0f, turtleHoleSizeY / 2.0f);
			turtles[i][j]->setPosition((float)(i * xOffset + xOrigin), (float)(j * yOffset + yOrigin));
		}
	}

}

PlayScreen::~PlayScreen()
{
	for (int i = 0; i < NUM_TURTLE_HOLE_COLS; i++)
	{
		for (int j = 0; j < NUM_TURTLE_HOLE_ROWS; j++)
		{
			delete turtles[i][j];
		}
	}
}

void PlayScreen::handleMouseClick(sf::Vector2i clickPos) 
{

	for (int i = 0; i < NUM_TURTLE_HOLE_COLS; i++)
	{
		for (int j = 0; j < NUM_TURTLE_HOLE_ROWS; j++)
		{
			if (this->mouseClicksTurtle(clickPos, i, j) && turtles[i][j]->isActive)
			{
				if (clickTextRotation)
					clickTextRotation = false;
				else
					clickTextRotation = true;

				turtleClickText.push_back(FloatingText(sf::Vector2f((float)clickPos.x, (float)clickPos.y), font, clickTextRotation));

				if (!turtles[i][j]->isClicked)
				{
					turtles[i][j]->isClicked = true;
					turtlesSmashed++; 
				}

			}
		}
	}
}

bool PlayScreen::mouseClicksTurtle(sf::Vector2i clickPos, int xCoord, int yCoord)
{
	int turtleCoordX1 = (int)turtles[xCoord][yCoord]->getPosition().x - (int)(turtleHoleSizeY / 2.0f); 
	int turtleCoordX2 = turtleCoordX1 + (int)turtleHoleSizeY;
	int turtleCoordY1 = (int)turtles[xCoord][yCoord]->getPosition().y - (int)(turtleHoleSizeY / 2.0f);
	int turtleCoordY2 = turtleCoordY1 + (int)turtleHoleSizeY;

	if (clickPos.x > turtleCoordX1 && clickPos.x < turtleCoordX2)
	{
		if (clickPos.y > turtleCoordY1 && clickPos.y < turtleCoordY2)
		{
			return true;
		}
		else
			return false;
	}
	else
		return false;
}

int PlayScreen::getTurtlesWhacked()
{
	return turtlesSmashed;
}

void PlayScreen::updateActiveTurtles()
{
	for (int i = 0; i < NUM_TURTLE_HOLE_COLS; i++)
	{
		for (int j = 0; j < NUM_TURTLE_HOLE_ROWS; j++)
		{
			turtles[i][j]->updateActiveStatus();
			turtles[i][j]->updateTexture();
		}
	}
}

void PlayScreen::updateTurtleCreation() //
{
	turtleDeltaTime = turtleCreationTimer.getElapsedTime().asSeconds();

	if (turtleDeltaTime > createTurtleFreq)
	{
		turtleCreationTimer.restart();

		std::vector<Turtle*> inactiveTurtles;
		int numActive = 0;

		for (int i = 0; i < NUM_TURTLE_HOLE_COLS; i++)
		{
			for (int j = 0; j < NUM_TURTLE_HOLE_ROWS; j++)
			{
				if (!turtles[i][j]->isActive)
				{
					inactiveTurtles.push_back(turtles[i][j]);
					numActive++;
				}
			}
		}

		if (numActive > 0)
		{
			int randTurtleIndex = rand() % numActive;
			inactiveTurtles[randTurtleIndex]->isActive = true;
			inactiveTurtles[randTurtleIndex]->restartAnimTimer();
			inactiveTurtles[randTurtleIndex]->resetAnimation();
			inactiveTurtles[randTurtleIndex]->restartActiveTimer();
		}

	}
}

void PlayScreen::updateTurtleCreationRate() //frekvence spawnování 
{
	if (timerBarClock.getElapsedTime().asSeconds() > THIRD_PHASE_START_TIME)
	{
		createTurtleFreq = THIRD_TURTLE_FREQ;
	}
	else if (timerBarClock.getElapsedTime().asSeconds() > SECOND_PHASE_START_TIME)
	{
		createTurtleFreq = SECOND_TURTLE_FREQ;
	}

}

void PlayScreen::updateTimerBar()
{
	timerBar.setSize(sf::Vector2f(((GAMEOVER_TIME - timerBarClock.getElapsedTime().asSeconds()) / GAMEOVER_TIME) * TIMER_BAR_SIZE_X, TIMER_BAR_SIZE_Y));
}

void PlayScreen::updateClickText()
{
	for (iter = turtleClickText.begin(); iter < turtleClickText.end(); iter++)
	{
		(*iter).update();
	}

	if (turtleClickText.size() > 0)
	{
		if (!turtleClickText[0].isActive)
			turtleClickText.erase(turtleClickText.begin());
	}

}

bool PlayScreen::isGameOver()
{
	if (timerBarClock.getElapsedTime().asSeconds() >= GAMEOVER_TIME)
	{
		return true;
	}
	else
		return false;
}

void PlayScreen::draw(sf::RenderWindow* window)
{
	window->clear();
	window->draw(background);

	for (int i = 0; i < NUM_TURTLE_HOLE_COLS; i++)
	{
		for (int j = 0; j < NUM_TURTLE_HOLE_ROWS; j++)
		{
			window->draw(turtleHoles[i][j]);
		}
	}

	for (int i = 0; i < NUM_TURTLE_HOLE_COLS; i++)
	{
		for (int j = 0; j < NUM_TURTLE_HOLE_ROWS; j++)
		{
			if (turtles[i][j]->isActive)
			{
				window->draw((*turtles[i][j]));
			}
		}
	}

	window->draw(timerBarOutline);
	window->draw(timerBar);

	mousePos = sf::Mouse::getPosition(*window);
	mousePointer.setPosition((float)mousePos.x, (float)mousePos.y);
	window->draw(mousePointer);

	for (iter = turtleClickText.begin(); iter < turtleClickText.end(); iter++)
	{
		std::string s = (std::string)((*iter).text.getString());
		sf::Text t(s, font);
		t.setOrigin(sf::Vector2f(55.0f, 5.0f));
		t.setPosition((*iter).text.getPosition());
		t.setRotation((*iter).text.getRotation());
		t.setFillColor((*iter).text.getFillColor());
		window->draw(t);
	}

	window->display();
}

void PlayScreen::reset()
{
	turtlesSmashed = 0;
	timerBarClock.restart();
	turtleCreationTimer.restart();
	createTurtleFreq = STARTING_TURTLE_FREQ;
}