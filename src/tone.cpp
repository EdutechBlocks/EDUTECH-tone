#include "tone.h"
#include "pitches.h"
#include <Arduino.h>

void TONE::tone(uint8_t pin, unsigned int frequency, unsigned long duration, uint8_t channel)
{
    /*if (ledcRead(channel)) {
         log_e("Tone channel %d is already in use", ledcRead(channel));
         return;
     }*/
    ledcSetup(channel, 1000, 10);
    ledcAttachPin(pin, channel);
    ledcWriteTone(channel, frequency);
    if (duration != 0) {
        delay(duration);
        noTone(pin, channel);
    }
}

void TONE::noTone(uint8_t pin, uint8_t channel)
{
    ledcDetachPin(pin);
    ledcWrite(channel, 0);
}

void TONE::sirene(uint8_t pin, uint8_t channel)
{
    tone(pin, NOTE_C5,300,channel);
    noTone(pin, channel);
    tone(pin, NOTE_D5, 300,channel);
    noTone(pin, channel);
    tone(pin, NOTE_E5, 300,channel);
    noTone(pin, channel);
}

void TONE::playMusic(String nameMusic,uint8_t pin,uint8_t channel)
{
    if(nameMusic="StarWars"){
        playStarWars(pin,channel);
    };
    if(nameMusic="PinkPanther"){
        playPinkPanther(pin,channel);
    };
}

void TONE::playMelody(int melody[], int melodySize, uint8_t pin, uint8_t channel, int duration) {
    int tempo = 200;
    //int notes = sizeof(melody) / sizeof(melody[0]) / 2;
    int notes = melodySize / sizeof(melody[0]) / 2;
    int wholenote = (duration * 4) / tempo;
    int divider = 0, noteDuration = 0;

    for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {
        divider = melody[thisNote + 1];
        if (divider > 0) {
            noteDuration = (wholenote) / divider;
        }
        else if (divider < 0) {
            noteDuration = (wholenote) / abs(divider);
            noteDuration *= 1.5; // increases the duration in half for dotted notes
        }

        tone(pin, melody[thisNote], noteDuration * 0.9, channel);
        delay(noteDuration);
        noTone(pin, channel);
    }
}

void TONE::playStarWars(uint8_t pin,uint8_t channel)
{
    // Dart Vader theme (Imperial March) - Star wars
    int melody[] = {
        NOTE_AS4,8, NOTE_AS4,8, NOTE_AS4,8,//1
        NOTE_F5,2, NOTE_C6,2,
        NOTE_AS5,8, NOTE_A5,8, NOTE_G5,8, NOTE_F6,2, NOTE_C6,4,
        NOTE_AS5,8, NOTE_A5,8, NOTE_G5,8, NOTE_F6,2, NOTE_C6,4,
        NOTE_AS5,8, NOTE_A5,8, NOTE_AS5,8, NOTE_G5,2, NOTE_C5,8, NOTE_C5,8, NOTE_C5,8,
        NOTE_F5,2, NOTE_C6,2,
        NOTE_AS5,8, NOTE_A5,8, NOTE_G5,8, NOTE_F6,2, NOTE_C6,4,

        NOTE_AS5,8, NOTE_A5,8, NOTE_G5,8, NOTE_F6,2, NOTE_C6,4, //8
        NOTE_AS5,8, NOTE_A5,8, NOTE_AS5,8, NOTE_G5,2, NOTE_C5,-8, NOTE_C5,16,
        NOTE_D5,-4, NOTE_D5,8, NOTE_AS5,8, NOTE_A5,8, NOTE_G5,8, NOTE_F5,8,
        NOTE_F5,8, NOTE_G5,8, NOTE_A5,8, NOTE_G5,4, NOTE_D5,8, NOTE_E5,4,NOTE_C5,-8, NOTE_C5,16,
        NOTE_D5,-4, NOTE_D5,8, NOTE_AS5,8, NOTE_A5,8, NOTE_G5,8, NOTE_F5,8,

        NOTE_C6,-8, NOTE_G5,16, NOTE_G5,2, REST,8, NOTE_C5,8,//13
        NOTE_D5,-4, NOTE_D5,8, NOTE_AS5,8, NOTE_A5,8, NOTE_G5,8, NOTE_F5,8,
        NOTE_F5,8, NOTE_G5,8, NOTE_A5,8, NOTE_G5,4, NOTE_D5,8, NOTE_E5,4,NOTE_C6,-8, NOTE_C6,16,
        NOTE_F6,4, NOTE_DS6,8, NOTE_CS6,4, NOTE_C6,8, NOTE_AS5,4, NOTE_GS5,8, NOTE_G5,4, NOTE_F5,8,
        NOTE_C6,1
    };

    playMelody(melody, sizeof(melody), pin, channel);

/*    int tempo = 200;
    int notes = sizeof(melody) / sizeof(melody[0]) / 2;
    int wholenote = (60000 * 4) / tempo;
    int divider = 0, noteDuration = 0;

    for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {
        divider = melody[thisNote + 1];
        if (divider > 0) {
            noteDuration = (wholenote) / divider;
        } else if (divider < 0) {
            noteDuration = (wholenote) / abs(divider);
            noteDuration *= 1.5; // increases the duration in half for dotted notes
        }

        tone(pin, melody[thisNote], noteDuration * 0.9,channel);
        delay(noteDuration);
        noTone(pin,channel);
    }
*/
}

