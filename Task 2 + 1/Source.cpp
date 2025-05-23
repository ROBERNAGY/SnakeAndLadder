#include<SFML\Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <sstream>
#include"Menu.h"
#include"Playersnumber.h"
#include"Nameofplayers.h"
#include "Nameofplayers2.h"
#include "Nameofplayers3.h"
#include "Option.h"
#include "GameOver_Screen.h"
#include "Resume.h"
#include"levels.h"

using namespace std;
using namespace sf;

struct Players
{
	string Name;
	int Square;
	float namePosition_x, namePosition_y, squarePosition_x, squarePosition_y;
	Sprite Piece;
	bool winner = false;
}Player[4];

struct Score
{
	string Name;
	long long winTimes;
	long long loseTimes;
};

//Global Variables.
vector <Score> playerScore;
float SquarePositions[100][3], screenWidth = 1500, screenHeight = 1000, volume = 100.0f;
int PlayerNum, desktopWidth = 1366, desktopHeight = 768, PlayerTurn = -1, selectedMode;
bool callFromResumeScreen = false, closeGameBoard = false, playing = true;;
sf::Sound sound;
sf::Font font, font2;

bool arrangeBySquarePosition(const Players &a, const Players &b);

bool arrangeByNamePosition(const Players &a, const Players &b);

void writeToTempFile();

void HallOfFame(sf::RenderWindow &window);

void addPlayersToVector();

bool compareByNumberOfWinsAndLose(const Score &a, const Score &b);

void sortPlayersByScore();

void readFromFile();

void writeToFile();

void AboutUs(sf::RenderWindow &window);

void rearrangeTheNamesDiplayed();

void Resume_screen();

void Game_Over(string Winner , sf::RenderWindow &window);

void Initialize_SquaresPositions();

void Initialize_SnakesPositions();

int FindTailPosition(int Square);

void Initialize_LaddersPositions();

int FindTopPosition(int Square);

void GameBoard_Screen(sf::RenderWindow &window);

void mainMenu(sf::RenderWindow &window);

void Nameeofplayers3(sf::RenderWindow &window);

void Nameeofplayers2(sf::RenderWindow &window);

void Nameeofplayers(sf::RenderWindow &window);

void playeersnumber(sf::RenderWindow &window);

void option(sf::RenderWindow &window);

void Levels(sf::RenderWindow &window);

int Insane_FindTailPosition(int Square);

void Initialize_SnakesPositions_Insanemode();

//Main Function !!!!!!!!!!!!!

void main()
{
	srand(time(0));

	sf::SoundBuffer soundbuffer;

	if (!soundbuffer.loadFromFile("alanwalkersinmetosleep.wav"))
	{
		cout << "Error .. loading sound";
		system("pause");
	}
	sound.setBuffer(soundbuffer);
	sound.play();
	sound.setLoop(true);

	if (!font.loadFromFile("ferrum.otf"))
	{
		cout << "Error .. loading font";
		system("pause");
	}
	if (!font2.loadFromFile("arial.ttf"))
	{
		cout << "Error .. loading font";
		system("pause");
	}

	sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "SFML works!", Style::None);

	window.setPosition(sf::Vector2i((desktopWidth - screenWidth) / 2, (desktopHeight - screenHeight) / 4)); // to set position of the screen on the desktop

	sf::Texture ptex;
	ptex.loadFromFile("loading 1.jpg");
	sf::Sprite sprite(ptex);

	Clock clock;

	clock.restart();
	while (window.isOpen())
	{
		sf::Event event;
		if (clock.getElapsedTime().asSeconds() > 3.0f)
		{
			mainMenu(window);
		}

		window.clear();
		window.draw(sprite);
		window.display();
	}

	writeToFile();

}

void mainMenu(sf::RenderWindow &window)
{
	Menu menu(window.getSize().x, window.getSize().y, font);

	Initialize_SquaresPositions();

	playerScore.clear();
	readFromFile();
	sortPlayersByScore();

	sf::Vector2f targetSize(screenWidth, screenHeight);

	sf::Texture ptex;
	ptex.loadFromFile("gameScreen.jpg");
	sf::Sprite sprite(ptex);

	sprite.setScale(
		targetSize.x / sprite.getLocalBounds().width,
		targetSize.y / sprite.getLocalBounds().height);

	while (window.isOpen())
	{

		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
					menu.MoveUp();
					break;
				case sf::Keyboard::Down:
					menu.MoveDown();
					break;
				case sf::Keyboard::Return:
					switch (menu.GetPressedItem())
					{
					case 0:
						playeersnumber(window);
						break;
					case 1:
						HallOfFame(window);
						break;
					case 2:
						option(window);
						break;
					case 3:
						AboutUs(window);
						break;
					case 4:
						window.close();
						break;
					}
					break;
				}
				break;
			}
		}
		window.clear();
		window.draw(sprite);
		menu.draw(window);
		window.display();
	}
}

void option(sf::RenderWindow &window)
{
	Option option(window.getSize().x, window.getSize().y , font);

	sf::Vector2f targetSize(screenWidth, screenHeight);

	sf::Texture ptex;
	ptex.loadFromFile("gameScreen.jpg");
	sf::Sprite sprite(ptex);

	sprite.setScale(
		targetSize.x / sprite.getLocalBounds().width,
		targetSize.y / sprite.getLocalBounds().height);


	bool enterkey = false;
	while (window.isOpen())
	{

		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Right:
					if (enterkey == true && option.GetPressedItem() == 0)
					{
						if (volume != 100.0f)
							volume = volume + 5.0f;
						sound.setVolume(volume);
					}
					break;
				case sf::Keyboard::Left:
					if (enterkey == true && option.GetPressedItem() == 0)
					{
						if (volume != 0.0f)
							volume = volume - 5.0f;
						sound.setVolume(volume);
					}
					break;
				case sf::Keyboard::Up:
					if (enterkey == false)
						option.MoveUp();
					break;
				case sf::Keyboard::Down:
					if (enterkey == false)
						option.MoveDown();
					break;
				case sf::Keyboard::Return:
					switch (option.GetPressedItem())
					{
					case 0:
						enterkey = !enterkey;
						break;
					case 1:
						playing = !playing;
						if (playing == true)
						{
							sound.play();
						}
						else if (playing == false)
						{
							sound.pause();
						}
						break;
					case 2:
						if (callFromResumeScreen)
						{
							callFromResumeScreen = false;
							GameBoard_Screen(window);
						}
						else
						{
							mainMenu(window);
						}
						break;
					}
					break;
				}
				break;
			}
		}

		std::ostringstream oss;
		oss << volume;
		std::string str = oss.str();

		sf::Text text1, text2, text3;

		text1.setFont(font);
		text1.setString(str);
		text1.setCharacterSize(50);
		text1.setFillColor(sf::Color::Magenta);
		text1.setStyle(sf::Text::Bold | sf::Text::Underlined);
		text1.setPosition(screenWidth / 2.3f, screenHeight / 2.5f);

		text2.setFont(font);
		text2.setString("On");
		text2.setCharacterSize(50);
		text2.setFillColor(sf::Color::Magenta);
		text2.setPosition(screenWidth / 2.4f, 600);

		text3.setFont(font);
		text3.setString("Off");
		text3.setCharacterSize(50);
		text3.setFillColor(sf::Color::Magenta);
		text3.setPosition(screenWidth / 2.4f, 600);

		window.clear();
		window.draw(sprite);
		option.draw(window);
		window.draw(text1);
		if(playing)
		window.draw(text2);
		else
		window.draw(text3);
		window.display();
	}
}

