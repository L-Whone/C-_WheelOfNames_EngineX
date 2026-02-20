#pragma once
#include "Game/Public/Utils.h"
#include "Game/Public/Actor.h"
#include "Game/Public/Actors/WheelSlice.h"
#include <vector>

class CircleRenderComponent;
class LineRenderComponent;

class SpinningWheelActor : public Actor
{
public:
    SpinningWheelActor() = delete;
    SpinningWheelActor(float Radius);

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

    void AddSlice(const String& Label, exColor SliceColor);
    void Spin(float InitialVelocity);
    WheelSlice* GetResult();

private:
    void RecalculateSlices();
    void UpdateComponentPositions();
    void UpdateTickerPosition();
    exVector2 AngleToPoint(float AngleDegrees, float Radius);
    float NormalizeAngle(float Angle);

    std::vector<WheelSlice>               mSlices;
    std::weak_ptr<CircleRenderComponent>  mCircleComp;
    std::weak_ptr<LineRenderComponent>    mTickerComp;

    float mRotationOffset = 0.0f;
    float mSpinVelocity = 0.0f;
    float mDamping = 0.98f;
    float mRadius = 0.0f;
    float mPointerAngle = 90.0f;
    bool  mIsSpinning = false;
};

// add slice
// spin thing
// Get rsult of spion
// Calculate slices
// create a ticker to show the winning position
// get the angle of the winning to a point
// normalize angels to 0-360 range FOR MY FUCKING BAINR
// List of slices
// Ptr to the circle backdrop
// ptr to ticker render

// velocity of spin
// friction
// radius of ciircle
// the angle where the pointer is stored
// if spinning