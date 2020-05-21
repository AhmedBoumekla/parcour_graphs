#include <stdlib.h>
#include <stdio.h>

#include <string.h>
#include "graphe_parcours.h"
#include "graphe-4.h"
#include "parcours.h"
#include "conteneur_sommets.h"

int graphe_parcours_profondeur(graphe *g, graphe **arbo, int **suff, int *prio)
{
  /*La difference entre un parcours profondeur avec les autres c'est qu'on utilise une pile comme conteneur*/
  parcours *p = pc_init(g,cs_creer_pile(graphe_get_n(g)),prio);
  if(!p)
  {
	  return EXIT_FAILURE;
  }
  /*on parcours*/
  pc_parcourir(p);
  /*on récupére le resultats*/
  *arbo = p->arbo;
  p->arbo = NULL;
  /*on recupere le suffixe*/
  *suff = p->suffixe;
  free(p->distance);
  free(p->cfc);
  pc_detruire(p);
  return 0;
}

int graphe_parcours_largeur(graphe *g, graphe **arbo, int **suff, int *prio)
{
  /*Dans le parcours en largeur on utilise une file*/
    parcours *p = pc_init(g,cs_creer_file(graphe_get_n(g)),prio);
    /*si allocation mémoire échoué*/
    if(!p)
    {
	  	return EXIT_FAILURE;
    }
    /*On parcour puis recupere les resultats*/
    pc_parcourir(p);
    *arbo = p->arbo;
     p->arbo = NULL;
    *suff = p->suffixe;
    p->suffixe = NULL;
    free(p->distance);
    free(p->cfc);
    pc_detruire(p);
    return 0;
}

int graphe_parcours_larg_ou_prof(graphe *g, graphe **arbo, int **suff, int *prio)
{
  /*On utilise la structure pile_ou file*/
  parcours *p = pc_init(g,cs_creer_pile_ou_file(graphe_get_n(g)),prio);
  if(!p)
  {
	  return EXIT_FAILURE;
  }
    /*On parcour puis recupere les resultats*/
  pc_parcourir(p);
  *arbo = p->arbo;
  p->arbo = NULL;
  *suff = p->suffixe;
  p->suffixe = NULL;
  free(p->distance);
  free(p->cfc);
  pc_detruire(p);
  return 0;
}

int graphe_ordre_top(graphe *g, int **ordre_top)
{ 
  /*On veut obtenir l'ordre topologique  d'un parcour en profondreur*/
   parcours *p = pc_init(g,cs_creer_pile(graphe_get_n(g)),NULL);
  if(!p)
  {
    graphe_liberer(p->arbo);
    free(p->suffixe);
    pc_detruire(p);
	  return EXIT_FAILURE;
  }
  pc_parcourir(p);
  /*si le graphe est cyclique il n'y a pas d'ordre topologique*/
  if(p->arc_arriere==1)
  {
    *ordre_top=NULL;
    graphe_liberer(p->arbo);
    free(p->suffixe);
    free(p->distance);
    free(p->cfc);
    pc_detruire(p);
    return -2;
  } 
  /*Si le graphe est acyclique alors l'ordre topologique est l'inverse du suffixe*/
  int* ordre_topo = calloc(graphe_get_n(p->g),sizeof(int));
  int j =0;
  /*on inverse le suffixe pour obtenire l'ordre topologique*/
  for(int i = graphe_get_n(p->g)-1;i>=0;i--)
  {
    ordre_topo[i]= p->suffixe[j];
    j++;
  }
  *ordre_top=ordre_topo;
  ordre_topo = NULL;
  graphe_liberer(p->arbo);
  free(p->suffixe);
  /* on libere la mémoire*/
  free(p->distance);
  free(p->cfc);
  pc_detruire(p);
  return 0;
}  


