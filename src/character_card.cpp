/* Leonid Lysenko st128618@student.spbu.ru
   Lab2
*/

#include "character_card.h"
#include "player.h"
#include <sstream>
#include <algorithm>
#include <iostream>

CharacterCard::CharacterCard(int id, const std::string& name, const std::string& description,
                           int manaCost, CharacterClass characterClass,
                           int attack, int health, int defense, 
                           CardRarity rarity)
    : Card(id, name, description, manaCost, CardType::Character, rarity),
      m_class(characterClass),
      m_attack(attack),
      m_health(health),
      m_maxHealth(health),
      m_defense(defense),
      m_canAttack(false),
      m_hasStatusEffect(false) {
}

CharacterClass CharacterCard::getCharacterClass() const {
    return m_class;
}

int CharacterCard::getAttack() const {
    return m_attack;
}

int CharacterCard::getHealth() const {
    return m_health;
}

int CharacterCard::getMaxHealth() const {
    return m_maxHealth;
}

int CharacterCard::getDefense() const {
    return m_defense;
}

bool CharacterCard::canAttack() const {
    return m_canAttack && isAlive() && !m_hasStatusEffect;
}

void CharacterCard::setCanAttack(bool canAttack) {
    m_canAttack = canAttack;
}

bool CharacterCard::hasStatusEffect() const {
    return m_hasStatusEffect;
}

void CharacterCard::setStatusEffect(bool hasEffect) {
    m_hasStatusEffect = hasEffect;
}

int CharacterCard::modifyHealth(int amount) {
    int oldHealth = m_health;

    if (amount < 0) {
        // Taking damage
        int damage = -amount;
        // Apply defense reduction
        damage = std::max(1, damage - m_defense);
        m_health = std::max(0, m_health - damage);
    } else {
        // Healing
        m_health = std::min(m_maxHealth, m_health + amount);
    }

    return m_health - oldHealth;
}

void CharacterCard::modifyAttack(int amount) {
    m_attack = std::max(0, m_attack + amount);
}

void CharacterCard::modifyDefense(int amount) {
    m_defense = std::max(0, m_defense + amount);
}

bool CharacterCard::isAlive() const {
    return m_health > 0;
}

bool CharacterCard::attack(CharacterCard* target) {
    if (!target || !canAttack() || !target->isAlive()) {
        return false;
    }

    // Deal damage to target
    target->modifyHealth(-m_attack);

    // Take counterattack damage if target survives
    if (target->isAlive()) {
        modifyHealth(-target->getAttack());
    }

    // Cannot attack again this turn
    m_canAttack = false;

    return true;
}

bool CharacterCard::play(Player* source, Player* target) {
    if (!source || !canPlay(source, target)) {
        return false;
    }

    // Spend player's mana
    source->modifyMana(-m_manaCost);

    // Add character to player's field
    source->addCharacterToField(std::static_pointer_cast<CharacterCard>(shared_from_this()));

    // Character cannot attack the turn it is played
    m_canAttack = false;

    return true;
}

void CharacterCard::onTurnStart() {
    if (isAlive()) {
        m_canAttack = true;
    }
}

void CharacterCard::onTurnEnd() {
    // Handle end of turn effects
}

std::string CharacterCard::toString() const {
    std::stringstream ss;
    ss << getClassString() << " " << Card::toString()
       << " [ATK: " << m_attack
       << ", HP: " << m_health << "/" << m_maxHealth
       << ", DEF: " << m_defense << "]";
    return ss.str();
}

std::string CharacterCard::getClassString() const {
    switch (m_class) {
        case CharacterClass::Warrior: return "Warrior";
        case CharacterClass::Mage: return "Mage";
        case CharacterClass::Rogue: return "Rogue";
        case CharacterClass::Priest: return "Priest";
        case CharacterClass::Hunter: return "Hunter";
        case CharacterClass::Paladin: return "Paladin";
        default: return "Unknown";
    }
}

bool CharacterCard::removeEffect(int effectId) {
    auto it = std::find_if(m_effects.begin(), m_effects.end(),
        [effectId](const std::shared_ptr<Effect>& effect) { return effect->getId() == effectId; });
    
    if (it != m_effects.end()) {
        (*it)->remove(this);
        m_effects.erase(it);
        return true;
    }
    return false;
}

void CharacterCard::updateEffects() {
    // Update and remove expired effects
    auto it = m_effects.begin();
    while (it != m_effects.end()) {
        if (!(*it)->update()) {
            // Effect has expired, remove it
            (*it)->remove(this);
            it = m_effects.erase(it);
        } else {
            // Apply periodic effects
            if ((*it)->isPeriodicEffect()) {
                (*it)->apply(this);
            }
            ++it;
        }
    }
}
