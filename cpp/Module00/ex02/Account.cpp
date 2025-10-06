/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Account.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 16:14:37 by erazumov          #+#    #+#             */
/*   Updated: 2025/10/06 21:35:02 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Account.hpp"
#include <iostream>
#include <ctime>

/*
 * Initialisation des variables static de la classe
 */
int Account::_nbAccounts = 0;
int Account::_totalAmount = 0;
int Account::_totalNbDeposits = 0;
int Account::_totalNbWithdrawals = 0;

/*
 * Le constructeur
 */
Account::Account(int initial_deposit) {
	// Afficher l'horodatage
	Account::_displayTimestamp();
	// Initialiser les variables de ce compte
	this->_accountIndex = Account::_nbAccounts;
	this->_amount = initial_deposit;
	this->_nbDeposits = 0;
	this->_nbWithdrawals = 0;
	// MàJ les totaux de la banque
	Account::_nbAccounts++;
	Account::_totalAmount += this->_amount;
	// Affixher le message de creation
	std::cout << "index:" << this->_accountIndex
			<< ";amount:" << this->_amount
			<< ";created"
			<< std::endl;
}

/*
 * Le destructeur
 */
Account::~Account(void) {
	// Afficher l'horodatage
	Account::_displayTimestamp();
	// Afficher le message de fermeture
	std::cout << "index:" << this->_accountIndex
		<< ";amount:" << this->_amount
		<< ";closed" << std::endl;
}

/* ------------------------------- FUNCTIONS -------------------------------- */

/*
 * Afficher la date et l'heure actuelles au format [YYYYMMDD_HHMMSS]
 */
void	Account::_displayTimestamp(void) {
	// Créer un espace pour stocker la chaîne de caractères formatée
	char	buffer[20];

	// Obtenir l'heure système actuelle
	std::time_t	currTime = std::time(NULL);
	// Formater l'heure dans le buffer selon le modèle demandé
	std::strftime(buffer, sizeof(buffer), "[%Y%m%d_%H%M%S] ",
			std::localtime(&currTime));
	// Afficher le résultat
	std::cout << buffer;
}

/*
 * Donner une vue d'ensemble de tous les comptes, sans se soucier d'un compte
 * en particulier. C'est le rapport global de la banque
 */
void	Account::displayAccountsInfos(void) {
	Account::_displayTimestamp();

	std::cout << "accounts:" << Account::getNbAccounts()
			<< ";total:" << Account::getTotalAmount()
			<< ";deposits:" << Account::getNbDeposits()
			<< ";withdrawals:" << Account::getNbWithdrawals()
			<< std::endl;
}

/* 
 * Afficher les informations d'un compte spécifique 
 */
void	Account::displayStatus(void) const {
	Account::_displayTimestamp();

	std::cout << "index:" << this->_accountIndex
			<< ";amount:" << this->_amount
			<< ";deposits:" << this->_nbDeposits
			<< ";withdrawals:" << this->_nbWithdrawals
			<< std::endl;
}

/*
 * Gèrer les dépôts
 */
void	Account::makeDeposit(int deposit) {
	Account::_displayTimestamp();

	// Afficher le statut AVANT le dépôt et le montant du dépôt
	std::cout << "index:" << this->_accountIndex
			<< ";p_amount:" << this->_amount
			<< ";deposit:" << deposit; // MONTANT du dépôt
	// MàJ
	this->_amount += deposit;
	this->_nbDeposits++;
	Account::_totalAmount += deposit;
	Account::_totalNbDeposits++;
	// Afficher le statut APRES le dépôt
	std::cout << ";amount:" << this->_amount
			<< ";nb_deposits:" << this->_nbDeposits // Nouveau COMPTEUR de dépôts
			<< std::endl;
}

/*
 * La fonction pour les retraits
 */
bool	Account::makeWithdrawal(int withdrawal) {
	Account::_displayTimestamp();

	std::cout << "index:" << this->_accountIndex
			<< ";p_amount:" << this->_amount;

	if (withdrawal > this->_amount) {
		std::cout << ";withdrawal:refused" << std::endl;
		return false; // Le chemin "échec" se termine ici
	}
	else {
		std::cout << ";withdrawal:" << withdrawal;

		this->_amount -= withdrawal;
		this->_nbWithdrawals++;
		Account::_totalAmount -= withdrawal;
		Account::_totalNbWithdrawals++;

		std::cout << ";amount:" << this->_amount
				<< ";nb_withdrawals:" << this->_nbWithdrawals
				<< std::endl;

		return true; // Le chemin "succès" se termine ici
	}
}

/*
 * Retourner le solde actuel du compte
 */
int	Account::checkAmount(void) const {
	return this->_amount;
}

/* -------------------------------- GETTERS --------------------------------- */

int	Account::getNbAccounts(void) {
	return Account::_nbAccounts;
}

int	Account::getTotalAmount(void) {
	return Account::_totalAmount;
}

int	Account::getNbDeposits(void) {
	return Account::_totalNbDeposits;
}

int	Account::getNbWithdrawals(void) {
	return Account::_totalNbWithdrawals;
}
