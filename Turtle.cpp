#include "Turtle.h"

Turtle::Turtle(sf::Vector2f size, int xCoordinate, int yCoordinate) : sf::RectangleShape(size)
{
	this->xCoordinate = xCoordinate;  //nastavení souøadnic
	this->yCoordinate = yCoordinate;

	animDeltaTime = 0.0f;

	turtleTexture.loadFromFile(TURTLE_TEXTURE);	//elva
	this->setTexture(&turtleTexture);
	turtleAnim = new Animation(&turtleTexture, sf::Vector2u(TEXTURE_COLS, TEXTURE_ROWS), ACTIVE_TURTLE_DURATION / (float)(TEXTURE_COLS * TEXTURE_ROWS));

	turtleClickedTexture.loadFromFile(TURTLE_DEAD_TEXTURE);	//mrtvá elva
	turtleClickedAnim = new Animation(&turtleClickedTexture, sf::Vector2u(TEXTURE_COLS, TEXTURE_ROWS), ACTIVE_TURTLE_DURATION / (float)(TEXTURE_COLS * TEXTURE_ROWS));

	isActive = false;
	isClicked = false;
	activeDeltaTime = 0.0f; //naètení obrázkù elvy
}

Turtle::~Turtle()
{
	delete turtleAnim;
	delete turtleClickedAnim;
}

void Turtle::updateActiveStatus()
{
	if (isActive) //spuštìní animace
	{
		activeDeltaTime = turtleActiveTimer.getElapsedTime().asSeconds();

		if (activeDeltaTime > ACTIVE_TURTLE_DURATION)
		{
			isActive = false;
			isClicked = false;
			turtleActiveTimer.restart();
		}
	}
}

void Turtle::restartActiveTimer()
{
	turtleActiveTimer.restart();
}

void Turtle::updateTexture()
{
	animDeltaTime = animTimer.getElapsedTime().asSeconds();
	animTimer.restart();

	if (isClicked)
	{
		turtleClickedAnim->update(animDeltaTime);// animace po kliknutí
		this->setTexture(&turtleClickedTexture);
		this->setTextureRect(turtleClickedAnim->uvRect);
	}
	else
	{
		turtleAnim->update(animDeltaTime);
		turtleClickedAnim->update(animDeltaTime);
		this->setTexture(&turtleTexture);
		this->setTextureRect(turtleAnim->uvRect);
	}
}

void Turtle::resetAnimation()
{
	turtleAnim->reset();
	turtleClickedAnim->reset();
}

void Turtle::restartAnimTimer()
{
	animTimer.restart();
}