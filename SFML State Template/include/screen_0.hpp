// SFML 2.0 - Manage Different Screens In A Game  *** Screen_0.hpp ***

/* screen_0.hpp contains the object definition and its code. "Run" is like the
main loop you can have in a simple SFML application. The constructor defines
the first value of private members which are finally more like static
variables in our case. This permits to have a fade presentation at first
loading, since the menu will appear directly. Once background is shown, we
use two string to make a menu in which you can navigate with direction's key.
Choosing "Play" will go to the game, "Exit" will exit the application by
returning -1 to the main function :
*/

#pragma once;

#include <iostream>
#include "cScreen.hpp"

class screen_0 : public cScreen
{
private:
	int alpha_max;
	int alpha_div;
	bool playing;
public:
	screen_0(void);
	virtual int Run(sf::RenderWindow &App);
};

screen_0::screen_0(void)
{
	alpha_max = 3 * 255;
	alpha_div = 3;
	playing = false;
}

int screen_0::Run(sf::RenderWindow &App)
{
	sf::Event Event;
	bool Running = true;
	//sf::Texture Image;
	//sf::Sprite Sprite;
	int alpha = 0;
	sf::Font Font;
	sf::Text Menu1;
	sf::Text Menu2;
	sf::Text Menu3;
	int menu = 0;

	//if (!Image.loadFromFile("presentation.png"))
	//{
	//	std::cerr << "Error loading presentation.png" << std::endl;
	//	return (-1);
	//}
	//Sprite.setTexture(Image);
	//Sprite.setColor(sf::Color(255, 255, 255, alpha));
	if (!Font.loadFromFile("assets/fonts/arialbd.ttf"))
	{
		std::cerr << "Error loading font" << std::endl;
		return (-1);
	}
	Menu1.setFont(Font);
	Menu1.setCharacterSize(20);
	Menu1.setString("Play");
	Menu1.setPosition(280.0, 160.0);
	Menu2.setFont(Font);
	Menu2.setCharacterSize(20);
	Menu2.setString("Exit");
	Menu2.setPosition(280.0, 220.0);
	Menu3.setFont(Font);
	Menu3.setCharacterSize(20);
	Menu3.setString("Continue");
	Menu3.setPosition(280.0, 160.0);

	//Clearing screen
	App.clear();

	if (playing)
	{
		alpha = alpha_max;
	}

	while (Running)
	{
		//Verifying events
		while (App.pollEvent(Event))
		{
			// Window closed
			if (Event.type == sf::Event::Closed)
			{
				return (-1);
			}
			//Key pressed
			if (Event.type == sf::Event::KeyPressed)
			{
				switch (Event.key.code)
				{
				case sf::Keyboard::Up:
					menu = 0;
					break;
				case sf::Keyboard::Down:
					menu = 1;
					break;
				case sf::Keyboard::Return:
					if (menu == 0)
					{
						//Let's get play !
						playing = true;
						return (1);
					}
					else
					{
						//Let's get work...
						return (-1);
					}
					break;
				default:
					break;
				}
			}
		}
		//When getting at alpha_max, we stop modifying the sprite
		if (alpha<alpha_max)
		{
			alpha++;
		}
		//Sprite.setColor(sf::Color(255, 255, 255, alpha / alpha_div));
		if (menu == 0)
		{
			Menu1.setColor(sf::Color(255, 0, 0, 255));
			Menu2.setColor(sf::Color(255, 255, 255, 255));
			Menu3.setColor(sf::Color(255, 0, 0, 255));
		}
		else
		{
			Menu1.setColor(sf::Color(255, 255, 255, 255));
			Menu2.setColor(sf::Color(255, 0, 0, 255));
			Menu3.setColor(sf::Color(255, 255, 255, 255));
		}

		//Drawing
		//App.draw(Sprite);
		if (alpha == alpha_max)
		{
			if (playing)
			{
				App.draw(Menu3);
			}
			else
			{
				App.draw(Menu1);
			}
			App.draw(Menu2);
		}
		App.display();
	}

	//Never reaching this point normally, but just in case, exit the application
	return (-1);
}