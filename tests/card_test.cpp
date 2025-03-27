#include <gtest/gtest.h>
#include <memory>
#include "test_helpers.h"

class CardTest : public ::testing::Test {
protected:
    std::shared_ptr<TestCard> card;
    std::shared_ptr<TestPlayer> player;
    std::shared_ptr<TestPlayer> opponent;
    
    void SetUp() override {
        card = std::make_shared<TestCard>(1, "Test Card");
        player = std::make_shared<TestPlayer>(1, "Player", 30, 10);
        opponent = std::make_shared<TestPlayer>(2, "Opponent", 30, 10);
    }
};

TEST_F(CardTest, BasicProperties) {
    EXPECT_EQ(card->getName(), "Test Card");
    EXPECT_EQ(card->getId(), 1);
}

TEST_F(CardTest, CardPlay) {
    EXPECT_TRUE(card->play(player.get(), opponent.get()));
}

TEST_F(CardTest, CardCloning) {
    auto cloned = card->clone();
    EXPECT_EQ(cloned->getName(), "Test Card");
}