void Nameeofplayers3(sf::RenderWindow &window)
{
	Nameofplayers3 nameofplayers(window.getSize().x, window.getSize().y , font);

	sf::Vector2f targetSize(screenWidth, screenHeight);

	sf::Texture ptex;
	ptex.loadFromFile("gameScreen.jpg");
	sf::Sprite sprite(ptex);

	sprite.setScale(
		targetSize.x / sprite.getLocalBounds().width,
		targetSize.y / sprite.getLocalBounds().height);;

	sf::String playerInput, playerInput2;
	sf::Text playerText, playerText2 , errorText1, errorText2;
	bool error1 = false, error2 = false;

	playerText.setPosition(screenWidth / 1.5, screenHeight / (5) * 1);
	playerText.setFillColor(sf::Color::Yellow);
	playerText.setFont(font2);
	playerText.setCharacterSize(50);

	playerText2.setPosition(screenWidth / 1.5, screenHeight / (5) * 2);
	playerText2.setFillColor(sf::Color::Yellow);
	playerText2.setFont(font2);
	playerText2.setCharacterSize(50);

	errorText1.setPosition(screenWidth / 1.5, screenHeight / (5) * 1.5);
	errorText1.setFillColor(sf::Color::Magenta);
	errorText1.setFont(font2);
	errorText1.setString("Player name should be at least 3 charcters ...");
	errorText1.setCharacterSize(20);

	errorText2.setPosition(screenWidth / 1.5, screenHeight / (5) * 2.5);
	errorText2.setFillColor(sf::Color::Magenta);
	errorText2.setFont(font2);
	errorText2.setString("Player name should be at least 3 charcters ...");
	errorText2.setCharacterSize(20);

	bool enterkey = false;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
					if (enterkey == false)
						nameofplayers.MoveUp();
					break;
				case sf::Keyboard::Down:
					if (enterkey == false)
						nameofplayers.MoveDown();
					break;
				case sf::Keyboard::Return:
					switch (nameofplayers.GetPressedItem())
					{
					case 0:
						enterkey = !enterkey;
						break;
					case 1:
						enterkey = !enterkey;
						break;
					case 2:
						if (Player[0].Name.size() > 3 && Player[1].Name.size() > 3)
						{
							Levels(window);
						}
						else
						{
							if (!(Player[0].Name.size() > 3))
							{
								error1 = true;
							}
							else
								error1 = false;
							if (!(Player[1].Name.size() > 3))
							{
								error2 = true;
							}
							else
								error2 = false;
						}
							break;
					case 3:
						playeersnumber(window);
						break;
					}
					break;
				}
				break;
			}
			if (enterkey == true)
			{
				if (event.type == sf::Event::TextEntered && nameofplayers.GetPressedItem() == 0)
				{
					if (event.text.unicode < 128 && event.type && sf::Event::KeyPressed && Player[0].Name.size() != 8 && event.text.unicode != 8 && event.text.unicode != 32)
					{
						Player[0].Name += (char)event.text.unicode;
						playerText.setString(Player[0].Name);
					}
					if (event.type == sf::Event::TextEntered) {

						if (event.text.unicode == 8)
							if (Player[0].Name.size() > 0)
								Player[0].Name.erase(Player[0].Name.size() - 1, Player[0].Name.size());
						playerText.setString(Player[0].Name);
						break;
					}
				}
				if (event.type == sf::Event::TextEntered && nameofplayers.GetPressedItem() == 1)
				{
					if (event.text.unicode < 128 && event.type && sf::Event::KeyPressed && Player[1].Name.size() != 8 && event.text.unicode != 8 && event.text.unicode != 32)
					{
						Player[1].Name += (char)event.text.unicode;
						playerText2.setString(Player[1].Name);
					}
					if (event.type == sf::Event::TextEntered) {

						if (event.text.unicode == 8)
							if (Player[1].Name.size() > 0)
								Player[1].Name.erase(Player[1].Name.size() - 1, Player[1].Name.size());
						playerText2.setString(Player[1].Name);
						break;
					}
				}
			}
		}
		window.clear();
		window.draw(sprite);
		nameofplayers.draw(window);
		window.draw(playerText);
		window.draw(playerText2);
		if (error1)
			window.draw(errorText1);
		if (error2)
			window.draw(errorText2);
		window.display();
	}
}

