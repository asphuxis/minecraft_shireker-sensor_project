
#include <avr/io.h>

void setup()
{
  // Määritetään A0 syöttöpinniks, tän voi salee vaihtaa mut 6 ja 7 on "ongelmallisia" ehkä emt pitää kysyä
  DDRC &= ~(1 << DDC0);

  // Referenssijännitteen valinta -> otetaan käyttöön AVCC eli 5V refe
  ADMUX = (1 << REFS0);

  // Prescaler käyttöönotto ja määritys; 1,1,1 == 128
  ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

  Serial.begin(9600);
}

void loop()
{
    ADCSRA |= (1 << ADSC);

    while (ADCSRA & (1 << ADSC));

    uint16_t soundValue = ADC;

    Serial.println(soundValue);

    delay(100);
}
