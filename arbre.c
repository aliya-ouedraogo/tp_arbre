#include "arbre.h"
#include <stdio.h>
#include <stdlib.h>

// Question 2

arbre_t cree_arbre(int val,arbre_t gauche,arbre_t droit) {
    arbre_t nouvel_arbre = (noeud_t *)malloc(sizeof(noeud_t));
    nouvel_arbre->val = val;
    nouvel_arbre->gauche = gauche;
    nouvel_arbre->droit = droit;
    return nouvel_arbre;
}

//Question 3

void detruit_arbre(arbre_t arbre) {
    if (arbre == NULL) {
        return;
    }
    detruit_arbre(arbre->gauche);
    detruit_arbre(arbre->droit);
    free(arbre);
}

// Question 4

int nombre_de_noeuds(arbre_t arbre) {
    if (arbre == NULL) {
        return 0;
    }
    return 1 + nombre_de_noeuds(arbre->gauche) + nombre_de_noeuds(arbre->droit);
}

//Question 5

void affiche_arbre(arbre_t arbre) {
    if (arbre == NULL) {
        return;
    }
    affiche_arbre(arbre->gauche);
    printf("%d", arbre->val);
    affiche_arbre(arbre->droit);
}

//Question 6

int compare(arbre_t arbre1, arbre_t arbre2) {
    if (arbre1 == NULL && arbre2 == NULL) {
        return 0;
    }
    if (arbre1 == NULL || arbre2 == NULL) {
        return 1;
    }
    if (arbre1->val != arbre2->val) {
        return 1;
    }
    return compare(arbre1->gauche, arbre2->gauche) || compare(arbre1->droit, arbre2->droit);
}

//Question 7

arbre_t insere(arbre_t arbre, int val) {
    if (arbre == NULL) {
        return cree_arbre(val, NULL, NULL);
    }
    if (val < arbre->val) {
        arbre->gauche = insere(arbre->gauche, val);
    } else {
        arbre->droit = insere(arbre->droit, val);
    }

    return arbre;
}

//Question 8

arbre_t trouve_noeud(arbre_t arbre, int val) {
     if (arbre == NULL) {
        return NULL;
    }

    if (arbre->val == val) {
        return arbre;
    }

    if (val < arbre->val) {
        return trouve_noeud(arbre->gauche, val);
    } else {
        return trouve_noeud(  arbre->droit, val);
    }
}

//Question 9

static int verifie_aux(arbre_t arbre, int *min, int *max) {
    if (arbre == NULL) {
        return 1;
    }

    int min_gauche, max_gauche, min_droit, max_droit;
    *min = arbre->val;
    *max = arbre->val;

    if (arbre->gauche != NULL) {
        if (!verifie_aux(arbre->gauche, &min_gauche, &max_gauche)) {
            return 0;
        }

        if (max_gauche >= arbre->val) {
            return 0;
        }
        *min = min_gauche;
    }

    if (arbre->droit != NULL) {
        if (!verifie_aux(arbre->droit, &min_droit, &max_droit)) {
            return 0;
        }

        if (min_droit < arbre->val) {
            return 0;
        }
        *max = max_droit;
    }

    return 1;
}
int verifie(arbre_t arbre) {
    if (arbre == NULL) {
        return 1;
    }
    int min, max;
    return verifie_aux(arbre, &min, &max);
}

//Question 10

static int remplit_tableau(arbre_t arbre, int *tableau, int position) {
    if (arbre == NULL) {
        return 0;
    }
    int nb_gauche = remplit_tableau(arbre->gauche, tableau, position);
    tableau[position + nb_gauche] = arbre->val;
    int nb_droit = remplit_tableau(arbre->droit, tableau, position + nb_gauche + 1);

    return nb_gauche + 1 + nb_droit;
}

void tri(int *tableau, int taille) {
    arbre_t abr = NULL;
    int i;
    for (i = 0; i < taille; i++) {
        abr = insere(abr, tableau[i]);
    }
    remplit_tableau(abr, tableau, 0);
    detruit_arbre(abr);

}
//Question 11

