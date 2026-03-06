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
    , mSpinKey(false)
{
}

MyGame::~MyGame()
{
}

void MyGame::Initialize(exEngineInterface* pEngine)
{
    // generate seed
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    mEngine = pEngine;

    mFontID = mEngine->LoadFont("Resources/Montserrat-Regular.ttf", 32);


    float Radius = 25.0f;

    exColor White;
    White.mColor[0] = 255;
    White.mColor[1] = 255;
    White.mColor[2] = 255;
    White.mColor[3] = 255;

	mHeaderColor.mColor[0] = 130;
	mHeaderColor.mColor[1] = 170;
	mHeaderColor.mColor[2] = 150;
	mHeaderColor.mColor[3] = 255;

    // Spawn wheel at center screen with radius 200
    mSpinningWheel = Actor::SpawnActorOfType<SpinningWheelActor>(exVector2(500.0f, 300.0f), 200.0f);

    mTextFileReader = Actor::SpawnActorOfType<TextFileReader>();
    std::vector<std::string> listOfNames = *(mTextFileReader->GetComponentOfType<TextFileReaderComponent>()->ReadTextFile());

    if (mTextFileReader->GetComponentOfType<TextFileReaderComponent>()->TextFileIsNotEmpty())
    {
        mSpinningWheel->RemoveAllSlices();
        mSpinningWheel->AddMultipleSlices(listOfNames);
    }
    else
    {
        mSpinningWheel->AddMultipleSlices({ "Open", "names.txt", "To", "Input", "Names" });
    }

    // HUD starts with a prompt to spin
    mHUD = std::make_shared<HUD>(White, String("Press SPACE to spin!"),
        String("Resources/Montserrat-Regular.ttf"), 32,
        exVector2{ 0.0f, 0.0f }, 10);

	mHUD->BeginPlay();
	mHUDText = mHUD->GetComponentOfType<TextRenderComponent>();

	

	/*mWinnerPopup.Show("We have a winner!", "Diana", mHeaderColor);
	mConfettiBurst.Spawn(exVector2(400.0f, 100.0f), 100);
	mConfettiBurst.Spawn(exVector2(200.0f, 100.0f), 100);
	mConfettiBurst.Spawn(exVector2(600.0f, 100.0f), 100);*/
	//mWinnerPopup.Hide();
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

    mSpinKey = pState[SDL_SCANCODE_SPACE];
    mCloseKey = pState[SDL_SCANCODE_RETURN];
}

void MyGame::Run(float fDeltaT)
{

    // Game State decides logic and keybind effects
    switch (mGameState)
    {
    case Base:
        // Only lets the list of names be altered in the base state -> can't change the list in the middle of spinning
        #pragma region Text File Reader
            if (mTextFileReader->GetComponentOfType<TextFileReaderComponent>()->TextFileUpdated())
            {
                // Reinitialize the names
                mSpinningWheel->RemoveAllSlices();
                std::vector<std::string> listOfNames = *(mTextFileReader->GetComponentOfType<TextFileReaderComponent>()->ReadTextFile());
                mSpinningWheel->AddMultipleSlices(listOfNames);
            }
        #pragma endregion
            if (mSpinKey)
            {
                mGameState = Spinning;
                mSpinningWheel->Spin((10000 + (rand() % 10001)));
                if (mHUDText)
                {
                    mHUDText->SetText("Spinning...");
                }
            }
        break;
    case Spinning:
        mSpinningWheel->Tick(fDeltaT);

        // Once the wheel stops update the HUD with the winner
        if (WheelSlice* Result = mSpinningWheel->GetResult())
        {
            if (mHUDText)
            {
                mHUDText->SetText("Winner: " + Result->mLabel);

                std::ofstream file("./" + winnerFilePath); //, std::ios::app);
                file << "\n" + Result->mLabel;
                mWinnerPopup.Show("We have a winner!", Result->mLabel, mHeaderColor);
                mConfettiBurst.Spawn(exVector2(400.0f, 100.0f), 100);
                mConfettiBurst.Spawn(exVector2(200.0f, 100.0f), 100);
                mConfettiBurst.Spawn(exVector2(600.0f, 100.0f), 100);
            }
            mGameState = Celebration;
        }
        break;
    case Celebration:
        if (mCloseKey)
        {
            mWinnerPopup.Hide();
            mGameState = Base;
        }
        break;
    }

    PHYSICS_ENGINE.PhysicsUpdate(fDeltaT);
    mConfettiBurst.Update(fDeltaT);
    RENDER_ENGINE.RenderUpdate(mEngine);
}