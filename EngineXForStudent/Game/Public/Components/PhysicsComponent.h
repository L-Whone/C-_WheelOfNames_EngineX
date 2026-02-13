#pragma once
#include "Game/Public/Component.h"
#include "Engine/Public/EngineTypes.h"
#include <type_traits>

using CollisionEventSignature = std::function<void(std::weak_ptr<Actor>, const exVector2)>;

class PhysicsComponent : public Component, public std::enable_shared_from_this<PhysicsComponent>
{

public: 

	PhysicsComponent() = delete;
	
	PhysicsComponent(std::weak_ptr<Actor> owner, exVector2 velocity = { 0.0f,0.0f }, 
					bool isStatic = false, bool isGravityEnabled = false);

	virtual void BeginPlay() override;
	virtual void Tick(const float DeltaTime) override;
	virtual void DoPhysics();

#pragma region Collision
	
	virtual bool IsCollisionDetected(std::weak_ptr<PhysicsComponent>& otherComponent);
	virtual void CollisionResolution();

	void ListenForCollision(CollisionEventSignature& delegateToAdd);
	void StopListeningForCollision(CollisionEventSignature& delegateToRemove);
	void BroadcastCollisionEvents(std::weak_ptr<Actor> otherActor, const exVector2 hitLocation);

	exVector2 GetVelocity() const;
	void SetVelocity(exVector2 inVelocity);

private:

	unsigned int mIsGravityEnabled : 1; // bit field, they can be used if the game has more than one boolean
	unsigned int mIsStatic : 1;
	exVector2 mVelocity;
	std::list<CollisionEventSignature> mCollisionEvents;

#pragma endregion

};