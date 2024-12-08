#ifndef HEADERS_H_INCLUDED
#define HEADERS_H_INCLUDED
#include<stdio.h>
#include <stdbool.h>
//headers.h
struct position{
    int etage;
    char bloc;
};
typedef struct position POSITION;


struct facture{
    float prix_normal;
    int remise_abonne;
    int tarif_nuit;
    float montant;
};
typedef struct facture FACTURE ;

struct date{
    int jour;
    int mois;
    int annee;
};
typedef struct date DATE;

struct driver {
    char nom[50];
    int id;
    bool a; //abonné ou pas
    FACTURE fac;
    int nbr_dates;
    DATE* dates;
};
typedef struct driver DRIVER;

struct personnel {
    char nom[50];
    int id;
    int salaire ;
    int nbr_position;
    POSITION* pos;//lieu de travail(bloc et étage)
};
typedef struct personnel PERSONNEL;

struct temps{
    int h;
    int mins;
    int sec;
    bool jn; //jour ou nuit
    };
typedef struct temps TEMPS;

struct depenses{
    int id;
    int nbrperso;
    PERSONNEL *personnel;//la calculer
    int salaires;
    int electricite ;
    int taxes;
    int maintenance[3];// [nettoyage ventilation; reparation]
};
typedef struct depenses DEPENSES;

struct voiture {
    int matricule;
    POSITION position;
    TEMPS tempsentree;
    TEMPS tempssortie;
    DATE date;
    int nbr_drivers;
    DRIVER* drv;
    FACTURE tarif;
};

typedef struct voiture VOITURE;

struct resultat{
    TEMPS duree;
    VOITURE mat;
};
typedef struct resultat RESULTAT;


int saisirEntier(char variable[]);
float saisirReel(char variable[]);
TEMPS calculerDuree(TEMPS, TEMPS);
int calculerSalaires(PERSONNEL*,int);
int sommeDepense(int,int,int,int,int,int);
//DEPENSES saisirDepenses();
void afficherDepenses(DEPENSES*);
float calculerFacture(float,int,int);
FACTURE saisirTarifs();
FACTURE remplirFacture(FACTURE,DRIVER);
void afficherFacture(FACTURE);
DRIVER saisirDriver(FACTURE);
void afficherDriver(DRIVER);
DRIVER* creerTabDriver(int);
void remplirTabDriver(DRIVER*,int,FACTURE,FILE*,FILE*);
void afficherTabDriver(DRIVER* drv, int x);
void trierDriverParFacture(DRIVER*, int);
void recherchedrivermatricule(struct voiture*, int, int);
POSITION remplirPosition();
void afficherPosition(struct position);
TEMPS donnerTemps(char variable[]);
void afficherTemps(TEMPS,char variable[]);
VOITURE saisirVoiture();
void afficherVoiture(VOITURE);
VOITURE* creerTabVoiture(int);
void remplirTabVoiture(VOITURE*, int,FACTURE );
void afficherTabVoiture(VOITURE*, int);
PERSONNEL saisirPerso();
void afficherPerso(PERSONNEL);
PERSONNEL* creerTabPerso(int);
void remplirTabPerso(PERSONNEL*, int);
void afficherTabPerso(PERSONNEL*, int);
DATE saisirDate();
void afficherDate(DATE);

#endif // HEADERS_H_INCLUDED



//mainnnnnn
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


//header.c
#include "Headers.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

int saisirEntier(char variable[]){
	int x;
	printf("\nSaisir %s :\n",variable);
	scanf("%d",&x);
	return x;
}

float saisirReel(char variable[]){
    float x;
    printf("\nSaisir %s :\n",variable);
	scanf("%f",&x);
	return x;
}

POSITION remplirPosition() {
    POSITION pos;
    printf("Donner l'etage: \n");
    scanf("%d", &pos.etage);
    getchar();
    printf("Donner le bloc: \n");
    scanf("%c", &pos.bloc);
    return pos;
}

void afficherPosition(struct position pos) {
    printf("La position est : [etage:%d|bloc:%c] \n", pos.etage,pos.bloc);
}

TEMPS donnerTemps(char variable[]){
    TEMPS t;
    int t1, t2, t3, t4, t5, t6;
    while (true) {
        printf("Entrez le temps de %s [heure:minutes:secondes]\n",variable);
        scanf("%d", &t1);
        scanf("%d", &t2);
        scanf("%d", &t3);
        if (t1 >= 0 && t1 <= 23 && t2 >= 0 && t2 <= 59 && t3 >= 0 && t3 <= 59)
            break;
        else
            printf("l'heure entre 00h et 23h; les minutes entre 00 et 59; les secondes entre 00 et 59\n");
    }
    t.h=t1;
    t.mins=t2;
    t.sec=t3;

    return t;
}

void afficherTemps(TEMPS t,char variable[]){
    printf("Le temps de %s est: [%d:%d:%d]\n", variable,t.h,t.mins,t.sec);
}

TEMPS calculerDuree(TEMPS t1, TEMPS t2){
    TEMPS d;
    int total_seconds = (t2.h - t1.h) * 3600 + (t2.mins - t1.mins) * 60 + (t2.sec - t1.sec);
    if (total_seconds < 0) total_seconds += 24 * 3600;

    d.h = total_seconds / 3600;
    d.mins = (total_seconds % 3600) / 60;
    d.sec = total_seconds % 60;

    return d;
}

VOITURE saisirVoiture(FACTURE tarifs){
    VOITURE v;
    printf("------------------------------------\n");
    int nbr_driveres;
    printf("donner le nombre des proprietaires du voiture \n");
    scanf("%d",&nbr_driveres);
    DRIVER* driver=creerTabDriver(nbr_driveres);
    for(int i=0;i<nbr_driveres;i++){
        *(driver+i)=saisirDriver(tarifs);
    }
    v.drv=driver;
    v.nbr_drivers=nbr_driveres;
    v.matricule=saisirEntier("La matricule de la voiture");
    v.position=remplirPosition();
    v.tempsentree=donnerTemps("entree");
    v.tempssortie=donnerTemps("sortie");
    return v;
}

void afficherVoiture(VOITURE v){
    printf("------------------------------------\n");
    afficherTabDriver(v.drv,v.nbr_drivers);
    printf("La matricule de la voiture est: %d\n",v.matricule);
    afficherPosition(v.position);
    afficherTemps(v.tempsentree,"entree");
    afficherTemps(v.tempssortie,"sortie");


}
VOITURE* creerTabVoiture(int x){
	VOITURE* v;
	v=(VOITURE*) malloc (x * sizeof(VOITURE));
	if(!v) exit(-1);
	return v;
}

DATE* AllocTabDate(int x){
	DATE* d;
	d=(DATE*) malloc (x * sizeof(DATE));
	if(!d) exit(-1);
	return d;
}

