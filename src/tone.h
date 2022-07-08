#ifndef _TONE_h
#define _TONE_h

#include "Arduino.h"

#define TONE_CHANNEL 0
#define TONE_DURATION 0

class TONE{
    public:
        void tone(uint8_t pin, unsigned int frequency, unsigned long duration = TONE_DURATION, uint8_t channel = TONE_CHANNEL);
        void noTone(uint8_t pin, uint8_t channel = TONE_CHANNEL);
        void sirene(uint8_t pin, uint8_t channel = TONE_CHANNEL);
        void playStarWars(uint8_t pin,uint8_t channel = TONE_CHANNEL);
        void playPinkPanther(uint8_t pin,uint8_t channel = TONE_CHANNEL);
        void playMarioBross(uint8_t pin,uint8_t channel = TONE_CHANNEL);
        void playFelizAniversario(uint8_t pin,uint8_t channel = TONE_CHANNEL);
        void playFelizNatal(uint8_t pin,uint8_t channel = TONE_CHANNEL);
        void playCoffinDance(uint8_t pin, uint8_t channel = TONE_CHANNEL);
        void playGameThrones(uint8_t pin, uint8_t channel = TONE_CHANNEL);
        void playAsaBranca(uint8_t pin, uint8_t channel = TONE_CHANNEL);        
        void playTakeOnMe(uint8_t pin, uint8_t channel = TONE_CHANNEL);
        void playPacMan(uint8_t pin, uint8_t channel = TONE_CHANNEL);
        void playSinfonia9(uint8_t pin, uint8_t channel = TONE_CHANNEL);  
        void playJamesBond(uint8_t pin, uint8_t channel = TONE_CHANNEL);       
        void playMelody(int melody[], int melodySize, uint8_t pin, uint8_t channel, int duration = 60000);
    private:
        void playMusic(String nameMusic,uint8_t pin,uint8_t channel = TONE_CHANNEL);
        //void playMelody(int melody[], int melodySize, uint8_t pin, uint8_t channel, int duration= 60000);
};
#endif
