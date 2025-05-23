#include <SFML/Graphics.hpp>
#define MAX_NUMBER_OF_ITEMS_N2 5
class Nameofplayers2
{
public:
	Nameofplayers2(float width, float height, sf::Font &font3);
	~Nameofplayers2();
	void draw(sf::RenderWindow &window);
	void MoveUp();
	void MoveDown();
	int GetPressedItem() { return selectedItemIndex3; }
private:
	int selectedItemIndex3;
	sf::Text menu3[MAX_NUMBER_OF_ITEMS_N2];
};