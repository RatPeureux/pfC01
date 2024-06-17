/**
 * @page Général
 * 
 * @file sudoku.c   
 * @brief Programme de résolution de Sudoku en mode console.
 * 
 * @author BLÉAS
 * @version 1.0
 * @date 29 novembre 2023
 * 
 * Ce programme permet à l'utilisateur de jouer au Sudoku en chargeant une grille à partir d'un fichier.
 * L'utilisateur peut remplir les cases vides de la grille en respectant les règles du Sudoku.
 * Le programme indique si une valeur peut être placée dans une case donnée en fonction des valeurs déjà présentes dans la ligne, la colonne et le bloc.
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

/* déclaration des constantes */


/** 
 * @def N
 * @brief Taille d'un bloc de Sudoku.
 *
 * Taille d'une ligne/colonne d'une sous-grille de Sudoku.
 */
#define N 3

/**
 * @def TAILLE
 * @brief Taille de la grille de Sudoku.
 * 
 * Taille d'une ligne/colonne d'une grille de Sudoku.
 */
#define TAILLE (N*N)

/** 
 * @typedef tGrille
 * @brief Type représentant une grille de Sudoku.
 *
 * Tableau 9 par 9 correspondant à la grille d'un Sudoku.
 */
typedef int tGrille[TAILLE][TAILLE];

/* déclaration des procédures/fonctions */

void chargerGrille(tGrille);
void afficherGrille(tGrille);
void saisir(int*);
bool possible(tGrille, int, int, int);
bool gpleine(tGrille);
int nbElementsLigne(tGrille g, int lig);
int nbElementsColonne(tGrille g, int col);

/** 
 * @fn int main()
 * @brief Fonction principale du programme de résolution de Sudoku.
 * @return EXIT_SUCCESS, Code de sortie normale du programme.
 *
 * Le programme principal permet de jouer à un sudoku avec l'aide de plusieurs fonctions/procédures : 
 * il créé et génère une grille, l'affiche, demande à l'utilisateur des indices où saisir une valeur dans la grille, 
 * stock ces valeurs, vérifie si c'est possible de placer la valeur aux coordonnées, puis boucle, lorsque la grille 
 * est pleine ; il affiche un message de fin.
 */
int main(){
    tGrille g;
    int numLigne, numColonne, valeur;

    chargerGrille(g);
    while (gpleine(g) == false)
    {
        afficherGrille(g);  
        printf("Indices de la case : (ligne puis colonne)\n");
        saisir(&numLigne);
        saisir(&numColonne);
        if (g[numLigne-1][numColonne-1] != 0)
        {
            printf("\n IMPOSSIBLE, la case n'est pas libre ! \n");
        }else
        {
            printf("Valeur à insérer :\n");
            saisir(&valeur);
            if (possible(g, numLigne, numColonne, valeur))
            {
                g[numLigne-1][numColonne-1] = valeur;
            }
        }
    }
    printf("\nBravo, vous avez gagné !\n\n");
    printf(" Fin de partie, grille pleine\n\n");
        
    return EXIT_SUCCESS;
}

/* rédaction des procédures/fonctions */

/** 
 * @fn void chargerGrille(tGrille g).
 * @brief Charge une grille de Sudoku à partir d'un fichier.
 * @param g Grille de Sudoku à remplir.
 * 
 * Utilisateur saisi un nom de fichier en .sud, la fonction vérifie s'il existe et si celui-ci n'est pas altéré,
 * si c'est le cas ; la grille est initialisée.
 */
