/*
 * process_paccueil.c
 *
 *  Created on: 23 janv. 2009
 *      Author: Charaf SALMI
 */

#include "type_definitions.h"

int chercher_dans_fVoyage(char* Voyage)
{
	struct produit p;
	int f, g;

	if((f = open("fVoyages", O_RDONLY)) < 0)
	{
		perror("Impossible d'ouvrir fVoyages. \n");
		exit(1);
	}

	while(read(f, &p, sizeof(Produit)))
	{
		if(!strcmp(p.identp, Voyage))
			return 1;
	}

	close(f);
	return 0;
}

int main(int nbarg, char *tbarg[])
{
	int i = 0;
	char* cbuffer;

	/*
	 * Création des guichets
	 */
	int nb_guichets = 2; //argument de l'application

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
				//execl("pguichet", "pguichet", i, Taccu_guichet[0], NULL);
				//exit(1);
			}
	}

	/*
	 * Ouverture du fichier fTransactions_clients
	 */

	int fTransac;
	if((fTransac = open("fTransactions_clients", O_RDONLY | O_CREAT,S_IRWXU)) < 0)
	{
		perror("Erreur d'ouverture du fichier 'fTransactions_clients'\n");
		exit(errno);
	}

	/*
	 * Traitement
	 */
	struct transaction t;

	//se placer au début
	lseek(fTransac, 0, SEEK_SET);

	//lire les transactions
	while(read(fTransac,&t, sizeof(t)))
	{
		/*
		 * Traitement du signal
		 */
		//Tester que si on reçoit un signal

		/*
		 * Traitement de la transaction en cours
		 */
		//Si code = C
		if(t.code == 'C')
		{
			//vérifier l'existance du voyage dans fVoyage
			if(chercher_dans_fVoyage(t.identp))
			{
				//Ecrire la transaction dans le tube
			}
			else
			{
				//Si il n'existe pas
					//C'est la première réservation
					//L'ajouter dans le fichier créé Reservation/[t.identp].fa
					//Incrémenter le fichier créé ACreer/[t.identp].desc
			}
		}
	}

	/*
	 * Fin du programme
	 */
	return 0;
}
