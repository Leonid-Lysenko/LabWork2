/**
 * @file game_mode.h
 * @brief Базовый класс для игровых режимов
 */

#ifndef GAME_MODE_H
#define GAME_MODE_H

#include <string>
#include <vector>
#include <memory>
#include "player.h"

/**
 * @class GameMode
 * @brief Базовый класс для всех игровых режимов
 */
class GameMode {
protected:
    int m_id;                        ///< Уникальный идентификатор режима
    std::string m_name;              ///< Название режима
    std::string m_description;       ///< Описание режима
    int m_minPlayers;                ///< Минимальное количество игроков
    int m_maxPlayers;                ///< Максимальное количество игроков
    bool m_isFinished;               ///< Флаг завершения режима
    int m_currentTurn;               ///< Текущий ход
    std::vector<PlayerPtr> m_players;  ///< Список игроков

public:
    /**
     * @brief Конструктор для GameMode
     * @param id Уникальный идентификатор режима
     * @param name Название режима
     * @param description Описание режима
     * @param minPlayers Минимальное количество игроков
     * @param maxPlayers Максимальное количество игроков
     */
    GameMode(int id, const std::string& name, const std::string& description,
             int minPlayers, int maxPlayers);
    
    /**
     * @brief Виртуальный деструктор
     */
    virtual ~GameMode() = default;

    /**
     * @brief Инициализировать режим с заданными игроками
     * @param players Список игроков
     * @return True, если инициализация прошла успешно, false в противном случае
     */
    virtual bool initialize(const std::vector<PlayerPtr>& players);
    
    /**
     * @brief Обновить состояние режима
     * @return True, если обновление прошло успешно, false в противном случае
     */
    virtual bool update();
    
    /**
     * @brief Получить список игроков
     * @return Список игроков
     */
    const std::vector<PlayerPtr>& getPlayers() const;
    
    /**
     * @brief Добавить игрока в режим
     * @param player Указатель на игрока
     * @return True, если игрок был успешно добавлен, false в противном случае
     */
    bool addPlayer(PlayerPtr player);
    
    /**
     * @brief Удалить игрока из режима
     * @param index Индекс игрока для удаления
     * @return True, если игрок был успешно удален, false в противном случае
     */
    bool removePlayer(int index);
    
    /**
     * @brief Получить текущего игрока
     * @return Указатель на текущего игрока или nullptr
     */
    PlayerPtr getCurrentPlayer() const;
    
    /**
     * @brief Перейти к следующему ходу
     */
    virtual void nextTurn();
    
    /**
     * @brief Получить номер текущего хода
     * @return Номер текущего хода
     */
    int getCurrentTurn() const;
    
    /**
     * @brief Проверить, завершен ли режим
     * @return True, если режим завершен, false в противном случае
     */
    bool isFinished() const;
    
    /**
     * @brief Получить начальный размер руки
     * @return Начальный размер руки
     */
    virtual int getInitialHandSize() const;
    
    /**
     * @brief Получить название режима
     * @return Название режима
     */
    std::string getName() const;
    
    /**
     * @brief Получить описание режима
     * @return Описание режима
     */
    std::string getDescription() const;
    
    /**
     * @brief Отобразить текущее состояние игры
     */
    virtual void displayGameState() const;
    
    /**
     * @brief Обработать команду
     * @param command Команда для обработки
     * @return True, если команда была успешно обработана, false в противном случае
     */
    virtual bool handleCommand(const std::string& command);
    
    /**
     * @brief Отобразить справку по командам
     */
    virtual void displayHelp() const;
    
    /**
     * @brief Выполнить при начале игры
     */
    virtual void onGameStart();
    
    /**
     * @brief Выполнить при завершении игры
     */
    virtual void onGameEnd();
    
    /**
     * @brief Отобразить результаты игры
     */
    virtual void displayResults() const;
    
    /**
     * @brief Проверить условие завершения режима
     * @return True, если режим должен быть завершен, false в противном случае
     */
    virtual bool checkEndCondition() {
        return false;  // Базовая реализация всегда возвращает false
    }
    
    /**
     * @brief Запустить режим
     * @return True, если режим был успешно запущен, false в противном случае
     */
    virtual bool start() = 0;
    
    /**
     * @brief Выполнить ход игрока
     * @param currentPlayer Текущий игрок
     * @param opponent Противник
     * @return True, если ход был успешно выполнен, false в противном случае
     */
    virtual bool executeTurn(PlayerPtr currentPlayer, PlayerPtr opponent) = 0;
};

#endif // GAME_MODE_H