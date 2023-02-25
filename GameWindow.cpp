#include "GameWindow.h"

GameWindow::GameWindow(sf::Uint32 style) 
	: sf::RenderWindow(sf::VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y), "Smash a turtle", style),
	playScreen(PlayScreen::NUM_TURTLE_HOLE_COLS, PlayScreen::NUM_TURTLE_HOLE_ROWS, sf::Vector2f((float)WINDOW_SIZE_X, (float)WINDOW_SIZE_Y)),
	scoreScreen(sf::Vector2f((float)WINDOW_SIZE_X, (float)WINDOW_SIZE_Y))
{
	this->setMouseCursorVisible(false);
	this->activeScreen = PLAY_SCREEN;
}

void GameWindow::displayActiveScreen()
{
	if (activeScreen == START_SCREEN)
	{
		
	}
	else if (activeScreen == PLAY_SCREEN)
	{
		playScreen.draw(this); 
	}
	else if (activeScreen == SCORE_SCREEN)
	{
		scoreScreen.display(this);
	}
}


void GameWindow::handleMouseClick()
{
	mousePos = sf::Mouse::getPosition(*this);

	if (activeScreen == PLAY_SCREEN)
	{
		playScreen.handleMouseClick(mousePos);
	}
	else if (activeScreen == SCORE_SCREEN)
	{
		scoreScreen.handleMouseClick(mousePos);
	}
}

void GameWindow::updateActiveScreenItems()
{
	if (activeScreen == START_SCREEN)
	{

	}
	else if (activeScreen == PLAY_SCREEN)
	{
		playScreen.updateTimerBar(); 
		playScreen.updateTurtleCreationRate();
		playScreen.updateTurtleCreation();
		playScreen.updateActiveTurtles();
		playScreen.updateClickText();
		if (playScreen.isGameOver())
		{
			this->setMouseCursorVisible(true);
			scoreScreen.setScore(playScreen.getTurtlesWhacked());
			scoreScreen.animClock.restart();
			activeScreen = SCORE_SCREEN;
		}

	}
	else if (activeScreen == SCORE_SCREEN)
	{
		if (scoreScreen.replayButtonClicked)
		{
			this->setMouseCursorVisible(false);
			scoreScreen.replayButtonClicked = false;
			playScreen.reset();
			activeScreen = PLAY_SCREEN;
		}
	}
}