/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 19:21:54 by erazumov          #+#    #+#             */
/*   Updated: 2026/05/26 17:50:37 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Utils.hpp"

namespace Utils
{
	std::string
	getMimeType(const std::string &path)
	{
		// 1. Find the position of the last dot '.' in the path
		size_t		dotPos = path.find_last_of('.');

		if (dotPos == std::string::npos)
			return "text/plain";

		// 2. Extract the extension (everything after the dot)
		std::string	ext = path.substr(dotPos + 1);

		// 3. Map common extensions to their official MIME types
		if (ext == "html" || ext == "htm") return "text/html";
		if (ext == "css")                  return "text/css";
		if (ext == "js")                   return "text/javascript";
		if (ext == "png")                  return "image/png";
		if (ext == "jpg" || ext == "jpeg") return "image/jpeg";
		if (ext == "gif")                  return "image/gif";
		if (ext == "ico")                  return "image/x-icon";
		if (ext == "json")                 return "application/json";
		if (ext == "pdf")                  return "application/pdf";

		return "application/octet-stream";
	};

	std::string
	trim(const std::string &str)
	{
		size_t	first = str.find_first_not_of(" \t;");
		if (first == std::string::npos)
			return "";

		size_t	last = str.find_last_not_of(" \t;");

		return str.substr(first, (last - first + 1));
	}

	std::string
	generateAutoindex(const std::string &dirPath, const std::string &requestPath)
	{
		DIR				*dir = opendir(dirPath.c_str());
		struct dirent	*entry;
		std::string		html;

		if (!dir)
			return "";

		// Ensure the request path ends with a slash for clean relative links
		std::string		basePath = requestPath;
		if (basePath.empty() || basePath[basePath.size() - 1] != '/')
			basePath += "/";

		html = "<html>\n<head><title>Index of " + requestPath + "</title></head>\n";
		html += "<body>\n<h1>Index of " + requestPath + "</h1>\n<hr>\n<ul>\n";

		while ((entry = readdir(dir)) != NULL)
		{
			std::string	name = entry->d_name;

			// Skip the current directory pointer '.'
			if (name == ".")
				continue;

			// Add trailing slash for directories if your OS support entry type flags
			if (entry->d_type == DT_DIR)
				name += "/";

			html += "  <li><a href=\"" + basePath + entry->d_name + "\">" + name + "</a></li>\n";
		}
		closedir(dir);
		html += "</ul>\n<hr>\n</body>\n</html>\n";
		return html;
	}
}
