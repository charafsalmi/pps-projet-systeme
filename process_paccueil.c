/*
 * process_paccueil.c
 *
 *  Created on: 23 janv. 2009
 *      Author: Charaf SALMI
 */

#include "type_definitions.h"

int main(int nbarg, char *tbarg[])
{
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
