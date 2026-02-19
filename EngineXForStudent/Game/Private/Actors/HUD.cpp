#include "Game/Public/Actors/HUD.h"
#include "Game/Public/Utils.h"
#include "Game/Public/Components/TextRenderComponent.h"
#include "Game/Public/Components/TransformComponent.h"

HUD::HUD(exColor HUDColor, const String& Text, const String& FontPath, int PtSize, exVector2 Offset, int Layer)
{
    mColor = HUDColor;
    mText = Text;
    mFontPath = FontPath;
    mPtSize = PtSize;
    mOffset = Offset;
    mLayer = Layer;
}

void HUD::Render(exEngineInterface* EngineInterface)
{
    if (EngineInterface)
    {
        if (auto text = GetComponentOfType<TextRenderComponent>())
        {
            text->Render(EngineInterface);
        }
    }
}

void HUD::BeginPlay()
{
    Actor::BeginPlay();

    AddComponentOfType<TransformComponent>(mOffset);
    AddComponentOfType<TextRenderComponent>(mColor, mText, mFontPath, mPtSize, mOffset, mLayer);
}
