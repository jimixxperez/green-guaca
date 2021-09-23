#pragma once

#include "game.hpp"
#include <map>
#include <string>
#include <glm/glm.hpp>

enum Action { move_up = 0, move_down = 1, move_left = 2, move_right = 3, still = 4 };

class Entity
{
    public:
        virtual void init(){};
        virtual void update(float dt){};
        virtual void render(){};
        virtual void handleEvent(SDL_Event event){};

        void setName(const std::string n) {name = n;};
        const std::string getName() {return name;};

        bool isDestroyed() { return destroyed; };
    protected:
        std::string name;
        bool destroyed;
        void* customData = nullptr;
};

class PlayerData
{
    public:
        SDL_Texture* tex;
        glm::vec2 pos = glm::vec2(0);
        glm::vec2 vel = glm::vec2(0);
        glm::vec2 acc = glm::vec2(0);
        ~PlayerData(){
            SDL_DestroyTexture(tex);
        };

};

class Player : public Entity
{
    public:
        void init() override;
        void update(float dt) override;
        void render() override;
        void handleEvent(SDL_Event event) override;
};

class EntityManager
{
    public:
        static EntityManager* getInstance();
        void addEntity(Entity* entity);
        void removeEntity(std::string name);
        void handleEvent(SDL_Event event);
        void update(float dt);
        void render();
    private:
        EntityManager();
        static EntityManager* instance;
        std::map<const std::string, std::shared_ptr<Entity> > entities;
};
