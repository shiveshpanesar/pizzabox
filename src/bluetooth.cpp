#include <Arduino.h>
// #define SERIALPRINT
#include "note.h"
#define MIDITONE
#ifdef MIDITONE
#include <BLEMIDI_Transport.h>
#include <hardware/BLEMIDI_ESP32.h>
BLEMIDI_CREATE_INSTANCE("AWESOME_INSTRUMENT", MIDI)

bool noteOn(byte channel, byte pitch, byte velocity)
{
    // midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
    // MidiUSB.sendMIDI(noteOn);
    // MidiUSB.flush();
    MIDI.sendNoteOn(0x09, 0x90 | channel, pitch);
}

bool noteOff(byte channel, byte pitch, byte velocity)
{
    // midiEventPacket_t noteOff = {0x08, 0x80 | channel, pitch, velocity};
    // MidiUSB.sendMIDI(noteOff);
    // MidiUSB.flush();
    MIDI.sendNoteOn(0x08, 0x80 | channel, pitch);
}
void controlChangeOn(byte channel, byte control, byte value)
{
    // midiEventPacket_t cc = {0x0B, 0xB0 | channel, control, value};
    // MidiUSB.sendMIDI(cc);
    // MidiUSB.flush();
    MIDI.sendNoteOn(0x0B, 0xB0 | channel, control);
}

void controlChangeOff(byte channel, byte control)
{
    // midiEventPacket_t cc = {0x0B, 0xB0 | channel, control, 0};
    // MidiUSB.sendMIDI(cc);
    // MidiUSB.flush();
    MIDI.sendNoteOn(0x0B, 0xB0 | channel, control);
}
void programChangeOn(byte channel, byte programNumber)
{
    // midiEventPacket_t pc = {0x0C, 0xC0 | channel, programNumber, 0};
    // MidiUSB.sendMIDI(pc);
    // MidiUSB.flush();
    MIDI.sendNoteOn(0x0C, 0xC0 | channel, programNumber);
}
void programChangeOff(byte channel)
{
    // midiEventPacket_t pc = {0x0C, 0xC0 | channel, 0, 0};
    // MidiUSB.sendMIDI(pc);
    // MidiUSB.flush();
    MIDI.sendNoteOn(0x0C, 0xC0 | channel, 0);
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
bool buttonStates[NUM_BUTTONS];

// const uint8_t buttonPins[12] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 16, 14, 15};
// const uint8_t note_1[12] = {60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71};             // C4–B4
// const uint8_t note_2[12] = {72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83};             // C5–B5
// const uint8_t note_3[12] = {84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95};             // C6–B6
// const uint8_t note_4[12] = {96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107};     // C7–B7
// const uint8_t note_5[12] = {108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119}; // C8–B8
// const uint8_t *notes[] = {note_1, note_2, note_3, note_4, note_5};
// bool buttonStates[12];
const uint8_t button1 = 36;
const uint8_t button2 = 39;
void updatePermanentMidiNotes()
{
#ifdef SERIALPRINT
    for (uint8_t i = 0; i < NUM_BUTTONS; i++)
    {
        bool isPressed = !digitalRead(buttonPins[i]);

        if (isPressed && !buttonStates[i])
        {
            Serial.print("\ncurrentState:   ");
            Serial.println(currentState);
            buttonStates[i] = true;

            switch (pages[currentState][i].type)
            {
            case NOTE:
                Serial.print("NOTE ON: ");
                Serial.println(pages[currentState][i].note);
                break;

            case CC:
                Serial.print("CC ON: ");
                Serial.println(pages[currentState][i].note);
                break;

            case PC:
                Serial.print("PC ON: ");
                Serial.println(pages[currentState][i].note);
                break;

            default:
                break;
            }
            delay(50);
        }

        if (!isPressed && buttonStates[i])
        {
            buttonStates[i] = false;

            switch (pages[currentState][i].type)
            {
            case NOTE:
                Serial.print("NOTE OFF: ");
                Serial.println(pages[currentState][i].note);
                break;

            case CC:
                Serial.print("CC OFF: ");
                Serial.println(pages[currentState][i].note);
                break;

            case PC:
                Serial.print("PC OFF: ");
                Serial.println(pages[currentState][i].note);
                break;

            default:
                break;
            }
            delay(50);
        }
    }

#endif
#ifdef MIDITONE
    // for (uint8_t i = 0; i < 12; i++)
    // {
    //     if (!digitalRead(buttonPins[i]) && buttonStates[i] == false)
    //     {
    //         buttonStates[i] = true;
    //         noteOn(1, notes[currentState][i], 127);
    //         delay(50);
    //     }
    //     if (digitalRead(buttonPins[i]) && buttonStates[i] == true)
    //     {
    //         buttonStates[i] = false;
    //         noteOff(1, notes[currentState][i], 0);
    //         delay(50);
    //     }
    // }
    for (uint8_t i = 0; i < NUM_BUTTONS; i++)
    {
        bool isPressed = !digitalRead(buttonPins[i]);

        if (isPressed && !buttonStates[i])
        {
            buttonStates[i] = true;
            switch (pages[currentState][i].type)
            {
            case NOTE:
                noteOn(pages[currentState][i].channel, pages[currentState][i].note, pages[currentState][i].velocity);
                break;
            case CC:
                controlChangeOn(pages[currentState][i].channel, pages[currentState][i].note, pages[currentState][i].velocity);
                break;
            case PC:
                programChangeOn(pages[currentState][i].channel, pages[currentState][i].note);
                break;
            default:
                break;
            }
            delay(50);
        }

        if (!isPressed && buttonStates[i])
        {
            buttonStates[i] = false;
            switch (pages[currentState][i].type)
            {
            case NOTE:
                noteOff(pages[currentState][i].channel, pages[currentState][i].note, 0);
                break;
            case CC:
                controlChangeOff(pages[currentState][i].channel, pages[currentState][i].note);
                break;
            case PC:
                programChangeOff(pages[currentState][i].channel);
                break;
            default:
                break;
            }
            delay(50);
        }
    }
#endif
}
void setup()
{
    pinMode(button1, INPUT_PULLUP);
    pinMode(button2, INPUT_PULLUP);
    MIDI.begin();
    // for (uint8_t i = 0; i < 12; i++)
    // {
    //     pinMode(buttonPins[i], INPUT_PULLUP);
    //     buttonStates[i] = false;
    // }
    for (uint8_t i = 0; i < NUM_BUTTONS; i++)
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
#ifdef MIDITONE
        // noteOn(1, 121, 127);
        controlChangeOn(shiftButtons[1].channel, shiftButtons[1].note, shiftButtons[1].velocity);
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
#ifdef MIDITONE
        // noteOn(1, 121, 0);
        controlChangeOff(shiftButtons[1].channel, shiftButtons[1].note);

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
#ifdef MIDITONE
        // noteOn(1, 120, 127);
        controlChangeOn(shiftButtons[0].channel, shiftButtons[0].note, shiftButtons[0].velocity);

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
#ifdef MIDITONE
        // noteOn(1, 120, 0);
        controlChangeOff(shiftButtons[0].channel, shiftButtons[0].note);

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