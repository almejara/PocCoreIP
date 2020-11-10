/**
 * @file global_config.h
 * @author Alejandro Mejia (alejandro.mejia@groupe-arcom.com)
 * @brief 
 * @version 0.1
 * @date 05-02-2019
 * 
 * @copyright Copyright Arcom 2019
 * 
 */

/*-------------------------------VERSIONNING INFORMATIONS---------
SOFTWARE_VERSION defined by:
               HLB_update-firmware-handler
               hlb-ip (this application)   
               hlb-rest-api                


SOFTWARE_VERSION = 2.2 
 - HLB_update-firmware-handler -> V1.0.0
 - hlb-ip                      -> V2.2
 - hlb-rest-api                -> V2.4

 SOFTWARE_VERSION = 2.3 
 - HLB_update-firmware-handler -> V1.0.0
 - hlb-ip                      -> V2.2
 - hlb-rest-api                -> V2.5

  SOFTWARE_VERSION = 2.4 
 - HLB_update-firmware-handler -> V1.0.0
 - hlb-ip                      -> V2.2
 - hlb-rest-api                -> V2.5
 - arcomIP.db                  -> V1.4
 - add crond service which call ip_addr_check.sh script used for check if device has an ip address

   SOFTWARE_VERSION = 2.5 
 - HLB_update-firmware-handler -> V1.0.0
 - hlb-ip                      -> V2.3
 - hlb-rest-api                -> V2.6 (swagger)
 - arcomIP.db                  -> V1.4


   SOFTWARE_VERSION = 2.6 
 - HLB_update-firmware-handler -> V1.0.0
 - hlb-ip                      -> V2.3
 - hlb-rest-api                -> V2.6 (swagger)
 - arcomIP.db                  -> V1.5

    SOFTWARE_VERSION = 2.7 
 - HLB_update-firmware-handler -> V1.0.0
 - hlb-ip                      -> V2.3
 - hlb-rest-api                -> V2.6 (swagger)
 - arcomIP.db                  -> V1.5
 - Add service for fix cpu frequency at startup see http://www.armadeus.org/wiki/index.php?title=Armadeus_7.0_Troubleshots 

  SOFTWARE_VERSION = 2.8 
 - HLB_update-firmware-handler -> V1.0.0
 - hlb-ip                      -> V2.4 (Fix #2545 and KNX Modif:
                                       * Correction du calcul de l'intégrale 
                                       * Suppression de l'alarme de température si l'entrée est constante
 - hlb-rest-api                -> V2.6 (swagger)
 - arcomIP.db                  -> V1.5

   SOFTWARE_VERSION = 2.9 
 - HLB_update-firmware-handler -> V1.0.0
 - hlb-ip                      -> V2.5   
                                        * Erreur temperature si pas de mise à jours au bout de 10 heures au lieu de 1 heure lorsqu'elle fournie par le réseau
 - hlb-rest-api                -> V2.6 (swagger)
 - arcomIP.db                  -> V1.5

   SOFTWARE_VERSION = 3.0 
 - HLB_update-firmware-handler -> V1.0.0
 - hlb-ip                      -> V2.6   
                                        * Function used for get system in ms overflow after 24 days approximately
 - hlb-rest-api                -> V2.6 (swagger)
 - arcomIP.db                  -> V1.5
 
*/

#ifndef GLOBAL_CONFIG_H /** Prevent multiple inclusions **/
#define GLOBAL_CONFIG_H

/* Exported types---------------------------------------------*/
typedef enum {SUCCESS,ERROR} ErrorStatus;
/* Exported constants---------------------------------------------*/ 
#define HLB_IP_VERSION "2.6" 
#define SOFT_VERSION_S "3.0"  
#define SOFTWARE_VERSION "ARCOM_SOFT_VERSION:"SOFT_VERSION_S

//#define ACTIVATED_APP_TEST_HARDWARE

#define _OFF   0x00
#define _ON    0x01

//#define SAVE_VARIABLE_TABLE         /*We don't save in the database the runtime values*/
#define DEBUG_SPI_LOW_LEVEL
//#define MODBUS_SERVER_ACTIVATED
//#define USE_XRAC0006B_BOARD         /*Used for testing only (first phase of dev) XRAC0006B board (SLB main board)*/ 
                                    /*NATURE_CMD_VENTIL_S1 output S1 relay*/
                                    /*NATURE_CMD_VANNE_Y3  output S2 triac*/
                                    /*NATURE_CMD_VANNE_Y1  output S3 triac*/
                                     /*NATURE_CMD_BAT_B     output S4 relay*/
                                    /*NATURE_CMD_0_10V_Y8  output S5 1-10*/

/** Exported functions---------------------------------------------*/


#endif /*GLOBAL_CONFIG_H*/