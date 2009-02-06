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
	char param1[256];
	char param2[256];
	char param3[256];
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
			printf("dans le fork accueil\n");
			sprintf(param1, "%d", Tadmin_accueil[0]);
			sprintf(param2, "%d", Taccu_guichet[0]);
			sprintf(param3, "%d", Taccu_guichet[1]);
			close(Tadmin_accueil[1]);
			 printf("%d\n",atoi(tbarg[3]));
			if(execl("paccueil","paccueil",param1, param2, param3, tbarg[2], tbarg[3], NULL)==-1)
			{
				printf("Erreur de lancement de l'execl paccueil\n");
			}
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
			printf("dans le fork admin\n");
			close(Tadmin_accueil[0]);
			close(Taccu_guichet[0]);
			close(Taccu_guichet[1]);
			sprintf(param1, "%d",Tadmin_accueil[1]);
			sprintf(param2, "%d", pidAccueil);
			printf("%s\n", tbarg[1]);
			execl("padmin","padmin", tbarg[1], param1, param2, (char*)NULL);
			 
				printf("Erreur de lancement de l'execl padmin\n");
				printf("erreur : %s\n",strerror(errno));
			exit(8);
		}
	int e;
	wait(&e);
	kill(SIGUSR1,pidAdministration);
	wait(&e);
	return 0;
}
