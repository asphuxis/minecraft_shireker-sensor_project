volatile uint8_t counter = 0; // volatile can be changed in interrupts

void setup() {

  cli();  // disable interrupts 

  // Data Direction Register D
  // & = bitwise AND
  DDRD &= ~(1 << PD2);  // Set pin 2 as input (0, ~ = negation)
  // Data Register D
  PORTD &= ~(1 << PD2); // disable internal pull-up (0)

  // External Interruptor Controll Register A
  // ISC01 = 1 ja ISC00 = 0 => falling edge
  EICRA |= (1 << ISC01);
  EICRA &= ~(1 << ISC00);

  // External Interrupt Mask Register 
  EIMSK |= (1 << INT0);

  // Data Direction Register B
  DDRC |= (1 << PC2); // Set pin 12 as output (1)
  
  sei();  // Enable global interrupts

  Serial.begin(9600);
}

ISR(INT0_vect){
  counter++;

  if(counter > 9){
    counter = 0;
  }

  // toggle led
  //PORTC ^= (1 << PC2);  // ^= means XOR 
  PINC = (1 << PC2);
}

void loop(){
  static uint8_t lastCounter = 0;

  if(lastCounter != counter){
    Serial.println(counter);
    lastCounter = counter;
  }  
}
