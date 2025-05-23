#include "Nameofplayers.h"
#include<iostream>
#include <SFML/Graphics.hpp>


Nameofplayers::Nameofplayers(float width, float height, sf::Font &font3)
{
	menu3[0].setFont(font3);
	menu3[0].setFillColor(sf::Color::Blue);
	menu3[0].setString("PLAYER 1");
	menu3[0].setPosition(sf::Vector2f(width / 2.5, height / (MAX_NUMBER_OF_ITEMS_N + 1) * 1));
	menu3[0].setCharacterSize(50);

	menu3[1].setFont(font3);
	menu3[1].setFillColor(sf::Color::Red);
	menu3[1].setString("PLAYER 2");
	menu3[1].setPosition(sf::Vector2f(width / 2.5, height / (MAX_NUMBER_OF_ITEMS_N + 1) * 2));
	menu3[1].setCharacterSize(50);

	menu3[2].setFont(font3);
	menu3[2].setFillColor(sf::Color::Red);
	menu3[2].setString("PLAYER 3");
	menu3[2].setPosition(sf::Vector2f(width / 2.5, height / (MAX_NUMBER_OF_ITEMS_N + 1) * 3));
	menu3[2].setCharacterSize(50);

	menu3[3].setFont(font3);
	menu3[3].setFillColor(sf::Color::Red);
	menu3[3].setString("PLAYER 4");
	menu3[3].setPosition(sf::Vector2f(width / 2.5, height / (MAX_NUMBER_OF_ITEMS_N + 1) * 4));
	menu3[3].setCharacterSize(50);

	menu3[4].setFont(font3);
	menu3[4].setFillColor(sf::Color::Red);
	menu3[4].setString("Select Mode");
	menu3[4].setPosition(sf::Vector2f(width / 2.5, height / (MAX_NUMBER_OF_ITEMS_N + 1) * 5));
	menu3[4].setCharacterSize(50);

	menu3[5].setFont(font3);
	menu3[5].setFillColor(sf::Color::Red);
	menu3[5].setString("BACK");
	menu3[5].setPosition(sf::Vector2f(width / 2.5, height / (MAX_NUMBER_OF_ITEMS_N + 1) * 6));
	menu3[5].setCharacterSize(50);

	selectedItemIndex3 = 0;
}


Nameofplayers::~Nameofplayers()
{
}
void Nameofplayers::draw(sf::RenderWindow &window)
{
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS_N; i++)
	{
		window.draw(menu3[i]);
	}
}

void Nameofplayers::MoveUp()
{
	if (selectedItemIndex3 - 1 >= 0)
	{
		menu3[selectedItemIndex3].setFillColor(sf::Color::Red);
		selectedItemIndex3 --;
		menu3[selectedItemIndex3].setFillColor(sf::Color::Blue);
	}
}

void Nameofplayers::MoveDown()
{
	if (selectedItemIndex3 + 1 < MAX_NUMBER_OF_ITEMS_N)
	{
		menu3[selectedItemIndex3].setFillColor(sf::Color::Red);
		selectedItemIndex3 ++;
		menu3[selectedItemIndex3].setFillColor(sf::Color::Blue);
	}
}