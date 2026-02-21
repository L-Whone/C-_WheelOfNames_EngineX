#include "Game/Public/Components/TextFileReaderComponent.h"

std::shared_ptr<std::vector<std::string>> TextFileReaderComponent::ReadTextFile()
{
	auto nameList = std::make_shared<std::vector<std::string>>();

	std::ifstream file("./names.txt");

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

TextFileReaderComponent::TextFileReaderComponent(std::weak_ptr<Actor> owner) : Component(owner)
{

}