void TONE::playPinkPanther(uint8_t pin,uint8_t channel)
{
    // Pink Panther theme
    int melody[] = {
        REST,2, REST,4, REST,8, NOTE_DS4,8,
        NOTE_E4,-4, REST,8, NOTE_FS4,8, NOTE_G4,-4, REST,8, NOTE_DS4,8,
        NOTE_E4,-8, NOTE_FS4,8,  NOTE_G4,-8, NOTE_C5,8, NOTE_B4,-8, NOTE_E4,8, NOTE_G4,-8, NOTE_B4,8,
        NOTE_AS4,2, NOTE_A4,-16, NOTE_G4,-16, NOTE_E4,-16, NOTE_D4,-16,
        NOTE_E4,2, REST,4, REST,8, NOTE_DS4,4,

        NOTE_E4,-4, REST,8, NOTE_FS4,8, NOTE_G4,-4, REST,8, NOTE_DS4,8,
        NOTE_E4,-8, NOTE_FS4,8,  NOTE_G4,-8, NOTE_C5,8, NOTE_B4,-8, NOTE_G4,8, NOTE_B4,-8, NOTE_E5,8,
        NOTE_DS5,1,
        NOTE_D5,2, REST,4, REST,8, NOTE_DS4,8,
        NOTE_E4,-4, REST,8, NOTE_FS4,8, NOTE_G4,-4, REST,8, NOTE_DS4,8,
        NOTE_E4,-8, NOTE_FS4,8,  NOTE_G4,-8, NOTE_C5,8, NOTE_B4,-8, NOTE_E4,8, NOTE_G4,-8, NOTE_B4,8,

        NOTE_AS4,2, NOTE_A4,-16, NOTE_G4,-16, NOTE_E4,-16, NOTE_D4,-16,
        NOTE_E4,-4, REST,4,
        REST,4, NOTE_E5,-8, NOTE_D5,8, NOTE_B4,-8, NOTE_A4,8, NOTE_G4,-8, NOTE_E4,-8,
        NOTE_AS4,16, NOTE_A4,-8, NOTE_AS4,16, NOTE_A4,-8, NOTE_AS4,16, NOTE_A4,-8, NOTE_AS4,16, NOTE_A4,-8,
        NOTE_G4,-16, NOTE_E4,-16, NOTE_D4,-16, NOTE_E4,16, NOTE_E4,16, NOTE_E4,2,

    };

    playMelody(melody, sizeof(melody), pin, channel);
/*
    int tempo = 200;
    int notes = sizeof(melody) / sizeof(melody[0]) / 2;
    int wholenote = (60000 * 4) / tempo;
    int divider = 0, noteDuration = 0;

    for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {
        divider = melody[thisNote + 1];
        if (divider > 0) {
            noteDuration = (wholenote) / divider;
        } else if (divider < 0) {
            noteDuration = (wholenote) / abs(divider);
            noteDuration *= 1.5; // increases the duration in half for dotted notes
        }

        tone(pin, melody[thisNote], noteDuration * 0.9,channel);
        delay(noteDuration);
        noTone(pin,channel);
    }
*/
}

