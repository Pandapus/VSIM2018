#ifndef AISYSTEM_H
#define AISYSTEM_H

#include "systembase.h"
#include "componentbase.h"
#include <vector>

class ECSManager;

class AiSystem : public SystemBase
{
public:
    AiSystem();

    void patrol(GLfloat deltatime);
    static AiSystem getInstance();

private:
    ECSManager* mManager{nullptr};
    static AiSystem* mInstance;
};

#endif // AISYSTEM_H
