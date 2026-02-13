#pragma once
#include <type_traits>
#include <memory>
#include "Game/Public/LifetimeInterface.h"
#include "Engine/Public/EngineInterface.h"
#include "Game/Public/ComponentTypes.h"

class Actor : public ILifetimeInterface, public std::enable_shared_from_this<Actor>
{
public:
	Actor();
	virtual ~Actor();

	#pragma region ILifetimeInterface
	virtual void BeginPlay() override;
	virtual void EndPlay() override ;
	virtual void Tick(float DeltaSeconds) override;
	#pragma endregion
	
	virtual void Render(exEngineInterface* EngineInterface);

private:
	// Stores all of the components
	ComponentList mComponents; 

#pragma region TemplateRegion
public:

	template<std::derived_from<Actor> ActorType, typename ...Args>
	static std::shared_ptr<ActorType> SpawnActorOfType(exVector2 SpawnLocation, Args... Arguments)
	{
		std::shared_ptr<ActorType> SpawnedActor = std::make_shared<ActorType>(Arguments...);
		SpawnedActor->BeginPlay();
		SpawnedActor->AddComponentOfType<TransformComponent>(SpawnLocation);

		return SpawnedActor;
	}

	template<std::derived_from<Component> ComponentType, typename ...Args> // Variatics (arbitrary number of arguments
	std::tuple<std::shared_ptr<ComponentType>, bool, String> AddComponentOfType(Args... Arguments) // tuple can take in more than 2 values
	{
		ComponentType* ComponentPtr = new ComponentType(weak_from_this(), Arguments...);
		std::shared_ptr<ComponentType> NewComponent = std::make_shared<ComponentType>(*ComponentPtr); //weak_from_this returns a weak_ptr of this class
		delete ComponentPtr;

		if (NewComponent->CanAddComponent())
		{
			NewComponent->BeginPlay();
			mComponents.emplace_back(NewComponent);
			return { NewComponent, true, "Component was created SUCCESSFULLY" };
		}
		
		return { nullptr, false, "FAILED to add component" };
	} // tuple is quick way to return multiple values

	template<std::derived_from<Component> ComponentType>
	std::shared_ptr<ComponentType> GetComponentOfType()
	{
		for (std::shared_ptr<Component> ComponentIterator : mComponents)
		{
			if (std::shared_ptr<ComponentType> FoundComponent = std::dynamic_pointer_cast<ComponentType>(ComponentIterator))
			{
				return FoundComponent;
			}
		}
		
		return nullptr;
	}
	
	// Write Function to spawn Actor with a Transform Comp
#pragma endregion
};

