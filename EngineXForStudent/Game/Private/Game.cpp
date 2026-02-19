//
// * ENGINE-X
// * SAMPLE GAME
//
// + Game.cpp
// implementation of MyGame, an implementation of exGameInterface
//
#pragma once

#include "Game/Public/Game.h"
#include "Engine/Public/EngineInterface.h"
#include "Engine/Public/SDL.h"

#include "Game/Public/Actors/Ball.h"
#include "Game/Public/Actors/HUD.h"
#include "Game/Public/Components/TextRenderComponent.h"
#include "Game/Public/ComponentTypes.h"
#include "Game/Public/Subsystems/PhysicsSystem.h"
#include "Game/Public/Subsystems/RenderSystem.h"

//-----------------------------------------------------------------
//-----------------------------------------------------------------

const char* gWindowName = "PG29 Ken Vi Diana Game Engine"; // What the window is called

//-----------------------------------------------------------------
//-----------------------------------------------------------------

MyGame::MyGame()
	: mEngine(nullptr) // Rendering
	, mFontID(-1)
	, mUp(false)
	, mDown(false)
{
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

MyGame::~MyGame()
{
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

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

	mBall_First = std::make_shared<Ball>(Radius, Color1);
	mBall_First = Actor::SpawnActorOfType<Ball>(exVector2(200.0f, 300.0f), Radius, Color1);

	mBall_Second = Actor::SpawnActorOfType<Ball>(exVector2(200.0f, 100.0f), Radius, Color2);

	//mBox = Actor::SpawnActorOfType<Box>(exVector2(500.0f,200.0f),200.0f, 300.0f, Color3);

	if (std::shared_ptr<PhysicsComponent> BallPhysicsComp = mBall_Second->GetComponentOfType<PhysicsComponent>())
	{
		BallPhysicsComp->SetVelocity(exVector2(0.0f, 0.5f));
	}

	mHUD = std::make_shared<HUD>(White, String("Score: 0"), String("Resources/Montserrat-Regular.ttf"),
		32, exVector2{ 0.0f, 0.0f }, 10);

	mHUD->BeginPlay();
	mHUDText = mHUD->GetComponentOfType<TextRenderComponent>();

	exColor header; 
	header.mColor[0] = 130;
	header.mColor[1] = 170;
	header.mColor[2] = 150;
	header.mColor[3] = 255;

	mWinnerPopup.Show("We have a winner!", "Diana", header);
	//mWinnerPopup.Hide();
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

const char* MyGame::GetWindowName() const
{
	return gWindowName;
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

// This changes background color
/// <param name="color"></param>
void MyGame::GetClearColor(exColor& color) const
{
	color.mColor[0] = 128; // R
	color.mColor[1] = 128; // G
	color.mColor[2] = 128; // B
	//color.mColor[3] = 255 // A
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

// Registers different types of events (key presses, mouse clicks, etc...)
void MyGame::OnEvent(SDL_Event* pEvent)
{
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

void MyGame::OnEventsConsumed()
{
	// nKeys influenced by keys -- reads bits of the int
	int nKeys = 0;
	const Uint8* pState = SDL_GetKeyboardState(&nKeys);

	// Keyboard inputs are set as enums
	mUp = pState[SDL_SCANCODE_UP];
	mDown = pState[SDL_SCANCODE_DOWN];
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

// Fires every frame and returns the time between each frame
void MyGame::Run(float fDeltaT)
{
	RENDER_ENGINE.RenderUpdate(mEngine);

	mBall_First->Tick(fDeltaT);

	mBall_Second->Tick(fDeltaT);

	exVector2 BallVelocity(0.0f, 0.0f);

	if (mUp)
	{
		BallVelocity.y = -2.5f;
	}
	if (mDown)
	{
		BallVelocity.y = 2.5f;
	}

	if (std::shared_ptr<PhysicsComponent> BallPhysicsComp = mBall_First->GetComponentOfType<PhysicsComponent>())
	{
		BallPhysicsComp->SetVelocity(BallVelocity);
	}

	PHYSICS_ENGINE.PhysicsUpdate(fDeltaT);
	//mBall->SetBallPosition(mTextPosition);
}
