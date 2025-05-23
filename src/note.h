// // ButtonNoteMap.h

// #ifndef BUTTON_NOTE_MAP_H
// #define BUTTON_NOTE_MAP_H

// #include <Arduino.h>
// enum MidiType : uint8_t
// {
//     NOTE = 1,
//     CC = 3,
//     PC = 5,
// };
// struct ButtonNote
// {
//     uint8_t pin;
//     MidiType type;
//     uint8_t note;
//     uint8_t velocity;
//     uint8_t channel;
// };

// const uint8_t NUM_BUTTONS = 12;
// const uint8_t buttonPins[12] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 16, 14, 15};
// ButtonNote shiftButtons[2] = {
//     {A0, CC, 121, 127, 1},
//     {A1, CC, 120, 127, 1}};
// ButtonNote buttonNotes_1[NUM_BUTTONS] = {
//     {buttonPins[0], CC, 60, 127, 1},
//     {buttonPins[1], CC, 61, 127, 1},
//     {4, CC, 62, 127, 1},
//     {5, CC, 63, 127, 1},
//     {6, CC, 64, 127, 1},
//     {7, CC, 65, 127, 1},
//     {8, CC, 66, 127, 1},
//     {9, CC, 67, 127, 1},
//     {10, CC, 68, 127, 1},
//     {16, CC, 69, 127, 1},
//     {14, CC, 70, 127, 1},
//     {15, CC, 71, 127, 1}};

// ButtonNote buttonNotes_2[NUM_BUTTONS] = {
//     {buttonPins[0], CC, 72, 127, 1},
//     {buttonPins[1], CC, 73, 127, 1},
//     {4, CC, 74, 127, 1},
//     {5, CC, 75, 127, 1},
//     {6, CC, 76, 127, 1},
//     {7, CC, 77, 127, 1},
//     {8, CC, 78, 127, 1},
//     {9, CC, 79, 127, 1},
//     {10, CC, 80, 127, 1},
//     {16, CC, 81, 127, 1},
//     {14, CC, 82, 127, 1},
//     {15, CC, 83, 127, 1}};

// ButtonNote buttonNotes_3[NUM_BUTTONS] = {
//     {buttonPins[0], CC, 84, 127, 1},
//     {buttonPins[1], CC, 85, 127, 1},
//     {4, CC, 86, 127, 1},
//     {5, CC, 87, 127, 1},
//     {6, CC, 88, 127, 1},
//     {7, CC, 89, 127, 1},
//     {8, CC, 90, 127, 1},
//     {9, CC, 91, 127, 1},
//     {10, CC, 92, 127, 1},
//     {16, CC, 93, 127, 1},
//     {14, CC, 94, 127, 1},
//     {15, CC, 95, 127, 1}};

// ButtonNote buttonNotes_4[NUM_BUTTONS] = {
//     {buttonPins[0], CC, 96, 127, 1},
//     {buttonPins[1], CC, 97, 127, 1},
//     {4, CC, 98, 127, 1},
//     {5, CC, 99, 127, 1},
//     {6, CC, 100, 127, 1},
//     {7, CC, 101, 127, 1},
//     {8, CC, 102, 127, 1},
//     {9, CC, 103, 127, 1},
//     {10, CC, 104, 127, 1},
//     {16, CC, 105, 127, 1},
//     {14, CC, 106, 127, 1},
//     {15, CC, 107, 127, 1}};

// ButtonNote buttonNotes_5[NUM_BUTTONS] = {
//     {buttonPins[0], CC, 108, 127, 1},
//     {buttonPins[1], CC, 109, 127, 1},
//     {4, CC, 110, 127, 1},
//     {5, CC, 111, 127, 1},
//     {6, CC, 112, 127, 1},
//     {7, CC, 113, 127, 1},
//     {8, CC, 114, 127, 1},
//     {9, CC, 115, 127, 1},
//     {10, CC, 116, 127, 1},
//     {16, CC, 117, 127, 1},
//     {14, CC, 118, 127, 1},
//     {15, CC, 119, 127, 1}};

// const ButtonNote *pages[] = {buttonNotes_1, buttonNotes_2, buttonNotes_3, buttonNotes_4, buttonNotes_5};

// #endif

// esp32

#ifndef BUTTON_NOTE_MAP_H
#define BUTTON_NOTE_MAP_H

#include <Arduino.h>
enum MidiType : uint8_t
{
    NOTE = 1,
    CC = 3,
    PC = 5,
};
struct ButtonNote
{
    uint8_t pin;
    MidiType type;
    uint8_t note;
    uint8_t velocity;
    uint8_t channel;
};

