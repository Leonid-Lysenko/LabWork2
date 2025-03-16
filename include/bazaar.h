/* Leonid Lysenko st128618@student.spbu.ru
   Lab2
*/

/**
 * @file bazaar.h
 * @brief Класс магазина карт
 */

#ifndef BAZAAR_H
#define BAZAAR_H

#include <vector>
#include <memory>
#include "card.h"
#include "player.h"
#include "card_factory.h"

/**
 * @class Bazaar
 * @brief Представляет магазин карт в игре
 */
class Bazaar {
private:
    Cards m_stock;     ///< Ассортимент карт
    int m_gold;        ///< Количество золота магазина
    PlayerPtr m_player; ///< Игрок в магазине

public:
    /**
     * @brief Конструктор для Bazaar
     */
    Bazaar();
    
    /**
     * @brief Конструктор для Bazaar с игроком
     * @param player Игрок, который посещает магазин
     */
    Bazaar(PlayerPtr player) : m_gold(0), m_player(player) {
        refreshStock();
    }
    
    /**
     * @brief Обновить ассортимент карт
     */
    void refreshStock();
    
    /**
     * @brief Купить карту
     * @param player Игрок, который покупает
     * @param index Индекс карты в ассортименте
     * @return True, если покупка прошла успешно, false в противном случае
     */
    bool buyCard(Player* player, int index);
    
    /**
     * @brief Продать карту
     * @param player Игрок, который продает
     * @param index Индекс карты в колоде игрока
     * @return True, если продажа прошла успешно, false в противном случае
     */
    bool sellCard(Player* player, int index);
    
    /**
     * @brief Получить ассортимент карт
     * @return Ссылка на ассортимент
     */
    const Cards& getStock() const {
        return m_stock;
    }
    
    /**
     * @brief Войти в магазин
     * @return True, если вход прошел успешно, false в противном случае
     */
    bool enter() {
        if (!m_player) return false;
        
        displayWelcomeMessage();
        
        bool staying = true;
        while (staying) {
            displayMenu();
            int choice = getMenuChoice();
            staying = processMenuChoice(choice);
        }
        
        return true;
    }
    
    /**
     * @brief Отобразить приветственное сообщение
     */
    void displayWelcomeMessage() const;
    
    /**
     * @brief Отобразить меню магазина
     */
    void displayMenu() const;
    
    /**
     * @brief Получить выбор пункта меню от пользователя
     * @return Номер выбранного пункта меню
     */
    int getMenuChoice() const;
    
    /**
     * @brief Обработать выбор пункта меню
     * @param choice Номер выбранного пункта меню
     * @return True, если пользователь хочет остаться в магазине, false в противном случае
     */
    bool processMenuChoice(int choice);
};

#endif // BAZAAR_H
