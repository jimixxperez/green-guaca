#pragma once

class Scene
{
    public:
        virtual void start();
        virtual void update(float dt);
        virtual void render();

};