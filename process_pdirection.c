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
	int Tadmin_accu[2],
	    Taccu_guichet[2];
	pipe(Tadmin_accu);
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
			close(Tadmin_accu[1]);
			execl("pAccueil","pAccueil",Tadmin_accu[0],Taccu_guichet[0],Taccu_guichet[1],NULL);
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
			close(Tadmin_accu[0]);
			close(Taccu_guichet[0]);
			close(Taccu_guichet[1]);
			execl("pAdmin","pAdmin",Tadmin_accu[1],pidAccueil,NULL);
		}
	int e;
	wait(&e);
	kill(SIGUSR1,pidAdministration);
	wait(&e);
	return 0;
}
