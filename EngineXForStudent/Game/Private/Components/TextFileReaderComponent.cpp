#include "Game/Public/Components/TextFileReaderComponent.h"

std::shared_ptr<std::vector<std::string>> TextFileReaderComponent::ReadTextFile()
{
	auto nameList = std::make_shared<std::vector<std::string>>();

	std::ifstream file("./"+mPath);

	if (!file.is_open())
	{
		std::cout << "Failed to open names.txt" << std::endl;
		return nullptr;
	}

	std::string name;

	while (file >> name)
	{
		nameList->emplace_back(name);
	}

	file.close();

	return nameList;
}

bool TextFileReaderComponent::TextFileUpdated()
{
	std::filesystem::file_time_type latestWriteTime = std::filesystem::last_write_time(mPath);

	if (latestWriteTime != mLastWriteTime)
	{
		mLastWriteTime = latestWriteTime;
		return true;
	}
	return false;
}

void TextFileReaderComponent::SetLastWriteTime()
{
	mLastWriteTime = std::filesystem::last_write_time(mPath);
}

TextFileReaderComponent::TextFileReaderComponent(std::weak_ptr<Actor> owner) : Component(owner)
{

}

