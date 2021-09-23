#include "map.hpp"
#include "textureManager.hpp"

Map::Map()
{
    dirt = TextureManager::LoadTexture("../asset/dirt.png");
}