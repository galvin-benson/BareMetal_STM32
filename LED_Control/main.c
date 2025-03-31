#include "stm32f103x6.h"

#define GPIOCEN			(1U<<0)
#define PC13			(1U<<13)
#define LED_PIN 		PC13

#define GPIOAEN			(1U<<2)
#define PA0				(1U<<0)
#define BTN_PIN 		PA0

int main(void){

	RCC->APB2ENR |= (1<<4);	// GPIOC clock enable
	RCC->APB2ENR |= (1<<2); // GPIOA clock enable

	GPIOA->CRL &= ~(0xF << (0 * 4));  // Clear PA0
	GPIOA->CRL |=  (0x4 << (0 * 4));  // 0b0100 = Input

	GPIOC->CRH &= ~(0xF << ((13 - 8) * 4));  // Clear PC13
	GPIOC->CRH |=  (0x2 << ((13 - 8) * 4));  // MODE = 2


	while(1){
		if(!(GPIOA->IDR & BTN_PIN))
			GPIOC->BSRR = LED_PIN; // Turn ON LED
		else
			GPIOC->BSRR = (1U<<29); // Turn OFF LED
	}
}
