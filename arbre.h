#ifndef ARBRE_H_INCLUDED
#define ARBRE_H_INCLUDED

typedef struct noeud_s {
    int val;
    struct noeud_s * gauche;
    struct noeud_s * droit;
}noeud_t;
typedef noeud_t * arbre_t;

arbre_t cree_arbre(int val,arbre_t gauche,arbre_t droit);
void detruit_arbre(arbre_t arbre);
int nombre_de_noeuds(arbre_t arbre);
void affiche_arbre(arbre_t arbre);
int compare(arbre_t arbre1, arbre_t arbre2);
arbre_t insere(arbre_t arbre, int val);
arbre_t trouve_noeud(arbre_t arbre, int val);
int verifie(arbre_t arbre);
void tri(int *tableau, int taille);
arbre_t supprime(arbre_t arbre, int val);

void parcoursPrefixe_it(arbre_t arbre);
void parcoursInfixe_it(arbre_t arbre);
void parcoursPostfixe_it(arbre_t arbre);

typedef struct pile_s {
    arbre_t *elements;
    int sommet;
    int capacite;
} pile_t;

pile_t* cree_pile(int capacite);
void detruit_pile(pile_t *pile);
void empile(pile_t *pile, arbre_t noeud);
arbre_t depile(pile_t *pile);
int pile_vide(pile_t *pile);

#endif // ARBRE_H_INCLUDED