POSITION* AllocTabPosition(int x){
	POSITION* p;
	p=(POSITION*) malloc (x * sizeof(POSITION));
	if(!p) exit(-1);
	return p;
}

void remplirTabVoiture(VOITURE* v, int x,FACTURE tarifs){
    for(int i=0; i<x; i++){
        printf("\n||| Voiture num %d |||\n",i+1);
        *(v+i)=saisirVoiture(tarifs);
        afficherVoiture(*(v+i));
    }
}

void afficherTabVoiture(VOITURE* v, int x){
    printf("\n**********************************************\n");
    for(int i=0; i<x; i++){
        printf("\n||| Voiture num %d |||\n",i+1);
        afficherVoiture(*(v+i));
    }
}

PERSONNEL saisirPerso(){
    PERSONNEL perso;
    printf("------------------------------------\n");
    printf("\nDonner le nom du personnel:\n");
    scanf("%s",&perso.nom);
    perso.id=saisirEntier("La CIN du personnel");
    perso.salaire=saisirEntier("Le salaire du personnel");

    int nbPosition=saisirEntier("le nombre de potion");
    POSITION* pos=AllocTabPosition(nbPosition);
    for(int i=0;i<nbPosition;i++){
        *(pos+i)=remplirPosition();
    }
    perso.nbr_position=nbPosition;
    perso.pos=pos;
    return perso;
}

void afficherPerso(PERSONNEL perso){
    printf("------------------------------------\n");
    printf("Le nom du personnel est: %s\n",perso.nom);
    printf("La CIN du personnel est: %d\n",perso.id);
    printf("Le salaire du personnel est: %d\n",perso.salaire);
    for(int  i=0;i<perso.nbr_position;i++){
        afficherPosition(*(perso.pos+i));
    }
}

PERSONNEL* creerTabPerso(int x){
	PERSONNEL* perso;
	perso=(PERSONNEL*) malloc (x * sizeof(PERSONNEL));
	if(!perso) exit(-1);
	return perso;
}

DEPENSES* allocTabDep(int x){
	DEPENSES* dep;
	dep=(DEPENSES*) malloc (x * sizeof(DEPENSES));
	if(!dep) exit(-1);
	return dep;
}

void remplirTabPerso(PERSONNEL* perso, int x){
    for(int i=0; i<x; i++){
        printf("\n||| Personnel num %d |||\n",i+1);
        *(perso+i)=saisirPerso();
    }
}

void afficherTabPerso(PERSONNEL* perso, int x){
    printf("\n**********************************************\n");
    for(int i=0; i<x; i++){
        printf("\n||| Personnel num %d |||\n",i+1);
        afficherPerso(*(perso+i));
    }
}

int sommeDepenses(int a ,int b,int c,int d,int e, int f ){
    return (a+b+c+d+e+f);
}

int calculerSalaires(PERSONNEL* perso,int nbperso){
    int s=0;
    for (int i=0;i<nbperso;i++)
        s+=((perso+i)->salaire);
    return s;
}

void saisirDepenses(DEPENSES* d){
    PERSONNEL P;
    int nbperso;
    printf("------------------------------------\n");
    d->id=rand();
    d->electricite=saisirEntier("le cout de l'electricite");
    d->taxes=saisirEntier("le cout des taxes");
    printf("Maintenance:\n");
    printf("   Le cout de nettoyage est: \n");
    scanf("%d", d->maintenance);
    printf("   Le cout de ventilation est: \n");
    scanf("%d", d->maintenance+1);
    printf("   Le cout de reparation est: \n");
    scanf("%d", d->maintenance+2);
    nbperso=saisirEntier("le nombre de personnels");
    PERSONNEL* perso=creerTabPerso(nbperso);
    remplirTabPerso(perso,nbperso);
    d->personnel=perso;
    d->nbrperso=nbperso;
    d->salaires=calculerSalaires(d->personnel,d->nbrperso);
}

void remplirDepenses(DEPENSES* dep ,int nbrDepenses){
    for (int i=0;i<nbrDepenses;i++){
      saisirDepenses((dep+i));
    }

}
void afficherDepenses(DEPENSES* d){
    printf("------------------------------------\n");
     printf("Id : %d\n", d->id);
    printf("Le cout de l'electricite est: %d\n", d->electricite);
    printf("Le cout des taxes est: %d \n", d->taxes);
    printf("Maintenance:\n");
    printf("   Le cout de nettoyage est: %d\n", *(d->maintenance));
    printf("   Le cout de ventilation est: %d\n", *(d->maintenance+1));
    printf("   Le cout de reparation est: %d\n", *(d->maintenance+2));
    printf("Le cout des salaires est: %d\n",d->salaires);
    printf("\n||| Le total des depenses vaut: %d |||\n",sommeDepenses(d->salaires,*(d->maintenance+2),*(d->maintenance+1),*(d->maintenance),d->taxes,d->electricite));
}

FACTURE saisirTarifs(){
    FACTURE f;
    f.prix_normal=saisirReel("le prix normal du parking");
    f.tarif_nuit=saisirEntier("le tarif de la nuit du parking");
    f.remise_abonne=saisirEntier("le remise d'abonnement du parking");
    return f;
}

float calculerFacture(float x,int y,int z){
    return x+y-z;
}

FACTURE remplirFacture(FACTURE f,DRIVER d){
    int h2;
    FACTURE x;
    float y;
    x.prix_normal=f.prix_normal;
    if (d.a==true)
        x.remise_abonne=f.remise_abonne;
    else
        x.remise_abonne=0;
    while (true) {
        printf("Entrez 1 si le chauffeur est arrive pendant le jour, 0 si pendant la nuit ");
        scanf("%d", &h2);
        if (h2 == 0) {
            x.tarif_nuit=f.tarif_nuit;
            break;
    }   else if (h2 == 1) {
            x.tarif_nuit=0;
            break;
    }   else {
            printf("Veuillez entrer seulement 0 ou 1.\n");
    }
    }
    x.montant=calculerFacture(x.prix_normal,x.tarif_nuit,x.remise_abonne);
return x;
}

void afficherFacture(FACTURE f){
    printf("------------------------------------\n");
    printf("| Facture: |\n");
    printf("   Le prix est: %.3f dt\n",f.prix_normal);
    printf("   La remise d'abonnement est: %d dt\n",f.remise_abonne);
    printf("   Le tarif de la nuit est: %d dt\n",f.tarif_nuit);
    printf("\n   |||Le montant total a payer est: %.3f dt|||\n",f.montant);
}

