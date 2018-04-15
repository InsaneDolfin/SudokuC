#include<stdio.h>
#include<stdlib.h>
#include<string.h>


#define SIZE 9
#define SIZEMAX 80
#define TRUE 1
#define FALSE 0
typedef int GRILLE[SIZE][SIZE];

//Struct ****************************************************************************
typedef struct _DATA {
    GRILLE grille;
    int num_test;
    int pos_ligne;
    int pos_colonne;
    int pos_bloc;
} DATA;

typedef struct _NODE {
    DATA data;
    struct _NODE * next;
    struct _NODE * prev;

} NODE;

typedef struct _PILE {
    NODE * head;
    NODE * tail;
} PILE;

// Annonce fonctions ***************************************************
void affichage(GRILLE grille);

void initialisation_facile(GRILLE grille);
void initialisation_moyen(GRILLE grille);
void initialisation_difficile(GRILLE grille);

int exist_bloc(GRILLE grille, int pos_ligne, int pos_colonne, int num_test);
int exist_ligne(GRILLE grille, int pos_ligne, int num_test);
int exist_colonne(GRILLE grille, int pos_colonne, int num_test);
int valid_grille(GRILLE grille, int *pos_ligne, int *pos_colonne, int num_test);

void menu(void);

int grille_zero(GRILLE grille);
int grille_dix(GRILLE grille);
void pos_zero(GRILLE grille, int *pos_zero_ligne, int *pos_zero_colonne);

void prependToList(PILE *pile, DATA data);
void removeHead(PILE * pile);

void copyGrille2(GRILLE *dest, GRILLE src);
void copyData(DATA *dest, DATA src);

void resolution2(NODE sudoku, PILE pile);

// Main *************************************************************

int main(void)
{
    /*
    NODE sudoku;
    GRILLE grilletest;
    PILE *pile;
    pile = calloc(1, sizeof(PILE));
    
    initialisation(grilletest);
    menu();

    copyGrille2(&sudoku.data.grille, grilletest);
    prependToList(pile, sudoku.data);
    affichage(sudoku.data.grille);
    printf("\n\n\n");
    resolution2(sudoku, *pile);

    */
    menu();
    getchar();
}

// Fonctions ************************************************************************

void initialisation_facile(GRILLE grille)
{
    int i, j;
    FILE* fichier = NULL;

    char chaine[SIZEMAX]; //chaine vide stockage des lignes
    char *token;
    fichier = fopen("grille_facile.csv", "r");
    if (fichier != NULL)
    {
        for (i = 0; i<9; i++) {
            fgets(chaine, SIZEMAX, fichier);
            token = strtok(chaine, ";");
            sscanf(token, "%d", &grille[i][0]);
            for (j = 1; j<9; j++) {
                token = strtok(NULL, ";");
                sscanf(token, "%d", &grille[i][j]);
            }
        }
        fclose(fichier);
    }
    else
    {
        printf("Impossible d'ouvrir le fichier test.txt");
    }
    return;
}
void initialisation_moyen(GRILLE grille)
{
    int i, j;
    FILE* fichier = NULL;

    char chaine[SIZEMAX]; //chaine vide stockage des lignes
    char *token;
    fichier = fopen("grille_moyen.csv", "r");
    if (fichier != NULL)
    {
        for (i = 0; i<9; i++) {
            fgets(chaine, SIZEMAX, fichier);
            token = strtok(chaine, ";");
            sscanf(token, "%d", &grille[i][0]);
            for (j = 1; j<9; j++) {
                token = strtok(NULL, ";");
                sscanf(token, "%d", &grille[i][j]);
            }
        }
        fclose(fichier);
    }
    else
    {
        printf("Impossible d'ouvrir le fichier test.txt");
    }
    return;
}
void initialisation_difficile(GRILLE grille)
{
    int i, j;
    FILE* fichier = NULL;

    char chaine[SIZEMAX]; //chaine vide stockage des lignes
    char *token;
    fichier = fopen("grille_diabolique.csv", "r");
    if (fichier != NULL)
    {
        for (i = 0; i<9; i++) {
            fgets(chaine, SIZEMAX, fichier);
            token = strtok(chaine, ";");
            sscanf(token, "%d", &grille[i][0]);
            for (j = 1; j<9; j++) {
                token = strtok(NULL, ";");
                sscanf(token, "%d", &grille[i][j]);
            }
        }
        fclose(fichier);
    }
    else
    {
        printf("Impossible d'ouvrir le fichier test.txt");
    }
    return;
}
//Fonction qui affiche la grille
void affichage(GRILLE grille)
{
    int i, j;
    for (i = 0; i<9; i++) {
        for (j = 0; j<9; j++) {
            printf("%d	", grille[i][j]);
        }
        printf("\n\n");
    }
}



