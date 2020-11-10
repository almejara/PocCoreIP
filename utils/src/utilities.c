/**
 * @file utilities.c
 * @author Alejandro Mejia (alejandro.mejia@groupe-arcom.com)
 * @brief 
 * @version 0.1
 * @date 06-02-2019
 * 
 * @copyright Copyright Arcom 2019
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <sys/timeb.h>

#include "utilities.h"
#include "logger.h"
#include "config.h"

/* Global variables -------------------------------------------*/

/* Private defines --------------------------------------------*/

/* Private typedef --------------------------------------------*/

/* Private macros ---------------------------------------------*/

/* Private variables ------------------------------------------*/
static struct timeval sys_start_time, sys_current_time;
static struct timespec start_time, end_time;
static bool start_time_set = false;



/* Private function prototype ---------------------------------*/


/**
 * @brief Set the start time object
 * 
 */
void set_start_time(void)
{
    start_time_set = true;
    clock_gettime(CLOCK_MONOTONIC_RAW, &start_time);
}
/**
 * @brief Print the time elapse between the call of function "set_start_time" et this function
 *        for testing only. 
 * 
 */
void print_time_elapse(void)
{
    if(start_time_set == true)
    {
        ///start_time_set = false;
        clock_gettime(CLOCK_MONOTONIC_RAW, &end_time);
        LOG(AR_ERROR,"Time = %f\n",(end_time.tv_nsec - start_time.tv_nsec) / 1000000000.0 +(end_time.tv_sec  - start_time.tv_sec));
    }
    else
    {
        fprintf(stderr, "function \"set_start_time\" shoulb be called before call this function\n");
    }
    
}

/**
 * @brief 
 * 
 */
void start_system_time(void)
{
    clock_gettime(CLOCK_MONOTONIC_RAW, &start_time);
    fprintf (stderr,"start_time sec : %ld, start_time nsec : %ld \n",start_time.tv_sec,start_time.tv_nsec);
}
/**
 * @brief Get the time ms object
 * 
 * @return uint64_t Time in ms elapse since the start of application
 */
uint64_t get_time_ms(void)
{
    clock_gettime(CLOCK_MONOTONIC_RAW, &end_time);
    //end_time.tv_sec = end_time.tv_sec + 2147380;               /*for test end_time.tv_sec overflow (reboot system before)*/ 
    return (end_time.tv_sec  - start_time.tv_sec)*1000LL + (end_time.tv_nsec - start_time.tv_nsec)/1000000LL;
}

/**
 * @brief Get the time ms object
 * 
 * @return uint64_t Time in ms elapse since the start of application
 */
uint64_t get_time_s(void)
{
    return get_time_ms()/1000;    
}




/**
 * @brief Get the system time object
 * 
 * @return uint64_t 
 */
uint64_t get_system_time(void)
{
	struct timeb timebuffer;
	ftime( &timebuffer );
	return ((uint64_t)timebuffer.time * 1000 + timebuffer.millitm);
}

uint64_t get_mseconds(void)
{
	uint64_t t;
	t = get_system_time();
    return (t / 1000 + t % 1000);
}

/**
 * @brief Get the time string object
 * 
 * @param time 
 * @param s 
 * @param format 
 * @param length 
 * @param msec 
 */
void get_time_string(uint64_t time, char * s, const char * format, int length, char msec) {
	struct tm timeinfo;
	time_t seconds;
	uint32_t mseconds;
	char millisec[8];
	mseconds = time % 1000;
	seconds = time / 1000;
	/* Convert this to a tm struct */
	if (1) {
		localtime_r(&seconds, &timeinfo);
	}
	else {
		gmtime_r(&seconds, &timeinfo);
	}
	if (msec) {
		strftime (s,length - 4,format, &timeinfo);
		/* append the milliseconds */
		memset(millisec, 0, 8);
		sprintf(millisec,"%u", mseconds);
		if (strlen(s) < (size_t)(length - 9)) {
			strncat(s, ",", 1);
			strncat(s, millisec, 8);
		}
	} else strftime (s,length,format,&timeinfo);
}
/**
 * @brief Get the system time string object
 * 
 * @param s 
 * @param format 
 * @param length 
 * @param msec 
 */
void get_system_time_string(char * s, const char * format, int length, char msec)
{
	uint64_t t;
	t = get_system_time();
	get_time_string(t, s, format, length, msec);
}


/**
 * @brief mutex creation
 * 
 * @return pthread_mutex_t* 
 */
pthread_mutex_t * ar_mutex_create() 
{
	pthread_mutex_t * tmp = malloc(sizeof(pthread_mutex_t));
	if (!tmp) 
    {
        LOG(AR_ERROR,"Error creating mutex in %s",__FUNCTION__);
        return NULL;
    }
	return tmp;
}

/**
 * @brief 
 * 
 * @param m 
 */
void ar_mutex_delete(pthread_mutex_t * m) 
{
	pthread_mutex_t * tmp = m;
	if (tmp != NULL) 
    {
	    m = NULL;
	    pthread_mutex_destroy(tmp);
	    free(tmp);
    }
}


/**
 * @brief Allocating memory for string
 * 
 * @param input 
 * @return char* 
 */
char * duplicate_string(const char *input)
{
    char * res = NULL;
    if(!input)
        return NULL;

    res = (char *)calloc(strlen(input) + 1,1);
    if(!res)
    {
        return NULL;
    }

    strcpy(res,input);
    return res;
}
