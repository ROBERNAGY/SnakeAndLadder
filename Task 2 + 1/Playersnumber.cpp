#include "Playersnumber.h"
#include<SFML\Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <sstream>


Playersnumber::Playersnumber(float width, float height ,sf::Font &font2)
{
	menu2[0].setFont(font2);
	menu2[0].setFillColor(sf::Color::Blue);
	menu2[0].setString("2 PLAYERS");
	menu2[0].setPosition(sf::Vector2f(width / 2.5, height / (MAX_NUMBER_OF_PLAYERS + 1) * 1));
	menu2[0].setCharacterSize(50);

	menu2[1].setFont(font2);
	menu2[1].setFillColor(sf::Color::Red);
	menu2[1].setString("3 PLAYERS");
	menu2[1].setPosition(sf::Vector2f(width / 2.5, height / (MAX_NUMBER_OF_PLAYERS + 1) * 2));
	menu2[1].setCharacterSize(50);

	menu2[2].setFont(font2);
	menu2[2].setFillColor(sf::Color::Red);
	menu2[2].setString("4 PLAYERS");
	menu2[2].setPosition(sf::Vector2f(width / 2.5, height / (MAX_NUMBER_OF_PLAYERS + 1) * 3));
	menu2[2].setCharacterSize(50);

	menu2[3].setFont(font2);
	menu2[3].setFillColor(sf::Color::Red);
	menu2[3].setString("BACK");
	menu2[3].setPosition(sf::Vector2f(width / 2.5, height / (MAX_NUMBER_OF_PLAYERS + 1) * 4));
	menu2[3].setCharacterSize(50);

	selectedItemIndex2 = 0;
}


Playersnumber::~Playersnumber()
{
}
void Playersnumber::draw(sf::RenderWindow &window)
{
	for (int i = 0; i < MAX_NUMBER_OF_PLAYERS; i++)
	{
		window.draw(menu2[i]);
	}
}
void Playersnumber::MoveUp()
{
	if (selectedItemIndex2 - 1 >= 0)
	{
		menu2[selectedItemIndex2].setFillColor(sf::Color::Red);
		selectedItemIndex2--;
		menu2[selectedItemIndex2].setFillColor(sf::Color::Blue);
	}
}

void Playersnumber::MoveDown()
{
	if (selectedItemIndex2 + 1 < MAX_NUMBER_OF_PLAYERS)
	{
		menu2[selectedItemIndex2].setFillColor(sf::Color::Red);
		selectedItemIndex2++;
		menu2[selectedItemIndex2].setFillColor(sf::Color::Blue);
	}
}