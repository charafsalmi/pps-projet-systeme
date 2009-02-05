/*
 * main.c
 *
 *  Created on: 16 janv. 2009
 *      Author: Charaf SALMI, François HAURIT, Sophie SURMONT
 */

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
 * Point d'entrée de l'application
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
	if(nbarg != 3 || (atoi(tbarg[2]) > NB_max_guichets || atoi(tbarg[1]) < 1))
	{
		printf("agence: usage: agence f<fichier1> f<fichier2> <nbguichet> \n");
		printf("Options:\n");
		printf("\tf<fichier1>\t\tChemin vers le fichier …\n");
		printf("\tf<fichier2>\t\tChemin vers le fichier …\n");
		printf("\t<nbguichet>\t\tNombre de guichets entre 1 et %d\n",
				NB_max_guichets);
		exit(1);
	}

	/*
	 * Ouverture du fichier journal
	 */

	// Ouverture du fichier journal
	if((fJournal = open("journal.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644)) < 0)
	{
		perror("Impossible d'ouvrir le fichier journal.");
		exit(1);
	}
	sprintf(flog,"%d",fJournal);
	journal("DEBUT pDirection", fJournal);


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
			//execl("pdirection");
		}

	/*
	 * Fin du programme
	 */
	return 0;
}
