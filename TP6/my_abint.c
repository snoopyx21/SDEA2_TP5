#include "my_abint.h"

abint enrac(int v, abint fdroit, abint fgauche)
{
    abint a = (abint) malloc(sizeof(noeud));
    a->val=v;
    a->fg=fgauche;
    a->fd=fdroit;
    return a;
}

abint filsg(abint a)
{
    return a->fg;
}

abint filsd(abint a)
{
    return a->fd;
}

int racine(abint a)
{
    return a->val;
}

int vide(abint a)
{
    if ((a->fd==NULL) && (a->fg==NULL)) return 1;
    return 0;
}


int appart(abint a, int v)
{
    if (a == NULL) return 0;
    return (a->val==v) ? 1 : ((v < a->val) ? appart(a->fg,v) : appart(a->fd,v));
}
int trier_fg(abint a, int v)
{    
    if (a == NULL) return 1;
    return (a->val > v) ? 0 : trier_fg(a->fg,v) && trier_fg(a->fd,v);
}
int trier_fd(abint a, int v)
{    
    if (a == NULL) return 1;
    return (a->val < v) ? 0 : trier_fd(a->fg,v) && trier_fd(a->fd,v);
}
int vide_racine(abint a)
{
    if (a==NULL) return 1;
    else return 0;
}
int trier(abint a)
{
    if(vide_racine(a)==1) return 1;
    if(trier_fg(a->fg,a->val) && trier_fd(a->fd,a->val)) return trier(a->fg) && trier(a->fg);
    else return 0;
}

void liberer_arbre(abint a)
{
    if(! vide_racine(a))
    {
        liberer_arbre(filsg(a));
        liberer_arbre(filsd(a));
        free(a);
    }
}

void affiche_arbre2(abint a)
{
    if (a== NULL) return;
    affiche_arbre2(a->fg);
    if(a->fg != NULL) printf(" ; ");
    printf("%d", a->val);
    if (a->fd != NULL) printf(" ; ");
    affiche_arbre2(a->fd);
}
void affiche_arbre(abint a)
{
    affiche_arbre2(a);
    printf("\n");
}

abint inserer_feuille(abint a, int val)
{
    if (a==NULL) return enrac(val, NULL, NULL);
    if (appart(a,val) != 1)
    {
        if (a == NULL) return enrac(val, NULL, NULL);
        if (val < a->val) a->fg=inserer_feuille(a->fg,val);
        else 
        {
            if(val>a->val) a->fd=inserer_feuille(a->fd,val);
        }  
        deseq(a); 
    } 
    else printf("%d can't be insert, try again \n", val);   
    return a;
}

int hauteur(abint a)
{
    int hg;
    int hd;
    if(vide_racine(a)) return 0;
    else
    {
        hg=1+hauteur(filsg(a)); 
        hd=1+hauteur(filsd(a));
        return hg>hd ? hg : hd;
    }   
}

abint insertion_racine2(abint a, int val)
{
    if (a==NULL) return enrac(val, NULL,NULL);
    int val_racine=racine(a);
    abint a1=a->fg;
    abint a2=a->fd;
    free(a); //on supprime l'ancien arbre
             //inutile de liberer l'arbre dans le main

    if( val_racine > val)
    {   
        abint tmp=enrac(a1->fg->val,a1->fd,a1->fg);
        a=enrac( val, enrac(val_racine, a2, tmp->fd), tmp->fg);
        // a est un nouvel arbre
        free(tmp);
        return a;
    }
    else if( val_racine < val) 
    {
        abint tmp=enrac(a2->fg->val,a2->fd,a2->fg);
        a=enrac( val, tmp->fd, enrac(val_racine, tmp->fg, a1) );
        free(tmp);
        return a;
    }   
    return a; 
}


abint insertion_racine(abint a, int val)
{
    if (appart(a,val) !=1)
    {
        if(a->val == val) return a;
        a=insertion_racine2(a,val);
        deseq(a);
        return a;
    }
    else 
    {
        printf("%d can't be insert, try again \n",val);
        return a;
    }
}


abint oter_max(abint a, int * val)
{
    if(a==NULL) return a;
    if(a->fd ==NULL)
    {
        *val=racine(a);
        abint a1=a->fg;
        free(a);
        return a1;
    }
    else 
    {
        a->fd=oter_max(a->fd, val);
        return a;
    }
}

abint supprimer_feuille2(abint a, int val)
{
    if(vide_racine(a)) return a;
    int val_racine=racine(a);
    abint a1=filsg(a);
    abint a2=filsd(a);
    free(a); //on libere l'ancien arbre 
             //inutile de liberer l'arbre dans le main
    
    if( val == val_racine)
    {
        // cas ou on veut supprimer la racine
        if(a1 == NULL) return a2;
        if(a2 == NULL) return a1;
        a1=oter_max(a1,&val_racine);
        a=enrac(val_racine, a2, a1);
        return a;
    }
    
    if(val < val_racine) 
        return enrac(val_racine, a2 , supprimer_feuille2(a1, val));
    if(val > val_racine)
        return enrac(val_racine, supprimer_feuille2(a2, val), a1);
    return a;
}

