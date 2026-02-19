#include "Game/Public/Components/TextRenderComponent.h"
#include "Engine/Public/EngineInterface.h"
#include "Game/Public/Actor.h"
#include "Game/Public/Components/TransformComponent.h"

void TextRenderComponent::Render(exEngineInterface* EngineInterface)
{
    if (!EngineInterface) return;

    if (mFontID < 0 && !mFontPath.empty())  mFontID = EngineInterface->LoadFont(mFontPath.c_str(), mPtSize);

    if (mFontID < 0) return;
    if (mText.empty()) return;

    exVector2 TextPos = { 0.0f, 0.0f };

    if (!mOwner.expired())
    {
        if (std::shared_ptr<Actor> owner = mOwner.lock())
        {
            if (std::shared_ptr<TransformComponent> TransformComp = owner->GetComponentOfType<TransformComponent>())
            {
                TextPos = TransformComp->GetLocation();
            }
        }
    }

    TextPos.x += mOffset.x;
    TextPos.y += mOffset.y;

    EngineInterface->DrawText(mFontID, TextPos, mText.c_str(), mRenderColor, mLayer);
}

TextRenderComponent::TextRenderComponent(std::weak_ptr<Actor> owner, exColor RenderColor, const String& Text,
    const String& FontPath, int PtSize, exVector2 Offset, int Layer)
    : RenderComponent(owner, RenderColor), mText(Text), mFontPath(FontPath), mPtSize(PtSize), mOffset(Offset), mLayer(Layer)
{
}