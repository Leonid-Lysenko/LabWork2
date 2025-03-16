## Description of the main classes

### Base classes

1. **BaseEntity**
- Base class for all game entities
- Contains general characteristics and methods

2. **Card**
- Abstract class for all cards
- Defines the base interface of cards

3. **Effect**
- Abstract class for effects
- Controls duration and application of effects

4. **Player**
- Abstract class of player
- Controls state and actions of player

5. **GameMode**
- Abstract class of game mode
- Defines logic of different modes

### Cards

1. **CharacterCard**
- Creature cards
- Combat characteristics and mechanics

2. **SpellCard**
- Spell cards
- Various magic effects

3. **ItemCard**
- Item cards
- One-time effects

4. **WeaponCard**
- Weapon cards
- Creature buffs

### Effects

1. **BuffEffect**
- Positive effects
- Strengthening characteristics

2. **DebuffEffect**
- Negative effects
- Weakening opponents

3. **StatusEffect**
- Status effects
- Special conditions

### Players

1. **HumanPlayer**
- Human player control
- Handling user input

2. **AIPlayer**
- Artificial intelligence
- Strategy and decision making

### Game modes

1. **DuelMode**
- Duel mode
- One-on-one combat

2. **TrainingMode**
- Training mode
- Step-by-step instructions

3. **MeditationMode**
- Meditation mode
- Free play
