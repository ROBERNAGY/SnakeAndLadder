#include "Nameofplayers2.h"
#include<iostream>
#include <SFML/Graphics.hpp>



Nameofplayers2::Nameofplayers2(float width, float height, sf::Font &font3)
{
	menu3[0].setFont(font3);
	menu3[0].setFillColor(sf::Color::Blue);
	menu3[0].setString("PLAYER 1");
	menu3[0].setPosition(sf::Vector2f(width / 2.5, height / (MAX_NUMBER_OF_ITEMS_N2 + 1) * 1));
	menu3[0].setCharacterSize(50);

	menu3[1].setFont(font3);
	menu3[1].setFillColor(sf::Color::Red);
	menu3[1].setString("PLAYER 2");
	menu3[1].setPosition(sf::Vector2f(width / 2.5, height / (MAX_NUMBER_OF_ITEMS_N2 + 1) * 2));
	menu3[1].setCharacterSize(50);

	menu3[2].setFont(font3);
	menu3[2].setFillColor(sf::Color::Red);
	menu3[2].setString("PLAYER 3");
	menu3[2].setPosition(sf::Vector2f(width / 2.5, height / (MAX_NUMBER_OF_ITEMS_N2 + 1) * 3));
	menu3[2].setCharacterSize(50);

	menu3[3].setFont(font3);
	menu3[3].setFillColor(sf::Color::Red);
	menu3[3].setString("Select Mode");
	menu3[3].setPosition(sf::Vector2f(width / 2.5, height / (MAX_NUMBER_OF_ITEMS_N2 + 1) * 4));
	menu3[3].setCharacterSize(50);

	menu3[4].setFont(font3);
	menu3[4].setFillColor(sf::Color::Red);
	menu3[4].setString("BACK");
	menu3[4].setPosition(sf::Vector2f(width / 2.5, height / (MAX_NUMBER_OF_ITEMS_N2 + 1) * 5));
	menu3[4].setCharacterSize(50);

	selectedItemIndex3 = 0;
}


Nameofplayers2::~Nameofplayers2()
{
}
void Nameofplayers2::draw(sf::RenderWindow &window)
{
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS_N2; i++)
	{
		window.draw(menu3[i]);
	}
}

void Nameofplayers2::MoveUp()
{
	if (selectedItemIndex3 - 1 >= 0)
	{
		menu3[selectedItemIndex3].setFillColor(sf::Color::Red);
		selectedItemIndex3--;
		menu3[selectedItemIndex3].setFillColor(sf::Color::Blue);
	}
}

void Nameofplayers2::MoveDown()
{
	if (selectedItemIndex3 + 1 < MAX_NUMBER_OF_ITEMS_N2)
	{
		menu3[selectedItemIndex3].setFillColor(sf::Color::Red);
		selectedItemIndex3++;
		menu3[selectedItemIndex3].setFillColor(sf::Color::Blue);
	}
}