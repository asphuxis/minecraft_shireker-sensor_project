#define Button_D2 2//Arduino
//#define Button_D2 D2 //ESP32

void setup() {
    Serial.begin(115200);
    pinMode(Button_D2, INPUT);
    pinMode(5, OUTPUT);
}

void loop() {
    if (digitalRead(Button_D2) == 1) {
        digitalWrite(5, HIGH);
    } else {
        digitalWrite(5, LOW);
    }
}
