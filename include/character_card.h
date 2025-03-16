/**
 * @file character_card.h
 * @brief Character card class for creatures/minions
 */

#ifndef CHARACTER_CARD_H
#define CHARACTER_CARD_H

#include "card.h"
#include <memory>
#include <vector>

// Forward declaration
class WeaponCard;
class Player;
class Effect;

// Character class enumeration
enum class CharacterClass {
    Warrior,
    Mage,
    Rogue,
    Priest,
    Hunter,
    Paladin
};

/**
 * @class CharacterCard
 * @brief Represents a character/creature card in the game
 */
class CharacterCard : public Card, public std::enable_shared_from_this<CharacterCard> {
protected:
    CharacterClass m_class;     ///< Class of the character
    int m_attack;               ///< Attack value
    int m_health;               ///< Current health
    int m_maxHealth;            ///< Maximum health
    int m_defense;              ///< Defense value
    bool m_canAttack;           ///< Whether the character can attack
    bool m_hasStatusEffect;     ///< Whether the character has a status effect
    
    std::shared_ptr<WeaponCard> m_weapon;    ///< Equipped weapon
    std::vector<std::shared_ptr<Effect>> m_effects;  ///< Applied effects

public:
    /**
     * @brief Constructor for CharacterCard
     * @param id Unique identifier for the card
     * @param name Name of the card
     * @param description Description of the card
     * @param manaCost Mana cost to play the card
     * @param characterClass Class of the character
     * @param attack Initial attack value
     * @param health Initial health value
     * @param defense Initial defense value
     */
    CharacterCard(int id, const std::string& name, const std::string& description,
                 int manaCost, CharacterClass characterClass,
                 int attack, int health, int defense = 0, 
                 CardRarity rarity = CardRarity::Common);

    /**
     * @brief Get the class of the character
     * @return The character's class
     */
    CharacterClass getCharacterClass() const;
    
    /**
     * @brief Get the attack value of the character
     * @return The character's attack value
     */
    int getAttack() const;
    
    /**
     * @brief Get the current health of the character
     * @return The character's current health
     */
    int getHealth() const;
    
    /**
     * @brief Get the maximum health of the character
     * @return The character's maximum health
     */
    int getMaxHealth() const;
    
    /**
     * @brief Get the defense value of the character
     * @return The character's defense value
     */
    int getDefense() const;
    
    /**
     * @brief Check if the character can attack
     * @return True if the character can attack, false otherwise
     */
    bool canAttack() const;
    
    /**
     * @brief Set whether the character can attack
     * @param canAttack True if the character can attack, false otherwise
     */
    void setCanAttack(bool canAttack);
    
    /**
     * @brief Check if the character has a status effect
     * @return True if the character has a status effect, false otherwise
     */
    bool hasStatusEffect() const;
    
    /**
     * @brief Set whether the character has a status effect
     * @param hasEffect True if the character has a status effect, false otherwise
     */
    void setStatusEffect(bool hasEffect);
    
    /**
     * @brief Modify the health of the character
     * @param amount Amount to modify (positive for healing, negative for damage)
     * @return The actual amount of health changed
     */
    int modifyHealth(int amount);
    
    /**
     * @brief Modify the attack value of the character
     * @param amount Amount to modify
     */
    void modifyAttack(int amount);
    
    /**
     * @brief Modify the defense value of the character
     * @param amount Amount to modify
     */
    void modifyDefense(int amount);
    
    /**
     * @brief Check if the character is alive
     * @return True if the character is alive, false otherwise
     */
    bool isAlive() const;
    
    /**
     * @brief Attack another character
     * @param target The target character
     * @return True if the attack was successful, false otherwise
     */
    bool attack(CharacterCard* target);
    
    /**
     * @brief Play the character card
     * @param source The player who plays the card
     * @param target The target player (usually the player who plays the card)
     * @return True if the card was played successfully, false otherwise
     */
    bool play(Player* source, Player* target = nullptr) override;
    
    /**
     * @brief Called at the start of the turn
     */
    void onTurnStart();
    
    /**
     * @brief Called at the end of the turn
     */
    void onTurnEnd();
    
    /**
     * @brief Convert the character card to a string representation
     * @return String representation of the character card
     */
    std::string toString() const override;
    
    /**
     * @brief Get the string representation of the character class
     * @return String representation of the character class
     */
    std::string getClassString() const;
    
    /**
     * @brief Create a copy of the character card
     * @return Shared pointer to a new copy of the character card
     */
    std::shared_ptr<Card> clone() const override {
        return std::make_shared<CharacterCard>(*this);
    }
    
    /**
     * @brief Get the equipped weapon
     * @return Shared pointer to the equipped weapon, or nullptr if none
     */
    std::shared_ptr<WeaponCard> getWeapon() const {
        return m_weapon;
    }
    
    /**
     * @brief Equip a weapon
     * @param weapon The weapon to equip
     */
    void equipWeapon(std::shared_ptr<WeaponCard> weapon) {
        m_weapon = weapon;
    }
    
    /**
     * @brief Unequip the current weapon
     */
    void unequipWeapon() {
        m_weapon = nullptr;
    }
    
    /**
     * @brief Add an effect to the character
     * @param effect The effect to add
     */
    void addEffect(std::shared_ptr<Effect> effect) {
        m_effects.push_back(effect);
    }
    
    /**
     * @brief Remove an effect from the character
     * @param effectId The ID of the effect to remove
     * @return True if the effect was removed, false otherwise
     */
    bool removeEffect(int effectId);
    
    /**
     * @brief Update all effects on the character
     */
    void updateEffects();
    
    /**
     * @brief Set whether the character can act (for status effects)
     * @param canAct True if the character can act, false otherwise
     */
    void setCanAct(bool canAct) {
        m_canAttack = canAct;
    }
};

// Convenient typedefs
using CharacterCardPtr = std::shared_ptr<CharacterCard>;
using Characters = std::vector<CharacterCardPtr>;

#endif // CHARACTER_CARD_H