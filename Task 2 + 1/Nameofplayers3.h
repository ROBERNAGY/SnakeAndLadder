#pragma once
#include <SFML/Graphics.hpp>
#define MAX_NUMBER_OF_ITEMS_N3 4

class Nameofplayers3
{
public:
	Nameofplayers3(float width, float height, sf::Font &font3);
	~Nameofplayers3();
	void draw(sf::RenderWindow &window);
	void MoveUp();
	void MoveDown();
	int GetPressedItem() { return selectedItemIndex3; }
private:
	int selectedItemIndex3;
	sf::Text menu3[MAX_NUMBER_OF_ITEMS_N3];
};