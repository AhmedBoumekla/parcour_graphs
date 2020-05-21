/**
 * \file pile_ou_file.h
 * \brief Structure de donnée où l'élément choisi est choisi avec probabilité
 * 1/2 en tete et probabilité 1/2 en fin.
 * \version 1
 * \date mer. 20 nov. 2019 11:35:37 CET
 * \authors Pierre Rousselin, Antoine Rozenknop, Sophie Toulouse
 */
#ifndef pile_ou_file_H
#define pile_ou_file_H

/**
 * \brief Structure de données entre la pile et la file, où le choix d'un
 * élément se fait aléatoirement en tête ou en queue (et l'ajout toujours en
 * queue). Le nombre maximal d'ajouts est fixé.
 */
typedef struct pile_ou_file pile_ou_file;

/**
 * \brief Crée une pile_ou_file dont le nombre maximal d'ajouts est n
 * \return un pointeur vers la file créée (NULL en cas d'échec d'allocation
 * mémoire).
 */
pile_ou_file *pile_ou_file_creer(int n);

/**
 * \brief Libère la mémoire occupée par la pile_ou_file d'adresse p (ne fait rien si p
 * est NULL).
 */
void pile_ou_file_detruire(pile_ou_file *p);

/**
 * \brief Retourne 1 si la pile_ou_file pointée est vide, 0 sinon.
 */
int pile_ou_file_est_vide(pile_ou_file *p);

/**
 * \brief Ajoute le sommet \a sommet à la fin de la pile_ou_fil
 */
void pile_ou_file_ajouter(pile_ou_file *p, int sommet);
/**
 * \brief Choisit un élément dans la pile_ou_file, le supprime et le retourne.
 * L'élément supprimé est le même que celui qui a été retourné lors d'un appel précédent
 * de pile_ou_file_choisir si aucune suppression ni ajout n'a été effectuée entre-temps.
 */
int pile_ou_file_retirer(pile_ou_file *p);

/**
 * \brief Choisit un élément dans la pile_ou_file. Cet élément est, avec
 * probabilité 1/2 en tête de la structure et avec probabilité 1/2 à la fin.
 */
int pile_ou_file_choisir(pile_ou_file *p);


/**
 * \brief Crée un tableau d'entiers contenant la liste des sommets de \a p.
 * \param taille : adresse où stocker la taille du tableau (ou NULL)
 * \return l'adresse du tableau alloué.
 * \note Cette fonction réalise une allocation mémoire et la libération de 
 * l'espace alloué pour le tableau est à la charge de l'appelant.
 */
int * pile_ou_file_tabint(pile_ou_file *p, int * taille);

#endif
