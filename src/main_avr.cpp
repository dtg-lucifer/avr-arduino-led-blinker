#include <avr/io.h>
#include <util/delay.h>

// ========== UART SETUP ==========

#define BAUD 115200
#define MYUBRR ((F_CPU + BAUD * 8) / (16 * BAUD) - 1)

void uart_init(unsigned int ubrr) {
  UBRR0H = (unsigned char)(ubrr >> 8);
  UBRR0L = (unsigned char)ubrr;
  UCSR0B = (1 << TXEN0);                   // Enable transmitter
  UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);  // 8 data bits, 1 stop bit
}

void uart_send(char data) {
  while (!(UCSR0A & (1 << UDRE0)));  // Wait until buffer empty
  UDR0 = data;
}

void uart_print(const char* str) {
  while (*str) {
    uart_send(*str++);
  }
}

// ========== LED BLINKER CLASS ==========

class Blinker {
 public:
  Blinker() {
    DDRB |= (1 << DDB5);  // Configure pin 13 (PORTB5) as output
  }

  void toggle() { PORTB ^= (1 << PORTB5); }

  void delay_ms(uint16_t ms) {
    while (ms--) _delay_ms(1);
  }
};

// ========== MAIN FUNCTION ==========

int main() {
  uart_init(MYUBRR);
  Blinker led;

  while (1) {
    led.toggle();
    uart_print("Toggled LED\r\n");
    led.delay_ms(500);
  }

  return 0;
}
