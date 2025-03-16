# Description of the Card Heroes Battle system

## Introduction
Card Heroes Battle is a card game with elements of collecting, implemented in C++. The game allows you to fight with artificial intelligence, collect cards and experiment with different strategies.

## Main components of the system

### 1. Card system
- Base card class with descendants for different types
- Support for different types of cards (creatures, spells, items, etc.)
- Effect and status system

### 2. Game modes
- Duel (1 on 1 against AI)
- Training (learning mechanics)
- Meditation (free play for experiments)

### 3. Artificial intelligence
- Basic decision-making system
- Different difficulty levels
- Possibility of expanding strategies

### 4. Additional systems
- Bazaar for buying/selling cards
- Training system
- Card collecting

## Architectural solutions

### Design patterns
- Factory Method for creating cards
- Strategy for implementing AI
- Observer for the effects system
- Command for processing player actions

### Technical features
- Modular architecture
- Using smart pointers
- CMake build system
- Unit testing

## Extensibility
The system is designed to allow for the addition of:
- New card types
- New game modes
- Improved AI strategies
- Additional game mechanicss
