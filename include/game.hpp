#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <entityManager.hpp>
#include <map>
#include <string>

class GameState 
{
    public:
        std::map<SDL_Keycode, bool> keyboard;
};

class Game 
{
    public:
        void init(std::string title, int xpos, int ypos, int width, int height, bool fullscreen);
        void handleEvents();
        void update();
        void render();
        void clean();
        bool running() {return isRunning;};
        static SDL_Renderer* renderer;
        static GameState* gameState;

    private:
        bool isRunning;
        SDL_Window* window;
        EntityManager* entityManager;
};