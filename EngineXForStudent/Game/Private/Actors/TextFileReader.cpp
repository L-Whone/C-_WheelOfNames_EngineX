#include "Game/Public/Actors/TextFileReader.h"


TextFileReader::~TextFileReader()
{

}

void TextFileReader::BeginPlay()
{
	AddComponentOfType<TextFileReaderComponent>();
}


