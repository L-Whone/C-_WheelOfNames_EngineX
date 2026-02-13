//
// * ENGINE-X
// * SAMPLE GAME
//
// + Game.h
// definition of MyGame, an implementation of exGameInterface
//

#include "Game/Public/Utils.h"
#include "Game/Public/GameInterface.h"
#include "Engine/Public/EngineTypes.h"

#include "Game/Public/Actors/Ball.h"
#include "Game/Public/Actors/Box.h"
#include "Game/Public/Actors/Line.h"

//-----------------------------------------------------------------
//-----------------------------------------------------------------

class MyGame : public exGameInterface
{
public:

								MyGame();
	virtual						~MyGame();

	virtual void				Initialize( exEngineInterface* pEngine );

	virtual const char*			GetWindowName() const;
	virtual void				GetClearColor( exColor& color ) const;

	virtual void				OnEvent( SDL_Event* pEvent );
	virtual void				OnEventsConsumed();

	virtual void				Run( float fDeltaT );

private:

	exEngineInterface*			mEngine;

	int							mFontID;

	bool						mUp;
	bool						mDown;

	exVector2					mTextPosition;
	std::shared_ptr<Ball>		mBall_First;
	std::shared_ptr<Ball>		mBall_Second;
	std::shared_ptr<Box>		mBox;
	std::shared_ptr<Line>         mLine;
};
