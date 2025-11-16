#include <iostream>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio/Music.hpp>

int main(int argc, char **argv)
{
	//std::cout << "hello " << argc  << " " << argv[1] << std::endl;
	auto Music = new sf::Music("ikutaerika.mp3");
	std::cout << "play start" << std::endl;
	Music->play();
	std::cout << "play end" << std::endl;
	while (1);
	return 0;
}
