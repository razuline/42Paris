/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Account.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 16:14:37 by erazumov          #+#    #+#             */
/*   Updated: 2025/10/03 16:56:31 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Account.hpp"
#include <iostream>
#include <ctime>

Account::Account(int initial_deposit) {
	
}

Account::~Account(void) {
	
}

/* ------------------------------- FUNCTIONS -------------------------------- */

void	Account::displayAccountsInfos(void) {
	
}

void	Account::_displayTimestamp(void) {
	
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
