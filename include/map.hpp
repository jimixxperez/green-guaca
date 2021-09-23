#pragma once
#include "game.hpp"

class Map
{
    public:
        Map();
        ~Map();

        void LoadMap();
        void DrawMap();

    private:
        SDL_Rect src, dst;
        SDL_Texture* dirt;
        SDL_Texture* grass;
        SDL_Texture* water;

        int map[20][20];
};