void chargerGrille(tGrille g){
    char nomFichier[30];
    bool conforme = true;
    int somme;
    int i, j;

    do{
        FILE * f;
        printf("\nNom du fichier ? ");
        scanf("%s", nomFichier);
        f = fopen(nomFichier, "rb");
        while (f==NULL)
        {
            printf("\n Fichier %s non reconnu \n", nomFichier);
            printf("\nNom du fichier ? ");
            scanf("%s", nomFichier);
            f = fopen(nomFichier, "rb");
        }
        fread(g, sizeof(int), TAILLE*TAILLE, f);
        fclose(f);
        
        somme = 0;
        for (i=0; i < TAILLE; i++){
            for (j=0; j < TAILLE; j++){
                if (g[i][j] != 0 && g[i][j] != 1 && g[i][j] != 2 && g[i][j] != 3 && g[i][j] != 4 && g[i][j] != 5 && g[i][j] != 6 && g[i][j] != 7 && g[i][j] != 8 && g[i][j] != 9){
                    conforme = false;
                }else{
                    somme++;
                }
            }
        }
        if (conforme == false || somme != 81){
            printf("\n Grille altérée, non conforme : En choisir une autre ! \n");
        }
    }while (conforme == false && somme != 81);

    printf("\nBonne chance !\n");
}

/** 
 * @fn void afficherGrille(tGrille g).
 * @brief Affiche la grille de Sudoku.
 * @param g Grille de Sudoku à afficher.
 *
 * Cette fonction affiche et met en forme le tableau de type tGrille pour un affichage meilleur et semblable à une vrai grille de Sudoku. 
 * La fonction utilise les fonctions nbElementsLigne et nbElementsColonne pour :
 *     - ajouter à l'affichage le nombre de cases non vides dans une ligne,
 *     - et ajouter à l'affichage le nombre de cases non vides dans une colonne.
 */
void afficherGrille(tGrille g){
    int i, j;

    printf("\n");
    printf("%3c", ' ');
    for (i = 1; i <= TAILLE; i++){
        printf("%3d", i);
        if (i == (N*0) || i == (N*1) || i == (N*2)){
            printf("%c", ' ');
        }
    }
    printf("\n");
    for (i = 0; i < TAILLE; i++){
        if (i == (N*0) || i == (N*1) || i == (N*2)){
            printf("%3c", ' ');
            printf("+---------+---------+---------+\n");
        }
        printf("%d", i+1);
        printf("%2c", ' ');
        for (j = 0; j < TAILLE; j++){
            if (j == (N*0) || j == (N*1) || j == (N*2)){
                printf("%c", '|');
            }
            if (g[i][j] == 0){
                printf("%s", " . ");
            }else{
                printf("%c%d%c", ' ',g[i][j],' ');
            }
        }
        printf("%c", '|');
        printf(" (%d)", nbElementsLigne(g, i));
        printf("\n");
    }
    printf("%3c", ' ');
    printf("+---------+---------+---------+\n");
    printf("%4c", ' ');
    for (i = 0; i < TAILLE; i++){
        if (i == N || i == (2*N) || i == (3*N)){
            printf("%c", ' ');
        }
        printf("(%d)", nbElementsColonne(g, i));
    }
    printf("\n\n");
}

/** 
 * @fn void saisir(int *S).
 * @brief Saisie d'un entier avec gestion des erreurs.
 * @param S Pointeur vers l'entier à saisir.
 * 
 * Cette fonction demande à l'utilisateur une saisie et vérifie s'il s'agit bien d'un entier entre 1 et 9,
 * retourne un message d'erreur si ce n'est pas le cas.
 */
void saisir(int *S){
    char ch[19];

    printf(": ");
    scanf("%s", ch);
    
    while(sscanf(ch, "%d", &(*S)) == 0 || strlen(ch) >= 2 || (*S < 1 || (N*N) < *S)){
        if (sscanf(ch, "%d", &(*S)) == 0){
            printf("\n Caractère non reconnu : Aucune valeur saisie ? \n\n");
            printf(": ");
            scanf("%s", ch);
        }else if (*S <= 0){
            printf("\n Valeur strictement positive ! \n\n");
            printf(": ");
            scanf("%s", ch);
        }else if (*S < 1 || (N*N) < *S){
            printf("\n Valeur comprise entre 1 et 9 ! \n\n");
            printf(": ");
            scanf("%s", ch);
        }else if (ch[1] == ',' || ch[1] == '.'){
            printf("\n Valeur entière essentiellement ! \n\n");
            printf(": ");
            scanf("%s", ch);
        }else{
            printf("\n Caractère non reconnu : Erreur de frappe ? \n\n");
            printf(": ");
            scanf("%s", ch);
        }
    }
}

