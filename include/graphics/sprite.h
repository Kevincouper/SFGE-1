/*
MIT License

Copyright (c) 2017 SAE Institute Switzerland AG

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef SFGE_SPRITE_H
#define SFGE_SPRITE_H

//STL
#include <map>
#include <string>
//Engine
#include <engine/component.h>
#include <engine/engine.h>
//Dependencies
#include <SFML/Graphics.hpp>

namespace sfge
{
class GraphicsManager;
/**
* \brief Sprite component used in the GameObject
*/
class Sprite : public Component
{
public:
	using Component::Component;
	/**
	* \brief Update the Component
	* \param dt Delta time since last frame
	*/
	virtual void Update(float dt) override;
	
	void Draw(sf::RenderWindow& window);

	static std::shared_ptr<Sprite> LoadSprite(json& componentJson, GameObject& gameObject);

	void SetTexture(std::shared_ptr<sf::Texture> newTexture);

	void SetLayer(int layer);
	static bool SpriteLayerComp(std::shared_ptr<Sprite> s1, std::shared_ptr<Sprite> s2);
protected:
	std::string filename;
	int textureId;
	int layer;
	sf::Sprite sprite;
};

/**
* \brief Sprite manager caching all the sprites and rendering them at the end of the frame
*/
class SpriteManager 
{
public:
	SpriteManager(GraphicsManager& graphicsManager);
	void Update(sf::Time dt);
	void Draw(sf::RenderWindow& window);
	void LoadSprite(json& componentJson, std::shared_ptr<Sprite> sprite);
protected:
	std::list<std::shared_ptr<sfge::Sprite>> m_Sprites;
	GraphicsManager& m_GraphicsManager;
};

/**
* \brief The Texture Manager is the cache of all the textures used for sprites or other objects
*
*/
class TextureManager
{
public:
	
	/**
	* \brief load the texture from the disk or the texture cache
	* \param filename The filename string of the texture
	* \return The strictly positive texture id > 0, if equals 0 then the texture was not loaded
	*/
	unsigned int LoadTexture(std::string filename);
	/**
	* \brief Used after loading the texture in the texture cache to get the pointer to the texture
	* \param text_id The texture id striclty positive
	* \return The pointer to the texture in memory
	*/
	std::shared_ptr<sf::Texture> GetTexture(unsigned int text_id);

private:

	std::map<std::string, unsigned int> nameIdsMap;
	std::map<unsigned int, std::shared_ptr<sf::Texture>> texturesMap;
	unsigned int increment_id = 0;

};

}
#endif // !SFGE_SPRITE
