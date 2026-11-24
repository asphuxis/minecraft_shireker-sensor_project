#include <SD.h>
#include <SPI.h>
#include <TMRpcm.h>

#define SD_CS 4

TMRpcm audio;

const char* audiofiles[] = {"shriek1.wav", "shriek2.wav", "shriek3.wav", "shriek4.wav", "shriek5.wav"};
const int numFiles = sizeof(audiofiles) / sizeof(audiofiles[0]);

int lastIndex = -1;

void playRandomSound() {
  int i;
  do {
    i = random(numFiles);
  } while (i == lastIndex && numFiles > 1);  
  lastIndex = i;

  Serial.print("Playing ");
  Serial.println(audiofiles[i]);
  audio.play((char*)audiofiles[i]);
}

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(A0));      
  audio.speakerPin = 9;

  if (!SD.begin(SD_CS)) {
    Serial.println("SD init failed");
    while (true);                  
  }
  Serial.println("SD OK");

  audio.setVolume(5);          
  audio.quality(1);
}

void loop() {
  if (!audio.isPlaying()) {
    delay(2000);      
    playRandomSound();
  }
}