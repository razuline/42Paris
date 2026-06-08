/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 19:21:54 by erazumov          #+#    #+#             */
/*   Updated: 2026/06/09 00:24:48 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Utils.hpp"

#include <csignal>
#include <sstream>

namespace Utils
{
	std::string
	getMimeType(const std::string &path)
	{
		// 1. Find the position of the last dot '.' in the path
		size_t dotPos = path.find_last_of('.');

		if (dotPos == std::string::npos)
			return "text/plain";

		// 2. Extract the extension (everything after the dot)
		std::string ext = path.substr(dotPos + 1);

		// 3. Map common extensions to their official MIME types
		if (ext == "html" || ext == "htm")
			return "text/html";
		if (ext == "css")
			return "text/css";
		if (ext == "js")
			return "text/javascript";
		if (ext == "png")
			return "image/png";
		if (ext == "jpg" || ext == "jpeg")
			return "image/jpeg";
		if (ext == "gif")
			return "image/gif";
		if (ext == "ico")
			return "image/x-icon";
		if (ext == "json")
			return "application/json";
		if (ext == "pdf")
			return "application/pdf";

		return "application/octet-stream";
	};

	std::string
	trim(const std::string &str)
	{
		size_t first = str.find_first_not_of(" \t;");
		if (first == std::string::npos)
			return "";

		size_t last = str.find_last_not_of(" \t;");

		return str.substr(first, (last - first + 1));
	}

	std::string
	generateAutoindex(const std::string &dirPath, const std::string &reqPath)
	{
		DIR *dir = opendir(dirPath.c_str());
		struct dirent *entry;
		std::string html;

		if (!dir)
			return "";

		// Ensure the request path ends with a slash for clean relative links
		std::string basePath = reqPath;
		if (basePath.empty() || basePath[basePath.size() - 1] != '/')
			basePath += "/";

		html = "<html>\n<head><title>Index of " + reqPath + "</title></head>\n";
		html += "<body>\n<h1>Index of " + reqPath + "</h1>\n<hr>\n<ul>\n";

		while ((entry = readdir(dir)) != NULL)
		{
			std::string name = entry->d_name;

			// Skip the current directory pointer '.'
			if (name == ".")
				continue;

			// Add trailing slash for directories if OS support entry type flags
			if (entry->d_type == DT_DIR)
				name += "/";

			html += "  <li><a href=\"" + basePath + entry->d_name + "\">" + name + "</a></li>\n";
		}
		closedir(dir);
		html += "</ul>\n<hr>\n</body>\n</html>\n";
		return html;
	}

	std::string
	toStr(int number)
	{
		std::stringstream	ss;
		ss << number;
		return ss.str();
	}

	static std::string getCurrentTime()
	{
		std::time_t now = std::time(0);
		std::tm* now_tm = std::localtime(&now);
		char buf[16];
		std::strftime(buf, sizeof(buf), "[%H:%M:%S]", now_tm);
		return std::string(buf);
	}

	// Лог входящего запроса: [00:11:22] ➜ GET /directory/nop
	void logRequest(const std::string &method, const std::string &path)
	{
		std::string methodColor = CYAN;
		if (method == "POST") methodColor = MAGENTA;
		if (method == "DELETE") methodColor = RED;

		std::cout << WHITE << getCurrentTime() << RESET
				  << " ➜ " << methodColor << BOLD << method << RESET
				  << " " << path << std::endl;
	}

	// Лог ответа сервера: [00:11:22] ◀ 200 OK (/directory/nop/)
	void logResponse(int statusCode, const std::string &path)
	{
		std::string statusColor = GREEN;
		if (statusCode >= 300 && statusCode < 400) statusColor = YELLOW;
		if (statusCode >= 400) statusColor = RED;

		std::cout << WHITE << getCurrentTime() << RESET
				  << " ◀ " << statusColor << BOLD << statusCode << RESET
				  << " (" << path << ")" << std::endl;
	}

	// Лог системных ошибок (например, провал бинда порта)
	void logError(const std::string &message)
	{
		std::cerr << WHITE << getCurrentTime() << RESET
				  << " [" << RED << BOLD << "ERROR" << RESET << "] "
				  << message << std::endl;
	}

	// Лог успешных событий (старт сервера)
	void logInfo(const std::string &message)
	{
		std::cout << WHITE << getCurrentTime() << RESET
				  << " [" << GREEN << BOLD << "INFO" << RESET << "] "
				  << message << std::endl;
	}
}
