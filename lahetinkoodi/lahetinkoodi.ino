#define Button_D2 2//Arduino
const int sampleWindow = 50;
int const AMP_PIN = A0;
unsigned int sample;


void setup() {
  pinMode(Button_D2, OUTPUT);
  pinMode(A0, INPUT);
  Serial.begin(9600);
}

void loop() {
  unsigned long startMillis = millis(); // Start of sample window
  unsigned int peakToPeak = 0;   // peak-to-peak level

  unsigned int signalMax = 0;
  unsigned int signalMin = 1024;

   while (millis() - startMillis < sampleWindow)
  {
    sample = analogRead(AMP_PIN);
    if (sample < 1024)  // toss out spurious readings
    {
      if (sample > signalMax)
      {
        signalMax = sample;  // save just the max levels
      }
      else if (sample < signalMin)
      {
        signalMin = sample;  // save just the min levels
      }
    }
  }

  peakToPeak = signalMax - signalMin;  // max - min = peak-peak amplitude
  Serial.println(peakToPeak);
  
  if(peakToPeak > 200){
    digitalWrite(Button_D2, HIGH);
    delay(500);
    digitalWrite(Button_D2, LOW);

    delay(500); 
  }

}
