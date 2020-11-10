/**
 * @file logger.h
 * @author Alejandro Mejia (alejandro.mejia@groupe-arcom.com)
 * @brief 
 * @version 0.1
 * @date 04-02-2019
 * 
 * @copyright Copyright Arcom 2019
 * 
 */

#ifndef LOGGER_H /** Prevent multiple inclusions **/
#define LOGGER_H

#include <stdint.h>
#include <pthread.h>

/**
 * \brief The maximum size of the log buffer.
*/
#define LOGGER_BUF_SIZE 4096
#define LOG(level, fmt, ...)  ar_log(level, fmt, ##__VA_ARGS__)


#define LOGGER_RET_OK 0
#define NULL_OR_INVALID_LOGGER_SINGLETON 800


/**
 * \brief Log message level enumeration.
**/
enum LogLevel {
	AR_TRACE, /**< Application execution tracing. **/
	AR_DEBUG, /**< Debug messages for development. **/
	AR_INFO,  /**< General information messages. **/
	AR_WARN,  /**< Warning messages. **/
	AR_ERROR, /**< Error messages. **/
	AR_FORCE, /**< TBD **/
	AR_AUDIT  /**< TBD **/
};

/**
 * \brief Signature for logging function to be called when twLog() is invoked.
 *
 * \param[in]     level         The ::LogLevel of the log message.
 * \param[in]     timestamp     The timestamp of the log message.
 * \param[in]     message       The log message text.
 *
 * \return Nothing.
*/
typedef void (*log_function) ( enum LogLevel level, const char * timestamp, const char * message);

/**
 * \brief ThingWorx Logger singleton structure definition.
*/
typedef struct ar_logger {
    enum LogLevel level;      /**< The ::LogLevel of the ::twLogger. **/
    log_function f;           /**< The log_function() associated with the ::twLogger. **/
	char isVerbose;           /**< If TRUE, verbose logging is enabled. **/
	char * buffer;            /**< A pointer to the ::twLogger's message buffer. **/
	pthread_mutex_t * mtx;    /**< A mutex associated with the ::twLogger. **/
} ar_logger;

/**
 * \brief Gets a pointer to the ::ar_logger singleton and creates a new one if
 * it hasn't been created already.
 *
 * \return A pointer to the new or existing ::ar_logger singleton.
*/
ar_logger * ar_logger_instance();

/**
 * \brief Frees all memory associated with the ::ar_logger singleton.
 *
 * \return #TW_OK if successful, positive integral on error code (see
 * twErrors.h) if an error was encountered.
*/
int ar_logger_delete();

/**
 * \brief Sets the ::twLogger#LogLevel of the ::twLogger singleton.
 *
 * \param[in]     level     The ::LogLevel to set the ::twLogger to.
 *
 * \return #TW_OK if successful, positive integral on error code (see
 * twErrors.h) if an error was encountered.
*/
int ar_logger_set_level(enum  LogLevel level);


/**
 * \brief Logs a message.
 *
 * \param[in]     level     The ::LogLevel of the message.
 * \param[in]     format    The format of the message.
 * \param[in]     ...       A va_list of messages to log.
 *
 * \return Nothing.
*/
void ar_log(enum LogLevel level, const char * format, ... );


#endif

