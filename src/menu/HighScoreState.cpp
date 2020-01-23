#include "stdafx.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include "SDLTools.h"
#include "HighScoreState.h"
#include "MenuState.h"
#include "../engine/World.h"
#include "../engine/Consts.h"
#include "../engine/renderer.h"

namespace menu{

HighScoreState::HighScoreState(StateManager* pManager)
  : CGameState(pManager), mNewHighScore(0), mEnterName(false), 
    mFont(NULL), mNameIndex(0), mHighScores(10)
{
}

void HighScoreState::Init()
{
	mCurrentName[0] = '\0';
	mFont = new ast::GameFont("vector battle", 20);
	mFontSmall = new ast::GameFont("vector battle", 15);

	int dy = 20;
	int left = int(1.0 / 4.0 * geWorld.scrWidth);
	int right = int(3.0 / 4.0 * geWorld.scrWidth);
	int top = 50;
	int bottom = top + dy;
	mHighScore = new CTextControl(mFont, ast::Rectanglei(top, bottom, left, right));
	mHighScore->SetAlignement(CTextControl::taCenter);
	mHighScore->SetText("High Scores");

	int Marg = 10;
	mHighScoreRect.top = 550;
	mHighScoreRect.bottom = 600;
	mHighScoreRect.left = left - Marg;
	mHighScoreRect.right = right + Marg;

	mEntriesRect.top = 135;
	mEntriesRect.bottom = mEntriesRect.top + 35;
	mEntriesRect.left = left / 2;
	mEntriesRect.right = right + left / 2;
}

void HighScoreState::Cleanup()
{
	delete mHighScore;
	delete mFont;
	delete mFontSmall;
	
	mHighScore = NULL;
	mFont = NULL;
	mFontSmall = NULL;
}

void HighScoreState::EnterState()
{
	Init();
	// Clear the high-score table
	mHighScores.clear();
	std::ifstream inputFile("HighScores.txt");
	if (inputFile.fail())
	{
		if (mNewHighScore)
			mEnterName = true;
		return;
	}

	// Read all entries from the file
	std::string line;
	HighScoreData newScore;
	std::basic_string <char>::size_type idx;
	while (!inputFile.eof()) {
		getline(inputFile, line);
		if (line.empty()) continue;
		idx = line.find(";");
		if (idx == -1) continue;
		newScore.strPlayer = line.substr(0, idx); //strtok_s(buf, sep, &next_token1);
		newScore.ulScore = atoi(line.substr(idx + 1).c_str());
		mHighScores.push_back(newScore);
	}
	while (mHighScores.size() < 10)
		mHighScores.push_back(HighScoreData());

	// Sort the table
	sort(mHighScores.begin(), mHighScores.end());

	// Check if we have a new high-score that should be
	// added in the table. If yes, m_bEnterName is set
	// to true.
	ULONG lastScore = 0;
	if (mHighScores.size())
		lastScore = mHighScores[mHighScores.size() - 1].ulScore;
	if (mNewHighScore && mNewHighScore > lastScore)
		mEnterName = true;
}

void HighScoreState::LeaveState()
{
	Cleanup();
}

HighScoreState* HighScoreState::GetInstance(StateManager* pManager)
{
	static HighScoreState Instance(pManager);
	return &Instance;
}

void HighScoreState::OnKeyDown(SDL_KeyboardEvent& e)
{ 
	if (mEnterName)
	{
		switch(SDLTools::GetKeycode(e))
		{
			// In case of a return, the new score should be added.
		case SDLK_RETURN:
			if(!std::string(mCurrentName).empty()){
				AddNewScore(mCurrentName, mNewHighScore);
				mNewHighScore = 0;
				mEnterName = false;
				mNameIndex = 0;
				mCurrentName[0] = '\0';
			}
			break;
		case SDLK_BACKSPACE:
			// Remove one character
			if (mNameIndex>0)
			{
				mNameIndex--;
				mCurrentName[mNameIndex] = '\0';
			}
			break;
		}
	}
	else
	{
		switch(SDLTools::GetKeycode(e))
		{
		case SDLK_ESCAPE:
		case SDLK_RETURN:
			ChangeState(CMenuState::GetInstance(m_pStateManager));
			break;
		}
	}
}

void HighScoreState::OnChar(char* c) 
{ 
	if (mEnterName && (mNameIndex<25))
	{
		// Filter the characters for only alphabetical
		// characters.
		if ( (*c>=64 && *c<=91) ||
			 (*c>=97 && *c<=122))
		{
			mCurrentName[mNameIndex] = *c;
			mNameIndex++;
			mCurrentName[mNameIndex] = '\0';
		}
	}
}

void HighScoreState::Draw()  
{
	auto dm = ast::DrawMode2DText();
	mHighScore->Draw();
	ast::Rectanglei rcNum=mEntriesRect;
	rcNum.right=mEntriesRect.left+40;
	ast::Rectanglei rcTxt=mEntriesRect;
	rcTxt.left=mEntriesRect.left+60;
	int iCount=1;
	char buf[256];
	THighScoreTable::iterator iter = mHighScores.begin();
	for (iter; iter!=mHighScores.end(); iter++)
	{
		_itoa_s(iCount, buf, 10);
		CTextControl txtEntryN(mFont, rcNum);
		txtEntryN.SetAlignement(CTextControl::taRight);
		txtEntryN.SetText(buf);
		txtEntryN.Draw();

		CTextControl txtEntry(mFont, rcTxt);
		txtEntry.SetAlignement(CTextControl::taLeft);
		txtEntry.SetText(iter->strPlayer);
		txtEntry.Draw();

		std::stringstream ssScore;
		ssScore << iter->ulScore;
		txtEntry.SetAlignement(CTextControl::taRight);
		txtEntry.SetText(ssScore.str());
		txtEntry.Draw();

		rcNum.offsetRect(0, 35);
		rcTxt.offsetRect(0, 35);
		++iCount;
	}

	// If the player should enter its name, we draw something additional.
	if (mEnterName){
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_LINE_LOOP);
		glVertex2i(mHighScoreRect.left, mHighScoreRect.bottom);
		glVertex2i(mHighScoreRect.right, mHighScoreRect.bottom);
		glVertex2i(mHighScoreRect.right, mHighScoreRect.top);
		glVertex2i(mHighScoreRect.left, mHighScoreRect.top);
		glEnd();

		ast::Rectanglei rc(mHighScoreRect);
		rc.offsetRect(0, -50);
		CTextControl txtEnterName(mFont, rc);
		txtEnterName.SetAlignement(CTextControl::taCenter);
		txtEnterName.SetText("Enter Your name:");
		txtEnterName.Draw();

		CTextControl txtEntry(mFont, mHighScoreRect);
		txtEntry.SetAlignement(CTextControl::taCenter);
		txtEntry.SetText(mCurrentName);
		txtEntry.Draw();
	}
	else{
		ast::Rectanglei rc(geWorld.scrHeight-100, geWorld.scrHeight-50, 0, geWorld.scrWidth);
		CTextControl txtEnterName(mFontSmall, rc);
		txtEnterName.SetAlignement(CTextControl::taCenter);
		txtEnterName.SetText("Press Enter");
		txtEnterName.Draw();
	}
}

void HighScoreState::SaveScores()
{
	// Create the file
	std::ofstream outputFile("HighScores.txt");
	if (outputFile.fail())
		return;

	// Write all the entries in the file.
	THighScoreTable::iterator iter = mHighScores.begin();
	for (iter; iter != mHighScores.end(); iter++)
	{
		outputFile << iter->strPlayer << ";" << iter->ulScore<<'\n';
	}
}

void HighScoreState::AddNewScore(const std::string& strName, ULONG ulScore)
{
	// Create a new high-score and push it into the table 
	HighScoreData newData;
	newData.strPlayer = strName;
	newData.ulScore = ulScore;
	mHighScores.push_back(newData);
	
	// Sort the table
	sort(mHighScores.begin(), mHighScores.end());

	// If too much elements, remove the last one.
	while (mHighScores.size() > 10)
		mHighScores.pop_back();

	SaveScores();
}

}//namespace menu