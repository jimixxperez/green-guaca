#include "game.hpp"
#include "entityManager.hpp"
#include "textureManager.hpp"
#include "sdlUtils.hpp"
#include <random>

EntityManager* EntityManager::instance = nullptr;

EntityManager::EntityManager(){}

EntityManager* EntityManager::getInstance()
{
    if (!instance)
    instance = new EntityManager();
    return instance;
}

void EntityManager::addEntity(Entity* entity)
{
    //entity->init();
    std::cout << "insert " << entity->getName() << std::endl;
    entities[entity->getName()] = entity;
}

void EntityManager::removeEntity(std::string name)
{
    auto t = (*(entities[name])).getType();
    std::cout << "remove " << name  << " " << t << std::endl;
    if (t == "particle") delete (Particle*)entities[name];
    else if (t == "player") delete (Player*)entities[name];
    entities.erase(name);
}

void EntityManager::update(float dt)
{
    std::cout << "iterator" << std::endl;
    std::map<const std::string, Entity* >::iterator it;
    for (it=entities.begin(); it!=entities.end(); ++it)
    {
        auto ent = it->second;
        std::cout << "update entity manager " << ent->getName() << std::endl; 
        if(ent->isDestroyed()) {
            removeEntity(ent->getName());
            continue;
        }
        ent->update(dt);
    } 
}

void EntityManager::handleEvent(SDL_Event e)
{
    std::map<const std::string, Entity* >::iterator it;
    for (it=entities.begin(); it!=entities.end(); ++it)
    {
        auto ent = it->second;
        std::cout << "handle event entity manager" << std::endl; 
        ent->handleEvent(e);
    } 
}

void EntityManager::render()
{
    std::map<const std::string, Entity* >::iterator it;
    for (it=entities.begin(); it!=entities.end(); ++it)
    {
        auto ent = it->second;
        std::cout << "render entity manager" << std::endl; 
        ent->render();
    } 
}
// === ENTITY ===


// === PLAYER ===
// Player::Player()
// {
//     type = "player";
//     auto d = new PlayerData();
//     d->tex = TextureManager::LoadTexture("../assets/ham.png");
//     customData = d;
// }

void Player::init(void* init_d)
{
    auto d = static_cast<PlayerData*>(init_d);
    type = "player";   
    //setType("player");
    d->tex = TextureManager::LoadTexture("../assets/ham.png");
    customData = d;
    std::cout << "player init" << std::endl;
}

void Player::handleEvent(SDL_Event event)
{
    //std::cout << "Player handleEvent!" <<std::endl;
    auto d = static_cast<PlayerData*>(customData);
    auto k = Game::gameState->keyboard;

    // === MOVEMENT ===
    d->acc = glm::vec2(0);
    if (k[SDLK_UP]) d->acc += glm::vec2(0,-1);
    if (k[SDLK_DOWN]) d->acc += glm::vec2(0,1);
    if (k[SDLK_LEFT]) d->acc += glm::vec2(-1,0);
    if (k[SDLK_RIGHT]) d->acc += glm::vec2(1,0);

    // === SHOOT ===
    if (k[SDLK_SPACE])
    {
        auto em = EntityManager::getInstance();
        std::cout << em << std::endl;
        auto particle_vel = glm::normalize(d->vel);
        auto pd = new ParticleData();
        pd->vel = particle_vel * 7.0f;
        pd->pos = d->pos + (d->box_dim * 0.5f);
        pd->max_frame = 100;
        auto p = new Particle();
        p->setName("shooting particle");
        p->init(pd);
        em->addEntity(p);
    }
}

void Player::update(float dt)
{
    auto d = static_cast<PlayerData*>(customData);
    float max_speed = 40;
    d->vel += 12.0f * d->acc * dt - 0.5f * d->vel;
    d->pos += d->vel * dt;
    if (d->pos[0] < 0) d->pos[0] = 800;
    if (d->pos[0] > 800) d->pos[0] = 0;
    if (d->pos[1] < 0) d->pos[1] = 600;
    if (d->pos[1] > 600) d->pos[1] = 0;
}

void Player::render()
{
    auto d = static_cast<PlayerData*>(customData);
    std::cout << "Player render!" <<std::endl;
    std::cout << getName() <<std::endl;
    SDL_Rect dstRect;
    dstRect.w = d->box_dim[0];
    dstRect.h = d->box_dim[1];
    dstRect.x = d->pos[0];
    dstRect.y = d->pos[1];
    SDL_RendererFlip flip = (d->vel[0] > 0) ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
    SDL_RenderCopyEx(Game::renderer, d->tex, NULL, &dstRect,  NULL, NULL, flip);
}

// Particle::Particle()
// {
//     type = "particle"; 
//     auto d = new ParticleData();
//     customData = d;
// }

// Particle::Particle(glm::vec2 init_pos, glm::vec2 init_vel)
// {
//     type = "particle";
//     auto d = new ParticleData();
//     d->pos = init_pos;
//     d->vel = init_vel;
//     customData = d; 
// }

void Particle::init(void* init_d)
{
    auto d = static_cast<ParticleData*>(init_d);
    type = "particle";
    customData = d;
    std::cout << "particle init" << std::endl;
}

void Particle::update(float dt)
{
    auto d = static_cast<ParticleData*>(customData);
    d->pos += d->vel * dt;
    d->current_frame += 1;
    std::cout << d->current_frame << std::endl;
    if (d->current_frame > d->max_frame) destroyed = true;
        
    if (d->pos[0] < 0) d->vel = glm::reflect(d->vel, {1, 0});
    if (d->pos[0] > 800) d->vel = glm::reflect(d->vel, {-1, 0});
    if (d->pos[1] < 0) d->vel = glm::reflect(d->vel, {0, 1});
    if (d->pos[1] > 600) d->vel = glm::reflect(d->vel, {0, 1});
}

void Particle::render()
{
    std::cout << "Particle render!" << std::endl;
    auto d = static_cast<ParticleData*>(customData);
    SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);
    Circle::SDL_RenderFillCircle(Game::renderer, d->pos[0], d->pos[1], 5);
    SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);
}
// {
//     public:
//         static EntityManager* getInstance();
//         ~EntityManager();
//         void addEntity(Entity* entity);
//         void removeEntity(Entity* entity);
//     private:
//         EntityManager();
//         static EntityManager* instance;
//         std::map<std::string, std::shared_ptr<Entity>> entities;
// };