#include "StdAfx.h"
#include "MenuState.h"
#include "OptionsState.h"
#include "../engine/world.h"
#include "../engine/renderer.h"

namespace menu {

	OptionsState::OptionsState(StateManager* pManager)
		:CGameState(pManager)
	{
	}

	OptionsState* OptionsState::GetInstance(StateManager* pManager)
	{
		static OptionsState Instance(pManager);
		return &Instance;
	}

	void OptionsState::Init()
	{
		mCurrentSelection = 0;
		mFont = new ast::GameFont("vector battle", 20);

		int dy = 20;
		int left = int(1.0 / 4.0 * geWorld.scrWidth);
		int right = int(3.0 / 4.0 * geWorld.scrWidth);
		int top = 50;
		int bottom = top + dy;
		mTitleText = new CTextControl(mFont, ast::Rectanglei(top, bottom, left, right));
		mTitleText->SetAlignement(CTextControl::taCenter);
		mTitleText->SetText("Settings");

		dy = 45;
		top = 135;
		bottom += dy;
		mMusicVolText = new CTextControl(mFont, ast::Rectanglei(top, bottom, left, right));
		mMusicVolText->SetAlignement(CTextControl::taCenter);
		mMusicVolText->SetText("Music volume: ");

		top += dy;
		bottom += dy;
		mSoundVolText = new CTextControl(mFont, ast::Rectanglei(top, bottom, left, right));
		mSoundVolText->SetAlignement(CTextControl::taCenter);
		mSoundVolText->SetText("Sound volume: ");
	}

	void OptionsState::Cleanup()
	{
		delete mFont;
		delete mTitleText;
		delete mMusicVolText;
		delete mSoundVolText;
	}

	void OptionsState::EnterState()
	{
		Init();
		geWorld.ReadSettings();
		SetBlinkText(mCurrentSelection, true);
	}

	void OptionsState::LeaveState()
	{
		geWorld.SaveSettings();
		Cleanup();
	}

	void OptionsState::OnKeyDown(SDL_KeyboardEvent& e)
	{
		switch (e.keysym.sym) {
		case SDLK_DOWN:
			SelectionDown();
			break;
		case SDLK_UP:
			SelectionUp();
			break;
		case SDLK_LEFT:
			LeftArrow();
			break;
		case SDLK_RIGHT:
			RightArrow();
			break;
		case SDLK_ESCAPE:
			ChangeState(CMenuState::GetInstance(m_pStateManager));
			break;
		}
	}

	void OptionsState::Update(double TimeStep)
	{
		CTextControl* txtCtrl = GetTextControl(mCurrentSelection);
		if (txtCtrl)
			txtCtrl->Update(TimeStep);
	}

	void OptionsState::Draw()
	{
		auto dm = ast::DrawMode2DText();
		static const int BUF_SIZE = 128;
		static char buf[BUF_SIZE];
		mTitleText->Draw();

		int musicVol = int(ceil(10 * geMusic.GetVolume()));
		int soundVol = int(ceil(10 * geSound.GetVolume()));
		sprintf_s(buf, BUF_SIZE, "Music volume: %d", musicVol);
		mMusicVolText->SetText(std::string(buf));
		mMusicVolText->Draw();
		sprintf_s(buf, BUF_SIZE, "Sound volume: %d", soundVol);
		mSoundVolText->SetText(buf);
		mSoundVolText->Draw();
	}

	CTextControl* OptionsState::GetTextControl(int id)
	{
		switch (id) {
		case 0: return mMusicVolText; break;
		case 1: return mSoundVolText; break;
		}
		assert(NULL);
		return NULL;
	}

	void OptionsState::SetBlinkText(int id, bool isBlink)
	{
		CTextControl* txtCtrl = GetTextControl(mCurrentSelection);
		if (txtCtrl) txtCtrl->SetBlink(isBlink);
	}

	void OptionsState::SelectionUp()
	{
		SetBlinkText(mCurrentSelection, false);
		mCurrentSelection--;
		if (mCurrentSelection == -1)
			mCurrentSelection = 1;

		SetBlinkText(mCurrentSelection, true);
	}

	void OptionsState::SelectionDown()
	{
		SetBlinkText(mCurrentSelection, false);
		mCurrentSelection++;
		if (mCurrentSelection == 2)
			mCurrentSelection = 0;
		SetBlinkText(mCurrentSelection, true);
	}

	void OptionsState::LeftArrow()
	{
		switch (mCurrentSelection) {
		case 0://Music Volume
			geWorld.MusicVol = max(0, geWorld.MusicVol - 1);
			geMusic.SetVolume(0.1f * geWorld.MusicVol);
			break;
		case 1://Sound Volume
			geWorld.SoundVol = max(0, geWorld.SoundVol - 1);
			geSound.SetVolume(0.1f * geWorld.SoundVol);
			geSound.SoundTest();
			break;
		}
	}

	void OptionsState::RightArrow()
	{
		switch (mCurrentSelection) {
		case 0://Music Volume
			geWorld.MusicVol = min(10, geWorld.MusicVol + 1);
			geMusic.SetVolume(0.1f * geWorld.MusicVol);
			break;
		case 1://Sound Volume
			geWorld.SoundVol = min(10, geWorld.SoundVol + 1);
			geSound.SetVolume(0.1f * geWorld.SoundVol);
			geSound.SoundTest();
			break;
		}
	}

}//namespace menu