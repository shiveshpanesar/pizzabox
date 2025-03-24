**PIZZABOX Firmware Functionality Documentation**

### Overview
The firmware handles two buttons that cycle through five different states. Each button press and release triggers MIDI tones. Additionally, button actions include toggles, long presses, and simultaneous long presses to switch between predefined states.

### Button Functionality
1. **Button 1 Press:** Triggers MIDI tone **120 ON**
2. **Button 1 Release:** Triggers MIDI tone **120 OFF**
3. **Button 2 Press:** Triggers MIDI tone **121 ON**
4. **Button 2 Release:** Triggers MIDI tone **121 OFF**

### MIDI Tone Configuration
- The MIDI tones start from **60** and are assigned to **12 buttons**.
- Each button press sends an **ON** signal, and release sends an **OFF** signal.
- The default MIDI tone state is **0**, which can be modified at:
  ```c
  uint8_t currentState = 0;
  uint8_t lastState = 0;
  ```

### State Transitions
- **Button 1 Toggle:** Switches to **State 1**
- **Button 2 Toggle:** Switches to **State 0**
- **Button 1 Long Press:** Switches to **State 2**
- **Button 2 Long Press:** Switches to **State 3**
- **Button 1 & Button 2 Long Press:** Switches to **State 4**

### Timing Configuration
- The default toggle duration is **150ms**.
- It can be modified at the following line:
  ```c
  uint16_t longPressTime = 150;
  ```

### Debugging and MIDI Mode
- Enable debugging by uncommenting:
  ```c
  // #define SERIALPRINT
  ```
- Enable MIDI functionality by uncommenting:
  ```c
  // #define MIDI
  ```

