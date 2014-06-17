#include "Emic2TTS\Emic2TTS.h"

// Property tags
#define VOLUME "Volume"
#define VOICE "Voice"
#define WORDPERMINUTE "WordsPerMinute"
#define LANGUAGE "Language"
#define PARSER "Parser"
#define PLAYSPANISH "PlaySpanishDemo"
#define PLAYENGLISH "PlayEnglishDemo"
#define PLAYSINGING "PlaySingingDemo"
#define RESET "Reset"

// Command to execure like, speak, set volume, etc...
// This is to avoid the sync operation of the library we are using.
// This can be avoided by changing the Emic2TtsModule::sendTerminatorAndWait
// method and check the Emic2 response in Loop.
#define CMD_NONE 0
#define CMD_SPEAK 1
#define CMD_SET_VOLUME 2
#define CMD_SET_VOICE 3
#define CMD_SET_WORDS_PER_MINUTE 4
#define CMD_SET_LANGUAGE 5
#define CMD_PLAY_SPANISH_DEMO 6
#define CMD_PLAY_ENGLISH_DEMO 7
#define CMD_PLAY_SINGING_DEMO 8
#define CMD_RESET 9

Emic2TtsModule emic;
String textToSpeak = "";

int emicVolume = 10;
int emicVoice = PerfectPaul;
int emicWordsPerMinute = 200;
int emicLanguage = English;

int command = CMD_NONE;

// Speak the text
int emicSpeakText(String text){
    urlDecode(text);
    
    textToSpeak = "";
    textToSpeak += text;
        
    command = CMD_SPEAK;
    
    return 1;
}

// Set different Emic2 properties
int emicSetProperties(String prop){
    int delim = prop.indexOf('=');
    

    String key = (-1 == delim) ? prop : prop.substring(0, delim);
    String value = (-1 == delim) ? "" : prop.substring(delim + 1);
    
    // FOR DEBUGGING PURPOSE ONLY, WE CAN SAFELY REMOVE IT.
    Spark.publish("propInfo", prop + ", " + key + ", " + value);
    
    // Volume
    if(key.equalsIgnoreCase(VOLUME)){
        emicVolume = value.toInt();
        
        command = CMD_SET_VOLUME;
    }
    // Voice
    else if(key.equalsIgnoreCase(VOICE)){
        emicVoice = value.toInt();
        
        command = CMD_SET_VOICE;
    }
    // Words Per Minute
    else if(key.equalsIgnoreCase(WORDPERMINUTE)){
        emicWordsPerMinute = value.toInt();
        
        command = CMD_SET_WORDS_PER_MINUTE;
    }
    // Language
    else if(key.equalsIgnoreCase(LANGUAGE)){
        emicLanguage = value.toInt();
        
        command = CMD_SET_LANGUAGE;
    }
    // Play a spanish demo
    else if(key.equalsIgnoreCase(PLAYSPANISH)){
        command = CMD_PLAY_SPANISH_DEMO;
    }
    // Play English demo
    else if(key.equalsIgnoreCase(PLAYENGLISH)){
        command = CMD_PLAY_ENGLISH_DEMO;
    }
    // Play a demo song
    else if(key.equalsIgnoreCase(PLAYSINGING)){
        command = CMD_PLAY_SINGING_DEMO;
    }
    // Reset the Emic2 board
    else if(key.equalsIgnoreCase(RESET)){
        command = CMD_RESET;
    }
    
    return 1;
}

// Speak
void emicSpeak(String text){
    emic.say(textToSpeak);
}

// Set volume
void emicSetVolume(int vol){
    if(vol < -48){ vol = -48; }
    else if(vol > 18){ vol = 18; }
    
    emic.setVolume(vol);
}

// Set voice
void emicSetVoice(int voice){
    EmicVoice ev = PerfectPaul;
    
    switch(voice){
        case 0:     ev = PerfectPaul;       break;
        case 1:     ev = HugeHarry;         break;
        case 2:     ev = BeautifulBetty;    break;
        case 3:     ev = UppityUrsula;      break;
        case 4:     ev = DoctorDennis;      break;
        case 5:     ev = KitTheKid;         break;
        case 6:     ev = FrailFrank;        break;
        case 7:     ev = RoughRita;         break;
        case 8:     ev = WhisperingWendy;   break;
        default:    ev = PerfectPaul;       break;
    }
    
    emic.setVoice(ev);
}

