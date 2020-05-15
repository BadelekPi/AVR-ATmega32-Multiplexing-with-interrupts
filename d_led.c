
#include <avr/pgmspace.h> //dolaczanie w celu zapisu w pamieci programu FLASH wylacznie do odczytu

#include <avr/io.h> 
#include <avr/interrupt.h> 
#include "d_led.h" //plik naglowkowy, w nim definicje preprocesora
//zmeinne globalne, volatile zeby uzywac zmniennych do odczytu, w przerwaniu i programie glowny. Trzeba wiec wylaczyc optymalizacje do nich tzw. zmienne ulotne
volatile uint8_t cy1;
volatile uint8_t cy2;
volatile uint8_t cy3;
volatile uint8_t cy4;

//definicja funkcji inicjalizujacej prace z wyswietlaczem multipleksowanym 
void d_led_init(void)
{
	LED_DATA_DIR = 0xFF; //wszystkie piny portu C jako wyjscia, katody
	LED_DATA = 0xFF; //wygaszenie wszystkich katod - stan wysoki)
	ANODY_DIR |= CA1 | CA2 | CA3 | CA4; //(4 piny portu A jako WYJSCIA (anody)
	ANODY_PORT |= CA1 | CA2 |CA3 | CA4; //wygaszenie wszystkich wyswietlaczy (anody)
	
	//ustawienie TIMER0
	TCCR0 |= (1<<WGM01); //tryb CTC
	TCCR0 |= (1<<CS02) | (1<<CS00); //preskaler 1024
	0CR0 = 38; //dodatkowy podział przez 38 (rej. przepełnienia)
	TIMSK |= (1<<0CIE0); //zezwolenie na przerwanie COMPARE MATCH
}

//PROCEDURA OBSLUGI PRZERWANIA

ISR(TIMER0_COMP_vect)
{
	//zmienna do przełączania kolejno anod wyświetlacza
	static uint8_t licznik = 1;
	//cyklicze przełączanie w kazdym przerwaniu anod kazdego wyswietlacza
	// (wartosc jest negowana aby krazylo zero)
	ANODY_PORT = ~licznik;
	
	//gdy zapalony wyswietlacz 1, podaj stan zmiennej c1
	if (licznik == 1) LED_DATA = cy1;
	
	//gdy zapalony wyswietlacz 2, podaj stan zmiennej c2
	else if(licznik == 2) LED_DATA = cy2;
	
	//gdy zapalony wyswietlacz 3, podaj stan zmiennej c3
	else if (licznik ==4) LED_DATA = cy3;
	
	//gdy zapalony 4, podaj c4
	else if (licznik == 8) LED_DATA = cy4;
	//operacje cyklicznego przesuwania bitu zapalającego anody w zmiennej licznik
	licznik <<= 1; //przesuniecie zawartosci bitow licznika o 1 w lewo
	if(licznik>8) licznik = 1; //jesli licznik wiekszy niz 8, to ustaw na 1
	
	if(licznik == 1) LED_DATA = pgm_read_byte (&cyfry[cy1]); //gdy wyśw. 1, podaj cy1
	else if (licznik == 2) LED_DATA = pgm_read_byte (&cyfry[cy2]);
	else if (licznik == 4)(LED_DATA = pgm_read_byte(&cyfry[cy3]);
	else if (licznik == 8) LED_DATA = pgm_read_byte(&cyfry[cy4]);
}
}

