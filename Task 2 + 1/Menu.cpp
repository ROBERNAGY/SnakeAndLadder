#include "Menu.h"
#include<iostream>
#include <SFML/Graphics.hpp>
Menu::Menu(float width , float height, sf::Font &font)
{
	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color::Blue);
	menu[0].setString("PLAY");
	menu[0].setPosition(sf::Vector2f(width /2.5, height / (MAX_NUMBER_OF_ITEMS_M + 1) * 1));
	menu[0].setCharacterSize(50);

	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::Red);
	menu[1].setString("HALL OF FAME");
	menu[1].setPosition(sf::Vector2f(width / 2.5, height / (MAX_NUMBER_OF_ITEMS_M + 1) * 2));
	menu[1].setCharacterSize(50);

	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::Red);
	menu[2].setString("OPTIONS");
	menu[2].setPosition(sf::Vector2f(width / 2.5, height / (MAX_NUMBER_OF_ITEMS_M + 1) * 3));
	menu[2].setCharacterSize(50);

	menu[3].setFont(font);
	menu[3].setFillColor(sf::Color::Red);
	menu[3].setString("ABOUT US");
	menu[3].setPosition(sf::Vector2f(width / 2.5, height / (MAX_NUMBER_OF_ITEMS_M + 1) * 4));
	menu[3].setCharacterSize(50);

	menu[4].setFont(font);
	menu[4].setFillColor(sf::Color::Red);
	menu[4].setString("EXIT");
	menu[4].setPosition(sf::Vector2f(width / 2.5, height / (MAX_NUMBER_OF_ITEMS_M + 1) * 5));
	menu[4].setCharacterSize(50);

	selectedItemIndex = 0;
}


Menu::~Menu()
{
}
void Menu::draw(sf::RenderWindow &window)
{
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS_M; i++)
	{
		window.draw(menu[i]);
	}
}

void Menu::MoveUp()
{
	if (selectedItemIndex - 1 >= 0)
	{
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
		selectedItemIndex--;
		menu[selectedItemIndex].setFillColor(sf::Color::Blue);
	}
}

void Menu::MoveDown()
{
	if (selectedItemIndex +1 <MAX_NUMBER_OF_ITEMS_M)
	{
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
		selectedItemIndex++;
		menu[selectedItemIndex].setFillColor(sf::Color::Blue);
	}
}