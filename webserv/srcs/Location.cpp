/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 16:53:12 by erazumov          #+#    #+#             */
/*   Updated: 2026/05/26 17:42:19 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Location.hpp"

/* ------------------------- ORTHODOX CANONICAL FORM ------------------------ */

Location::Location() :
	_path(""),
	_root(""),
	_index(""),
	_redirect(""),
	_uploadStore(""),
	_methods(),
	_autoindex(false)
{
}

Location::Location(const Location &copy) :
	_path(copy._path),
	_root(copy._root),
	_index(copy._index),
	_redirect(copy._redirect),
	_uploadStore(copy._uploadStore),
	_methods(copy._methods),
	_autoindex(copy._autoindex)
{
}

Location
&Location::operator=(const Location &other)
{
	if (this != &other)
	{
		_path = other._path;
		_root = other._root;
		_index = other._index;
		_redirect = other._redirect;
		_uploadStore = other._uploadStore;
		_methods = other._methods;
		_autoindex = other._autoindex;
	}
	return *this;
}

Location::~Location()
{
}

/* -------------------------------- SETTERS --------------------------------- */

void
Location::setPath(const std::string &path)
{
	_path = path;
}

void
Location::setRoot(const std::string &root)
{
	_root = root;
}

void
Location::setIndex(const std::string &index)
{
	_index = index;
}

void
Location::setRedirect(const std::string &redirect)
{
	_redirect = redirect;
}

void
Location::setUploadStore(const std::string &store)
{
	_uploadStore = store;
}

void
Location::setMethods(const std::vector<std::string> &methods)
{
	_methods = methods;
}

void
Location::setAutoindex(bool autoindex)
{
	_autoindex = autoindex;
}

/* -------------------------------- GETTERS --------------------------------- */

const std::string
&Location::getPath() const
{
	return _path;
}

const std::string
&Location::getRoot() const
{
	return _root;
}

const std::string
&Location::getIndex() const
{
	return _index;
}

const std::string
&Location::getRedirect() const
{
	return _redirect;
}

const std::string
&Location::getUploadStore() const
{
	return _uploadStore;
}

const std::vector<std::string>
&Location::getMethods() const
{
	return _methods;
}

bool
Location::getAutoindex() const
{
	return _autoindex;
}