void Nameeofplayers2(sf::RenderWindow &window)
{
	Nameofplayers2 nameofplayers(window.getSize().x, window.getSize().y, font);

	sf::Vector2f targetSize(screenWidth, screenHeight);

	sf::Texture ptex;
	ptex.loadFromFile("gameScreen.jpg");
	sf::Sprite sprite(ptex);

	sprite.setScale(
		targetSize.x / sprite.getLocalBounds().width,
		targetSize.y / sprite.getLocalBounds().height);

	sf::String playerInput, playerInput2, playerInput3;
	sf::Text playerText, playerText2, playerText3 , errorText1 , errorText2 , errorText3;
	bool error1 = false, error2 = false, error3 = false;

	playerText.setPosition(screenWidth / 1.5, screenHeight / (6) * 1);
	playerText.setFillColor(sf::Color::Yellow);
	playerText.setFont(font2);
	playerText.setCharacterSize(50);

	playerText2.setPosition(screenWidth / 1.5, screenHeight / (6) * 2);
	playerText2.setFillColor(sf::Color::Yellow);
	playerText2.setFont(font2);
	playerText2.setCharacterSize(50);

	playerText3.setPosition(screenWidth / 1.5, screenHeight / (6) * 3);
	playerText3.setFillColor(sf::Color::Yellow);
	playerText3.setFont(font2);
	playerText3.setCharacterSize(50);

	errorText1.setPosition(screenWidth / 1.5, screenHeight / (6) * 1.5);
	errorText1.setFillColor(sf::Color::Magenta);
	errorText1.setFont(font2);
	errorText1.setString("Player name should be at least 3 charcters ...");
	errorText1.setCharacterSize(20);

	errorText2.setPosition(screenWidth / 1.5, screenHeight / (6) * 2.5);
	errorText2.setFillColor(sf::Color::Magenta);
	errorText2.setFont(font2);
	errorText2.setString("Player name should be at least 3 charcters ...");
	errorText2.setCharacterSize(20);

	errorText3.setPosition(screenWidth / 1.5, screenHeight / (6) * 3.5);
	errorText3.setFillColor(sf::Color::Magenta);
	errorText3.setFont(font2);
	errorText3.setString("Player name should be at least 3 charcters ...");
	errorText3.setCharacterSize(20);

	bool enterkey = false;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
					if (enterkey == false)
						nameofplayers.MoveUp();
					break;
				case sf::Keyboard::Down:
					if (enterkey == false)
						nameofplayers.MoveDown();
					break;
				case sf::Keyboard::Return:
					switch (nameofplayers.GetPressedItem())
					{
					case 0:
						enterkey = !enterkey;
						break;
					case 1:
						enterkey = !enterkey;
						break;
					case 2:
						enterkey = !enterkey;
						break;
					case 3:
						if (Player[0].Name.size() > 3 && Player[1].Name.size() > 3 && Player[2].Name.size() > 3)
						{
							Levels(window);
						}
						else
						{
							if (!(Player[0].Name.size() > 3))
							{
								error1 = true;
							}
							else
								error1 = false;
							if (!(Player[1].Name.size() > 3))
							{
								error2 = true;
							}
							else
								error2 = false;
							if (!(Player[2].Name.size() > 3))
							{
								error3 = true;
							}
							else
								error3 = false;
						}
						break;
					case 4:
						playeersnumber(window);
						break;
					}
					break;
				}
				break;
			}
			if (enterkey == true)
			{
				if (event.type == sf::Event::TextEntered && nameofplayers.GetPressedItem() == 0)
				{
					if (event.text.unicode < 128 && event.type && sf::Event::KeyPressed && Player[0].Name.size() != 8 && event.text.unicode != 8 && event.text.unicode != 32)
					{
						Player[0].Name += (char)event.text.unicode;
						playerText.setString(Player[0].Name);
					}
					if (event.type == sf::Event::TextEntered) {

						if (event.text.unicode == 8)
							if (Player[0].Name.size() > 0)
								Player[0].Name.erase(Player[0].Name.size() - 1, Player[0].Name.size());
						playerText.setString(Player[0].Name);
						break;
					}
				}
				if (event.type == sf::Event::TextEntered && nameofplayers.GetPressedItem() == 1)
				{
					if (event.text.unicode < 128 && event.type && sf::Event::KeyPressed && Player[1].Name.size() != 8 && event.text.unicode != 8 && event.text.unicode != 32)
					{
						Player[1].Name += (char)event.text.unicode;
						playerText2.setString(Player[1].Name);
					}
					if (event.type == sf::Event::TextEntered) {

						if (event.text.unicode == 8)
							if (Player[1].Name.size() > 0)
								Player[1].Name.erase(Player[1].Name.size() - 1, Player[1].Name.size());
						playerText2.setString(Player[1].Name);
						break;
					}
				}

				if (event.type == sf::Event::TextEntered && nameofplayers.GetPressedItem() == 2)
				{
					if (event.text.unicode < 128 && event.type && sf::Event::KeyPressed && Player[2].Name.size() != 8 && event.text.unicode != 8 && event.text.unicode != 32)
					{
						Player[2].Name += (char)event.text.unicode;
						playerText3.setString(Player[2].Name);
					}
					if (event.type == sf::Event::TextEntered) {

						if (event.text.unicode == 8)
							if (Player[2].Name.size() > 0)
								Player[2].Name.erase(Player[2].Name.size() - 1, Player[2].Name.size());
						playerText3.setString(Player[2].Name);
						break;
					}
				}
			}
		}
		window.clear();
		window.draw(sprite);
		nameofplayers.draw(window);
		window.draw(playerText);
		window.draw(playerText2);
		window.draw(playerText3);
		if (error1)
			window.draw(errorText1);
		if (error2)
			window.draw(errorText2);
		if (error3)
			window.draw(errorText3);
		window.display();
	}
}

void Nameeofplayers(sf::RenderWindow &window)
{
	Nameofplayers nameofplayers(window.getSize().x, window.getSize().y, font);

	sf::Vector2f targetSize(screenWidth, screenHeight);

	sf::Texture ptex;
	ptex.loadFromFile("gameScreen.jpg");
	sf::Sprite sprite(ptex);

	sprite.setScale(
		targetSize.x / sprite.getLocalBounds().width,
		targetSize.y / sprite.getLocalBounds().height);

	string playerInput , playerInput2, playerInput3, playerInput4;
	sf::Text playerText, playerText2, playerText3, playerText4 , errorText1, errorText2 , errorText3, errorText4;
	bool error1 = false, error2 = false, error3 = false, error4 = false;

	playerText.setPosition(screenWidth / 1.5, screenHeight / (7) * 1);
	playerText.setFillColor(sf::Color::Yellow);
	playerText.setFont(font2);
	playerText.setCharacterSize(50);

	playerText2.setPosition(screenWidth / 1.5, screenHeight / (7) * 2);
	playerText2.setFillColor(sf::Color::Yellow);
	playerText2.setFont(font2);
	playerText2.setCharacterSize(50);

	playerText3.setPosition(screenWidth / 1.5, screenHeight / (7) * 3);
	playerText3.setFillColor(sf::Color::Yellow);
	playerText3.setFont(font2);
	playerText3.setCharacterSize(50);

	playerText4.setPosition(screenWidth / 1.5, screenHeight / (7) * 4);
	playerText4.setFillColor(sf::Color::Yellow);
	playerText4.setFont(font2);
	playerText4.setCharacterSize(50);

	errorText1.setPosition(screenWidth / 1.5, screenHeight / (7) * 1.5);
	errorText1.setFillColor(sf::Color::Magenta);
	errorText1.setFont(font2);
	errorText1.setString("Player name should be at least 3 charcters ...");
	errorText1.setCharacterSize(20);

	errorText2.setPosition(screenWidth / 1.5, screenHeight / (7) * 2.5);
	errorText2.setFillColor(sf::Color::Magenta);
	errorText2.setFont(font2);
	errorText2.setString("Player name should be at least 3 charcters ...");
	errorText2.setCharacterSize(20);

	errorText3.setPosition(screenWidth / 1.5, screenHeight / (7) * 3.5);
	errorText3.setFillColor(sf::Color::Magenta);
	errorText3.setFont(font2);
	errorText3.setString("Player name should be at least 3 charcters ...");
	errorText3.setCharacterSize(20);

	errorText4.setPosition(screenWidth / 1.5, screenHeight / (7) * 4.5);
	errorText4.setFillColor(sf::Color::Magenta);
	errorText4.setFont(font2);
	errorText4.setString("Player name should be at least 3 charcters ...");
	errorText4.setCharacterSize(20);

	bool enterkey = false;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
					if (enterkey == false)
						nameofplayers.MoveUp();
					break;
				case sf::Keyboard::Down:
					if (enterkey == false)
						nameofplayers.MoveDown();
					break;
				case sf::Keyboard::Return:
					switch (nameofplayers.GetPressedItem())
					{
					case 0:
						enterkey = !enterkey;
						break;
					case 1:
						enterkey = !enterkey;
						break;
					case 2:
						enterkey = !enterkey;
						break;
					case 3:
						enterkey = !enterkey;
						break;
					case 4:
						if (Player[0].Name.size() > 3 && Player[1].Name.size() > 3 && Player[2].Name.size() > 3 && Player[3].Name.size() > 3)
						{
							Levels(window);
						}
						else
						{
							if (!(Player[0].Name.size() > 3))
							{
								error1 = true;
							}
							else
								error1 = false;
							if (!(Player[1].Name.size() > 3))
							{
								error2 = true;
							}
							else
								error2 = false;
							if (!(Player[2].Name.size() > 3))
							{
								error3 = true;
							}
							else
								error3 = false;
							if (!(Player[3].Name.size() > 3))
							{
								error4 = true;
							}
							else
								error4 = false;
						}
						break;
					case 5:
						playeersnumber(window);
						break;
					}
					break;
				}
				break;
			}
			if (enterkey == true)
			{
				if (event.type == sf::Event::TextEntered && nameofplayers.GetPressedItem() == 0)
				{
					if (event.text.unicode < 128 && event.type && sf::Event::KeyPressed && Player[0].Name.size() != 8 && event.text.unicode != 8 && event.text.unicode != 32)
					{
						Player[0].Name += (char)event.text.unicode;
						playerText.setString(Player[0].Name);
					}
					if (event.type == sf::Event::TextEntered) {

						if (event.text.unicode == 8)
							if (Player[0].Name.size() > 0)
								Player[0].Name.erase(Player[0].Name.size() - 1, Player[0].Name.size());
						playerText.setString(Player[0].Name);
						break;
					}
				}
				if (event.type == sf::Event::TextEntered && nameofplayers.GetPressedItem() == 1)
				{
					if (event.text.unicode < 128 && event.type && sf::Event::KeyPressed && Player[1].Name.size() != 8 && event.text.unicode != 8 && event.text.unicode != 32)
					{
						Player[1].Name += (char)event.text.unicode;
						playerText2.setString(Player[1].Name);
					}
					if (event.type == sf::Event::TextEntered) {

						if (event.text.unicode == 8)
							if (Player[1].Name.size() > 0)
								Player[1].Name.erase(Player[1].Name.size() - 1, Player[1].Name.size());
						playerText2.setString(Player[1].Name);
						break;
					}
				}

				if (event.type == sf::Event::TextEntered && nameofplayers.GetPressedItem() == 2)
				{
					if (event.text.unicode < 128 && event.type && sf::Event::KeyPressed && Player[2].Name.size() != 8 && event.text.unicode != 8 && event.text.unicode != 32)
					{
						Player[2].Name += (char)event.text.unicode;
						playerText3.setString(Player[2].Name);
					}
					if (event.type == sf::Event::TextEntered) {

						if (event.text.unicode == 8)
							if (Player[2].Name.size() > 0)
								Player[2].Name.erase(Player[2].Name.size() - 1, Player[2].Name.size());
						playerText3.setString(Player[2].Name);
						break;
					}
				}
				if (event.type == sf::Event::TextEntered && nameofplayers.GetPressedItem() == 3)
				{
					if (event.text.unicode < 128 && event.type && sf::Event::KeyPressed && Player[3].Name.size() != 8 && event.text.unicode != 8 && event.text.unicode != 32)
					{
						Player[3].Name += (char)event.text.unicode;
						playerText4.setString(Player[3].Name);
					}
					if (event.type == sf::Event::TextEntered) {

						if (event.text.unicode == 8)
							if (Player[3].Name.size() > 0)
								Player[3].Name.erase(Player[3].Name.size() - 1, Player[3].Name.size());
						playerText4.setString(Player[3].Name);
						break;
					}
				}
			}
		}
		window.clear();
		window.draw(sprite);
		nameofplayers.draw(window);
		window.draw(playerText);
		window.draw(playerText2);
		window.draw(playerText3);
		window.draw(playerText4);
		if (error1)
			window.draw(errorText1);
		if (error2)
			window.draw(errorText2);
		if (error3)
			window.draw(errorText3);
		if (error4)
			window.draw(errorText4);
		window.display();
	}
}

