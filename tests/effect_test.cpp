#include <gtest/gtest.h>
#include <memory>
#include "character_card.h"
#include "effect.h"

// Мок-эффект для тестирования
class TestEffect : public Effect {
public:
    TestEffect(int id, std::string name, std::string desc, int duration)
        : Effect(id, name, desc, duration) {}
    
    void apply(Character* target) override {
        // Реализация для теста
    }
};

class EffectTest : public ::testing::Test {
protected:
    std::shared_ptr<CharacterCard> character;
    
    void SetUp() override {
        character = std::make_shared<CharacterCard>(1, "Test", "", 1, 
                                                  CharacterClass::Warrior, 2, 3);
    }
};

TEST_F(EffectTest, BuffEffect) {
    auto buff = std::make_shared<TestEffect>(1, "Test Buff", "", 2);
    int initialAttack = character->getAttack();
    
    buff->apply(character.get());
    EXPECT_EQ(character->getAttack(), initialAttack);
}
