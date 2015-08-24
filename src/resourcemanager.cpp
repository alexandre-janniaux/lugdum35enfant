#include "resourcemanager.hpp"

template <>
std::unique_ptr<sf::Music>&& ResourceProvider(const std::string& filename) {
	auto ptr = make_unique<sf::Music>();
	ptr->openFromFile(filename);
	return std::move(ptr);
}