DRIVER saisirDriver(FACTURE tarifs){
    DRIVER d;
    int h1;
    printf("------------------------------------\n");
    printf("\nDonner le nom du chauffeur:\n");
    scanf("%s",&d.nom);
    d.id=saisirEntier("La CIN du chauffeur");
    while (true) {
        printf("Entrez 1 si le chauffeur est abonne, 0 si non ");
        scanf("%d", &h1);
        if (h1 == 0) {
            d.a = false;
            break;
        }else if (h1 == 1) {
            d.a=true;
            break;
        }   else {
            printf("Veuillez entrer seulement 0 ou 1.\n");
        }
    }
    int nb_dates;
    printf("Donner le nombre des dates d entree");
    scanf("%d",&nb_dates);
    DATE* dates=AllocTabDate(nb_dates);
    for(int i=0;i<nb_dates;i++){
        *(dates+i)=saisirDate();
    }
    d.nbr_dates=nb_dates;
    d.dates=dates;
    d.fac=remplirFacture(tarifs,d);
    return d;
}

void afficherDriver(DRIVER d){
    printf("------------------------------------\n");
    printf("Le nom du chauffeur est: %s\n", d.nom);
    printf("La CIN est: %d \n", d.id);
    if (d.a==true)
        printf("L'etat d'abonnement: abonne\n");
    else
        printf("L'etat d'abonnement: non abonne\n");
    afficherFacture(d.fac);
    for(int i=0;i<d.nbr_dates;i++){
        afficherDate(*(d.dates+i));
    }
}

DRIVER* creerTabDriver(int x){
	DRIVER* drv;
	drv=(DRIVER*) malloc (x * sizeof(DRIVER));
	if(!drv) exit(-1);
	return drv;
}

void remplirTabDriver(DRIVER* drv, int x,FACTURE tarifs,FILE* fp,FILE* fi){
    int pos,test;
    for(int i=0; i<x; i++){
        printf("\n||| Chauffeur num %d |||\n",i+1);
        *(drv+i)=saisirDriver(tarifs);
        pos=ftell(fp);
        fwrite(&pos,sizeof(int),1,fi);
        ecrireUnDriverDansFichier(fp,*(drv+i));
    }
}
void remplirTabDepenses(DEPENSES* dep, int x,FILE* fp,FILE* fi){
    int pos;
    for(int i=0; i<x; i++){
        printf("\n||| Depenses du jour num %d |||\n",i+1);
        saisirDepenses((dep+i));
        pos=ftell(fp);
        fwrite(&pos,sizeof(int),1,fi);
        ecrireLesDepensesDansFichier(fp,*(dep+i));
    }
}
void remplirFichierVoiture(VOITURE* v, int x,FILE* fp,FILE* fi,FACTURE tarifs){
    int pos;

    for(int i=0; i<x; i++){
        printf("\n||| Voiture num %d |||\n",i+1);
        *(v+i)=saisirVoiture(tarifs);
        pos=ftell(fp);
        printf("erkfrffff");
        fwrite(&pos,sizeof(int),1,fi);
        ecrireUneVoitureDansFichier(fp,*(v+i));
    }
}
void afficherTabDriver(DRIVER* drv, int x){
    printf("\n**********************************************\n");
    for(int i=0; i<x; i++){
        printf("\n||| Chauffeur num %d |||\n",i+1);
        afficherDriver(*(drv+i));
    }
}

DATE saisirDate()
{
	DATE d;
	printf("\n saisir une date ");
	scanf("%d%d%d", &d.jour, &d.mois, &d.annee);
	return d;
}
void afficherDate(DATE d)
{
	printf("\nLa date %d/%d/%d ", d.jour, d.mois, d.annee);
}
void trierDriverParFacture(DRIVER* dr, int nc) {
    for (int i = 0; i < nc - 1; i++) {
        for (int j = 0; j < nc - i - 1; j++) {
            if ((dr + j)->fac.montant < (dr + j + 1)->fac.montant) {
                DRIVER temp = *(dr + j);
                *(dr + j) = *(dr + j + 1);
                *(dr + j + 1) = temp;
            }
        }
    }
}

void rechercheDriverParMatricule(VOITURE* v, int nbv, int matriculerecherche) {
    bool trouve = false;

    for (int i = 0; i < nbv; i++) {
        if ((v + i)->matricule == matriculerecherche) {
            printf("Les chauffeurs de la voiture avec la matricule %d est \n", matriculerecherche);
            afficherDriver(*(v + i)->drv);
            trouve = true;
            break;
        }
    }

    if (!trouve) {
        printf("Aucune voiture avec la matricule %d n'a été trouvée.\n", matriculerecherche);
    }
}

void recherchePersoParCIN (PERSONNEL* perso, int nbperso, int CIN){
    bool trouve = false;

    for (int i = 0; i < nbperso; i++) {
        if ((perso + i)->id == CIN) {
            printf("Le chauffeur de la voiture avec la CIN %d est : %s\n", CIN, (perso + i)->nom);
            trouve = true;
            break;
        }
    }

    if (!trouve) {
        printf("Aucun personnel avec la CIN %d n'a été trouvee.\n", CIN);
    }
}

void rechercheVoitureParNom(VOITURE* v, int nbv, char nom1[]) {
    bool trouve = false;

    for (int i = 0; i < nbv; i++) {
        for (int j = 0; j < (v + i)->nbr_drivers; j++) {
            if (strcmp(((v + i)->drv + j)->nom, nom1) == 0) {
                printf("La matricule de la voiture, dont le nom du chauffeur est %s, est : %d\n",
                       nom1, (v + i)->matricule);
                trouve = true;
                break;
            }
        }
        if (trouve) {
            break;
        }
    }

    if (!trouve) {
        printf("Aucun chauffeur avec le nom %s est venu au parking.\n", nom1);
    }
}


void trierVoitureParTemps(VOITURE* v,int nbv){
    TEMPS t1,t2;
    for (int i = 0; i < nbv - 1; i++) {
        for (int j = 0; j < nbv - i - 1; j++) {
                t1=calculerDuree((v+j)->tempsentree,(v+j)->tempssortie);
                t2=calculerDuree((v+j+1)->tempsentree,(v+j+1)->tempssortie);
            if ((t1.h*3600+t1.mins*60+t1.sec)<(t2.h*3600+t2.mins*60+t2.sec)) {
                VOITURE voit = *(v + j);
                *(v + j) = *(v + j + 1);
                *(v + j + 1) = voit;
            }
        }
    }
}

RESULTAT saisirResultat(VOITURE* v, int nbv){
    RESULTAT res;
    res.mat.matricule=saisirEntier("la matricule de la voiture dont tu veux calculer la duree de sa parking");
    bool trouve = false;
    for (int i = 0; i < nbv; i++) {
        if ((v + i)->matricule == res.mat.matricule) {
            res.duree=calculerDuree((v+i)->tempsentree,(v+i)->tempssortie);
            trouve = true;
            break;
        }
    }

    if (!trouve) {
        printf("Aucune voiture avec la matricule %d n'a été trouvée.\n", res.mat.matricule);
        res.duree.h=0;
        res.duree.mins=0;
        res.duree.sec=0;
    }
    return res;
}

