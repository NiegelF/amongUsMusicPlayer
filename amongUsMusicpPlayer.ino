#include <SoftwareSerial.h>
#include <DFMiniMp3.h>

#define TX_PIN 10  // Connect to the TX pin of DFMini player
#define RX_PIN 11  // Connect to the RX pin of DFMini player

#define PLAY_PAUSE_BUTTON 2
#define NEXT_SONG_BUTTON 3
#define PREVIOUS_SONG_BUTTON 4

SoftwareSerial mp3Serial(TX_PIN, RX_PIN);
DFMiniMp3<SoftwareSerial, Mp3Notify> mp3(mp3Serial);

void setup() {
  Serial.begin(9600);
  mp3Serial.begin(9600);

  pinMode(PLAY_PAUSE_BUTTON, INPUT_PULLUP);
  pinMode(NEXT_SONG_BUTTON, INPUT_PULLUP);
  pinMode(PREVIOUS_SONG_BUTTON, INPUT_PULLUP);

  mp3.begin();
  mp3.setVolume(20); // Adjust the volume (0 to 30)
}

void loop() {
  // Check for play/pause button press
  if (digitalRead(PLAY_PAUSE_BUTTON) == LOW) {
    if (mp3.getStatus() == Mp3PlayStatus::PLAYING) {
      mp3.pause();
    } else {
      mp3.start();
    }
    delay(200);  // Debounce
  }

  // Check for next song button press
  if (digitalRead(NEXT_SONG_BUTTON) == LOW) {
    mp3.next();
    delay(200);  // Debounce
  }

  // Check for previous song button press
  if (digitalRead(PREVIOUS_SONG_BUTTON) == LOW) {
    mp3.previous();
    delay(200);  // Debounce
  }

  mp3.loop();
}
