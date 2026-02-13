#pragma once
#include "Game/Public/Components/RenderComponent.h"

class CircleRenderComponent : public RenderComponent
{
	friend class Actor;

public:

	CircleRenderComponent() = delete;

	virtual void Render(exEngineInterface* EngineInterface) override;

protected:

	CircleRenderComponent(std::weak_ptr<Actor> owner, exColor RenderColor, float Radius);

private:
	float mRadius;
};