void afficherResultat(RESULTAT res){
    printf("Tu cherche la duree pour la voiture de la matricule %d\n",res.mat);
    printf("La duree est: [%d h:%d mins:%d secs]\n",res.duree.h,res.duree.mins,res.duree.sec);
}

void   ajouterNewDriver(DRIVER** drv,int* nb,FACTURE tarifs){
        int nb_a_ajouter;
        printf("\n Entrer Combien de chauffeurs vous voulez ajouter ? \n");
        scanf("%d",&nb_a_ajouter);
        printf("%d",*nb);

        *drv=(DRIVER*)realloc(*drv,(*nb+nb_a_ajouter) * sizeof(DRIVER));

            int indicestart=*nb;

            for(int i=indicestart;i<(*nb)+nb_a_ajouter;i++){
                *((*drv)+i)= saisirDriver(tarifs);
            }
            *nb+=nb_a_ajouter;

}

int rechercheDriverAvecID(DRIVER* drv, int nb, int id) {
    for (int i = 0; i < nb; i++) {
        if ((*(drv+i)).id == id) {
            return i;
        }
    }
    return -1;
}

void modifierChauffeur(DRIVER** drv,int nb,FACTURE tarifs){
    //afficherTabDriver(*drv,nb);
    int id;
    printf("Donner la CIN du driver  voulez-vous modifier :");
    scanf("%d",&id);
    int indice=rechercheDriverAvecID((*drv),nb,id);
    if(indice==-1){
        printf("CIN incorrecte");
    }else{
         *((*drv)+indice)= saisirDriver(tarifs);
    }
}

void SupprimerUnDriverAvecID(DRIVER** drv,int* nb){
    //afficherTabDriver(*drv,nb);
    int id;
     printf("Entrez le id du driver a supprimer : ");
    scanf("%d", &id);
    int indice=rechercheDriverAvecID((*drv),*nb,id);
        for(int i=indice;i<*nb-1;i++){
                *((*drv)+i)=*((*drv)+i+1);
        }
        *drv = (DRIVER*) realloc(*drv, (*nb - 1) * sizeof(DRIVER));
        (*nb)--;
}

void trouverVoiture(VOITURE* v, int nbv){
    char nom[50];
    printf("Donner le nom du chauffeur pour le quel tu veux trouver sa voiture:\n");
    scanf("%s",&nom);
    rechercheVoitureParNom(v,nbv,nom);
}

float calculerInterets(DRIVER* drv,int nc){
    float s=0;
    for (int i=0;i<nc;i++)
        s+=((drv+i)->fac.montant);
    return s;
}
void afficherInterets(DRIVER* drv,int nc){
    float x;
    x=calculerInterets(drv,nc);
    printf("\nLes interets du parking sont:%.2f",x);
}

void calculerRevenus(DRIVER* drv,DEPENSES* d,int nc){
    int s;
    float i;
    float de;
    i=calculerInterets(drv,nc);
    de=sommeDepenses(d->salaires,*(d->maintenance+2),*(d->maintenance+1),*(d->maintenance),d->taxes,d->electricite);
    printf("\nles revenus du projet sont:%.2f",i-de);}

void trouverPersonnel(PERSONNEL* perso, int nbperso){
    int cin;
    printf("Donner la CIN du personnel pour le quel tu cherches:\n");
    scanf("%d",&cin);
    recherchePersoParCIN(perso,nbperso,cin);
}

void ajouterNewVoiture(VOITURE** voi ,int* nv,FACTURE tarifs){
    int nb_a_ajouter;
        printf("\n Entrer Combien voiture voulez-vous ajouter ? \n");
        scanf("%d",&nb_a_ajouter);
        *voi=(VOITURE*)realloc(*voi,(*nv+nb_a_ajouter) * sizeof(VOITURE));

        if (*voi==NULL){
                printf("Erreur redimensionnement");
                exit(-3);
        }
        else{
            int indicestart=*nv;
            for(int i=indicestart;i<(*nv)+nb_a_ajouter;i++){
                *((*voi)+i)=saisirVoiture(tarifs);
            }

            *nv+=nb_a_ajouter;
            printf("%d",*nv);
        }
}
int rechercheVoitureAvecMat(VOITURE* v, int nbv, int mat) {
    for (int i = 0; i < nbv; i++) {
        if ((*(v+i)).matricule == mat) {
            return i;
        }
    }
    return -3;
}

void modifierVoiture(VOITURE** v,int nbv,FACTURE tarifs){
    int mat;
    printf("Donner la matricule de la voiture que tu veux modifier :");
    scanf("%d",&mat);
    int matricule=rechercheVoitureAvecMat((*v),nbv,mat);
    if(matricule==-1){
        printf("matricule intouvable");
    }else{
         *((*v)+matricule)= saisirVoiture(tarifs);
    }
}

void SupprimerUneVoitureAvecMatricule(VOITURE** v,int* nbv){
    int mat;
     printf("Entrez la matricule de la voiture a supprimer : ");
    scanf("%d", &mat);
    int matricule=rechercheVoitureAvecMat(*v,*nbv,mat);
    if (matricule>-1){
        for(int i=matricule;i<2;i++){
                *((*v)+i)=*((*v)+i+1);
        }
        *v = (VOITURE*) realloc(*v, (*nbv - 1) * sizeof(VOITURE));
        (*nbv)--;
    }
    else printf("Matricule introuvable\n");
}
void   ajouterNewPersonnel(PERSONNEL** perso,int* nb){
        int nb_a_ajouter;
        printf("\n Entrer Combien de personnels vous voulez ajouter ? \n");
        scanf("%d",&nb_a_ajouter);
        *perso=(PERSONNEL*)realloc(*perso,(*nb+nb_a_ajouter) * sizeof(PERSONNEL));
        if (*perso==NULL){
                printf("Erreur redimensionnement");
                exit(-3);
        }else{
            int indicestart=*nb;
            for(int i=indicestart;i<(*nb+nb_a_ajouter);i++){
                *((*perso)+i)= saisirPerso();
            }
            *nb=(*nb)+nb_a_ajouter;
        }
}


int recherchePersoAvecID(PERSONNEL* perso, int nb, int id) {
    for (int i = 0; i < nb; i++) {
        if ((*(perso+i)).id == id) {
            return i;
        }
    }
    return -1;
}
void modifierPersonnel(PERSONNEL** perso,int* nb){
    int id;
    printf("Donner la CIN du personnel  voulez-vous modifier :");
    scanf("%d",&id);
    int indice=recherchePersoAvecID((*perso),*nb,id);
    if(indice==-1){
        printf("CIN incorrecte");
    }else{
         *((*perso)+indice)= saisirPerso();
    }
}
void SupprimerUnPersoAvecID(PERSONNEL** perso,int* nb){
    int id;
     printf("Entrez le id du personnel a supprimer : ");
    scanf("%d", &id);
    int indice=recherchePersoAvecID((*perso),*nb,id);
        for(int i=indice;i<*nb-1;i++){
                *((*perso)+i)=*((*perso)+i+1);
        }
        *perso = (PERSONNEL*) realloc(*perso, (*nb - 1) * sizeof(PERSONNEL));
        (*nb)--;
}

