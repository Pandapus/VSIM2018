#include "aisystem.h"
#include "ecsmanager.h"
#include "vec2.h"
#include "vertex.h"
#include "meshbase.h"
#include "coreengine.h"
#include "gsl_math.h"
#include "bsplinecurve.h"

using namespace gsl;

AiSystem* AiSystem::mInstance = nullptr;

AiSystem::AiSystem()
{
    mInstance = this;
    mManager = ECSManager::getInstance();
}

void AiSystem::patrol(GLfloat deltatime)
{
    //Gets all the trophies locations and gathers them in controllPoints vector
    std::vector<BoxColliderComponent>& boxCollider = mManager->mBoxColliderComponents;
    std::vector<gsl::Vec3> controllPoints;
    for(size_t i = 0; i < boxCollider.size(); i++)
    {
        if(boxCollider[i].bSpline == true)
            controllPoints.push_back(boxCollider[i].getFirstTransformComponent()->mTransform.getPosition());
    }

    //Runs the patrol() function on all the ai's
    std::vector<AiComponent>& ai = mManager->mAiComponents;
    for(size_t i = 0; i < ai.size(); i++)
    {
        std::vector<float> knots;
        BSplineCurve spline;
        float sum = 0.f;
        std::vector<gsl::Vec3> vs;

        //Sets up knots for a BSpline thats bigger than 2 (4 and 3 works)
        if (controllPoints.size() > 2)
        {
            for(uint j = 0; j < controllPoints.size()-2; j++)
            {
                vs.push_back(controllPoints[j+1] - controllPoints[j]);
                sum += vs.back().length();
            }

            knots.push_back(0.f);
            knots.push_back(0.f);
            knots.push_back(0.f);

            if(controllPoints.size() > 3)
                knots.push_back(0.5f);

            knots.push_back(1.f);
            knots.push_back(1.f);
            knots.push_back(1.f);
        }
        //Sets up knots for a Bspline that has 2 controllpoints
        else if(controllPoints.size() == 2)
        {
            Vec3 center = controllPoints[0];
            controllPoints.clear();

            Vec3 right = center + Vec3(20, 0, 0);
            Vec3 front = center + Vec3(0, 0, -20);
            Vec3 left = center + Vec3(-20, 0, 0);
            Vec3 back = center + Vec3(0, 0, 20);

            controllPoints.push_back(right);
            controllPoints.push_back(front);
            controllPoints.push_back(left);
            controllPoints.push_back(back);
            controllPoints.push_back(right);

            knots.push_back(0.f);
            knots.push_back(0.f);

            knots.push_back(0.f);
            knots.push_back(1.f/3.f);
            knots.push_back(2.f/3.f);
            knots.push_back(1.f);

            knots.push_back(1.f);
            knots.push_back(1.f);


            //Could not make this work.

            //            Vec3 aiPos = ai[i].getFirstTransformComponent()->mTransform.getPosition();
            //            Vec3 walkDir;
            //            bool switchDir = false;
            //            float distToGoal;
            //            std::vector<float> diffLoc;

            //            for(size_t u = 0; u < 2; u++)
            //                diffLoc.push_back((controllPoints[u]-ai[i].getFirstTransformComponent()->mTransform.getPosition()).length());

            //            if(diffLoc[0] >= diffLoc[1])
            //            {
            //                walkDir = controllPoints[1] - aiPos;
            //                distToGoal = diffLoc[1];
            //            }
            //            else
            //            {
            //                walkDir = controllPoints[0] - aiPos;
            //                distToGoal = diffLoc[0];
            //            }

            //            if(distToGoal < 1.f)
            //            {
            //                switchDir = !switchDir;
            //                if(switchDir)
            //                {
            //                    walkDir = controllPoints[1] - aiPos;
            //                    distToGoal = diffLoc[1];
            //                }
            //                else
            //                {
            //                    walkDir = controllPoints[0] - aiPos;
            //                    distToGoal = diffLoc[0];
            //                }
            //            }

            //            walkDir.normalize();
            //            ai[i].getFirstTransformComponent()->mTransform.setPosition(walkDir * ai[i].speed);
            //            std::cout << aiPos-walkDir << std::endl;

        }

        //if there is 1 or fewer controllPoints left, we don't run the movement on the ai
        if(controllPoints.size() >= 2)
        {
            //runs the needed bSpline functions
            unsigned int interval = spline.getIntervalFromTime(ai[i].time ,knots);
            Vec3 pos = spline.evaluate(2, 2, interval, ai[i].time, knots, controllPoints);

            //gets the transform of the ai for easier access
            TransformComponent* transform = ai[i].getFirstTransformComponent();
            std::vector<MeshColliderComponent>& t3 = mManager->mMeshColliderComponents;
            Mat4 terrainMat, invTerrainMat;

            for(size_t k = 0; k < t3.size(); k++)
            {
                terrainMat = t3[k].modelMatrix;
                invTerrainMat = terrainMat;
                invTerrainMat.inverse();

                //BaryCentic Coordinates
                int triangle = t3[k].mData->findTriangleIndexFromWorldPosition(ai[i].triangleLastFrame, pos, invTerrainMat, t3[k].triangles, t3[k].mData->vertices());
                if(triangle != -1)
                {
                    ai[i].triangleLastFrame = triangle;

                    float y = (ai[i].mData->mBoundingBoxRightUpFront).length();

                    Vec3 triangleCenter = (terrainMat*Vec4(ai[i].mData->getTriangleCenter(triangle, t3[k].triangles, t3[k].mData->vertices()), 1)).toVector3D();

                    Vec3 triangleNormal = (terrainMat*Vec4(ai[i].mData->normalFromTriangle(triangle, t3[k].triangles, t3[k].mData->vertices()), 0)).toVector3D().normalized();
                    Vec3 centerToTriangleCenter = pos - triangleCenter;

                    float distance = Vec3::dot(centerToTriangleCenter, triangleNormal);

                    pos.setY(pos.getY() - distance + y);
                }

                //applies speed and moves the ai
                transform->mTransform.setPosition(pos);

                Vec3 speed = transform->mTransform.getPosition() - ai[i].lastPosition;
                speed.setY(0.f);

                float speedMag = speed.length() / deltatime;

                if(speedMag > 12.f)
                    ai[i].speed -= 0.005f;
                else if(speedMag < 12.f)
                    ai[i].speed += 0.005f;

                speed.normalize();

                Vec3 rotAxis = speed^Vec3(0, 0, -1);

                double angle = gsl::rad2deg(static_cast<double>(std::acos(Vec3::dot(speed, Vec3(0, 0, -1)) / speed.length())));

                Quaternion rot(angle, rotAxis);
                transform->mTransform.setRotation(rot);

                if(ai[i].time >= knots[knots.size() - 1] - 0.001f)
                    ai[i].time = 0.f;
                else
                    ai[i].time += deltatime*ai[i].speed;

                ai[i].lastPosition = transform->mTransform.getPosition();
            }

        }
        else
            break;
    }
}
