#ifndef _d_led_h //dyrektywy zabezpieczajace przed wielokrotnym dołączaniem
#include <avr/pgmspace.h>
#define _d_led_h //tego samego pliku naglowkowego, jesli bedzie dolaczany w wielu roznych plikach programu 
//definicje portow i pinow wyswietlacza uzywanych  dla ulatwienia w programie jako stale preprocesora
#define LED_DATA PORTC //port z podłączonymi segmentami
#define LED_DATA_DIR DDRC
#define ANODY_PORT PORTA
#define ANODY_DIR DDRA

#define SEG_A (1<<0)
#define SEG_B (1<<1)
#define SEG_C (1<<2)
#define SEG_D (1<<3)
#define SEG_E (1<<4)
#define SEG_F (1<<5)
#define SEG_G (1<<6)
#define SEG_DP (1<<7)

#define CA1 (1<<PA0) //CA1  oznacza bit nr 0 portu A
#define CA2 (1<<PA1) //CA2 oznacza bit nr 1 portu a
#define CA3 (1<<PA2)
#define CA4 (1<<PA3)
//same deklaracje zmiennych globalnych na potrzeby wykorzystania ich w innych plikach projektu
//przydomek extern powoduje, ze te zmienne beda dostepne we wszystkich modulach, ktore dolacza plik d_led.h za pomoca dyrektywy #include

uint8_t cyfry[15] PROGMEM = {
	~(SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F), //0
	~(SEG_B | SEG_C), //1
	//I TAK DALEJ
}

extern volatile uint8_t cy1; //to sa tylko deklaracje, sluzace do przechowywania wyswietlanych cyfr i znakow na poszczegolnych wyswietlaczach LED
extern volatile uint8_t cy2; //informuje o tym słowo extern
extern volatile uint8_t cy3;
extern volatile uint8_t cy4;

//obszar deklaracji funkcji udostepnionych dla innych modulow
void d_led_init(void);

#endif //koniec _d_led_h 
