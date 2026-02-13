#include "Game/Public/Components/TransformComponent.h"

exVector2 TransformComponent::GetLocation() const
{
    return mLocation;
}

void TransformComponent::SetLocation(const exVector2 InValue)
{
    mLocation = InValue;
}

TransformComponent::TransformComponent(std::weak_ptr<Actor> owner, exVector2 location) :
    Component(owner),
    mLocation(location)
{
}
