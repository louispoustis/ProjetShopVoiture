#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAILLE 50           // Definie la taille d'une ligne
#define PR 15              // Definie la quantite de voiture 
#define MAX 40            // Definie la taille max du stokage
#define CL 5            

struct client{               //structure client   
    char nom[TAILLE];
    char prenom[TAILLE];
    char achat[TAILLE];
    char fichier[TAILLE];
};

struct voiture{             //structure voiture
    char nom[TAILLE];
    int reference;
    int prix;
    int quantite;
    int taille;
    char fichier[TAILLE];
};

int recherche(const char* fp, const char* nom){         //fonction qui permet de chercher si un nom est present dans un des fichiers
    FILE* f = fopen(fp,"r");
    if (f == NULL){
        printf("Le fichier texte n'a pas pu etre ouvert\n"); // si l'ouverture du fichier c'est mal passer
        return 0;
    }
    char ligne[TAILLE];
    int p = 1;
    while (fgets(ligne,sizeof(ligne),f) != NULL) {         //boucle qui va prendre une ligne a chaque fois dans le fichier jusqu'a ce qu'il n' y a plus de caractere 
        ligne[strcspn(ligne, "\n")] = '\0';
        if (strcmp(ligne, nom) == 0) {                //strcmp compare la ligne et nom et renvoie 0 si il ya ressemblance
            printf("Le nom '%s' a ete trouve dans le fichier.\n", nom);
            fclose(f);
            return p;
        }
        p++;
    }
    printf("Le nom '%s' n'a pas ete trouve dans le fichier.\n", nom);
    fclose(f);
    return 0;
}
void rempStruct(struct client voit[], int t, const char* fp) {          // procédure pour remplir un tableau de de strcture clients avecles donnes d'un fichiers 
    FILE * f;
    f = fopen(fp, "r");
    if (f == NULL) {
        printf("Le fichier texte n'a pas pu être ouvert\n");
        return;
    }
    char ligne[TAILLE];
    for (int i = 0; i < t; i++) {                                   // boucle pour recuperer les structures clients dans le tableau
        if (fgets(ligne, sizeof(ligne), f) != NULL) {
            strcpy(voit[i].nom, ligne);                             // strcpy va copier dans la partie nom de la structure la ligne du fichier
            voit[i].nom[strlen(voit[i].nom) - 1] = '\0';           // remplace le dernier caractere de voit[i].nom qui par '\0' pour marquer la fin du nom 
        }
        if (fgets(ligne, sizeof(ligne), f) != NULL) {
            strcpy(voit[i].prenom, ligne);                        
            voit[i].prenom[strlen(voit[i].prenom) - 1] = '\0';
        }
        if (fgets(ligne, sizeof(ligne), f) != NULL) {
            strcpy(voit[i].achat, ligne);
            voit[i].achat[strlen(voit[i].achat) - 1] = '\0';
        }
        if (fgets(ligne, sizeof(ligne), f) != NULL) {
            strcpy(voit[i].fichier, ligne);
            voit[i].fichier[strlen(voit[i].fichier) - 1] = '\0';
        }
        fgets(ligne, sizeof(ligne), f);
    }
    fclose(f);
}

void remplirStruct(struct voiture voit[], int t, const char* fp) {      //procedure pour remplir un tableau de structure de voiture avec des donnees d'un fichier
    FILE * f;
    f = fopen(fp, "r");
    if (f == NULL) {
        printf("Le fichier texte n'a pas pu être ouvert\n");
        return;
    }

    char ligne[30];
    for (int i = 0; i < t; i++) {
        if (fgets(ligne, sizeof(ligne), f) != NULL) {
            strcpy(voit[i].nom, ligne);
            voit[i].nom[strlen(voit[i].nom) - 1] = '\0';
        }

        if (fgets(ligne, sizeof(ligne), f) != NULL) {
            voit[i].reference = atoi(ligne);
        }

        if (fgets(ligne, sizeof(ligne), f) != NULL) {
            voit[i].prix = atoi(ligne);
        }

        if (fgets(ligne, sizeof(ligne), f) != NULL) {
            voit[i].quantite = atoi(ligne);
        }

        if (fgets(ligne, sizeof(ligne), f) != NULL) {
            voit[i].taille = atoi(ligne);
        }

        if (fgets(ligne, sizeof(ligne), f) != NULL) {
            strcpy(voit[i].fichier, ligne);
            voit[i].fichier[strlen(voit[i].fichier) - 1] = '\0';
        }
        fgets(ligne, sizeof(ligne), f);                             // saute un ligne vide du fichier
    }

    fclose(f);
}