/* on fait une fonction graphe inverser qui va nous aider pour trouve les composantes fortement connexe*/
graphe *graphe_inv(graphe *g){
  if(!g)
    return NULL;
  graphe *res = graphe_creer(graphe_get_n(g),graphe_est_or(g));
  if(!res)
    return NULL;
  msuc *m = NULL;
  for(int i = 0; i< graphe_get_n(g); i++)
  {
    m = g->tab_sucs[i];
    while(m != NULL)
    {
      graphe_ajouter_arc(res,msuc_sommet(m),i, msuc_valeur(m));
      m = m->suivant;
    }

  }   
  free(m);
  return res;

}



/*La fonction qui calcule les composante fortement connexe ne donne pas le bon resultats*/
int graphe_comp_fort_conn(graphe *g, int **reprs_cfc)
{
  if(g == NULL)
    return EXIT_FAILURE;
  /* declaration de la variable ordre topologique*/
  int *ordretop;
  /* Etape 1 : on recupere l'ordre topologique du graphe*/
  graphe_ordre_top(g,&ordretop);
  /* Etape 2 : On inverse le graphe */
  graphe *grapheInv = graphe_inv(g);
  parcours *p = pc_init(grapheInv,cs_creer_pile(graphe_get_n(g)),ordretop);
  free(ordretop);

  if(!p){
    
    graphe_liberer(p->arbo);
    free(p->suffixe);
    pc_detruire(p);
	  return EXIT_FAILURE;
  }

  /* Etape 3, on le parcours avec comme liste prio l'ordre topologique fait precedemment*/
  pc_parcourir(p);
  *reprs_cfc = p->cfc;
  p->cfc=NULL;
  graphe_liberer(grapheInv);
  graphe_liberer(p->arbo);
  free(p->suffixe);
  free(p->distance);
  free(p->cfc);
  pc_detruire(p);    
  return 0;

}

int *graphe_distances_depuis_sommet(graphe *g, int r)
{ /* Si g est null on arrete*/
  if(!g)
    return NULL;
  /*declaration de la variable qui prendra les resultats*/
  int *res;
  /*initialisation du parcours en largeur*/
  parcours *p = pc_init(g,cs_creer_file(graphe_get_n(g)),NULL);
  if(!p){
    graphe_liberer(p->arbo);
    free(p->cfc);
    free(p->distance);
    free(p->suffixe);
    pc_detruire(p);
    return NULL;
  }
  /*On parcour de depuis le sommet*/
  pc_parcourir_depuis_sommet(p,r);
  /* on recupere le champs distance de notre parcours*/
  res = p->distance;
  /*On libere toutes la memoire*/
  graphe_liberer(p->arbo);
  free(p->suffixe);
  free(p->cfc);
  pc_detruire(p);
  return res;
}

/*Fonction pour chercher la valeur maximal d'un tableau*/
int max_val(int *tab, int n){
  int max = tab[0];
  for(int i = 1; i< n;i++){
    if(tab[i]>max)
      max = tab[i];
  }
  return max;
}

/*Fonction dist_inf*/
int is_dist_inf(int *tab, int n){
  for(int i = 0; i < n; i++){
    if(tab[i] == DIST_INF)
      return 1;
  }
  return 0;
}

/*Fonction qui calcule le diametre*/
int graphe_diametre(graphe *g)
{
  int n = graphe_get_n(g);
  int *tab_disance_max = calloc(n,sizeof(int));
  int *tab_distance ;
  if(!tab_disance_max )
    return EXIT_FAILURE;
  for(int i =0; i < n; i++){
    tab_distance = graphe_distances_depuis_sommet(g,i);
    if(is_dist_inf(tab_distance, n)) // car le graphe n'est pas connexe 
      return -1;
    tab_disance_max[i] = max_val(tab_distance, n);
  }
  return max_val(tab_disance_max, n);
}

/*On sait que la compléxité d'un parcour est O(n + m) or dans le cas de diametre 
dans le pire des cas on repetera n parcours donc O(n*(n+m))*/
