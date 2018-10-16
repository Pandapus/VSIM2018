#ifndef PHYSICBALL_H
#define PHYSICBALL_H

#include "entity.h"
#include "vec3.h"
#include "gltypes.h"
#include "componentbase.h"

class PhysicBall: public Entity
{
    public:
        PhysicBall();
        void update(GLfloat deltaTime);

        void move();

    private:
        GLfloat mMovementSpeed;
        GLfloat mRadius;
        gsl::Vec3 mVelocity;
        InputComponent *mInputcomp{nullptr};
};

#endif // PHYSICBALL_H
