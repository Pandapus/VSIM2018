#ifndef BALLSYSTEM_H
#define BALLSYSTEM_H

#include "systembase.h"
#include "componentbase.h"

class ECSManager;

class Ballsystem : public SystemBase
{
public:
    Ballsystem();

    static Ballsystem* getInstance();

    void checkCollision();
    void applyPhysics(float deltaTime);
    size_t thropyCounter;

private:
    ECSManager* mManager{nullptr};

    static Ballsystem* mInstance;
};

#endif // BALLSYSTEM_H
