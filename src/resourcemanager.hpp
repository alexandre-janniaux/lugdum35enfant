#pragma once

#include <iostream>
#include <string>
#include <memory>
#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#if __APPLE__
#include "ResourcePath.hpp"
#endif

#include "cpp_std_11.hpp"

template <typename T>
T* ResourceProvider(const std::string& filename) {
	auto ptr = new T;
	ptr->loadFromFile(filename);
	return ptr;
}

template <>
sf::Music* ResourceProvider(const std::string& filename);

template <typename T>
class ResourceManager
{
public:
    static ResourceManager* instance()
    {
		if(m_instance == nullptr)
		{
	    	m_instance.reset(new ResourceManager<T>());
		}
		return m_instance.get();
    }
    
    T& get(const std::string& nom_fichier)
    {
        std::string filename = nom_fichier;
#if __APPLE__
        filename = resourcePath() + nom_fichier;
#endif

	if(m_resources.find(filename) == m_resources.end())
	{
	    std::cout << "chargement de " << filename << std::endl;
	    m_resources.insert(std::pair<std::string, T*>(filename, ResourceProvider<T>(filename)));
	}
	return *m_resources.at(filename);
    }
    
    ~ResourceManager() {
		std::cout << "Delete loader" << std::endl;
		for (auto res : m_resources)
			delete res.second;
	}
private:
    ResourceManager() { std::cout << "Create loader" << std::endl; }
    using Ptr = std::unique_ptr<ResourceManager<T>>;
    
    //friend make_unique<ResourceManager<T>>();
    
    static Ptr m_instance;
    std::map<std::string, T*> m_resources;
};

template <typename T>
typename ResourceManager<T>::Ptr ResourceManager<T>::m_instance = nullptr;

using FontManager = ResourceManager<sf::Font>;
using TextureManager = ResourceManager<sf::Texture>;
