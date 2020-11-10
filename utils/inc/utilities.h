/**
 * @file utilities.h
 * @author Alejandro Mejia (alejandro.mejia@groupe-arcom.com)
 * @brief 
 * @version 0.1
 * @date 06-02-2019
 * 
 * @copyright Copyright Arcom 2019
 * 
 */

#ifndef UTILITIES_H /** Prevent multiple inclusions **/
#define UTILITIES_H

#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <pthread.h>

/* Exported macros*/
#define TICK_GET_DIFF(a,b)         ((a) - (b))
#define DO_PRAGMA(x) _Pragma (#x)
#define TODO(x) ;//DO_PRAGMA(message ("\033[0;31m""TODO - " #x))

#define GET_INT16_FROM_INT8(tab_int8, index) ((tab_int8[(index)] << 8) + tab_int8[(index) + 1])

/*Debug print*/
#define TRACE_TEXT(Text)            fprintf(stderr,"%s",Text)
#define E_TRACE_TEXT(Text)          fprintf(stderr,"%s",Text)
#define TRACE_TEXT_LF(Text)         fprintf(stderr,"%s\n",Text)
#define E_TRACE_TEXT_LF(Text)       fprintf(stderr,"%s\n",Text)

#define TRACE_STRING(Text)          fprintf(stderr,"%s",Text)
#define TRACE_STRING_LF(Text)       fprintf(stderr,"%s\n",Text)

#define TRACE_INT8D(nDate)          fprintf(stderr,"%d",nDate)
#define TRACE_INT8D_LF(nDate)       fprintf(stderr,"%d\n",nDate)
#define TRACE_UINT8H(nDate)         fprintf(stderr,"%02x",nDate)
#define TRACE_UINT8H_LF(nDate)      fprintf(stderr,"%02x\n",nDate)
#define TRACE_UINT8D(nDate)         fprintf(stderr,"%u",nDate)
#define TRACE_UINT8D_LF(nDate)      fprintf(stderr,"%u\n",nDate)


#define TRACE_UINT16D(nDate)        fprintf(stderr,"%u",nDate)
#define TRACE_UINT16D_LF(nDate)     fprintf(stderr,"%u\n",nDate)


#define TRACE_FLOAT32(nDate)         fprintf(stderr,"%f",nDate)
#define E_TRACE_FLOAT32(nDate)       fprintf(stderr,"%f",nDate)
#define TRACE_FLOAT32_LF(nDate)      fprintf(stderr,"%f\n",nDate)
#define E_TRACE_FLOAT32_LF(nDate)    fprintf(stderr,"%f\n",nDate)

#define TRACE_UINT32D(nDate)        fprintf(stderr,"%u",nDate)
#define TRACE_UINT32D_LF(nDate)     fprintf(stderr,"%u\n",nDate)



/* Exported types---------------------------------------------*/
typedef    bool     bool_t;
typedef    char     char_t;
typedef    float    float32_t;
typedef    int32_t  sint32_t;
/* Exported constants---------------------------------------------*/
#define TICK   uint64_t
/** Exported functions---------------------------------------------*/
void set_start_time(void);
void print_time_elapse(void);

uint64_t get_system_time(void);
void get_time_string(uint64_t time, char * s, const char * format, int length, char msec);
void get_system_time_string(char * s, const char * format, int length, char msec);

void start_system_time(void);
uint64_t get_time_s(void);
uint64_t get_time_ms(void);


//uint64_t get_mseconds(void);

char * duplicate_string(const char *input);

pthread_mutex_t * ar_mutex_create(void);
void ar_mutex_delete(pthread_mutex_t * m);

float thermistor_calcule_degrees(uint16_t analog_temper);

int32_t set_app_version(void);

#endif  /*UTILITIES_H*/