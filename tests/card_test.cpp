/* Leonid Lysenko st128618@student.spbu.ru
   Lab2
*/

#include <gtest/gtest.h>
#include "card.h"
#include "player.h"

class CardTest : public ::testing::Test {
protected:
    std::shared_ptr<Player> player;
    std::shared_ptr<Player> opponent;
    
    void SetUp() override {
        player = std::make_shared<Player>(1, "Test Player", 30, 10);
        opponent = std::make_shared<Player>(2, "Test Opponent", 30, 10);
    }
};

TEST_F(CardTest, CharacterCardBasics) {
    auto card = std::make_shared<CharacterCard>(1, "Test", "Test char", 2, CharacterClass::Warrior, 2, 3);
    EXPECT_EQ(card->getAttack(), 2);
    EXPECT_EQ(card->getHealth(), 3);
    EXPECT_FALSE(card->canAttack());
}
