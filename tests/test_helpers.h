// test_helpers.h
#ifndef TEST_HELPERS_H
#define TEST_HELPERS_H

#include "player.h"
#include "card.h"

class TestPlayer : public Player {
public:
    TestPlayer(int id, const std::string& name, int health, int mana)
        : Player(id, name, health, mana) {}
    
    bool takeTurn(Player* opponent) override { 
        (void)opponent;
        return true; 
    }
    
    void displayStatus() const override {}
    void displayHelp() const override {}
};

class TestCard : public Card {
public:
    TestCard(int id, const std::string& name) 
        : Card(id, name, "", 0, CardType::Creature, CardRarity::Common) {}
    
    bool play(Player* source, Player* target = nullptr) override { 
        (void)source; (void)target;
        return true; 
    }
    
    std::shared_ptr<Card> clone() const override { 
        return std::make_shared<TestCard>(*this); 
    }
};

#endif // TEST_HELPERS_H
