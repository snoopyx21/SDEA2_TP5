#include <stdio.h>
#include <stdlib.h>
#include "my_abint.h"

int main(void)
{
    // partie arbre trié normal 
    abint a;
    a=enrac(7, NULL, NULL);
    a->fg=enrac(2, NULL, NULL);
    a->fd=enrac(14, NULL, NULL);
    // test insertion
    inserer_feuille(a,9);
    inserer_feuille(a,4);
    inserer_feuille(a,25);
    inserer_feuille(a,8);
    inserer_feuille(a,5);
    inserer_feuille(a,2); // 2 ne peut pas être inséré, déjà inséré
    
    avl_print(a);
    affiche_arbre(a);

    // test suppression
    a=supprimer_feuille(a,7); // suppression de la racine
    avl_print(a);
    
    a=supprimer_feuille(a,5); 
    avl_print(a);

    a=insertion_racine(a, 5); // insertion de 5 en racine
    avl_print(a);
    
    // test des rotations
    a=rotation_gauche(a);                           
    avl_print(a);
    a=rotation_droite(a);
    avl_print(a);
    a=rotation_gd(a);                           
    avl_print(a);
    a=rotation_dg(a);
    avl_print(a);
    
    // test si l'arbre est bien trié    
    if (trier(a) == 1)     
        affiche_arbre(a);

    liberer_arbre(a); 
     
 
    // partie AVL
    avl b;
   
    b=enrac(6, NULL, NULL);
    b->fg=enrac(3,NULL, NULL);
    b->fd=enrac(14,NULL, NULL);
    // test insertion
    inserer_feuille_avl(b,9);
    deseq(b);
    inserer_feuille_avl(b,4);
    deseq(b);
    inserer_feuille_avl(b,2);
    deseq(b);
    inserer_feuille_avl(b,8);
    deseq(b);
    inserer_feuille_avl(b,5);
    deseq(b);
    inserer_feuille_avl(b,1);
    deseq(b);
    inserer_feuille_avl(b,2); // déjà inséré donc impossible 
    avl_print(b);
    affiche_arbre(b);
    
    // test suppression
    b=supprimer_avl(b,6); // suppresion de la racine
    deseq(b);
    avl_print(b);
    
    b=supprimer_avl(b, 8);
    deseq(b);
    avl_print(b);
   
    b=supprimer_avl(b, 1);
    deseq(b);
    avl_print(b);
 
    // test si l'arbre b est trié
    if ( trier(b) == 1)
        affiche_arbre(b); 

    printf("equilibrage = %d \n",b->eq);
    
    liberer_arbre(b);
    
    return 0;
}

