/**
 * \file pile.h
 * \brief pile pouvant contenir un nombre maximal d'éléments
 * \version 1
 * \date mer. 20 nov. 2019 11:35:37 CET
 * \authors Pierre Rousselin, Antoine Rozenknop, Sophie Toulouse
 */
#ifndef PILE_H
#define PILE_H

/**
 * \brief structure de donnée pile avec une hauteur maximale
 */
typedef struct pile pile;

/**
 * \brief Crée une pile avec une hauteur maximale
 * \return un pointeur vers la pile créée (NULL en cas d'échec d'allocation
 * mémoire).
 */
pile *pile_creer(int n);

/**
 * \brief Crée une pile à partir du tableau passé en paramètre.
 * \return un pointeur vers la pile créée ou NULL en cas d'échec d'allocation
 * mémoire
 */
pile *pile_creer_depuis_tabint(int * tab, int taille) ;

/**
 * \brief Retourne la taille d'une pile
 */
int pile_taille(pile *p);

/**
 * \brief Libère la mémoire occupée par la file d'adresse f (ne fait rien si f
 * est NULL).
 */
void pile_detruire(pile *p);

/**
 * \brief Retourne 1 si la file pointée est vide, 0 sinon.
 */
int pile_est_vide(pile *p);

/**
 * \brief Empile le sommet \a sommet sur la pile.
 */
void pile_empiler(pile *p, int sommet);

/**
 * \brief Supprime l'élément en haut de la pile.
 */
int pile_depiler(pile *p);

/**
 * \brief Retourne l'élément en haut de la pile.
 */
int pile_sommet(pile *p);


/**
 * \brief Crée un tableau d'entiers contenant la liste des sommets de \a p.
 * \param taille : adresse où stocker la taille du tableau (ou NULL)
 * \return l'adresse du tableau alloué.
 * \note Cette fonction réalise une allocation mémoire et la libération de 
 * l'espace alloué pour le tableau est à la charge de l'appelant.
 */
int * pile_tabint(pile *p, int * taille);

#endif
