// This #include statement was automatically added by the Spark IDE.
#include "Emic2TTS\Emic2TTS.h"

Emic2TtsModule emic;
bool isDemoCompleted = false;

void setup() {
    emic.init();
    pinMode(D7, OUTPUT);
}

void loop() {
    if(!isDemoCompleted){
        emic.say("Hello everyone, here is a demonstration of a project using Spark Core and Emic2 Text-to-Speech board.");
        emic.say("Emic2 text-to-Speech board is simple to use and easy to connect powerful TTS board, it has all the features of common TTS engine, like change the volume, pitch and so on");
        emic.say("This project contains two applicaitons, one the Spark Core application and a web application to change the Emic2 properties like volume, voice, pitch, etc...");
        emic.say("Hope everybody enjoyed this video.");
        emic.say("Thank you for watching and happy TTS coding.");

        isDemoCompleted = true;
    }
    
    digitalWrite(D7, HIGH);
    delay(1000);
    digitalWrite(D7, LOW);
    delay(1000);
}