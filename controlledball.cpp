#include "controlledball.h"
#include "math_constants.h"


ControlledBall::ControlledBall()
{
    mRadius = 1.f;
    mVelocity = gsl::Vec3{0.f, 0.f, 0.f};
    mMovementSpeed = 2.f;
}


void ControlledBall::update(GLfloat deltaTime)
{
    gsl::Vec3 rotationAxis = gsl::Vec3::cross(mVelocity, gsl::Vec3{0.f, 1.f, 0.f});
    rotationAxis.normalize();

    mVelocity = mVelocity * deltaTime * mMovementSpeed;

    //OEF: this is broken now because of restructuring into ECS
    //GLfloat theta = mVelocity.length() / mRadius * (180.f / gsl::PI);
    //GLfloat theta = mVelocity.length() / mRadius * (180.f/gsl::PI);
    //mTransform.mTransform->rotate(-(rotationAxis.getX()*theta),-(rotationAxis.getY()*theta),-(rotationAxis.getZ()*theta));
    //mTransform.mTransform->setPosition(getTransform()->getPosition() + mVelocity);
}
