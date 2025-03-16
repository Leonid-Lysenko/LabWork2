/* Leonid Lysenko st128618@student.spbu.ru
   Lab2
*/

/**
 * @file armor_card.h
 * @brief Armor card class for equippable armor
 */

#ifndef ARMOR_CARD_H
#define ARMOR_CARD_H

#include "card.h"
#include <memory>

// Forward declarations
class Player;
class CharacterCard;

/**
 * @class ArmorCard
 * @brief Represents an armor card in the game
 */
class ArmorCard : public Card {
protected:
    int m_defense;      ///< Defense bonus provided by the armor
    int m_durability;   ///< Durability of the armor

public:
    /**
     * @brief Constructor for ArmorCard
     * @param id Unique identifier for the card
     * @param name Name of the card
     * @param description Description of the card
     * @param manaCost Mana cost to play the card
     * @param defense Defense bonus provided by the armor
     * @param durability Durability of the armor
     */
    ArmorCard(int id, const std::string& name, const std::string& description,
             int manaCost, int defense, int durability,
             CardRarity rarity = CardRarity::Common);

    /**
     * @brief Get the defense bonus provided by the armor
     * @return The defense bonus
     */
    int getDefense() const {
        return m_defense;
    }
    
    /**
     * @brief Get the durability of the armor
     * @return The durability
     */
    int getDurability() const {
        return m_durability;
    }
    
    /**
     * @brief Check if the armor card can be played
     * @param source The player who wants to play the card
     * @param target The target character (optional)
     * @return True if the card can be played, false otherwise
     */
    bool canPlay(const Player* source, CharacterCard* target = nullptr) const {
        return Card::canPlay(source) && target != nullptr;
    }
    
    /**
     * @brief Play the armor card on a character
     * @param source The player who plays the card
     * @param target The target character
     * @return True if the card was played successfully, false otherwise
     */
    bool play(Player* source, CharacterCard* target) override;
    
    /**
     * @brief Play the armor card (default implementation)
     * @param source The player who plays the card
     * @param target The target player (optional)
     * @return True if the card was played successfully, false otherwise
     */
    bool play(Player* source, Player* target = nullptr) override {
        // Default implementation needs a character target
        return false;
    }
    
    /**
     * @brief Reduce durability when damaged
     * @param amount Amount of damage taken
     * @return True if the armor is still intact, false if it breaks
     */
    bool reduceDurability(int amount) {
        m_durability -= amount;
        return m_durability > 0;
    }
    
    /**
     * @brief Convert the armor card to a string representation
     * @return String representation of the armor card
     */
    std::string toString() const override {
        return "Armor: " + m_name + " [DEF: " + std::to_string(m_defense) + 
               ", DUR: " + std::to_string(m_durability) + "] - " + m_description;
    }
    
    /**
     * @brief Create a copy of the armor card
     * @return Shared pointer to a new copy of the armor card
     */
    std::shared_ptr<Card> clone() const override {
        return std::make_shared<ArmorCard>(*this);
    }
};

// Convenient typedef
using ArmorCardPtr = std::shared_ptr<ArmorCard>;

#endif // ARMOR_CARD_H
