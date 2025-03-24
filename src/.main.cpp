//MIDI PRO MICRO 12 BUTTONS PIZZABOX

#include <Arduino.h>
// #define MIDI
#define SERIALPRINT
#ifdef MIDI
#include <MIDIUSB.h>
#endif
const int button1 = A0;
const int button2 = A1;
const int longPressThreshold = 150; // timing ms for longpress
const int buttonPins[12] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 16, 14, 15};
bool buttonStates[12];
int currentState = 0;
int lastPermanentState = 0;
const int stateMidiStart[4] = {60, 72, 84, 96};
int permanentMidiNotes[12];
bool button1Last = false;
bool button2Last = false;
unsigned long button1PressTime = 0;
unsigned long button2PressTime = 0;
bool button1Processed = false;
bool button2Processed = false;
#ifdef MIDI
bool noteOn(byte channel, byte pitch, byte velocity)
{
  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
  // midiEventPacket_t noteOn = {0x09, channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOn);
  MidiUSB.flush();
}

bool noteOff(byte channel, byte pitch, byte velocity)
{
  midiEventPacket_t noteOff = {0x08, 0x80 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOff);
  MidiUSB.flush();
}
#endif
void updatePermanentMidiNotes(int state)
{
#ifdef SERIALPRINT
  for (int i = 0; i < 12; i++)
  {
    Serial.print(stateMidiStart[state] + i);
    Serial.print(" , ");
  }
  Serial.print(" ----- ");
  for (int i = 0; i < 12; i++)
  {
    if (!digitalRead(buttonPins[i]) && buttonStates[i] == false)
    {
      buttonStates[i] = true;
      Serial.print("NOTEON");
      Serial.print(stateMidiStart[state] + i);
      delay(50);
    }
    if (digitalRead(buttonPins[i]) && buttonStates[i] == true)
    {
      buttonStates[i] = false;
      Serial.print("NOTEOff");
      Serial.print(stateMidiStart[state] + i);

      delay(50);
    }
    // digitalRead(buttonPins[i]) ? 0 : Serial.print(stateMidiStart[state] + i);
  }
  Serial.println();
#endif
#ifdef MIDI
  for (int i = 0; i < 12; i++)
  {
    if (!digitalRead(buttonPins[i]) && buttonStates[i] == false)
    {
      buttonStates[i] = true;
      noteOn(1, stateMidiStart[state] + i, 127);
      delay(50);
    }
    if (digitalRead(buttonPins[i]) && buttonStates[i] == true)
    {
      buttonStates[i] = false;
      noteOff(1, stateMidiStart[state] + i, 0);
      delay(50);
    }
  }
#endif
}
void setup()
{
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  for (int i = 0; i < 12; i++)
  {
    pinMode(buttonPins[i], INPUT_PULLUP);
    buttonStates[i] = false;
  }
#ifdef SERIALPRINT
  Serial.begin(115200);
#endif
}

void loop()
{
  bool btn1 = digitalRead(button1) == LOW;
  bool btn2 = digitalRead(button2) == LOW;
  unsigned long currentTime = millis();
  if (btn1 && !button1Last)
  {
    button1PressTime = currentTime;
    button1Processed = false;
  }
  if (btn2 && !button2Last)
  {
    button2PressTime = currentTime;
    button2Processed = false;
  }

  if (btn1 && !button1Processed && (currentTime - button1PressTime >= longPressThreshold))
  {
    currentState = 2; // 0;
    button1Processed = true;
// #ifdef MIDI
//     noteOn(1, 109, 127);
// #endif
// #ifdef SERIALPRINT
//     Serial.println("note on 109");
//     // delay(1000);
// #endif
  }
  if (!btn1 && button1Last && !button1Processed)
  {
    lastPermanentState = 0; // 2;
    button1Processed = true;
  }

  if (btn2 && !button2Processed && (currentTime - button2PressTime >= longPressThreshold))
  {
    currentState = 3; // 1;
// #ifdef MIDI
//     noteOn(1, 110, 127);
// #endif
// #ifdef SERIALPRINT
//     Serial.println("note on 110");
//     // delay(1000);
// #endif
    button2Processed = true;
  }
  if (!btn2 && button2Last && !button2Processed)
  {
    lastPermanentState = 1; // 3;
    button2Processed = true;
  }

  if (!btn1 && !btn2)
  {
    currentState = lastPermanentState;
  }

  button1Last = btn1;
  button2Last = btn2;

  // Serial.print("State: ");
  // Serial.print(currentState);
  updatePermanentMidiNotes(currentState);
  // Serial.print("  Permanent MIDI Notes: ");
  // for (int i = 0; i < 12; i++)
  // {
  //   Serial.print(permanentMidiNotes[i]);
  //   Serial.print(" ");
  // }
  // Serial.println();
}