/** 
 * @fn bool possible(tGrille g, int lig, int col, int val).
 * @brief Vérifie si une valeur peut être insérée dans une case de la grille.
 * @param g Grille de Sudoku.
 * @param lig Ligne de la case.
 * @param col Colonne de la case.
 * @param val Valeur à insérer.
 * @return true si l'insertion est possible, false sinon.
 * 
 * La fonction vérifie à l'aide de boucles 'pour' :
 *     - si la valeur 'val' n'est pas déjà présente dans la ligne 'lig' et dans la colonne 'col',
 *     - et si la valeur 'val' n'est pas déjà présente la sous-grille correspondante.
 */
bool possible(tGrille g, int lig, int col, int val){
    bool possible = true;
    int i, j;
    int ibloc, jbloc;

    ibloc = N*((lig-1)/N);
    jbloc = N*((col-1)/N);

    for (i=0; i < TAILLE; i++)
    {
        if (g[i][col-1] == val || g[lig-1][i] == val){
            printf("\n %d est DÉJÀ PRÉSENT dans la ligne/colonne ! \n", val);
            possible = false;
        }
    }

    for (i=ibloc; i < ibloc+N; i++){
        for (j=jbloc; j < jbloc+N; j++){
            if (g[i][j] == val){
                printf("\n %d est DÉJÀ PRÉSENT dans le bloc ! \n", val);
                possible = false;
            }
        
        }
    }

    return possible;
}

/** 
 * @fn bool gpleine(tGrille g).
 * @brief Vérifie si la grille est pleine.
 * @param g Grille de Sudoku.
 * @return true si la grille est pleine, false sinon.
 * 
 * La fonction parcourt le tableau 'g' de type tGrille et vérifie s'il reste des 0, si oui la fonction principale boucle.
 */
bool gpleine(tGrille g){
    int i = 0, j = 0;
    bool pleine = true;

    while (i < TAILLE && pleine == true){
        while (j < TAILLE && pleine == true){
            if (g[i][j] == 0){
                pleine = false;
            }
            j++;
        }
        j=0;
        i++;    
    }

    return pleine;
}

/** 
 * @fn int nbElementsLigne(tGrille g, int lig).
 * @brief Calcule le nombre d'éléments non nuls dans une ligne de la grille.
 * @param g Grille de Sudoku.
 * @param lig Ligne de la grille.
 * @see afficherGrille()
 * @return Le nombre d'éléments non nuls dans la ligne.
 * 
 * La fonction parcourt une ligne 'lig' dans la grille et compte le nombre de valeurs non nuls.
 */
int nbElementsLigne(tGrille g, int lig){
    int somme = 0;
    int i;

    for(i=0; i < TAILLE; i++){
        if(g[lig][i] != 0){
            somme++;
        }
    }

    return somme;
}

/** 
 * @fn int nbElementsColonne(tGrille g, int col).
 * @brief Calcule le nombre d'éléments non nuls dans une colonne de la grille.
 * @param g Grille de Sudoku.
 * @param col Colonne de la grille.
 * @see afficherGrille()
 * @return Le nombre d'éléments non nuls dans la colonne.
 * 
 * La fonction parcourt une colonne 'col' dans la grille et compte le nombre de valeurs non nuls.
 */
int nbElementsColonne(tGrille g, int col){
    int somme = 0;
    int i;

    for(i=0; i < TAILLE; i++){
        if(g[i][col] != 0){
            somme++;
        }
    }

    return somme;
}