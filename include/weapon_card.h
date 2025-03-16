/* Leonid Lysenko st128618@student.spbu.ru
   Lab2
*/


/**
 * @file weapon_card.h
 * @brief Weapon card class for equippable weapons
 */

#ifndef WEAPON_CARD_H
#define WEAPON_CARD_H

#include "card.h"
#include <memory>

// Forward declarations
class Player;
class CharacterCard;

// Weapon type enumeration
enum class WeaponType {
    Sword,
    Bow,
    Staff,
    Dagger
};

/**
 * @class WeaponCard
 * @brief Represents a weapon card in the game
 */
class WeaponCard : public Card, public std::enable_shared_from_this<WeaponCard> {
protected:
    WeaponType m_weaponType;       ///< Type of weapon
    int m_attack;                  ///< Attack bonus provided by the weapon
    int m_durability;              ///< Current durability of the weapon
    int m_maxDurability;           ///< Maximum durability of the weapon
    std::shared_ptr<CharacterCard> m_equippedCharacter;  ///< Character equipped with this weapon

public:
    /**
     * @brief Constructor for WeaponCard
     * @param id Unique identifier for the card
     * @param name Name of the card
     * @param description Description of the card
     * @param manaCost Mana cost to play the card
     * @param weaponType Type of weapon
     * @param attack Attack bonus provided by the weapon
     * @param durability Durability of the weapon
     */
    WeaponCard(int id, const std::string& name, const std::string& description,
              int manaCost, CardRarity rarity, WeaponType weaponType,
              int attack, int durability);

    /**
     * @brief Get the type of weapon
     * @return The weapon type
     */
    WeaponType getWeaponType() const;
    
    /**
     * @brief Get the attack bonus provided by the weapon
     * @return The attack bonus
     */
    int getAttack() const;
    
    /**
     * @brief Get the current durability of the weapon
     * @return The current durability
     */
    int getDurability() const;
    
    /**
     * @brief Get the maximum durability of the weapon
     * @return The maximum durability
     */
    int getMaxDurability() const;
    
    /**
     * @brief Get the character equipped with this weapon
     * @return Shared pointer to the equipped character, or nullptr if none
     */
    std::shared_ptr<CharacterCard> getEquippedCharacter() const;
    
    /**
     * @brief Check if the weapon card can be played
     * @param source The player who wants to play the card
     * @param target The target player (optional)
     * @return True if the card can be played, false otherwise
     */
    bool canPlay(const Player* source, const Player* target = nullptr) const override;
    
    /**
     * @brief Play the weapon card on a specific character
     * @param source The player who plays the card
     * @param target The target player (usually the player who plays the card)
     * @param characterIndex Index of the character to equip the weapon
     * @return True if the card was played successfully, false otherwise
     */
    bool play(Player* source, Player* target, int characterIndex);
    
    /**
     * @brief Play the weapon card (default implementation)
     * @param source The player who plays the card
     * @param target The target player (optional)
     * @return True if the card was played successfully, false otherwise
     */
    bool play(Player* source, Player* target = nullptr) override {
        // Default implementation needs a character index
        return false;
    }
    
    /**
     * @brief Called when the weapon is used in an attack
     */
    void onAttackUsed();
    
    /**
     * @brief Check if the weapon is compatible with a character
     * @param character The character to check
     * @return True if the weapon is compatible, false otherwise
     */
    bool isCompatibleWithCharacter(const std::shared_ptr<CharacterCard>& character) const;
    
    /**
     * @brief Convert the weapon card to a string representation
     * @return String representation of the weapon card
     */
    std::string toString() const override;
    
    /**
     * @brief Get the string representation of the weapon type
     * @return String representation of the weapon type
     */
    std::string getWeaponTypeString() const;
    
    /**
     * @brief Create a copy of the weapon card
     * @return Shared pointer to a new copy of the weapon card
     */
    std::shared_ptr<Card> clone() const override {
        return std::make_shared<WeaponCard>(*this);
    }
};

// Convenient typedef
using WeaponCardPtr = std::shared_ptr<WeaponCard>;

#endif // WEAPON_CARD_H
