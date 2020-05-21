#include <stdlib.h>
#include <stdio.h>
#include "graphe-4.h"
#include "parcours.h"
#include "conteneur_sommets.h"
#include <string.h> /* pour memcpy */


struct parcours *pc_init(graphe *g, conteneur_sommets *cs, int *prio)
{
	parcours *p= malloc(sizeof(parcours)); /*Allocation mémoire ppour le parcours*/
  p->g = g;/* Graphe a parcourir*/
  p->conteneur= cs;/*Conteneur pour parcourir*/
  if(prio ==NULL)
  {/*Si prio est null alors on creer prio*/
    p->prio= calloc(p->g->n,sizeof(int));
    for(int a = 0;a<p->g->n;a++)
    {
      p->prio[a]=a;
    }
  }
  else
  {
    p->prio = prio;
  }
  p->arbo = graphe_creer(graphe_get_n(p->g),graphe_est_or(p->g));/*allocation mémoire pour arbo*/
  p->est_visite = calloc(graphe_get_n(p->g),sizeof(int));/*allocation mémoire pour tableau est_visite*/
  p->est_explore= calloc(graphe_get_n(p->g),sizeof(int));/*allocation mémoire pour tableau est_exploré*/
  p->prefixe = calloc(graphe_get_n(p->g),sizeof(int));/*allocation mémoire pour tableau prefixe*/
  p->suffixe = calloc(graphe_get_n(p->g),sizeof(int));/*allocation mémoire pour tableau suffixe*/
  p->cfc = calloc(graphe_get_n(p->g),sizeof(int));/*allocation mémoire pour tableau fortement connexe*/
  p->distance = calloc(graphe_get_n(p->g),sizeof(int));/*allocation mémoire pour tableau des distances*/
  

  p->i =0;/*initialisation des variables indixe des tableau visite et exploire*/
  p->j=0;
  for(int i =0;i<p->g->n;i++)
  {
    /*initialisation des tableau est_visite et est_exploré a 0 et distance = DIST_INF*/
    p->est_visite[i]=0;
    p->est_explore[i]=0;
    p->distance[i]= -1;
  }
  /*initialisation des variables fini et arc_arriere */
  p->est_fini = 0;
  p->arc_arriere=0;
  return p;
  
}

void pc_detruire(struct parcours *p)
{
  /* liberation mémoire des champs qui ne sont pas liberer par les test*/
  cs_detruire(p->conteneur);
  free(p->prio);
  free(p->est_visite);
  free(p->est_explore);
  free(p->prefixe);
  free(p);
}

int pc_choisir_racine(struct parcours *p)
{
  /*choisir dans prio , la prochaine qui n'est pas dans prefixe*/
  for(int i =0;i<(p->g->n);i++)
  {
    if(!pc_est_visite(p,p->prio[i]))
    {
      return p->prio[i];
    }
  }
  return -2;
}    
  

int pc_est_fini(struct parcours *p)
{
  if(p->est_fini == graphe_get_n(p->g)) /*le parcour est fini si tout les sommet sont exploré*/
    return 1;
  
  return 0;
}

void pc_marquer_comme_visite(struct parcours *p, int sommet)
{
  p->est_visite[sommet]= 1; /*On met a 1 pour dire que le sommet est visité*/
}

void pc_marquer_comme_visite_depuis(struct parcours *p, int sommet, int depuis)
{
  /*non utilisé*/
}

void pc_marquer_comme_explore(struct parcours *p, int sommet)
{
     p->est_explore[sommet]=1;/*On met a 1 le sommet exploré*/
     p->est_fini++;/*On incremente une variable permettant de savoir si le parcour est fini par rapport au nombre de sommet exploré*/
}

int pc_conteneur_est_vide(struct parcours *p) 
{
  return cs_est_vide(p->conteneur);/*on appelle la fonction dans conteneur sommets qui permet de le faire*/
}

void pc_ajouter_dans_conteneur(struct parcours *p, int sommet) /* on appelle simplement la fonction du conteneur*/
{
  cs_ajouter(p->conteneur,sommet);
}

