/* Leonid Lysenko st128618@student.spbu.ru
   Lab2
*/

/**
 * @file status_effect.cpp
 * @brief Реализация класса статусных эффектов
 */

#include "status_effect.h"
#include "character_card.h"
#include <iostream>

StatusEffect::StatusEffect(int id, std::string name, std::string description,
                          int duration, StatusType type)
    : Effect(id, name, description, duration), m_type(type) {
}

void StatusEffect::apply(Character* target) {
    if (!target) {
        return;
    }
    
    // Устанавливаем флаг наличия эффекта
    target->setStatusEffect(true);
    
    // Применяем эффект в зависимости от типа
    switch (m_type) {
        case StatusType::Stun:
            // Оглушение - персонаж не может действовать
            target->setCanAct(false);
            std::cout << target->getName() << " оглушен и не может действовать!" << std::endl;
            break;
            
        case StatusType::Poison:
            // Отравление - наносит урон каждый ход
            target->modifyHealth(-2);
            std::cout << target->getName() << " получает 2 урона от отравления!" << std::endl;
            break;
            
        case StatusType::Shield:
            // Щит - увеличивает защиту
            target->modifyDefense(5);
            std::cout << target->getName() << " получает +5 к защите от щита!" << std::endl;
            break;
            
        default:
            std::cerr << "Неизвестный тип статусного эффекта!" << std::endl;
            break;
    }
}

void StatusEffect::remove(Character* target) {
    if (!target) {
        return;
    }
    
    // Снимаем эффект в зависимости от типа
    switch (m_type) {
        case StatusType::Stun:
            // Снимаем оглушение - персонаж снова может действовать
            target->setCanAct(true);
            std::cout << target->getName() << " больше не оглушен." << std::endl;
            break;
            
        case StatusType::Poison:
            // При снятии отравления ничего специального не делаем
            std::cout << target->getName() << " больше не отравлен." << std::endl;
            break;
            
        case StatusType::Shield:
            // Снимаем щит - уменьшаем защиту
            target->modifyDefense(-5);
            std::cout << target->getName() << " теряет +5 к защите от щита." << std::endl;
            break;
            
        default:
            break;
    }
    
    // Проверяем, есть ли еще эффекты на персонаже
    // При полной реализации нужно добавить проверку наличия других эффектов
    target->setStatusEffect(false);
}
