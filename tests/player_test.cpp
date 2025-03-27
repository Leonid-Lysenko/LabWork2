#include <gtest/gtest.h>
#include <memory>
#include "test_helpers.h"
#include "character_card.h"

class PlayerTest : public ::testing::Test {
protected:
    std::shared_ptr<TestPlayer> player;
    
    void SetUp() override {
        player = std::make_shared<TestPlayer>(1, "Test Player", 30, 10);
    }
};

TEST_F(PlayerTest, Initialization) {
    EXPECT_EQ(player->getName(), "Test Player");
    EXPECT_EQ(player->getHealth(), 30);
}

TEST_F(PlayerTest, DrawCard) {
    Cards deck = {
        std::make_shared<CharacterCard>(1, "C1", "", 1, CharacterClass::Warrior, 1, 1),
        std::make_shared<CharacterCard>(2, "C2", "", 1, CharacterClass::Warrior, 1, 1)
    };
    
    player->setDeck(deck);
    EXPECT_EQ(player->getHand().size(), 0);
    player->drawCard(1);
    EXPECT_EQ(player->getHand().size(), 1);
}