void TONE::playMarioBross(uint8_t pin,uint8_t channel)
{
  // Super Mario Bros theme
    int melody[] = {
        NOTE_E5,8, NOTE_E5,8, REST,8, NOTE_E5,8, REST,8, NOTE_C5,8, NOTE_E5,8, //1
        NOTE_G5,4, REST,4, NOTE_G4,8, REST,4,
        NOTE_C5,-4, NOTE_G4,8, REST,4, NOTE_E4,-4, // 3
        NOTE_A4,4, NOTE_B4,4, NOTE_AS4,8, NOTE_A4,4,
        NOTE_G4,-8, NOTE_E5,-8, NOTE_G5,-8, NOTE_A5,4, NOTE_F5,8, NOTE_G5,8,
        REST,8, NOTE_E5,4,NOTE_C5,8, NOTE_D5,8, NOTE_B4,-4,
        NOTE_C5,-4, NOTE_G4,8, REST,4, NOTE_E4,-4, // repeats from 3
        NOTE_A4,4, NOTE_B4,4, NOTE_AS4,8, NOTE_A4,4,
        NOTE_G4,-8, NOTE_E5,-8, NOTE_G5,-8, NOTE_A5,4, NOTE_F5,8, NOTE_G5,8,
        REST,8, NOTE_E5,4,NOTE_C5,8, NOTE_D5,8, NOTE_B4,-4,


        REST,4, NOTE_G5,8, NOTE_FS5,8, NOTE_F5,8, NOTE_DS5,4, NOTE_E5,8,//7
        REST,8, NOTE_GS4,8, NOTE_A4,8, NOTE_C4,8, REST,8, NOTE_A4,8, NOTE_C5,8, NOTE_D5,8,
        REST,4, NOTE_DS5,4, REST,8, NOTE_D5,-4,
        NOTE_C5,2, REST,2,

        REST,4, NOTE_G5,8, NOTE_FS5,8, NOTE_F5,8, NOTE_DS5,4, NOTE_E5,8,//repeats from 7
        REST,8, NOTE_GS4,8, NOTE_A4,8, NOTE_C4,8, REST,8, NOTE_A4,8, NOTE_C5,8, NOTE_D5,8,
        REST,4, NOTE_DS5,4, REST,8, NOTE_D5,-4,
        NOTE_C5,2, REST,2,

        NOTE_C5,8, NOTE_C5,4, NOTE_C5,8, REST,8, NOTE_C5,8, NOTE_D5,4,//11
        NOTE_E5,8, NOTE_C5,4, NOTE_A4,8, NOTE_G4,2,

        NOTE_C5,8, NOTE_C5,4, NOTE_C5,8, REST,8, NOTE_C5,8, NOTE_D5,8, NOTE_E5,8,//13
        REST,1,
        NOTE_C5,8, NOTE_C5,4, NOTE_C5,8, REST,8, NOTE_C5,8, NOTE_D5,4,
        NOTE_E5,8, NOTE_C5,4, NOTE_A4,8, NOTE_G4,2,
        NOTE_E5,8, NOTE_E5,8, REST,8, NOTE_E5,8, REST,8, NOTE_C5,8, NOTE_E5,4,
        NOTE_G5,4, REST,4, NOTE_G4,4, REST,4,
        NOTE_C5,-4, NOTE_G4,8, REST,4, NOTE_E4,-4, // 19

        NOTE_A4,4, NOTE_B4,4, NOTE_AS4,8, NOTE_A4,4,
        NOTE_G4,-8, NOTE_E5,-8, NOTE_G5,-8, NOTE_A5,4, NOTE_F5,8, NOTE_G5,8,
        REST,8, NOTE_E5,4, NOTE_C5,8, NOTE_D5,8, NOTE_B4,-4,

        NOTE_C5,-4, NOTE_G4,8, REST,4, NOTE_E4,-4, // repeats from 19
        NOTE_A4,4, NOTE_B4,4, NOTE_AS4,8, NOTE_A4,4,
        NOTE_G4,-8, NOTE_E5,-8, NOTE_G5,-8, NOTE_A5,4, NOTE_F5,8, NOTE_G5,8,
        REST,8, NOTE_E5,4, NOTE_C5,8, NOTE_D5,8, NOTE_B4,-4,

        NOTE_E5,8, NOTE_C5,4, NOTE_G4,8, REST,4, NOTE_GS4,4,//23
        NOTE_A4,8, NOTE_F5,4, NOTE_F5,8, NOTE_A4,2,
        NOTE_D5,-8, NOTE_A5,-8, NOTE_A5,-8, NOTE_A5,-8, NOTE_G5,-8, NOTE_F5,-8,

        NOTE_E5,8, NOTE_C5,4, NOTE_A4,8, NOTE_G4,2, //26
        NOTE_E5,8, NOTE_C5,4, NOTE_G4,8, REST,4, NOTE_GS4,4,
        NOTE_A4,8, NOTE_F5,4, NOTE_F5,8, NOTE_A4,2,
        NOTE_B4,8, NOTE_F5,4, NOTE_F5,8, NOTE_F5,-8, NOTE_E5,-8, NOTE_D5,-8,
        NOTE_C5,8, NOTE_E4,4, NOTE_E4,8, NOTE_C4,2,

        NOTE_E5,8, NOTE_C5,4, NOTE_G4,8, REST,4, NOTE_GS4,4,//repeats from 23
        NOTE_A4,8, NOTE_F5,4, NOTE_F5,8, NOTE_A4,2,
        NOTE_D5,-8, NOTE_A5,-8, NOTE_A5,-8, NOTE_A5,-8, NOTE_G5,-8, NOTE_F5,-8,

        NOTE_E5,8, NOTE_C5,4, NOTE_A4,8, NOTE_G4,2, //26
        NOTE_E5,8, NOTE_C5,4, NOTE_G4,8, REST,4, NOTE_GS4,4,
        NOTE_A4,8, NOTE_F5,4, NOTE_F5,8, NOTE_A4,2,
        NOTE_B4,8, NOTE_F5,4, NOTE_F5,8, NOTE_F5,-8, NOTE_E5,-8, NOTE_D5,-8,
        NOTE_C5,8, NOTE_E4,4, NOTE_E4,8, NOTE_C4,2,
        NOTE_C5,8, NOTE_C5,4, NOTE_C5,8, REST,8, NOTE_C5,8, NOTE_D5,8, NOTE_E5,8,
        REST,1,

        NOTE_C5,8, NOTE_C5,4, NOTE_C5,8, REST,8, NOTE_C5,8, NOTE_D5,4, //33
        NOTE_E5,8, NOTE_C5,4, NOTE_A4,8, NOTE_G4,2,
        NOTE_E5,8, NOTE_E5,8, REST,8, NOTE_E5,8, REST,8, NOTE_C5,8, NOTE_E5,4,
        NOTE_G5,4, REST,4, NOTE_G4,4, REST,4,
        NOTE_E5,8, NOTE_C5,4, NOTE_G4,8, REST,4, NOTE_GS4,4,
        NOTE_A4,8, NOTE_F5,4, NOTE_F5,8, NOTE_A4,2,
        NOTE_D5,-8, NOTE_A5,-8, NOTE_A5,-8, NOTE_A5,-8, NOTE_G5,-8, NOTE_F5,-8,

        NOTE_E5,8, NOTE_C5,4, NOTE_A4,8, NOTE_G4,2, //40
        NOTE_E5,8, NOTE_C5,4, NOTE_G4,8, REST,4, NOTE_GS4,4,
        NOTE_A4,8, NOTE_F5,4, NOTE_F5,8, NOTE_A4,2,
        NOTE_B4,8, NOTE_F5,4, NOTE_F5,8, NOTE_F5,-8, NOTE_E5,-8, NOTE_D5,-8,
        NOTE_C5,8, NOTE_E4,4, NOTE_E4,8, NOTE_C4,2,

        //game over sound
        NOTE_C5,-4, NOTE_G4,-4, NOTE_E4,4, //45
        NOTE_A4,-8, NOTE_B4,-8, NOTE_A4,-8, NOTE_GS4,-8, NOTE_AS4,-8, NOTE_GS4,-8,
        NOTE_G4,8, NOTE_D4,8, NOTE_E4,-2,

    };

    playMelody(melody, sizeof(melody), pin, channel);

/*    int tempo = 200;
    int notes = sizeof(melody) / sizeof(melody[0]) / 2;
    int wholenote = (60000 * 4) / tempo;
    int divider = 0, noteDuration = 0;

    for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {
        divider = melody[thisNote + 1];
        if (divider > 0) {
            noteDuration = (wholenote) / divider;
        } else if (divider < 0) {
            noteDuration = (wholenote) / abs(divider);
            noteDuration *= 1.5; // increases the duration in half for dotted notes
        }

        tone(pin, melody[thisNote], noteDuration * 0.9,channel);
        delay(noteDuration);
        noTone(pin,channel);
    }
*/
}

