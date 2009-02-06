/*
 * main.c
 *
 *  Created on: 16 janv. 2009
 *      Author: Charaf SALMI, François HAURIT, Sophie SURMONT
 */

#include "type_definitions.h"

char* journalisation(char* str)
{
	int f;
	printf("ok");
	char str1[] = str;
	//strcat(str1, "\n");
	return " ";
		/*f = open("./journal.txt", O_APPEND | O_CREAT);
	lseek(f, 0, SEEK_END);

	write(f, &str1, sizeof(char*));

	return strcat(str, " \n");*/
}

/**
 * Point d'entrée de l'application
 * @param nbarg
 * @param tbarg : tbarg[0]: ftransaction_admin, tbarg[1] : ftransaction_client, tbarg[2] : nbguichet
 * @return
 */
int main(int nbarg, char *tbarg[])
{

	journalisation("Salut !!");
	/*
	 * Si il n'y a pas tous les arguments ou si le nombre de guichets est
	 * supérieur à NB_max_guichets, on quitte.
	 */
	/*if(nbarg != 3 || (atoi(tbarg[2]) > NB_max_guichets))
	{
		printf("agence: usage: agence f<fichier1> f<fichier2> <nbguichet> \n");
		printf("Options:\n");
		printf("\t<fichier1>\t\tChemin vers le fichier …\n");
		printf("\t<fichier2>\t\tChemin vers le fichier …\n");
		printf("\t<nbguichet>\t\tNombre de guichets entre 1 et %d\n",
				NB_max_guichets);
		exit(1);
	}*/

	/*
	 * Ouverture des tubes
	 */
	pipe(Taccu_guichet);
	pipe(Tadmin_accueil);

	/*
	 * Variables algorithmiques
	 */
	char code_consultation = '\0';
	code_consultation = '\0';

	/*
	 * Action pour le processus Pdirection
	 */
	if((pidDirection = fork()) < 0)
	{
		perror("Erreur dans la création du processus Pdirection.");
		exit(1);
	}
	else
		if(pidDirection == 0)
		{
			/*
			 * Bienvenue dans le processus fils Pdirection.
			 */
			execl("pdirection", "pdirection", tbarg[0], tbarg[1], tbarg[2], NULL);
		}

	/*
	 * Fin du programme
	 */
	return 0;
}
