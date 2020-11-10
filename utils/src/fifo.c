
#include "Fifo.h"

File fileVide() {
   File F;
   F = (File)malloc(sizeof(struct _file));
   if (F == NULL) printf("erreur allocation fileVide");
   F->longueur = 0;
   F->tete = F->queue = NULL;
   return(F);
}

int longueur(File F) {
   if (F == NULL)printf("file existe pas - longueur");
   return(F->longueur);
}

void enfiler(File F, typage element) {
   Cellule cellule;
   if (F == NULL) printf ("file existe pas - enfiler");

   cellule = (Cellule)malloc(sizeof(struct _cellule));
   if (cellule == NULL) printf("erreur allocation memoire - enfiler");
   cellule->element = element;
   cellule->suivant = NULL;
   if (longueur(F) == 0){
      F->tete = F->queue = cellule;
   }
   else {
      cellule->suivant=F->tete;
      F->tete = cellule;
   }
   ++(F->longueur);
}

typage tete(File F) {
   if (F == NULL || longueur(F) == 0) printf(" File existe pas - tete");
   return(F->tete->element);
}

void defiler(File F) {
   Cellule cellule;

   if (F == NULL || longueur(F) == 0)printf("File existe pas - defiler");
   cellule = F->tete;
   if (longueur(F) == 1){
      F->tete = F->queue = NULL;
   }
   else{
      F->tete = F->tete->suivant;
   }
   --(F->longueur);
   free(cellule);
}

typage defilement(File F) {
   Cellule cellule;
   typage element;
   if (F == NULL || longueur(F) == 0) printf("File existe pas - defilement");
   cellule = F->tete;
   element = cellule->element;
   if (longueur(F) == 1){
      F->tete = F->queue = NULL;
   }
   else{
      F->tete = F->tete->suivant;
   }
   free(cellule);
   --(F->longueur);
   return(element);
}


File copie(File F) {
   File G, H;
   Cellule cellule;

   if (F == NULL) printf("erreur copie");
   H = fileVide();
   cellule = F->tete;
   while (cellule != NULL) {
      enfiler(H, cellule->element);
      cellule = cellule->suivant;
   }
   G = fileVide();
   cellule = H->tete;
   while (cellule != NULL) {
      enfiler(G, cellule->element);
      cellule = cellule->suivant;
   }
   return(G);
}

void ecrireFile(File F) {
   Cellule cellule;

   if (F == NULL) printf("erreur ecrireFile");
   cellule = F->tete;
   while (cellule != NULL) {
      printf("%d ", cellule->element);
      cellule = cellule->suivant;
   }
   printf("\n");
}