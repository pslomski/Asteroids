#include <fstream>
#include <sstream>
#include <algorithm>

#include "HighScoreState.h"
#include "MenuState.h"

#include "aster/Consts.h"
#include "aster/World.h"
#include "gl/Renderer.hpp"
#include "log/Log.hpp"
#include "sdl/SDLTools.h"

namespace ui
{
HighScoreState::HighScoreState(StateManager* const manager):
    GameState(manager),
    mNewHighScore(0),
    mEnterName(false), 
    mFont(nullptr),
    mNameIndex(0),
    mHighScores(10)
{}

void HighScoreState::init()
{
    mCurrentName[0] = '\0';
    mFont = new Font("vector battle", 20);
    mFontSmall = new Font("vector battle", 15);

    int dy = 20;
    int left = int(1.0 / 4.0 * geWorld.scrWidth);
    int right = int(3.0 / 4.0 * geWorld.scrWidth);
    int bottom = 50;
    int top = bottom + dy;
    mHighScore = new TextControl(mFont, ui::Rectangle(left, top, right, bottom));
    mHighScore->setAlignement(TextControl::taCenter);
    mHighScore->setText("High Scores");

    int Marg = 10;
    mHighScoreRect.left = left - Marg;
    mHighScoreRect.top = 600;
    mHighScoreRect.right = right + Marg;
    mHighScoreRect.bottom = 550;

    mEntriesRect.left = left / 2;
    mEntriesRect.bottom = 135;
    mEntriesRect.top = mEntriesRect.bottom + 35;
    mEntriesRect.right = right + left / 2;
}

void HighScoreState::cleanup()
{
    delete mHighScore;
    delete mFont;
    delete mFontSmall;
    
    mHighScore = NULL;
    mFont = NULL;
    mFontSmall = NULL;
}

void HighScoreState::enterState()
{
    LOG_INF("HighScoreState::enterState");
    init();
    mHighScores.clear();
    std::ifstream inputFile("HighScores.txt");
    if (inputFile.fail())
    {
        if (mNewHighScore)
        {
            mEnterName = true;
        }
        return;
    }

    // Read all entries from the file
    std::string line;
    HighScoreData newScore;
    std::basic_string <char>::size_type idx;
    while (!inputFile.eof()) 
    {
        getline(inputFile, line);
        if (line.empty())
            continue;
        idx = line.find(";");
        if (idx == -1)
            continue;
        newScore.strPlayer = line.substr(0, idx);
        newScore.score = atoi(line.substr(idx + 1).c_str());
        mHighScores.push_back(newScore);
    }
    while (mHighScores.size() < 10)
    {
        mHighScores.push_back(HighScoreData());
    }

    sort(mHighScores.begin(), mHighScores.end());

    // Check if we have a new high-score that should be
    // added in the table. If yes, m_bEnterName is set to true.
    uint32_t lastScore = 0;
    if (mHighScores.size())
    {
        lastScore = mHighScores[mHighScores.size() - 1].score;
    }
    if (mNewHighScore && mNewHighScore > lastScore)
    {
        mEnterName = true;
    }
}

void HighScoreState::leaveState()
{
    cleanup();
    LOG_INF("HighScoreState::leaveState");
}

HighScoreState* HighScoreState::getInstance(StateManager* const manager)
{
    static HighScoreState instance(manager);
    return &instance;
}

void HighScoreState::onKeyDown(SDL_KeyboardEvent& e)
{ 
    if (mEnterName)
    {
        switch(SDLTools::GetKeycode(e))
        {
            // In case of a return, the new score should be added.
        case SDLK_RETURN:
            if(!std::string(mCurrentName).empty()){
                addNewScore(mCurrentName, mNewHighScore);
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
            changeState(MenuState::getInstance(stateManager));
            break;
        }
    }
}

void HighScoreState::onChar(char* c) 
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

void HighScoreState::draw()  
{
    auto dm = gl::DrawMode2DText(geWorld.scrWidth, geWorld.scrHeight);
    mHighScore->draw();
    ui::Rectangle rcNum = mEntriesRect;
    rcNum.right = mEntriesRect.left + 40;
    ui::Rectangle rcTxt = mEntriesRect;
    rcTxt.left=mEntriesRect.left + 60;
    int count = 1;
    char buf[256];
    THighScoreTable::iterator iter = mHighScores.begin();
    for (iter; iter!=mHighScores.end(); iter++)
    {
        // itoa(cout, buf, 10);
        const auto entryN{std::to_string(count)};
        TextControl txtEntryN(mFont, rcNum);
        txtEntryN.setAlignement(TextControl::taRight);
        txtEntryN.setText(entryN);
        txtEntryN.draw();

        TextControl txtEntry(mFont, rcTxt);
        txtEntry.setAlignement(TextControl::taLeft);
        txtEntry.setText(iter->strPlayer);
        txtEntry.draw();

        std::stringstream ssScore;
        ssScore << iter->score;
        txtEntry.setAlignement(TextControl::taRight);
        txtEntry.setText(ssScore.str());
        txtEntry.draw();

        rcNum.offset(0, 35);
        rcTxt.offset(0, 35);
        ++count;
    }

    // If the player should enter its name, we draw something additional.
    if (mEnterName)
    {
        glColor3f(1.0, 1.0, 1.0);
        glBegin(GL_LINE_LOOP);
        glVertex2i(mHighScoreRect.left, mHighScoreRect.bottom);
        glVertex2i(mHighScoreRect.right, mHighScoreRect.bottom);
        glVertex2i(mHighScoreRect.right, mHighScoreRect.top);
        glVertex2i(mHighScoreRect.left, mHighScoreRect.top);
        glEnd();

        Rectangle rc(mHighScoreRect);
        rc.offset(0, -50);
        TextControl txtEnterName(mFont, rc);
        txtEnterName.setAlignement(TextControl::taCenter);
        txtEnterName.setText("Enter Your name:");
        txtEnterName.draw();

        TextControl txtEntry(mFont, mHighScoreRect);
        txtEntry.setAlignement(TextControl::taCenter);
        txtEntry.setText(mCurrentName);
        txtEntry.draw();
    }
    else
    {
        Rectangle rc(0, geWorld.scrHeight - 50, geWorld.scrWidth, geWorld.scrHeight - 100);
        TextControl txtEnterName(mFontSmall, rc);
        txtEnterName.setAlignement(TextControl::taCenter);
        txtEnterName.setText("Press Enter");
        txtEnterName.draw();
    }
}

void HighScoreState::saveScores()
{
    std::ofstream outputFile("HighScores.txt");
    if (outputFile.fail())
        return;

    THighScoreTable::iterator iter = mHighScores.begin();
    for (iter; iter != mHighScores.end(); iter++)
    {
        outputFile << iter->strPlayer << ";" << iter->score<<'\n';
    }
}

void HighScoreState::addNewScore(const std::string& strName, uint32_t score)
{
    HighScoreData newData;
    newData.strPlayer = strName;
    newData.score = score;
    mHighScores.push_back(newData);
    
    sort(mHighScores.begin(), mHighScores.end());

    while (mHighScores.size() > 10)
    {
        mHighScores.pop_back();
    }
    saveScores();
}
} // namespace ui
