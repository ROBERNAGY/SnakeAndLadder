#pragma once
#include <SFML/Graphics.hpp>
#define MAX_NUMBER_OF_ITEMS_M 5
class Menu
{
public:
	Menu(float width , float height, sf::Font &font);
	~Menu();
	
	void draw(sf::RenderWindow &window);
	void MoveUp();
	void MoveDown();
	int GetPressedItem() { return selectedItemIndex; }
	private:
		int selectedItemIndex;
		sf:: Text menu[MAX_NUMBER_OF_ITEMS_M];
};