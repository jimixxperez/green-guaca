#pragma once

#include "game.hpp"
#include <map>
#include <string>
#include <glm/glm.hpp>

enum Action { move_up = 0, move_down = 1, move_left = 2, move_right = 3, still = 4 };

class Entity
{
    public:
        virtual void init(void* init_d){};
        virtual void update(float dt){};
        virtual void render(){};
        virtual void handleEvent(SDL_Event event){};
        virtual ~Entity(){};

        void setName(const std::string n) {name = n;};
        const std::string getName() {return name;};

        bool isDestroyed() { return destroyed; };
        
        void setType(const std::string n) {type = n;};
        const std::string getType() {return type;};
    protected:
        std::string name;
        bool destroyed = false;
        void* customData = nullptr;
        std::string type;
};

class PlayerData
{
    public:
        SDL_Texture* tex;
        glm::vec2 pos = glm::vec2(0);
        glm::vec2 vel = glm::vec2(0);
        glm::vec2 acc = glm::vec2(0);
        glm::vec2 box_dim = {32,32};
        ~PlayerData(){
            SDL_DestroyTexture(tex);
        };

};

class Player : public Entity
{
    public:
        void init(void* init_d) override;
        void update(float dt) override;
        void render() override;
        void handleEvent(SDL_Event event) override;
        ~Player() override {
            delete (PlayerData*)customData;
        };
};

class ParticleData
{
    public:
        glm::vec2 pos = glm::vec2(0);
        glm::vec2 vel = glm::vec2(0);
        glm::vec2 acc = glm::vec2(0);
        int max_frame = 200;
        int current_frame = 0;
};

class Particle : public Entity
{
    public:
        void init(void* init_d) override;
        void update(float dt) override;
        void render() override;
        void handleEvent(SDL_Event event) override {};
        ~Particle() override 
        {
            std::cout << "delete particle: " << getName() <<  "!" << std::endl;
            delete (ParticleData*)customData;
        };
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
        std::map<const std::string, Entity* > entities;
};
