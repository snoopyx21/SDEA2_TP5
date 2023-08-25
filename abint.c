#include "abint.h"

int hauteur(abint a)
{
    if(a==NULL)
        return 0;
    if(a->fg==NULL && a->fd==NULL)
        return 1;
    int t1,t2;
    t1=hauteur(a->fg);
    t2=hauteur(a->fd);
    return (t1 > t2) ? t1+1 : t2+1;
}

int deseq(abint a)
{
    return hauteur(a->fg)-hauteur(a->fd);
}

abint enrac( abint fig,abint fid, int v)
{
    abint r =(abint)malloc(sizeof(struct s_noeudt));
    r->val=v;
    r->fg=fig;
    r->fd=fid;
    r->eq=deseq(r);
    return r;
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
    return (a==NULL);
}

int appart(abint a, int v)
{
    if (a == NULL)
        return 0;
    return (a->val==v) ? 1 : ((v<a->val) ? appart(a->fg,v) : appart(a->fd,v));
}

int trierfg(abint a, int v)
{    
    if (a == NULL)
        return 1;
    return (a->val > v) ? 0 : trierfg(a->fg,v) && trierfg(a->fd,v);
}

int trierfd(abint a, int v)
{    
    if (a == NULL)
        return 1;
    return (a->val < v) ? 0 : trierfd(a->fg,v) && trierfd(a->fd,v);
}


int trier(abint a)
{
    if(a==NULL)
        return 1;
    if(trierfg(a->fg,a->val) && trierfd(a->fd,a->val))
        return trier(a->fg) && trier(a->fd);
    else
        return 0;
}

void affichecroissantaux(abint a)
{ 
    if(a==NULL)
        return;
    affichecroissantaux(a->fg);
    printf("%d ", a->val);
    affichecroissantaux(a->fd);
    return;
}

void affichecroissant(abint a)
{
    printf("Les valeurs de l'arbre dans l'ordre croissant sont :\n");
    affichecroissantaux(a);
    printf("\n");
}

void majeq(abint a)
{
    if(!vide(a))
    {
        a->eq=deseq(a);
        majeq(a->fg);
        majeq(a->fd);
    }
    return;
}

abint insfaux(abint a, int v)
{
    if(a==NULL)
        return enrac(NULL,NULL,v);
    if (a->val<v)
        a->fd=insfaux(a->fd,v);
    else
        a->fg=insfaux(a->fg,v);
    return a;
}

abint insf(abint a, int v)
{
    if(appart(a,v))
        return a;
    a=insfaux(a,v);
    majeq(a);
    return a;
}

abint insraux(abint a, int v)
{
    if(a==NULL)
        return enrac(NULL,NULL,v);
    int r =racine(a);
    abint g=a->fg;
    abint d=a->fd;
    free(a);
    if(v < r)
    {
        abint b=insraux(g,v);
        a=enrac(b->fg,enrac(b->fd,d,r),v);
        free(b);
        return a;
    }
    else
    {
        abint b=insraux(d,v);
        a=enrac(enrac(g,b->fg,r),b->fd,v);
        free(b);
        return a;
    }
}

abint insr(abint a,int v)
{
    if(appart(a,v))
        return a;
    a=insraux(a,v);
    majeq(a);
    return a;
}

abint maxoter(abint a, int *r)
{
    if(a==NULL)
        return a;
    if(a->fd==NULL)
    {
        *r=racine(a);
        abint b=a->fg;
        free(a);
        return b;
    }
    else
    { 
        a->fd=maxoter(a->fd,r);
        return a;
    }
}

abint supeaux(abint a, int v)
{
    if(vide(a))
        return a;
    int r=racine(a);
    abint g=a->fg;
    abint d=a->fd;
    free(a);
    if(r==v)
    {
        if(g==NULL)
            return d;
        if(d==NULL)
            return g;
        g=maxoter(g,&r);
        a=enrac(g,d,r);
        return a;
    }
    if(v<r)
        return enrac(supeaux(g,v),d,r);
    return enrac(g,supeaux(d,v),r);
}

abint supe(abint a, int v)
{
    if(!appart(a,v))
        return a;
    a=supeaux(a,v);
    majeq(a);
    return a;
}

abint rd(abint a)
{
    if(a==NULL)
        return a;
    if(a->fg==NULL)
        return a;
    abint d=a;
    abint r=a->fg;
    abint dg=r->fd;
    r->fd=d;
    d->fg=dg;
    majeq(r);
    return r;
}

