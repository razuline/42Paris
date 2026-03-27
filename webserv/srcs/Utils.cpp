/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 19:21:54 by erazumov          #+#    #+#             */
/*   Updated: 2026/03/27 19:23:25 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Utils.hpp"

namespace Utils
{
	std::string	getMimeType(const std::string &path)
	{
		// 1. Find the position of the last dot '.' in the path
		size_t		dotPos = path.find_last_of('.');

		// 2. If no dot is found, it doesn't know the type.
		// Default to "text/plain" (basic text).
		if (dotPos == std::string::npos)
			return "text/plain";

		// 3. Extract the extension (everything after the dot)
		std::string	ext = path.substr(dotPos + 1);

		// 4. Map common extensions to their official MIME types
		if (ext == "html" || ext == "htm") return "text/html";
		if (ext == "css")                  return "text/css";
		if (ext == "js")                   return "text/javascript";
		if (ext == "png")                  return "image/png";
		if (ext == "jpg" || ext == "jpeg") return "image/jpeg";
		if (ext == "gif")                  return "image/gif";
		if (ext == "ico")                  return "image/x-icon";
		if (ext == "json")                 return "application/json";
		if (ext == "pdf")                  return "application/pdf";

		// 5. Default fallback for unknown files
		return "application/octet-stream";
	}
}