void afficherMenuVoitures(VOITURE** v, int* nbv,FACTURE tarifs) {
    int choix;
    do {
        printf("\n********** Menu Voitures **********\n");
        printf("* 1 - Ajouter une voiture          \n");
        printf("* 2 - Afficher les voitures        \n");
        printf("* 3 - Modifier les donnees d'une voiture        \n");
        printf("* 4 - Supprimer une voiture        \n");
        printf("* 5 - Afficher les donnees de la voiture qui a reste le plus long temps dans le parking     \n");
        printf("* 6 - Identifier une voiture a partir du nom du chauffeur       \n");
        printf("* 0 - Retour au menu principal     \n");
        printf("***********************************\n");

        printf("Entrer votre choix (0-6) :\t");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                ajouterNewVoiture(v ,nbv,tarifs);
                break;
            case 2:
                afficherTabVoiture(*v,*nbv);
                break;
            case 3:
                modifierVoiture(v,nbv,tarifs);
                break;
            case 4:
                SupprimerUneVoitureAvecMatricule(v,nbv);
                break;
            case 5:
                trierVoitureParTemps(*v,*nbv);
                afficherVoiture(**v);
                break;
            case 6:
                trouverVoiture(*v,*nbv);
                break;
            case 0:
                printf("Retour au menu principal...\n");
                break;
            default:
                printf("Choix invalide. Veuillez réessayer.\n");
        }
    } while (choix != 0);
}

int RechercheByIdDepense(DEPENSES* d,int nbrDepenses,int id){

    for(int i=0;i<nbrDepenses;i++){
        if((*(d+i)).id==id){
            return i;
        }
    }
    return -1;
}

void afficherMenuFinances(DRIVER* drv, int nc,DEPENSES** d,int* nbrDepenses) {
    int choix,id_depense;

    do {
        printf("\n********** Menu Finances **********\n");
        printf("* 1 - Consulter les depenses         \n");
        printf("* 2  - Gestion les personels         \n");
        printf("* 3 - Consulter les interets         \n");
        printf("* 4 - Consulter la recette du parking    \n");
        printf("* 0 - Retour au menu principal     \n");
        printf("***********************************\n");

        printf("Entrer votre choix (0-4) :\t");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                afficherLesDepenses(*d,*nbrDepenses);
                break;
            case 2:
                {
                   printf("Liste Depense\n");
                    for(int i=0;i<*nbrDepenses;i++){
                            printf("\n");
                            afficherDepenses((*d)+i);
                    }
                   printf("Donner Id Depense Modifier");
                   scanf("%d",&id_depense);
                   int indice=RechercheByIdDepense(*d,*nbrDepenses,id_depense);
                   if(indice!=-1){
                        afficherDepenses((*d)+indice);
                        afficherMenuPersonnels(&(((*d)+indice)->personnel),
                                               &(((*d)+indice)->nbrperso)
                                                ,*nbrDepenses);

                   }else{
                        printf(" Id Incorrect ");
                   }
                }
                break;
            case 3:
            afficherInterets(drv,nc);
                break;
            case 4:
            calculerRevenus(drv,d,nc);
                break;
            case 0:
                printf("Retour au menu principal...\n");
                break;
            default:
                printf("Choix invalide. Veuillez réessayer.\n");
        }

    } while (choix != 0);
}

void MettreAJourDepense(DEPENSES* dep,int nbr){
    for(int i=0;i<nbr;i++){
        (dep+i)->salaires=calculerSalaires((dep+i)->personnel,(dep+i)->nbrperso);
    }
}

void afficherMenuPersonnels(PERSONNEL** perso, int* nbperso,DEPENSES* d,int nbr_depense) {
    int choix;
    do {
        printf("\n********** Menu Personnels **********\n");
        printf("* 1 - Ajouter un personnel          \n");
        printf("* 2 - Afficher les personnels       \n");
        printf("* 3 - Modifier les donnees d'un personnel        \n");
        printf("* 4 - Supprimer les personnels       \n");
        printf("* 5 - Chercher le nom d'un personnel a partir de sa CIN       \n");
        printf("* 0 - Retour au menu principal      \n");
        printf("*************************************\n");

        printf("Entrer votre choix (0-4) :\t");
        scanf("%d", &choix);
        MettreAJourDepense(d,nbr_depense);
        switch (choix) {
            case 1:
                ajouterNewPersonnel(perso,nbperso);
                break;
            case 2:
                afficherTabPerso(*perso,*nbperso);
                break;
            case 3:
                modifierPersonnel(perso,nbperso);
                break;
            case 4:
                SupprimerUnPersoAvecID(perso,nbperso);
                break;
            case 5:
                trouverPersonnel(*perso,*nbperso);
                break;
            case 0:
                printf("Retour au menu principal...\n");
                break;
            default:
                printf("Choix invalide. Veuillez réessayer.\n");
        }
    } while (choix != 0);
}

void afficherMenuDrivers(DRIVER** drv, int* nc, FACTURE tarifs){
    int choix;
    do {
        printf("\n********** Menu Chauffeurs **********\n");
        printf("* 1 - Ajouter un chauffeur          *\n");
        printf("* 2 - Afficher les chauffeurs       *\n");
        printf("* 3 - Modifier chauffeur            *\n");
        printf("* 4 - Supprimer chauffeur           *\n");
        printf("* 5 - afficher les donnees du chauffeur qui a paye le plus        \n");
        printf("* 0 - Retour au menu principal      *\n");
        printf("*************************************\n");

        printf("Entrer votre choix1 (0-5) :\t");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                                        printf("%d",*nc);

                ajouterNewDriver(drv,nc,tarifs);
                break;
            case 2:
               afficherTabDriver(*drv,*nc);
                break;
            case 3:
                modifierChauffeur(drv,*nc,tarifs);break;
            case 4:
                SupprimerUnDriverAvecID(drv,nc);break;
            case 5:
                 trierDriverParFacture(*drv,*nc);
                 afficherDriver(**drv);break;
            case 0:
                printf("Retour au menu principal...\n");
                break;
            default:
                printf("Choix invalide. Veuillez reessayer.\n");
        }
    } while (choix != 0);
}

