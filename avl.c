int max(int a, int b)
{
    return a > b ? a : b;
}
int max(int a, int b)
{
    return a > b ? a : b;
}

int est_eq(abint a)
{
    int eq=0;
    if(a->fg !=NULL) eq+=hauteur(a->fg);
    if(a->fd != NULL) eq-=hauteur(a->fd);
    a->eq=eq;
    return eq;
}
abint rotation_droite(abint a)
{
    abint a1=a->fg;
    a->fg=a1->fd;
    a1->fd=a;
    return a1;
}


abint rotation_gauche(abint a)
{
    abint a1=NULL;
    a1=a->fg;
    a->fg=a->fd;
    a1->fd=a;
    return a1;
}

void rotation_gd(abint a)
{
    rotation_gauche(a);
    rotation_droite(a);
}
void rotation_dg(abint a)
{
    rotation_droite(a);
    rotation_gauche(a);
}

