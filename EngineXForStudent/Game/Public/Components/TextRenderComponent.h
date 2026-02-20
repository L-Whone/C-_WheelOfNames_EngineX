#pragma once
#include "Game/Public/Components/RenderComponent.h"

class TextRenderComponent : public RenderComponent
{
    friend class Actor;
public:
    TextRenderComponent() = delete;
    virtual void Render(exEngineInterface* EngineInterface) override;

    void SetText(const String& NewText) { mText = NewText; }
    const String& GetText() const { return mText; }
    void SetOffset(exVector2 Offset) { mOffset = Offset; }

protected:
    TextRenderComponent(std::weak_ptr<Actor> owner, exColor RenderColor, const String& Text,
        const String& FontPath, int PtSize, exVector2 Offset = { 0.0f, 0.0f }, int Layer = 1);
private:
    String    mText;
    String    mFontPath;
    int       mPtSize = 16;
    int       mFontID = -1;
    exVector2 mOffset = { 0.0f, 0.0f };
    int       mLayer = 1;
};