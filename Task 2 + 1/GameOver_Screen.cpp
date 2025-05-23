#include<SFML\Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <sstream>
#include "GameOver_Screen.h"

using namespace std;
using namespace sf;


GameOver_Screen::GameOver_Screen(float width, float height, sf::Font &font)
{
	menu[0].setFont(font);
	menu[0].setFillColor(Color::Blue);
	menu[0].setString("Play again");
	menu[0].setCharacterSize(75);
	menu[0].setPosition(Vector2f(width / 4.5, height / 4 * 3));

	menu[1].setFont(font);
	menu[1].setFillColor(Color::Red);
	menu[1].setString("Exit");
	menu[1].setCharacterSize(75);
	menu[1].setPosition(Vector2f(width / 1.4, height / 4 * 3));

	selectedItemIndex = 0;
}


GameOver_Screen::~GameOver_Screen()
{
}

void GameOver_Screen::draw(sf::RenderWindow & window)
{
	for (int i = 0; i < 2; i++)
	{
		window.draw(menu[i]);
	}
}

void GameOver_Screen::MoveLeft()
{
	if (menu[1].getFillColor() == Color::Blue)
	{
		menu[1].setFillColor(sf::Color::Red);
		menu[0].setFillColor(sf::Color::Blue);
	}
}

void GameOver_Screen::MoveRight()
{
	if (menu[0].getFillColor() == Color::Blue)
	{
		menu[0].setFillColor(sf::Color::Red);
		menu[1].setFillColor(sf::Color::Blue);
	}
}

int GameOver_Screen::getItemPressed()
{
	if (menu[0].getFillColor() == Color::Blue)
	{
		return 0;
	}
	else if (menu[1].getFillColor() == Color::Blue)
	{
		return 1;
	}
}