void afficherMenuPrincipal(VOITURE** v, int* nbv, DRIVER** drv, int* nc,FACTURE tarifs,DEPENSES** d,int* nbrDepenses) {
    int choix;
    do {
        printf("\n====================================\n");
        printf("||          MENU PRINCIPAL        ||\n");
        printf("====================================\n");
        printf("  1 - Gerer les chauffeurs\n");
        printf("  2 - Gerer les voitures\n");
        printf("  3 - Gerer les finances \n");
        printf("  4 - Quitter\n");
        printf("====================================\n");
        printf("Entrer votre choix (1-4) : ");
        scanf("%d", &choix);
        switch (choix) {
            case 1:
                printf("\n");
                afficherMenuDrivers(drv,nc,tarifs);
                break;
            case 2:
                printf("\n");
                afficherMenuVoitures(v,nbv,tarifs);
                break;
            case 3:
                printf("\n");
                afficherMenuFinances(*drv,*nc,d,nbrDepenses);

                break;
            case 4:
                printf("\nMerci d'avoir utilise notre application!\n");
                system("cls");
                break;
            default:
                printf("\n Erreur : Choix invalide. Veuillez reessayer.\n");
        }
    } while (choix != 4);
}

void  afficherLesDepenses(DEPENSES* d,int x){
        printf("\n%d\n",x);

    for (int i=0;i<x;i++){
    printf("\n------------------------------------\n");
    printf("\t Lid est %d",(d+i)->id);
    printf("\n------------------------------------\n");

    printf("Le cout de l'electricite est: %d\n", (d+i)->electricite);
    printf("Le cout des taxes est: %d \n", (d+i)->taxes);
    printf("Maintenance:\n");
    printf("   Le cout de nettoyage est: %d\n", *((d+i)->maintenance));
    printf("   Le cout de ventilation est: %d\n", *((d+i)->maintenance+1));
    printf("   Le cout de reparation est: %d\n", *((d+i)->maintenance+2));
    printf("Le cout des salaires est: %d\n",(d+i)->salaires);
    printf("\n||| Le total des depenses vaut: %d |||\n",sommeDepenses((d+i)->salaires,*((d+i)->maintenance+2),*((d+i)->maintenance+1),*((d+i)->maintenance),(d+i)->taxes,(d+i)->electricite));
    }
}

void creerFichierPersonnel(FILE**fp,FILE ** fi)
{
	*fp= fopen("personnel","wb+");
	if(!*fp) exit(-1);
    *fi= fopen("PersonnelIndex","wb+");
	if(!*fi) exit(-1);
}

void ecrireUnPersonnelDansFichier(FILE*fp, PERSONNEL perso)
{
	fwrite (&perso.nom ,sizeof(char), 1 , fp);
	fwrite (&perso.id, sizeof(int), 1, fp);
	fwrite (&perso.salaire, sizeof(int), 1, fp);
    fwrite(&perso.nbr_position, sizeof(int), 1, fp);
	for(int i=0;i<perso.nbr_position;i++){
        POSITION* pos=perso.pos+i;
        fwrite(&pos->bloc, sizeof(char), 1, fp);
        fwrite(&pos->etage, sizeof(int), 1, fp);
	}

}
/*void remplirFichierPersonnel(FILE*fp)
{
	PERSONNEL perso;
	do
	{
		perso=saisirPerso();
		if(perso.nom!='0') ecrireUnPersonnelDansFichier(fp, perso);
	}
	while(perso!='0');
}*/

PERSONNEL lireUnPersonnelDuFichier(FILE*fp)
{
	PERSONNEL perso;
	fread(&perso.nom ,sizeof(char), 1 , fp);
	fread(&perso.id, sizeof(int), 1, fp);
	fread(&perso.salaire, sizeof(int), 1, fp);
    fread(&perso.nbr_position, sizeof(int), 1, fp);

    int nbr_pos=perso.nbr_position;
    perso.pos=AllocTabPosition(nbr_pos);
    for(int i=0;i<nbr_pos;i++){
        POSITION* pos=perso.pos+i;
        fread(&(pos)->bloc, sizeof(char), 1, fp);
        fread(&(pos)->etage, sizeof(int), 1, fp);
	}
	return perso;
}

void afficherFichierPersonnels(FILE*fp)
{
	PERSONNEL perso; int x;
	rewind(fp);
	while(1)
	{
		fread(&x, sizeof(int), 1, fp);
		if(feof(fp)) break;
		fseek(fp, -sizeof(int),1);
		perso=lireUnPersonnelDuFichier(fp);
		//afficherPersonnel(perso);
	}
}

void creerFichierDriver(FILE**fp,FILE**fi)
{
	*fp= fopen("Chauffeur","wb+");
	if(!*fp) exit(-1);
	*fi= fopen("ChauffeurIndex","wb+");
	if(!*fi) exit(-1);
}

void afficherFichierIndex(FILE* fi){
    int nbr;
    rewind(fi);
    while(1){
        fread(&nbr,sizeof(int),1,fi);
        if(!feof(fi)) break;
    }
}

void OpenFichierVoiture(FILE**fp,FILE**fi)
{
	*fp= fopen("Voiture","a+");
	if(!*fp) exit(-1);
	*fi= fopen("VoitureIndex","a+");
	if(!*fi) exit(-1);
}
void OpenFichierDriver(FILE**fp,FILE**fi)
{
	*fp= fopen("Chauffeur","a+");
	if(!*fp) exit(-1);
	*fi= fopen("ChauffeurIndex","a+");
	if(!*fi) exit(-1);
}
void OpenFichierDepenses(FILE**fp,FILE**fi)
{
	*fp= fopen("Depenses","a+");
	if(!*fp) exit(-1);
	*fi= fopen("DepensesIndex","a+");
	if(!*fi) exit(-1);
}
/*
void ecrireUnDriverDansFichier(FILE*fp, DRIVER drv)
{
    afficherDriver(drv);
	fwrite (&drv.nom ,sizeof(char[50]), 1 , fp);
	fwrite (&drv.id, sizeof(int), 1, fp);
	fwrite (&drv.a, sizeof(bool), 1, fp);
	fwrite(&drv.fac, sizeof(FACTURE), 1, fp);
    fwrite(&drv.nbr_dates, sizeof(int), 1, fp);
    int nbr_dates=drv.nbr_dates;
    for(int i=0;i<nbr_dates;i++){
        DATE* d=(drv.dates)+i;
        fwrite(&d, sizeof(DATE), 1, fp);
	}
}*/

