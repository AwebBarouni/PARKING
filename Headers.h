#define HEADERS_H_INCLUDED
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
    bool a; //abonn� ou pas
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
    POSITION* pos;//lieu de travail(bloc et �tage)
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
void Initialiser(FILE* FDrive,FILE*FIDriver,FILE*FDepense,FILE*FIDepense,FILE*FVoiture,FILE*FIVoiture,
                 FACTURE tarifs,VOITURE* voiture,DEPENSES* depenses,DRIVER* drive,int nbrDepenses,int NbrDriver,int nbVoiture);
void Chargement(FILE** FDrive,FILE** FIDriver,FILE** FDepense,FILE** FIDepense,FILE** FVoiture,FILE** FIVoiture,
                VOITURE** voiture,DEPENSES** depenses,DRIVER** driver,int* NbrDriver,int* nbrDepenses,int* nbVoiture);
int NombreDeElemetnFichierIndex(FILE* fp);
void copierFichierDepensesDansTableau(FILE*fe,FILE*fi,DEPENSES*res,int n);
void copierFichierDepensesDansTableau(FILE*fe,FILE*fi,DEPENSES*res,int n);
void copierFichierVoitureDansTableau(FILE*fe,FILE*fi,VOITURE*res,int n);
void copierFichierDriverDansTableau(FILE*fe,FILE*fi,DRIVER*res,int n);
void creerFichiersDepensesIndex(FILE**fe, FILE**fi);
void afficherFichierDepenses(FILE*fp);
DEPENSES lireLesDepensesDuFichier(FILE*fp);
void ecrireLesDepensesDansFichier(FILE*fp, DEPENSES d);
void creerFichierDepenses(FILE**fp,FILE**fi);
void afficherFichierVoitures(FILE*fp);
VOITURE lireUneVoitureDuFichier(FILE* fp);
void ecrireUnDriverDansFichier(FILE* fp, DRIVER drv);
void ecrireUneVoitureDansFichier(FILE*fp, VOITURE v);
void creerFichierVoiture(FILE**fp,FILE **fi);
void afficherFichierDrivers(FILE*fp);
DRIVER* lireUnDriverDuFichierr(FILE* fp);
DRIVER lireUnDriverDuFichier(FILE* fp);
void OpenFichierDepenses(FILE**fp,FILE**fi);
void OpenFichierDriver(FILE**fp,FILE**fi);
void OpenFichierVoiture(FILE**fp,FILE**fi);
void afficherFichierIndex(FILE* fi);
void creerFichierDriver(FILE**fp,FILE**fi);
void afficherFichierPersonnels(FILE*fp);
PERSONNEL lireUnPersonnelDuFichier(FILE*fp);
void ecrireUnPersonnelDansFichier(FILE*fp, PERSONNEL perso);
void creerFichierPersonnel(FILE**fp,FILE ** fi);
void  afficherLesDepenses(DEPENSES* d,int x);
void afficherMenuPrincipal(VOITURE** v, int* nbv, DRIVER** drv, int* nc,FACTURE tarifs,DEPENSES** d,int* nbrDepenses);
void afficherMenuDrivers(DRIVER** drv, int* nc, FACTURE tarifs);
void afficherMenuPersonnels(PERSONNEL** perso, int* nbperso,DEPENSES* d,int nbr_depense);
void MettreAJourDepense(DEPENSES* dep,int nbr);
void afficherMenuFinances(DRIVER* drv, int nc,DEPENSES** d,int* nbrDepenses);
int RechercheByIdDepense(DEPENSES* d,int nbrDepenses,int id);
void afficherMenuVoitures(VOITURE** v, int* nbv,FACTURE tarifs);
void SupprimerUnPersoAvecID(PERSONNEL** perso,int* nb);
void modifierPersonnel(PERSONNEL** perso,int* nb);
int recherchePersoAvecID(PERSONNEL* perso, int nb, int id);
void   ajouterNewPersonnel(PERSONNEL** perso,int* nb);
void SupprimerUneVoitureAvecMatricule(VOITURE** v,int* nbv);
void modifierVoiture(VOITURE** v,int nbv,FACTURE tarifs);
int rechercheVoitureAvecMat(VOITURE* v, int nbv, int mat);
void ajouterNewVoiture(VOITURE** voi ,int* nv,FACTURE tarifs);
void trouverPersonnel(PERSONNEL* perso, int nbperso);
void calculerRevenus(DRIVER* drv,DEPENSES* d,int nc);
void afficherInterets(DRIVER* drv,int nc);
float calculerInterets(DRIVER* drv,int nc);
void trouverVoiture(VOITURE* v, int nbv);
void SupprimerUnDriverAvecID(DRIVER** drv,int* nb);

