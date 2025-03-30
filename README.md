# BareMetal_STM32
<details>
  <summary><big><b>Click Me😊</b></big></summary>
  <p>Hiii! I'm Galvin Benson<br>Email ID: galvin.benson@gmail.com<br>GitHub Profile: https://github.com/galvin-benson<br>LinkedIn Profile: www.linkedin.com/in/galvin-benson</p>
</details>

## STM32F103C8T6 (Blue Pill)
This repository documents my **bare-metal STM32 programming** journey from scratch, without HAL or libraries. Each project is in its respective folder.<br>
Programs were Flashed using a ST-Link V2

## Pin Diagram
![image](https://github.com/user-attachments/assets/ee903458-2c5b-4796-92c8-328674ff9ddf)

## Projects
| S.no  | Project Name | Description | Code |
|----|-------------|-------------|--------|
| 01 | [LED Blink](https://github.com/galvin-benson/BareMetal_STM32#:~:text=link-,1%20%2D%20LED%20BLINK,-This%20project%20blinks) | Blinking onboard LED (PC13) | [link](https://github.com/galvin-benson/BareMetal_STM32/blob/d4d827f9787c41d1d5f38766cc8d9db26bce9959/Blink_LED/main.c) |
| 02 |  |  | link |
| 03 |  |  | link |
<details>
  <summary><big><b> 1 - LED BLINK </b></big></summary>
  <p> This project blinks the onboard LED using GPIOC pin 13. </p>

### Pin Connections
| STM32 Pin | Function |
|-----------|----------|
| PC13      | LED |

### Code Explanation
Header File Inclusion:
```plaintext
#include "stm32f103x6.h"
```
- This includes the CMSIS (Cortex Microcontroller Software Interface Standard) header file.
- It provides register definitions for the STM32F103 series.
```plaintext
#define GPIOCEN			(1U << 4)  // Enable GPIOC clock
#define PIN13			(1U << 13) // Pin 13 mask
#define LED_PIN 		PIN13      // For LED
```
- **GPIOCEN:** Enables the clock for GPIOC (Bit 4 in RCC->APB2ENR).
- **PIN13:** Refers to bit 13 (PC13) in the GPIO Output Data Register (ODR).
- **LED_PIN:** Defines LED alias for better code readability.
```plaintext
RCC->APB2ENR |= GPIOCEN; // Enable GPIOC clock
```
- GPIO ports need a clock to operate.
- The RCC (Reset and Clock Control) peripheral has an APB2ENR (APB2 Enable Register).
- Bit 4 (corresponding to GPIOC) is set to 1 to enable the GPIOC peripheral.
```plaintext
GPIOC->CRH &= ~(0xF << ((13 - 8) * 4));  // Clear PC13 settings
GPIOC->CRH |=  (0x2 << ((13 - 8) * 4));  // Set PC13 as Output (MODE = 2, CNF = 0)
```
- GPIOC->CRH (GPIOC Configuration Register High) controls pins 8-15.
- PC13 is in CRH, so we configure the MODE and CNF bits.
```plaintext
GPIOC->CRH &= ~(0xF << ((13 - 8) * 4));
```
- (13 - 8) * 4 calculates the bit position of PC13 in CRH.
- 0xF (binary 1111) represents all 4 bits (MODE + CNF) for PC13.
- The bitwise AND with NOT (~) clears the bits.
```plaintext
GPIOC->CRH |= (0x2 << ((13 - 8) * 4));
```
- 0x2 in binary: 0010 (MODE = 10, CNF = 00).
- MODE = 2 (10) → Output mode at 2 MHz speed.
- CNF = 0 (00) → General-purpose push-pull output.
```plaintext
while(1){
	GPIOC->ODR ^= LED_PIN; // Toggle PC13 (LED)
	for(int i=0; i<680000; i++) {} // Simple delay
}
```
- **GPIOC->ODR ^= LED_PIN;**
- XOR (^=) toggles the LED.
- If LED was ON, it turns OFF, and vice versa.
- **for(int i=0; i<680000; i++) {}**
- Creates a delay (not precise, just a loop for roughly 1sec delay).
- The exact delay depends on the CPU clock speed.

### Output
When on-board LED is OFF.
![WhatsApp Image 2025-03-30 at 20 28 20](https://github.com/user-attachments/assets/bb6db1a2-3553-401a-886e-9280226750fc)
<br>
When on-board LED is ON.
![WhatsApp Image 2025-03-30 at 20 28 20 (1)](https://github.com/user-attachments/assets/a4d8bfb1-84d1-4c38-b567-7f595fd67e95)


</detail>
