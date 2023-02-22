#pragma once
#include <SFML/Graphics.hpp>
#include <cstdlib>

class ScoreScreen
{
public:
	const std::string BACKGROUND_TEXTURE = "images/pozadí_menu.png";
	const std::string FONT = "fonts/uni0553-webfont.ttf";
	const std::string REPLAY_TEXTURE = "images/button.png";
	const float animInterval = 1.0f; 

public:
	ScoreScreen(sf::Vector2f windowSize);
	void display(sf::RenderWindow* window);
	void handleMouseClick(sf::Vector2i clickPos);
	void setScore(int score);

private:
	void createHeader();
	void createScoreSection();
	void createDescription();
	void createReplayButton();

public:
	sf::Clock animClock;
	bool replayButtonClicked;

private:
	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	sf::Texture replayButtonTexture;
	sf::RectangleShape replayButton;
	sf::Text replayText;
	sf::Font font;
	sf::Text gameOver;
	sf::Text gameOverShadow;
	sf::RectangleShape scoreOutline;
	sf::Text scoreText;
	sf::Text scoreValue;
	sf::Text scoreDescription;
	sf::Text scoreDescriptionShadow;
	int replayCoordX1;
	int replayCoordX2;
	int replayCoordY1;
	int replayCoordY2;

};