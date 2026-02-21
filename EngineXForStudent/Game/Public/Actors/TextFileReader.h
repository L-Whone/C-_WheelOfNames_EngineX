#pragma once
#include "Game/Public/Actor.h"
#include "Engine/Public/EngineTypes.h"
#include "Game/Public/Components/TextFileReaderComponent.h"

class TextFileReader : public Actor
{
public:
	~TextFileReader();

	virtual void BeginPlay() override;

private:
	TextFileReader();
};