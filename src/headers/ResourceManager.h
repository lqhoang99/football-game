#ifndef RESOURCEMANAGER_H_
#define RESOURCEMANAGER_H_

#include <iostream>
#include <map>
#include <string>
#include <memory>
#include <stdexcept>
#include <cassert>


template<typename Identifier, typename Resource>
class ResourceManager
{
public:
	
	void load(Identifier id, const std::string& filepath);
	
	const Resource& get(Identifier id) const;

private:
	
	std::map<Identifier, std::unique_ptr<Resource>> m_resources;
};

template<typename Identifier, typename Resource>
void ResourceManager<Identifier, Resource>::load(Identifier id, const std::string& filepath)
{
	std::unique_ptr<Resource> resource(new Resource());
	
	if (!resource->loadFromFile(filepath)) {
		throw std::runtime_error("Failed to load: " + filepath);
	}
	
	auto goodInsert = m_resources.insert(std::make_pair(id, std::move(resource)));
	assert(goodInsert.second);
	
}

template<typename Identifier, typename Resource>
const Resource& ResourceManager<Identifier, Resource>::get(Identifier id) const
{
	auto found = m_resources.find(id);
	assert(found != m_resources.end());
	
	return *(found->second);
}

typedef ResourceManager<std::string, sf::Texture> TextureManager;
typedef ResourceManager<std::string, sf::Font> FontManager;
typedef ResourceManager<std::string, sf::SoundBuffer> SoundBufferManager;

#endif