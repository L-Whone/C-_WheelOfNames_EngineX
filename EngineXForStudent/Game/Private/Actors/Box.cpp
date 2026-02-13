#include "Game/Public/Actors/Box.h"

Box::Box(float Height, float Width, exColor BallColor)
{
	mHeight = Height;
	mWidth = Width;
	mColor = BallColor;
}

void Box::Render(exEngineInterface* EngineInterface)
{
	if (EngineInterface)
	{
		GetComponentOfType<RectangleRenderComponent>()->Render(EngineInterface);
	}
}

void Box::BeginPlay()
{
	AddComponentOfType<RectangleRenderComponent>(mColor, mHeight, mWidth);
}
