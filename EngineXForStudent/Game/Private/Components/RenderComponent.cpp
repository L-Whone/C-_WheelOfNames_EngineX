#include "Game/Public/Components/RenderComponent.h"

void RenderComponent::Render(exEngineInterface* EngineInterface)
{

}
void RenderComponent::BeginPlay()
{
	Component::BeginPlay();

	RENDER_ENGINE.AddRenderComponent(weak_from_this()); // You can only use this if you have the "enable_share_from_this"
}
void RenderComponent::SetColor(exColor newColor)
{
	mRenderColor = newColor;
}
RenderComponent::RenderComponent(std::weak_ptr<Actor> owner, exColor RenderColor)
	: Component(owner), mRenderColor(RenderColor)
{

}
