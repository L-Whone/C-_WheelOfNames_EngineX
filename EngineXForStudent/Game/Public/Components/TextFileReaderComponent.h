#pragma once

#include "Game/Public/Component.h"
#include "Engine/Public/EngineTypes.h"
#include <memory>
#include <fstream>
#include <filesystem>

class TextFileReaderComponent : public Component
{
	friend class Actor;

public:

	TextFileReaderComponent() = delete;


	std::shared_ptr<std::vector<std::string>> ReadTextFile();
	bool TextFileUpdated();
	void SetLastWriteTime();

private:
	TextFileReaderComponent(std::weak_ptr<Actor> owner);
	std::string mPath = "names.txt";
	std::filesystem::file_time_type mLastWriteTime;
};