void playeersnumber(sf::RenderWindow &window)
{

	Texture Picture[4];

	if (!Picture[0].loadFromFile("1.png"))
	{
		cout << "Pic 1 couldn't be loaded" << endl;
		system("pause");
	}
	if (!Picture[1].loadFromFile("2.png"))
	{
		cout << "Pic 2 couldn't be loaded" << endl;
		system("pause");
	}
	if (!Picture[2].loadFromFile("5.png"))
	{
		cout << "Pic 3 couldn't be loaded" << endl;
		system("pause");
	}
	if (!Picture[3].loadFromFile("7.png"))
	{
		cout << "Pic 4 couldn't be loaded" << endl;
		system("pause");
	}

	sf::Vector2f targetSize(screenWidth, screenHeight);

	sf::Texture ptex;
	ptex.loadFromFile("gameScreen.jpg");
	sf::Sprite sprite(ptex);

	sprite.setScale(
		targetSize.x / sprite.getLocalBounds().width,
		targetSize.y / sprite.getLocalBounds().height);

	Sprite P1(Picture[0]) , P2(Picture[1]) , P3(Picture[2]), P4(Picture[3]);

	Player[0].Piece = P1;
	Player[1].Piece = P2;
	Player[2].Piece = P3;
	Player[3].Piece = P4;

	for (int i = 0; i < 4; i++)
	{
		Player[i].Piece.setPosition(SquarePositions[0][0], SquarePositions[0][1]);
		Player[i].winner = false;
		Player[i].Square = 0;
		Player[i].Name = {};
		Player[i].namePosition_x = 1335;
		Player[i].squarePosition_x = 1400;
	}

	Player[0].namePosition_y = 136;
	Player[1].namePosition_y = 282;
	Player[2].namePosition_y = 440;
	Player[3].namePosition_y = 585;

	Player[0].squarePosition_y = 186;
	Player[1].squarePosition_y = 332;
	Player[2].squarePosition_y = 490;
	Player[3].squarePosition_y = 635;

	Playersnumber PNumber(window.getSize().x, window.getSize().y, font);

	while (window.isOpen())
	{

		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
					PNumber.MoveUp();
					break;
				case sf::Keyboard::Down:
					PNumber.MoveDown();
					break;
				case sf::Keyboard::Return:
					switch (PNumber.GetPressedItem())
					{
					case 0:
						PlayerNum = 1;
						Nameeofplayers3(window);
						break;
					case 1:
						PlayerNum = 2;
						Nameeofplayers2(window);
						break;
					case 2:
						PlayerNum = 3;
						Nameeofplayers(window);
						break;
					case 3:
						mainMenu(window);
						break;
					}
					break;
				}
				break;
			}
		}
		window.clear();
		window.draw(sprite);
		PNumber.draw(window);
		window.display();
	}
}

void Initialize_SquaresPositions()
{
	bool Reversed = false;
	float y = 841, x = 242;

	for (int i = 0; i < 100; i++)
	{
		SquarePositions[i][0] = x;
		SquarePositions[i][1] = y;
		SquarePositions[i][2] = 0;

		if ((i + 1) % 10 == 0)
		{
			y -= 83;
			Reversed = !Reversed;


			if (Reversed == true)
				x += 106;
			else
				x -= 106;
		}

		if (Reversed == false)
			x += 106;
		else if (Reversed == true)
			x -= 106;
	}
}

void Initialize_SnakesPositions()
{
	int Square, savedSquare;
	float snakeNum = -1.0;

	for (int k = 10; k > 0; k--)
	{
		//square rand from 0 to 98 ( 1 to 99 on the game board )

		Square = rand() % 99;

		if (SquarePositions[Square][2] == 0)
		{
			//snake head is -x

			if (k % 2 == 0 && Square > 9)
			{
				SquarePositions[Square][2] = snakeNum;
				savedSquare = Square;
				snakeNum -= 0.5;
			}

			//snake tail is -x.5

			else if (k % 2 != 0 && Square < savedSquare - 9)
			{
				SquarePositions[Square][2] = snakeNum;
				snakeNum -= 0.5;
			}
			else if (k % 2 != 0 && Square > savedSquare + 9)
			{
				SquarePositions[Square][2] = snakeNum;
				swap(SquarePositions[Square][2], SquarePositions[savedSquare][2]);
				snakeNum -= 0.5;
			}


			else
				k++;
		}
		else
			k++;
	}
}

