#include "Game/Public/Actors/Line.h"
#include "Game/Public/Components/TransformComponent.h"
#include "Game/Public/Components/LineRenderComponent.h"
#include "Game/Public/Utils.h"

Line::Line(exVector2 Point1, exVector2 Point2, exColor LineColor)
{
	mPoint1 = Point1;
	mPoint2 = Point2;
	mColor = LineColor;
}

void Line::Render(exEngineInterface* EngineInterface)
{
	if (EngineInterface)
	{
		// allows us to find component of type
		if (std::shared_ptr<TransformComponent> TransformComp = GetComponentOfType<TransformComponent>())
		{
			EngineInterface->DrawLine(mPoint1, mPoint2, mColor, 0);
		}
	}
}

void Line::BeginPlay()
{
	AddComponentOfType<LineRenderComponent>(mColor, mPoint1, mPoint2);
}