const uint8_t NUM_BUTTONS = 12;
const uint8_t buttonPins[12] = {29, 22, 1, 3, 21, 19, 18, 5, 17, 16, 4, 2};
ButtonNote shiftButtons[2] = {
    {36, CC, 121, 127, 1},
    {39, CC, 120, 127, 1}};
ButtonNote buttonNotes_1[NUM_BUTTONS] = {
    {buttonPins[0], CC, 60, 127, 1},
    {buttonPins[1], CC, 61, 127, 1},
    {buttonPins[2], CC, 62, 127, 1},
    {buttonPins[3], CC, 63, 127, 1},
    {buttonPins[4], CC, 64, 127, 1},
    {buttonPins[5], CC, 65, 127, 1},
    {buttonPins[6], CC, 66, 127, 1},
    {buttonPins[7], CC, 67, 127, 1},
    {buttonPins[8], CC, 68, 127, 1},
    {buttonPins[9], CC, 69, 127, 1},
    {buttonPins[10], CC, 70, 127, 1},
    {buttonPins[11], CC, 71, 127, 1}};

ButtonNote buttonNotes_2[NUM_BUTTONS] = {
    {buttonPins[0], CC, 72, 127, 1},
    {buttonPins[1], CC, 73, 127, 1},
    {buttonPins[2], CC, 74, 127, 1},
    {buttonPins[3], CC, 75, 127, 1},
    {buttonPins[4], CC, 76, 127, 1},
    {buttonPins[5], CC, 77, 127, 1},
    {buttonPins[6], CC, 78, 127, 1},
    {buttonPins[7], CC, 79, 127, 1},
    {buttonPins[8], CC, 80, 127, 1},
    {buttonPins[9], CC, 81, 127, 1},
    {buttonPins[10], CC, 82, 127, 1},
    {buttonPins[11], CC, 83, 127, 1}};

ButtonNote buttonNotes_3[NUM_BUTTONS] = {
    {buttonPins[0], CC, 84, 127, 1},
    {buttonPins[1], CC, 85, 127, 1},
    {buttonPins[2], CC, 86, 127, 1},
    {buttonPins[3], CC, 87, 127, 1},
    {buttonPins[4], CC, 88, 127, 1},
    {buttonPins[5], CC, 89, 127, 1},
    {buttonPins[6], CC, 90, 127, 1},
    {buttonPins[7], CC, 91, 127, 1},
    {buttonPins[8], CC, 92, 127, 1},
    {buttonPins[9], CC, 93, 127, 1},
    {buttonPins[10], CC, 94, 127, 1},
    {buttonPins[11], CC, 95, 127, 1}};

ButtonNote buttonNotes_4[NUM_BUTTONS] = {
    {buttonPins[0], CC, 96, 127, 1},
    {buttonPins[1], CC, 97, 127, 1},
    {buttonPins[2], CC, 98, 127, 1},
    {buttonPins[3], CC, 99, 127, 1},
    {buttonPins[4], CC, 100, 127, 1},
    {buttonPins[5], CC, 101, 127, 1},
    {buttonPins[6], CC, 102, 127, 1},
    {buttonPins[7], CC, 103, 127, 1},
    {buttonPins[8], CC, 104, 127, 1},
    {buttonPins[9], CC, 105, 127, 1},
    {buttonPins[10], CC, 106, 127, 1},
    {buttonPins[11], CC, 107, 127, 1}};

ButtonNote buttonNotes_5[NUM_BUTTONS] = {
    {buttonPins[0], CC, 108, 127, 1},
    {buttonPins[1], CC, 109, 127, 1},
    {buttonPins[2], CC, 110, 127, 1},
    {buttonPins[3], CC, 111, 127, 1},
    {buttonPins[4], CC, 112, 127, 1},
    {buttonPins[5], CC, 113, 127, 1},
    {buttonPins[6], CC, 114, 127, 1},
    {buttonPins[7], CC, 115, 127, 1},
    {buttonPins[8], CC, 116, 127, 1},
    {buttonPins[9], CC, 117, 127, 1},
    {buttonPins[10], CC, 118, 127, 1},
    {buttonPins[11], CC, 119, 127, 1}};

const ButtonNote *pages[] = {buttonNotes_1, buttonNotes_2, buttonNotes_3, buttonNotes_4, buttonNotes_5};

#endif
