/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 16:52:55 by erazumov          #+#    #+#             */
/*   Updated: 2026/05/24 17:54:11 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCATION_HPP
# define LOCATION_HPP

# include <string>
# include <vector>

class Location
{
private:
	std::string					_path;         // e.g., "/images"
	std::string					_root;         // Root directory on disk
	std::string					_index;        // Default file
	std::string					_redirect;     // HTTP redirection URL
	std::string					_uploadStore;  // Directory for uploaded files
	std::vector<std::string>	_methods;      // Allowed HTTP methods
	bool						_autoindex;    // Directory listing switch

public:
	/* --- Orthodox Canonical Form --- */
	Location();
	Location(const Location &copy);
	Location	&operator=(const Location &other);
	~Location();

	/* --- Setters --- */
	void	setPath(const std::string &path);
	void	setRoot(const std::string &root);
	void	setIndex(const std::string &index);
	void	setRedirect(const std::string &redirect);
	void	setUploadStore(const std::string &store);
	void	setMethods(const std::vector<std::string> &methods);
	void	setAutoindex(bool autoindex);

	/* --- Getters --- */
	const std::string				&getPath() const;
	const std::string				&getRoot() const;
	const std::string				&getIndex() const;
	const std::string				&getRedirect() const;
	const std::string				&getUploadStore() const;
	const std::vector<std::string>	&getMethods() const;
	bool							getAutoindex() const;
};

#endif