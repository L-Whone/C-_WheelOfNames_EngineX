#pragma once
#include "Game/Public/Component.h"
#include "Engine/Public/EngineTypes.h"

class TransformComponent : public Component
{
	friend class Actor;

public :

	TransformComponent() = delete;

	// Getter Setters

	exVector2 GetLocation() const;
	void SetLocation(const exVector2 InValue);

protected:

	TransformComponent(std::weak_ptr<Actor> owner, exVector2 location);

private:
	exVector2 mLocation;
};