static arbre_t trouve_min(arbre_t arbre) {
    while (arbre->gauche != NULL) {
        arbre = arbre->gauche;
    }
    return arbre;
}

arbre_t supprime(arbre_t arbre, int val) {
    if (arbre == NULL) {
        return NULL;
    }
    if (val < arbre->val) {
        arbre->gauche = supprime(arbre->gauche, val);
    } else if (val > arbre->val) {
        arbre->droit = supprime(arbre->droit, val);
    } else {
        if (arbre->gauche == NULL && arbre->droit == NULL) {
            free(arbre);
            return NULL;
        }
        if (arbre->gauche == NULL) {
            arbre_t temp = arbre->droit;
            free(arbre);
            return temp;
        }
        if (arbre->droit == NULL) {
            arbre_t temp = arbre->gauche;
            free(arbre);
            return temp;
        }
        arbre_t successeur = trouve_min(arbre->droit);
        arbre->val = successeur->val;
        arbre->droit = supprime(arbre->droit, successeur->val);
    }

    return arbre;
}

//Question 12

pile_t* cree_pile(int capacite) {
    pile_t *pile = (pile_t*)malloc(sizeof(pile_t));
    if (pile == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire pour la pile\n");
        exit(EXIT_FAILURE);
    }
    pile->elements = (arbre_t*)malloc(capacite * sizeof(arbre_t));
    if (pile->elements == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire pour les éléments de la pile\n");
        free(pile);
        exit(EXIT_FAILURE);
    }
    pile->sommet = -1;
    pile->capacite = capacite;
    return pile;
}

void detruit_pile(pile_t *pile) {
    if (pile != NULL) {
        free(pile->elements);
        free(pile);
    }
}

void empile(pile_t *pile, arbre_t noeud) {
    if (pile->sommet >= pile->capacite - 1) {
        fprintf(stderr, "Erreur: pile pleine\n");
        return;
    }
    pile->elements[++(pile->sommet)] = noeud;
}

arbre_t depile(pile_t *pile) {
    if (pile->sommet < 0) {
        return NULL;
    }
    return pile->elements[(pile->sommet)--];
}

int pile_vide(pile_t *pile) {
    return pile->sommet < 0;
}

/* Parcours préfixe itératif */
void parcoursPrefixe_it(arbre_t arbre) {
    if (arbre == NULL) {
        return;
    }

    pile_t *pile = cree_pile(1000);
    empile(pile, arbre);

    while (!pile_vide(pile)) {
        arbre_t noeud = depile(pile);
        printf("%d ", noeud->val);

        if (noeud->droit != NULL) {
            empile(pile, noeud->droit);
        }
        if (noeud->gauche != NULL) {
            empile(pile, noeud->gauche);
        }
    }

    detruit_pile(pile);
}

/* Parcours infixe itératif */
void parcoursInfixe_it(arbre_t arbre) {
    if (arbre == NULL) {
        return;
    }

    pile_t *pile = cree_pile(1000);
    arbre_t courant = arbre;

    while (courant != NULL || !pile_vide(pile)) {
        while (courant != NULL) {
            empile(pile, courant);
            courant = courant->gauche;
        }
        courant = depile(pile);
        printf("%d ", courant->val);

        courant = courant->droit;
    }

    detruit_pile(pile);
}

/* Parcours postfixe itératif */
void parcoursPostfixe_it(arbre_t arbre) {
    if (arbre == NULL) {
        return;
    }

    pile_t *pile1 = cree_pile(1000);
    pile_t *pile2 = cree_pile(1000);

    empile(pile1, arbre);

    while (!pile_vide(pile1)) {
        arbre_t noeud = depile(pile1);
        empile(pile2, noeud);

        if (noeud->gauche != NULL) {
            empile(pile1, noeud->gauche);
        }
        if (noeud->droit != NULL) {
            empile(pile1, noeud->droit);
        }
    }

    while (!pile_vide(pile2)) {
        arbre_t noeud = depile(pile2);
        printf("%d ", noeud->val);
    }

    detruit_pile(pile1);
    detruit_pile(pile2);
}