int FindTailPosition(int Square)
{
	bool headFound = false;
	float Tail;
	for (int i = -1; i >= -5; i--)
	{
		if (SquarePositions[Square][2] == i)
		{
			headFound = true;
			Tail = i - 0.5;
			break;
		}
	}
	if (headFound == true)
	{
		for (int i = 0; i < 100; i++)
		{
			if (SquarePositions[i][2] == Tail)
			{
				Square = i;
				break;
			}
		}

		Texture s;
		s.loadFromFile("snake .png");
		Sprite Snake(s);

		RenderWindow window(VideoMode(500, 500), "", Style::None);

		window.setPosition(sf::Vector2i((screenWidth - window.getSize().x) / 1.5, (screenHeight - window.getSize().y) / 2)); // to set position of the screen on the desktop

		sf::Vector2f targetSize(window.getSize().x, window.getSize().y);

		Snake.setScale(
			targetSize.x / Snake.getLocalBounds().width,
			targetSize.y / Snake.getLocalBounds().height);

		while (window.isOpen())
		{
			Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::KeyReleased)
				{
					if(event.key.code != Keyboard::Key::Space)
						window.close();
				}
			}
			window.clear();
			window.draw(Snake);
			window.display();
		}
	}
	return Square;
}

void Initialize_LaddersPositions()
{
	int Square, savedSquare;
	float ladderNum = 1.0;

	for (int k = 10; k > 0; k--)
	{
		Square = rand() % 99 + 1;

		if (SquarePositions[Square][2] == 0)
		{
			//ladder bottom +x

			if (k % 2 == 0)
			{
				SquarePositions[Square][2] = ladderNum;
				savedSquare = Square;
				ladderNum += 0.5;
			}
			//ladder top +x.5

			else if (k % 2 != 0 && Square > savedSquare + 9)
			{
				SquarePositions[Square][2] = ladderNum;
				ladderNum += 0.5;
			}
			else if (k % 2 != 0 && Square < savedSquare - 9)
			{
				SquarePositions[Square][2] = ladderNum;
				swap(SquarePositions[Square][2], SquarePositions[savedSquare][2]);
				ladderNum += 0.5;
			}


			else
				k++;
		}
		else
			k++;
	}
}

int FindTopPosition(int Square)
{
	bool botFound = false;
	float Top;
	for (int i = 1; i <= 5; i++)
	{
		if (SquarePositions[Square][2] == i)
		{
			botFound = true;
			Top = i + 0.5;
			break;
		}
	}

	if (botFound == true)
	{
		for (int i = 0; i < 100; i++)
		{
			if (SquarePositions[i][2] == Top)
			{
				Square = i;
				break;
			}
		}

		Texture l;
		l.loadFromFile("ladder.jpg");
		Sprite Ladder(l);
		Ladder.setPosition(0, 0);

		RenderWindow window(VideoMode(500, 500), "", Style::None);

		window.setPosition(sf::Vector2i((screenWidth - window.getSize().x) / 1.5, (screenHeight - window.getSize().y) / 2)); // to set position of the screen on the desktop

		sf::Vector2f targetSize(window.getSize().x, window.getSize().y);

		Ladder.setScale(
			targetSize.x / Ladder.getLocalBounds().width,
			targetSize.y / Ladder.getLocalBounds().height);

		while (window.isOpen())
		{
			Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::KeyReleased)
				{
					if (event.key.code != Keyboard::Key::Space)
						window.close();
				}
			}
			window.clear();
			window.draw(Ladder);
			window.display();
		}
	}
	return Square;
}

