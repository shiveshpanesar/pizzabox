#include <Arduino.h>
// #define SERIALPRINT
#define MIDI
#ifdef MIDI
#include <MIDIUSB.h>
bool noteOn(byte channel, byte pitch, byte velocity)
{
    midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
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
template <typename T>
void cout(T msg)
{
    Serial.print(msg);
}

uint16_t longPressTime = 150;

bool btn1State = false,
     btn1Toggle = false,
     btn1LongPress = false;
uint64_t btn1LastPressedTime;

bool btn2State = false,
     btn2Toggle = false,
     btn2LongPress = false;
uint64_t btn2LastPressedTime;
uint8_t currentState = 0;
uint8_t lastState = 0;
const uint8_t buttonPins[12] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 16, 14, 15};
const uint8_t stateMidiStart[5] = {60, 72, 84, 96, 108};
bool buttonStates[12];
const uint8_t button1 = A0;
const uint8_t button2 = A1;
void updatePermanentMidiNotes()
{
#ifdef SERIALPRINT
    for (uint8_t i = 0; i < 12; i++)
    {
        Serial.print(stateMidiStart[currentState] + i);
        Serial.print(" , ");
    }
    Serial.print(" ----- ");
    for (uint8_t i = 0; i < 12; i++)
    {
        if (!digitalRead(buttonPins[i]) && buttonStates[i] == false)
        {
            buttonStates[i] = true;
            Serial.print("NOTEON");
            Serial.print(stateMidiStart[currentState] + i);
            delay(50);
        }
        if (digitalRead(buttonPins[i]) && buttonStates[i] == true)
        {
            buttonStates[i] = false;
            Serial.print("NOTEOff");
            Serial.print(stateMidiStart[currentState] + i);
            delay(50);
        }
    }
    Serial.println();
#endif
#ifdef MIDI
    for (uint8_t i = 0; i < 12; i++)
    {
        if (!digitalRead(buttonPins[i]) && buttonStates[i] == false)
        {
            buttonStates[i] = true;
            noteOn(1, stateMidiStart[currentState] + i, 127);
            delay(50);
        }
        if (digitalRead(buttonPins[i]) && buttonStates[i] == true)
        {
            buttonStates[i] = false;
            noteOff(1, stateMidiStart[currentState] + i, 0);
            delay(50);
        }
    }
#endif
}
void setup()
{
    pinMode(button1, INPUT_PULLUP);
    pinMode(button2, INPUT_PULLUP);
    for (uint8_t i = 0; i < 12; i++)
    {
        pinMode(buttonPins[i], INPUT_PULLUP);
        buttonStates[i] = false;
    }
#ifdef SERIALPRINT
    Serial.begin(115200);
    Serial.println("Button Test Initialized");
#endif
}

void loop()
{
    bool btn1 = !digitalRead(button1);
    bool btn2 = !digitalRead(button2);
    uint64_t currentTime = millis();
    // button 1
    if (btn1 && !btn1State)
    {
        btn1State = true;
        btn1LastPressedTime = currentTime;
#ifdef MIDI
        noteOn(1, 121, 127);
#endif
#ifdef SERIALPRINT
        cout("\n noteON 121");
#endif
    }
    if (!btn1 && btn1State)
    {
        btn1State = false;
        if (!btn1LongPress)
        {
            btn1Toggle = !btn1Toggle;
            lastState = 1;
        }
        btn1LongPress = false;
#ifdef MIDI
        noteOn(1, 121, 0);
#endif
#ifdef SERIALPRINT
        cout("\n noteff 121");
#endif
    }
    if (btn1State && currentTime - btn1LastPressedTime > longPressTime)
    {
        btn1LongPress = true;
    }
    // button 2
    if (btn2 && !btn2State)
    {
        btn2State = true;
        btn2LastPressedTime = currentTime;
#ifdef MIDI
        noteOn(1, 120, 127);
#endif
#ifdef SERIALPRINT
        cout("\n noteON 120");
#endif
    }
    if (!btn2 && btn2State)
    {
        btn2State = false;
        if (!btn2LongPress)
        {
            btn2Toggle = !btn2Toggle;
            lastState = 0;
        }
        btn2LongPress = false;
#ifdef MIDI
        noteOn(1, 120, 0);
#endif
#ifdef SERIALPRINT
        cout("\n noteOff 120");
#endif
    }
    if (btn2State && currentTime - btn2LastPressedTime > longPressTime)
    {
        btn2LongPress = true;
    }
    // check states
    if (btn1LongPress && btn2LongPress)
    {
        currentState = 4;
    }
    else if (btn1LongPress)
    {
        currentState = 2;
    }
    else if (btn2LongPress)
    {
        currentState = 3;
    }
    else
    {
        currentState = lastState;
    }
    // if (btn1Toggle)
    // {
    // }
    // if (btn2Toggle)
    // {
    // }

    // cout("\nButton 1: " + String(btn1State) +
    //      " | Toggle: " + String(btn1Toggle) +
    //      " | LongPress: " + String(btn1LongPress));

    // cout(" Button 2: " + String(btn2State) +
    //      " | Toggle: " + String(btn2Toggle) +
    //      " | LongPress: " + String(btn2LongPress));
    updatePermanentMidiNotes();
    // cout("\n" + String(currentState));
}