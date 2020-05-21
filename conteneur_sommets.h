/**
 * \file conteneur_sommets.h
 * \brief conteneur générique de sommets et ses créateurs et destructeurs
 * spécialisés
 * \version 1
 * \date mer. 20 nov. 2019 11:41:55 CET
 * \authors Pierre Rousselin, Antoine Rozenknop, Sophie Toulouse
 */
#ifndef CONTENEUR_SOMMETS_H
#define CONTENEUR_SOMMETS_H

/**
 * \brief Conteneur générique de sommets pour les parcours
 */
typedef struct conteneur_sommets conteneur_sommets ; 

/* Partie générique */
/**
 * \brief Retourne 1 si le conteneur est vide, 0 sinon.
 * \param cs adresse du conteneur en lecture
 * \return 1 si le conteneur est vide, 0 sinon
 */
int cs_est_vide(conteneur_sommets *cs);

/**
 * \brief Ajoute le sommet \a sommet dans le conteneur \a cs.
 */
void cs_ajouter(conteneur_sommets *cs, int sommet);

/**
 * \brief Supprime le sommet \a sommet dans le conteneur \a cs.
 * On suppose que ce sommet est le dernier sommet à avoir été choisi
 * avec la fonction \a cs_choisir.
 */
void cs_supprimer(conteneur_sommets *cs);

/**
 * \brief Choisit un sommet dans le conteneur.
 */
int cs_choisir(conteneur_sommets *cs);

/**
 * \brief Libère la mémoire associée à un conteneur (ne fait rien si le
 * paramètre vaut NULL).
 */
void cs_detruire(conteneur_sommets *cs);


/* Partie PILE */
/**
 * \brief Crée un conteneur associé à la structure de donnée pile.
 * \param n taille maximale de la pile
 * \return un pointeur vers un nouveau conteneur de sommets (NULL en cas d'échec).
 *
 * En cas de succès, l'appelant devra ensuite libérer la mémoire à l'aide de
 * cs_detruire
 */
conteneur_sommets *cs_creer_pile(int n);


/* Partie FILE */
/**
 * \brief Crée un conteneur associé à la structure de donnée file
 * \param n nombre maximal d'éléments pouvant être ajoutés dans la file
 * \return un pointeur vers un nouveau conteneur de sommets (NULL en cas d'échec).
 *
 * En cas de succès, l'appelant devra ensuite libérer la mémoire à l'aide de
 * cs_detruire_file
 */
conteneur_sommets *cs_creer_file(int n);


/* Partie PILE_OU_FILE */
/**
 * \brief Crée un conteneur associé à la structure de donnée pile_ou_file.
 * \param n nombre maximal d'éléments pouvant être ajoutés dans la file
 * \return un pointeur vers un nouveau conteneur de sommets (NULL en cas d'échec).
 *
 * En cas de succès, l'appelant devra ensuite libérer la mémoire à l'aide de
 * cs_detruire_pile_ou_file.
 */
conteneur_sommets *cs_creer_pile_ou_file(int n);

#endif
