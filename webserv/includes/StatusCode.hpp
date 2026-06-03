/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StatusCode.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 21:07:39 by erazumov          #+#    #+#             */
/*   Updated: 2026/06/03 14:07:54 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STATUS_CODE_HPP
# define STATUS_CODE_HPP

// Enumeration of HTTP Status Codes supported by webserv
enum StatusCode
{
	SC_100 = 100,
	SC_101,
	SC_102,
	SC_103,
	SC_200 = 200,
	SC_201,
	SC_202,
	SC_203,
	SC_204,
	SC_205,
	SC_206,
	SC_207,
	SC_208,
	SC_226 = 226,
	SC_300 = 300,
	SC_301,
	SC_302,
	SC_303,
	SC_304,
	SC_307 = 307,
	SC_308,
	SC_400 = 400,
	SC_401,
	SC_402,
	SC_403,
	SC_404,
	SC_405,
	SC_406,
	SC_407,
	SC_408,
	SC_409,
	SC_410,
	SC_411,
	SC_412,
	SC_413,
	SC_414,
	SC_415,
	SC_416,
	SC_417,
	SC_418,
	SC_421 = 421,
	SC_422,
	SC_423,
	SC_424,
	SC_425,
	SC_426,
	SC_428,
	SC_429,
	SC_431 = 431,
	SC_451 = 451,
	SC_500 = 500,
	SC_501,
	SC_502,
	SC_503,
	SC_504,
	SC_505,
	SC_506,
	SC_507,
	SC_508,
	SC_510 = 510,
	SC_511,
	SC_MAX = 599
};

#endif