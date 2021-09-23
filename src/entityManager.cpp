#include "game.hpp"
#include "entityManager.hpp"
#include "textureManager.hpp"

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
    entity->init();
    entity->setName("Test");
    std::cout << "insert " << entity->getName() << std::endl;
    entities[entity->getName()] = std::shared_ptr<Entity>(entity);
}

void EntityManager::removeEntity(std::string name)
{
    std::cout << "remove " << name << std::endl;
    entities.erase(name);
}

void EntityManager::update(float dt)
{
    std::map<const std::string, std::shared_ptr<Entity> >::iterator it;
    for (it=entities.begin(); it!=entities.end(); ++it)
    {
        auto ent = it->second;
        ent->update(dt);
    } 
}

void EntityManager::handleEvent(SDL_Event e)
{
    std::map<const std::string, std::shared_ptr<Entity> >::iterator it;
    for (it=entities.begin(); it!=entities.end(); ++it)
    {
        auto ent = it->second;
        ent->handleEvent(e);
    } 
}

void EntityManager::render()
{
    std::map<const std::string, std::shared_ptr<Entity> >::iterator it;
    for (it=entities.begin(); it!=entities.end(); ++it)
    {
        auto ent = it->second;
        std::cout << "render entity manager" << std::endl; 
        ent->render();
    } 
}
// === ENTITY ===


// === PLAYER ===
void Player::init()
{
    auto d = new PlayerData();
    d->tex = TextureManager::LoadTexture("../assets/ham.png");
    customData = d;
}

void Player::handleEvent(SDL_Event event)
{
    //std::cout << "Player handleEvent!" <<std::endl;
    auto d = static_cast<PlayerData*>(customData);
    auto k = Game::gameState->keyboard;
    d->acc = glm::vec2(0);
    if (k[SDLK_UP]) d->acc += glm::vec2(0,-1);
    if (k[SDLK_DOWN]) d->acc += glm::vec2(0,1);
    if (k[SDLK_LEFT]) d->acc += glm::vec2(-1,0);
    if (k[SDLK_RIGHT]) d->acc += glm::vec2(1,0);
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
    dstRect.w = 32;
    dstRect.h = 32;
    dstRect.x = d->pos[0];
    dstRect.y = d->pos[1];
    SDL_RendererFlip flip = (d->vel[0] > 0) ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
    SDL_RenderCopyEx(Game::renderer, d->tex, NULL, &dstRect,  NULL, NULL, flip);
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