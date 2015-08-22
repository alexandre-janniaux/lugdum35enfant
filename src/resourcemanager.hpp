#pragma once

#include <string>
#include <memory>
#include <map>
#include <SFML/Graphics.hpp>

#include "cpp_std_11.hpp"

template <typename T>
class ResourceManager
{
public:
    static ResourceManager& instance()
    {
	if(m_instance != nullptr)
	    return m_instance;
	else
	    return ResourceManager();
    }
    
    T& get(const std::string& name)
    {
	return *m_resources.at(name);
    }
    
    void set(const std::string& name, const std::string& file)
    {
	m_resources[name] = make_unique<T>();
	m_resources[name]->loadFromFile(file);
    }
    
private:
    using Ptr = std::unique_ptr<ResourceManager<T>>;
    ResourceManager() = default;
    
    static Ptr m_instance;
    std::map<std::string, std::unique_ptr<T>> m_resources;
};

template <typename T>
typename ResourceManager<T>::Ptr ResourceManager<T>::m_instance = nullptr;

using FontManager = ResourceManager<sf::Font>;
using TextureManager = ResourceManager<sf::Texture>;