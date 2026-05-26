/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 16:52:55 by erazumov          #+#    #+#             */
/*   Updated: 2026/05/26 17:41:17 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCATION_HPP
# define LOCATION_HPP

# include <string>
# include <vector>

class Location
{
private:
	std::string					_path;
	std::string					_root;
	std::string					_index;
	std::string					_redirect;
	std::string					_uploadStore;
	std::vector<std::string>	_methods;
	bool						_autoindex;

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