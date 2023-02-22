#include "ScoreScreen.h"

ScoreScreen::ScoreScreen(sf::Vector2f windowSize)
	: background(windowSize)
{
	replayButtonClicked = false;

	backgroundTexture.loadFromFile(BACKGROUND_TEXTURE);
	background.setTexture(&backgroundTexture);

	replayButtonTexture.loadFromFile(REPLAY_TEXTURE);
	replayButton.setTexture(&replayButtonTexture);

	font.loadFromFile(FONT);

	createHeader();
	createScoreSection();
	createDescription();
	createReplayButton(); // nastavení pozadí a menu
}

void ScoreScreen::display(sf::RenderWindow* window)
{
	window->clear();
	window->draw(background);

	if (animClock.getElapsedTime().asSeconds() > animInterval)
	{
		window->draw(gameOverShadow);
		window->draw(gameOver);
	}

	if (animClock.getElapsedTime().asSeconds() > animInterval * 2)
	{
		window->draw(scoreOutline);
		window->draw(scoreText);
	}

	if (animClock.getElapsedTime().asSeconds() > animInterval * 3)
	{
		window->draw(scoreValue);
	}

	if (animClock.getElapsedTime().asSeconds() > animInterval * 4)
	{
		window->draw(scoreDescriptionShadow);
		window->draw(scoreDescription);
	}

	if (animClock.getElapsedTime().asSeconds() > animInterval * 5)
	{
		window->draw(replayButton);
		window->draw(replayText);
	}

	window->display();
}


void ScoreScreen::createHeader() //GAMEOVER menu nadpis a stíny
{
	gameOver.setFont(font);
	gameOver.setCharacterSize(80);
	gameOver.setString("---Game Over---");
	gameOver.setPosition(sf::Vector2f(18.0f, 5.0f));

	gameOverShadow.setFont(font);
	gameOverShadow.setCharacterSize(80);
	gameOverShadow.setString("---Game Over---");
	gameOverShadow.setFillColor(sf::Color::Black);
	gameOverShadow.setPosition(sf::Vector2f(21.0f, 8.0f));
}

void ScoreScreen::createScoreSection() //SCORE sekce
{

	scoreOutline.setTexture(&backgroundTexture);
	sf::Vector2f scoreOutlineSize(350.0f, 100.0f);
	scoreOutline.setSize(scoreOutlineSize);
	sf::Vector2f scoreOutlinePosition(225.0f, 200.0f);
	scoreOutline.setPosition(scoreOutlinePosition);
	scoreOutline.setTextureRect(sf::IntRect(scoreOutlinePosition.x * 10,
		scoreOutlinePosition.y * 10, scoreOutlineSize.x * 10, scoreOutlineSize.y * 10));
	scoreOutline.setOutlineColor(sf::Color::Black);
	scoreOutline.setOutlineThickness(4);

	scoreText.setFont(font);
	scoreText.setCharacterSize(45);
	scoreText.setFillColor(sf::Color(255, 255, 255));
	scoreText.setString("Score:");
	scoreText.setPosition(sf::Vector2f(245.0f, 220.0f));

	scoreValue.setFont(font);
	scoreValue.setCharacterSize(45);
	scoreValue.setString("0");
	scoreValue.setPosition(sf::Vector2f(435.0f, 220.0f));
}


void ScoreScreen::createDescription() //menu podnadpis
{
	scoreDescription.setFont(font);
	scoreDescription.setCharacterSize(70);
	scoreDescription.setString("Great Job!!");
	scoreDescription.setPosition(sf::Vector2f(190.0f, 340.0f));

	scoreDescriptionShadow.setFont(font);
	scoreDescriptionShadow.setCharacterSize(70);
	scoreDescriptionShadow.setFillColor(sf::Color::Black);
	scoreDescriptionShadow.setString("Great Job!!");
	scoreDescriptionShadow.setPosition(sf::Vector2f(193.0f, 343.0f));
}


void ScoreScreen::createReplayButton() //PLAYAGAIN button
{
	replayButton.setSize(sf::Vector2f(300.0f, 100.0f));
	replayButton.setPosition(sf::Vector2f(250.0f, 475.0f));

	replayText.setFont(font);
	replayText.setCharacterSize(40);
	replayText.setFillColor(sf::Color::White);
	replayText.setString("PLAY AGAIN");
	replayText.setPosition(sf::Vector2f(272.0f, 500.0f));

	replayCoordX1 = (int)replayButton.getPosition().x;
	replayCoordX2 = replayCoordX1 + (int)replayButton.getSize().x;
	replayCoordY1 = (int)replayButton.getPosition().y;
	replayCoordY2 = replayCoordY1 + (int)replayButton.getSize().y;
}

void ScoreScreen::handleMouseClick(sf::Vector2i clickPos) // zakliknutí playagain
{
	if (clickPos.x > replayCoordX1 && clickPos.x < replayCoordX2)
	{
		if (clickPos.y > replayCoordY1 && clickPos.y < replayCoordY2)
		{
			replayButtonClicked = true;
		}
	}
}

void ScoreScreen::setScore(int score) //výpoèet score
{
	scoreValue.setString(std::to_string(score * 100));
}