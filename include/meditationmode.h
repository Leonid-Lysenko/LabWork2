#ifndef MEDITATIOMODE_H
#define MEDITATIOMODE_H

#include "game_mode.h"

class MeditationMode : public GameMode {
protected:
    bool m_infiniteMana;      ///< Флаг бесконечной маны
    bool m_infiniteHealth;    ///< Флаг бесконечного здоровья
    bool m_unlimitedCards;    ///< Флаг неограниченного количества карт
    
    void setupModeOptions();
    void applyModeSettings();
    void handleTestCommand(const std::string& args);
    void testCardCombo();
    void testEffect(int effectId);
    void testDamage(int damage);

public:
    MeditationMode();
    
    bool initialize(const std::vector<PlayerPtr>& players) override;
    bool start() override;
    bool executeTurn(PlayerPtr currentPlayer, PlayerPtr opponent) override {
        return true;
    }
    
    void refreshResources();
    bool handleCommand(const std::string& command) override;
    void resetGameState();
};

#endif // MEDITATIOMODE_H