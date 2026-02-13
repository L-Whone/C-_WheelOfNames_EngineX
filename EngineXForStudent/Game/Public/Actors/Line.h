#pragma once
#include "Game/Public/Actor.h"
#include "Engine/Public/EngineTypes.h"

class Line : public Actor
{
public:
	Line(exVector2 Point1, exVector2 Point2, exColor LineColor);

	void Render(exEngineInterface* EngineInterface) override;

	virtual void BeginPlay() override;
private:

	exVector2 mPoint1;
	exVector2 mPoint2;
	exColor mColor;
};
