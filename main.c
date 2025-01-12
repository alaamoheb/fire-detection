/*
 * GccApplication6.c
 *
 * Created: 5/2/2023 3:51:54 PM
 * Author : alaay
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>

#define FLAME_SENSOR_PIN PD3   // Digital pin for flame sensor input (pin 3)
#define LED_PIN PB5            // Digital pin for LED output (pin 13)
#define BUZZER_PIN PB4         // Digital pin for Buzzer output (pin 12)

// Timer1 compare match "interrupt service routine"
ISR(TIMER1_COMPA_vect) {
	// Read the flame sensor input
	uint8_t flameDetected = PIND & (1 << FLAME_SENSOR_PIN);
	
	// If flame is detected, turn on the LED and activate the buzzer
	if (flameDetected == 0) {
		PORTB |= (1 << LED_PIN);    // Turn on LED
		PORTB |= (1 << BUZZER_PIN); // Activate buzzer
		} else {
		PORTB &= ~(1 << LED_PIN);   // Turn off LED
		PORTB &= ~(1 << BUZZER_PIN);// Deactivate buzzer
	}
}

void setup() {
	// Set flame sensor pin as input
	DDRD &= ~(1 << FLAME_SENSOR_PIN);
	
	// Set LED pin as output
	DDRB |= (1 << LED_PIN);
	
	// Set Buzzer pin as output
	DDRB |= (1 << BUZZER_PIN);
	
	// Configure Timer1
	TCCR1A = 0;               // Set entire TCCR1A register to 0
	TCCR1B = 0;               // Same for TCCR1B
	TCNT1  = 0;               // Initialize counter value to 0
	// Set compare match register for 1 Hz increments
	OCR1A = 15624;            // = (16*10^6) / (1024*1) - 1 (must be <65536)
	// Turn on CTC mode
	TCCR1B |= (1 << WGM12);
	// Set CS12 and CS10 bits for 1024 prescaler
	TCCR1B |= (1 << CS12) | (1 << CS10);
	// Enable timer compare interrupt
	TIMSK1 |= (1 << OCIE1A);

	// Enable global interrupts
	sei();
}

int main(void) {
	setup();
	while (1) {
		// Main loop - do other tasks if needed
	}
	return 0;
}
