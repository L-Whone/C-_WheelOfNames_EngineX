#pragma once
#include "Game/Public/Utils.h"
#include "Game/Public/LIfetimeInterface.h"

class Actor;

class Component : public ILifetimeInterface
{
	friend Actor; // only actors can make components

public:

	Component() = delete; // factory pattern another class is able to construct you
	virtual ~Component();

	std::weak_ptr<Actor> GetOwner();

protected:

	Component(std::weak_ptr<Actor> Owner);

	// Inherited from ILifetimeInterface
	virtual void BeginPlay() override;
	virtual void Tick(const float DeltaTime) override;
	virtual void EndPlay() override;
	// End ILifetimeInterface

	virtual bool CanAddComponent() const; // IF logic | If I can add this component to a class | Can override for specific scenarios

	std::weak_ptr<Actor> mOwner; // Components is only alive if the Actor is alive  | We don't want components to keep Actor's alive
								 // Shared_ptr would keep the Actor alive unless we kill the component first
};

using ComponentList = std::list<std::shared_ptr<Component>>; // TypeDef for a list of Components