void StockBas(struct voiture produits[], int taille) {         // procedure qui permet de trier le tablau de structure voiture par sa quantite et affiche les voiturees vides ainsi que les 5 premieres voitures dont la quantite est la plus basses
    printf("Attention ceci sont les produits avec les stocks les plus bas ou vide :\n");
    int a = 0;            // servira a compter le nombre de voiture a quantite 0
    int i , j;
    for (i = 0; i < taille - 1; i++) {                 // Ceci est tri a bulle 
        for (j = 0; j < taille - i - 1; j++) {
            if (produits[j].quantite > produits[j + 1].quantite) { // on compare deux elements du tableaux  
                struct voiture temp = produits[j];     // stocke la structure la plus grande
                produits[j] = produits[j + 1];        // echange de place 
                produits[j + 1] = temp;
            }
        }
    }
    for (i = 0; i < taille - 1; i++) {           //  affiche les donnees des voitures dont la quantite est a 0
        if (produits[i].quantite == 0){
            a = a + 1;
            printf("Nom: %s, Reference: %d, Quantite: %d, Prix: %d, Taille: %d\n", produits[i].nom, produits[i].reference, produits[i].quantite, produits[i].prix, produits[i].taille);
        }
    }
    for (int i = a; i < a + 5; i++) {           // affiche les donnees des 5 autres voitures dont le stockese est le blus bas
         printf("Nom: %s, Reference: %d, Quantite: %d, Prix: %d, Taille: %d\n", produits[i].nom, produits[i].reference, produits[i].quantite, produits[i].prix, produits[i].taille);
    }
    printf("\n");
}

void afficher(struct voiture produits[], int nbProduits) {      // procedure pour   afficher les voitures du magasin
    printf("Liste des produits :\n");
    for (int i = 0; i < nbProduits; i++) {
        printf("Produit %d\n", i + 1);                        // decompte le nombre de produits
        printf("Nom : %s\n", produits[i].nom);
        printf("Reference : %d\n", produits[i].reference);
        printf("Quantite en stock : %d\n", produits[i].quantite);
        printf("Prix : %d\n", produits[i].prix);
        printf("Taille : %d\n", produits[i].taille);
        printf("\n");
    }
}
void aff(struct voiture produits[], int nbProduits) {       // procedure pour le choix de voiture qu'on va acheté
    printf("Liste des voitures :\n");
    for (int i = 0; i < nbProduits; i++) {
        printf("Produit %d\n", i + 1);
        printf("Nom : %s\n", produits[i].nom);
        printf("Reference : %d\n", produits[i].reference);
        printf("\n");
    }
}

void affiche(struct client produits) {              // procedure pour afficher les donnees du clients 
        printf("Nom : %s\n", produits.nom);
        printf("Prenom : %s\n", produits.prenom);
        printf("Achat precedent : %s\n", produits.achat);
        printf("\n");

}

struct voiture stock(struct voiture produits[],const char * nom, int reference){        // stock va renvoie la voiture correspondant au nom ou a la reference
    for (int i = 0; i < PR; i++) {
        if (strcmp(produits[i].nom, nom) == 0){
            return produits[i];
        }
        else if (produits[i].reference == reference) {
            return produits[i];
        }
    }
    printf("Ce produit n'est pas valide ou a ete mal orthographier\n");
}

