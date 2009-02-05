/*
 * type_definitions.h
 *
 *  Created on: 2 févr. 2009
 *      Author: charaf
 */
#include <fcntl.h>
#include <errno.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define NB_max_guichets			5
#define NB_max_voyages			5
#define Tmax_nom_produit        8
#define NB_max_guichets			5
#define Tmax_nom_utilisateur	20

enum
{
	Consultation = 'C', Demande = 'D', Annulation = 'A', Confirmation = 'F'
};

/*
 * Format d'un poste réservation
 */
struct reservation
{
	/*
	 * Nom du réservataire
	 * */
	char identu[Tmax_nom_utilisateur];

	/*
	 * Pas plus de 255 places réservées par client
	 */
	char nb_places;
};
typedef struct reservation Reservation;

/*
 * Format d'un poste du fichier de description de voyages
 */
struct produit
{
	/*
	 * Nom du produit
	 */
	char identp[Tmax_nom_produit];
	int nb_max_places;
	int nb_places_libres;
};
typedef struct produit Produit;

/*
 * Format d'une transaction client
 */
struct transaction
/*
 * Dans l'énoncé, je trouve super-idiot de déclarer "Reservation" (10 lettres)
 * et de déclarer "Transac" (7 lettres) plutôt que "Transaction" (11 lettres)…
 * Cohérence iut-debianique ?
 */
{
	/*
	 * Nom du client
	 */
	char identu[Tmax_nom_utilisateur];
	/*
	 * Nom du voyage
	 */
	char identp[Tmax_nom_produit];
	/*
	 * Code de transaction :
	 *     - R)éservation
	 *     - C)onsultation
	 *     - L)ibération
	 */
	char code;
	/*
	 * N'est utilisé que pour le code R
	 */
	char nb_places;
};
typedef struct transaction Transaction;

/*
 * Format d'une transaction administration
 */
struct Transaction_Admin
{
	/*
	 * Nom du voyage
	 */
	char identp[Tmax_nom_produit];
	/*
	 * Code de transaction :
	 *     - C)réation
	 *  - F)ermeture
	 */
	char code;
	/*
	 * N'est utilisé que pour le code C
	 */
	int nb_max_places;
};
typedef struct transaction_admin Transaction_Admin;

/*
 * Identifiants des processus fils.
 */
pid_t
    pidAccueil,
    pidAdministration,
    pidDirection,
    pidGuichet[NB_max_guichets];

/*
 * Création des tubes
 */
int
    Tadmin_accueil[1],
    Taccu_guichet[1];

