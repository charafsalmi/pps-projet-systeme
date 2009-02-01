



/*
 * main.c
 *
 *  Created on: 16 janv. 2009
 *      Author: Charaf SALMI, François HAURIT, Sophie SURMONT
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

#include "fork_process.h"

/*
 * Précisions :
 *  - Si un voyage est annulé, on prend qqun en attente.
 * Par contre, si le voyage est supprimé, on se fiche
 * de tous les gens en attente.
 *  - Les signaux interdits d'utilisation 9 10 12 18 19
 *
 */

#define NB_max_voyages            5
#define Tmax_nom_produit        8
#define Tmax_nom_utilisateur    7
#define NB_max_guichets            5

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
struct transac
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
typedef struct transac Transac;

/*
 * Format d'une transaction administration
 */
struct trans_ad
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
typedef struct trans_ad Trans_ad;

/**
 * point d'entrée de l'application
 * @param nbarg
 * @param tbarg
 * @return
 */
int main(int nbarg, char *tbarg[])
{
    /*
     * Si il n'y a pas tous les arguments, on quitte.
     */
    if(nbarg != 3)
        exit(1);

    /*
     * Si le nombre de guichets est supérieur à NB_max_guichets, on quitte.
     */
    if(atoi(tbarg[2]) > NB_max_guichets || atoi(tbarg[1]) < 1)
    {
          perror("Nombre de guichets incorrect \n");
          printf("Choisissez un nombre entre 1 et %d\n", NB_max_guichets);
          exit(errno);
    }

    /*
     * Identifiants des processus fils.
     */
    pid_t
        pidAccueil,
        pidAdministration,
        pidDirection,
        pidGuichet[(*tbarg[2])];

    /*
     * Création des tubes
     */
    int
        Tadmin_accueil[1],
        Taccu_guichet[1];

    pipe(Taccu_guichet);
    pipe(Tadmin_accueil);

    /*
     * Compteurs et buffers
     */
    int i = 0;
    char* cbuffer;

    /*
     * Variables algorithmiques
     */
    char code_consultation ='\0';


    /*
     * Action pour le processus Pdirection
     */
    if((pidDirection = fork()) < 0)
    {
        perror("Erreur dans la création du processus Pdirection.");
        exit(errno);
    }
    else if(pidDirection == 0)
    {
        /*
         * Bienvenue dans le processus fils Pdirection.
         */
		//Ne pas oublier de fermer les tubes inutiles
		    /*
			* Action pour le processus Paccueil
			*/
			if((pidAccueil = fork()) < 0)
			{
				perror("Erreur dans la création du processus Paccueil.");
				exit(errno);
			}
			else if(pidAccueil == 0)
			{
				/*
				 * Bienvenue dans le processus fils Paccueil.
				 */
				     /*
					  * Action pour les processus Pguichet
					  */
				     for(i = 0; i < (*tbarg[2]); ++i)
					{
						if((pidGuichet[i] = fork()) < 0)
						{
							sprintf(cbuffer, "Erreur dans la création du processus Pguichet[%d].", i);
							perror(cbuffer);
							exit(errno);
						}
						else if(pidGuichet[i] == 0)
						{
							/*
							 * Bienvenue dans le processus fils id_Pguichet[i]
							 */
							//Ne pas oublier de fermer les tubes inutiles
							close(Taccu_guichet[1]);
							close(Tadmin_accueil[0]);
							close(Tadmin_accueil[1]);
							call_process_pguichet(i, Taccu_guichet);
							exit (1);
						}
					}
				close(Taccu_guichet[0]);
				close(Tadmin_accueil[1]);
				call_process_paccueil(Tadmin_accueil, Taccu_guichet);
				exit (1) ;
			}

			/*
			 * Action pour le processus Padministration
			 */
			if((pidAdministration = fork()) < 0)
			{
				perror("Erreur dans la création du processus Padministration.");
				exit(errno);
			}
			else if(pidAdministration == 0)
			{
				/*
				 * Bienvenue dans le processus fils Padministration.
				 */
				// S'occupe du catalogue des voyages
				// Lit l'enregistrement de fichier de ce type
				close(Taccu_guichet[0]);
				close(Taccu_guichet[1]);
				close(Tadmin_accueil[0]);
				call_process_padministration(Tadmin_accueil[1],pidAccueil);
			}

		close(Taccu_guichet[0]);
		close(Taccu_guichet[1]);
		close(Tadmin_accueil[0]);
		close(Tadmin_accueil[1]);
		call_process_pdirection();

    }

    /*
     * Fin du programme
     */
    return 0;
}
