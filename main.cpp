#include <SFML/Graphics.hpp>

int main()
{
	// Create a video mode object and set the screen resolution.
	sf::VideoMode vm(1920, 1080);

	// Create a window object and give it the video mode, a title
	// and a style parameter
	sf::RenderWindow window(vm, "Timber!!!", sf::Style::Fullscreen);

	// Primary game loop
	while (window.isOpen())
	{
		/*
		****************************************************
		* Handle the player's input
		****************************************************
		*/
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			window.close();
		}

		/*
		****************************************************
		* Update the scene
		****************************************************
		*/

		/*
		****************************************************
		* Draw the scene
		****************************************************
		*/

		// Clear everything from the last frame
		window.clear();

		// Draw the newly updated scene here

		// Show the updated scene
		window.display();
	}

	return 0;
}