/*
void remplirFichierDriver(FILE*fp)
{
	DRIVER drv;
	do
	{
		drv=saisirDriver(FACTURE);
		if(drv.nom!='0') ecrireUnDriverDansFichier(fp, drv);
	}
	while(drv.nom!='0');
}*/
/*
DRIVER lireUnDriverDuFichier(FILE*fp)
{
	DRIVER drv;

	fread (&drv.nom ,sizeof(char[50]), 1 , fp);
	fread (&drv.id, sizeof(int), 1, fp);
	fread (&drv.a, sizeof(bool), 1, fp);
	fread(&drv.fac, sizeof(FACTURE), 1, fp);
    fread(&drv.nbr_dates, sizeof(int), 1, fp);

    int nbr_dates=drv.nbr_dates;

    drv.dates=AllocTabDate(nbr_dates);

    for(int i=0;i<nbr_dates;i++){
        DATE* d=(drv.dates)+i;
        fread(&d, sizeof(DATE), 1, fp);
	}
	return drv;
}*/
DRIVER lireUnDriverDuFichier(FILE* fp) {
    DRIVER drv;

    // Read each part of the DRIVER struct
    fread(&drv.nom, sizeof(char[50]), 1, fp);  // Read 50 characters for the name
    fread(&drv.id, sizeof(int), 1, fp);     // Read an integer for the id
    fread(&drv.a, sizeof(bool), 1, fp);     // Read a boolean for "abonné"
    fread(&drv.fac, sizeof(FACTURE), 1, fp);  // Read the FACTURE structure
    fread(&drv.nbr_dates, sizeof(int), 1, fp); // Read the number of dates

    // Allocate memory for the dates array
    drv.dates = (DATE*)malloc(drv.nbr_dates * sizeof(DATE));
    if (drv.dates == NULL) {
        printf("Memory allocation failed for dates.\n");
        exit(1);  // Handle memory allocation failure
    }

    // Read each DATE structure into the dates array without using []
    for (int i = 0; i < drv.nbr_dates; i++) {
        fread(drv.dates+i, sizeof(DATE), 1, fp);  // Pointer arithmetic to access each DATE
    }
    return drv;
}

DRIVER* lireUnDriverDuFichierr(FILE* fp) {
    DRIVER* drv;

    // Read each part of the DRIVER struct
    fread(&drv->nom, sizeof(char[50]), 1, fp);  // Read 50 characters for the name
    fread(&drv->id, sizeof(int), 1, fp);     // Read an integer for the id
    fread(&drv->a, sizeof(bool), 1, fp);     // Read a boolean for "abonné"
    fread(&drv->fac, sizeof(FACTURE), 1, fp);  // Read the FACTURE structure
    fread(&drv->nbr_dates, sizeof(int), 1, fp); // Read the number of dates

    // Allocate memory for the dates array
    drv->dates = (DATE*)malloc(drv->nbr_dates * sizeof(DATE));
    if (drv->dates == NULL) {
        printf("Memory allocation failed for dates.\n");
        exit(1);  // Handle memory allocation failure
    }

    // Read each DATE structure into the dates array without using []
    for (int i = 0; i < drv->nbr_dates; i++) {
        fread(drv->dates + i, sizeof(DATE), 1, fp);  // Pointer arithmetic to access each DATE
    }    return drv;
}

void afficherFichierDrivers(FILE*fp)
{
	DRIVER driver; int x;
	rewind(fp);
	while(1)
	{
		fread(&x, sizeof(int), 1, fp);
		if(feof(fp)) break;
		fseek(fp, -sizeof(int),1);
		driver=lireUnDriverDuFichier(fp);
		afficherDriver(driver);
	}
}
void creerFichierVoiture(FILE**fp,FILE **fi)
{
	*fp= fopen("Voiture","wb+");
	if(!*fp) exit(-1);
    *fi= fopen("VoitureIndex","wb+");
	if(!*fi) exit(-1);
}


void ecrireUneVoitureDansFichier(FILE*fp, VOITURE v)
{
	fwrite (&v.matricule ,sizeof(int), 1 , fp);
	fwrite (&v.position, sizeof(POSITION), 1, fp);
	fwrite (&v.tempsentree, sizeof(TEMPS), 1, fp);
	fwrite (&v.tempssortie, sizeof(TEMPS), 1, fp);
	fwrite(&v.tarif, sizeof(FACTURE), 1, fp);
	fwrite (&v.nbr_drivers, sizeof(int), 1, fp);
	int nbr_drivers=v.nbr_drivers;
    for(int i=0;i<nbr_drivers;i++){
        DRIVER* driver=v.drv+i;
        ecrireUnDriverDansFichier(fp,*driver);
	}
}

void ecrireUnDriverDansFichier(FILE* fp, DRIVER drv) {
    fwrite(&drv.nom, sizeof(char[50]), 1, fp);  // Write the name (50 characters)
    fwrite(&drv.id, sizeof(int), 1, fp);     // Write the driver ID
    fwrite(&drv.a, sizeof(bool), 1, fp);     // Write the "abonné" boolean flag
    fwrite(&drv.fac, sizeof(FACTURE), 1, fp); // Write the FACTURE structure
    fwrite(&drv.nbr_dates, sizeof(int), 1, fp); // Write the number of dates

    // Write each DATE structure without using []
    for (int i = 0; i < drv.nbr_dates; i++) {
        fwrite(drv.dates + i, sizeof(DATE), 1, fp);  // Pointer arithmetic to access each DATE
    }
}

/*void remplirFichierVoiture(FILE*fp)
{
	VOITURE v;
	do
	{
		v=saisirVoiture();
		if(v.matricule!=0) ecrireUneVoitureDansFichier(fp,v);
	}
	while(v.matricule!=0);
}*/

VOITURE lireUneVoitureDuFichier(FILE* fp)
{
	VOITURE v;
	fread (&v.matricule ,sizeof(int), 1 , fp);
	fread (&v.position, sizeof(POSITION), 1, fp);
	fread (&v.tempsentree, sizeof(TEMPS), 1, fp);
	fread (&v.tempssortie, sizeof(TEMPS), 1, fp);
	fread(&v.tarif, sizeof(FACTURE), 1, fp);
	fread (&v.nbr_drivers, sizeof(int), 1, fp);
	int nbr_drivers=v.nbr_drivers;
    v.drv=creerTabDriver(nbr_drivers);
    DRIVER drv;
    for(int i=0;i<nbr_drivers;i++){
        drv=lireUnDriverDuFichier(fp);
        *(v.drv+i)=drv;
	}
	return v;
}

void afficherFichierVoitures(FILE*fp)
{
	VOITURE v; int x;
	rewind(fp);
	while(1)
	{
		fread(&x, sizeof(int), 1, fp);
		if(feof(fp)) break;
		fseek(fp, -sizeof(int),1);
		v=lireUneVoitureDuFichier(fp);
		afficherVoiture(v);
	}
}
void creerFichierDepenses(FILE**fp,FILE**fi)
{
	*fp= fopen("Depenses","wb+");
	if(!*fp) exit(-1);
    *fi= fopen("DepensesIndex","wb+");
	if(!*fi) exit(-1);
}

void ecrireLesDepensesDansFichier(FILE*fp, DEPENSES d)
{
    fwrite(&d.id,sizeof(int),1,fp);
	fwrite (&d.salaires, sizeof(int), 1, fp);
	fwrite(&d.electricite, sizeof(int), 1, fp);
	fwrite(&d.taxes, sizeof(int), 1, fp);

	for (int i = 0; i < 3; i++) {
        fwrite(d.maintenance + i, sizeof(int), 1, fp);  // Pointer arithmetic to access each DATE
    }
	fwrite(&d.nbrperso, sizeof(int), 1, fp);
	int nbr_dep=d.nbrperso;
    for(int i=0;i<nbr_dep;i++){
        PERSONNEL* perso=d.personnel+i;
        ecrireUnPersonnelDansFichier(fp,*perso);
	}

}

