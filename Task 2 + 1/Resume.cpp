#include<SFML\Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <sstream>
#include "Resume.h"

using namespace std;
using namespace sf;

Resume::Resume(float width, float height, sf::Font &font)
{
	menu[0].setFont(font);
	menu[0].setFillColor(Color::Blue);
	menu[0].setString("Resume");
	menu[0].setPosition(Vector2f(width / 2.5, height / (MAX_NUMBER_OF_ITEMS_R + 1) * 1));
	menu[0].setCharacterSize(50);

	menu[1].setFont(font);
	menu[1].setFillColor(Color::Red);
	menu[1].setString("Options");
	menu[1].setPosition(Vector2f(width / 2.5, height / (MAX_NUMBER_OF_ITEMS_R + 1) * 2));
	menu[1].setCharacterSize(50);

	menu[2].setFont(font);
	menu[2].setFillColor(Color::Red);
	menu[2].setString("Go to main menu");
	menu[2].setPosition(Vector2f(width / 3.5, height / (MAX_NUMBER_OF_ITEMS_R + 1) * 3));
	menu[2].setCharacterSize(50);

	selectedItemIndex = 0;
}


Resume::~Resume()
{
}

void Resume::draw(RenderWindow & window)
{
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS_R; i++)
	{
		window.draw(menu[i]);
	}
}

void Resume::MoveUp()
{
	if (selectedItemIndex - 1 >= 0)
	{
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
		selectedItemIndex--;
		menu[selectedItemIndex].setFillColor(sf::Color::Blue);
	}
}

void Resume::MoveDown()
{
	if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS_R)
	{
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
		selectedItemIndex++;
		menu[selectedItemIndex].setFillColor(sf::Color::Blue);
	}
}

int Resume::GetPressedItem()
{
	return selectedItemIndex;
}