void TONE::playFelizAniversario(uint8_t pin,uint8_t channel)
{
    // Happy Birthday
    int melody[] = {
        NOTE_C4,4, NOTE_C4,8,
        NOTE_D4,-4, NOTE_C4,-4, NOTE_F4,-4,
        NOTE_E4,-2, NOTE_C4,4, NOTE_C4,8,
        NOTE_D4,-4, NOTE_C4,-4, NOTE_G4,-4,
        NOTE_F4,-2, NOTE_C4,4, NOTE_C4,8,

        NOTE_C5,-4, NOTE_A4,-4, NOTE_F4,-4,
        NOTE_E4,-4, NOTE_D4,-4, NOTE_AS4,4, NOTE_AS4,8,
        NOTE_A4,-4, NOTE_F4,-4, NOTE_G4,-4,
        NOTE_F4,-2,
    };

    playMelody(melody, sizeof(melody), pin, channel);
    /*
    int tempo = 200;
    int notes = sizeof(melody) / sizeof(melody[0]) / 2;
    int wholenote = (60000 * 4) / tempo;
    int divider = 0, noteDuration = 0;

    for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {
        divider = melody[thisNote + 1];
        if (divider > 0) {
            noteDuration = (wholenote) / divider;
        } else if (divider < 0) {
            noteDuration = (wholenote) / abs(divider);
            noteDuration *= 1.5; // increases the duration in half for dotted notes
        }

        tone(pin, melody[thisNote], noteDuration * 0.9,channel);
        delay(noteDuration);
        noTone(pin,channel);
    }
    */
}

