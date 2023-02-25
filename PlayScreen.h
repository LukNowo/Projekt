#pragma once

#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <vector>
#include "Turtle.h"
#include "FloatingText.h"

class PlayScreen
{
public:
	const std::string TURTLE_HOLE_TEXTURE = "images/dira.png";
	const std::string MOUSE_TEXTURE = "images/kladivo.png";
	const std::string BACKGROUND_TEXTURE = "images/pozadí_hry.png";
	const std::string TIMERBAR_TEXTURE = "images/èas.png";
	const std::string FONT = "fonts/uni0553-webfont.ttf";
	const float MOUSE_POINTER_SIZE_X = 100.0f; 
	const float MOUSE_POINTER_SIZE_Y = 100.0f;
	const static int NUM_TURTLE_HOLE_COLS = 3;
	const static int NUM_TURTLE_HOLE_ROWS = 3;
	const float GAMEOVER_TIME = 40.0f; 
	const float STARTING_TURTLE_FREQ = 2.5f; //NASTAVENÍ FREKVENCE SPAWNOVÁNÍ
	const float SECOND_TURTLE_FREQ = STARTING_TURTLE_FREQ / 2.0f;
	const float THIRD_TURTLE_FREQ = SECOND_TURTLE_FREQ / 3.0f;
	const float SECOND_PHASE_START_TIME = 10.0f;
	const float THIRD_PHASE_START_TIME = 23.0f;
	const float TIMER_BAR_POS_X = 275.0f;
	const float TIMER_BAR_POS_Y = 25.0f;
	const float TIMER_BAR_SIZE_X = 250.0f;
	const float TIMER_BAR_SIZE_Y = 25.0f;

public:
	PlayScreen(int numCols, int numRows, sf::Vector2f);
	~PlayScreen();
	void handleMouseClick(sf::Vector2i clickPos);
	void updateActiveTurtles();
	void updateTurtleCreationRate();
	void updateTurtleCreation();
	void updateTimerBar();
	void updateClickText();
	void draw(sf::RenderWindow* window);
	bool isGameOver();
	int getTurtlesWhacked();
	void reset();

public:
	sf::RectangleShape background; 
	sf::RectangleShape mousePointer;
	sf::RectangleShape timerBar;
	sf::RectangleShape timerBarOutline;
	sf::RectangleShape turtleHoles[NUM_TURTLE_HOLE_COLS][NUM_TURTLE_HOLE_ROWS];
	Turtle* turtles[NUM_TURTLE_HOLE_COLS][NUM_TURTLE_HOLE_ROWS];
	std::vector<FloatingText> turtleClickText;
	std::vector<FloatingText>::iterator iter;

private:
	bool mouseClicksTurtle(sf::Vector2i mousePos, int xCoord, int yCoord);

private:
	sf::Texture mouseTexture;
	sf::Texture turtleHoleTexture;
	sf::Texture backgroundTexture;
	sf::Texture timerBarTexture;
	sf::Vector2i mousePos;
	int turtlesSmashed;
	float turtleHoleSizeX;
	float turtleHoleSizeY;
	sf::Clock timerBarClock;
	sf::Clock turtleCreationTimer;
	float turtleDeltaTime;
	float createTurtleFreq;
	sf::Font font;
	bool clickTextRotation;
};