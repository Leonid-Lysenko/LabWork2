#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <random>
#include "card.h"  
#include "character_card.h"
#include "effect.h"

// Предварительные объявления
class Card;
class CharacterCard;
class Effect;

// Типы для работы с коллекциями карт
typedef std::shared_ptr<Card> CardPtr;
typedef std::vector<CardPtr> Cards;
typedef std::shared_ptr<CharacterCard> CharacterCardPtr;
typedef std::vector<CharacterCardPtr> Characters;
typedef std::shared_ptr<Effect> EffectPtr;

/**
 * @class Player
 * @brief Базовый класс для всех игроков в игре
 */
class Player : public std::enable_shared_from_this<Player> {
protected:
    int m_id;                           ///< Уникальный идентификатор игрока
    std::string m_name;                 ///< Имя игрока
    int m_health;                       ///< Текущее здоровье
    int m_maxHealth;                    ///< Максимальное здоровье
    int m_mana;                         ///< Текущая мана
    int m_maxMana;                      ///< Максимальная мана
    int m_gold;                         ///< Количество золота
    
    std::vector<CardPtr> m_deck;
    std::vector<CardPtr> m_hand;
    Characters m_field;                 ///< Поле игрока (существа в игре)
    CharacterCardPtr m_selectedCharacter; ///< Выбранный персонаж
    std::vector<EffectPtr> m_effects;   ///< Эффекты на игроке

public:
    /**
     * @brief Конструктор для Player
     * @param id Уникальный идентификатор игрока
     * @param name Имя игрока
     * @param maxHealth Максимальное здоровье
     * @param maxMana Максимальная мана
     * @param gold Начальное количество золота
     */
    Player(int id, std::string name, int maxHealth = 30, int maxMana = 10, int gold = 100);
    
    /**
     * @brief Виртуальный деструктор
     */
    virtual ~Player() = default;

    /**
     * @brief Получить уникальный идентификатор игрока
     * @return Идентификатор игрока
     */
    int getId() const {
        return m_id;
    }
    
    /**
     * @brief Получить имя игрока
     * @return Имя игрока
     */
    const std::string& getName() const {
        return m_name;
    }
    
    /**
     * @brief Получить текущее здоровье игрока
     * @return Текущее здоровье
     */
    int getHealth() const {
        return m_health;
    }
    
    /**
     * @brief Получить максимальное здоровье игрока
     * @return Максимальное здоровье
     */
    int getMaxHealth() const {
        return m_maxHealth;
    }
    
    /**
     * @brief Получить текущую ману игрока
     * @return Текущая мана
     */
    int getMana() const {
        return m_mana;
    }
    
    /**
     * @brief Получить максимальную ману игрока
     * @return Максимальная мана
     */
    int getMaxMana() const {
        return m_maxMana;
    }
    
    /**
     * @brief Получить количество золота игрока
     * @return Количество золота
     */
    int getGold() const {
        return m_gold;
    }
    
    /**
     * @brief Установить текущее здоровье игрока
     * @param health Новое значение здоровья
     */
    void setHealth(int health) {
        m_health = std::min(health, m_maxHealth);
    }
    
    /**
     * @brief Установить максимальное здоровье игрока
     * @param maxHealth Новое максимальное здоровье
     */
    void setMaxHealth(int maxHealth) {
        m_maxHealth = maxHealth;
        m_health = std::min(m_health, m_maxHealth);
    }
    
    /**
     * @brief Установить текущую ману игрока
     * @param mana Новое значение маны
     */
    void setMana(int mana) {
        m_mana = std::min(mana, m_maxMana);
    }
    
    /**
     * @brief Установить максимальную ману игрока
     * @param maxMana Новое максимальное значение маны
     */
    void setMaxMana(int maxMana) {
        m_maxMana = maxMana;
        m_mana = std::min(m_mana, m_maxMana);
    }
    
    /**
     * @brief Изменить здоровье игрока
     * @param amount Количество (положительное для лечения, отрицательное для урона)
     * @return Фактическое изменение здоровья
     */
    int modifyHealth(int amount) {
        int oldHealth = m_health;
        if (amount < 0) {
            // Получение урона
            m_health = std::max(0, m_health + amount);
        } else {
            // Лечение
            m_health = std::min(m_maxHealth, m_health + amount);
        }
        return m_health - oldHealth;
    }
    
    /**
     * @brief Изменить ману игрока
     * @param amount Количество (положительное для восстановления, отрицательное для траты)
     * @return Фактическое изменение маны
     */
    int modifyMana(int amount) {
        int oldMana = m_mana;
        if (amount < 0) {
            // Трата маны
            m_mana = std::max(0, m_mana + amount);
        } else {
            // Восстановление маны
            m_mana = std::min(m_maxMana, m_mana + amount);
        }
        return m_mana - oldMana;
    }
    
    /**
     * @brief Изменить золото игрока
     * @param amount Количество (положительное для получения, отрицательное для траты)
     * @return Фактическое изменение золота
     */
    int modifyGold(int amount) {
        int oldGold = m_gold;
        m_gold = std::max(0, m_gold + amount);
        return m_gold - oldGold;
    }
    
