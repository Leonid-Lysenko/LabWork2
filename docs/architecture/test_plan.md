## 1. Модульное тестирование

### 1.1 Тестирование карт
- Создание карт разных типов
- Проверка базовых характеристик
- Тестирование механик карт
- Проверка эффектов карт

### 1.2 Тестирование игроков
- Управление картами в руке
- Розыгрыш карт
- Проверка ресурсов
- Тестирование ИИ
### 1.3 Тестирование эффектов
- Применение эффектов
- Длительность эффектов
- Снятие эффектов
- Взаимодействие эффектов

TEST_F(EffectTest, BuffDuration) {
    auto buff = std::make_shared<BuffEffect>(1, "Test", "Buff", 2, 2);
    character->addEffect(buff);
    
    EXPECT_TRUE(buff->update());  // 1-й ход
    EXPECT_TRUE(buff->update());  // 2-й ход
    EXPECT_FALSE(buff->update()); // Эффект закончился
}


### 1.4 Тестирование игровых режимов
- Инициализация режимов
- Проверка условий победы
- Тестирование хода игры
- Переходы между состояниями

TEST_F(GameModeTest, DuelModeWinCondition) {
    auto mode = std::make_shared<DuelMode>();
    mode->initialize({player1, player2});
    
    player2->modifyHealth(-30);  // Убиваем второго игрока
    EXPECT_TRUE(mode->checkEndCondition());
    EXPECT_EQ(mode->getWinner(), player1);
}

## 2. Интеграционное тестирование

### 2.1 Взаимодействие компонентов
- Карты и эффекты
- Игроки и карты
- Режимы и игроки
- Система в целом

TEST_F(IntegrationTest, CardEffectInteraction) {
    auto card = std::make_shared<SpellCard>(1, "Test", "Test spell", 2, SpellType::Buff, 2);
    auto player = std::make_shared<Player>(1, "Test", 30, 10);
    auto target = std::make_shared<CharacterCard>(2, "Target", "Test target", 2, 
                                                CharacterClass::Warrior, 2, 3);
    
    player->playCard(card, target);
    EXPECT_EQ(target->getAttack(), 4);  // Базовая атака + бафф
}

### 2.2 Сценарии использования
- Полный игровой цикл
- Комбинации карт
- Сложные взаимодействия
- Граничные случаи

## 3. Нагрузочное тестирование

### 3.1 Производительность

TEST_F(PerformanceTest, LargeGameState) {
    const int NUM_CARDS = 1000;
    auto startTime = std::chrono::high_resolution_clock::now();
    
    for(int i = 0; i < NUM_CARDS; i++) {
        gameState.addCard(createRandomCard());
    }
    
    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>
                   (endTime - startTime);
                   
    EXPECT_LT(duration.count(), 100);  // Должно выполняться менее чем за 100мс
}


### 3.2 Утечки памяти

TEST_F(MemoryTest, NoLeaks) {
    void* initialMemory = getCurrentMemoryUsage();
    
    {
        GameState state;
        // Интенсивные операции с памятью
        runGameCycle();
    }
    
    void* finalMemory = getCurrentMemoryUsage();
    EXPECT_EQ(initialMemory, finalMemory);
}

## 4. Регрессионное тестирование

### 4.1 Автоматизированные тесты
- Непрерывная интеграция
- Ежедневное тестирование
- Проверка всех изменений

### 4.2 Тестовые сценарии

class RegressionTest : public ::testing::Test {
protected:
    void SetUp() override {
        loadTestScenarios();
    }
    
    void runScenario(const std::string& name) {
        auto scenario = scenarios[name];
        EXPECT_TRUE(scenario.execute());
        EXPECT_TRUE(scenario.verifyResults());
    }
};

TEST_F(RegressionTest, BasicGameplay) {
    runScenario("basic_gameplay");
}

TEST_F(RegressionTest, ComplexCombos) {
    runScenario("complex_combos");
}


## 5. Приёмочное тестирование

### 5.1 Критерии приёмки
- Функциональность соответствует требованиям
- Производительность в пределах нормы
- Отсутствие критических ошибок
- Пользовательский интерфейс работает корректно

### 5.2 Тестовые сценарии
TEST_F(AcceptanceTest, FullGameCycle) {
    // Инициализация игры
    Game game;
    EXPECT_TRUE(game.initialize());
    
    // Проверка основных функций
    EXPECT_TRUE(game.createPlayer("TestPlayer"));
    EXPECT_TRUE(game.startDuel());
    EXPECT_TRUE(game.playTurn());
    EXPECT_TRUE(game.endGame());
    
    // Проверка результатов
    EXPECT_TRUE(game.saveResults());
    EXPECT_TRUE(game.cleanup());
}


## 6. Документирование тестов

### 6.1 Формат документации
- Описание тест-кейса
- Предусловия
- Шаги выполнения
- Ожидаемые результаты
- Фактические результаты

### 6.2 Пример документации теста

/**
 * @test CardPlayTest
 * @brief Тестирование розыгрыша карты
 * 
 * Предусловия:
 * - Игрок имеет карту в руке
 * - Достаточно маны для розыгрыша
 * 
 * Шаги:
 * 1. Создаём тестового игрока
 * 2. Добавляем карту в руку
 * 3. Пытаемся разыграть карту
 * 
 * Ожидаемый результат:
 * - Карта успешно разыграна
 * - Мана уменьшена
 * - Карта удалена из руки
 */