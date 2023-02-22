#include "FloatingText.h"

FloatingText::FloatingText(sf::Vector2f clickPos,  sf::Font font, bool rotateClockwise) //Text po trefení cíle, dodána rotace textu pro efekt a 45stpnu nahodnì do obou stran + pøechod do ztracena
	: text("SMACK!!!", font, 30),
	startingPos(clickPos)
{
	animDuration = 1.0f;
	maxRotAngle = 45.0f;
	maxVertical = -45.0f;

	this->rotateClockwise = rotateClockwise;

	text.setPosition(startingPos);

	isActive = true;
}

void FloatingText::update()
{
	updateRotation();
	updateOpacity();
	updateIsActive();
	updateVertical();
}

void FloatingText::updateRotation()
{
	if (rotateClockwise)
		text.setRotation(maxRotAngle * (animClock.getElapsedTime().asSeconds() / animDuration));
	else
		text.setRotation(-1 * maxRotAngle * (animClock.getElapsedTime().asSeconds() / animDuration));
}

void FloatingText::updateOpacity()
{
	text.setFillColor(sf::Color(255, 255, 255, 255 - (255 * (animClock.getElapsedTime().asSeconds() / animDuration))));
}

void FloatingText::updateIsActive()
{
	if (animClock.getElapsedTime().asSeconds() > animDuration)
		isActive = false;
}

void FloatingText::updateVertical()
{
	text.setPosition(sf::Vector2f(startingPos.x, startingPos.y + (maxVertical * (animClock.getElapsedTime().asSeconds() / animDuration))));
}