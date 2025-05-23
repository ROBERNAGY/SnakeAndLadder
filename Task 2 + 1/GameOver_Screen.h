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

using namespace std;
using namespace sf;

class GameOver_Screen
{
public:

	GameOver_Screen(float width , float height , Font &font);
	~GameOver_Screen();

	//Make it static !!!!!!!!!!!!!!!!!

	void draw(sf::RenderWindow &window);
	void MoveLeft();
	void MoveRight();
	int getItemPressed();

private:
	int selectedItemIndex;
	Text menu[2];
};