#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "GameWindow.h"

int main()
{
	GameWindow gameWindow(sf::Style::Close);

	sf::Event evnt;

	while (gameWindow.isOpen())
	{
		while (gameWindow.pollEvent(evnt))
		{
			if (evnt.type == sf::Event::Closed)
				gameWindow.close();

			if (evnt.type == sf::Event::MouseButtonReleased)
			{
				gameWindow.handleMouseClick();
			}
		}

		gameWindow.updateActiveScreenItems();
		gameWindow.displayActiveScreen();

	}

	return 0;
}