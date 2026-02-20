#pragma once

#include "Game/Public/Game.h"
#include "Engine/Public/EngineInterface.h"
#include "Engine/Public/SDL.h"

#include "Game/Public/Actors/Ball.h"
#include "Game/Public/Actors/HUD.h"
#include "Game/Public/Actors/SpinningWheel.h"
#include "Game/Public/Components/TextRenderComponent.h"
#include "Game/Public/ComponentTypes.h"
#include "Game/Public/Subsystems/PhysicsSystem.h"
#include "Game/Public/Subsystems/RenderSystem.h"

const char* gWindowName = "PG29 Ken Vi Diana Game Engine";

MyGame::MyGame()
    : mEngine(nullptr)
    , mFontID(-1)
    , mUp(false)
    , mDown(false)
    , mSpinKey(false)
{
}

MyGame::~MyGame()
{
}

void MyGame::Initialize(exEngineInterface* pEngine)
{
    mEngine = pEngine;

    mFontID = mEngine->LoadFont("Resources/Montserrat-Regular.ttf", 32);

    mTextPosition.x = 50.0f;
    mTextPosition.y = 50.0f;

    float Radius = 25.0f;

    exColor White;
    White.mColor[0] = 255;
    White.mColor[1] = 255;
    White.mColor[2] = 255;
    White.mColor[3] = 255;

    exColor Color1;
    Color1.mColor[0] = 255;
    Color1.mColor[1] = 50;
    Color1.mColor[2] = 150;
    Color1.mColor[3] = 255;

    exColor Color2;
    Color2.mColor[0] = 255;
    Color2.mColor[1] = 150;
    Color2.mColor[2] = 150;
    Color2.mColor[3] = 255;

    exColor Color3;
    Color3.mColor[0] = 130;
    Color3.mColor[1] = 170;
    Color3.mColor[2] = 150;
    Color3.mColor[3] = 255;

    exColor Color4;
    Color4.mColor[0] = 100;
    Color4.mColor[1] = 200;
    Color4.mColor[2] = 255;
    Color4.mColor[3] = 255;

    mBall_First = Actor::SpawnActorOfType<Ball>(exVector2(200.0f, 300.0f), Radius, Color1);
    mBall_Second = Actor::SpawnActorOfType<Ball>(exVector2(200.0f, 100.0f), Radius, Color2);

    if (std::shared_ptr<PhysicsComponent> BallPhysicsComp = mBall_Second->GetComponentOfType<PhysicsComponent>())
    {
        BallPhysicsComp->SetVelocity(exVector2(0.0f, 0.5f));
    }

    // Spawn wheel at center screen with radius 200
    mSpinningWheel = Actor::SpawnActorOfType<SpinningWheelActor>(exVector2(500.0f, 300.0f), 200.0f);
    mSpinningWheel->AddSlice("Diana", Color1);
    mSpinningWheel->AddSlice("Ken", Color2);
    mSpinningWheel->AddSlice("Vi", Color3);

    // HUD starts with a prompt to spin
    mHUD = std::make_shared<HUD>(White, String("Press SPACE to spin!"),
        String("Resources/Montserrat-Regular.ttf"), 32,
        exVector2{ 0.0f, 0.0f }, 10);

    mHUD->BeginPlay();
    mHUDText = mHUD->GetComponentOfType<TextRenderComponent>();
}

const char* MyGame::GetWindowName() const
{
    return gWindowName;
}

void MyGame::GetClearColor(exColor& color) const
{
    color.mColor[0] = 128;
    color.mColor[1] = 128;
    color.mColor[2] = 128;
}

void MyGame::OnEvent(SDL_Event* pEvent)
{
}

void MyGame::OnEventsConsumed()
{
    int nKeys = 0;
    const Uint8* pState = SDL_GetKeyboardState(&nKeys);

    mUp = pState[SDL_SCANCODE_UP];
    mDown = pState[SDL_SCANCODE_DOWN];
    mSpinKey = pState[SDL_SCANCODE_SPACE];
}

void MyGame::Run(float fDeltaT)
{
    RENDER_ENGINE.RenderUpdate(mEngine);

    mBall_First->Tick(fDeltaT);
    mBall_Second->Tick(fDeltaT);
    mSpinningWheel->Tick(fDeltaT);

    exVector2 BallVelocity(0.0f, 0.0f);

    if (mUp)
    {
        BallVelocity.y = -2.5f;
    }
    if (mDown)
    {
        BallVelocity.y = 2.5f;
    }

    // Space bar spins the wheel
    if (mSpinKey)
    {
        mSpinningWheel->Spin(360.0f);
        if (mHUDText)
        {
            mHUDText->SetText("Spinning...");
        }
    }

    if (std::shared_ptr<PhysicsComponent> BallPhysicsComp = mBall_First->GetComponentOfType<PhysicsComponent>())
    {
        BallPhysicsComp->SetVelocity(BallVelocity);
    }

    // Once the wheel stops update the HUD with the winner
    if (WheelSlice* Result = mSpinningWheel->GetResult())
    {
        if (mHUDText)
        {
            mHUDText->SetText("Winner: " + Result->mLabel);
        }
    }

    PHYSICS_ENGINE.PhysicsUpdate(fDeltaT);
}