//Test ligne,colonne,bloc ***************************************************


//Teste si un chiffre existe sur un bloc **************************
int exist_bloc(GRILLE grille, int pos_ligne, int pos_colonne, int num_test)
{
    int i, j;
    int x = pos_ligne - (pos_ligne % 3);
    int y = pos_colonne - (pos_colonne % 3);
    for (i = x; i<x + 3; i++)
        for (j = y; j<y + 3; j++) {
            if (grille[i][j] == num_test)
                return 1;
        }
    return 0;


}

//Teste si un chiffre existe sur une ligne ****************
int exist_ligne(GRILLE grille, int pos_ligne, int num_test)
{
    int i;
    for (i = 0; i<9; i++)
    {
        if (grille[pos_ligne][i] == num_test)
            return 1;

    }
    return 0;
}

//Teste si un chiffre existe sur une colonne ********************
int exist_colonne(GRILLE grille, int pos_colonne, int num_test)
{
    int j;
    for (j = 0; j<9; j++)
    {
        if (grille[j][pos_colonne] == num_test)
            return 1;
    }
    return 0;
}


//Validateur de grille ************************************************
int valid_grille(GRILLE grille, int *pos_ligne, int *pos_colonne, int num_test)
{
    if (exist_colonne(grille, pos_colonne, num_test) == 1 || exist_ligne(grille, pos_ligne, num_test) == 1 || exist_bloc(grille, pos_ligne, pos_colonne, num_test) == 1) {
        return 0;
        printf("La grille n'est pas valide \n");
    }
    else
        return 1;
}



//Fonction menu *************************************************************
void menu(void)
{
    int choix,diff;
    char res;
    GRILLE grilletest;
    NODE sudoku;
    PILE *pile;
    pile = calloc(1, sizeof(PILE));
    while (1)
    {
        printf(" ****************   SUDOKU ! *****************\n\n\n\n");
        printf("Entrer votre choix ! \n\n");
        printf("[1]  Lancer le jeu ! \n");
        printf("[2]  Instructions !\n\n");
        printf("[3]  Quitter le jeu !\n");
        scanf("%d", &choix);
        if (choix == 1)
        {
            printf("\n\n\n\n\n\n\n");
            printf("Quelle difficulte ?\n");
            printf("[1]  Facile ! \n");
            printf("[2]  Moyen !\n");
            printf("[3]  Diabolique !\n");
            scanf("%d", &diff);
            if (diff == 1) {
                initialisation_facile(grilletest);
            }
            if (diff == 2) {
                initialisation_moyen(grilletest);
            }
            if (diff == 3) {
                initialisation_difficile(grilletest);
            }
            copyGrille2(&sudoku.data.grille, grilletest);
            prependToList(pile, sudoku.data);
            affichage(sudoku.data.grille);
            printf("\n\n\n");
            resolution2(sudoku, *pile);
        }

        if (choix == 2)
        {
            printf("\n\n\n\n\n\n\n");
            printf("Les regles du sudoku sont tres simples. Un sudoku classique contient neuf lignes et neuf colonnes, donc 81 cases au total. \n");
            printf("Le but du jeu est de remplir ces cases avec des chiffres allant de 1 à 9 en veillant toujours a ce qu'un meme chiffre ne figure qu'une seule fois par colonne, une seule fois par ligne, et une seule fois par carre de neuf cases. \n");
            printf("Au debut du jeu, une vingtaine de chiffres sont deja places et il vous reste à trouver les autres. En effet, une grille initiale de sudoku correctement constituee ne peut aboutir qu'a une et une seule solution. Pour trouver les chiffres manquants, tout est une question de logique et d'observation. \n");
            printf("\n\n\n\n\n\n\n");
        }

        if (choix == 3)
        {
            break;
        }

    }
}

//Fonction qui vérifie s'il y a un 0 dans la grille
int grille_zero(GRILLE grille)
{
    int i, j, c = 0;
    for (i = 0; i < 9; i++)
    {
        for (j = 0; j < 9; j++)
        {
            if (grille[i][j] == 0)
                c += 1;
        }
    }
    if (c == 0)
        return 0;
    else
        return 1;
}
//Fonction qui renvoie la position du zéro

