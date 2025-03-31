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

## Mini-Projects
| S.no  | Project Name | Description | Code |
|----|-------------|-------------|--------|
| 01 | LED Blink with simple Delay | Blinking onboard LED (PC13) | [link](https://github.com/galvin-benson/BareMetal_STM32/tree/main/Blink_LED) |
| 02 | LED Control with switch | Turn ON and OFF onboard LED (PC13) based on Switch (PA0) | [link](https://github.com/galvin-benson/BareMetal_STM32/tree/main/LED_Control) |
| 03 |  |  | link |
<details>
  <summary><big><b> 1 - LED BLINK </b></big></summary>
  <p> This project blinks the onboard LED using GPIOC pin 13.<br> To Toggle the LED Pin we can use ODR(Output Data Register) or for Set and Reset we can use BSRR (Bit Set/Reset Register).</p>

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

```plaintext
while(1){
    GPIOC->BSRR = LED_PIN;  // Turn ON LED (Set PC13 = 1)
    for(int i=0; i<680000; i++) {}  // Delay
    
    GPIOC->BSRR = (1U<<29); // Turn OFF LED (Reset PC13 = 0)
    for(int i=0; i<680000; i++) {}  // Delay
}
```
- GPIOC->BSRR (Bit Set/Reset Register)
- GPIOC->BSRR = LED_PIN; (Turn ON LED)
- BSRR's lower 16 bits (0-15) set a pin HIGH (1).
- GPIOC->BSRR = (1U<<29); (Turn OFF LED)
- BSRR's upper 16 bits (16-31) reset a pin LOW (0).
- Why use BSRR? Faster & safer than using GPIOC->ODR ^= LED_PIN;
- Avoids read-modify-write issues (which can cause glitches).

### Output
ON and OFF of on-board LED.

https://github.com/user-attachments/assets/ceb7df33-c68e-4283-8a62-9ff17bf89488

</details>

<details>
  <summary><big><b> 2 - LED CONTROL </b></big></summary>
  <p> This project controls the onboard LED using GPIOC pin 13 based on switch input in GPIOA pin 0.</p>

### Pin Connections
| STM32 Pin | Function |
|-----------|----------|
| PC13      | LED |
| PCA0     | SWITCH |

### Code Explanation
- Configure PA0 as Input (Button)
```plaintext
GPIOA->CRL &= ~(0xF << (0 * 4));  // Clear PA0 configuration
GPIOA->CRL |=  (0x4 << (0 * 4));  // 0b0100 = Input mode (Pull-up/Pull-down)
```
- PA0 is configured as input mode (Pull-up/Pull-down).
- The CRL register controls pins 0-7 of GPIOA.
- Bit shifting (0 * 4) targets PA0.
- 0x4 configures it as Input with Pull-up/Pull-down.
<br>
- Main Loop: Read Button & Control LED

```plaintext
while(1){
    if(!(GPIOA->IDR & BTN_PIN))
        GPIOC->BSRR = LED_PIN;  // Turn ON LED
    else
        GPIOC->BSRR = (1U<<29); // Turn OFF LED
}
```

- GPIOA->IDR & BTN_PIN reads PA0 state.
- Active LOW logic:
-  When button is pressed (PA0 = LOW), LED turns ON.
-  When button is not pressed (PA0 = HIGH), LED turns OFF.
- BSRR register (Bit Set/Reset Register):
-  GPIOC->BSRR = LED_PIN; → Set PC13 HIGH (LED ON).
-  GPIOC->BSRR = (1U << 29); → Reset PC13 LOW (LED OFF).
</details>