// Set words per minute
void emicSetWordsPerMinute(int words){
    if(words < 75){ words = 75; }
    else if(words > 600){ words = 600; }
    
    emic.setWordsPerMinute(words);
}

// Set language
void emicSetLanguage(int language){
    EmicLanguage lan = English;
    
    switch(language){
        case 0:     lan = English;           break;
        case 1:     lan = CastilianSpanish;  break;
        case 2:     lan = LatinSpanish;      break;
        default:    lan = English;           break;
    }
    
    emic.setLanguage(lan);
}

// Play Spanish demo
void emicPlaySpanishDemo(){
    emic.playSpanishDemo();
}

// Play English demo
void emicPlayElglishDemo(){
    emic.playSpeakingDemo();
}

// Play a demo song
void emicPlaySingingDemo(){
    emic.playSingingDemo();
}

// Reset the Emic2 board
void emicReset(){
    emic.restoreDefaults();
}

// urlDecode function taken from
// https://community.spark.io/t/problem-with-function-returning-string/3135/5
void urlDecode(String &input){
    input.replace("%20", " ");
    input.replace("+", " ");
    input.replace("%21", "!");
    input.replace("%22", "\"");
    input.replace("%23", "#");
    input.replace("%24", "$");
    input.replace("%25", "%");
    input.replace("%26", "&");
    input.replace("%27", "\'");
    input.replace("%28", "(");
    input.replace("%29", ")");
    input.replace("%30", "*");
    input.replace("%31", "+");
    input.replace("%2C", ",");
    input.replace("%2E", ".");
    input.replace("%2F", "/");
    input.replace("%2C", ",");
    input.replace("%3A", ":");
    input.replace("%3A", ";");
    input.replace("%3C", "<");
    input.replace("%3D", "=");
    input.replace("%3E", ">");
    input.replace("%3F", "?");
    input.replace("%40", "@");
    input.replace("%5B", "[");
    input.replace("%5C", "\\");
    input.replace("%5D", "]");
    input.replace("%5E", "^");
    input.replace("%5F", "-");
    input.replace("%60", "`");
}

// Blink LED
void BlinkLED(){
    digitalWrite(D7, HIGH);   
    delay(500);
    digitalWrite(D7, LOW);   
    delay(500);
}

void setup() {
    pinMode(D7, OUTPUT);
    emic.init();
    
    Spark.function("speak", emicSpeakText);
    Spark.function("setProp", emicSetProperties);
}

void loop() {
    // Whether we have a command to execute or not
    bool isCommandFound = true;
    
    // Execute command.
    switch(command){
        case CMD_SPEAK:{
            emicSpeak(textToSpeak);
            
            textToSpeak = "";
            
            break;
        }
        case CMD_SET_VOLUME:{
            emicSetVolume(emicVolume);
            
            break;
        }
        case CMD_SET_VOICE:{
            emicSetVoice(emicVoice);
            
            break;
        }
        case CMD_SET_WORDS_PER_MINUTE:{
            emicSetWordsPerMinute(emicWordsPerMinute);
            
            break;
        }
        case CMD_SET_LANGUAGE:{
            emicSetLanguage(emicLanguage);
            
            break;
        }
        case CMD_PLAY_SPANISH_DEMO:{
            emicPlaySpanishDemo();
            
            break;
        }
        case CMD_PLAY_ENGLISH_DEMO:{
            emicPlayElglishDemo();
            
            break;
        }
        case CMD_PLAY_SINGING_DEMO:{
            emicPlaySingingDemo();
            
            break;
        }
        case CMD_RESET:{
            emicReset();
            
            break;
        }
        default:{
            isCommandFound = false;
        }
    }
    
    // Set command to none if we have one command to executre and done.
    if(isCommandFound){
        command = CMD_NONE;
    }
    
    
    BlinkLED();
    
    delay(1000);
}