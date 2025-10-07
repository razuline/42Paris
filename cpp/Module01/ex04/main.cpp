/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 14:20:25 by erazumov          #+#    #+#             */
/*   Updated: 2025/10/07 15:24:07 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

int	main(int ac, char **av) {
// --- 1. Validation des arguments ---
	// Le nom du programme + les 3 arguments (nom de fichier, s1, s2).
	if (ac != 4) {
		std::cout << "Usage: ./sed <filename> <s1> <s2>." << std::endl;
		return 1;
	}

	// Stocker les args dans des vars std::string pour plus de facilité.
	std::string		filename = av[1];
	std::string		s1 = av[2];
	std::string		s2 = av[3];

	// Vérifier que s1 n'est pas vide pour éviter une boucle infinie.
	if (s1.empty()) {
		std::cout << "Error: The string to be replaced cannot be empty."
				<< std::endl;
		return 1;
	}

// --- 2. Gestion des fichiers ---
	// Créer un flux pour lire le fichier d'entrée.
	// input file stream ("ouvre" le document original pour le lire)
	std::ifstream	inputFile(filename.c_str());
	// Vérifier si l'ouverture a réussi.
	if (!inputFile.is_open()) {
		std::cout << "Error: Could not open input file." << std::endl;
		return 1; // Quitter si le fichier ne peut pas être lu.
	}

	// Construir le nom du fichier de sortie en ajoutant ".replace".
	std::string		outputFilename = filename + ".replace";
	// Créer un flux pour écrire dans le fichier de sortie.
	// output file stream ("crée" la nouvelle page blanche pour écrire dessus)
	std::ofstream	outputFile(outputFilename.c_str());
	// Vérifie si la création a réussi.
	if (!outputFile.is_open()) {
		std::cout << "Error: Could not create output file." << std::endl;
		inputFile.close(); // On ferme le premier fichier avant de quitter.
		return 1;
	}

// --- 3. Lecture et Remplacement ---
	// Ustringstream pour "aspirer" tout le contenu du fichier d'un coup.
	std::stringstream	buffer;
	buffer << inputFile.rdbuf();
	// Convertir le contenu du buffer en une seule grande chaîne de caractères.
	std::string			content = buffer.str(); // La "photocopie"

	// Chercher la position de la première occurrence de s1.
	size_t				pos = content.find(s1);
	// Boucler tant que 'find' trouve une occurrence (ne retourne pas npos).
	while (pos != std::string::npos) {
		// Effacer l'ancienne chaîne (s1) de la position 'pos'.
		content.erase(pos, s1.length());
		// Insèrer la nouvelle chaîne (s2) à cette même position.
		content.insert(pos, s2);
		// Chercher l'occurrence suivante APRÈS le mot qu'on vient d'insérer.
		pos = content.find(s1, pos + s2.length());
	}

// --- 4. Écriture du résultat ---
	// Écrire le contenu de la chaîne modifiée dans le fichier de sortie.
	outputFile << content;

	// Les fichiers sont automatiquement fermés par les destructeurs 
	// de inputFile et outputFile.
	return 0;
}

/* c_str() est le traducteur. Il prend l'objet std::string moderne et en sort
 * une version const char* que les vieilles fonctions du langage C
 * peuvent comprendre. */