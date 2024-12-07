#ifndef HEADERS_H_INCLUDED
#define HEADERS_H_INCLUDED
#include<stdio.h>
#include <stdbool.h>
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
