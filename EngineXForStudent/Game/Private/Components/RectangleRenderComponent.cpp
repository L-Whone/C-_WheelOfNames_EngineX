#include "Game/Public/Components/RectangleRenderComponent.h"
#include "Engine/Public/EngineInterface.h"
#include "Game/Public/Actor.h"
#include "Game/Public/Components/TransformComponent.h"

void RectangleRenderComponent::Render(exEngineInterface* EngineInterface)
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
					exVector2 TopLeftCorner = { CenterPos.x - mWidth / 2, CenterPos.y - mHeight / 2 };
					exVector2 BottomRightCorner = { CenterPos.x + mWidth / 2, CenterPos.y + mHeight / 2 };
					EngineInterface->DrawBox(TopLeftCorner, BottomRightCorner, mRenderColor, 0);
				}
			}
		}
	}
}

RectangleRenderComponent::RectangleRenderComponent(std::weak_ptr<Actor> owner, exColor RenderColor, float Height, float Width)
	: RenderComponent(owner, RenderColor), mHeight(Height), mWidth(Width)
{
}
