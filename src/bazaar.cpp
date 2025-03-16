/* Leonid Lysenko st128618@student.spbu.ru
   Lab2
*/


#include "bazaar.h"

Bazaar::Bazaar() : m_gold(0) {
    refreshStock();
}

void Bazaar::refreshStock() {
    m_stock.clear();
    auto& factory = CardFactory::getInstance();
    
    // Добавляем случайные карты в магазин
    for(int i = 0; i < 6; i++) {
        m_stock.push_back(factory.createRandomCard());
    }
}

bool Bazaar::buyCard(Player* player, int index) {
    if (index >= 0 && index < m_stock.size()) {
        auto card = m_stock[index];
        if (player->getGold() >= card->getCost()) {
            player->modifyGold(-card->getCost());
            player->addCardToDeck(card);
            m_stock.erase(m_stock.begin() + index);
            return true;
        }
    }
    return false;
}

bool Bazaar::sellCard(Player* player, int index) {
    if (auto card = player->removeCardFromDeck(index)) {
        int value = card->getCost() / 2;
        player->modifyGold(value);
        return true;
    }
    return false;
}
