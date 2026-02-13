#pragma once
#include "Game/Public/Actor.h"
#include "Engine/Public/EngineTypes.h"

class Ball : public Actor
{
public:
	Ball(float BallRadius, exColor BallColor);

	void Render(exEngineInterface* EngineInterface) override;

	virtual void BeginPlay() override;

	void OnCollision(std::weak_ptr<Actor>, const exVector2);

private:

	float mRadius;
	exColor mColor;

};