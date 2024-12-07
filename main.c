#include "Headers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int main(){
    int choix;
    FILE* FDrive,*FIDriver,*FDepense,*FIDepense,*FVoiture,*FIVoiture;
    FACTURE tarifs=saisirTarifs();
    VOITURE* voiture;DEPENSES* depenses;DRIVER* drive;
    int nbrDepenses,NbrDriver,nbVoiture;
    /*creerFichierDriver(&FDrive,&FIDriver);
    int nc=saisirEntier("le nombre des chauffeurs dans le parking");
    DRIVER* drv=creerTabDriver(nc);
    remplirTabDriver(drv,nc,tarifs,FDrive,FIDriver);
    afficherTabDriver(drv,nc);*/

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
                OpenFichierDriver(&FDrive,&FIDriver);
                afficherFichierIndex(FIDriver);
                NbrDriver=NombreDeElemetnFichierIndex(FIDriver);
                printf("dddddddddddddddd %d",NbrDriver);
                drive=creerTabDriver(NbrDriver);
                copierFichierDriverDansTableau(FDrive,FIDriver,drive,NbrDriver);
                afficherTabDriver(drive,NbrDriver);
                //Chargement(&FDrive,&FIDriver,&FDepense,&FIDepense,&FVoiture,&FIVoiture,&voiture,&depenses,&drive,&NbrDriver,&nbrDepenses,&nbVoiture);
                //afficherMenuPrincipal(voiture,nbVoiture,drive, NbrDriver, tarifs,depenses,nbrDepenses);
                break;
            case 2:
                system("color 01");
                //Initialiser();
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
