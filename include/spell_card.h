/* Leonid Lysenko st128618@student.spbu.ru
   Lab2
*/


/**
 * @file spell_card.h
 * @brief Spell card class for spells
 */

#ifndef SPELL_CARD_H
#define SPELL_CARD_H

#include "card.h"
#include <memory>

// Forward declarations
class Player;
class CharacterCard;

// Spell type enumeration
enum class SpellType {
    Damage,
    Healing,
    Buff,
    Debuff,
    Draw,
    AoE  // Area of Effect
};

/**
 * @class SpellCard
 * @brief Represents a spell card in the game
 */
class SpellCard : public Card {
protected:
    SpellType m_spellType;  ///< Type of spell
    int m_power;            ///< Power/strength of the spell
    int m_duration;         ///< Duration of the effect (if applicable)

public:
    /**
     * @brief Constructor for SpellCard
     * @param id Unique identifier for the card
     * @param name Name of the card
     * @param description Description of the card
     * @param manaCost Mana cost to play the card
     * @param spellType Type of spell
     * @param power Power/strength of the spell
     * @param duration Duration of the effect (if applicable)
     */
    SpellCard(int id, const std::string& name, const std::string& description,
             int manaCost, SpellType spellType, int power, 
             int duration = 0, CardRarity rarity = CardRarity::Common);

    /**
     * @brief Get the type of spell
     * @return The spell type
     */
    SpellType getSpellType() const;
    
    /**
     * @brief Get the power of the spell
     * @return The power value
     */
    int getPower() const;
    
    /**
     * @brief Get the duration of the spell effect
     * @return The duration (in turns)
     */
    int getDuration() const;
    
    /**
     * @brief Check if the spell card can be played
     * @param source The player who wants to play the card
     * @param target The target player or character (optional)
     * @return True if the card can be played, false otherwise
     */
    bool canPlay(const Player* source, const Player* target = nullptr) const override;
    
    /**
     * @brief Play the spell card with a player target
     * @param source The player who plays the card
     * @param target The target player (optional)
     * @return True if the card was played successfully, false otherwise
     */
    bool play(Player* source, Player* target = nullptr) override;
    
    /**
     * @brief Play the spell card with a character target
     * @param source The player who plays the card
     * @param target The target character
     * @return True if the card was played successfully, false otherwise
     */
    bool play(Player* source, CharacterCard* target) override;
    
    /**
     * @brief Convert the spell card to a string representation
     * @return String representation of the spell card
     */
    std::string toString() const override;
    
    /**
     * @brief Get the string representation of the spell type
     * @return String representation of the spell type
     */
    std::string getSpellTypeString() const;
    
    /**
     * @brief Create a copy of the spell card
     * @return Shared pointer to a new copy of the spell card
     */
    std::shared_ptr<Card> clone() const override {
        return std::make_shared<SpellCard>(*this);
    }
};

// Convenient typedef
using SpellCardPtr = std::shared_ptr<SpellCard>;

#endif // SPELL_CARD_H
