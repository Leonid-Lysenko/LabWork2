/* Leonid Lysenko st128618@student.spbu.ru
   Lab2
*/

#ifndef DUELMMODE_H
#define DUELMMODE_H

#include "game_mode.h"

class DuelMode : public GameMode {
protected:
    PlayerPtr m_winner;  ///< Победитель дуэли (nullptr если ничья)

public:
    DuelMode();
    
    DuelMode(int id, const std::string& name, const std::string& description);
    
    bool initialize(const std::vector<PlayerPtr>& players) override;
    
    bool start() override;
    
    bool executeTurn(PlayerPtr currentPlayer, PlayerPtr opponent) override;
    
    PlayerPtr getOpponent() const;
    
    bool checkEndCondition() override;
    
    void displayResults() const override;
    
    void displayHelp() const override;
    
    PlayerPtr getWinner() const {
        return m_winner;
    }
};

#endif // DUELMMODE_H
