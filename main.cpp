#include <SFML/Graphics.hpp>

int main()
{
    // Create a video mode object and set the screen resolution.
    sf::VideoMode vm(1920, 1080);

    // Create a window object and give it the video mode, a title
    // and a style parameter
    sf::RenderWindow window(vm, "Timber!!!", sf::Style::Fullscreen);

    return 0;
}