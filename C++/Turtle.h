#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"

class Turtle : public sf::RectangleShape
{
public:
	const std::string TURTLE_TEXTURE = "images/turtle-anim.png";
	const std::string TURTLE_DEAD_TEXTURE = "images/turtle-anim-clicked.png";
	const float ACTIVE_TURTLE_DURATION = 2.0f;
	const int TEXTURE_COLS = 7;
	const int TEXTURE_ROWS = 7;

public:
	Turtle(sf::Vector2f size, int xCoordinate, int yCoordinate);
	~Turtle();
	void updateActiveStatus();
	void restartActiveTimer();
	void restartAnimTimer();
	void updateTexture();
	void resetAnimation();

public:
	bool isActive;
	bool isClicked;
	int xCoordinate;
	int yCoordinate;

private:
	sf::Texture turtleTexture;
	sf::Texture turtleClickedTexture;
	float activeDeltaTime;
	sf::Clock turtleActiveTimer;
	float animDeltaTime;
	Animation* turtleAnim;
	Animation* turtleClickedAnim;
	sf::Clock animTimer;

};
