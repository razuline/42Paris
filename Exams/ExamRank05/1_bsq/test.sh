#!/bin/bash

# BSQ Test Suite - Creates all test files and runs checks

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

echo "BSQ Test Suite - Creating test files..."

# Test 1: Basic example (from subject)
cat > test1_basic.txt << 'EOF'
9 . o x
...........................
....o......................
............o..............
...........................
....o......................
...............o...........
...........................
......o..............o.....
..o.......o................
EOF

# Test 2: Small 3x3 map
cat > test2_small.txt << 'EOF'
3 - # +
---
-#-
---
EOF

# Test 3: Single line only
cat > test3_single_line.txt << 'EOF'
1 . o x
.....
EOF

# Test 4: Map with only one 1x1 square possible
cat > test4_obstacles.txt << 'EOF'
4 . o x
oooo
o..o
o..o
oooo
EOF

# Test 5: Map without obstacles (all empty)
cat > test5_no_obstacles.txt << 'EOF'
5 _ # X
_____
_____
_____
_____
_____
EOF

# Test 6: Perfect square in the center
cat > test6_perfect.txt << 'EOF'
7 . # X
#######
#.....#
#.....#
#.....#
#.....#
#.....#
#######
EOF

# Test 7: Multiple squares of same size (should choose top-left)
cat > test7_multiple.txt << 'EOF'
5 . o x
.....
.....
.....
.....
.....
EOF

# Test 8: Large map with complex pattern
cat > test8_large.txt << 'EOF'
12 . # X
............
.###........
....#.......
............
........####
............
.......#....
............
............
############
............
............
EOF

# ========== ERROR TESTS ==========

# Test E1: Duplicate characters in header
cat > error1_duplicate_chars.txt << 'EOF'
3 . . x
...
...
...
EOF

# Test E2: Different line lengths
cat > error2_different_lengths.txt << 'EOF'
3 . o x
...
..
...
EOF

# Test E3: Wrong number of rows (says 5 but has 3)
cat > error3_wrong_rows.txt << 'EOF'
5 . o x
...
...
...
EOF

# Test E4: Invalid character in map
cat > error4_invalid_char.txt << 'EOF'
3 . o x
...
.a.
...
EOF

# Test E5: Empty line
cat > error5_empty_line.txt << 'EOF'
3 . o x
...

...
EOF

# Test E6: Malformed header
cat > error6_bad_header.txt << 'EOF'
abc . o x
...
...
...
EOF

# Test E7: Zero rows
cat > error7_zero_rows.txt << 'EOF'
0 . o x
EOF

# Test E8: Non-printable characters (tab in header)
cat > error8_nonprintable.txt << 'EOF'
3 . 	 x
...
...
...
EOF

# Test E9: Empty file
cat > error9_empty.txt << 'EOF'
EOF

# Test E10: Header only
cat > error10_header_only.txt << 'EOF'
3 . o x
EOF

echo "Test files created!"
echo ""

# Function to run tests
run_test() {
    local test_file=$1
    local test_name=$2
    local expected_result=$3  # "success" or "error"

    echo -n "$test_name: "

    if [[ ! -f "$test_file" ]]; then
        echo -e "${RED}SKIP${NC} (file not found)"
        return
    fi

    # Run the program and capture output and stderr
    output=$(./bsq "$test_file" 2>/dev/null)
    error_output=$(./bsq "$test_file" 2>&1 >/dev/null)
    exit_code=$?

    if [[ "$expected_result" == "error" ]]; then
        if [[ "$error_output" == *"map error"* ]]; then
            echo -e "${GREEN}PASS${NC} (error correctly detected)"
        else
            echo -e "${RED}FAIL${NC} (should have been map error)"
            echo "  Output: '$output'"
            echo "  Error: '$error_output'"
        fi
    else
        if [[ "$error_output" == *"map error"* ]]; then
            echo -e "${RED}FAIL${NC} (unexpected map error)"
            echo "  Error: '$error_output'"
        else
            echo -e "${GREEN}PASS${NC}"
            # Optionally show output for success tests
            if [[ "$4" == "show" ]]; then
                echo "$output"
                echo ""
            fi
        fi
    fi
}

# Compile the program with required flags
echo "Compiling bsq with -Wall -Wextra -Werror..."
if cc -Wall -Wextra -Werror -o bsq *.c; then
    echo -e "${GREEN}Compilation successful!${NC}"
else
    echo -e "${RED}Compilation failed!${NC}"
    exit 1
fi
echo ""

# Check if the program exists
if [[ ! -f "./bsq" ]]; then
    echo -e "${YELLOW}Program './bsq' not found!${NC}"
    echo "   Compile the program first with: cc -Wall -Wextra -Werror -o bsq *.c"
    echo ""
fi

echo "Running success tests..."
echo "=================================="

run_test "test1_basic.txt" "Test 1 - Basic example" "success" "show"
run_test "test2_small.txt" "Test 2 - Small 3x3 map" "success" "show"
run_test "test3_single_line.txt" "Test 3 - Single line only" "success" "show"
run_test "test4_obstacles.txt" "Test 4 - Obstacles everywhere" "success" "show"
run_test "test5_no_obstacles.txt" "Test 5 - No obstacles" "success" "show"
run_test "test6_perfect.txt" "Test 6 - Perfect square" "success" "show"
run_test "test7_multiple.txt" "Test 7 - Multiple squares" "success" "show"
run_test "test8_large.txt" "Test 8 - Large map" "success"

echo ""
echo "Error tests (should fail)..."
echo "====================================="

run_test "error1_duplicate_chars.txt" "Error 1 - Duplicate characters" "error"
run_test "error2_different_lengths.txt" "Error 2 - Different lengths" "error"
run_test "error3_wrong_rows.txt" "Error 3 - Wrong number of rows" "error"
run_test "error4_invalid_char.txt" "Error 4 - Invalid character" "error"
run_test "error5_empty_line.txt" "Error 5 - Empty line" "error"
run_test "error6_bad_header.txt" "Error 6 - Malformed header" "error"
run_test "error7_zero_rows.txt" "Error 7 - Zero rows" "error"
run_test "error8_nonprintable.txt" "Error 8 - Non-printable characters" "error"
run_test "error9_empty.txt" "Error 9 - Empty file" "error"
run_test "error10_header_only.txt" "Error 10 - Header only" "error"

echo ""
echo "Stdin test (copy and paste this command):"
echo "cat test1_basic.txt | ./bsq"
echo ""

echo "Multiple files test:"
echo "./bsq test1_basic.txt test2_small.txt error1_duplicate_chars.txt"
echo ""

echo "Additional manual tests:"
echo "1. Check memory leaks with: valgrind --leak-check=full ./bsq test1_basic.txt"
echo "2. Test with very large files (create a 1000x1000 map)"
echo "3. Test with special characters: spaces, numbers, symbols"
echo ""

# Additional test: create a large map for performance testing
echo "Creating performance test (100x100 map)..."
{
    echo "100 . # X"
    for i in {1..100}; do
        line=""
        for j in {1..100}; do
            if (( RANDOM % 10 == 0 )); then
                line+="#"
            else
                line+="."
            fi
        done
        echo "$line"
    done
} > test_performance_100x100.txt

echo "Performance test created: test_performance_100x100.txt"
echo ""

echo "To run all tests:"
echo "   chmod +x test.sh"
echo "   ./test.sh"
echo ""
echo "For specific debugging:"
echo "   ./bsq test1_basic.txt"
echo "   ./bsq error1_duplicate_chars.txt"