#pragma once

#include "../Menu/gamestate.h"
#include "../Menu/GameFont.h"
#include "../Menu/TextControl.h"

namespace menu{

class OptionsState : public CGameState{
public:
	void OnKeyDown(SDL_KeyboardEvent& e);
	void Update(double TimeStep);
	void Draw();
	void EnterState();
	void LeaveState();
	static OptionsState* GetInstance(StateManager* pManager);

protected:
	OptionsState(StateManager* pManager);
private:
	int mCurrentSelection;
	ast::GameFont* mFont;
	CTextControl* mTitleText;
	CTextControl* mMusicVolText;
	CTextControl* mSoundVolText;

	void Init();
	void Cleanup();
	void SelectionUp();
	void SelectionDown();
	void LeftArrow();
	void RightArrow();
	CTextControl* GetTextControl(int id);
	void SetBlinkText(int id, bool isBlink);
};

}//namespace menu