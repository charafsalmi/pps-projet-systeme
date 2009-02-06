/*
 * process_pdirection.c
 *
 *  Created on: 23 janv. 2009
 *      Author: Charaf SALMI
 */

#include "type_definitions.h"

/**
 * Point d'entrée de l'application
 * @param nbarg
 * @param tbarg
 * @return
 */
int main(int nbarg, char *tbarg[])
{
	/*
	 * Lance pAccueil en premier pour lui donner le pid de pAdministration
	 */
	pipe(Tadmin_accueil);
	pipe(Taccu_guichet);
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
			close(Tadmin_accueil[1]);
			execl("paccueil","paccueil",Tadmin_accueil[0],Taccu_guichet[0],Taccu_guichet[1], tbarg[1], tbarg[2], NULL);
			exit(0);
		}

	/*
	 * Lance pAdministration
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
			close(Taccu_guichet[0]);
			close(Taccu_guichet[1]);
			execl("padmin","padmin", tbarg[0], Tadmin_accueil[1], pidAccueil, NULL);
		}
	int e;
	wait(&e);
	kill(SIGUSR1,pidAdministration);
	wait(&e);
	return 0;
}
