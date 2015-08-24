#include "resourcemanager.hpp"

template <>
sf::Music* ResourceProvider(const std::string& filename) {
	auto ptr = new sf::Music;
	ptr->openFromFile(filename);
	return ptr;
}
