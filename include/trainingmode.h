/* Leonid Lysenko st128618@student.spbu.ru
   Lab2
*/


#ifndef TRAININGMODE_H
#define TRAININGMODE_H

#include "game_mode.h"
#include <utility>
#include <string>
#include <iostream>
#include <vector>
#include "card_factory.h"
#include "magic_card.h"
#include "spell_card.h"
#include "ai_player.h"

/**
 * @class TrainingMode
 * @brief Представляет обучающий режим
 */
class TrainingMode : public GameMode {
protected:
    int m_currentLesson;   ///< Текущий урок
    int m_totalLessons;    ///< Общее количество уроков
    bool m_lessonCompleted;  ///< Флаг завершения текущего урока
    
    struct {
        bool hasPlayedCard;            ///< Флаг разыгрывания карты
        bool hasViewedHelp;            ///< Флаг просмотра справки
        bool hasPlayedCreature;        ///< Флаг разыгрывания существа
        bool hasAttackedWithCreature;  ///< Флаг атаки существом
        bool hasUsedDamageSpell;       ///< Флаг использования урона
        bool hasUsedHealingSpell;      ///< Флаг использования лечения
        bool hasAppliedBuff;           ///< Флаг наложения бафа
        bool hasAppliedDebuff;         ///< Флаг наложения дебафа
        bool hasCompletedCombo;        ///< Флаг выполнения комбо
        bool hasWonTrainingBattle;     ///< Флаг победы в тренировочном бою
    } m_objectives;  ///< Цели обучения
    
    std::vector<std::pair<std::string, std::string>> m_lessons;  ///< Список уроков (название, описание)
    
    /**
     * @brief Инициализировать уроки
     */
    void initializeLessons();
    
    /**
     * @brief Настроить тренировочную колоду для ИИ
     * @param player Указатель на ИИ-игрока
     */
    void setupTrainingDeck(PlayerPtr player);
    
    /**
     * @brief Проверить выполнение целей текущего урока
     */
    void checkLessonObjectives();
    
    /**
     * @brief Получить команду от игрока
     * @return Команда игрока
     */
    std::string getPlayerCommand();

public:
    /**
     * @brief Конструктор для TrainingMode
     */
    TrainingMode();
    
    /**
     * @brief Конструктор для TrainingMode с параметрами
     * @param id Уникальный идентификатор режима
     * @param name Название режима
     * @param description Описание режима
     */
    TrainingMode(int id, const std::string& name, const std::string& description);
    
    /**
     * @brief Деструктор
     */
    virtual ~TrainingMode() = default;
    
    /**
     * @brief Запустить режим тренировки
     * @return True, если режим был успешно запущен, false в противном случае
     */
    bool start() override;
    
    /**
     * @brief Выполнить ход игрока в режиме тренировки
     * @param currentPlayer Текущий игрок
     * @param opponent Противник
     * @return True, если ход был успешно выполнен, false в противном случае
     */
    bool executeTurn(PlayerPtr currentPlayer, PlayerPtr opponent) override;
    
    /**
     * @brief Отобразить текущий урок
     */
    void displayCurrentLesson() const;
    
    /**
     * @brief Настроить тренировочного противника
     */
    void setupTrainingOpponent();
    
    /**
     * @brief Выполнить текущий урок
     * @return True, если урок был успешно выполнен, false в противном случае
     */
    bool executeLesson();
    
    /**
     * @brief Проверить выполнение текущего урока
     * @return True, если урок выполнен, false в противном случае
     */
    bool checkLessonCompletion();
    
    /**
     * @brief Обработать команду пользователя
     * @param command Команда для обработки
     * @return True, если команда обработана успешно, false в противном случае
     */
    bool handleCommand(const std::string& command) override;
    
    /**
     * @brief Отобразить справку по командам режима тренировки
     */
    void displayHelp() const override;
    
    /**
     * @brief Выполнить при завершении режима тренировки
     */
    void onGameEnd() override;
    
    /**
     * @brief Проверить условие завершения режима
     * @return True, если режим завершен, false в противном случае
     */
    bool checkEndCondition() override;
};

#endif // TRAININGMODE_H
