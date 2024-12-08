#include "Headers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


int main(){
    int choix;
    FILE* FDrive,*FIDriver,*FDepense,*FIDepense,*FVoiture,*FIVoiture;
    FACTURE tarifs;
    VOITURE* voiture;DEPENSES* depenses;DRIVER* drive;

    int nbrDepenses,NbrDriver,nbVoiture;
    /*creerFichierDriver(&FDrive,&FIDriver);
    int nc=saisirEntier("le nombre des chauffeurs dans le parking");
    DRIVER* drv=creerTabDriver(nc);
    remplirTabDriver(drv,nc,tarifs,FDrive,FIDriver);
    afficherTabDriver(drv,nc);
    creerFichierDepenses(&FDepense,&FIDepense);
    printf("Voulez-vous savoir les depenses dans combien de jours ? \n");
    scanf("%d",&nbrDepenses);
    depenses=allocTabDep(nbrDepenses);
    remplirTabDepenses(depenses, nbrDepenses,FDepense,FIDepense);
    afficherLesDepenses(depenses,nbrDepenses);
    /*creerFichierVoiture(&FVoiture,&FIVoiture);
    nbVoiture=saisirEntier("le nombre des voitures dans le parking");
    VOITURE* v=creerTabVoiture(nbVoiture);
    remplirFichierVoiture(v,nbVoiture,FVoiture,FIVoiture,tarifs);
    printf("jjjjjjjjjjjjjjjjjjjj");
    afficherTabVoiture(v,nbVoiture);*/


    system("color 04");
    do {
        printf("\n====================================\n");
        printf("||          MENU Global        ||\n");
        printf("====================================\n");
        printf("  1 - Chargement \n");
        printf("  2 - Initialiser \n");
        printf("  3 - Quitter\n");
        printf("====================================\n");
        printf("Entrer votre choix (1-3) : ");
        scanf("%d", &choix);
        switch (choix) {
            case 1:
                system("color 05");
                Chargement(&FDrive,&FIDriver,&FDepense,&FIDepense,&FVoiture,&FIVoiture,&voiture,&depenses,&drive,&NbrDriver,&nbrDepenses,&nbVoiture);
                printf("%d",NbrDriver);
                afficherMenuPrincipal(&voiture,&nbVoiture,&drive, &NbrDriver, tarifs,&depenses,&nbrDepenses);
                break;
            case 2:
                system("color 01");
                Initialiser(FDrive,FIDriver,FDepense,FIDepense,FVoiture,FIVoiture,tarifs,voiture,depenses,drive,nbrDepenses,NbrDriver,nbVoiture);
                break;
            case 3:
                printf("\n Merci");
                break;

            default:
                printf("\nErreur : Choix invalide. Veuillez reessayer.\n");
        }
    } while (choix != 3);

return 0;
}
