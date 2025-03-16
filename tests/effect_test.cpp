/* Leonid Lysenko st128618@student.spbu.ru
   Lab2
*/

class EffectTest : public ::testing::Test {
protected:
    std::shared_ptr<Character> character;
    
    void SetUp() override {
        character = std::make_shared<CharacterCard>(1, "Test", "", 1, CharacterClass::Warrior, 2, 3);
    }
};

TEST_F(EffectTest, BuffEffect) {
    auto buff = std::make_shared<BuffEffect>(1, "Test Buff", "", 2, 2);
    int initialAttack = character->getAttack();
    
    buff->apply(character.get());
    EXPECT_EQ(character->getAttack(), initialAttack + 2);
    
    buff->remove(character.get());
    EXPECT_EQ(character->getAttack(), initialAttack);
}
