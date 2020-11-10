/*
 * ech_logger.c
 *
 * Copyright 2010 Echelon Corporation.  All Rights Reserved.
 *
 * This file contains Echelon Logger API implementation.
 */


#include <stdarg.h>
#include <string.h>
#include <syslog.h>
#include <stdio.h>

#include "ech_logger.h"

#define BUFSIZE		1024


LOG_TIME_SPEC DeltaTime(LOG_TIME_SPEC start, LOG_TIME_SPEC end)
{
	LOG_TIME_SPEC temp;

#ifdef USE_NON_OSAL_TICK_COUNT
	if ((end.tv_nsec-start.tv_nsec)<0) {
		temp.tv_sec = end.tv_sec-start.tv_sec-1;
		temp.tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;
	} else {
		temp.tv_sec = end.tv_sec-start.tv_sec;
		temp.tv_nsec = end.tv_nsec-start.tv_nsec;
	}
#else
	temp = end - start;			// OsalTickCount is unsigned 32-bit integer
#endif
	return temp;
}

int DeltaTimeGreaterThan(LOG_TIME_SPEC time, unsigned long int seconds)
{
#ifdef USE_NON_OSAL_TICK_COUNT
	return (time.tv_sec > seconds);
#else
	return ((time/OsalGetTicksPerSecond()) > seconds);
#endif
}

int DeltaTimeLessThan(LOG_TIME_SPEC time, unsigned long int seconds)
{
#ifdef USE_NON_OSAL_TICK_COUNT
	return (time.tv_sec < seconds);
#else
	return ((time/OsalGetTicksPerSecond()) < seconds);
#endif
}

int DeltaTimeEqual(LOG_TIME_SPEC time, unsigned long int seconds)
{
#ifdef USE_NON_OSAL_TICK_COUNT
	return (time.tv_sec == seconds);
#else
	return ((time/OsalGetTicksPerSecond()) == seconds);
#endif
}


LOG_TIME_SPEC GetCurrentTime()
{
#ifdef USE_NON_OSAL_TICK_COUNT
	LOG_TIME_SPEC time;
	clockGettime(CLOCK_MONOTONIC, &time);
	return time;
#else
	return OsalGetTickCount();
#endif
}

int ThrottleLogging(throttle_log * pThrottle)
{
	LOG_TIME_SPEC time, delta;
	int    retVal = FALSE;

	pThrottle->transitionFlag = FALSE;					// reset the transistion flag
	time = GetCurrentTime();
	delta = DeltaTime(pThrottle->prevTimeStamp, time);
	if (DeltaTimeLessThan(delta, 60))					// less than a minute?
	{
		if (++(pThrottle->count) > 9)
		{
			if (pThrottle->count > 59)							// let one of every 50 missed log entries through
			{
				pThrottle->missedCount = pThrottle->count - 10;	// store the missed count
				pThrottle->transitionFlag = TRUE;				// we just transition from throttling to no throttling
				// reset the throttle count back to 9, so next time may transition again to throttling
				pThrottle->count = 9;
			}
			else
			{
				if (pThrottle->count == 10)					// This is the 11th entry
					pThrottle->transitionFlag = TRUE;		// we just transition from no throttling to throttling
				retVal = TRUE;
			}
		}
	}
	else	// over a minute has passed
	{
		if (pThrottle->count > 9)							// zero based
		{
			pThrottle->missedCount = pThrottle->count - 9;	// store the missed count
			pThrottle->transitionFlag = TRUE;				// we just transition from throttling to no throttling
		}
		// reset the throttle count
		pThrottle->count = 0;
	}
	pThrottle->prevTimeStamp = time;

	return retVal;
}

const char *pPreFormatStrDbg[] =
{
		"[EMERG] %s:%d:%s: ",
		"[ALERT] %s:%d:%s: ",
		"[CRIT]  %s:%d:%s: ",
		"[ERR]   %s:%d:%s: ",
		"[WARN]  %s:%d:%s: ",
		"[NOTICE]%s:%d:%s: ",
		"[INFO]  %s:%d:%s: ",
		"[DEBUG] %s:%d:%s: "
};

const char *pPreFormatStr[] =
{
		"[EMERG] %s: ",
		"[ALERT] %s: ",
		"[CRIT]  %s: ",
		"[ERR]   %s: ",
		"[WARN]  %s: ",
		"[NOTICE]%s: ",
		"[INFO]  %s: ",
		"[DEBUG] %s: "
};

void	_EchLog(unsigned int flag, int pri, const char *pFormat, ...)
{
	char buffer[BUFSIZE];
	va_list arglist;
	int option = LOG_CONS;

	if (flag & DEBUG_FLAG)
	{
		strcpy (buffer, pPreFormatStrDbg[pri]);
	}
	else
	{
		if ((flag & PRINT_FLAG) && pri != LOG_EMERG)	// LOG_EMERG by default already sent out to stdout
			option = LOG_PERROR;					// requested to also print the log to stderr
		strcpy (buffer, pPreFormatStr[pri]);
	}
	strcat (buffer, pFormat);
	pFormat = buffer;
	openlog (NULL, option, LOG_LOCAL1);
	va_start(arglist, pFormat);
	vsyslog(pri, pFormat, arglist);
	va_end(arglist);
}

