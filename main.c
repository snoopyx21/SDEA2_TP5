#include "abint.h"


int main(void)
{
	printf("##### FONCTION DE BASE D'UN ARBRE #######\n");
    abint a;
    abint g=NULL;
    abint d=NULL;
    a=enrac(g,d,25);
    a->fg=enrac(g,d,10);
    a->fg->fd=enrac(g,d,15);
    a->fg->fg=enrac(g,d,8);
    a->fd=enrac(g,d,35);
    a->fd->fg=enrac(g,d,28);
    a->fd->fd=enrac(g,d,36);
    print(a);
    int r = racine(a);
    printf("Racine :%d\n", r);
    if(appart(a,8))
    {
    	printf("8 appartient à l'arbre a (8 est dans l'arbre)\n");
    }
    else
    {
    	printf("8 n'appartient pas à l'arbre a (8 est dans l'arbre)\n");
    }
    if(appart(a,9))
    {
    	printf("9 appartient à l'arbre a (9 n'est pas dans l'arbre)\n");
    }
    else
    {
    	printf("9 n'appartient pas à l'arbre a (9 n'est pas dans l'arbre)\n");    
    }
    r=trier(a);
    if(r==1)
    {
        printf("Arbre trié\n");
    }
    else
    {
        printf("Arbre non trié\n\n");
    }
	printf("##### FONCTION D'AFFICHAGE CROISSANT DES VALEURS #######\n");    
    affichecroissant(a);
    printf("\n\n");
	printf("##### FONCTION D'INSERTION ET SUPPRESSION #######\n");
	printf("Insertion en feuille: 1, 51, 12, 18\n");
    a=insf(a,1);
    a=insf(a,51);
    a=insf(a,12);
    a=insf(a,18);
    printf("Insertion en racine: 14, 16, 17\n");
    a=insr(a,14);
    a=insr(a,16);
    a=insr(a,17);
    print(a);
    printf("Suppression: 8, 36, 17(racine)\n");
    a=supe(a,8);
    a=supe(a,36);
    a=supe(a,17);
    print(a);
	printf("##### FONCTION DE ROTATION #######\n");
	printf("Rotation droite\n");
    a=rd(a);
    print(a);
	printf("Rotation gauche\n");
    a=rg(a);
    print(a);
    abint b=copyarbre(a);
    printf("Test double-rotation sur nouvel arbre\n");
 	printf("(Premier utile pour les tests AVL)\n");
    b=insf(b,17);
    print(b);
    printf("Rotation droite gauche \n");
    b=rdg(b);
    print(b);
    printf("Rotation gauche droite \n");
    b=rgd(b);
    print(b);
    free_abint(b);
	printf("##### FONCTION D'INSERTION ET SUPPRESSION AVL #######\n");
	printf("Retour sur l'arbre original\n");
	print(a);    
    if(isavl(a))
    {
        printf("Arbre a est un avl\n");
    }
    else
    {
        printf("Arbre a n'est pas un avl\n");
    }
	printf("Insertion en feuille: 26, 52, 31, 13, 2\n");
    a=avl_insf(a,26);
    a=avl_insf(a,52);
    a=avl_insf(a,31);
    a=avl_insf(a,13);
    a=avl_insf(a,2);
    print(a);
	printf("Suppression: 51, 45(pas dans l'avl), 16(racine)\n");
    a=avl_supe(a,51);
    a=avl_supe(a,45);
    a=avl_supe(a,16);
    print(a);
    free_abint(a);
    return 0;
}
