#include <stdlib.h>
#include <stdio.h>

typedef struct s_noeudt {
    int val;
    int eq;
    struct s_noeudt* fg;
    struct s_noeudt* fd;
} noeud,*abint,*avl;

abint enrac(int v, abint fdroit, abint fgauche);
abint filsg(abint a);
abint filsd(abint a);
int racine(abint a);
int vide(abint a);
int appart(abint a, int v);

int trier_fg(abint a, int v);
int trier_fd(abint a, int v);
int trier(abint a);
int vide_racine(abint a);

void affiche_arbre2(abint a);
void affiche_arbre(abint a);
void node_print(abint a, int current_level, int max_level);
void avl_print(abint a);

abint supprimer_feuille2(abint a, int val);
abint supprimer_feuille(abint a, int val);
abint inserer_feuille(abint a, int val);
int hauteur(abint a);
abint insertion_racine2(abint a, int val);
abint insertion_racine(abint a, int val);
abint oter_max(abint a, int * val);
int deseq(abint a);
int val_max(abint a);

abint rotation_droite(abint a);
abint rotation_gauche(abint a);
abint rotation_dg(abint a);
abint rotation_gd(abint a);

avl reeq(avl a);
avl inserer_feuille_avl(avl a, int val);
avl supprimer_avl(avl a, int val);

void liberer_arbre(abint a);
