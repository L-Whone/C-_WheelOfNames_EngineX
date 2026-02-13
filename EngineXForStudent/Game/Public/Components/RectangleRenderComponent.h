#pragma once
#include "Game/Public/Components/RenderComponent.h"

class RectangleRenderComponent : public RenderComponent
{
	friend class Actor;

public:

	RectangleRenderComponent() = delete;

	virtual void Render(exEngineInterface* EngineInterface) override;

protected:

	RectangleRenderComponent(std::weak_ptr<Actor> owner, exColor RenderColor, float Height, float Width);

private:
	float mHeight;
	float mWidth;
};