void GameBoard_Screen(sf::RenderWindow &window)
{
	Texture Game_Board1, Game_Board2, Game_Board3;

	if (!Game_Board1.loadFromFile("2 players.png"))
	{
		cout << "GameBoard 1 couldn't be loaded" << endl;
		system("pause");
	}
	if (!Game_Board2.loadFromFile("3 players.png"))
	{
		cout << "GameBoard 2 couldn't be loaded" << endl;
		system("pause");
	}
	if (!Game_Board3.loadFromFile("4 players.png"))
	{
		cout << "GameBoard 3 couldn't be loaded" << endl;
		system("pause");
	}

	Sprite GameBoard1(Game_Board1), GameBoard2(Game_Board2), GameBoard3(Game_Board3);

	Clock clock;
	int count = 0;

	Text Dice, displayPlayerName[4] , displayPlayerPosition[4];
	Dice.setFillColor(Color::Red);
	Dice.setFont(font2);
	Dice.setCharacterSize(25);
	Dice.setPosition(555, 0);
	Dice.setString("Press Space To roll the dice");

	for (int i = 0; i < 4; i++)
	{
		displayPlayerName[i].setFillColor(Color::Cyan);
		displayPlayerName[i].setFont(font2);
		displayPlayerName[i].setCharacterSize(35);
		displayPlayerName[i].setPosition(Player[i].namePosition_x, Player[i].namePosition_y);
		displayPlayerName[i].setString(Player[i].Name);

		string s = to_string(Player[i].Square + 1);

		displayPlayerPosition[i].setFillColor(Color::Cyan);
		displayPlayerPosition[i].setFont(font2);
		displayPlayerPosition[i].setCharacterSize(40);
		displayPlayerPosition[i].setPosition(Player[i].squarePosition_x, Player[i].squarePosition_y);
		displayPlayerPosition[i].setString(s);
	}

	while (window.isOpen())
	{
		Event event;

		while (window.pollEvent(event))
		{
			if (Keyboard::isKeyPressed(Keyboard::Key::Space))
			{
				PlayerTurn++;

				int diceInt = (1 + rand() % 6);

				//to convert from INT to STRING we use this

				string a = to_string(diceInt);

				Dice.setString(a);
				Dice.setCharacterSize(50);
				Dice.setPosition(690, 0);

				//Animation

				clock.restart();
				while (count != diceInt && Player[PlayerTurn].Square != 99)
				{
					if (clock.getElapsedTime().asSeconds() >= 0.6f)
						clock.restart();
					if (clock.getElapsedTime().asSeconds() <= 0.6f && clock.getElapsedTime().asSeconds() >= 0.5f)
					{
						Player[PlayerTurn].Square++;
						Player[PlayerTurn].Piece.setPosition(SquarePositions[Player[PlayerTurn].Square][0], SquarePositions[Player[PlayerTurn].Square][1]);
						count++;
						clock.restart();

						string s = to_string(Player[PlayerTurn].Square + 1);
						displayPlayerPosition[PlayerTurn].setString(s);

						rearrangeTheNamesDiplayed();

						for (int i = 0; i < 4; i++)
						{
							displayPlayerName[i].setPosition(Player[i].namePosition_x, Player[i].namePosition_y);

							displayPlayerPosition[i].setPosition(Player[i].squarePosition_x, Player[i].squarePosition_y);
						}

						window.clear();

						if (PlayerNum == 1)
						{
							window.draw(GameBoard1);

							window.draw(Player[0].Piece);
							window.draw(Player[1].Piece);
						}
						if (PlayerNum == 2)
						{
							window.draw(GameBoard2);

							window.draw(Player[0].Piece);
							window.draw(Player[1].Piece);
							window.draw(Player[2].Piece);
						}
						if (PlayerNum == 3)
						{
							window.draw(GameBoard3);

							window.draw(Player[0].Piece);
							window.draw(Player[1].Piece);
							window.draw(Player[2].Piece);
							window.draw(Player[3].Piece);
						}

						for (int i = 0; i <= PlayerNum; i++)
						{
							window.draw(displayPlayerName[i]);
							window.draw(displayPlayerPosition[i]);
						}

						window.draw(Dice);

						window.display();

					}
				}

				count = 0;

				if (SquarePositions[Player[PlayerTurn].Square][2] != 0)
				{
					if (SquarePositions[Player[PlayerTurn].Square][2] > 0)
					{
						Player[PlayerTurn].Square = FindTopPosition(Player[PlayerTurn].Square);
						Player[PlayerTurn].Piece.setPosition(SquarePositions[Player[PlayerTurn].Square][0], SquarePositions[Player[PlayerTurn].Square][1]);
					}
					if (SquarePositions[Player[PlayerTurn].Square][2] < 0)
					{
						if (selectedMode == 0)
							Player[PlayerTurn].Square = FindTailPosition(Player[PlayerTurn].Square);
						else if (selectedMode == 1)
							Player[PlayerTurn].Square = Insane_FindTailPosition(Player[PlayerTurn].Square);
						Player[PlayerTurn].Piece.setPosition(SquarePositions[Player[PlayerTurn].Square][0], SquarePositions[Player[PlayerTurn].Square][1]);
					}

					string s = to_string(Player[PlayerTurn].Square + 1);
					displayPlayerPosition[PlayerTurn].setString(s);

					rearrangeTheNamesDiplayed();

					for (int i = 0; i < 4; i++)
					{
						displayPlayerName[i].setPosition(Player[i].namePosition_x, Player[i].namePosition_y);

						displayPlayerPosition[i].setPosition(Player[i].squarePosition_x, Player[i].squarePosition_y);
					}

					window.clear();

					if (PlayerNum == 1)
					{
						window.draw(GameBoard1);

						window.draw(Player[0].Piece);
						window.draw(Player[1].Piece);
					}
					if (PlayerNum == 2)
					{
						window.draw(GameBoard2);

						window.draw(Player[0].Piece);
						window.draw(Player[1].Piece);
						window.draw(Player[2].Piece);
					}
					if (PlayerNum == 3)
					{
						window.draw(GameBoard3);

						window.draw(Player[0].Piece);
						window.draw(Player[1].Piece);
						window.draw(Player[2].Piece);
						window.draw(Player[3].Piece);
					}

					for (int i = 0; i <= PlayerNum; i++)
					{
						window.draw(displayPlayerName[i]);
						window.draw(displayPlayerPosition[i]);
					}

					window.draw(Dice);

					window.display();
				}


				if (PlayerNum == PlayerTurn)
				{
					PlayerTurn = -1;
				}
			}

			if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
			{
				Resume_screen();
			}
		}

		if (closeGameBoard)
		{
			closeGameBoard = false;
			mainMenu(window);
		}

		if (callFromResumeScreen)
		{
			option(window);
		}

		//Game Over!!!!!!!!!!!!!!!!!
		for (int i = 0; i < 4; i++)
		{
			if (Player[i].Square == 99)
			{
				Player[i].winner = true;

				string Winner;
						
				Winner = Player[i].Name;

				Game_Over(Winner, window);
			}
		}

		rearrangeTheNamesDiplayed();

		window.clear();

		if (PlayerNum == 1)
		{
			window.draw(GameBoard1);

			window.draw(Player[0].Piece);
			window.draw(Player[1].Piece);
		}
		if (PlayerNum == 2)
		{
			window.draw(GameBoard2);

			window.draw(Player[0].Piece);
			window.draw(Player[1].Piece);
			window.draw(Player[2].Piece);
		}
		if (PlayerNum == 3)
		{
			window.draw(GameBoard3);

			window.draw(Player[0].Piece);
			window.draw(Player[1].Piece);
			window.draw(Player[2].Piece);
			window.draw(Player[3].Piece);
		}

		for (int i = 0; i <= PlayerNum; i++)
		{
			window.draw(displayPlayerName[i]);
			window.draw(displayPlayerPosition[i]);
		}

		window.draw(Dice);

		window.display();
	}
}

void Game_Over(string Winner, sf::RenderWindow &window)
{
	writeToTempFile();
	addPlayersToVector();
	writeToFile();

	GameOver_Screen GameOver(screenWidth, screenHeight, font);

	Text text1, text2;

	sf::Vector2f targetSize(screenWidth, screenHeight);

	sf::Texture ptex;
	ptex.loadFromFile("gameScreen.jpg");
	sf::Sprite sprite(ptex);

	sprite.setScale(
		targetSize.x / sprite.getLocalBounds().width,
		targetSize.y / sprite.getLocalBounds().height);

	text1.setFont(font);
	text1.setFillColor(Color::Magenta);
	text1.setString(Winner);
	text1.setCharacterSize(75);
	text1.setPosition(Vector2f(screenWidth / 2.4, screenHeight / 4 * 1));

	text2.setFont(font);
	text2.setFillColor(Color::Green);
	text2.setString("escaped successfully.");
	text2.setCharacterSize(75);
	text2.setPosition(Vector2f(screenWidth / 3, screenHeight / 4 * 2));

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::KeyReleased)
			{
				if (event.key.code == sf::Keyboard::Left)
				{
					GameOver.MoveLeft();
				}
				if (event.key.code == sf::Keyboard::Right)
				{
					GameOver.MoveRight();
				}
				if (event.key.code == sf::Keyboard::Enter)
				{
					if (GameOver.getItemPressed() == 0)
					{
						mainMenu(window);
					}

					if (GameOver.getItemPressed() == 1)
					{
						window.close();
					}
				}
			}
		}

		window.clear();
		window.draw(sprite);
		GameOver.draw(window);
		window.draw(text1);
		window.draw(text2);
		window.display();
	}
}

void Resume_screen()
{
	RenderWindow window1(VideoMode(600, screenHeight), "", Style::None);

	window1.setPosition(sf::Vector2i((desktopWidth - 600) / 2, (desktopHeight - screenHeight) / 4)); // to set position of the screen on the desktop

	Resume resume(window1.getSize().x, window1.getSize().y, font);

	Texture background;
	if (!background.loadFromFile("pauseScreen.png"))
	{
		cout << "error .. line 1423";
		system("pause");
	}

	Sprite BacKGrounD(background);

	sf::Vector2f targetSize(window1.getSize().x, window1.getSize().y);

	BacKGrounD.setScale(
		targetSize.x / BacKGrounD.getLocalBounds().width,
		targetSize.y / BacKGrounD.getLocalBounds().height);

	while (window1.isOpen())
	{
		sf::Event event;
		while (window1.pollEvent(event))
		{
			if (event.type == sf::Event::KeyReleased)
			{
				if (event.key.code == sf::Keyboard::Up)
				{
				resume.MoveUp();
				}
				if (event.key.code == sf::Keyboard::Down)
				{
					resume.MoveDown();
				}
				if (event.key.code == sf::Keyboard::Enter)
				{
					if (resume.GetPressedItem() == 0)
					{
						window1.close();
					}
					if (resume.GetPressedItem() == 1)
					{
						window1.close();
						callFromResumeScreen = true;
					}
					if (resume.GetPressedItem() == 2)
					{
						closeGameBoard = true;
						window1.close();
					}
				}
			}
		}
		window1.clear();
		window1.draw(BacKGrounD);
		resume.draw(window1);
		window1.display();
	}
}

