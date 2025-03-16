/* Leonid Lysenko st128618@student.spbu.ru
   Lab2
*/

/**
 * @file card.h
 * @brief Base class for all cards in the game
 */

#ifndef CARD_H
#define CARD_H

#include <string>
#include <memory>
#include <vector>

// Forward declarations
class Player;
#include <vector>
class CharacterCard;
class Player;
class CharacterCard;                       
// Card type enumeration
enum class CardType {
    Character,
    Magic,
    Weapon,
    Spell,
    Armor,
    Accessory,
    Item
};

// Card rarity enumeration
enum class CardRarity {
    Common,
    Uncommon,
    Rare,
    Epic,
    Legendary
};

/**
 * @class Card
 * @brief Base class for all cards in the game
 */
class Card : public std::enable_shared_from_this<Card> {
protected:
    int m_id;                   ///< Unique identifier for the card
    std::string m_name;         ///< Name of the card
    std::string m_description;  ///< Description of the card
    int m_manaCost;             ///< Mana cost to play the card
    CardType m_type;            ///< Type of the card
    CardRarity m_rarity;        ///< Rarity of the card

public:
    /**
     * @brief Constructor for Card
     * @param id Unique identifier for the card
     * @param name Name of the card
     * @param description Description of the card
     * @param manaCost Mana cost to play the card
     * @param type Type of the card
     * @param rarity Rarity of the card
     */
    Card(int id, const std::string& name, const std::string& description,
         int manaCost, CardType type, CardRarity rarity = CardRarity::Common);
    
    /**
     * @brief Virtual destructor
     */
    virtual ~Card() = default;

    /**
     * @brief Get the unique identifier of the card
     * @return The card's ID
     */
    int getId() const;
    
    /**
     * @brief Get the name of the card
     * @return The card's name
     */
    const std::string& getName() const;
    
    /**
     * @brief Get the description of the card
     * @return The card's description
     */
    const std::string& getDescription() const;
    
    /**
     * @brief Get the mana cost of the card
     * @return The card's mana cost
     */
    int getManaCost() const;
    
    /**
     * @brief Get the type of the card
     * @return The card's type
     */
    CardType getType() const;
    
    /**
     * @brief Get the rarity of the card
     * @return The card's rarity
     */
    CardRarity getRarity() const;

    /**
     * @brief Check if the card can be played
     * @param source The player who wants to play the card
     * @param target The target player (optional)
     * @return True if the card can be played, false otherwise
     */
    virtual bool canPlay(const Player* source, const Player* target = nullptr) const;
    
    /**
     * @brief Play the card
     * @param source The player who plays the card
     * @param target The target player (optional)
     * @return True if the card was played successfully, false otherwise
     */
    virtual bool play(Player* source, Player* target = nullptr) = 0;
    
    /**
     * @brief Overload for playing the card with a character target
     * @param source The player who plays the card
     * @param target The target character
     * @return True if the card was played successfully, false otherwise
     */
    virtual bool play(Player* source, CharacterCard* target) {
        return false; // Default implementation does nothing
    }

    /**
     * @brief Convert the card to a string representation
     * @return String representation of the card
     */
    virtual std::string toString() const;
    
    /**
     * @brief Get the string representation of the card type
     * @return String representation of the card type
     */
    std::string getTypeString() const;
    
    /**
     * @brief Get the string representation of the card rarity
     * @return String representation of the card rarity
     */
    std::string getRarityString() const;
    
    /**
     * @brief Virtual method to create a copy of the card
     * @return Shared pointer to a new copy of the card
     */
    virtual std::shared_ptr<Card> clone() const = 0;

    /**
     * @brief Get the cost of the card for bazaar
     * @return The card's cost in gold
     */
    virtual int getCost() const {
        // Default implementation based on rarity
        switch (m_rarity) {
            case CardRarity::Common: return 100;
            case CardRarity::Uncommon: return 200;
            case CardRarity::Rare: return 400;
            case CardRarity::Epic: return 800;
            case CardRarity::Legendary: return 1600;
            default: return 100;
        }
    }
};

// Convenient typedefs
using CardPtr = std::shared_ptr<Card>;
#include <vector>
typedef std::vector<CardPtr> Cards;

#endif // CARD_H
