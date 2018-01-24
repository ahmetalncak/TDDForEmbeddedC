#pragma once

void LedDriver_Create(unsigned short* address);
void LedDriver_Destroy(void);
void LedDriver_TurnOn(int ledNumber);
void LedDriver_TurnOff(int ledNumber);
void LedDriver_TurnAllOn(void);
void LedDriver_TurnAllOff(void);
unsigned char LedDriver_IsOn(int ledNumber); 
unsigned char LedDriver_IsOff(int ledNumber);