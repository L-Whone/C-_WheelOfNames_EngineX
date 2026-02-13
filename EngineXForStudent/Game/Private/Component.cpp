#include "Game/Public/Component.h"
#include "Game/Public/Actor.h"

Component::~Component()
{
	//TODO
}

std::weak_ptr<Actor> Component::GetOwner() 
{
	return mOwner;
}

Component::Component(std::weak_ptr<Actor> Owner) : mOwner(Owner)
{

}

void Component::BeginPlay()
{
	if (!mOwner.expired()) // if Owner is VALID
	{
		// Cannot gaurentee it exist as a WEAK must convert to a SHARED to see if it still exists 
		// Cannot access functions/properties of a WEAK only UNIQUE and SHARED can access those things
		// std::shared_ptr<Actor> = weak_ptr.lock()

		std::cout << "Component Owner: " << mOwner.lock().get() << std::endl; //LOCK converts WEAK to SHARED for that to access properties

	}
}

void Component::Tick(const float DeltaTime)
{
	//TODO
}

void Component::EndPlay()
{
	//TODO
}

bool Component::CanAddComponent() const
{
	return true;
}