    /**
     * @brief Проверить, жив ли игрок
     * @return True, если игрок жив, false в противном случае
     */
    bool isAlive() const {
        return m_health > 0;
    }
    
    /**
     * @brief Получить колоду игрока
     * @return Ссылка на колоду
     */
    const Cards& getDeck() const {
        return m_deck;
    }
    
    /**
     * @brief Получить руку игрока
     * @return Ссылка на руку
     */
    const Cards& getHand() const {
        return m_hand;
    }
    
    /**
     * @brief Получить поле игрока
     * @return Ссылка на поле
     */
    const Characters& getField() const {
        return m_field;
    }
    
    /**
     * @brief Получить выбранного персонажа
     * @return Указатель на выбранного персонажа или nullptr
     */
    CharacterCardPtr getSelectedCharacter() const {
        return m_selectedCharacter;
    }
    
    /**
     * @brief Установить колоду игрока
     * @param deck Новая колода
     */
    void setDeck(const Cards& deck) {
        m_deck = deck;
    }
    
    /**
     * @brief Перемешать колоду игрока
     */
    void shuffleDeck() {
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(m_deck.begin(), m_deck.end(), g);
    }
    
    /**
     * @brief Взять карты из колоды
     * @param count Количество карт для взятия
     */
    void drawCard(int count);
    
    /**
     * @brief Добавить карту в руку
     * @param card Карта для добавления
     */
    void addCardToHand(CardPtr card) {
        m_hand.push_back(card);
    }
    
    /**
     * @brief Добавить карту в колоду
     * @param card Карта для добавления
     */
    void addCardToDeck(CardPtr card) {
        m_deck.push_back(card);
    }
    
    /**
     * @brief Удалить карту из колоды
     * @param index Индекс карты для удаления
     * @return Удаленная карта или nullptr
     */
    CardPtr removeCardFromDeck(int index) {
        if (index >= 0 && index < m_deck.size()) {
            CardPtr card = m_deck[index];
            m_deck.erase(m_deck.begin() + index);
            return card;
        }
        return nullptr;
    }
    
    /**
     * @brief Добавить персонажа на поле
     * @param character Персонаж для добавления
     */
    void addCharacterToField(CharacterCardPtr character) {
        m_field.push_back(character);
    }
    
    /**
     * @brief Удалить персонажа с поля
     * @param index Индекс персонажа для удаления
     * @return Удаленный персонаж или nullptr
     */
    CharacterCardPtr removeCharacterFromField(int index) {
        if (index >= 0 && index < m_field.size()) {
            CharacterCardPtr character = m_field[index];
            m_field.erase(m_field.begin() + index);
            return character;
        }
        return nullptr;
    }
    
    /**
     * @brief Разыграть карту
     * @param index Индекс карты в руке
     * @param target Целевой игрок
     * @return True, если карта была успешно разыграна, false в противном случае
     */
    bool playCard(int index, Player* target = nullptr);
    
    /**
     * @brief Добавить эффект на игрока
     * @param effect Эффект для добавления
     */
    void addEffect(EffectPtr effect) {
        m_effects.push_back(effect);
    }
    
    /**
     * @brief Удалить эффект с игрока
     * @param effectId Идентификатор эффекта для удаления
     * @return True, если эффект был удален, false в противном случае
     */
    bool removeEffect(int effectId) {
        auto it = std::find_if(m_effects.begin(), m_effects.end(),
            [effectId](const EffectPtr& effect) { return effect->getId() == effectId; });
        
        if (it != m_effects.end()) {
            (*it)->remove(nullptr);  // Очистить эффект при удалении
            m_effects.erase(it);
            return true;
        }
        return false;
    }
    
    /**
     * @brief Обновить состояние всех эффектов
     */
    void updateEffects();
    
    /**
     * @brief Начать ход игрока
     */
    virtual void startTurn();
    
    /**
     * @brief Закончить ход игрока
     */
    virtual void endTurn();
    
    /**
     * @brief Обновить состояние игрока
     * @return True, если обновление прошло успешно, false в противном случае
     */
    virtual bool update();
    
    /**
     * @brief Выполнить ход игрока
     * @param opponent Противник
     * @return True, если ход был успешно выполнен, false в противном случае
     */
    virtual bool takeTurn(Player* opponent) = 0;
    
    /**
     * @brief Отобразить статус игрока
     */
    virtual void displayStatus() const;
    
    /**
     * @brief Сбросить статистику игрока
     */
    virtual void resetStats() {
        m_health = m_maxHealth;
        m_mana = m_maxMana;
    }
    
    /**
     * @brief Очистить поле игрока
     */
    void clearBoard() {
        m_field.clear();
    }
    
    /**
     * @brief Очистить руку игрока
     */
    void clearHand() {
        m_hand.clear();
    }
    
    /**
     * @brief Очистить колоду игрока
     */
    void clearDeck() {
        m_deck.clear();
    }
};

// Удобное определение типа
using PlayerPtr = std::shared_ptr<Player>;

#endif // PLAYER_H