void TONE::playFelizNatal(uint8_t pin,uint8_t channel)
{
     // We Wish You a Merry Christmas
    int melody[] = {
        NOTE_C5,4, //1
        NOTE_F5,4, NOTE_F5,8, NOTE_G5,8, NOTE_F5,8, NOTE_E5,8,
        NOTE_D5,4, NOTE_D5,4, NOTE_D5,4,
        NOTE_G5,4, NOTE_G5,8, NOTE_A5,8, NOTE_G5,8, NOTE_F5,8,
        NOTE_E5,4, NOTE_C5,4, NOTE_C5,4,
        NOTE_A5,4, NOTE_A5,8, NOTE_AS5,8, NOTE_A5,8, NOTE_G5,8,
        NOTE_F5,4, NOTE_D5,4, NOTE_C5,8, NOTE_C5,8,
        NOTE_D5,4, NOTE_G5,4, NOTE_E5,4,

        NOTE_F5,2, NOTE_C5,4, //8
        NOTE_F5,4, NOTE_F5,8, NOTE_G5,8, NOTE_F5,8, NOTE_E5,8,
        NOTE_D5,4, NOTE_D5,4, NOTE_D5,4,
        NOTE_G5,4, NOTE_G5,8, NOTE_A5,8, NOTE_G5,8, NOTE_F5,8,
        NOTE_E5,4, NOTE_C5,4, NOTE_C5,4,
        NOTE_A5,4, NOTE_A5,8, NOTE_AS5,8, NOTE_A5,8, NOTE_G5,8,
        NOTE_F5,4, NOTE_D5,4, NOTE_C5,8, NOTE_C5,8,
        NOTE_D5,4, NOTE_G5,4, NOTE_E5,4,
        NOTE_F5,2, NOTE_C5,4,

        NOTE_F5,4, NOTE_F5,4, NOTE_F5,4,//17
        NOTE_E5,2, NOTE_E5,4,
        NOTE_F5,4, NOTE_E5,4, NOTE_D5,4,
        NOTE_C5,2, NOTE_A5,4,
        NOTE_AS5,4, NOTE_A5,4, NOTE_G5,4,
        NOTE_C6,4, NOTE_C5,4, NOTE_C5,8, NOTE_C5,8,
        NOTE_D5,4, NOTE_G5,4, NOTE_E5,4,
        NOTE_F5,2, NOTE_C5,4,
        NOTE_F5,4, NOTE_F5,8, NOTE_G5,8, NOTE_F5,8, NOTE_E5,8,
        NOTE_D5,4, NOTE_D5,4, NOTE_D5,4,

        NOTE_G5,4, NOTE_G5,8, NOTE_A5,8, NOTE_G5,8, NOTE_F5,8, //27
        NOTE_E5,4, NOTE_C5,4, NOTE_C5,4,
        NOTE_A5,4, NOTE_A5,8, NOTE_AS5,8, NOTE_A5,8, NOTE_G5,8,
        NOTE_F5,4, NOTE_D5,4, NOTE_C5,8, NOTE_C5,8,
        NOTE_D5,4, NOTE_G5,4, NOTE_E5,4,
        NOTE_F5,2, NOTE_C5,4,
        NOTE_F5,4, NOTE_F5,4, NOTE_F5,4,
        NOTE_E5,2, NOTE_E5,4,
        NOTE_F5,4, NOTE_E5,4, NOTE_D5,4,

        NOTE_C5,2, NOTE_A5,4,//36
        NOTE_AS5,4, NOTE_A5,4, NOTE_G5,4,
        NOTE_C6,4, NOTE_C5,4, NOTE_C5,8, NOTE_C5,8,
        NOTE_D5,4, NOTE_G5,4, NOTE_E5,4,
        NOTE_F5,2, NOTE_C5,4,
        NOTE_F5,4, NOTE_F5,8, NOTE_G5,8, NOTE_F5,8, NOTE_E5,8,
        NOTE_D5,4, NOTE_D5,4, NOTE_D5,4,
        NOTE_G5,4, NOTE_G5,8, NOTE_A5,8, NOTE_G5,8, NOTE_F5,8,
        NOTE_E5,4, NOTE_C5,4, NOTE_C5,4,

        NOTE_A5,4, NOTE_A5,8, NOTE_AS5,8, NOTE_A5,8, NOTE_G5,8,//45
        NOTE_F5,4, NOTE_D5,4, NOTE_C5,8, NOTE_C5,8,
        NOTE_D5,4, NOTE_G5,4, NOTE_E5,4,
        NOTE_F5,2, NOTE_C5,4,
        NOTE_F5,4, NOTE_F5,8, NOTE_G5,8, NOTE_F5,8, NOTE_E5,8,
        NOTE_D5,4, NOTE_D5,4, NOTE_D5,4,
        NOTE_G5,4, NOTE_G5,8, NOTE_A5,8, NOTE_G5,8, NOTE_F5,8,
        NOTE_E5,4, NOTE_C5,4, NOTE_C5,4,

        NOTE_A5,4, NOTE_A5,8, NOTE_AS5,8, NOTE_A5,8, NOTE_G5,8, //53
        NOTE_F5,4, NOTE_D5,4, NOTE_C5,8, NOTE_C5,8,
        NOTE_D5,4, NOTE_G5,4, NOTE_E5,4,
        NOTE_F5,2, REST,4
    };

    playMelody(melody, sizeof(melody), pin, channel);

    /*
    int tempo = 200;
    int notes = sizeof(melody) / sizeof(melody[0]) / 2;
    int wholenote = (60000 * 4) / tempo;
    int divider = 0, noteDuration = 0;

    for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {
        divider = melody[thisNote + 1];
        if (divider > 0) {
            noteDuration = (wholenote) / divider;
        } else if (divider < 0) {
            noteDuration = (wholenote) / abs(divider);
            noteDuration *= 1.5; // increases the duration in half for dotted notes
        }

        tone(pin, melody[thisNote], noteDuration * 0.9,channel);
        delay(noteDuration);
        noTone(pin,channel);
    }
    */
}

void TONE::playCoffinDance(uint8_t pin, uint8_t channel)
{
    int melody[] = {
        NOTE_AS4,4, NOTE_AS4,4, NOTE_AS4,4, NOTE_AS4,4,
        NOTE_AS4,4, NOTE_AS4,4, NOTE_AS4,4, NOTE_AS4,4,
        NOTE_AS4,4, NOTE_AS4,4, NOTE_AS4,4, NOTE_AS4,4,
        NOTE_AS4,4, NOTE_AS4,4, NOTE_AS4,4, NOTE_AS4,4,
        NOTE_AS4,4, NOTE_AS4,4, NOTE_AS4,4, NOTE_AS4,4,
        NOTE_D5,4, NOTE_D5,4, NOTE_D5,4, NOTE_D5,4,
        NOTE_C5,4, NOTE_C5,4, NOTE_C5,4, NOTE_C5,4,
        NOTE_F5,4, NOTE_F5,4, NOTE_F5,4, NOTE_F5,4,
        NOTE_G5,4, NOTE_G5,4, NOTE_G5,4, NOTE_G5,4,
        NOTE_G5,4, NOTE_G5,4, NOTE_G5,4, NOTE_G5,4,
        NOTE_G5,4, NOTE_G5,4, NOTE_G5,4, NOTE_G5,4,
        NOTE_C5,4, NOTE_AS4,4, NOTE_A4,4, NOTE_F4,4,
        NOTE_G4, 0, NOTE_G4, NOTE_D5,
        NOTE_C5, 0, NOTE_AS4, 0,
        NOTE_A4, 0, NOTE_A4, NOTE_A4,
        NOTE_C5, 0, NOTE_AS4, NOTE_A4,
        NOTE_G4,0, NOTE_G4, NOTE_AS5,
        NOTE_A5, NOTE_AS5, NOTE_A5, NOTE_AS5,
        NOTE_G4,0, NOTE_G4, NOTE_AS5,
        NOTE_A5, NOTE_AS5, NOTE_A5, NOTE_AS5,
        NOTE_G4, 0, NOTE_G4, NOTE_D5,
        NOTE_C5, 0, NOTE_AS4, 0,
        NOTE_A4, 0, NOTE_A4, NOTE_A4,
        NOTE_C5, 0, NOTE_AS4, NOTE_A4,
        NOTE_G4,0, NOTE_G4, NOTE_AS5,
        NOTE_A5, NOTE_AS5, NOTE_A5, NOTE_AS5,
        NOTE_G4,0, NOTE_G4, NOTE_AS5,
        NOTE_A5, NOTE_AS5, NOTE_A5, NOTE_AS5
    };

    playMelody(melody, sizeof(melody), pin, channel);
};

