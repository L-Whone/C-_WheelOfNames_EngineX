#pragma once
#include "Game/Public/Component.h"
#include "Engine/Public/EngineTypes.h"
#include "Game/Public/Subsystems/RenderSystem.h"

class exEngineInterface;

class RenderComponent : public Component, public std::enable_shared_from_this<RenderComponent>
{
	friend class Actor;

public:

	RenderComponent() = delete;

	virtual void Render(exEngineInterface* EngineInterface);

	virtual void BeginPlay() override;

	void SetColor(exColor newColor);

protected:

	RenderComponent(std::weak_ptr<Actor> owner, exColor RenderColor);
	exColor mRenderColor;
};
