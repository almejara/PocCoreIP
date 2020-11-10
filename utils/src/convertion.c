/**
 * @file convertion.c
 * @author 
 * @brief 
 * @version 0.1
 * @date 
 * 
 * @copyright Copyright Arcom 2019
 * 
 */

#include <math.h>
#include "convertion.h"

/* Global variables -------------------------------------------*/

/* Private defines --------------------------------------------*/

/* Private typedef --------------------------------------------*/

/* Private macros ---------------------------------------------*/

/* Private variables ------------------------------------------*/
static uint16_t Temperature_Analogique[24];
static int8_t Temperature_Degres[24];
/* Private function prototype ---------------------------------*/



void init_variables_convertion(void)
{
     Temperature_Analogique[0] = 3889;
     Temperature_Analogique[1] = 3444;
     Temperature_Analogique[2] = 3006;
     Temperature_Analogique[3] = 2591;
     Temperature_Analogique[4] = 2210;
     Temperature_Analogique[5] = 1868;
     Temperature_Analogique[6] = 1568;
     Temperature_Analogique[7] = 1405;
     Temperature_Analogique[8] = 1359;
     Temperature_Analogique[9] = 1312;
     Temperature_Analogique[10] = 1265;
     Temperature_Analogique[11] = 1220;
     Temperature_Analogique[12] = 1177;
     Temperature_Analogique[13] = 1135;
     Temperature_Analogique[14] = 1094;
     Temperature_Analogique[15] = 1055;
     Temperature_Analogique[16] = 1017;
     Temperature_Analogique[17] = 911;
     Temperature_Analogique[18] = 758;
     Temperature_Analogique[19] = 632;
     Temperature_Analogique[20] = 441;
     Temperature_Analogique[21] = 311;
     Temperature_Analogique[22] = 161;
     Temperature_Analogique[23] = 88;
     
     Temperature_Degres[0] = -15;
     Temperature_Degres[1] = -10;
     Temperature_Degres[2] = -5;
     Temperature_Degres[3] = 0;
     Temperature_Degres[4] = 5;
     Temperature_Degres[5] = 10;
     Temperature_Degres[6] = 15;
     Temperature_Degres[7] = 18;
     Temperature_Degres[8] = 19;
     Temperature_Degres[9] = 20;
     Temperature_Degres[10] = 21;
     Temperature_Degres[11] = 22;
     Temperature_Degres[12] = 23;
     Temperature_Degres[13] = 24;
     Temperature_Degres[14] = 25;
     Temperature_Degres[15] = 26;
     Temperature_Degres[16] = 27;
     Temperature_Degres[17] = 30;
     Temperature_Degres[18] = 35;
     Temperature_Degres[19] = 40;
     Temperature_Degres[20] = 50;
     Temperature_Degres[21] = 60;
     Temperature_Degres[22] = 80;
     Temperature_Degres[23] = 100;
}
/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------  
* Description : fonction de conversion de la temperature analogique en degrès
* Input (s): valeur analogique de la température 
* Output (s) : valeur en degrès de la temperature 
* Paramètre(s): aucun 
* Commentaire(s): température analogique mesurée avec une sonde de type NTC 10 kOhm et remontée par une trame SPI  
*/
float32_t conversionTemperature(uint16_t temperature_analogique)
{
     //unsigned short Temperature_Analogique[24]={3889,3444,3006,2591,2210,1868,1568,1405,1359,1312,1265,1220,1177,1135,1094,1055,1017,911,758,632,441,311,161,88};
     //signed char Temperature_Degres[24]={-15,-10,-5,0,5,10,15,18,19,20,21,22,23,24,25,26,27,30,35,40,50,60,80,100};	
     
     float32_t xa_analogique = 0;
     float32_t xb_analogique = 0;				
     float32_t ya_degres = 0;	
     float32_t yb_degres = 0;
     float32_t pente_temperature = 0;
     float32_t oo_temperature = 0;
     
     float32_t temperature_degres = 0;	
     
     
     if (temperature_analogique > Temperature_Analogique[0])
     {
          temperature_degres = -20; 
     }
     else if (temperature_analogique < Temperature_Analogique[23])
     {
          temperature_degres = 120; 
     }
     else 
     {
          for (uint8_t t = 0; t < 23; t++)
          {
               if ((temperature_analogique <= Temperature_Analogique[t]) && (temperature_analogique >= Temperature_Analogique[t+1]))
               {
                    
                    xa_analogique = Temperature_Analogique[t+1];
                    xb_analogique = Temperature_Analogique[t];
                    
                    ya_degres = Temperature_Degres[t+1];
                    yb_degres = Temperature_Degres[t];
                    break;
               }
          }
          
          pente_temperature = ((yb_degres - ya_degres) / (xb_analogique - xa_analogique));
          oo_temperature = (ya_degres - (pente_temperature * xa_analogique));
          
          temperature_degres = (temperature_analogique * pente_temperature) + oo_temperature; 
     }
     
     
     
     return temperature_degres;  
     
}

uint8_t conversionPourcentageDALI(uint8_t prc)
{
     if(prc == 0) return 0;
     else if(prc >= 100) return 254;
     else return (uint8_t)(36.763*log((double)prc)+84.717);   
}

uint8_t conversionDALIPourcentage(uint8_t dali_value)
{
     if (dali_value == 0) return 0;
      else if(dali_value >= 254) return 100;
      else return (uint8_t) (pow(10.0, (((float32_t)dali_value -1)/(253.0/3.0)))*0.1);
}

uint8_t hex2int(char in1, char in2) 
{
     uint8_t msb;
     uint8_t lsb;
     
    if(((in1 >= '0') && (in1 <= '9'))) msb = in1-'0';
    else if(((in1 >= 'a') && (in1 <= 'f'))) msb = in1-'a' + 10;
    else if(((in1 >= 'A') && (in1 <= 'F'))) msb = in1-'A' + 10;
    else msb = 0;
    
    if(((in2 >= '0') && (in2 <= '9'))) lsb = in2-'0';
    else if(((in2 >= 'a') && (in2 <= 'f'))) lsb = in2-'a' + 10;
    else if(((in2 >= 'A') && (in2 <= 'F'))) lsb = in2-'A' + 10;
    else lsb = 0;
    
    uint8_t retour = (msb <<4) + lsb;
   
    return retour;
}

uint8_t roundFloat2Int(float32_t value)
{
     return lroundf(value);
}