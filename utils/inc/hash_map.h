/**
 * @file hash_map.h
 * @author Alejandro Mejia (alejandro.mejia@groupe-arcom.com)
 * @brief hash use for reading rows from sqlite data base
 * @version 0.1
 * @date 07-03-2019
 * 
 * @copyright Copyright Arcom 2019
 * 
 */

#ifndef HASH_MAP_H /** Prevent multiple inclusions **/
#define HASH_MAP_H

#include <stdint.h>
#include "uthash.h"

#define TEXT_SIZE   10   /*Form the moment the values retrieve in arcom data base are the numerical values (column "value" in tables)*/

/* Exported types---------------------------------------------*/
typedef struct _sqlite_res_map {
    int32_t  id;                    /* key */
    char     value[TEXT_SIZE];
    UT_hash_handle hh;             /* makes this structure hashable */
}sqlite_row_map_t;

/* Exported constants---------------------------------------------*/


/** Exported functions---------------------------------------------*/
void add_row(sqlite_row_map_t **rows_map,int32_t row_id, char *value);
sqlite_row_map_t *find_row(sqlite_row_map_t **rows_map,int32_t row_id);
void delete_row(sqlite_row_map_t **rows_map,sqlite_row_map_t *user);
void delete_all(sqlite_row_map_t **rows_map);
uint16_t rows_length(sqlite_row_map_t **rows_map);
void print_rows(sqlite_row_map_t **rows_map);


#endif /*HASH_MAP_H*/






