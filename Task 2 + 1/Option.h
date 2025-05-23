#pragma once
#include<SFML\Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <sstream>

#define MAX_NUMBER_OF_ITEMS_O 3
class Option
{
public:
	Option(float width, float height, sf::Font &font3);
	~Option();
	void draw(sf::RenderWindow &window);
	void MoveUp();
	void MoveDown();
	int GetPressedItem() { return selectedItemIndex3; }
private:
	int selectedItemIndex3;
	sf::Text menu3[MAX_NUMBER_OF_ITEMS_O];
};

