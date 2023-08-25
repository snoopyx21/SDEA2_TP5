#include "abint.h"

/*
typedef struct s_noeud { 
	T val; 
	int eq;
	struct s_noeud *fg;
	struct s_noeud *fd; 
} noeud, *avl;  
*/

avl enracinement(T val)
{
	avl a=(avl)malloc(sizeof(noeud));
	a->val=val;
	a->eq=0;
	a->fg=NULL;
	a->fd=NULL;
	return a;
}

avl filsG(avl a)
{
	return a->fg;
}

avl filsD(avl a)
{
	return a->fd;
}

avl vide()
{
	return NULL;
}

int isVide(avl a)
{
	return a==NULL ? 1 : 0;
}

T racine(avl a)
{
	return a->val;
}


int valIn(avl n, T val)
{
	if(n==NULL)
		return 0;
	if(n->val==val)
		return 1;
	if(n->val>val)
		valIn(n->fg,val);
	else
		valIn(n->fd,val);
	return 0;
}

int isTrier(avl a)
{
	if(a==NULL)
		return 1;
	if(trierFilsG(a->fg, a->val)&&trierFilsD(a->fd, a->val))
		return isTrier(a->fg)&&isTrier(a->fd);
	else
		return 0;

}

int trierFilsG(avl a, T val)
{
	if(a==NULL)
		return 1;
	if(a->val > val)
		return 0;
	return trierFilsG(a->fg,val)&&trierFilsG(a->fd,val);
}

int trierFilsD(avl a, T val)
{
	if(a==NULL)
		return 1;
	if(a->val < val)
		return 0;
	return trierFilsD(a->fg,val)&&trierFilsD(a->fd,val);
}

void printavl(avl a)
{
	if(a->fg!=NULL)
		printavl(a->fg);
	printf("%d ",a->val);
	if(a->fd!=NULL)
		printavl(a->fd);
}

avl insFeuille(avl ar, T val)
{
	if (ar==NULL)
		return enracinement(val);
	avl a = ar;
	while(a->val!=val)
	{
		if(a->val>val)
		{
			if(a->fg==NULL)
			{
				a->fg=enracinement(val);
				a->eq=deseq(a);
			}
			else
				a=a->fg;
		}
		else
		{
			if(a->fd==NULL)
			{
				a->fd=enracinement(val);
				a->eq=deseq(a);
			}
			else
			a=a->fd;
		}
		if(a==NULL)
			return ar;
	}
	ar->eq=deseq(ar);
	return reeq(ar);
}

// avl insFeuille(avl a, T val)
// {
// 	if(a==NULL)
// 		return enracinement(val);
	
// 	if(a->val<val)
// 		a->fd=insFeuille(a->fd, val);
// 	else if(a->val<val)
// 		a->fg=insFeuille(a->fg, val);

// 	return a;
// }

// int hauteur(avl a)
// {
// 	if(a==NULL)
// 		return 0;
// 	else
// 		return (1+MAX(hauteur(a->fg),hauteur(a->fd)));
// }

int hauteur(avl a)
{
    int hg;
    int hd;
    if(isVide(a)) return 0;
    else
    {
        hg=1+hauteur(filsG(a)); 
        hd=1+hauteur(filsD(a));
        return hg>hd ? hg : hd;
    }   
}
void node_print(avl a, int current_level, int max_level)
{
  int i;
  if (!isVide(a)){
    node_print(filsD(a), current_level + 1, max_level);
    for (i = 0; i < current_level; i++) {
      printf("    ");
    }
    printf("%d\n", racine(a));
    node_print(filsG(a), current_level + 1, max_level);
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


void print(avl a)
{
  printf("Display tree :\n");
  node_print(a, 0, hauteur(a));
  printf("\n\n");
}


avl maxFils(avl a)
{
	if(a->fd==NULL)
		return a;
	else
		return maxFils(a->fd);
}

avl otermax(avl a)
{
	if(a->fd==NULL)
		return NULL;
	else
	{
		a->fd=otermax(a->fd);
		return a;
	}
}

avl sup(avl a, T val)
{
	if (a->val==val)
	{
		if (isVide(a->fg))
			return a->fd;
		else if (isVide(a->fd))
			return a->fg;
		else
		{
			avl b;
			b=maxFils(a->fg);
			b->fg=otermax(a->fg);
			b->fd=a->fd;
			b->eq=deseq(b);
			free(a);
			return b;
		}
	}
	else if (a->val > val)
	{
		a->fg=sup(a->fg, val);
		a->eq=deseq(a);
		return a;
	}
	else
	{	
		a->fd=sup(a->fd, val);
		a->eq=deseq(a);
		return a;
	}
}

avl rg(avl a)
{
	if(isVide(a->fg))
		return a;

	avl fg=a->fg;
	a->fg=fg->fd;
	fg->fd=a;
	a->eq=deseq(a);
	fg->eq=deseq(fg);
	return fg;
}

avl rd(avl a)
{
	if(isVide(a->fd))
		return a;
	
	avl fd=a->fd;
	a->fd=fd->fg;
	fd->fg=a;
	a->eq=deseq(a);
	fd->eq=deseq(fd);
	return fd;
}


avl rgd(avl a)
{
	//test something
	a->fg=rg(a->fg);
	return rd(a);
}

avl rdg(avl a)
{
	a->fd=rd(a->fd);
	return rg(a);
}

void liberer_arbre(avl a)
{
    if(! isVide(a))
    {
        liberer_arbre(filsG(a));
        liberer_arbre(filsD(a));
        free(a);
    }
    return;
}


// avl insRacine(avl a, T val)
// {
// 	if(a==NULL)
// 		return enracinement(val);
// 	if(a->val==val)
// 		return a;
// 	else if(a->val<val)
// 	{

// 		return
// 	}
// 	else
// 	{
// 		return
// 	}
// }

int deseq(avl a)
{
	return (hauteur(a->fg)-hauteur(a->fd)) ;
}


avl reeq(avl a)
{
	if (-2<deseq(a) && deseq(a)<2)
		return a;
	if (a->eq>1)
	{
		if (a->fg!=NULL && a->fg->eq>0)
			a=rg(a);
		else
			a=rdg(a);
	}
	else
	{
		if (a->fd!=NULL && a->fd->eq>0)
			a=rd(a);
		else
			a=rgd(a);
	}
	return a;
}