void placerestante(struct voiture produits[], int max){      // la fonction sert a calculer et  afficher le nombre de place restante dans le stockage
    int capacite = 0;
    for (int i = 0; i < PR; i++) {
        capacite = capacite + (produits[i].taille * produits[i].quantite);  // Incremente capacite avec la taille qui est multiplier par la quantite d'une voiture
    }
    printf("Il reste que %d place libre dans le stockage\n", (max - capacite));
}

int capacite(struct voiture produits[], int max , int ajout){     // Procedure servant a connaitre si une voiture peut etre ajouter au stokage  
    int capacite = 0;
    int quantit = 0;
    for (int i = 0; i < PR; i++) {         
        capacite = capacite + (produits[i].taille * produits[i].quantite);
        quantit = quantit + produits[i].quantite;
    }
    printf("%d\n", capacite);              
    if (capacite + ajout > max){                             // conditions pour savoir si il reste de la place dans le stokage limite 
        printf("L'ajout du produit est refuser\n");
        return 0;
    }
    else {
        printf("L'ajout d'un produit est accepter\n");
        return 1;
    }
}

void supprimerLigne(const char* fp, int numeroLigne) {       // Permet de supprimer une ligne dans un fichier 
    FILE* f = fopen(fp, "r");                                 // Ouvre le ficher fp
    if (f == NULL) {
        printf("Le fichier texte n'a pas pu être ouvert\n");
        return;
    }
    FILE* temp = fopen("fichier.txt", "w");                 // Cree un fichier temporaire qui va acceuillir le fichier avec la ligne supprimer 
    if (temp == NULL) {
        printf("Erreur lors de la creation du fichier temporaire\n");
        return;
    }

    char ligne[100];
    int compteurLignes = 1;
    while (fgets(ligne, sizeof(ligne), f) != NULL) {               // Boucle pour obtenir la ligne a supprimer
        if (compteurLignes != numeroLigne) {
            fputs(ligne, temp);                         // fputs va envoyer les ligne du  fichier fp dans celle du fichier temp sauf celle de la ligne a supprimer
        }
        compteurLignes++;
    }

    fclose(f);             // ferme le fichier
    fclose(temp);

    remove(fp);          // efface l'ancien fichier fp
    rename("fichier.txt", fp);  // renome le fichier temporaire par le nom fp
}

void modifierLigne(const char* nomFichier, int numeroLigne, const char* nouvelleLigne) {  // Modifie la ligne du fichier en parametre
    FILE* fichierOrigine = fopen(nomFichier, "r");
    FILE* fichierTemporaire = fopen("fichier.txt", "w");

    if (fichierOrigine == NULL || fichierTemporaire == NULL) {
        printf("Erreur lors de l'ouverture des fichiers.\n");
        return;
    }

    char ligne[256];
    int compteurLigne = 1;

    while (fgets(ligne, sizeof(ligne), fichierOrigine) != NULL) {
        if (compteurLigne == numeroLigne) {                      
            fprintf(fichierTemporaire, "%s\n", nouvelleLigne);  // remplace la ligne equivalent au numero de ligne en parametre par la nouvelle ligne 
        } else {
            fprintf(fichierTemporaire, "%s", ligne);
        }

        compteurLigne++;
    }

    fclose(fichierOrigine);
    fclose(fichierTemporaire);

    remove(nomFichier);
    rename("fichier.txt", nomFichier);
}

void restokage(struct voiture produits[], struct voiture ajout, int r){    // Fonction qui sert à modifier les fichiers et à augmanter la quantité d'un produit dans la structure et dans le fichier du produit
    if (r == 1){
        for (int i = 0; i < PR; i++) {
            if (strcmp(produits[i].nom, ajout.nom) == 0){
                produits[i].quantite = produits[i].quantite + 1;
                char s[TAILLE];
                sprintf(s, "%d", produits[i].quantite);
                modifierLigne(produits[i].fichier,recherche(produits[i].fichier,produits[i].nom)+3,s);
                modifierLigne("stokage.txt",recherche("stokage.txt",produits[i].nom)+3,s);
                printf("Le restokage est reussi");
            }
        }
    }
    placerestante(produits,MAX);
}

