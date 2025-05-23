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
#define MAX_NUMBER_OF_PLAYERS 4
class Playersnumber
{
public:
	Playersnumber(float width, float height ,sf::Font &font2);
	~Playersnumber();
	void draw(sf::RenderWindow &window);
	void MoveUp();
	void MoveDown();
	int GetPressedItem() { return selectedItemIndex2; }
private:
	int selectedItemIndex2;
	sf::Text menu2[MAX_NUMBER_OF_PLAYERS];
};