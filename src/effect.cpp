/* Leonid Lysenko st128618@student.spbu.ru
   Lab2
*/


// effect.cpp
#include "effect.h"
#include "character_card.h"
Effect::Effect(int id, std::string name, std::string description, int duration)
    : m_id(id), m_name(name), m_description(description), m_duration(duration) {}

bool Effect::update() {
    if (m_duration > 0) m_duration--;
    return m_duration != 0;
}
