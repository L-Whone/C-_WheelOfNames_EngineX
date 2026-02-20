#include "Game/Public/Actors/SpinningWheel.h"
#include "Game/Public/Utils.h"
#include "Game/Public/Components/CircleRenderComponent.h"
#include "Game/Public/Components/LineRenderComponent.h"
#include "Game/Public/Components/TextRenderComponent.h"
#include "Game/Public/Components/TransformComponent.h"
#include <cmath>

static constexpr float PI = 3.14159265f;
static constexpr float DEG_TO_RAD = PI / 180.0f;
static constexpr float TEXT_RADIUS_MULT = 0.6f;
static constexpr float VELOCITY_THRESHOLD = 0.5f;

SpinningWheelActor::SpinningWheelActor(float Radius)
    : Actor(), mRadius(Radius)
{
}

void SpinningWheelActor::BeginPlay()
{
    Actor::BeginPlay();

    // colour of circle
    exColor White;
    White.mColor[0] = 255;
    White.mColor[1] = 255;
    White.mColor[2] = 255;
    White.mColor[3] = 255;
    
    // add circle component
    auto [CircleComp, CircleSuccess, CircleMsg] = AddComponentOfType<CircleRenderComponent>(White, mRadius);
    if (CircleSuccess)
    {
        mCircleComp = CircleComp;
    }

    // colour of ticker
    exColor TickerColor;
    TickerColor.mColor[0] = 255;
    TickerColor.mColor[1] = 0;
    TickerColor.mColor[2] = 0;
    TickerColor.mColor[3] = 255;

    // add tickerr cimponent
    auto [TickerComp, TickerSuccess, TickerMsg] = AddComponentOfType<LineRenderComponent>(
        TickerColor,
        exVector2{ 0.0f, 0.0f },
        exVector2{ 0.0f, 0.0f },
        2
    );
    if (TickerSuccess)
    {
        mTickerComp = TickerComp;
    }

    //position ticker
    UpdateTickerPosition();
}

void SpinningWheelActor::AddSlice(const String& Label, exColor SliceColor)
{
    WheelSlice NewSlice;
    NewSlice.mLabel = Label;

    auto [LineComp, LineSuccess, LineMsg] = AddComponentOfType<LineRenderComponent>(
        SliceColor,
        exVector2{ 0.0f, 0.0f },
        exVector2{ 0.0f, 0.0f },
        1
    );
    if (LineSuccess)
    {
        NewSlice.mLineComp = LineComp;
    }

    auto [TextComp, TextSuccess, TextMsg] = AddComponentOfType<TextRenderComponent>(
        SliceColor,
        Label, "Resources/Montserrat-Regular.ttf", 14,
        exVector2{ 0.0f, 0.0f }, 2
    );
    if (TextSuccess)
    {
        NewSlice.mTextComp = TextComp;
    }

    mSlices.push_back(NewSlice);
    RecalculateSlices();
    UpdateComponentPositions();
}

void SpinningWheelActor::RecalculateSlices()
{
    if (mSlices.empty()) return;

    // angle of each slice
    float SliceAngle = 360.0f / static_cast<float>(mSlices.size());

    // set angles for each slice
    for (int i = 0; i < static_cast<int>(mSlices.size()); i++)
    {
        // angle of each slice * index
        mSlices[i].mStartAngle = SliceAngle * i;
        // angle of each slice * (index + 1)
        mSlices[i].mEndAngle = SliceAngle * (i + 1);
        // angle of each slice + have the slice angle
        mSlices[i].mMidAngle = mSlices[i].mStartAngle + (SliceAngle * 0.5f);
    }
}

exVector2 SpinningWheelActor::AngleToPoint(float AngleDegrees, float Radius)
{
    exVector2 Center = { 0.0f, 0.0f };
    if (auto TransformComp = GetComponentOfType<TransformComponent>())
    {
        Center = TransformComp->GetLocation();
    }

    float Radians = AngleDegrees * DEG_TO_RAD;
    return exVector2
    {
        // ad the wheel center to the (unit circle position * radius of circle)
        Center.x + (std::cos(Radians) * Radius),
        Center.y + (std::sin(Radians) * Radius)
    };
}
// get world position
// find position on unit cirlce with angle (radians of angle to find)
// add the radius of the wheel circle to the normalized position
// add the world position to the sum

float SpinningWheelActor::NormalizeAngle(float Angle)
{
    while (Angle >= 360.0f) Angle -= 360.0f;
    while (Angle < 0.0f)    Angle += 360.0f;
    return Angle;
    // normalizes angle
}

void SpinningWheelActor::UpdateTickerPosition()
{
    exVector2 TickerStart = AngleToPoint(mPointerAngle, mRadius + 20.0f);
    exVector2 TickerEnd = AngleToPoint(mPointerAngle, mRadius * 0.75f);

    if (auto TickerComp = mTickerComp.lock())
    {
        TickerComp->SetStart(TickerStart);
        TickerComp->SetEnd(TickerEnd);
    }
}

void SpinningWheelActor::UpdateComponentPositions()
{
    // center of wheel
    exVector2 Center = { 0.0f, 0.0f };
    if (auto TransformComp = GetComponentOfType<TransformComponent>())
    {
        Center = TransformComp->GetLocation();
    }

    for (auto& Slice : mSlices)
    {
        // find 
        float BoundaryAngle = NormalizeAngle(Slice.mStartAngle + mRotationOffset);
        exVector2 LineEnd = AngleToPoint(BoundaryAngle, mRadius);

        if (auto LineComp = Slice.mLineComp.lock())
        {
            LineComp->SetStart(Center);
            LineComp->SetEnd(LineEnd);
        }

        float TextAngle = NormalizeAngle(Slice.mMidAngle + mRotationOffset);
        exVector2 TextPoint = AngleToPoint(TextAngle, mRadius * TEXT_RADIUS_MULT);

        if (auto TextComp = Slice.mTextComp.lock())
        {
            TextComp->SetOffset(exVector2
                {
                    TextPoint.x - Center.x,
                    TextPoint.y - Center.y
                });
        }
    }
}

void SpinningWheelActor::Spin(float InitialVelocity)
{
    // set the velocity of the wheel
    mSpinVelocity = InitialVelocity;
    mIsSpinning = true;
}

void SpinningWheelActor::Tick(float DeltaTime)
{
    UpdateTickerPosition();

    if (mIsSpinning)
    {
        // add friction
        mSpinVelocity *= mDamping;
        // add current roation offsset + velocity + time since last frame
        mRotationOffset = NormalizeAngle(mRotationOffset + mSpinVelocity * DeltaTime);

        // if the velocity is less than the threshold, stop spinning
        if (std::abs(mSpinVelocity) < VELOCITY_THRESHOLD)
        {
            mSpinVelocity = 0.0f;
            mIsSpinning = false;
        }

        UpdateComponentPositions();
    }
}

WheelSlice* SpinningWheelActor::GetResult()
{
    if (mIsSpinning) return nullptr;

    for (auto& Slice : mSlices)
    {
        float Start = NormalizeAngle(Slice.mStartAngle + mRotationOffset);
        float End = NormalizeAngle(Slice.mEndAngle + mRotationOffset);

        if (Start <= End)
        {
            if (mPointerAngle >= Start && mPointerAngle < End)
                return &Slice;
        }
        else
        {
            if (mPointerAngle >= Start || mPointerAngle < End)
                return &Slice;
        }
    }

    return nullptr;
}