/* Leonid Lysenko st128618@student.spbu.ru
   Lab1
*/

/**
 * @file ai_player.h
 * @brief Класс ИИ-игрока
 */

#ifndef AI_PLAYER_H
#define AI_PLAYER_H

#include "player.h"
#include "spell_card.h"

// Уровни сложности ИИ
enum class DifficultyLevel {
    Easy,    ///< Легкий (случайные ходы)
    Medium,  ///< Средний (базовая стратегия)
    Hard     ///< Сложный (продвинутая стратегия)
};

/**
 * @class AIPlayer
 * @brief Представляет ИИ-игрока, управляемого компьютером
 */
class AIPlayer : public Player {
protected:
    DifficultyLevel m_difficulty;  ///< Уровень сложности ИИ
    
    /**
     * @brief Выбрать лучшую цель для атаки
     * @param opponent Противник
     * @return Указатель на лучшую цель или nullptr
     */
    CharacterCardPtr selectBestTarget(Player* opponent);
    
    /**
     * @brief Выбрать лучшую карту для розыгрыша
     * @return Индекс лучшей карты или -1, если нет подходящих карт
     */
    int selectBestCard() const;
    
    /**
     * @brief Принять решение на основе текущего состояния игры
     * @param opponent Противник
     * @return Индекс выбранной карты или -1 для пропуска хода
     */
    int makeDecision(Player* opponent);

public:
    /**
     * @brief Конструктор для AIPlayer
     * @param id Уникальный идентификатор игрока
     * @param name Имя игрока
     * @param difficulty Уровень сложности ИИ
     * @param maxHealth Максимальное здоровье
     * @param maxMana Максимальная мана
     * @param gold Начальное количество золота
     */
    AIPlayer(int id, std::string name, DifficultyLevel difficulty = DifficultyLevel::Medium,
             int maxHealth = 30, int maxMana = 10, int gold = 100)
        : Player(id, name, maxHealth, maxMana, gold), m_difficulty(difficulty) {}

    /**
     * @brief Получить уровень сложности ИИ
     * @return Уровень сложности
     */
    DifficultyLevel getDifficulty() const {
        return m_difficulty;
    }
    
    /**
     * @brief Установить уровень сложности ИИ
     * @param difficulty Новый уровень сложности
     */
    void setDifficulty(DifficultyLevel difficulty) {
        m_difficulty = difficulty;
    }
    
    /**
     * @brief Выполнить ход ИИ-игрока
     * @param opponent Противник
     * @return True, если ход был успешно выполнен, false в противном случае
     */
    bool takeTurn(Player* opponent) override;
};

#endif // AI_PLAYER_H
