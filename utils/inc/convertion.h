/**
 * @file convertion.h
 * @author 
 * @brief 
 * @version 0.1
 * @date 
 * 
 * @copyright Copyright Arcom 2019
 * 
 */
#ifndef CONVERTION_H /** Prevent multiple inclusions **/
#define CONVERTION_H

#include <stdint.h>
#include "utilities.h"

/* Exported types---------------------------------------------*/


/* Exported constants---------------------------------------------*/


/** Exported functions---------------------------------------------*/
void init_variables_convertion(void);

float32_t conversionTemperature(uint16_t temperature_analogique);

uint8_t conversionPourcentageDALI(uint8_t prc);
uint8_t conversionDALIPourcentage(uint8_t dali_value);
uint8_t hex2int(char in1, char in2);
uint8_t roundFloat2Int(float32_t value);


#endif /*CONVERTION_H*/