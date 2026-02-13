#include "Game/Public/Components/CircleRenderComponent.h"
#include "Engine/Public/EngineInterface.h"
#include "Game/Public/Actor.h"
#include "Game/Public/Components/TransformComponent.h"

void CircleRenderComponent::Render(exEngineInterface* EngineInterface)
{
	if (EngineInterface)
	{
		exVector2 CenterPos = { 0.0f, 0.0f };
		if (!mOwner.expired())
		{
			if (std::shared_ptr<Actor> owner = mOwner.lock())
			{
				if (std::shared_ptr<TransformComponent> TransformComp = owner->GetComponentOfType<TransformComponent>())
				{
					CenterPos = TransformComp->GetLocation();
					EngineInterface->DrawCircle(CenterPos, mRadius, mRenderColor, 1); // TODO Add variable layer to Base RenderComponent
				}
			}
		}
	}
}

CircleRenderComponent::CircleRenderComponent(std::weak_ptr<Actor> owner, exColor RenderColor, float Radius)
	: RenderComponent(owner, RenderColor), mRadius(Radius)
{
}
