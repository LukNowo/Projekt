#pragma once
#include <SFML/Graphics.hpp>

class FloatingText
{
public:
	FloatingText(sf::Vector2f clickPos, sf::Font font, bool rotateClockwise);
	void update();

public:
	bool isActive;
	sf::Text text;

private:
	void updateRotation();
	void updateOpacity();
	void updateIsActive();
	void updateVertical();

private:
	float animDuration;
	float maxRotAngle;
	float maxVertical;
	sf::Clock animClock;
	bool rotateClockwise;
	sf::Vector2f startingPos;
};