void TONE::playGameThrones(uint8_t pin, uint8_t channel)
{
    int melody[] = {

        // Game of Thrones
        // Score available at https://musescore.com/user/8407786/scores/2156716

        NOTE_G4,8, NOTE_C4,8, NOTE_DS4,16, NOTE_F4,16, NOTE_G4,8, NOTE_C4,8, NOTE_DS4,16, NOTE_F4,16, //1
        NOTE_G4,8, NOTE_C4,8, NOTE_DS4,16, NOTE_F4,16, NOTE_G4,8, NOTE_C4,8, NOTE_DS4,16, NOTE_F4,16,
        NOTE_G4,8, NOTE_C4,8, NOTE_E4,16, NOTE_F4,16, NOTE_G4,8, NOTE_C4,8, NOTE_E4,16, NOTE_F4,16,
        NOTE_G4,8, NOTE_C4,8, NOTE_E4,16, NOTE_F4,16, NOTE_G4,8, NOTE_C4,8, NOTE_E4,16, NOTE_F4,16,
        NOTE_G4,-4, NOTE_C4,-4,//5

        NOTE_DS4,16, NOTE_F4,16, NOTE_G4,4, NOTE_C4,4, NOTE_DS4,16, NOTE_F4,16, //6
        NOTE_D4,-1, //7 and 8
        NOTE_F4,-4, NOTE_AS3,-4,
        NOTE_DS4,16, NOTE_D4,16, NOTE_F4,4, NOTE_AS3,-4,
        NOTE_DS4,16, NOTE_D4,16, NOTE_C4,-1, //11 and 12

        //repeats from 5
        NOTE_G4,-4, NOTE_C4,-4,//5

        NOTE_DS4,16, NOTE_F4,16, NOTE_G4,4, NOTE_C4,4, NOTE_DS4,16, NOTE_F4,16, //6
        NOTE_D4,-1, //7 and 8
        NOTE_F4,-4, NOTE_AS3,-4,
        NOTE_DS4,16, NOTE_D4,16, NOTE_F4,4, NOTE_AS3,-4,
        NOTE_DS4,16, NOTE_D4,16, NOTE_C4,-1, //11 and 12
        NOTE_G4,-4, NOTE_C4,-4,
        NOTE_DS4,16, NOTE_F4,16, NOTE_G4,4,  NOTE_C4,4, NOTE_DS4,16, NOTE_F4,16,

        NOTE_D4,-2,//15
        NOTE_F4,-4, NOTE_AS3,-4,
        NOTE_D4,-8, NOTE_DS4,-8, NOTE_D4,-8, NOTE_AS3,-8,
        NOTE_C4,-1,
        NOTE_C5,-2,
        NOTE_AS4,-2,
        NOTE_C4,-2,
        NOTE_G4,-2,
        NOTE_DS4,-2,
        NOTE_DS4,-4, NOTE_F4,-4,
        NOTE_G4,-1,

        NOTE_C5,-2,//28
        NOTE_AS4,-2,
        NOTE_C4,-2,
        NOTE_G4,-2,
        NOTE_DS4,-2,
        NOTE_DS4,-4, NOTE_D4,-4,
        NOTE_C5,8, NOTE_G4,8, NOTE_GS4,16, NOTE_AS4,16, NOTE_C5,8, NOTE_G4,8, NOTE_GS4,16, NOTE_AS4,16,
        NOTE_C5,8, NOTE_G4,8, NOTE_GS4,16, NOTE_AS4,16, NOTE_C5,8, NOTE_G4,8, NOTE_GS4,16, NOTE_AS4,16,

        REST,4, NOTE_GS5,16, NOTE_AS5,16, NOTE_C6,8, NOTE_G5,8, NOTE_GS5,16, NOTE_AS5,16,
        NOTE_C6,8, NOTE_G5,16, NOTE_GS5,16, NOTE_AS5,16, NOTE_C6,8, NOTE_G5,8, NOTE_GS5,16, NOTE_AS5,16
    };

    playMelody(melody, sizeof(melody), pin, channel);
};

