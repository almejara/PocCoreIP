/**
 * @file logger.c
 * @author Alejandro Mejia (alejandro.mejia@groupe-arcom.com)
 * @brief 
 * @version 0.1
 * @date 04-02-2019
 * 
 * @copyright Copyright Arcom 2019
 * 
 */

#include <stdint.h>
#include <stdlib.h>

#include <stdio.h>
#include <stdarg.h>

#include "logger.h"
#include "utilities.h"


static ar_logger * logger_singleton = NULL;


/**
 * @brief 
 * 
 * @param LogLevel 
 * @return char* 
 */
char * levelString(enum LogLevel level) {
	switch(level) {
	case AR_TRACE: 
		return "AR_TRACE";
	case AR_DEBUG: 
		return "AR_DEBUG";
	case AR_INFO: 
		return "AR_INFO";
	case AR_WARN: 
		return "AR_WARN";
	case AR_ERROR: 
		return "AR_ERROR";
	case AR_FORCE: 
		return "AR_FORCE";
	case AR_AUDIT: 
		return "AR_AUDIT";
	default: 
		return "UNKNOWN";
	}
}

/* Logging Function */
void LOGGING_FUNCTION( enum LogLevel level, const char * timestamp, const char * message ) 
{
	#if 0
	if(level == AR_ERROR)
		fprintf(stderr,"\033[0;31m""[%-5s] %s: %s", levelString(level), timestamp, message);
	else if(level == AR_WARN)
		fprintf(stderr,"\033[0;33m""[%-5s] %s: %s", levelString(level), timestamp, message);
	else if(level == AR_AUDIT)
		fprintf(stderr,"\033[0;32m""[%-5s] %s: %s", levelString(level), timestamp, message);
	else
		fprintf(stderr,"\033[0;37m""[%-5s] %s: %s", levelString(level), timestamp, message);
	#endif
		if(level == AR_ERROR)
		fprintf(stderr,"\033[0;31m""[%-5s]: %s", levelString(level), message);
	else if(level == AR_WARN)
		fprintf(stderr,"\033[0;33m""[%-5s]: %s", levelString(level), message);
	else if(level == AR_AUDIT)
		fprintf(stderr,"\033[0;32m""[%-5s]: %s", levelString(level), message);
	else
		fprintf(stderr,"\033[0;37m""[%-5s]: %s", levelString(level), message);
}

ar_logger * ar_logger_instance() 
{
	ar_logger * temp = NULL;
	/* Check to see if it was created already */
	if (logger_singleton) return logger_singleton;
	temp = (ar_logger *)calloc(sizeof(ar_logger),1);
	temp->level = AR_WARN;
	temp->f = LOGGING_FUNCTION;
	temp->isVerbose = 0;
	temp->buffer = (char *)malloc(LOGGER_BUF_SIZE);
	temp->mtx = ar_mutex_create();
	logger_singleton = temp;
	return logger_singleton;
}

int ar_logger_delete() 
{
	if (logger_singleton) {
		ar_logger * temp = logger_singleton;
		logger_singleton = NULL;
		free(temp->buffer);
		ar_mutex_delete(temp->mtx);
		free(temp);
	}
	return LOGGER_RET_OK;
}

int ar_logger_set_level(enum LogLevel level) 
{
	ar_logger * l = ar_logger_instance();
	if (l) {
		l->level = level;
		fprintf(stderr,"\033[0;37m""");  /*Color default set write*/
		return LOGGER_RET_OK;
	} else return NULL_OR_INVALID_LOGGER_SINGLETON;
}


void ar_log(enum LogLevel level, const char * format, ... ) 
{
	char timeStr[80];
	ar_logger * l = ar_logger_instance();
	va_list va;

	if (!l || level < l->level) return;
	/* prepare the message */
	if (!l->buffer || !l->mtx) return;
	//if (!l->buffer) return;
	pthread_mutex_lock(l->mtx);
    va_start(va, format);
    vsnprintf(l->buffer, LOGGER_BUF_SIZE - 1, format, va);
	va_end(va);
	/* get the timestamp */
	get_system_time_string(timeStr, "%Y-%m-%d %H:%M:%S", 80, 0);
	//get_system_time_string(timeStr, "%d %H:%M:%S", 80, 1, 1);
	l->f(level, timeStr, l->buffer);
	pthread_mutex_unlock(l->mtx);
}


