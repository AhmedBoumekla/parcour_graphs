/**
 * \file file.h
 * \brief file pouvant contenir un nombre maximal d'éléments donné
 * \version 1
 * \date mer. 20 nov. 2019 11:35:37 CET
 * \authors Pierre Rousselin, Antoine Rozenknop, Sophie Toulouse
 */
#ifndef FILE_H
#define FILE_H

/**
 * \brief structure de donnée file avec un nombre maximal d'ajouts dans la file
 */
typedef struct file file;

/**
 * \brief Crée une file dont le nombre maximal d'ajouts est n.
 * \return un pointeur vers la file créée (NULL en cas d'échec d'allocation
 * mémoire).
 */
file *file_creer(int n);

/**
 * \brief Retourne la taille d'une file
 */
int file_taille(file *f);

/**
 * \brief Crée une file à partir du tableau passé en paramètre.
 * \return un pointeur vers la file créée ou NULL en cas d'échec d'allocation
 * mémoire
 */
file *file_creer_depuis_tabint(int * tab, int taille) ;

/**
 * \brief Libère la mémoire occupée par la file d'adresse f (ne fait rien si f
 * est NULL).
 */
void file_detruire(file *f);

/**
 * \brief Retourne 1 si la file pointée est vide, 0 sinon.
 */
int file_est_vide(file *f);

/**
 * \brief Ajoute le sommet \a sommet à la fin de la file.
 */
void file_enfiler(file *f, int sommet);

/**
 * \brief Supprime la tête de la file.
 */
int file_defiler(file *f);

/**
 * \brief Retourne la tête de la file
 */
int file_tete(file *f);


/**
 * \brief Crée un tableau d'entiers contenant la liste des sommets de \a f.
 * \param taille : adresse où stocker la taille du tableau (ou NULL)
 * \return l'adresse du tableau alloué.
 * \note Cette fonction réalise une allocation mémoire et la libération de 
 * l'espace alloué pour le tableau est à la charge de l'appelant.
 */
int * file_tabint(file *f, int * taille);

#endif
