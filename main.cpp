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
    spriteBee.setPosition(0, 800);

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

    spriteCloud1.setPosition(0, 0);
    spriteCloud2.setPosition(0, 250);
    spriteCloud3.setPosition(0, 500);

    /*
    *************************************************************************** 
    * Variables for game state
    ***************************************************************************
    */

    // Bee ////////////////////////////////////////////////////////////////////

    // Is the bee currently moving?
    bool beeActive = false;

    // How fast is the bee (in pixels per second)?
    float beeSpeed = 0.0f;

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

        /*
        ***********************************************************************
        * Update the scene
        ***********************************************************************
        */

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