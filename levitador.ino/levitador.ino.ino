byte TP = 0b10101010; //every 2nd port receives the opposite signal
void setup()
{
 DDRC = 0b11111111; //Define all analog ports as outputs
  // Initialize timer 1
  noInterrupts();           // Disable interrupts
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;
  OCR1A = 200;              // Set Compare Match Register (16MHz / 200 = 80kHz square -> 40kHz full wave)
  TCCR1B |= (1 << WGM12);   // CTC mode
  TCCR1B |= (1 << CS10);    
  TIMSK1 |= (1 << OCIE1A);  // Switch on Compare Timer Interrupt  
  interrupts();             // Activate interrupts
}
ISR(TIMER1_COMPA_vect)          
{
  PORTC = TP; // Send the value TP to the outputs
  TP = ~TP;   // Invert TP for the next run
}
void loop(){
  // there is nothing left to do here:-(
}
