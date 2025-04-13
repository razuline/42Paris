#!/bin/bash

# --- Настройки ---
PUSH_SWAP_EXEC="./push_swap"     # Путь к твоей программе
CHECKER_EXEC="./checker_Mac"         # Путь к checker (убедись, что он есть и рабочий)
# Максимально допустимое кол-во операций (измени согласно требованиям)
MAX_OPS_3=3
MAX_OPS_5=12
MAX_OPS_100=100 # Пример (чем меньше, тем лучше)
MAX_OPS_500=500 # Пример (чем меньше, тем лучше)

# --- Цвета ---
GREEN="\033[0;32m"
RED="\033[0;31m"
YELLOW="\033[0;33m"
RESET="\033[0m"
BOLD="\033[1m"

# --- Счетчик ошибок ---
FAIL_COUNT=0

# --- Функция для запуска одного теста ---
# Параметры: Название_теста Ожидаемый_результат(OK/Error) Макс_операций(для OK) Аргументы...
run_test() {
	local title=$1
	local expected_result=$2
	local max_ops=$3
	shift 3 # Сдвигаем аргументы, оставляя только числа для push_swap
	local args_str="$*" # Строка с числами

	echo -n -e "${YELLOW}${BOLD}Test:${RESET}${YELLOW} ${title} (${args_str:-Empty})${RESET} ... "

	# Выполняем push_swap, ловим stdout (операции) и stderr (ошибки)
	local ops_output
	local error_output
	# Хитрость для разделения stdout и stderr
	ops_output=$( { $PUSH_SWAP_EXEC $args_str ; } 2> >(error_output=$(cat); cat >&2) )

	# 1. Проверка на ОШИБКУ
	if [ "$expected_result" == "Error" ]; then
		if [[ "$error_output" == "Error" ]]; then
			echo -e "${GREEN}PASSED (Error as expected)${RESET}"
		else
			echo -e "${RED}FAILED${RESET}"
			echo -e "      Expected: Error"
			echo -e "      Got stdout: '$ops_output'"
			echo -e "      Got stderr: '$error_output'"
			((FAIL_COUNT++))
		fi
		return
	fi

	# 2. Проверка на НЕОЖИДАННУЮ ОШИБКУ
	if [[ "$error_output" == "Error" ]]; then
		echo -e "${RED}FAILED (Got Error unexpectedly)${RESET}"
		((FAIL_COUNT++))
		return
	elif [[ ! -z "$error_output" ]]; then
		# Если есть другой вывод в stderr - тоже плохо
		 echo -e "${RED}FAILED (Unexpected stderr: '$error_output')${RESET}"
		 ((FAIL_COUNT++))
		 return
	fi

	# 3. Проверка корректности через CHECKER (если ожидался OK)
	local checker_result=""
	# Если аргументов не было, checker может вести себя по-разному
	if [ $# -eq 0 ]; then
		# Если push_swap ничего не вывел (0 опс), то OK
		[ -z "$ops_output" ] && checker_result="OK" || checker_result="KO"
	else
		# Передаем операции в checker
		 checker_result=$(echo -n "$ops_output" | $CHECKER_EXEC $args_str 2>/dev/null)
	fi

	if [ "$checker_result" != "OK" ]; then
		echo -e "${RED}FAILED (Checker: $checker_result)${RESET}"
		echo -e "      Operations:\n$ops_output" # Показываем операции, которые привели к KO
		((FAIL_COUNT++))
		return
	fi

	# 4. Проверка количества операций (если ожидался OK)
	local op_count
	# Считаем строки в выводе push_swap
	op_count=$(echo -n "$ops_output" | wc -l | awk '{print $1}')

	# Сравниваем с максимальным лимитом
	if [ "$max_ops" -ne -1 ] && [ "$op_count" -gt "$max_ops" ]; then
		echo -e "${RED}FAILED (Ops: $op_count > $max_ops)${RESET}"
		((FAIL_COUNT++))
	else
		# Если все проверки пройдены
		echo -e "${GREEN}PASSED (Checker: OK, Ops: $op_count <= $max_ops)${RESET}"
	fi
}

# --- Запуск Тестов ---
echo -e "\n${BOLD}=== Error Handling Tests ===${RESET}"
run_test "Duplicate" Error -1 1 5 3 5
run_test "Non-numeric" Error -1 1 two 3
run_test "Max Int + 1" Error -1 2147483648
run_test "Min Int - 1" Error -1 -2147483649
# Добавь еще тесты на ошибки

echo -e "\n${BOLD}=== Basic & Small Cases ===${RESET}"
run_test "No args" OK 0
run_test "Single arg" OK 0 42
run_test "Sorted 3" OK 0 1 2 3
run_test "Size 2 Unsorted" OK 1 2 1
run_test "Size 3 Rev" OK $MAX_OPS_3 3 2 1
run_test "Size 3 Var 1" OK $MAX_OPS_3 2 1 3
run_test "Size 3 Var 2" OK $MAX_OPS_3 3 1 2
run_test "Size 5 Rev" OK $MAX_OPS_5 5 4 3 2 1
# Добавь еще тесты на 3 и 5

echo -e "\n${BOLD}=== Random Large Tests ===${RESET}"
# Тест на 100 чисел
echo "Testing Size 100..."
# Генерируем случайные числа от -50 до 49 (пример)
ARG_100=$(seq -50 49 | gshuf | tr '\n' ' ')
run_test "Random 100" OK $MAX_OPS_100 $ARG_100

# Тест на 500 чисел
echo "Testing Size 500..."
# Генерируем случайные числа от 1 до 500
ARG_500=$(seq 1 500 | gshuf | tr '\n' ' ')
run_test "Random 500" OK $MAX_OPS_500 $ARG_500

# Можно добавить цикл для нескольких случайных тестов

# --- Итог ---
echo -e "\n${BOLD}=== Testing Complete ===${RESET}"
if [ $FAIL_COUNT -eq 0 ]; then
	echo -e "${GREEN}${BOLD}All tests passed! ✔${RESET}"
else
	echo -e "${RED}${BOLD}$FAIL_COUNT test(s) failed! ✘${RESET}"
fi

exit $FAIL_COUNT