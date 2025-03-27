#include <gtest/gtest.h>
#include <memory>
#include <vector>
#include "player.h"
#include "duel_mode.h"

class TestPlayer : public Player {
public:
    using Player::Player;
    
    bool takeTurn(Player* opponent) override { 
        (void)opponent;
        return true; 
    }
    void displayStatus() const override {}
    void displayHelp() const override {} // Добавленная реализация
};

class GameModeTest : public ::testing::Test {
protected:
    std::shared_ptr<DuelMode> mode;
    std::vector<std::shared_ptr<Player>> players;
    
    void SetUp() override {
        players = {
            std::make_shared<TestPlayer>(1, "P1", 30, 10),
            std::make_shared<TestPlayer>(2, "P2", 30, 10)
        };
        mode = std::make_shared<DuelMode>();
    }
};

TEST_F(GameModeTest, Initialization) {
    EXPECT_TRUE(mode->initialize(players));
    EXPECT_EQ(mode->getPlayers().size(), 2);
}
