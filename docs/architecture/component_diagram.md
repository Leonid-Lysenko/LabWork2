## Component Description

### Game Core
The central component responsible for coordinating all subsystems and the main game loop.

### Card System
- **Card Factory**: Card creation and management
- **Effects System**: Effect and status system
- **Combat System**: Combat mechanics and card interactions

### Game Modes
- **Duel Mode**: 1v1 mode against AI
- **Training Mode**: Tutorial mode
- **Meditation Mode**: Free play mode

### Player System
- **Human Player**: Player control component
- **AI Player**: Artificial intelligence
- **Player Stats**: Statistics and achievements

### Market System
- **Card Shop**: Card buying/selling system
- **Collection**: Card collection management

### Support Systems
- **Tutorial**: Training system
- **Achievement System**: Achievement system
- **Save System**: Save/load game

## Component interactions

1. **Game Core ↔ Card System**
- Managing cards in the game
- Applying effects
- Resolving combat interactions

2. **Game Core ↔ Game Modes**
- Initializing modes
- Managing gameplay
- Switching modes

3. **Game Core ↔ Player System**
- Processing player actions
- Managing AI
- Tracking statistics

4. **Market System ↔ Card System**
- Creating cards for the store
- Managing collections
- Card transactions

5. **Support Systems ↔ Other Components**
- Saving state
- Tracking achievements
- Tutorials
