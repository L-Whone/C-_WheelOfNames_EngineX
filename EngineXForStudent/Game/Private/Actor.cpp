#include "Game/Public/Actor.h"

Actor::Actor()
{
	// TODO
}

Actor::~Actor()
{
	// TODO
}

void Actor::BeginPlay()
{
	// TODO
}

void Actor::EndPlay()
{
	// TODO
}

void Actor::Tick(float DeltaSeconds)
{
	for (std::shared_ptr<Component> ComponentIt : mComponents)
	{
		ComponentIt->Tick(DeltaSeconds);
	}
	// TODO
}

void Actor::Render(exEngineInterface* EngineInterface)
{
	// TODO
}
