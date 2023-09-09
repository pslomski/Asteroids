#pragma once

#include <string>
#include <vector>

#include "GameState.h"

#include "ui/Font.hpp"
#include "ui/Rectangle.h"
#include "ui/TextControl.h"

namespace ui
{
class HighScoreState : public GameState
{
public:
    void setNewHighScore(uint32_t NewHighScore) { mNewHighScore = NewHighScore; }
    void onKeyDown(SDL_KeyboardEvent& e) override;
    void onChar(char* c) override;
    void draw() override;
    void enterState() override;
    void leaveState() override;

    static HighScoreState* getInstance(StateManager* const manager);

protected:
    HighScoreState(StateManager* const manager);

private:
    void init();
    void cleanup();
    void saveScores();
    void addNewScore(const std::string& strName, uint32_t score);

    struct HighScoreData
    {
        std::string strPlayer;
        uint32_t score;
        HighScoreData():strPlayer(), score(0){}
        bool operator< (const HighScoreData& other)
        {
            // We have to sort in decreasing order, so the <
            // operator returns the opposite.
            if  (this->score > other.score) 
                return true;
            return false;
        }
    };

    // The new high-score, if any.
    uint32_t mNewHighScore;
    // Mode in which the user has to enter his name.
    bool mEnterName;
    // Char array containing the name currently being entered.
    char mCurrentName[26];
    // The index of the next char to be entered.
    int mNameIndex;

    Font* mFont;
    Font* mFontSmall;

    typedef std::vector<HighScoreData> THighScoreTable;
    // The high-score table.
    THighScoreTable mHighScores;
    TextControl* mHighScore;
    Rectangle mHighScoreRect;
    Rectangle mEntriesRect;
};
} // namespace ui