void TONE::playAsaBranca(uint8_t pin, uint8_t channel)
{

    int melody[] = {

        // Asa branca - Luiz Gonzaga
        // Score available at https://musescore.com/user/190926/scores/181370

        NOTE_G4,8, NOTE_A4,8, NOTE_B4,4, NOTE_D5,4, NOTE_D5,4, NOTE_B4,4,
        NOTE_C5,4, NOTE_C5,2, NOTE_G4,8, NOTE_A4,8,
        NOTE_B4,4, NOTE_D5,4, NOTE_D5,4, NOTE_C5,4,

        NOTE_B4,2, REST,8, NOTE_G4,8, NOTE_G4,8, NOTE_A4,8,
        NOTE_B4,4, NOTE_D5,4, REST,8, NOTE_D5,8, NOTE_C5,8, NOTE_B4,8,
        NOTE_G4,4, NOTE_C5,4, REST,8, NOTE_C5,8, NOTE_B4,8, NOTE_A4,8,

        NOTE_A4,4, NOTE_B4,4, REST,8, NOTE_B4,8, NOTE_A4,8, NOTE_G4,8,
        NOTE_G4,2, REST,8, NOTE_G4,8, NOTE_G4,8, NOTE_A4,8,
        NOTE_B4,4, NOTE_D5,4, REST,8, NOTE_D5,8, NOTE_C5,8, NOTE_B4,8,

        NOTE_G4,4, NOTE_C5,4, REST,8, NOTE_C5,8, NOTE_B4,8, NOTE_A4,8,
        NOTE_A4,4, NOTE_B4,4, REST,8, NOTE_B4,8, NOTE_A4,8, NOTE_G4,8,
        NOTE_G4,4, NOTE_F5,8, NOTE_D5,8, NOTE_E5,8, NOTE_C5,8, NOTE_D5,8, NOTE_B4,8,

        NOTE_C5,8, NOTE_A4,8, NOTE_B4,8, NOTE_G4,8, NOTE_A4,8, NOTE_G4,8, NOTE_E4,8, NOTE_G4,8,
        NOTE_G4,4, NOTE_F5,8, NOTE_D5,8, NOTE_E5,8, NOTE_C5,8, NOTE_D5,8, NOTE_B4,8,
        NOTE_C5,8, NOTE_A4,8, NOTE_B4,8, NOTE_G4,8, NOTE_A4,8, NOTE_G4,8, NOTE_E4,8, NOTE_G4,8,
        NOTE_G4,-2, REST,4
    };

    playMelody(melody, sizeof(melody), pin, channel);
};

void TONE::playTakeOnMe(uint8_t pin, uint8_t channel)
{

    int melody[] = {

        // Take on me, by A-ha
        // Score available at https://musescore.com/user/27103612/scores/4834399
        // Arranged by Edward Truong

        NOTE_FS5,8, NOTE_FS5,8,NOTE_D5,8, NOTE_B4,8, REST,8, NOTE_B4,8, REST,8, NOTE_E5,8,
        REST,8, NOTE_E5,8, REST,8, NOTE_E5,8, NOTE_GS5,8, NOTE_GS5,8, NOTE_A5,8, NOTE_B5,8,
        NOTE_A5,8, NOTE_A5,8, NOTE_A5,8, NOTE_E5,8, REST,8, NOTE_D5,8, REST,8, NOTE_FS5,8,
        REST,8, NOTE_FS5,8, REST,8, NOTE_FS5,8, NOTE_E5,8, NOTE_E5,8, NOTE_FS5,8, NOTE_E5,8,
        NOTE_FS5,8, NOTE_FS5,8,NOTE_D5,8, NOTE_B4,8, REST,8, NOTE_B4,8, REST,8, NOTE_E5,8,

        REST,8, NOTE_E5,8, REST,8, NOTE_E5,8, NOTE_GS5,8, NOTE_GS5,8, NOTE_A5,8, NOTE_B5,8,
        NOTE_A5,8, NOTE_A5,8, NOTE_A5,8, NOTE_E5,8, REST,8, NOTE_D5,8, REST,8, NOTE_FS5,8,
        REST,8, NOTE_FS5,8, REST,8, NOTE_FS5,8, NOTE_E5,8, NOTE_E5,8, NOTE_FS5,8, NOTE_E5,8,
        NOTE_FS5,8, NOTE_FS5,8,NOTE_D5,8, NOTE_B4,8, REST,8, NOTE_B4,8, REST,8, NOTE_E5,8,
        REST,8, NOTE_E5,8, REST,8, NOTE_E5,8, NOTE_GS5,8, NOTE_GS5,8, NOTE_A5,8, NOTE_B5,8,

        NOTE_A5,8, NOTE_A5,8, NOTE_A5,8, NOTE_E5,8, REST,8, NOTE_D5,8, REST,8, NOTE_FS5,8,
        REST,8, NOTE_FS5,8, REST,8, NOTE_FS5,8, NOTE_E5,8, NOTE_E5,8, NOTE_FS5,8, NOTE_E5,8,
    };

    playMelody(melody, sizeof(melody), pin, channel);
};

