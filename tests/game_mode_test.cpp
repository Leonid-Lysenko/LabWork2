/* Leonid Lysenko st128618@student.spbu.ru
   Lab2
*/

class GameModeTest : public ::testing::Test {
protected:
    std::shared_ptr<GameMode> mode;
    std::vector<std::shared_ptr<Player>> players;
    
    void SetUp() override {
        players = {
            std::make_shared<Player>(1, "P1", 30, 10),
            std::make_shared<Player>(2, "P2", 30, 10)
        };
        mode = std::make_shared<DuelMode>();
    }
};

TEST_F(GameModeTest, Initialization) {
    EXPECT_TRUE(mode->initialize(players));
    EXPECT_EQ(mode->getPlayers().size(), 2);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
