/*
 * Cellule.h
 *
 *  Created on: 3 sept. 2020
 *      Author: occitaline
 */

#ifndef _CELLULE_H_
#define _CELLULE_H_


typedef int typage;

struct _cellule {
   typage element;
   struct _cellule *suivant;
};

typedef struct _cellule* Cellule;



#endif /* PROJETS_NODECOMINTERTHREADS_CELLULE_H_ */