void TONE::playPacMan(uint8_t pin, uint8_t channel)
{
    int melody[] = {

        // Pacman
        // Score available at https://musescore.com/user/85429/scores/107109
        NOTE_B4, 16, NOTE_B5, 16, NOTE_FS5, 16, NOTE_DS5, 16, //1
        NOTE_B5, 32, NOTE_FS5, -16, NOTE_DS5, 8, NOTE_C5, 16,
        NOTE_C6, 16, NOTE_G6, 16, NOTE_E6, 16, NOTE_C6, 32, NOTE_G6, -16, NOTE_E6, 8,

        NOTE_B4, 16,  NOTE_B5, 16,  NOTE_FS5, 16,   NOTE_DS5, 16,  NOTE_B5, 32,  //2
        NOTE_FS5, -16, NOTE_DS5, 8,  NOTE_DS5, 32, NOTE_E5, 32,  NOTE_F5, 32,
        NOTE_F5, 32,  NOTE_FS5, 32,  NOTE_G5, 32,  NOTE_G5, 32, NOTE_GS5, 32,  NOTE_A5, 16, NOTE_B5, 8
    };

    playMelody(melody, sizeof(melody), pin, channel);
};

void TONE::playSinfonia9(uint8_t pin, uint8_t channel)
{

    int melody[] = {


        NOTE_E4,4,  NOTE_E4,4,  NOTE_F4,4,  NOTE_G4,4,//1
        NOTE_G4,4,  NOTE_F4,4,  NOTE_E4,4,  NOTE_D4,4,
        NOTE_C4,4,  NOTE_C4,4,  NOTE_D4,4,  NOTE_E4,4,
        NOTE_E4,-4, NOTE_D4,8,  NOTE_D4,2,

        NOTE_E4,4,  NOTE_E4,4,  NOTE_F4,4,  NOTE_G4,4,//4
        NOTE_G4,4,  NOTE_F4,4,  NOTE_E4,4,  NOTE_D4,4,
        NOTE_C4,4,  NOTE_C4,4,  NOTE_D4,4,  NOTE_E4,4,
        NOTE_D4,-4,  NOTE_C4,8,  NOTE_C4,2,

        NOTE_D4,4,  NOTE_D4,4,  NOTE_E4,4,  NOTE_C4,4,//8
        NOTE_D4,4,  NOTE_E4,8,  NOTE_F4,8,  NOTE_E4,4, NOTE_C4,4,
        NOTE_D4,4,  NOTE_E4,8,  NOTE_F4,8,  NOTE_E4,4, NOTE_D4,4,
        NOTE_C4,4,  NOTE_D4,4,  NOTE_G3,2,

        NOTE_E4,4,  NOTE_E4,4,  NOTE_F4,4,  NOTE_G4,4,//12
        NOTE_G4,4,  NOTE_F4,4,  NOTE_E4,4,  NOTE_D4,4,
        NOTE_C4,4,  NOTE_C4,4,  NOTE_D4,4,  NOTE_E4,4,
        NOTE_D4,-4,  NOTE_C4,8,  NOTE_C4,2

    };

    playMelody(melody, sizeof(melody), pin, channel);
};

void TONE::playJamesBond(uint8_t pin, uint8_t channel)
{

    int melody[] =
    {
        //NOTE_G4,8, NOTE_G4,8, NOTE_G4 ,2, NOTE_G4,8, NOTE_G4,8, NO_SOUND ,2, NOTE_G4,16, NOTE_G4,8, NOTE_G4,16, NOTE_G4,8, NOTE_G4,8,
        //NOTE_B3,2, NOTE_G3,4, NOTE_C4,2, NOTE_G3,4, NOTE_CS4,2, NOTE_G3,4, NOTE_C4,2, NOTE_G3,4, NOTE_B3,2, NOTE_G3,4, NOTE_C4,2, NOTE_G3,4, NOTE_CS4,2, NOTE_G3,4, NOTE_C4,2, NOTE_G3,4,
        NOTE_E4,8, NOTE_F4,16, NOTE_F4,16, NOTE_F4,8, NOTE_F4,4, NOTE_E4,8, NOTE_E4,8, NOTE_E4,8,
        NOTE_E4,8, NOTE_G4,16, NOTE_G4,16, NOTE_G4,8, NOTE_G4,4, NOTE_E4,8, NOTE_E4,8, NOTE_E4,8,
        //Introduction
        NOTE_E4,8, NOTE_F4,16, NOTE_F4,16, NOTE_F4,8, NOTE_F4,4, NOTE_E4,8, NOTE_E4,8, NOTE_E4,8,
        NOTE_E4,8, NOTE_G4,16, NOTE_G4,16, NOTE_G4,8, NOTE_G4,4, NOTE_E4,8, NOTE_E4,8, NOTE_E4,8,
        NOTE_E4,8, NOTE_F4,16, NOTE_F4,16, NOTE_F4,8, NOTE_F4,4, NOTE_E4,8, NOTE_E4,8, NOTE_E4,8,
        NOTE_E4,8, NOTE_G4,16, NOTE_G4,16, NOTE_G4,8, NOTE_G4,4, NOTE_E4,8, NOTE_E4,8, NOTE_E4,8,
        NOTE_DS5,8, NOTE_D5,2, NOTE_B4,8, NOTE_A4,8, NOTE_B4,1,
        NOTE_E4,8, NOTE_G4,4, NOTE_DS5,8, NOTE_D5,4, NOTE_G4,8, NOTE_B4,8,
        NOTE_B4,8, NOTE_FS5,8, NOTE_F5,4, NOTE_B4,8, NOTE_D5,4, NOTE_AS5,8,
        NOTE_A5,4, NOTE_F5,8, NOTE_A5,4, NOTE_DS6,8, NOTE_D6, NOTE_D6,0 ,3,
    };

    playMelody(melody, sizeof(melody), pin, channel);
};



