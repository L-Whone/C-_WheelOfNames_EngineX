#include "Game/Public/Subsystems/PhysicsSystem.h"
#include "Game/Public/Components/PhysicsComponent.h"

std::unique_ptr<PhysicsEngine> PhysicsEngine::sPhysicsEngine = nullptr;

PhysicsEngine::~PhysicsEngine()
{
	ClearInvalidPhysicsComponents();
}



void PhysicsEngine::AddPhysicsComponent(std::weak_ptr<PhysicsComponent> componentToAdd)
{
	mPhysicsComponents.emplace_back(componentToAdd);
}

void PhysicsEngine::ClearInvalidPhysicsComponents()
{
	if (mPhysicsComponents.empty())
	{
		return;
	}

	mPhysicsComponents.remove_if(
		[](const std::weak_ptr<PhysicsComponent>& component)
		{
			return component.expired();
		});
}

void PhysicsEngine::PhysicsUpdate(const float DeltaTime)
{
	ClearInvalidPhysicsComponents();

	for (size_t index1 = 0; index1 < mPhysicsComponents.size(); ++index1)
	{
		std::list<std::weak_ptr<PhysicsComponent>>::iterator firstPhysicsComponentIt = mPhysicsComponents.begin();
		std::advance(firstPhysicsComponentIt, index1);

		if (!firstPhysicsComponentIt->expired())
		{
			std::shared_ptr<PhysicsComponent> firstPhysicsComponentToCheck = firstPhysicsComponentIt->lock(); //locks converts the weak ptr to a shared ptr

			for (size_t index2 = index1 + 1; index2 < mPhysicsComponents.size(); ++index2)
			{
				std::list<std::weak_ptr<PhysicsComponent>>::iterator secondPhysicsComponentIt = mPhysicsComponents.begin();
				std::advance(secondPhysicsComponentIt, index2);

				if (!secondPhysicsComponentIt->expired())
				{
					std::shared_ptr<PhysicsComponent> secondPhysicsComponentToCheck = secondPhysicsComponentIt->lock();

					if (firstPhysicsComponentToCheck->IsCollisionDetected(*secondPhysicsComponentIt))
					{
						// # TODO: Change the hitLocation and change the placeholder of the Broadcast
						firstPhysicsComponentToCheck->BroadcastCollisionEvents(secondPhysicsComponentToCheck->GetOwner(), { 0.0f, 0.0f });
						secondPhysicsComponentToCheck->BroadcastCollisionEvents(firstPhysicsComponentToCheck->GetOwner(), { 0.0f, 0.0f });

						secondPhysicsComponentToCheck->CollisionResolution();
					}
				}
			}

			firstPhysicsComponentToCheck->DoPhysics();
		}
	}
}

PhysicsEngine::PhysicsEngine()
{

}
