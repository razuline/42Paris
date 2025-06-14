#!/bin/bash

# Configuration
PHILOSOPHER_BIN="./philo"
TEMP_OUTPUT="/tmp/philo_output.txt"
LOG_FILE="test_results.log"

# Couleurs pour la sortie
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[0;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Fonction pour exécuter un test
run_test() {
    TEST_NAME="$1"
    ARGS="$2"
    EXPECTED_EXIT_CODE="$3"
    EXPECTED_OUTPUT_REGEX="$4"
    TIMEOUT_SEC="$5" # Timeout for the command in seconds

    echo -e "${BLUE}--- Running Test: ${TEST_NAME} ---${NC}" | tee -a "$LOG_FILE"
    echo "Command: ${PHILOSOPHER_BIN} ${ARGS}" | tee -a "$LOG_FILE"

    # Exécute la commande avec un timeout
    # La sortie est redirigée vers un fichier temporaire
    timeout "$TIMEOUT_SEC" ${PHILOSOPHER_BIN} ${ARGS} > "$TEMP_OUTPUT" 2>&1
    ACTUAL_EXIT_CODE=$?

    # Vérifie le code de retour du timeout. 124 si timeout expiré.
    if [ $ACTUAL_EXIT_CODE -eq 124 ]; then
        echo -e "${YELLOW}WARNING: Test timed out after ${TIMEOUT_SEC}s.${NC}" | tee -a "$LOG_FILE"
    fi

    # Vérifie le code de sortie du programme
    if [ "$ACTUAL_EXIT_CODE" -eq "$EXPECTED_EXIT_CODE" ]; then
        echo -e "${GREEN}  [PASS] Exit Code: Expected ${EXPECTED_EXIT_CODE}, Got ${ACTUAL_EXIT_CODE}.${NC}" | tee -a "$LOG_FILE"
        PASS_EXIT_CODE=true
    else
        echo -e "${RED}  [FAIL] Exit Code: Expected ${EXPECTED_EXIT_CODE}, Got ${ACTUAL_EXIT_CODE}.${NC}" | tee -a "$LOG_FILE"
        PASS_EXIT_CODE=false
    fi

    # Vérifie la sortie du programme (si un regex est fourni)
    if [ -n "$EXPECTED_OUTPUT_REGEX" ]; then
        if grep -qE "$EXPECTED_OUTPUT_REGEX" "$TEMP_OUTPUT"; then
            echo -e "${GREEN}  [PASS] Output Regex: '${EXPECTED_OUTPUT_REGEX}' found.${NC}" | tee -a "$LOG_FILE"
            PASS_OUTPUT=true
        else
            echo -e "${RED}  [FAIL] Output Regex: '${EXPECTED_OUTPUT_REGEX}' NOT found.${NC}" | tee -a "$LOG_FILE"
            echo -e "${YELLOW}----- Actual Output Start -----${NC}" | tee -a "$LOG_FILE"
            cat "$TEMP_OUTPUT" | tee -a "$LOG_FILE"
            echo -e "${YELLOW}----- Actual Output End -----${NC}" | tee -a "$LOG_FILE"
            PASS_OUTPUT=false
        fi
    else
        # Si aucun regex n'est attendu, affiche la sortie si non vide
        if [ -s "$TEMP_OUTPUT" ]; then # -s checks if file has size > 0
            echo -e "${YELLOW}----- Actual Output (no regex check) -----${NC}" | tee -a "$LOG_FILE"
            cat "$TEMP_OUTPUT" | tee -a "$LOG_FILE"
            echo -e "${YELLOW}-----------------------------------------${NC}" | tee -a "$LOG_FILE"
        fi
        PASS_OUTPUT=true # Pas de vérification de sortie, donc toujours "pass"
    fi
    
    if $PASS_EXIT_CODE && $PASS_OUTPUT; then
        echo -e "${GREEN}Test ${TEST_NAME} PASSED!${NC}\n" | tee -a "$LOG_FILE"
        return 0 # Test passed
    else
        echo -e "${RED}Test ${TEST_NAME} FAILED!${NC}\n" | tee -a "$LOG_FILE"
        return 1 # Test failed
    fi
}

# Crée le fichier de log et le vide
> "$LOG_FILE"
echo "Starting Philsopher Tests at $(date)" | tee -a "$LOG_FILE"
echo "-------------------------------------" | tee -a "$LOG_FILE"

# Assurez-vous que le binaire existe
if [ ! -f "$PHILOSOPHER_BIN" ]; then
    echo -e "${RED}Error: ${PHILOSOPHER_BIN} not found. Please compile your project first. (e.g., make)${NC}"
    exit 1
fi

# --- Exécution des tests ---

# Tests d'arguments invalides
run_test "Invalid Args - No Args" "" 1 "Usage" 2
run_test "Invalid Args - Too Few" "5" 1 "Usage" 2
run_test "Invalid Args - Non-numeric philo count" "abc 800 200 200" 1 "Error: Invalid philosopher count" 2
run_test "Invalid Args - Negative time_to_die" "5 -800 200 200" 1 "Error: Invalid time_to_die" 2
run_test "Invalid Args - Zero philosophers" "0 800 200 200" 1 "Error: Invalid philosopher count" 2

# Tests de fonctionnement sans mort
run_test "Basic Run - 5 philos, no death expected" "5 800 200 200" 124 "" 5 # Timeout 5s, 124 = timeout exit code

# Tests de scénarios de mort
run_test "Death Scenario - 1 philo dies" "1 50 100 0" 0 "1 died" 2 # 1 philo dies
run_test "Death Scenario - Multiple philos die" "5 100 200 50" 0 "died" 3 # Some philos should die

# Tests avec limite de repas
run_test "Meal Limit - 5 philos, 5 meals each" "5 800 200 200 5" 0 "" 5 # Should exit gracefully, no specific output for success, just termination

# Test combinant repas et mort (celui-ci est tricky car l'ordre de sortie peut varier)
# On s'attend à une mort avant la fin des repas
run_test "Meal Limit & Death - philos die before meals complete" "5 100 200 50 5" 0 "died" 3

echo -e "${BLUE}-------------------------------------${NC}" | tee -a "$LOG_FILE"
echo "All tests finished. Check ${LOG_FILE} for details." | tee -a "$LOG_FILE"

# Clean up temporary file
rm -f "$TEMP_OUTPUT"