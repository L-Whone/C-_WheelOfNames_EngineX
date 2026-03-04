#include "Game/Public/Components/WinnerPopupComponent.h"
#include "Game/Public/Actor.h"
#include "Game/Public/Components/RenderComponent.h"      
#include "Game/Public/Components/TextRenderComponent.h" 
#include "Game/Public/Components/RectangleRenderComponent.h"

exColor WinnerPopup::MakeColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
    exColor c;
    c.mColor[0] = r;
    c.mColor[1] = g;
    c.mColor[2] = b;
    c.mColor[3] = a;
    return c;
}

void WinnerPopup::Show(const String& title, const String& name, const exColor& headerColor)
{
    const exVector2 center = { kViewportWidth * 0.5f, kViewportHeight * 0.5f };

    const float modalW = 700.0f;
    const float modalH = 260.0f;
    const float headerH = 70.0f;

    const exColor white = MakeColor(255, 255, 255, 255);
    const exColor bodyColor = MakeColor(30, 30, 30, 255);
    const exColor titleTextColor = MakeColor(15, 15, 15, 255);
    const exColor nameTextColor = MakeColor(255, 255, 255, 255);

    if (!mBody)
    {
        // Border
        mBorder = Actor::SpawnActorOfType<Actor>(center);
        mBorder->AddComponentOfType<RectangleRenderComponent>(white, modalH + 8.0f, modalW + 8.0f);

        // Body
        mBody = Actor::SpawnActorOfType<Actor>(center);
        mBody->AddComponentOfType<RectangleRenderComponent>(bodyColor, modalH, modalW);

        // Header
        const float headerCenterY = center.y - (modalH * 0.5f) + (headerH * 0.5f);
        mHeader = Actor::SpawnActorOfType<Actor>({ center.x, headerCenterY });
        mHeader->AddComponentOfType<RectangleRenderComponent>(headerColor, headerH, modalW);

        mTextActor = Actor::SpawnActorOfType<Actor>(center);

        // Header text
        {
            auto [comp, ok, msg] = mTextActor->AddComponentOfType<TextRenderComponent>(
                titleTextColor,
                title,
                String("Resources/Montserrat-Regular.ttf"),
                28,
                exVector2{ -modalW * 0.5f + 18.0f, -modalH * 0.5f + 18.0f },
                2
            );
            mTitleText = comp;
        }

        // Winer name text
        {
            auto [comp, ok, msg] = mTextActor->AddComponentOfType<TextRenderComponent>(
                nameTextColor,
                name,
                String("Resources/Montserrat-Regular.ttf"),
                64,
                exVector2{ -120.0f, -10.0f },
                2
            );
            mNameText = comp;
        }
    }

    if (mHeader)
    {
        if (auto rect = mHeader->GetComponentOfType<RectangleRenderComponent>())
            rect->SetColor(headerColor);
    }
    if (mTitleText) mTitleText->SetText(title);
    if (mNameText)  mNameText->SetText(name);

    mVisible = true;
}

void WinnerPopup::Hide()
{
    mTitleText.reset();
    mNameText.reset();

    mTextActor.reset();
    mHeader.reset();
    mBody.reset();
    mBorder.reset();

    mVisible = false;
}
