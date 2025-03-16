/**
 * @file magic_card.h
 * @brief Magic card class for spells and other magical effects
 */

#ifndef MAGIC_CARD_H
#define MAGIC_CARD_H

#include "card.h"
#include <memory>

// Forward declarations
class Player;
class Effect;

// Magic type enumeration
enum class MagicType {
    DamageSpell,
    Healing,
    Enhancement,
    Curse,
    AreaEffect
};

/**
 * @class MagicCard
 * @brief Represents a magic card in the game
 */
class MagicCard : public Card {
protected:
    MagicType m_magicType;   ///< Type of magic
    int m_power;             ///< Power/strength of the magic effect
    int m_duration;          ///< Duration of the effect (if applicable)

    /**
     * @brief Apply the magic effect
     * @param source The player who plays the card
     * @param target The target player
     * @return True if the effect was applied successfully, false otherwise
     */
    bool applyMagicEffect(Player* source, Player* target);

public:
    /**
     * @brief Constructor for MagicCard
     * @param id Unique identifier for the card
     * @param name Name of the card
     * @param description Description of the card
     * @param manaCost Mana cost to play the card
     * @param magicType Type of magic
     * @param power Power/strength of the magic effect
     * @param duration Duration of the effect (if applicable)
     */
    MagicCard(int id, const std::string& name, const std::string& description,
             int manaCost, CardRarity rarity, MagicType magicType,
             int power, int duration = 0);

    /**
     * @brief Get the type of magic
     * @return The magic type
     */
    MagicType getMagicType() const;
    
    /**
     * @brief Get the power of the magic effect
     * @return The power value
     */
    int getPower() const;
    
    /**
     * @brief Get the duration of the magic effect
     * @return The duration (in turns)
     */
    int getDuration() const;
    
    /**
     * @brief Check if the magic card can be played
     * @param source The player who wants to play the card
     * @param target The target player (optional)
     * @return True if the card can be played, false otherwise
     */
    bool canPlay(const Player* source, const Player* target = nullptr) const override;
    
    /**
     * @brief Play the magic card
     * @param source The player who plays the card
     * @param target The target player (optional)
     * @return True if the card was played successfully, false otherwise
     */
    bool play(Player* source, Player* target = nullptr) override;
    
    /**
     * @brief Convert the magic card to a string representation
     * @return String representation of the magic card
     */
    std::string toString() const override;
    
    /**
     * @brief Get the string representation of the magic type
     * @return String representation of the magic type
     */
    std::string getMagicTypeString() const;
    
    /**
     * @brief Create a copy of the magic card
     * @return Shared pointer to a new copy of the magic card
     */
    std::shared_ptr<Card> clone() const override {
        return std::make_shared<MagicCard>(*this);
    }
};

// Convenient typedef
using MagicCardPtr = std::shared_ptr<MagicCard>;

#endif // MAGIC_CARD_H