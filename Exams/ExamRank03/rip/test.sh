#!/bin/sh

# Script de test pour l'exercice 'rip'

EXECUTABLE="./rip"

# On s'assure que le programme est bien compilé
if [ ! -f "$EXECUTABLE" ]; then
    echo "ERREUR: Le programme '$EXECUTABLE' n'a pas été trouvé."
    echo "Veuillez d'abord le compiler (ex: cc -Wall *.c -o rip)"
    exit 1
fi

echo "==============================================="
echo "Lancement des tests pour le programme RIP"
echo "==============================================="

# --- Cas déjà valides ---
echo "\n--- Tests sur des chaînes déjà valides ---"
echo "\n▶ Test avec '()' :"
$EXECUTABLE '()'
echo "\n▶ Test avec '((()()())())' :"
$EXECUTABLE '((()()())())'

# --- Cas avec des parenthèses fermantes en trop ---
echo "\n\n--- Tests avec des parenthèses fermantes en trop ---"
echo "\n▶ Test avec '())' :"
$EXECUTABLE '())'
echo "\n▶ Test avec '()())()' :"
$EXECUTABLE '()())()'

# --- Cas avec des parenthèses ouvrantes en trop ---
echo "\n\n--- Tests avec des parenthèses ouvrantes en trop ---"
echo "\n▶ Test avec '(()' :"
$EXECUTABLE '(()'
echo "\n▶ Test avec '(()(()(' :"
$EXECUTABLE '(()(()('

# --- Cas complexes / Cas limites ---
echo "\n\n--- Tests complexes et cas limites ---"
echo "\n▶ Test avec ')(' :"
$EXECUTABLE ')('
echo "\n▶ Test avec '(((' :"
$EXECUTABLE '((('
echo "\n▶ Test avec ')))' :"
$EXECUTABLE ')))'
echo "\n▶ Test avec une chaîne vide '' :"
$EXECUTABLE ''

echo "\n==============================================="
echo "Tests terminés."
echo "==============================================="