void pc_supprimer_du_conteneur(struct parcours *p) /*On appelle la fonction correspondant pour le conteneur du parcours*/
{
  cs_supprimer(p->conteneur);
}

int pc_choisir_dans_conteneur(struct parcours *p)/*On appelle la fonction correspondante dans la structure conteneur*/
{
  return cs_choisir(p->conteneur);
}

msuc *pc_prochain_msuc(struct parcours *p, int sommet)
{
  return p->g->tab_sucs[sommet]->suivant; /*On renvoie le premier voisin d'un sommet*/
}

int pc_est_visite(struct parcours *p, int sommet)/* on veut savoir qui si un sommet est visité*/
{
    return p->est_visite[sommet];
}

void pc_parcourir_depuis_sommet(struct parcours *p, int r)
{
  int racine,choix;/*declaration de la racine, puis du sommet courant*/
  msuc *m;/*variable pour parcour des voisins*/
  racine = r;/*enlever go to , puis les choisir*/
  pc_ajouter_dans_conteneur(p,racine);/*ajouter r au conteneur*/
  pc_marquer_comme_visite(p,racine);/*marquer r comme visité*/
  p->prefixe[p->i]= racine;/*r visité donc on l'ajoute dans le prefixe*/
  (p->i)++;/*incrementation d'une variable dans le parcour pour savoir on nous en sommes*/
  p->distance[racine] = 0;

  while(!pc_conteneur_est_vide(p)){/*Tant que le conteneur n’est pas vide*/
    expr1 : choix = (pc_choisir_dans_conteneur(p));/*choisir un sommet v dans le conteneur*/ 
    p->cfc[choix]=racine;/*on rempli les representants pour les composante fortement connexe*/
      for (m = graphe_get_prem_msuc(p->g, choix); m!=NULL; m = msuc_suivant(m)) 
      { /*Si v a des successeurs non visités, alors*/
        /*On verifie si msuc_sommet(m)) est deja dans le conteneur pour detecter un cycle*/
        if(pc_est_visite(p,msuc_sommet(m)) && !p->est_explore[msuc_sommet(m)])
        {
              p->arc_arriere=1;/*Variable 0 ou 1 pour savoir si il y a un arc arriere*/
        }
        /*On rentre dans ces voisins non visité pour le parcours*/
        if(!pc_est_visite(p,msuc_sommet(m)))
        {
          pc_ajouter_dans_conteneur(p,msuc_sommet(m));/*ajouter w au conteneur*/
          pc_marquer_comme_visite(p,msuc_sommet(m));/*marquer w comme visité*/
          p->prefixe[p->i]=msuc_sommet(m);/*msuc_sommet visité donc on l'ajoute dans le prefixe*/
          (p->i)++;
          p->distance[msuc_sommet(m)] = p->distance[choix] +msuc_valeur(m);
          graphe_ajouter_arc(p->arbo,choix,msuc_sommet(m),msuc_valeur(m));/*ajouter l'arc dans lequel on vient de parcourir*/
          goto expr1; /*choisir un tel succeseur*/
        }
      }
         /* Sinon */
      pc_marquer_comme_explore(p,choix);/*marquer v comme exploré*/
      p->suffixe[p->j]=choix;/*exploré donc ajout au suffixe*/
      (p->j)++;
       pc_supprimer_du_conteneur(p);
          /*enlever v du conteneur*/
  }
}  

void pc_parcourir(struct parcours *p)
{
  /*tant que le parcour n'est pas fini*/
  while(pc_est_fini(p) == 0)
  {
    /*on choisi la racine*/
    int racine = pc_choisir_racine(p);
    /*On verifie si arc arriere*/
    if(pc_est_visite(p,racine) && !p->est_explore[racine])
    {
      p->arc_arriere=1;
    }
    /*puis on parcour depuis la racine choisi*/
    pc_parcourir_depuis_sommet(p,pc_choisir_racine(p));
  }
}

