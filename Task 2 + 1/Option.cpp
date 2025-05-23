#include "Option.h"
#include<SFML\Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <sstream>



Option::Option(float width, float height, sf::Font &font3)
{
	menu3[0].setFont(font3);
	menu3[0].setFillColor(sf::Color::Blue);
	menu3[0].setString("<< VOLUME >>");
	menu3[0].setPosition(sf::Vector2f(width / 2.9, height / (MAX_NUMBER_OF_ITEMS_O + 1) * 1));
	menu3[0].setCharacterSize(50);

	menu3[1].setFont(font3);
	menu3[1].setFillColor(sf::Color::Red);
	menu3[1].setString("Music");
	menu3[1].setPosition(sf::Vector2f(width / 2.5, height / (MAX_NUMBER_OF_ITEMS_O + 1) * 2));
	menu3[1].setCharacterSize(50);

	menu3[2].setFont(font3);
	menu3[2].setFillColor(sf::Color::Red);
	menu3[2].setString("BACK");
	menu3[2].setPosition(sf::Vector2f(width / 2.5, height / (MAX_NUMBER_OF_ITEMS_O + 1) * 3));
	menu3[2].setCharacterSize(50);

	selectedItemIndex3 = 0;
}


Option::~Option()
{
}
void Option::draw(sf::RenderWindow &window)
{
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS_O; i++)
	{
		window.draw(menu3[i]);
	}
}

void Option::MoveUp()
{
	if (selectedItemIndex3 - 1 >= 0)
	{
		menu3[selectedItemIndex3].setFillColor(sf::Color::Red);
		selectedItemIndex3--;
		menu3[selectedItemIndex3].setFillColor(sf::Color::Blue);
	}
}

void Option::MoveDown()
{
	if (selectedItemIndex3 + 1 < MAX_NUMBER_OF_ITEMS_O)
	{
		menu3[selectedItemIndex3].setFillColor(sf::Color::Red);
		selectedItemIndex3++;
		menu3[selectedItemIndex3].setFillColor(sf::Color::Blue);
	}
}