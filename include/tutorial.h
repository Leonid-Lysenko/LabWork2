/**
 * @file tutorial.h
 * @brief Класс обучения игре
 */

#ifndef TUTORIAL_H
#define TUTORIAL_H

#include <string>
#include <vector>
#include <functional>
#include "player.h"
#include "card_factory.h"

/**
 * @class Tutorial
 * @brief Представляет обучающую систему для игры
 */
class Tutorial {
private:
    PlayerPtr m_player;  ///< Игрок, проходящий обучение
    std::vector<std::pair<std::string, std::function<bool(Player*)>>> m_lessons;  ///< Список уроков (название, функция)
    
    /**
     * @brief Инициализировать уроки
     */
    void initializeLessons();
    
    /**
     * @brief Базовый урок по основам игры
     * @param player Игрок, проходящий обучение
     * @return True, если урок пройден успешно, false в противном случае
     */
    static bool basicLesson(Player* player);
    
    /**
     * @brief Урок по боевым механикам
     * @param player Игрок, проходящий обучение
     * @return True, если урок пройден успешно, false в противном случае
     */
    static bool combatLesson(Player* player);
    
    /**
     * @brief Урок по эффектам и статусам
     * @param player Игрок, проходящий обучение
     * @return True, если урок пройден успешно, false в противном случае
     */
    static bool effectsLesson(Player* player);

public:
    /**
     * @brief Конструктор для Tutorial
     */
    Tutorial();
    
    /**
     * @brief Конструктор для Tutorial с игроком
     * @param player Игрок, проходящий обучение
     */
    Tutorial(PlayerPtr player) : m_player(player) {
        initializeLessons();
    }
    
    /**
     * @brief Запустить обучение
     * @return True, если обучение прошло успешно, false в противном случае
     */
    bool start();
    
    /**
     * @brief Отобразить информацию об обучении
     */
    void displayInfo() const;
    
    /**
     * @brief Установить игрока, проходящего обучение
     * @param player Игрок, проходящий обучение
     */
    void setPlayer(PlayerPtr player) {
        m_player = player;
    }
    
    /**
     * @brief Получить игрока, проходящего обучение
     * @return Указатель на игрока
     */
    PlayerPtr getPlayer() const {
        return m_player;
    }
};

#endif // TUTORIAL_H