volatile uint8_t counter = 0;

// G = PD7, F = PD6, E = PD5, D = PD3
const uint8_t numsD[]{
  0b01101000, // 0: F E D
  0b00000000, // 1: -
  0b10101000, // 2: G E D
  0b10001000, // 3: G D
  0b11000000, // 4: G F
  0b11001000, // 5: G F D
  0b11101000, // 6: G F E D
  0b00000000, // 7: -
  0b11101000, // 8: G F E D 
  0b11001000  // 9: G F D
};

// C = PB4, B = PB3, A = PB2
const uint8_t numsB[]{
  0b00011100, // 0: C B A
  0b00011000, // 1: C B
  0b00001100, // 2: B A
  0b00011100, // 3: C B A
  0b00011000, // 4: B C 
  0b00010100, // 5: C A
  0b00010100, // 6: C A
  0b00011100, // 7: C B A
  0b00011100, // 8: C B A
  0b00011100  // 9: C B A
};

void setup() {
  cli();  // disable interrupts 

  // Set 7-seg display led pins as output
  DDRB |= (1 << PB2) | (1 << PB3) | (1 << PB4);
  DDRD |= (1 << PD3) | (1 << PD5) | (1 << PD6) | (1 << PD7);

  // Data Direction Register D
  DDRD &= ~(1 << PD2);  // Set pin 2 as input (0)
  // Data Register D
  PORTD &= ~(1 << PD2); // Disable internal pull-up (0)

  // External Interruptor Controll Register A
  // ISC01 = 1 ja ISC00 = 0 => falling edge
  EICRA |= (1 << ISC01);
  EICRA &= ~(1 << ISC00);

  // External Interrupt Mask
  EIMSK |= (1 << INT0);
  
  sei();  // Enable global interrupts

  Serial.begin(9600);
}

void loop(){
  // for debuggin
  static uint32_t lastCounter = 0;
  if(lastCounter != counter){
    Serial.println(counter);
    lastCounter = counter;
  }

  // Update 7-segment display pins (PB2-PB4 and PD3, PD5-PD7) without affecting other pins
  PORTB = (PORTB & 0b11100011) | (numsB[counter] & 0b00011100);
  PORTD = (PORTD & 0b00010111) | (numsD[counter] & 0b11101000);
}
  
// Interrupt Service Routine for pin 2 (INT0)
ISR(INT0_vect){
  counter++;

  if(counter > 9){
    counter = 0;
  }
}
