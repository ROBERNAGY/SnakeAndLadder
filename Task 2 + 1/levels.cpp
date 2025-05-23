#include "levels.h"
#include<SFML\Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <sstream>



levels::levels(float width, float height, sf::Font &font2)
{
	menu5[0].setFont(font2);
	menu5[0].setFillColor(sf::Color::Blue);
	menu5[0].setString("NORMAL");
	menu5[0].setPosition(sf::Vector2f(width / 2.5, height / (MAX_NUMBER_OF_LEVELS + 1) * 1));
	menu5[0].setCharacterSize(50);

	menu5[1].setFont(font2);
	menu5[1].setFillColor(sf::Color::Red);
	menu5[1].setString("INSANE");
	menu5[1].setPosition(sf::Vector2f(width / 2.5, height / (MAX_NUMBER_OF_LEVELS + 1) * 2));
	menu5[1].setCharacterSize(50);

	menu5[2].setFont(font2);
	menu5[2].setFillColor(sf::Color::Red);
	menu5[2].setString("BACK");
	menu5[2].setPosition(sf::Vector2f(width / 2.5, height / (MAX_NUMBER_OF_LEVELS + 1) * 3));
	menu5[2].setCharacterSize(50);

	index = 0;
}


levels::~levels()
{
}
void levels::draw(sf::RenderWindow &window)
{
	for (int i = 0; i < MAX_NUMBER_OF_LEVELS; i++)
	{
		window.draw(menu5[i]);
	}
}
void levels::MoveUp()
{
	if (index - 1 >= 0)
	{
		menu5[index].setFillColor(sf::Color::Red);
		index--;
		menu5[index].setFillColor(sf::Color::Blue);
	}
}

void levels::MoveDown()
{
	if (index + 1 < MAX_NUMBER_OF_LEVELS)
	{
		menu5[index].setFillColor(sf::Color::Red);
		index++;
		menu5[index].setFillColor(sf::Color::Blue);
	}
}