#include "Game/Public/Components/CircleColliderComponent.h"
#include "Game/Public/Components/TransformComponent.h"
#include "Game/Public/Actor.h"

CircleColliderComponent::CircleColliderComponent(std::weak_ptr<Actor> owner, float radius,
	exVector2 velocity,
	bool isStatic,
	bool isGravityEnabled) : PhysicsComponent(owner, velocity, isStatic, isGravityEnabled),
	mRadius(radius)
{

};

bool CircleColliderComponent::IsCollisionDetected(std::weak_ptr<PhysicsComponent>& otherComponent)
{
	if (!otherComponent.expired())
	{
		if (std::shared_ptr<CircleColliderComponent> OtherCircleColliderComponent = std::dynamic_pointer_cast<CircleColliderComponent>(otherComponent.lock()))
		{
			exVector2 SelfCenterPos;
			exVector2 OtherCenterPos;

			if (!mOwner.expired())
			{
				if (const std::shared_ptr<TransformComponent> TransformComp = mOwner.lock()->GetComponentOfType<TransformComponent>())
				{
					SelfCenterPos = TransformComp->GetLocation();
				}

				if (!(otherComponent.lock()->GetOwner().expired()))
				{
					if (const std::shared_ptr<TransformComponent> TransformComp = OtherCircleColliderComponent->GetOwner().lock()->GetComponentOfType<TransformComponent>())
					{
						OtherCenterPos = TransformComp->GetLocation();
					}
				}


			exVector2 Length = SelfCenterPos - OtherCenterPos;
			float DistanceSquared = (Length.x * Length.x) + (Length.y * Length.y);
			float RadiusSum = mRadius + OtherCircleColliderComponent->GetRadius();
			return DistanceSquared < (RadiusSum * RadiusSum);
			}
		}
	}
	PhysicsComponent::IsCollisionDetected(otherComponent);
}

void CircleColliderComponent::CollisionResolution()
{
	exVector2 CurrentVelocity = GetVelocity();
	exVector2 ResolvedVelocity = CurrentVelocity * -1.0f;
	SetVelocity(ResolvedVelocity);
}

float CircleColliderComponent::GetRadius() const
{
	return mRadius;
}
