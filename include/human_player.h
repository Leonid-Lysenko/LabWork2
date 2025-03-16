/* Leonid Lysenko st128618@student.spbu.ru
   Lab2
*/


/**
 * @file human_player.h
 * @brief Класс игрока-человека
 */

#ifndef HUMAN_PLAYER_H
#define HUMAN_PLAYER_H

#include "player.h"
#include <iostream>
#include <string>

/**
 * @class HumanPlayer
 * @brief Представляет игрока-человека, управляемого пользователем
 */
class HumanPlayer : public Player {
public:
    /**
     * @brief Конструктор для HumanPlayer
     * @param id Уникальный идентификатор игрока
     * @param name Имя игрока
     * @param maxHealth Максимальное здоровье
     * @param maxMana Максимальная мана
     * @param gold Начальное количество золота
     */
    HumanPlayer(int id, std::string name, int maxHealth = 30, int maxMana = 10, int gold = 100)
        : Player(id, name, maxHealth, maxMana, gold) {}

    /**
     * @brief Выполнить ход игрока
     * @param opponent Противник
     * @return True, если ход был успешно выполнен, false в противном случае
     */
    bool takeTurn(Player* opponent) override;
    
    /**
     * @brief Отобразить справку по командам
     */
    void displayHelp() const;
    
    /**
     * @brief Обработать команду пользователя
     * @param command Команда пользователя
     * @param opponent Противник (если нужен)
     * @return True, если команда была успешно обработана, false в противном случае
     */
    bool handleCommand(const std::string& command, Player* opponent);
};

#endif // HUMAN_PLAYER_H