void rearrangeTheNamesDiplayed()
{
	if (Player[0].Square < Player[1].Square && Player[0].namePosition_y < Player[1].namePosition_y)
	{
		swap(Player[0].namePosition_y, Player[1].namePosition_y);
		swap(Player[0].squarePosition_y, Player[1].squarePosition_y);
	}
	else if (Player[0].Square > Player[1].Square && Player[0].namePosition_y > Player[1].namePosition_y)
	{
		swap(Player[0].namePosition_y, Player[1].namePosition_y);
		swap(Player[0].squarePosition_y, Player[1].squarePosition_y);
	}
	if (Player[0].Square < Player[2].Square && Player[0].namePosition_y < Player[2].namePosition_y)
	{
		swap(Player[0].namePosition_y, Player[2].namePosition_y);
		swap(Player[0].squarePosition_y, Player[2].squarePosition_y);
	}
	else if (Player[0].Square > Player[2].Square && Player[0].namePosition_y > Player[2].namePosition_y)
	{
		swap(Player[0].namePosition_y, Player[2].namePosition_y);
		swap(Player[0].squarePosition_y, Player[2].squarePosition_y);
	}
	if (Player[0].Square < Player[3].Square && Player[0].namePosition_y < Player[3].namePosition_y)
	{
		swap(Player[0].namePosition_y, Player[3].namePosition_y);
		swap(Player[0].squarePosition_y, Player[3].squarePosition_y);
	}
	else if (Player[0].Square > Player[3].Square && Player[0].namePosition_y > Player[3].namePosition_y)
	{
		swap(Player[0].namePosition_y, Player[3].namePosition_y);
		swap(Player[0].squarePosition_y, Player[3].squarePosition_y);
	}


	if (Player[1].Square < Player[2].Square && Player[1].namePosition_y < Player[2].namePosition_y)
	{
		swap(Player[1].namePosition_y, Player[2].namePosition_y);
		swap(Player[1].squarePosition_y, Player[2].squarePosition_y);
	}
	else if (Player[1].Square > Player[2].Square && Player[1].namePosition_y > Player[2].namePosition_y)
	{
		swap(Player[1].namePosition_y, Player[2].namePosition_y);
		swap(Player[1].squarePosition_y, Player[2].squarePosition_y);
	}
	if (Player[1].Square < Player[3].Square && Player[1].namePosition_y < Player[3].namePosition_y)
	{
		swap(Player[1].namePosition_y, Player[3].namePosition_y);
		swap(Player[1].squarePosition_y, Player[3].squarePosition_y);
	}
	else if (Player[1].Square > Player[3].Square && Player[1].namePosition_y > Player[3].namePosition_y)
	{
		swap(Player[1].namePosition_y, Player[3].namePosition_y);
		swap(Player[1].squarePosition_y, Player[3].squarePosition_y);
	}


	if (Player[2].Square < Player[3].Square && Player[2].namePosition_y < Player[3].namePosition_y)
	{
		swap(Player[2].namePosition_y, Player[3].namePosition_y);
		swap(Player[2].squarePosition_y, Player[3].squarePosition_y);
	}
	else if (Player[2].Square > Player[3].Square && Player[2].namePosition_y > Player[3].namePosition_y)
	{
		swap(Player[2].namePosition_y, Player[3].namePosition_y);
		swap(Player[2].squarePosition_y, Player[3].squarePosition_y);
	}

	/*sort(begin(Player)->namePosition_y, end(Player)->namePosition_y, arrangeByNamePosition);
	sort(begin(Player)->squarePosition_y, end(Player)->squarePosition_y, arrangeBySquarePosition);*/
}

void AboutUs(sf::RenderWindow &window)
{
	sf::Texture ptex;
	ptex.loadFromFile("knights 22.jpg");
	sf::Sprite sprite(ptex);

	sf::Vector2f targetSize(window.getSize().x, window.getSize().y);

	sprite.setScale(
		targetSize.x / sprite.getLocalBounds().width,
		targetSize.y / sprite.getLocalBounds().height);


	Clock clock;

	clock.restart();
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (clock.getElapsedTime().asSeconds() > 10.0f || event.type == sf::Event::KeyReleased)
			{
				mainMenu(window);
			}
		}

		window.clear();
		window.draw(sprite);
		window.display();
	}
}

void readFromFile()
{
	ifstream readFromFile("Hall Of Fame.txt");

	Score temp;

	while (readFromFile >> temp.Name >> temp.winTimes >> temp.loseTimes)
	{
		playerScore.push_back(temp);
	}

	readFromFile.close();
}

void addPlayersToVector()
 {
	ifstream tempFile("temp.txt");

	vector <Score> tempVector;

	Score tempScore;

	while (tempFile >> tempScore.Name >> tempScore.winTimes >> tempScore.loseTimes)
	{
		tempVector.push_back(tempScore);
	}

	for (int j = 0; j < tempVector.size(); j++)
	{
		bool found = false;
		for (int i = 0; i < playerScore.size(); i++)
		{
			if (playerScore[i].Name == tempVector[j].Name)
				{
				found = true;
				playerScore[i].winTimes += tempVector[j].winTimes;
				playerScore[i].loseTimes += tempVector[j].loseTimes;
				break;
			}
		}
		if(!found)
		{
			playerScore.push_back(tempVector[j]);
		}
	}

	tempFile.close();

	remove("temp.txt");
}

void writeToFile()
{
	ofstream writeToFile("Hall Of Fame.txt");

	int count = 0;

	while (count != playerScore.size())
	{
		writeToFile << playerScore[count].Name << " " << playerScore[count].winTimes << " " << playerScore[count].loseTimes << endl;
		count++;
	}

	writeToFile.close();

}

bool compareByNumberOfWinsAndLose(const Score &a, const Score &b)
{
	//if not equal return the higher
	if (a.winTimes != b.winTimes)
		return a.winTimes > b.winTimes;
	else if (a.loseTimes != b.loseTimes)
		return a.loseTimes < b.loseTimes;
	else
		return a.Name < b.Name;
}

void sortPlayersByScore()
{
	sort(playerScore.begin(), playerScore.end(), compareByNumberOfWinsAndLose);
}

