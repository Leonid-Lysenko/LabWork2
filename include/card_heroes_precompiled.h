#ifndef CARD_HEROES_PRECOMPILED_H
#define CARD_HEROES_PRECOMPILED_H

// Стандартные библиотеки
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <random>
#include <functional>

// Предварительные объявления классов для разрешения циклических зависимостей
class Card;
class Player;
class CharacterCard;
class Effect;
class CardFactory;
class GameMode;

// Типы указателей для работы с классами
typedef std::shared_ptr<Card> CardPtr;
typedef std::shared_ptr<CharacterCard> CharacterCardPtr;
typedef std::shared_ptr<Effect> EffectPtr;
typedef std::shared_ptr<Player> PlayerPtr;
typedef std::vector<CardPtr> Cards;
typedef std::vector<CharacterCardPtr> Characters;

#endif // CARD_HEROES_PRECOMPILED_H