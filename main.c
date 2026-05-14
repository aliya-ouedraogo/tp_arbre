#include <stdio.h>
#include <stdlib.h>

#include "arbre.h"

void test_creation_destruction() {
    printf("\n=== Test 1 & 2 & 3: Creation et destruction d'arbre ===\n");
    arbre_t feuille1 = cree_arbre(5, NULL, NULL);
    arbre_t feuille2 = cree_arbre(15, NULL, NULL);
    arbre_t racine = cree_arbre(10, feuille1, feuille2);

    printf("Arbre cree avec succes (racine: %d)\n", racine->val);
    detruit_arbre(racine);
    printf("Arbre detruit avec succes\n");
}

void test_nombre_noeuds() {
    printf("\n=== Test 4: Nombre de noeuds ===\n");
    arbre_t arbre = NULL;
    arbre = insere(arbre, 10);
    arbre = insere(arbre, 5);
    arbre = insere(arbre, 15);
    arbre = insere(arbre, 3);
    arbre = insere(arbre, 7);
    arbre = insere(arbre, 12);
    arbre = insere(arbre, 17);

    printf("Nombre de noeuds: %d (attendu: 7)\n", nombre_de_noeuds(arbre));
    detruit_arbre(arbre);
}

void test_affichage() {
    printf("\n=== Test 5: Affichage (parcours infixe) ===\n");
    arbre_t arbre = NULL;
    arbre = insere(arbre, 10);
    arbre = insere(arbre, 5);
    arbre = insere(arbre, 15);
    arbre = insere(arbre, 3);
    arbre = insere(arbre, 7);
    arbre = insere(arbre, 12);
    arbre = insere(arbre, 17);

    printf("Affichage en ordre croissant: ");
    affiche_arbre(arbre);
    printf("\n");
    detruit_arbre(arbre);
}

void test_comparaison() {
    printf("\n=== Test 6: Comparaison d'arbres ===\n");

    /* Arbre 1 */
    arbre_t arbre1 = cree_arbre(10,cree_arbre(5, NULL, NULL),cree_arbre(15, NULL, NULL));

    /* Arbre 2 (identique) */
    arbre_t arbre2 = cree_arbre(10,cree_arbre(5, NULL, NULL),cree_arbre(15, NULL, NULL));

    /* Arbre 3 (différent) */
    arbre_t arbre3 = cree_arbre(10,cree_arbre(5, NULL, NULL),cree_arbre(20, NULL, NULL));

    printf("Comparaison arbre1 et arbre2 (identiques): %d (attendu: 0)\n", compare(arbre1, arbre2));
    printf("Comparaison arbre1 et arbre3 (differents): %d (attendu: 1)\n", compare(arbre1, arbre3));

    detruit_arbre(arbre1);
    detruit_arbre(arbre2);
    detruit_arbre(arbre3);
}

void test_insertion_recherche() {
    printf("\n=== Test 7 & 8: Insertion et recherche ===\n");
    arbre_t arbre = NULL;

    arbre = insere(arbre, 10);
    arbre = insere(arbre, 5);
    arbre = insere(arbre, 15);
    arbre = insere(arbre, 3);
    arbre = insere(arbre, 7);

    printf("Arbre construit: ");
    affiche_arbre(arbre);
    printf("\n");

    arbre_t trouve = trouve_noeud(arbre, 7);
    if (trouve != NULL) {
        printf("Valeur 7 trouvee: %d\n", trouve->val);
    }

    trouve = trouve_noeud(arbre, 100);
    if (trouve == NULL) {
        printf("Valeur 100 non trouvee (correct)\n");
    }

    detruit_arbre(arbre);
}

void test_verification() {
    printf("\n=== Test 9: Verification ABR ===\n");

    /* ABR valide */
    arbre_t abr_valide = NULL;
    abr_valide = insere(abr_valide, 10);
    abr_valide = insere(abr_valide, 5);
    abr_valide = insere(abr_valide, 15);
    abr_valide = insere(abr_valide, 3);
    abr_valide = insere(abr_valide, 7);

    printf("ABR valide: %d (attendu: 1)\n", verifie(abr_valide));

    /* ABR invalide (construit manuellement) */
    arbre_t abr_invalide = cree_arbre(10,cree_arbre(15, NULL, NULL),cree_arbre(5, NULL, NULL));

    printf("ABR invalide: %d (attendu: 0)\n", verifie(abr_invalide));

    detruit_arbre(abr_valide);
    detruit_arbre(abr_invalide);
}

void test_tri() {
    printf("\n=== Test 10: Tri par ABR ===\n");
    int tableau[] = {15, 3, 10, 5, 7, 12, 17, 1, 20, 8};
    int taille = 10;

    printf("Tableau avant tri: ");
    int i;
    for (i = 0; i < taille; i++) {
        printf("%d ", tableau[i]);
    }
    printf("\n");

    tri(tableau, taille);

    printf("Tableau apres tri: ");
    for (i = 0; i < taille; i++) {
        printf("%d ", tableau[i]);
    }
    printf("\n");
}

void test_suppression() {
    printf("\n=== Test 11: Suppression ===\n");
    arbre_t arbre = NULL;

    arbre = insere(arbre, 10);
    arbre = insere(arbre, 5);
    arbre = insere(arbre, 15);
    arbre = insere(arbre, 3);
    arbre = insere(arbre, 7);
    arbre = insere(arbre, 12);
    arbre = insere(arbre, 17);

    printf("Arbre initial: ");
    affiche_arbre(arbre);
    printf("\n");

    /* Suppression d'une feuille */
    arbre = supprime(arbre, 3);
    printf("Apres suppression de 3 (feuille): ");
    affiche_arbre(arbre);
    printf("\n");

    /* Suppression d'un noeud avec un fils */
    arbre = supprime(arbre, 5);
    printf("Apres suppression de 5 (un fils): ");
    affiche_arbre(arbre);
    printf("\n");

    /* Suppression d'un noeud avec deux fils */
    arbre = supprime(arbre, 15);
    printf("Apres suppression de 15 (deux fils): ");
    affiche_arbre(arbre);
    printf("\n");

    detruit_arbre(arbre);
}

void test_parcours_iteratifs() {
    printf("\n=== Test 12: Parcours iteratifs ===\n");
    arbre_t arbre = NULL;

    arbre = insere(arbre, 10);
    arbre = insere(arbre, 5);
    arbre = insere(arbre, 15);
    arbre = insere(arbre, 3);
    arbre = insere(arbre, 7);
    arbre = insere(arbre, 12);
    arbre = insere(arbre, 17);

    printf("Parcours prefixe iteratif: ");
    parcoursPrefixe_it(arbre);
    printf("\n");

    printf("Parcours infixe iteratif: ");
    parcoursInfixe_it(arbre);
    printf("\n");

    printf("Parcours postfixe iteratif: ");
    parcoursPostfixe_it(arbre);
    printf("\n");

    detruit_arbre(arbre);
}

int main() {
    printf("========================================\n");
    printf("Tests des fonctions sur les arbres binaires\n");
    printf("========================================\n");

    test_creation_destruction();
    test_nombre_noeuds();
    test_affichage();
    test_comparaison();
    test_insertion_recherche();
    test_verification();
    test_tri();
    test_suppression();
    test_parcours_iteratifs();

    printf("\n========================================\n");
    printf("Tous les tests termines avec succes!\n");
    printf("========================================\n");

    return 0;
}
