/**
 * \file graphe_parcours.h
 * \brief parcours spécialisés et applications de ces parcours pour un graphe
 * représenté par une liste de successeurs
 * \version 1
 * \date mer. 20 nov. 2019 11:35:37 CET
 * \authors Pierre Rousselin, Antoine Rozenknop, Sophie Toulouse
 */
#ifndef GRAPHE_PARCOURS_H
#define GRAPHE_PARCOURS_H

#define DIST_INF -1
#include "graphe-4.h"
/* Parcours spécialisés */

/**
 * \brief Parcourt le graphe en profondeur
 * \param g adresse d'un graphe à parcourir
 * \param arbo adresse de l'adresse de l'arborescence que le parcours va écrire
 * \param suff adresse du tableau contenant l'ordre suffixe que le parcours va
 * écrire
 * \param prio tableau de priorités pour le choix des *racines* du parcours ; si
 * ce paramètre vaut NULL, la priorité est celle par défaut : 0, 1, 2, ...
 * \return 0 en cas de succès, -1 en cas de problème d'allocation mémoire
 */
int graphe_parcours_profondeur(graphe *g, graphe **arbo, int **suff, int *prio);

/**
 * \brief Parcourt le graphe en largeur
 * \param g adresse d'un graphe à parcourir
 * \param arbo adresse de l'adresse de l'arborescence que le parcours va écrire
 * \param suff adresse du tableau contenant l'ordre suffixe que le parcours va
 * écrire
 * \param prio tableau de priorités pour le choix des *racines* du parcours ; si
 * ce paramètre vaut NULL, la priorité est celle par défaut : 0, 1, 2, ...
 * \return 0 en cas de succès, -1 en cas de problème d'allocation mémoire
 */
int graphe_parcours_largeur(graphe *g, graphe **arbo, int **suff, int *prio);

/**
 * \brief Parcourt le graphe en choisissant à chaque étape de façon aléatoire si
 * le sommet choisi est le premier ou le dernier ajouté
 * \param g adresse d'un graphe à parcourir
 * \param arbo adresse de l'adresse de l'arborescence que le parcours va écrire
 * \param suff adresse du tableau contenant l'ordre suffixe que le parcours va
 * écrire
 * \param prio tableau de priorités pour le choix des *racines* du parcours ; si
 * ce paramètre vaut NULL, la priorité est celle par défaut : 0, 1, 2, ...
 * \return 0 en cas de succès, -1 en cas de problème d'allocation mémoire
 */
int graphe_parcours_larg_ou_prof(graphe *g, graphe **arbo, int **suff, int *prio);

/* Applications du parcours en profondeur */
/**
 * \brief Si le graphe est acyclique, en donne un ordre topologique.
 * \param g adresse de la variable g à lire
 * \param ordre_top adresse du tableau voué à contenir l'ordre topologique s'il
 * existe. Si le graphe a au moins un circuit, *ordre_top vaudra NULL
 * \return -1 en cas de problème d'allocation mémoire, -2 si le graphe n'est pas
 * acyclique, 0 sinon.
 *
 * En cas d'écriture de l'ordre topologique, c'est la responsabilité de
 * l'appelant de libérer le tableau obtenu avec la fonction \a free
 */
int graphe_ordre_top(graphe *g, int **ordre_top);

/**
 * \brief Calcule les composantes fortement connexes d'un graphe
 * \param g adresse de la variable graphe à lire
 * \param reprs_cfc adresse d'un tableau à écrire : pour chaque composante
 * fortement connexe, un représentant a été choisi et le représentant de la
 * composante du sommet v est (*reprs_cfc)[v]
 *
 * En cas de succès, c'est la responsabilité de
 * l'appelant de libérer le tableau obtenu avec la fonction \a free
 */
int graphe_comp_fort_conn(graphe *g, int **reprs_cfc);

/* Applications du parcours en largeur */
/** \brief Calcule les distances de graphe des sommets du graphe à un sommet
 * donné
 * \param g adresse du graphe à lire
 * \param r sommet depuis lequel on veut calculer les distances
 *
 * \return NULL en cas d'échec d'allocation mémoire, sinon l'adresse d'un
 * tableau dynamiquement alloué
 * d'entiers tel que, pour chaque sommet \a v du graphe,
 * la case indexée par v est la distance de r à v.
 *
 * Si v n'est pas accessible depuis r, la distance de r à v est la constante
 * DIST_INF, définie dans graphe_parcours.h.
 */
int *graphe_distances_depuis_sommet(graphe *g, int sommet);

/**
 * \brief Calcule le diamètre du graphe g
 * \param g adresse du graphe à lire
 *
 * \return -2 en cas de problème d'allocation mémoire, la constante DIST_INF si
 * le graphe n'est pas fortement connexe et le diamètre (entier positif ou nul
 * fini) dans les autres cas.
 */
int graphe_diametre(graphe *g);

graphe *graphe_inv(graphe *g);
int *inv_tab(int *tab, int n);
int is_dist_inf(int *tab, int n);
int max_val(int *tab, int n);



#endif
