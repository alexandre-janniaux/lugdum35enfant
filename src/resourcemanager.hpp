#pragma once

#include <iostream>
#include <string>
#include <memory>
#include <map>
#include <SFML/Graphics.hpp>

#if __APPLE__
#include "ResourcePath.hpp"
#endif

#include "cpp_std_11.hpp"
#include "singleton.hpp"

template <typename T>
class ResourceManager : public Singleton<ResourceManager<T>>
{
	public:
		T& get(const std::string& nom_fichier);

		~ResourceManager() = default;
	private:

    	std::map<std::string, T*> m_resources;
};

template <typename T>
T& ResourceManager<T>::get(const std::string& nom_fichier)
{
	std::string filename = nom_fichier;
	#if __APPLE__
	filename = resourcePath() + nom_fichier;
	#endif

	if(m_resources.find(filename) == m_resources.end())
	{
		std::cout << "chargement de " << filename << std::endl;
		m_resources.insert(std::pair<std::string, T*>(filename, new T));
		m_resources[filename]->loadFromFile(filename);
	}
	return *m_resources.at(filename);
}

using FontManager = ResourceManager<sf::Font>;
using TextureManager = ResourceManager<sf::Texture>;
