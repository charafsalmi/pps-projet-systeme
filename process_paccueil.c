/*
 * process_paccueil.c
 *
 *  Created on: 23 janv. 2009
 *      Author: Charaf SALMI
 */

#include "type_definitions.h"

/*
 * L'accueil reçoit les clients, les oriente éventuellement vers les guichets
 * et affiche les réservations des voyages définitivement clos.
 */

/*
	L'accueil exploite le fichier fTransactions_clients pour y lire ce que veut
	faire le client.
	Si il s'agit d'une consultation, pAccueil écrit le nombre de place
	disponibles ou non dans le terminal et un journal de bord.

	L'accueil exploite aussi le fichier fVoyages qui contient un article par
	voyage.

 */

int main(int nbarg, char *tbarg[])
{
	struct sigaction sigFin, sigAdminCrea, sigAdminSuppr;
	extern void journal(char*, int);

	/*
	 * Compteurs et buffers
	 */
	int i = 0;
	char* cbuffer;

	/*
	 * Paramètres
	 */
	//Nombre de guichets voulus
	int nb_guichets = 0;

	/*
	 * Début du programme
	 */

	//Signaux
	sigFin.sa_handler=finAccueil;
	sigFin.sa_flags=0;
	sigFin.sa_restorer=NULL;
	sigaction(SIGTERM,&sigFin,NULL);
	sigAdminCrea.sa_handler=AdminCrea;
	sigAdminCrea.sa_flags=0;
	sigAdminCrea.sa_restorer=NULL;
	sigaction(SIGUSR1,&sigAdminCrea,NULL);
	sigAdminSuppr.sa_handler=AdminSuppr;
	sigAdminSuppr.sa_flags=0;
	sigAdminSuppr.sa_restorer=NULL;

	for(i = 0; i < nb_guichets; ++i)
	{
		if((pidGuichet[i] = fork()) < 0)
		{
			sprintf(cbuffer,
					"Erreur dans la création du processus Pguichet[%d].", i);
			perror(cbuffer);
			exit(errno);
		}
		else
			if(pidGuichet[i] == 0)
			{
				/*
				 * Bienvenue dans le processus fils Pguichet[i]
				 */
				//execl("process_guichet");
				exit(1);
			}
	}

	/*
	 * Fin du programme
	 */
	return 0;
}
