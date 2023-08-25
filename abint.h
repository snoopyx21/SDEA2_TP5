#include <stdlib.h>
#include <stdio.h>


#ifndef __ABINT_H_
#define __ABINT_H_


typedef struct s_noeudt {
    int val;
    int eq;
    struct s_noeudt *fg,*fd;
    } noeud,*abint,*avl;

//int hauteur(abint a);

//int deseq(abint a);

abint enrac( abint fig,abint fid, int v);

abint filsg(abint a);

abint filsd(abint a);

int racine(abint a);

int vide(abint a);

int appart(abint a, int v);

//int trierfg(abint a, int v);

//int trierfd(abint a, int v);

int trier(abint a);

//void affichecroissantaux(abint a);

void affichecroissant(abint a);

//void majeq(abint a);

//abint insfaux(abint a, int v);

abint insf(abint a, int v);

//abint insraux(abint a, int v);

abint insr(abint a,int v);

//abint maxoter(abint a, int *r);

//abint supeaux(abint a, int v);

abint supe(abint a, int v);

abint rd(abint a);

abint rg(abint a);

abint rgd(abint a);

abint rdg(abint a);

int isavl(avl a);

//avl reeq(abint a);

//avl avl_insfaux(avl a, int v);

avl avl_insf(avl a, int v);

//avl avl_maxoter(avl a, int *r);

//avl avl_supeaux(avl a, int v);

avl avl_supe(avl a, int v);

abint copyarbre(abint a);

void free_abint(abint a);

//void node_print(abint a, int current_level, int max_level);

void print(abint a);

#endif