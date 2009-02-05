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
	if((pidAccueil = fork()) < 0)
	{
		perror("Erreur dans la création du processus Paccueil.");
		exit(1);
	}
	else
		if(pidAccueil == 0)
		{
			/*
			 * Bienvenue dans le processus fils Paccueil.
			 */
			//execl();
		}

	/*
	 * Lance pAdministration
	 */
	if((pidAdministration = fork()) < 0)
	{
		perror("Erreur dans la création du processus Padministration.");
		exit(errno);
	}
	else
		if(pidAdministration == 0)
		{
			/*
			 * Bienvenue dans le processus fils Padministration.
			 */
			//execl();
		}

	return 0;
}
