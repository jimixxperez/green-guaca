#include "game.hpp"
#include "textureManager.hpp"
#include "entityManager.hpp"

// === STATIC VARIABLE ===
SDL_Renderer* Game::renderer = nullptr;
GameState* Game::gameState = new GameState();

void Game::init(std::string title, int xpos, int ypos, int width, int height, bool fullscreen)
{
    int flags = 0;
    if (fullscreen) 
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if(SDL_Init(SDL_INIT_EVERYTHING) == 0) 
    {
        std::cout << "Subsystem Initialised..." << std::endl;
        window = SDL_CreateWindow(title.c_str(), xpos, ypos, width, height, flags);
        if (window) 
        {
            std::cout << "Window created!" << std::endl;
        }
        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer)
        {
            std::cout << "Renderer created!" << std::endl;
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        }

        std::cout << SDL_GetError() << std::endl;
        entityManager = EntityManager::getInstance();
        Player* player = new Player();
        player->setName("player");
        player->init(new PlayerData());

        ParticleData* p1_d = new ParticleData();
        p1_d->max_frame = 200;
        p1_d->vel = {1,0.5};
        p1_d->pos = {20,400};
        Particle* particle = new Particle();
        //Particle* particle = new Particle({20,20}, {1,1});
        particle->setName("particle1");
        particle->init(p1_d);

        auto p2_d = new ParticleData();
        p2_d->max_frame = 80;
        p2_d->vel = {0.5,0.5};
        p2_d->pos = {400,200};
        Particle* particle2 = new Particle();
        //Particle* particle = new Particle({20,20}, {1,1});
        particle2->setName("particle2");
        particle2->init(p2_d);
        // Particle* particle2 = new Particle({20,200}, {-1,1});
        // particle2->setName("particle2");

        entityManager->addEntity(player);
        entityManager->addEntity(particle);
        //entityManager->addEntity(particle2);
        //entityManager->addEntity(particle2);
        isRunning = true;
    }
    else 
    {
        isRunning = false;
    }
}

void Game::handleEvents()
{
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;
        case SDL_KEYDOWN:
            gameState->keyboard[event.key.keysym.sym] = true;
            entityManager->handleEvent(event);
            break;
        case SDL_KEYUP:
            gameState->keyboard[event.key.keysym.sym] = false;
            entityManager->handleEvent(event);
            break;
        default:
            //entityManager->handleEvent(event);
            break;
    }
}

void Game::update()
{
    //std::cout << cnt << std::endl;
    entityManager->update(1.0);
}

void Game::render()
{
    SDL_RenderClear(renderer);
    entityManager->render();
    SDL_RenderPresent(renderer);
}

void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game Cleaned!" << std::endl;
}