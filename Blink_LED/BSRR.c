#include "stm32f103x6.h"

#define GPIOCEN			(1U<<0)
#define PIN13			(1U<<13)
#define LED_PIN 		PIN13

int main(void){

	RCC->APB2ENR |= (1<<4);	// GPIOC clock enable

	GPIOC->CRH &= ~(0xF << ((13 - 8) * 4));  // Clear PC13
	GPIOC->CRH |=  (0x2 << ((13 - 8) * 4));  // MODE = 2


	while(1){
		GPIOC->BSRR = LED_PIN;
		for(int i=0;i<680000;i++) {}
		GPIOC->BSRR = (1U<<29);
		for(int i=0;i<680000;i++) {}
		for(int i=0;i<680000;i++) {}
	}
}
