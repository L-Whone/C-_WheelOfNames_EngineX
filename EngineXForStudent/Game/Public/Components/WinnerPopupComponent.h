#pragma once
#include <memory>
#include "Game/Public/Utils.h"
#include "Engine/Public/EngineTypes.h"
#include "Engine/Public/EngineInterface.h"

class Actor;
class TextRenderComponent;

class WinnerPopup
{
public:
    WinnerPopup() = default;

    void Show(const String& title, const String& name, const exColor& headerColor);

    void Hide();

    bool IsVisible() const { return mVisible; }

private:
    bool mVisible = false;

    std::shared_ptr<Actor> mBorder;
    std::shared_ptr<Actor> mBody;
    std::shared_ptr<Actor> mHeader;
    std::shared_ptr<Actor> mTextActor;

    std::shared_ptr<TextRenderComponent> mTitleText;
    std::shared_ptr<TextRenderComponent> mNameText;

private:
    static exColor MakeColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255);
};
