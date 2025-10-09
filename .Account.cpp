/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Account.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 13:58:19 by erazumov          #+#    #+#             */
/*   Updated: 2025/08/03 17:13:56 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Account.hpp"
#include <iostream>
#include <ctime>

int	Account::_nbAccounts = 0;
int	Account::_totalAmount = 0;
int	Account::_totalNbDeposits = 0;
int	Account::_totalNbWithdrawals = 0;

void	Account::_displayTimestamp(void)
{
	time_t		now = time(0);
	struct tm	*ltm = localtime(&now);
	char		buff[20];

	strftime(buff, sizeof(buff), "[%Y%m%d_%H%M%S] ", ltm);

	std::cout << buff;
}

void	Account::displayAccountsInfos(void)
{
	_displayTimestamp();
	std::cout << "accounts:" << getNbAccounts() << ";";
	std::cout << "total:" << getTotalAmount() << ";";
	std::cout << "deposits:" << getNbDeposits() << ";";
	std::cout << "withdrawals:" << getNbWithdrawals() << std::endl;
}

void	Account::displayStatus(void) const
{
	_displayTimestamp();
	std::cout << "index:" << this->_accountIndex << ";";
	std::cout << "amount:" << this->_amount << ";";
	std::cout << "deposits:" << this->_nbDeposits << std::endl;
}

void	Account::makeDeposit(int deposit)
{
	// 1. Affichez le timestamp et les infos de la transaction
	_displayTimestamp();
	std::cout << "index:" << this->_accountIndex << ";";
	std::cout << "p_amount:" << this->_amount << ";"; // Montant précédent
	std::cout << "deposit:" << deposit << ";";

	// 2. Mettez à jour les variables de l'instance
	this->_amount += deposit;
	this->_nbDeposits++;

	// 3. Mettez à jour les variables statiques (globales)
	Account::_totalAmount += deposit;
	Account::_totalNbDeposits++;

	// 4. Affichez le nouvel état du compte
	std::cout << "amount:" << this->_amount << ";";
	std::cout << "nb_deposits:" << this->_nbDeposits << std::endl;
}

bool	Account::makeWithdrawal(int withdrawal)
{
	// 1. Affichez le timestamp et la tentative de retrait
	_displayTimestamp();
	std::cout << "index:" << this->_accountIndex << ";";
	std::cout << "p_amount:" << this->_amount << ";";
	std::cout << "withdrawal:";

	// 2. Vérifiez s'il y a assez d'argent
	if (this->_amount < withdrawal)
	{
		// Pas assez d'argent
		std::cout << "refused" << std::endl;
		return (false);
	}

	// 3. S'il y a assez d'argent, effectuez le retrait
	std::cout << withdrawal << ";";
	
	// Mettez à jour les variables de l'instance
	this->_amount -= withdrawal;
	this->_nbWithdrawals++;

	// Mettez à jour les variables statiques
	Account::_totalAmount -= withdrawal;
	Account::_totalNbWithdrawals++;

	// Affichez le nouvel état et retournez true
	std::cout << "amount:" << this->_amount << ";";
	std::cout << "nb_withdrawals:" << this->_nbWithdrawals << std::endl;
	return (true);
}

Account::Account(int initial_deposit)
{
	this->_accountIndex = Account::_nbAccounts;
	this->_amount = initial_deposit;
	this->_nbDeposits = 0;
	this->_nbWithdrawals = 0;

	Account::_nbAccounts++;
	Account::_totalAmount += initial_deposit;

	Account::_displayTimestamp();
	std::cout << "index:" << this->_accountIndex << ";";
	std::cout << "amount:" << this->_amount << ";";
	std::cout << "created" << std::endl;
}

Account::~Account(void)
{
	Account::_displayTimestamp();
	std::cout << "index:" << this->_accountIndex << ";";
	std::cout << "amount:" << this->_amount << ";";
	std::cout << "closed" << std::endl;
}

int	Account::getNbAccounts(void)
{
	return (_nbAccounts);
}

int	Account::getTotalAmount(void)
{
	return (_totalAmount);
}

int	Account::getNbDeposits(void)
{
	return (_totalNbDeposits);
}

int	Account::getNbWithdrawals(void)
{
	return (_totalNbWithdrawals);
}

int	Account::checkAmount(void) const
{
	return (this->_amount);
}
