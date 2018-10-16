#include "physicball.h"

PhysicBall::PhysicBall()
{

}

void PhysicBall::update(GLfloat deltaTime)
{
    // Endre så update bruker move, hvor move bruker newtons andre lov for bevegelse
    gsl::Vec3 rotationAxis = gsl::Vec3::cross(mVelocity, gsl::Vec3{0.f, 1.f, 0.f});
    rotationAxis.normalize();

    mVelocity = mVelocity * deltaTime * mMovementSpeed;
}

void PhysicBall::move()
{

}
