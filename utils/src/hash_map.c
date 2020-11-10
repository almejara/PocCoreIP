/**
 * @file hash_map.c
 * @author Alejandro Mejia (alejandro.mejia@groupe-arcom.com)
 * @brief 
 * @version 0.1
 * @date 07-03-2019
 * 
 * @copyright Copyright Arcom 2019
 * 
 */
#include <stdio.h>   
#include <stdlib.h>  
#include <string.h>  

#include "hash_map.h"

/* Global variables -------------------------------------------*/

/* Private defines --------------------------------------------*/

/* Private typedef --------------------------------------------*/

/* Private macros ---------------------------------------------*/

/* Private variables ------------------------------------------*/

/* Private function prototype ---------------------------------*/

/**
 * @brief 
 * 
 * @param rows_map 
 * @param row_id 
 * @param value 
 */
void add_row(sqlite_row_map_t **rows_map,int row_id, char *value)
{
    sqlite_row_map_t *s;

    HASH_FIND_INT(*rows_map, &row_id, s);  /* id already in the hash? */
    if (s==NULL) {
        s = (sqlite_row_map_t*)malloc(sizeof(sqlite_row_map_t));
        s->id = row_id;
        HASH_ADD_INT( *rows_map, id, s );  /* id: name of key field */
    }
    strcpy(s->value, value);
}

/**
 * @brief 
 * 
 * @param row_id 
 * @return sqlite_row_map_t* 
 */
sqlite_row_map_t *find_row(sqlite_row_map_t **rows_map,int row_id)
{
    sqlite_row_map_t *s;

    HASH_FIND_INT( *rows_map, &row_id, s );  /* s: output pointer */
    return s;
}

/**
 * @brief 
 * 
 * @param rows_map 
 * @param user 
 */
void delete_row(sqlite_row_map_t **rows_map,sqlite_row_map_t *user)
{
    HASH_DEL( *rows_map, user);  /* user: pointer to deletee */
    free(user);
}

/**
 * @brief 
 * 
 * @param rows_map 
 */
void delete_all(sqlite_row_map_t **rows_map)
{
    sqlite_row_map_t *current_user, *tmp;

    HASH_ITER(hh, *rows_map, current_user, tmp) {
        HASH_DEL(*rows_map,current_user);  /* delete it (users advances to next) */
        free(current_user);            /* free it */
    }
}

/**
 * @brief 
 * 
 * @param rows_map 
 */
void print_rows(sqlite_row_map_t **rows_map)
{
    sqlite_row_map_t *s;

    for(s=*rows_map; s != NULL; s=(sqlite_row_map_t*)(s->hh.next)) {
        fprintf(stderr,"row id %d: value %s\n", s->id, s->value);
    }
}

/**
 * @brief 
 * 
 * @param rows_map 
 * @return uint16_t 
 */
uint16_t rows_length(sqlite_row_map_t **rows_map)
{
     return HASH_COUNT(*rows_map);

}