void choixderecherche(struct voiture produits[]){  // Fonction permettant de choisir entre une recherche par nom ou par référence pour le restockage
    int a = 0;
    printf ("Veillez choisir si cest nom ou si cest une reference que vous souhaiter utiliser pour la recherche\n");
    struct voiture p;
    while (a == 0){
        printf ("taper 1 pour le nom et taper 2 pour la reference\n");
        scanf("%d", &a);
        if (a == 1){
            char nom[TAILLE];
            printf("Saisir le nom du produit\n");
            scanf(" %[^\n]", nom);
            p = stock(produits, nom, 0);
            printf("On a possede %d %s en stocke\n", p.quantite, p.nom);
        }
        else if (a == 2){
            int ref;
            printf("Saisir la reference du produit\n");
            scanf("%d",&ref);
            p = stock(produits," ",ref);
            printf("On a possede %d %s en stocke\n", p.quantite, p.nom);
        }
        else {
            a = 0;
        }
    }
}

void choireche(struct voiture produits[]){
    int a = 0;
    struct voiture n;
    int w;
    printf ("Veillez choisir si cest un nom ou si cest une reference que vous souhaiter utiliser pour la recherche\n");
    while (a == 0){
        printf ("taper 1 pour le nom et taper 2 pour la reference\n");
        scanf("%d", &a);
        if (a == 1){
            char nom[TAILLE];
            printf("Saisir le nom du produit\n");
            scanf(" %[^\n]", nom);
            n = stock(produits, nom, 0);
            w = capacite(produits, MAX,n.taille);
            restokage(produits,n,w);
        }
        else if (a == 2){
            int ref;
            printf("Saisir la reference du produit\n");
            scanf("%d",&ref);
            n = stock(produits," ",ref);
            w = capacite(produits,MAX,n.taille);
            restokage(produits,n,w);
        }
        else {
            a = 0;
        }

    }
}

void deinscrire(struct client cli,const char* nom,const char* prenom){
    if (strcmp(cli.nom, nom) == 0 && strcmp(cli.prenom,prenom)==0){
        remove(cli.fichier);
        int n = recherche("ClientGestion.txt",cli.nom);
        for(int j=0;j<=4;j++){
            supprimerLigne("ClientGestion.txt",n + 1);
        }
        printf("La deinscription est reussi");
        return;
    }
    printf("La deinscription a echouer. Le nom est il correct ?\n");
    printf("%s\n",nom);
}

void choixp(struct client cli,struct voiture voit[]){
    int a = 0;
    int n = 0;
    while (a == 0){
        printf ("Veillez indiquer ce que vous souhaiter faire\n");
        printf ("1. recherche une autre voiture par un affichage de nos produits\n");
        printf ("2 Se Deinscrire\n");
        scanf("%d", &a);
        if (a == 1){
            afficher(voit,PR);
        }
        else if (a == 2){
            char nom[TAILLE];
            char prenom[TAILLE];
            printf("Saisir le nom : ");
            scanf("%s", nom);
            printf("Saisir le prenom : ");
            scanf("%s", prenom);
            deinscrire(cli,nom,prenom);
        }
        else {
            n = 0;
        }
    }
}

int achat(struct voiture produits[],struct client cli,const char* nom){
    for (int i = 0; i < PR; i++) {
        if (strcmp(produits[i].nom, nom) == 0){
                if (produits[i].quantite == 0){
                    printf("Nous sommes vraiment desole mais ce produit est completement epuiser\n");
                    choixp(cli,produits);
                    return 0;
                }
            produits[i].quantite = produits[i].quantite - 1;
            char s[TAILLE];
            sprintf(s, "%d", produits[i].quantite);
            modifierLigne(produits[i].fichier,recherche(produits[i].fichier,produits[i].nom)+3,s);
            modifierLigne("stokage.txt",recherche("stokage.txt",produits[i].nom)+3,s);
            printf("L'achat est reussi\n");
            return produits[i].prix;
        }
    }
    printf("L'achat a echouer le nom n'est pas valide ?\n%s\n",nom);
}

