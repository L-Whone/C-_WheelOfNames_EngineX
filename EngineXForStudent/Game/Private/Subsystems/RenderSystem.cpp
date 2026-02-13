#include "Game/Public/Subsystems/RenderSystem.h"
#include "Game/Public/Components/RenderComponent.h"

std::unique_ptr<RenderEngine> RenderEngine::sRenderEngine = nullptr;


RenderEngine::~RenderEngine()
{
	ClearInvalidRenderComponents();
}

void RenderEngine::AddRenderComponent(std::weak_ptr<RenderComponent> componentToAdd)
{
	mRenderComponents.emplace_back(componentToAdd);
}

void RenderEngine::ClearInvalidRenderComponents()
{
	if (mRenderComponents.empty())
	{
		return;
	}

	mRenderComponents.remove_if(
		[](const std::weak_ptr<RenderComponent>& component)
		{
			return component.expired();
		});
}

void RenderEngine::RenderUpdate(exEngineInterface* RenderInterface)
{
	ClearInvalidRenderComponents();

	for (std::weak_ptr<RenderComponent> RenderComponent : mRenderComponents)
	{
		if (!RenderComponent.expired())
		{
			RenderComponent.lock()->Render(RenderInterface);
		}
	}
}

RenderEngine::RenderEngine()
{

}
