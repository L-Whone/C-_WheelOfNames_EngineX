#pragma once
#include "Game/Public/Components/PhysicsComponent.h"

class CircleColliderComponent : public PhysicsComponent
{

public:
	CircleColliderComponent() = delete;
	CircleColliderComponent(std::weak_ptr<Actor> owner, float radius, exVector2 velocity = { 0.0f,0.0f },
		bool isStatic = false, bool isGravityEnabled = false);

	virtual bool IsCollisionDetected(std::weak_ptr<PhysicsComponent>& otherComponent);
	virtual void CollisionResolution() override;

	float GetRadius() const;
private:

	float mRadius;

};