void ajouteachat(struct client cli, const char* nom){
    strcpy(cli.achat, nom);
}

void parcours(struct voiture voit[]){
    int a = 0;
    int n = 0;
    while (a == 0){
        printf ("Veillez indiquer ce que vous souhaiter\n");
        printf ("1. recherche une voiture precise\n");
        printf ("2 voir nos gammes de voitures\n");
        scanf("%d", &a);
        if (a == 1){
            while (n == 0){
                printf("1. Saisir le nom du de la voiture si possible\n");
                printf("2. Dans le cas ou vous ne connaissez pas le nom du vehicule une option sera ajouter\n");
                scanf("%d",&n);
                if (n == 1){
                    choixderecherche(voit);
                }
                else if (n == 2){
                    aff(voit,PR);
                }
                else {
                    n = 0;
                }
            }
        }
        else if (a == 2){
            printf("Ici a Toyota nous vendons 4 gammes de voitures au choix et selon vos envies\n");
            printf("1. Gamme Hybrides\n");
            printf("2. Gamme Sport\n");
            printf("3. Gamme Utilitaire\n");
            printf("4. Gamme Familiales\n");

        }
        else {
            a = 0;
        }
    }
}

void comptePrix(struct voiture voit[],struct client cli,int a){
    int res = a;
    int n = 0;
    while (n == 0){
        printf("Que voulez vous faire\n");
        printf("1. Ajouter un autre achat !\n");
        printf("2. voir le montant de votre achat\n");
        scanf("%d", &n);
        if (n == 1){
            char nom[TAILLE];
            int r;
            printf("Taper le nom du vehicule je vous prie pour valider l'achat\n");
            scanf(" %[^\n]", &nom);
            r = achat(voit,cli,nom);
            if (r!=1){
                ajouteachat(cli,nom);
            }
            res = res + r;
            n = 0;
        }
        else if (n == 2){
            printf("Vos achat couteras %d euros\n",res);
            return;
        }
        else {
            n = 0;
        }
    }
}

void clientOp(struct voiture voit[],struct client cli){
    int n = 0;
    while (n == 0){
        printf("Que nous faut cette viste\n");
        printf("1. Faire un achat !\n");
        printf("2. Parcourir notre Magasin !\n");
        printf("3. Se deconnecter\n");
        scanf("%d", &n);
        if (n == 1){
            char nom[TAILLE];
            int r;
            printf("Taper le nom du vehicule je vous prie pour valider l'achat\n");
            scanf(" %[^\n]", &nom);
            r = achat(voit,cli,nom);
            if (r!=1){
                ajouteachat(cli,nom);
            }
            comptePrix(voit,cli,r);
            n = 0;
        }
        else if (n == 2){
            parcours(voit);
            n = 0;
        }
        else if (n == 3){
             return;
        }
        else {
            n = 0;
        }
    }
}


void clientIns(struct client cli[], struct voiture v[]){
    int n = 0;
    int a = 0;
    char nom[TAILLE];
    char prenom[TAILLE];
    printf("Bon retour parmi nous!\n Pour plus d' option veuillez vous connecter.\n");
    while (n==0){
        printf("Saisir le nom :");
        scanf("%s", &nom);
        printf("Prenom :");
        scanf("%s", &prenom);
        for(int i = 0; i < 5 ; i++) {
            if (strcmp(cli[i].nom, nom) == 0 && strcmp(cli[i].prenom, prenom) == 0){
                printf(" Voici vos donnes !\n");
                affiche(cli[i]);
                n = 1;
                a = 1;
                clientOp(v, cli[i]);
            }
            else {
                n = 0;
            }
        }
        if (a != 1){
            printf ("la saisie est errone, ces informations n'est pas dans notre base de donnees\n Reessayer\n");
            n = 0;
        }
    }
}

