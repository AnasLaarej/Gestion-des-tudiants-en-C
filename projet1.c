#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GREEN   "\033[1;32m"
#define RED     "\033[1;31m"
#define CYAN    "\033[1;36m"
#define YELLOW  "\033[1;33m"
#define RESET   "\033[0m"

typedef struct etudiant {
    int id;
    char nom[50];
    float moyenne;
} etudiant;

void ajouter(FILE *f) {
    etudiant e;
    printf(GREEN "\n╔══════════════════════════════╗\n");
    printf("║      AJOUTER UN ÉTUDIANT      ║\n");
    printf("╚══════════════════════════════╝\n" RESET);
    printf(YELLOW "ID       : " RESET);
    scanf("%d", &e.id);
    printf(YELLOW "Nom      : " RESET);
    scanf("%s", e.nom);
    printf(YELLOW "Moyenne  : " RESET);
    scanf("%f", &e.moyenne);
    fprintf(f, "%d %s %.2f\n", e.id, e.nom, e.moyenne);
    fflush(f);
    printf(GREEN "✅ Étudiant ajouté avec succès !\n" RESET);
}

void afficher(FILE *f) {
    etudiant e;
    rewind(f);
    printf(CYAN "\n╔════════════════════════════════════════════╗\n");
    printf("║           LISTE DES ÉTUDIANTS              ║\n");
    printf("╚════════════════════════════════════════════╝\n" RESET);
    while (fscanf(f, "%d %s %f", &e.id, e.nom, &e.moyenne) == 3) {
        printf("🧾 ID: %d | Nom: %s | Moyenne: %.2f\n", e.id, e.nom, e.moyenne);
    }
}

void supprimer() {
    FILE *f = fopen("donnee.txt", "r");
    if (f == NULL) {
        printf(RED "❌ Erreur lors de l'ouverture du fichier.\n" RESET);
        return;
    }

    FILE *temp = fopen("temp.txt", "w");
    if (temp == NULL) {
        printf(RED "❌ Erreur lors de la création du fichier temporaire.\n" RESET);
        fclose(f);
        return;
    }

    etudiant e;
    int idsupp, trouve = 0;

    printf(YELLOW "\nID de l'étudiant à supprimer : " RESET);
    scanf("%d", &idsupp);

    while (fscanf(f, "%d %s %f", &e.id, e.nom, &e.moyenne) == 3) {
        if (e.id != idsupp) {
            fprintf(temp, "%d %s %.2f\n", e.id, e.nom, e.moyenne);
        } else {
            trouve = 1;
        }
    }

    fclose(f);
    fclose(temp);
    remove("donnee.txt");
    rename("temp.txt", "donnee.txt");

    if (trouve)
        printf(GREEN "🗑️ Étudiant supprimé avec succès.\n" RESET);
    else
        printf(RED "⚠️ ID non trouvé.\n" RESET);
}

int main() {
    system("chcp 65001 > nul");
    FILE *f = fopen("donnee.txt", "a+");
    const char *nomfichier;
    if (f == NULL) {
        printf(RED "❌ Erreur lors de l'ouverture du fichier.\n" RESET);
    } else {
        printf(GREEN "📂 Fichier ouvert avec succès.\n" RESET);
    }

    int choix;
    do {
        printf(CYAN "\n╔══════════════════════════════╗\n");
        printf("║           MENU               ║\n");
        printf("╠══════════════════════════════╣\n");
        printf("║ 1. Ajouter un étudiant       ║\n");
        printf("║ 2. Afficher les étudiants    ║\n");
        printf("║ 3. Supprimer un étudiant     ║\n");
        printf("║ 0. Quitter                   ║\n");
        printf("╚══════════════════════════════╝\n" RESET);
        printf(YELLOW "Votre choix : " RESET);
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                ajouter(f);
                break;
            case 2:
                afficher(f);
                break;
            case 3:
                fclose(f);
                supprimer();
                f = fopen("donnee.txt", "a+");
                break;
            case 0:
                printf(GREEN "\n👋 Au revoir et bonne journée !\n" RESET);
                break;
            default:
                printf(RED "❌ Choix invalide !\n" RESET);
        }
    } while (choix != 0);

    fclose(f);
}
