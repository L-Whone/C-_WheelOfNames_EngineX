#include "Game/Public/Actors/Ball.h"
#include "Game/Public/Components/TransformComponent.h"
#include "Game/Public/Components/CircleRenderComponent.h"
#include "Game/public/Components/CircleColliderComponent.h"
#include "Game/Public/Utils.h"

Ball::Ball(float BallRadius, exColor BallColor )
{
	mRadius = BallRadius;
	mColor = BallColor;
}

void Ball::Render(exEngineInterface* EngineInterface)
{
	if (EngineInterface)
	{
		// allows us to find component of type
		if (std::shared_ptr<TransformComponent> TransformComp = GetComponentOfType<TransformComponent>())
		{
			EngineInterface->DrawCircle(TransformComp->GetLocation(), mRadius, mColor, 2);
		}
	}
}

void Ball::BeginPlay()
{
	AddComponentOfType<CircleRenderComponent>(mColor, mRadius);
	std::tuple<std::shared_ptr<CircleColliderComponent>, bool, String> ResultCircleCollider = AddComponentOfType<CircleColliderComponent>(mRadius); 

	if (std::shared_ptr<CircleColliderComponent> CircleColliderComp = std::get<0>(ResultCircleCollider))
	{
		CollisionEventSignature CollisionDelegate = std::bind(&Ball::OnCollision, this, std::placeholders::_1, std::placeholders::_2);
		CircleColliderComp->ListenForCollision(CollisionDelegate);
	}
}

void Ball::OnCollision(std::weak_ptr<Actor>, const exVector2)
{
	if (std::shared_ptr<RenderComponent> RenderComp = GetComponentOfType<RenderComponent>())
	{
		exColor Color2;
		Color2.mColor[0] = 20;
		Color2.mColor[1] = 255;
		Color2.mColor[2] = 150;
		Color2.mColor[3] = 255;
		RenderComp->SetColor(Color2);
	}
}
