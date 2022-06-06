#pragma once

#include <string>
#include <vector>

#include "ui/Font.h"
#include "ui/Rectangle.h"
#include "ui/TextControl.h"

#include "GameState.h"

namespace ui
{
// Specialization of the CGameState class for 
// the high scores state. This displays the high
// scores (player name+score). When a new high 
// score is available after a game, it lets the 
// player enters his name.
class HighScoreState : public CGameState
{
public:
    // Sets a new score: if this score should be 
    // part of the high scores, the user will need 
    // to enter his name.
    void SetNewHighScore(ULONG NewHighScore) { mNewHighScore = NewHighScore; }

    // Implementation of specific events
    void OnKeyDown(SDL_KeyboardEvent& e);
    void OnChar(char* c);
    void Draw();
    void EnterState();
    void LeaveState();

    static HighScoreState* GetInstance(StateManager* pManager);
protected:
    HighScoreState(StateManager* pManager);
private:
    void Init();
    void Cleanup();

    // Saves the current high scores
    void SaveScores();

    // Adds a new score in the high-score table and
    // insert it at the correct location.
    void AddNewScore(const std::string& strName, ULONG ulScore);

    // High-score data: score and player name.
    struct HighScoreData
    {
        std::string strPlayer;
        ULONG ulScore;
        HighScoreData():strPlayer(), ulScore(0){}
        // We have to sort in decreasing order, so the <
        // operator returns the opposite.
        bool operator< (const HighScoreData& other)
        {
            if  (this->ulScore > other.ulScore) 
                return true;
            return false;
        }
    };

    // The new high-score, if any.
    ULONG mNewHighScore;
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