void pos_zero(GRILLE grille, int *pos_zero_ligne, int *pos_zero_colonne)
{
    int i, j;
    *pos_zero_ligne = 10;
    *pos_zero_colonne = 10;
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++) {
            if (grille[i][j] == 0) {
                *pos_zero_ligne = i;
                *pos_zero_colonne = j;
                break;
            }
        }
        if (*pos_zero_ligne != 10 || *pos_zero_colonne != 10)
            break;
    }
    // printf("%d ; %d\n", *pos_zero_ligne, *pos_zero_colonne);
}

int grille_dix(GRILLE grille)
{
    int i, j, c = 0;
    for (i = 0; i < 9; i++)
    {
        for (j = 0; j < 9; j++)
        {
            if (grille[i][j] == 10)
                c += 1;
        }
    }
    if (c == 0)
        return 0;
    else
        return 1;
}
//Fonctions de gestions des listes:
void prependToList(PILE *pile, DATA data) //ajout au debut
{
    NODE *pnode;
    pnode = calloc(1, sizeof(NODE));
    copyData(&(pnode->data), data);
    if (pile->head != NULL) {

        pnode->next = pile->head;
        pile->head = pnode;
    }
    else {
        pile->head = pnode;

    }
}

void removeHead(PILE * pile)
{
    DATA data;
    if (pile->head == NULL) {
        printf("Erreur, la liste est vide\n");
    }
    else {
        NODE *pnode;
        pnode = pile->head->next;
        // copyData(&data, pnode->data);
        pile->head = NULL;
        pile->head = pnode->next;

        free(pnode);
    }

}

void copyData(DATA *dest, DATA src)
{
    copyGrille2(&dest->grille, src.grille);
    dest->num_test = src.num_test;
    dest->pos_bloc = src.pos_bloc;
    dest->pos_colonne = src.pos_colonne;
    dest->pos_ligne = src.pos_ligne;
}


void copyGrille2(GRILLE *dest, GRILLE src)
{
    int i, j;
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++) {
            (*dest)[i][j] = src[i][j];
        }
    }
}






void resolution2(NODE sudoku, PILE pile)
{

    GRILLE grille_tempo;
    int *pos_zero_ligne = NULL;
    int *pos_zero_colonne = NULL;
    int compteur = 0;
    prependToList(&pile, sudoku.data);
    sudoku.data.num_test = 0;
    while (grille_zero(sudoku.data.grille) == 1 ||grille_dix(sudoku.data.grille)==1) {

        int num_temp = 0;

        //l'affichage suivant permet de voir la résolution case par case!
        //affichage(sudoku.data.grille);
        //printf("\n\n\n");


        if (grille_dix(sudoku.data.grille)) {
            removeHead(&pile);
            pos_zero_ligne = NULL;
            pos_zero_colonne = NULL;
            pos_zero_ligne = &pile.head->data.pos_ligne;
            pos_zero_colonne = &pile.head->data.pos_colonne;
            num_temp = grille_tempo[pile.head->data.pos_ligne][pile.head->data.pos_colonne];
            //affichage(pile.head->data.grille);
            //printf("\n\n\n");
        }

        else if (!grille_zero(pile.head->data.grille))
            break; //pas de zéro dans la grille, on a fini

        else {
            pos_zero(pile.head->data.grille, &pos_zero_ligne, &pos_zero_colonne);
            //printf("%d ; %d \n", pos_zero_ligne, pos_zero_colonne);
            pile.head->data.pos_ligne = pos_zero_ligne;
            pile.head->data.pos_colonne = pos_zero_colonne;
            num_temp = 0;
        }
        copyGrille2(&grille_tempo, pile.head->data.grille); //grille contient le contenu de la tete de la pile
        num_temp++;
        for (; num_temp <= 9; num_temp++) {
            if (valid_grille(grille_tempo, pile.head->data.pos_ligne, pile.head->data.pos_colonne, num_temp)) {
                //printf("bbbbbbbbbbbbb");
                grille_tempo[pile.head->data.pos_ligne][pile.head->data.pos_colonne] = num_temp;
                copyGrille2(&sudoku.data.grille, grille_tempo);
                prependToList(&pile, sudoku.data);
                break;
            }
        }
        if (num_temp == 10)
        {
            grille_tempo[pile.head->data.pos_ligne][pile.head->data.pos_colonne] = 10;
            copyGrille2(&sudoku.data.grille, grille_tempo);
            prependToList(&pile, sudoku.data);
        }


        compteur++;
    }
    affichage(sudoku.data.grille);
    printf("\n\n");
    printf("Nombre d'essai: %d", compteur);
    printf("\n\n\n");
}








//Estimation de difficulté ********************************************
/*void difficulte(void)
{

}*/



