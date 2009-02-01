/*
 * fork_process.h
 *
 *  Created on: 23 janv. 2009
 *      Author: Charaf SALMI
 */

#ifndef FORK_PROCESS_H_
#define FORK_PROCESS_H_

/**
 * @brief
 * @param[in/out] : tube Tadmin_accueil
 * @param[in/out] : tube Taccu_guichet
 */
void call_process_paccueil(int *Tadmin_accueil, int *Taccu_guichet);

/**
 * @brief
 * @param[in/out] : tube Tadmin_accueil
 */
void call_process_padministration(int *Tadmin_accueil);

/**
 * @brief
 */
void call_process_pdirection();

/**
 * @brief
 * @param[in] : numéro de guichet
 * @param[in/out] : tube Taccu_guichet
 */
void call_process_pguichet(const unsigned short int i, int *Taccu_guichet);


#endif /* FORK_PROCESS_H_ */
