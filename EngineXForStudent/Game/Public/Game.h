#include "Game/Public/Utils.h"
#include "Game/Public/GameInterface.h"
#include "Engine/Public/EngineTypes.h"
#include "Game/Public/Actors/Ball.h"
#include "Game/Public/Actors/Box.h"
#include "Game/Public/Actors/Line.h"
#include "Game/Public/Actors/HUD.h"
#include "Game/Public/Actors/SpinningWheel.h"
#include "Game/Public/Components/TextRenderComponent.h"
#include "Game/Public/Actors/TextFileReader.h"
#include "Game/Public/Components/WinnerPopupComponent.h"
#include "Game/Public/Components/ConfettiBurstComponent.h"

class MyGame : public exGameInterface
{
public:
    MyGame();
    virtual                     ~MyGame();
    virtual void                Initialize(exEngineInterface* pEngine);
    virtual const char* GetWindowName() const;
    virtual void                GetClearColor(exColor& color) const;
    virtual void                OnEvent(SDL_Event* pEvent);
    virtual void                OnEventsConsumed();
    virtual void                Run(float fDeltaT);
private:
    exEngineInterface* mEngine;
    int                                     mFontID;
    std::shared_ptr<HUD>                    mHUD;
    std::shared_ptr<TextRenderComponent>    mHUDText;
    std::shared_ptr<SpinningWheelActor>     mSpinningWheel;
    bool                                    mSpinKey;
    std::shared_ptr<TextFileReader>         mTextFileReader;
    std::string                             winnerFilePath = "winners.txt";
	WinnerPopup								mWinnerPopup;
	ConfettiBurstComponent					mConfettiBurst;
    exColor                                 mHeaderColor;
};