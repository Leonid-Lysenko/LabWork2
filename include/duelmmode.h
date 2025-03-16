/* Leonid Lysenko st128618@student.spbu.ru
   Lab2
*/


#ifndef DUELMMODE_H
#define DUELMMODE_H

#include "game_mode.h"

/**
 * @class DuelMode
 * @brief Представляет режим дуэли (1 на 1)
 */
class DuelMode : public GameMode {
protected:
    PlayerPtr m_winner;  ///< Победитель дуэли (nullptr если ничья)

public:
    /**
     * @brief Конструктор для DuelMode
     */
    DuelMode();
    
    /**
     * @brief Конструктор для DuelMode с параметрами
     * @param id Уникальный идентификатор режима
     * @param name Название режима
     * @param description Описание режима
     */
    DuelMode(int id, const std::string& name, const std::string& description);
    
    /**
     * @brief Инициализировать режим дуэли с заданными игроками
     * @param players Список игроков (должно быть 2)
     * @return True, если инициализация прошла успешно, false в противном случае
     */
    bool initialize(const std::vector<PlayerPtr>& players) override;
    
    /**
     * @brief Запустить режим дуэли
     * @return True, если режим был успешно запущен, false в противном случае
     */
    bool start() override;
    
    /**
     * @brief Выполнить ход игрока в режиме дуэли
     * @param currentPlayer Текущий игрок
     * @param opponent Противник
     * @return True, если ход был успешно выполнен, false в противном случае
     */
    bool executeTurn(PlayerPtr currentPlayer, PlayerPtr opponent) override;
    
    /**
     * @brief Получить противника текущего игрока
     * @return Указатель на противника или nullptr
     */
    PlayerPtr getOpponent() const;
    
    /**
     * @brief Проверить условие завершения дуэли
     * @return True, если дуэль должна быть завершена, false в противном случае
     */
    bool checkEndCondition() override;
    
    /**
     * @brief Отобразить результаты дуэли
     */
    void displayResults() const override;
    
    /**
     * @brief Отобразить справку по командам режима дуэли
     */
    void displayHelp() const override;
    
    /**
     * @brief Получить победителя дуэли
     * @return Указатель на победителя или nullptr если ничья
     */
    PlayerPtr getWinner() const {
        return m_winner;
    }
};

#endif // DUELMMODE_H