abint supprimer_feuille(abint a, int val)
{
    if( appart(a, val)) 
    {    
        a=supprimer_feuille2(a, val);
        deseq(a);
        return a;
    }
    return a;
}

int deseq(abint a)
{
    if (a ==NULL) return 999; 
    int eq;
    eq=hauteur(a->fg) - hauteur(a->fd);
    a->eq=eq;
    deseq(a->fd);
    deseq(a->fg);
    return eq;
}
    

abint rotation_droite(abint a)
{
    if (a->fg ==NULL || a==NULL) return a;
    
    abint a1 = a;
    abint a2 = a->fg;
    abint a3 = a2->fd; 
    
    a2->fd = a1;
    a1->fg = a3;
    
    deseq(a2);
    return a2;  
}

abint rotation_gauche(abint a)
{
    if (a->fg ==NULL || a==NULL) return a;
    
    abint a1 = a;
    abint a2 = a->fd;
    abint a3 = a2->fg; 
    
    a2->fg = a1;
    a1->fd = a3;
    
    deseq(a2);
    return a2;
}

abint rotation_gd(abint a)
{
    if (a==NULL) return a;
    a->fg=rotation_gauche(a->fg);
    deseq(a);
    return rotation_droite(a);
}


abint rotation_dg(abint a)
{
    if(a==NULL) return a;
    a->fd=rotation_droite(a->fd);
    deseq(a);
    return rotation_gauche(a);
}


avl reeq(avl a)
{
    if (a==NULL) return a;    
    deseq(a); //mise a jour de l'équilibrage 
    if ((-2 < a->eq) &&  (2 > a->eq) ) return a;
    if (a->eq >= 2)
    {
        if ((a->fg != NULL) && (a->fg->eq > 0)) a=rotation_droite(a);
        else if ((a->fg !=NULL) && (a->fg->eq < 0)) a=rotation_gd(a);
    }
    else if (a->eq <= -2)
    {
        if ((a->fd != NULL) && (a->fd->eq > 0)) a=rotation_gauche(a);
        else if((a->fd != NULL) && (a->fd->eq < 0)) a=rotation_gd(a);
    }
    return a;
}


avl inserer_feuille_avl(avl a, int val)
{
    if (a==NULL) return enrac(val,NULL,NULL);
    if (a->eq >2 || a->eq < -2) 
        printf("arbre not avl, %d can't be insert, try again \n", val);
    if(appart(a, val)) 
    {
        printf("%d can't be insert, try again \n", val);
        return a;
    }

    int val_racine=racine(a);
    if (val <  val_racine)
    {
        a->fg=inserer_feuille_avl(a->fg, val);
        a=reeq(a);
        return a;
    }
    else if (val > val_racine)
    {
        a->fd=inserer_feuille_avl(a->fd, val);
        a=reeq(a);
        return a;
    }
    else return a;

}


avl supprimer_avl(avl a, int val)
{
    if (a==NULL) return a;
    if (!appart(a, val)) 
    {
        printf("%d don't exist, try again \n", val);
        return a;
    }

    int val_racine=racine(a);
    avl a1= a->fg;
    avl a2= a->fd;
    free(a);

    if (val_racine == val)
    {
        if (a1 ==NULL) return a2;
        if (a2 == NULL) return a1;
        
        a1=oter_max(a1, &val_racine);
        a=enrac(val_racine, a2, a1);
        a=reeq(a);
        deseq(a);
        return a;
    }
    else if (val_racine > val) return reeq( enrac( val_racine, a2, supprimer_avl(a1, val)));
    else if (val_racine < val) return reeq( enrac( val_racine, supprimer_avl(a2, val), a1));
    else return a;
}


// fonction permettant d'afficher un arbre avec son arborescene complète
void node_print(abint a, int current_level, int max_level)
{
    int i;
    if (!vide_racine(a))
    {
        node_print(filsd(a), current_level + 1, max_level);
        for (i = 0; i < current_level; i++) 
        {
            printf("    ");
        }
        printf("%d\n", racine(a));
        node_print(filsg(a), current_level + 1, max_level);
    } 
    else 
    {
        if (current_level < max_level) 
        {
            node_print(NULL, current_level + 1, max_level);
            for (i = 0; i < current_level; i++) 
            {
                printf("    ");
            }
            printf("..\n");
            node_print(NULL, current_level + 1, max_level);
        }
    }
}
void avl_print(abint a)
{
    printf("Display tree :\n");
    node_print(a, 0, hauteur(a));
    printf("\n\n");
} 


