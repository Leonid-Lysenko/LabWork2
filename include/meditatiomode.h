/* Leonid Lysenko st128618@student.spbu.ru
   Lab2
*/


#ifndef MEDITATIOMODE_H
#define MEDITATIOMODE_H

#include "game_mode.h"

/**
 * @class MeditationMode
 * @brief Представляет режим медитации для экспериментов
 */
class MeditationMode : public GameMode {
protected:
    bool m_infiniteMana;      ///< Флаг бесконечной маны
    bool m_infiniteHealth;    ///< Флаг бесконечного здоровья
    bool m_unlimitedCards;    ///< Флаг неограниченного количества карт
    
    /**
     * @brief Настроить параметры режима
     */
    void setupModeOptions();
    
    /**
     * @brief Применить настройки режима к игроку
     */
    void applyModeSettings();
    
    /**
     * @brief Обработать команду тестирования
     * @param args Аргументы команды
     */
    void handleTestCommand(const std::string& args);
    
    /**
     * @brief Тестирование комбинации карт
     */
    void testCardCombo();
    
    /**
     * @brief Тестирование эффекта
     * @param effectId Идентификатор эффекта
     */
    void testEffect(int effectId);
    
    /**
     * @brief Тестирование урона
     * @param damage Величина урона
     */
    void testDamage(int damage);

public:
    /**
     * @brief Конструктор для MeditationMode
     */
    MeditationMode();
    
    /**
     * @brief Инициализировать режим медитации с заданными игроками
     * @param players Список игроков (обычно 1)
     * @return True, если инициализация прошла успешно, false в противном случае
     */
    bool initialize(const std::vector<PlayerPtr>& players) override;
    
    /**
     * @brief Запустить режим медитации
     * @return True, если режим был успешно запущен, false в противном случае
     */
    bool start() override;
    
    /**
     * @brief Выполнить ход игрока в режиме медитации
     * @param currentPlayer Текущий игрок
     * @param opponent Противник (обычно nullptr)
     * @return True, если ход был успешно выполнен, false в противном случае
     */
    bool executeTurn(PlayerPtr currentPlayer, PlayerPtr opponent) override {
        return true;  // В режиме медитации нет стандартных ходов
    }
    
    /**
     * @brief Восстановить ресурсы игрока (мана, здоровье, карты)
     */
    void refreshResources();
    
    /**
     * @brief Обработать команду
     * @param command Команда для обработки
     * @return True, если команда была успешно обработана, false в противном случае
     */
    bool handleCommand(const std::string& command) override;
    
    /**
     * @brief Сбросить состояние игры к начальному
     */
    void resetGameState();
};

#endif // MEDITATIOMODE_H