void remplirFichier(FILE*fp)
{
	DEPENSES d;
	do
	{
		saisirDepenses(&d);//verifier
		if(d.nbrperso!=0) ecrireLesDepensesDansFichier(fp, d);
	}
	while(d.nbrperso!=0);
}

DEPENSES lireLesDepensesDuFichier(FILE*fp)
{
	DEPENSES d;
	fread (&d.id, sizeof(int), 1, fp);
	fread (&d.salaires, sizeof(int), 1, fp);
	fread(&d.electricite, sizeof(int), 1, fp);
	fread(&d.taxes, sizeof(int), 1, fp);
	for (int i = 0; i < 3; i++) {
        fread(d.maintenance + i, sizeof(int), 1, fp);  // Pointer arithmetic to access each DATE
    }
	fread (&d.nbrperso ,sizeof(int), 1 , fp);

	d.personnel = (PERSONNEL*)malloc(d.nbrperso * sizeof(PERSONNEL));
    if (d.personnel == NULL) {
        printf("Memory allocation failed for dates.\n");
        exit(1);  // Handle memory allocation failure
    }

    // Read each DATE structure into the dates array without using []
    for (int i = 0; i < d.nbrperso; i++) {
        fread(d.personnel + i, sizeof(PERSONNEL), 1, fp);  // Pointer arithmetic to access each DATE
    }

	return d;
}

void afficherFichierDepenses(FILE*fp)
{
	DEPENSES d; int x;
	rewind(fp);
	while(1)
	{
		fread(&x, sizeof(int), 1, fp);
		if(feof(fp)) break;
		fseek(fp, -sizeof(int),1);
		d=lireLesDepensesDuFichier(fp);
		printf("%d \n",d.id);
		//afficherDepenses(d);
	}
}

void creerFichiersDepensesIndex(FILE**fe, FILE**fi)
{
	*fe= fopen("DepensesC","wb+");
	if(!*fe) exit(-1);
	*fi= fopen("IndexC","wb+");
	if(!*fi) exit(-1);
}
/*
int remplirFichierDepensesIndex(FILE*fe,FILE*fi)
{
	DEPENSES d; int x;
	int nb=0;
	do
	{
		d=saisirDepenses(perso);//verifier
		if(d.nbrperso!=0)
		{
			x=ftell(fe);
			fwrite(&x, sizeof(int),1, fi);
			ecrireLesDepensesDansFichier(fe,d);
			nb++;
		}
	}
	while(d.nbrperso!=0);
	return nb;
}*/

void copierTableauDansFichier(FILE*fe,FILE*fi, DEPENSES*tab,int n)
{
	int val;
	for(int i=0; i<n; i++)
	{
		val=ftell(fe);
		fwrite(&val, sizeof(int), 1, fi);
		ecrireLesDepensesDansFichier (fe, *(tab+i));
	}
}
void copierFichierDansTableau(FILE*fe,DEPENSES*res,int n)
{
	rewind(fe);
	for(int i=0; i<n; i++)
		*(res+i)=lireLesDepensesDuFichier(fe);
}

void copierFichierDriverDansTableau(FILE*fe,FILE*fi,DRIVER*res,int n)
{
	rewind(fe);rewind(fi);
    int pos;
	for(int i=0; i<n; i++){
        fread(&pos,sizeof(int),1,fi);
        fseek(fe,pos,0);
        *(res+i)=lireUnDriverDuFichier(fe);
	}
}
void copierFichierVoitureDansTableau(FILE*fe,FILE*fi,VOITURE*res,int n)
{
	rewind(fe);rewind(fi);
    int pos;
	for(int i=0; i<n; i++){
        fread(&pos,sizeof(int),1,fi);
        fseek(fe,pos,0);
        *(res+i)=lireUneVoitureDuFichier(fe);
	}
}


void copierFichierDepensesDansTableau(FILE*fe,FILE*fi,DEPENSES*res,int n)
{
	rewind(fe);rewind(fi);
    int pos;
	for(int i=0; i<n; i++){
        fread(&pos,sizeof(int),1,fi);
        fseek(fe,pos,0);
        *(res+i)=lireLesDepensesDuFichier(fe);
	}
}

int NombreDeElemetnFichierIndex(FILE* fp){
    fseek(fp,0,2);
    int taille=ftell(fp);
    int sizee=sizeof(int);
    return taille/sizee ;
}

void Chargement(FILE** FDrive,FILE** FIDriver,FILE** FDepense,FILE** FIDepense,FILE** FVoiture,FILE** FIVoiture,
                VOITURE** voiture,DEPENSES** depenses,DRIVER** driver,int* NbrDriver,int* nbrDepenses,int* nbVoiture)
{
    OpenFichierDriver(FDrive,FIDriver);
    afficherFichierIndex(*FIDriver);
    *NbrDriver=NombreDeElemetnFichierIndex(*FIDriver);
    *driver=creerTabDriver(*NbrDriver);
    copierFichierDriverDansTableau(*FDrive,*FIDriver,*driver,*NbrDriver);
    afficherTabDriver(*driver,*NbrDriver);
    OpenFichierDepenses(FDepense,FIDepense);
    afficherFichierIndex(*FIDepense);
    *nbrDepenses=NombreDeElemetnFichierIndex(*FIDepense);
    *depenses=allocTabDep(*nbrDepenses);
    copierFichierDepensesDansTableau(*FDepense,*FIDepense,*depenses,*nbrDepenses);
    afficherLesDepenses(*depenses,*nbrDepenses);
    OpenFichierVoiture(FVoiture,FIVoiture);
    afficherFichierIndex(*FIVoiture);
    *nbVoiture=NombreDeElemetnFichierIndex(*FIVoiture);
    *voiture=creerTabVoiture(*nbVoiture);
    copierFichierVoitureDansTableau(*FVoiture,*FIVoiture,*voiture,*nbVoiture);
    afficherTabVoiture(*voiture, *nbVoiture);

}
void Initialiser(FILE* FDrive,FILE*FIDriver,FILE*FDepense,FILE*FIDepense,FILE*FVoiture,FILE*FIVoiture,
                 FACTURE tarifs,VOITURE* voiture,DEPENSES* depenses,DRIVER* drive,int nbrDepenses,int NbrDriver,int nbVoiture)
{
    tarifs=saisirTarifs();
    creerFichierDriver(&FDrive,&FIDriver);
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
    creerFichierVoiture(&FVoiture,&FIVoiture);
    nbVoiture=saisirEntier("le nombre des voitures dans le parking");
    VOITURE* v=creerTabVoiture(nbVoiture);
    remplirFichierVoiture(v,nbVoiture,FVoiture,FIVoiture,tarifs);
    afficherTabVoiture(v,nbVoiture);
}