void Nouvclient(struct client cli[],struct voiture v[]){
    char nom[TAILLE];
    char prenom[TAILLE];
    printf("Bienvenue parmi nous!\nPour plus d'option veuillez vous inscrire.\n Nom :");

    FILE* fichier;
    fichier = fopen("Client5.txt", "w");

    printf("Saisir le nom : ");
    scanf("%s", nom);
    fprintf(fichier, "%s\n", nom);

    printf("Saisir le prenom : ");
    scanf("%s", prenom);
    fprintf(fichier, "%s\n", prenom);

    fclose(fichier);
    FILE* f;
    f = fopen("ClientGestion.txt", "a");
    fprintf(f, "\n%s\n", nom);
    fprintf(f, "%s\n", prenom);
    fprintf(f,"\n");
    fprintf(f, "%s\n", "Client5.txt");

    fclose(f);
    struct client clit;
    strcpy(clit.nom, nom);
    strcpy(clit.prenom, prenom);
    clit.achat[0] = '\0';
    strcpy(clit.fichier, "Client5.txt");
    clientOp(v,clit);
}

void modeGestion(struct voiture v[]) {
    int n = 0;
    StockBas(v,PR);
    placerestante(v, MAX);
    printf ("Que desiriez vous donc entreprendre ?\n");
    while (n == 0){
        printf ("Que desiriez vous donc entreprendre ?\n");
        printf ("1. souhaiter vous voir les produits\n");
        printf ("2. souhaiter vous connaitre la quantite d'un produit\n");
        printf ("3. souhaiter vous augmenter le stokage\n");
        printf ("4. Quitter\n");
        scanf("%d",&n);

        if (n == 1){
            afficher(v,PR);
            n = 0;
        }
        else if (n == 2){
            choixderecherche(v);
            n = 0;
        }
        else if (n == 3){
            printf("quel produits souhaiter vous ajouter\n");
            choireche(v);
            n = 0;
        }
        else if (n == 4){
            return;
        }
        else {
            n = 0;
        }
    }
}

void modeAchat(struct voiture v[],struct client cli[]) {
    int choix = 0;
    while (choix == 0){
        printf("Veuillez indiquer si faites partie de la grande famille de TOYOTA :\n");
        printf("1. Vous etes un membre\n");
        printf("2. Nouveau client\n");
        printf("3. Quiter\n");
        printf("Votre choix : ");
        scanf("%d", &choix);

        if (choix == 1){
            clientIns(cli, v);
            choix = 0;
        }
        else if (choix == 2){
            Nouvclient(cli, v);
            choix = 0;
        }
        else if (choix == 3){
            return;
        }
        else {
            choix = 0;
        }
    }
}

void debut(){
    struct client cli[CL];
    rempStruct(cli, CL, "clientGestion.txt");
    int n = 0;
    struct voiture v[PR];
    remplirStruct(v,PR,"stokage.txt");
    int choix = 0;
    while (choix == 0){
        printf("Veuillez choisir le mode :\n");
        printf("1. Mode gestion\n");
        printf("2. Mode achat\n");
        printf("3. Quiter\n");
        printf("Votre choix : ");
        scanf("%d", &choix);

        if (choix == 1){
            printf ("Bienvenue dans le Mode Gestion !\n");
            modeGestion(v);
        }
        else if (choix == 2){
            printf ("Bienvenue dans le Mode Achat !\n");
            modeAchat(v,cli);
        }
        else if (choix == 3){
            return;
        }
        else {
            choix = 0;
        }
    }
}

int main() {
    printf("Nous vous souhaitons la bienvenue dans le Magasin TOYOTA\n");
    printf("Mais avant\n");
    debut();
    printf("Merci d'avoir visiter nos services et a la prochaine !\n");
    return 0;
}