abint rg(abint a)
{
    if(a==NULL)
        return a;
    if(a->fd==NULL)
        return a;
    abint g=a;
    abint r=a->fd;
    abint gd=r->fg;
    r->fg=g;
    g->fd=gd;
    majeq(r);
    return r;
}

abint rgd(abint a)
{
    if(a==NULL)
        return NULL;
    a->fg=rg(a->fg);
    a=rd(a);
    majeq(a);
    return a;
}

abint rdg(abint a)
{
    if(a==NULL)
        return NULL;
    a->fd=rd(a->fd);
    a=rg(a);
    majeq(a);
    return a;
}

int isavl(avl a)
{
    if(a==NULL)
        return 1;
    if(a->eq > 2 || a->eq < -2)
        return 0;
    else
        return isavl(a->fg) && isavl(a->fd);
}

avl reeq(abint a)
{

    if(a==NULL)
        return a;
    a->eq=deseq(a);
    if(a->eq < 2 && a->eq >-2)
        return a;
    if(a->eq >= 2)
    {
        if(a->fg->eq==1)
            a=rd(a);
        else if (a->fg->eq==-1)
            a=rgd(a);
    }
    else if(a->eq <= -2)  
    {
        if(a->fd->eq==1)
            a=rdg(a);
        else if (a->fd->eq==-1)
            a=rg(a);
    }  
    return a;
}

avl avl_insfaux(avl a, int v)
{
    if (a==NULL)
        return enrac(NULL,NULL,v);
    if (v < racine(a))
    {
        a->fg=avl_insfaux(a->fg,v);
        a=reeq(a);
        return a;
    }
    else
    {
        a->fd=avl_insfaux(a->fd,v);
        a=reeq(a);
        return a;
    }

}
avl avl_insf(avl a, int v)
{
    if(appart(a,v))
        return a;
    if(!isavl(a))
    {
        printf("Arbre n'est pas un avl: pas d'insertion\n");
        return a;
    }
    
    a=avl_insfaux(a,v);
    return a;
}

avl avl_maxoter(avl a, int *r)
{
    if(a==NULL)
        return a;
    if(a->fd==NULL)
    {
        *r=racine(a);
        avl b=a->fg;
        free(a);
        return b;
    }
    else
    { 
        a->fd=avl_maxoter(a->fd,r);
        a=reeq(a);
        return a;
    }
}


avl avl_supeaux(avl a, int v)
{
    if(vide(a))
        return a;
    int r=racine(a);
    avl g=a->fg;
    avl d=a->fd;
    free(a);
    if(r==v)
    {
        if(g==NULL)
            return d;
        if(d==NULL)
            return g;
        g=avl_maxoter(g,&r);
        a=enrac(g,d,r);
        a=reeq(a);
        return a;
    }
    if(v<r)
        return reeq(enrac(avl_supeaux(g,v),d,r));
    return reeq(enrac(g,avl_supeaux(d,v),r));
}

avl avl_supe(avl a, int v)
{
    if(!appart(a,v))
        return a;
    a=avl_supeaux(a,v);
    majeq(a);
    return a;
}

abint copyarbre(abint a)
{
    if(vide(a))
        return a;
    abint b=enrac(NULL,NULL,a->val);
    b->eq=a->eq;
    b->fg=copyarbre(a->fg);
    b->fd=copyarbre(a->fd);
    return b;
}

void free_abint(abint a)
{
    if(!vide(a))
    {
        free_abint(a->fg);
        free_abint(a->fd);
        free(a);
    }
}

void node_print(abint a, int current_level, int max_level)
{
  int i;
  if (!vide(a)){
    node_print(filsd(a), current_level + 1, max_level);
    for (i = 0; i < current_level; i++) {
      printf("    ");
    }
    printf("%d(%d)\n", racine(a),a->eq);
    node_print(filsg(a), current_level + 1, max_level);
  } else {
    if (current_level < max_level) {
      node_print(NULL, current_level + 1, max_level);
      for (i = 0; i < current_level; i++) {
        printf("    ");
      }
      printf("..\n");
      node_print(NULL, current_level + 1, max_level);
    }
  }
}


void print(abint a)
{
  printf("display tree :\n");
  node_print(a, 0, hauteur(a));
  printf("\n\n");
}