void HallOfFame(sf::RenderWindow &window)
{
	Text topTenPlayerNames[10], topTenPlayerWins[10], topTenPlayerLoses[10] , Header[3];

	Header[0].setFont(font);
	Header[0].setCharacterSize(55);
	Header[0].setFillColor(Color::Red);
	Header[0].setPosition(screenWidth / 8.2, screenHeight / 14 * 1);
	Header[0].setString("Player Name");

	Header[1].setFont(font);
	Header[1].setCharacterSize(55);
	Header[1].setFillColor(Color::Red);
	Header[1].setPosition(screenWidth / 2.7, screenHeight / 14 * 1);
	Header[1].setString("Succeded escapes");

	Header[2].setFont(font);
	Header[2].setCharacterSize(55);
	Header[2].setFillColor(Color::Red);
	Header[2].setPosition(screenWidth / 1.5, screenHeight / 14 * 1);
	Header[2].setString("Failed escapes");

	for (int i = 0; i < 10; i++)
	{
		topTenPlayerNames[i].setFont(font2);
		topTenPlayerNames[i].setCharacterSize(50);
		topTenPlayerNames[i].setFillColor(Color::Cyan);
		topTenPlayerNames[i].setPosition(screenWidth / 8.2 , screenHeight / 14 * (i + 3));
		topTenPlayerNames[i].setString(playerScore[i].Name);

		string win = to_string(playerScore[i].winTimes);
		string lose = to_string(playerScore[i].loseTimes);

		topTenPlayerWins[i].setFont(font2);
		topTenPlayerWins[i].setCharacterSize(50);
		topTenPlayerWins[i].setFillColor(Color::Cyan);
		topTenPlayerWins[i].setPosition(screenWidth / 2.7, screenHeight / 14 * (i + 3));
		topTenPlayerWins[i].setString(win);

		topTenPlayerLoses[i].setFont(font2);
		topTenPlayerLoses[i].setCharacterSize(50);
		topTenPlayerLoses[i].setFillColor(Color::Cyan);
		topTenPlayerLoses[i].setPosition(screenWidth / 1.5, screenHeight / 14 * (i + 3));
		topTenPlayerLoses[i].setString(lose);
	}

	sf::Vector2f targetSize(screenWidth, screenHeight);

	sf::Texture ptex;
	ptex.loadFromFile("gameScreen.jpg");
	sf::Sprite sprite(ptex);

	sprite.setScale(
		targetSize.x / sprite.getLocalBounds().width,
		targetSize.y / sprite.getLocalBounds().height);

	while (window.isOpen())
	{
		Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::KeyReleased)
			{
				if (event.key.code == sf::Keyboard::Enter)
				{
					mainMenu(window);
				}
			}
		}

		window.clear();

		window.draw(sprite);

		for (int i = 0; i < 3; i++)
		{
			window.draw(Header[i]);
		}
		for (int i = 0; i < 10; i++)
		{
			window.draw(topTenPlayerNames[i]);
			window.draw(topTenPlayerWins[i]);
			window.draw(topTenPlayerLoses[i]);
		}
		window.display();
	}
}

void Initialize_SnakesPositions_Insanemode()
{
	int Square, savedSquare;
	float snakeNum = -1.0;

	for (int k = 20; k > 0; k--)
	{
		//square rand from 0 to 98 ( 1 to 99 on the game board )

		Square = rand() % 99;

		if (SquarePositions[Square][2] == 0)
		{
			//snake head is -x

			if (k % 2 == 0 && Square > 9 && Square != 99)
			{
				SquarePositions[Square][2] = snakeNum;
				savedSquare = Square;
				snakeNum -= 0.5;
			}

			//snake tail is -x.5

			else if (k % 2 != 0 && Square < savedSquare - 9)
			{
				SquarePositions[Square][2] = snakeNum;
				snakeNum -= 0.5;
			}
			else if (k % 2 != 0 && Square > savedSquare + 9)
			{
				SquarePositions[Square][2] = snakeNum;
				swap(SquarePositions[Square][2], SquarePositions[savedSquare][2]);
				snakeNum -= 0.5;
			}


			else
				k++;
		}
		else
			k++;
	}
}

int Insane_FindTailPosition(int Square)
{
	bool headFound = false;
	float Tail;
	for (int i = -1; i >= -10; i--)
	{
		if (SquarePositions[Square][2] == i)
		{
			headFound = true;
			Tail = i - 0.5;
			break;
		}
	}
	if (headFound == true)
	{
		for (int i = 0; i < 100; i++)
		{
			if (SquarePositions[i][2] == Tail)
			{
				Square = i;
				break;
			}
		}

		Texture s;
		s.loadFromFile("snake .png");
		Sprite Snake(s);

		RenderWindow window(VideoMode(500, 500), "", Style::None);

		window.setPosition(sf::Vector2i((screenWidth - window.getSize().x) / 1.5, (screenHeight - window.getSize().y) / 2)); // to set position of the screen on the desktop

		sf::Vector2f targetSize(window.getSize().x, window.getSize().y);

		Snake.setScale(
			targetSize.x / Snake.getLocalBounds().width,
			targetSize.y / Snake.getLocalBounds().height);

		while (window.isOpen())
		{
			Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::KeyReleased)
				{
					if (event.key.code != Keyboard::Key::Space)
						window.close();
				}
			}
			window.clear();
			window.draw(Snake);
			window.display();
		}
	}
	return Square;
}

void Levels(sf::RenderWindow &window)
{
	levels levels(window.getSize().x, window.getSize().y, font);

	sf::Vector2f targetSize(screenWidth, screenHeight);

	sf::Texture ptex;
	ptex.loadFromFile("gameScreen.jpg");
	sf::Sprite sprite(ptex);

	sprite.setScale(
		targetSize.x / sprite.getLocalBounds().width,
		targetSize.y / sprite.getLocalBounds().height);


	while (window.isOpen())
	{

		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
					levels.MoveUp();
					break;
				case sf::Keyboard::Down:
					levels.MoveDown();
					break;
				case sf::Keyboard::Return:
					switch (levels.GetPressedItem())
					{
					case 0:
						selectedMode = 0;
						Initialize_SquaresPositions();
						Initialize_LaddersPositions();
						Initialize_SnakesPositions();
						GameBoard_Screen(window);
						break;
					case 1:
						selectedMode = 1;
						Initialize_SquaresPositions();
						Initialize_LaddersPositions();
						Initialize_SnakesPositions_Insanemode();
						GameBoard_Screen(window);
						break;
					case 2:
						if (PlayerNum == 1)
						{
							Nameeofplayers3(window);
						}
						else if (PlayerNum == 2)
						{
							Nameeofplayers2(window);
						}
						else if (PlayerNum == 3)
						{
							Nameeofplayers2(window);
						}
						break;
					}
					break;
				}
				break;
			}
		}
		window.clear();
		window.draw(sprite);
		levels.draw(window);
		window.display();
	}
}

void writeToTempFile()
{
	ofstream temp("temp.txt");
	
	for (int i = 0; i <= PlayerNum; i++)
	{
		if (Player[i].winner == true)
			temp << Player[i].Name << " " << 1 << " " << 0 << endl;
		else
			temp << Player[i].Name << " " << 0 << " " << 1 << endl;
	}

	temp.close();
}

bool arrangeBySquarePosition(const Players &a , const Players &b)
{
	//if not equal return the higher
	if (a.Square >= b.Square)
		return a.squarePosition_y < b.squarePosition_y;
	else if (a.Square < b.Square)
		return a.squarePosition_y < b.squarePosition_y;
}

bool arrangeByNamePosition(const Players &a, const Players &b)
{
	if (a.Square >= b.Square)
		return a.namePosition_y < b.namePosition_y;
	else if (a.Square < b.Square)
		return a.namePosition_y < b.namePosition_y;
}