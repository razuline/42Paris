/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpStatusCode.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 21:07:39 by erazumov          #+#    #+#             */
/*   Updated: 2026/06/02 21:07:46 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTP_STATUS_CODE_HPP
# define HTTP_STATUS_CODE_HPP

// Enumeration of HTTP Status Codes supported by webserv
enum HttpStatusCode
{
	// Success (2xx)
	HTTP_OK = 200,
	HTTP_CREATED = 201,
	HTTP_ACCEPTED = 202,
	HTTP_NO_CONTENT = 204,

	// Redirection (3xx)
	HTTP_MOVED_PERMANENTLY = 301,

	// Client Errors (4xx)
	HTTP_BAD_REQUEST = 400,
	HTTP_UNAUTHORIZED = 401,
	HTTP_FORBIDDEN = 403,
	HTTP_NOT_FOUND = 404,
	HTTP_METHOD_NOT_ALLOWED = 405,
	HTTP_PAYLOAD_TOO_LARGE = 413,
	HTTP_HEADERS_TOO_LARGE = 431,

	// Server Errors (5xx)
	HTTP_INTERNAL_SERVER_ERROR = 500,
	HTTP_BAD_GATEWAY = 502,
	HTTP_SERVICE_UNAVAILABLE = 503,
	HTTP_VERSION_NOT_SUPPORTED = 505
};

#endif