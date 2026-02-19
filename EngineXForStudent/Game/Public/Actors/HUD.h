#pragma once
#include "Game/Public/Actor.h"
#include "Engine/Public/EngineTypes.h"

class HUD : public Actor
{
public:
    HUD(exColor HUDColor, const String& Text, const String& FontPath, int PtSize, exVector2 Offset = { 0.0f, 0.0f }, int Layer = 1);

    void Render(exEngineInterface* EngineInterface) override;

    virtual void BeginPlay() override;

private:

    exColor mColor;
    String mText;
    String mFontPath;
    int mPtSize;
    exVector2 mOffset;
    int mLayer;
};