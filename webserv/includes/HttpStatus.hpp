/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpStatus.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 21:07:39 by erazumov          #+#    #+#             */
/*   Updated: 2026/06/03 22:35:45 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTP_STATUS_HPP
# define HTTP_STATUS_HPP

namespace Http
{
	enum Code
	{
		CONTINUE = 100,
		SWITCHING_PROTOCOLS,
		PROCESSING,
		EARLY_HINTS,

		OK = 200,
		CREATED,
		ACCEPTED,
		NON_AUTHORITATIVE_INFORMATION,
		NO_CONTENT,
		RESET_CONTENT,
		PARTIAL_CONTENT,
		MULTI_STATUS,
		ALREADY_REPORTED,
		IM_USED = 226,

		MULTIPLE_CHOICES = 300,
		MOVED_PERMANENTLY,
		FOUND,
		SEE_OTHER,
		NOT_MODIFIED,
		TEMPORARY_REDIRECT = 307,
		PERMANENT_REDIRECT,

		BAD_REQUEST = 400,
		UNAUTHORIZED,
		PAYMENT_REQUIRED,
		FORBIDDEN,
		NOT_FOUND,
		METHOD_NOT_ALLOWED,
		NOT_ACCEPTABLE,
		PROXY_AUTHENTICATION_REQUIRED,
		REQUEST_TIMEOUT,
		CONFLICT,
		GONE,
		LENGTH_REQUIRED,
		PRECONDITION_FAILED,
		PAYLOAD_TOO_LARGE,
		URI_TOO_LONG,
		UNSUPPORTED_MEDIA_TYPE,
		RANGE_NOT_SATISFIABLE,
		EXPECTATION_FAILED,
		IM_A_TEAPOT, // 🫖
		MISDIRECTED_REQUEST = 421,
		UNPROCESSABLE_ENTITY,
		LOCKED,
		FAILED_DEPENDENCY,
		TOO_EARLY,
		UPGRADE_REQUIRED,
		PRECONDITION_REQUIRED = 428,
		TOO_MANY_REQUESTS,
		HEADER_FIELDS_TOO_LARGE = 431,
		UNAVAILABLE_FOR_LEGAL_REASONS = 451,

		INTERNAL_SERVER_ERROR = 500,
		NOT_IMPLEMENTED,
		BAD_GATEWAY,
		SERVICE_UNAVAILABLE,
		GATEWAY_TIMEOUT,
		HTTP_VERSION_NOT_SUPPORTED,
		VARIANT_ALSO_NEGOTIATES,
		INSUFFICIENT_STORAGE,
		LOOP_DETECTED,
		NOT_EXTENDED = 510,
		NETWORK_AUTHENTICATION_REQUIRED,
		MAX_STATUS = 599
	};
}

#endif