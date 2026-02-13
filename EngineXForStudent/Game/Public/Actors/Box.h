#pragma once
#include "Game/Public/Actor.h"
#include "Engine/Public/EngineTypes.h"
#include "Game/Public/Components/RectangleRenderComponent.h"

class Box : public Actor
{
public:
	Box(float Height, float Width, exColor BallColor);

	void Render(exEngineInterface* EngineInterface) override;

	virtual void BeginPlay() override;
private:

	float mHeight;
	float mWidth;
	exColor mColor;

};