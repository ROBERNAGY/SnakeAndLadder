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
#include "Resume.h"

#define MAX_NUMBER_OF_ITEMS_R 3

using namespace std;
using namespace sf;

class Resume
{
public:
	Resume(float width, float height, sf::Font &font);
	~Resume();

	void draw(RenderWindow &window);
	void MoveUp();
	void MoveDown();
	int GetPressedItem();

private:
	int selectedItemIndex;
	Text menu[MAX_NUMBER_OF_ITEMS_R];
};