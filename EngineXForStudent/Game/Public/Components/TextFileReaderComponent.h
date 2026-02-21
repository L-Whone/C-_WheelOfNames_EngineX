#pragma once

#include "Game/Public/Component.h"
#include "Engine/Public/EngineTypes.h"
#include <memory>
#include <fstream>

class TextFileReaderComponent : public Component
{
	friend class Actor;

public:

	TextFileReaderComponent() = delete;

	// Getter Setters

	std::shared_ptr<std::vector<std::string>> ReadTextFile();

private:
};
