#ifndef ECSMANAGER_H
#define ECSMANAGER_H

#include "systembase.h"
#include "componentbase.h"
#include "constants.h"
#include <list>
#include <vector>

class RenderSystem;
class InputSystem;
class CollisionSystem;
class ScriptSystem;
class PhysicsSystem;
class CameraSystem;
class RenderWindow;
class MeshFactory;
class Entity;
class Shader;
class Texture;
class PointLight;
class DirectionalLight;

class ECSManager
{
    public:
        ECSManager(RenderWindow *renderWindow);
        static ECSManager* getInstance();

        void runRenderSystem();
        void runInputSystem();
        void runCollisionSystem();
        void runScriptSystem(GLfloat deltaTime);
        void runPhysicsSystem(GLfloat deltaTime);
        void runCameraSystem();

        //Testing a makeEntity function. Must use to see what is best as default parameters
        Entity* makeEntity(std::string entityName);
        Entity* makeEntity(std::string entityName, std::string meshName, gsl::ShaderTypes shader);

        DirectionalLight *getLight() const;

        std::list<Entity*> mEntities;            //All Entities in the program
        InputComponent* mInComp{nullptr};       //OEF: this should belong to an Entity

        //All components in the program. Making own vectors pr Component for now
        //Easier to grasp, than having a std::list<of std::vectors>...
        std::vector<MeshComponent> mMeshComponents;
        std::vector<TransformComponent> mTransformComponents;
        std::vector<MaterialComponent> mMaterialComponents;
        std::vector<InputComponent> mInputComponents;
        std::vector<RigidBodyComponent> mRigidBodyComponents;
        std::vector<ScriptComponent*> mScriptComponents;
        std::vector<BoxColliderComponent> mBoxColliderComponents;
        std::vector<SphereColliderComponent> mSphereColliderComponents;
        std::vector<CyllinderColliderComponent> mCyllinderColliderComponents;
        std::vector<CapsuleColliderComponent> mCapsuleColliderComponents;
        std::vector<MeshColliderComponent> mMeshColliderComponents;
        std::vector<CameraComponent> mCameraComponents;

        //Direct pointers to systems instead of having a std::list< of systems>
        //That way it is easier to controll the order of the systems running
        RenderSystem *mRenderSystem{nullptr};
        InputSystem *mInputSystem{nullptr};
        MeshFactory *mMeshFactory{nullptr};
        RenderWindow *mRenderWindow{nullptr};    //Only to get access to Materials for now - this should be fixed!!!
        CollisionSystem *mCollisionSystem{nullptr};
        ScriptSystem *mScriptSystem{nullptr};
        PhysicsSystem* mPhysicsSystem{nullptr};
        CameraSystem* mCameraSystem{nullptr};

        //Other resources:
        Shader *mShaders[4]{nullptr};
        Texture *mTextures[4]{nullptr};
        Material *mMaterials[4]{nullptr};
        DirectionalLight *mLight{nullptr}; //Only temporary

    private:
        ECSManager(ECSManager const&);      ///< Private copy constructor.
        void operator=(ECSManager const&);    ///< Private class assignment operator.
        static ECSManager *mInstance;         ///< Singleton instance pointer.

        void makeShaders();
        void makeTextures();
        void makeMaterials();
};

#endif // ECSMANAGER_H
