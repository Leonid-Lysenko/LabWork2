/* Leonid Lysenko st128618@student.spbu.ru
   Lab2
*/

class PlayerTest : public ::testing::Test {
protected:
    std::shared_ptr<Player> player;
    
    void SetUp() override {
        player = std::make_shared<Player>(1, "Test Player", 30, 10);
    }
};

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
