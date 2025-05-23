#pragma once
#include <SFML/Graphics.hpp>
#include<SFML\Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <sstream>
#define MAX_NUMBER_OF_LEVELS 3
class levels
{
public:
	levels(float width, float height, sf::Font &font2);
	void draw(sf::RenderWindow &window);
	void MoveUp();
	void MoveDown();
	int GetPressedItem() { return index; }
	~levels();
private:
	int index;
	sf::Text menu5[MAX_NUMBER_OF_LEVELS];
};