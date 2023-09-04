#include <SFML/Graphics.hpp>

int main()
{
	// Create a video mode object and set the screen resolution.
	sf::VideoMode vm(1920, 1080);

	// Create a window object and give it the video mode, a title
	// and a style parameter
	sf::RenderWindow window(vm, "Timber!!!", sf::Style::Fullscreen);

	/*
	***************************************************************************
	* Textures
	***************************************************************************
	*/

	// Background /////////////////////////////////////////////////////////////
	sf::Texture textureBackground; //..........................................Create a texture object to hold a graphic on the GPU in memory
	textureBackground.loadFromFile("graphics/background.png"); //..............Load a graphic into the texture

	// Tree ///////////////////////////////////////////////////////////////////
	sf::Texture textureTree;
	textureTree.loadFromFile("graphics/tree.png");

	// Bee ////////////////////////////////////////////////////////////////////
	sf::Texture textureBee;
	textureBee.loadFromFile("graphics/bee.png");

	// Clouds /////////////////////////////////////////////////////////////////
	sf::Texture textureCloud;
	textureCloud.loadFromFile("graphics/cloud.png");

	/*
	***************************************************************************
	* Sprites
	***************************************************************************
	*/

	// Background /////////////////////////////////////////////////////////////
	sf::Sprite spriteBackground; //............................................Create a sprite
	spriteBackground.setTexture(textureBackground); //.........................Attach the texture to the sprite
	spriteBackground.setPosition(0, 0);	//.....................................Set the spriteBackground to cover the screen

	// Tree ///////////////////////////////////////////////////////////////////
	sf::Sprite spriteTree;
	spriteTree.setTexture(textureTree);
	spriteTree.setPosition(810, 0);

	// Bee ////////////////////////////////////////////////////////////////////
	sf::Sprite spriteBee;
	spriteBee.setTexture(textureBee);
	spriteBee.setPosition(2000, 800);

	// Clouds /////////////////////////////////////////////////////////////////
	//
	// There will be 3 clouds instantiated from one texture; this is allowed
	// because we will be using the exact same cloud for each sprite; if they
	// were different clouds, we would need a unique Texture for each cloud
	sf::Sprite spriteCloud1;
	sf::Sprite spriteCloud2;
	sf::Sprite spriteCloud3;

	spriteCloud1.setTexture(textureCloud);
	spriteCloud2.setTexture(textureCloud);
	spriteCloud3.setTexture(textureCloud);

	spriteCloud1.setPosition(-700, 0);
	spriteCloud2.setPosition(-700, 250);
	spriteCloud3.setPosition(-700, 500);

	/*
	***************************************************************************
	* Variables for game state
	***************************************************************************
	*/

	// Timing /////////////////////////////////////////////////////////////////
	sf::Clock clock;

	bool paused = true;

	// Bee ////////////////////////////////////////////////////////////////////

	// Is the bee currently moving?
	bool beeActive = false;

	// How fast is the bee (in pixels per second)?
	float beeSpeed = 0.0f;

	int beeHeightOccillationCounter = 0;
	int beeHeightOccilationTrigger;
	bool beeGoUp = true;

	// Clouds /////////////////////////////////////////////////////////////////

	// Are the clouds currently visible on screen?
	bool cloud1Active = false;
	bool cloud2Active = false;
	bool cloud3Active = false;

	// How fast is each cloud (in pixels per second)?
	float cloud1Speed = 0.0f;
	float cloud2Speed = 0.0f;
	float cloud3Speed = 0.0f;

	/*
	***************************************************************************
	* Game loop
	***************************************************************************
	*/
	while (window.isOpen())
	{
		/*
		***********************************************************************
		* Handle the player's input
		***********************************************************************
		*/

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			window.close();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		{
			paused = !paused;
		}

		if (!paused)
		{
			/*
			***********************************************************************
			* Update the scene
			***********************************************************************
			*/

			sf::Time dt = clock.restart();

			// Bee Animation //////////////////////////////////////////////////////

			// Set up Bee animation on first execution of game loop
			if (!beeActive)
			{
				// Set Bee speed
				srand((int)time(0)); //............................................Seed random number generator with current system time
				beeSpeed = (rand() % 200) + 200;

				// Set Bee's origin for y-axis
				srand((int)time(0) * 10);
				float height = (rand() % 500) + 500;
				spriteBee.setPosition(2000, height); //............................The bee starts off the right-hand side of the screen

				// Set Bee Occillation Trigger
				srand((int)time(0) * 10);
				beeHeightOccilationTrigger = rand() % (vm.width + 1);

				beeActive = true;
			}
			else // After first game loop, make the bee move
			{
				// Bees always fly left
				float beeNewXCoordinate = spriteBee.getPosition().x - (beeSpeed * dt.asSeconds());


				// Make the bee oscillate up and down at random
				float beeNewYCoordinate;
				if (beeHeightOccillationCounter % beeHeightOccilationTrigger == 0)
				{
					beeGoUp = !beeGoUp;
				}
				if (beeGoUp)
				{
					beeNewYCoordinate = spriteBee.getPosition().y + (0.5 * beeSpeed * dt.asSeconds());

					if (beeNewYCoordinate > 1000)
					{
						beeNewYCoordinate = 1000.0f;
					}
				}
				else
				{
					beeNewYCoordinate = spriteBee.getPosition().y - (0.5 * beeSpeed * dt.asSeconds());
					if (beeNewYCoordinate < 500)
					{
						beeNewYCoordinate = 500.0f;
					}
				}
				beeHeightOccillationCounter++;

				spriteBee.setPosition(beeNewXCoordinate, beeNewYCoordinate);

				// Has the bee reached the left-hand or upper edge of the screen?
				if (spriteBee.getPosition().x < -100)
				{
					// Set it up to appear as a 'new' bee in the next frame
					beeActive = false;
					beeHeightOccillationCounter = 0;
				}
			}

			// Cloud Animation ////////////////////////////////////////////////////

			if (!cloud1Active)
			{
				srand((int)time(0) * 10); //.......................................Note that we use a different factor to ensure that the
				cloud1Speed = (rand() % 200);                                   //.seed values for each speed and height is different.
				//.If this had not been done, the clouds would overlap.
				srand((int)time(0) * 10);
				float height = (rand() % 150);
				spriteCloud1.setPosition(-200, height);

				cloud1Active = true;
			}
			else
			{
				spriteCloud1.setPosition(
					spriteCloud1.getPosition().x + (cloud1Speed * dt.asSeconds()),
					spriteCloud1.getPosition().y
				);
			}

			if (!cloud2Active)
			{
				srand((int)time(0) * 20);
				cloud2Speed = (rand() % 200);

				srand((int)time(0) * 20);
				float height = (rand() % 150);
				spriteCloud2.setPosition(-200, height);

				cloud2Active = true;
			}
			else
			{
				spriteCloud2.setPosition(
					spriteCloud2.getPosition().x + (cloud2Speed * dt.asSeconds()),
					spriteCloud2.getPosition().y
				);
			}

			if (!cloud3Active)
			{
				srand((int)time(0) * 30);
				cloud3Speed = (rand() % 200);

				srand((int)time(0) * 30);
				float height = (rand() % 150);
				spriteCloud3.setPosition(-200, height);

				cloud3Active = true;
			}
			else
			{
				spriteCloud3.setPosition(
					spriteCloud3.getPosition().x + (cloud3Speed * dt.asSeconds()),
					spriteCloud3.getPosition().y
				);
			}

			if (spriteCloud1.getPosition().x > 1920)
			{
				cloud1Active = false;
			}

			if (spriteCloud2.getPosition().x > 1920)
			{
				cloud2Active = false;
			}

			if (spriteCloud3.getPosition().x > 1920)
			{
				cloud3Active = false;
			}
		}

		/*
		***********************************************************************
		* Draw the scene
		***********************************************************************
		*/

		// Clear everything from the last frame
		window.clear();

		// Draw the newly updated scene here; order matters! If you drew
		// the background last, it would cover all other drawings before it.
		window.draw(spriteBackground);
		window.draw(spriteCloud1);
		window.draw(spriteCloud2);
		window.draw(spriteCloud3);
		window.draw(spriteTree);
		window.draw(spriteBee);

		// Show the updated scene
		window.display();
	}

	return 0;
}