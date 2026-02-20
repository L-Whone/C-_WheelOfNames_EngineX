#pragma once
#include "Game/Public/Utils.h"
#include "Game/Public/Components/LineRenderComponent.h"
#include "Game/Public/Components/TextRenderComponent.h"
#include <memory>

struct WheelSlice
{
    String mLabel;
    float mStartAngle;
    float mEndAngle;
    float mMidAngle;
    std::weak_ptr<LineRenderComponent> mLineComp;
    std::weak_ptr<TextRenderComponent> mTextComp;
};