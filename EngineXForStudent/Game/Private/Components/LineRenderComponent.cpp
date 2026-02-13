#include "Game/Public/Components/LineRenderComponent.h"
#include "Engine/Public/EngineInterface.h"
#include "Game/Public/Actor.h"
#include "Game/Public/Components/TransformComponent.h"

void LineRenderComponent::Render(exEngineInterface* EngineInterface)
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
					EngineInterface->DrawLine(mPoint1, mPoint2, mRenderColor, 0);
				}
			}
		}
	}
}

LineRenderComponent::LineRenderComponent(std::weak_ptr<Actor> owner, exColor RenderColor, exVector2 Point1, exVector2 Point2)
	: RenderComponent(owner, RenderColor), mPoint1(Point1), mPoint2(Point2)
{

}