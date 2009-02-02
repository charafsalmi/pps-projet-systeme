



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

#include "type_definitions.h"

/*
 * Précisions :
 *  - Si un voyage est annulé, on prend qqun en attente.
 * Par contre, si le voyage est supprimé, on se fiche
 * de tous les gens en attente.
 *  - Les signaux interdits d'utilisation 9 10 12 18 19
 *
 */


/**
 * point d'entrée de l'application
 * @param nbarg
 * @param tbarg
 * @return
 */
int main(int nbarg, char *tbarg[])
{
    /*
     * Si il n'y a pas tous les arguments ou si le nombre de guichets est
     * supérieur à NB_max_guichets, on quitte.
     */
    if(nbarg != 3 || (atoi(tbarg[2]) > NB_max_guichets || atoi(tbarg[1]) < 1) )
    {
    	printf("agence: usage: agence f<fichier1> f<fichier2> <nbguichet> \n");
    	printf("Options:\n");
    	printf("\tf<fichier1>\t\tChemin vers le fichier …\n");
    	printf("\tf<fichier2>\t\tChemin vers le fichier …\n");
    	printf("\t<nbguichet>\t\tNombre de guichets entre 1 et %d\n", NB_max_guichets);
        exit(1);
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
    code_consultation ='\0';


    /*
     * Action pour le processus Pdirection
     */
    if((pidDirection = fork()) < 0)
    {
        perror("Erreur dans la création du processus Pdirection.");
        exit(1);
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
				exit(1);
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
							//execl("process_guichet");
							exit (1);
						}
					}
				close(Taccu_guichet[0]);
				close(Tadmin_accueil[1]);
				//execl();
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
				//execl();
			}

		close(Taccu_guichet[0]);
		close(Taccu_guichet[1]);
		close(Tadmin_accueil[0]);
		close(Tadmin_accueil[1]);
		//execl();

    }

    /*
     * Fin du programme
     */
    return 0;
}
