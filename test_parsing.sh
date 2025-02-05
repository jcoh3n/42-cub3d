#!/bin/bash

# Colors for output
GREEN='\033[0;32m'
RED='\033[0;31m'
BLUE='\033[0;34m'
NC='\033[0m'

# Counter for tests
TOTAL=0
PASSED=0

# Function to run a test
run_test() {
    local map=$1
    local expected_error=$2
    local description=$3
    ((TOTAL++))
    
    echo -e "\n${BLUE}Testing: $description${NC}"
    echo "Map: $map"
    echo "Expected: $expected_error"
    
    # Run the program and capture output
    output=$(./cub3D "$map" 2>&1)
    exit_code=$?
    
    # Check if the output contains the expected error message
    if [[ $expected_error == "SUCCESS" ]]; then
        if [ $exit_code -eq 0 ]; then
            echo -e "${GREEN}✓ Test passed${NC}"
            ((PASSED++))
        else
            echo -e "${RED}✗ Test failed${NC}"
            echo "Got: $output"
        fi
    else
        if [[ $output == *"Error"* && $output == *"$expected_error"* ]]; then
            echo -e "${GREEN}✓ Test passed${NC}"
            ((PASSED++))
        else
            echo -e "${RED}✗ Test failed${NC}"
            echo "Got: $output"
        fi
    fi
}

# Make sure the program is compiled
make re

echo -e "\n${BLUE}=== Starting Parsing Tests ===${NC}\n"

# File existence and format tests
run_test "nonexistent.cub" "Could not open map file" "Non-existent file"
run_test "test.txt" "Invalid file extension" "Wrong file extension"
run_test "maps/directory.cub" "Path is a directory" "Directory instead of file"

# Configuration tests - Textures
run_test "maps/invalid_missing_texture.cub" "Missing texture configuration" "Missing texture"
run_test "maps/duplicate_texture.cub" "Duplicate texture definition" "Duplicate texture"
run_test "maps/invalid_duplicate_texture.cub" "Duplicate texture definition" "Invalid duplicate texture"
run_test "maps/missing_no.cub" "Missing texture configuration" "Missing NO texture"

# Configuration tests - Colors
run_test "maps/invalid_missing_floor.cub" "Invalid color configuration" "Missing floor color"
run_test "maps/missing_floor.cub" "Invalid color configuration" "Missing floor definition"
run_test "maps/invalid_color_range.cub" "Color values must be between 0 and 255" "Invalid color range"
run_test "maps/invalid_color_format.cub" "Invalid color format" "Invalid color format"
run_test "maps/invalid_color.cub" "Invalid color format" "Invalid color value"
run_test "maps/invalid_duplicate_color.cub" "Duplicate color definition" "Invalid duplicate color"
run_test "maps/duplicate_color.cub" "Duplicate color definition" "Duplicate color definition"
run_test "maps/invalid_extra_comma.cub" "Invalid color format" "Extra comma in color"
run_test "maps/invalid_missing_comma.cub" "Invalid color format" "Missing comma in color"
run_test "maps/invalid_non_numeric.cub" "Invalid color format" "Non-numeric in color"
run_test "maps/invalid_empty_color.cub" "Invalid color format" "Empty color value"
run_test "maps/invalid_spaces_between_nums.cub" "Invalid color format" "Spaces between numbers"

# Map structure and format tests
run_test "maps/empty_line_in_map.cub" "Empty line within map" "Empty line in map"
run_test "maps/invalid_empty_lines.cub" "Empty line within map" "Invalid empty lines"
run_test "maps/map_before_config.cub" "Missing texture configuration" "Map before config"
run_test "maps/invalid_map_before_config.cub" "Missing texture configuration" "Invalid map before config"
run_test "maps/invalid_chars.cub" "Invalid character in map" "Invalid characters"
run_test "maps/invalid_map_char.cub" "Invalid character in map" "Invalid map character"

# Map enclosure tests
run_test "maps/open_map.cub" "Map not enclosed by walls" "Open map"
run_test "maps/invalid_not_enclosed.cub" "Map not enclosed by walls" "Not enclosed map"
run_test "maps/invalid_not_properly_enclosed.cub" "Map not enclosed by walls" "Not properly enclosed map"
run_test "maps/space_edge_top.cub" "Map not enclosed by walls" "Space at top edge"
run_test "maps/space_edge_bottom.cub" "Map not enclosed by walls" "Space at bottom edge"
run_test "maps/space_edge_left.cub" "Map not enclosed by walls" "Space at left edge"
run_test "maps/space_edge_right.cub" "Map not enclosed by walls" "Space at right edge"
run_test "maps/space_diagonal.cub" "Map not enclosed by walls" "Space at diagonal"
run_test "maps/space_around_player.cub" "Map not enclosed by walls" "Space around player"

# Player position tests
run_test "maps/no_player.cub" "No player position found" "No player"
run_test "maps/invalid_no_player.cub" "No player position found" "Invalid no player"
run_test "maps/multiple_players.cub" "Multiple player positions found" "Multiple players"
run_test "maps/invalid_multiple_players.cub" "Multiple player positions found" "Invalid multiple players"

# Valid maps - Different orientations
run_test "maps/valid_north.cub" "SUCCESS" "Valid north-facing player"
run_test "maps/valid_south.cub" "SUCCESS" "Valid south-facing player"
run_test "maps/valid_east.cub" "SUCCESS" "Valid east-facing player"
run_test "maps/valid_west.cub" "SUCCESS" "Valid west-facing player"

# Valid maps - Different styles
run_test "maps/valid_minimal.cub" "SUCCESS" "Minimal valid map"
run_test "maps/valid_basic.cub" "SUCCESS" "Basic valid map"
run_test "maps/valid_spaces.cub" "SUCCESS" "Map with spaces"
run_test "maps/valid_whitespace.cub" "SUCCESS" "Map with whitespace"
run_test "maps/valid_indented_map.cub" "Map not enclosed by walls" "Map with indentation"
run_test "maps/valid_spaced_map.cub" "Map not enclosed by walls" "Map with spacing"
run_test "maps/valid_large.cub" "SUCCESS" "Large valid map"

# Element ordering tests
run_test "maps/test_order1.cub" "SUCCESS" "F/C first, then textures with empty lines"
run_test "maps/test_order2.cub" "SUCCESS" "Mixed textures and F/C with empty lines"
run_test "maps/test_order3.cub" "SUCCESS" "All textures first, then F/C with multiple empty lines"
run_test "maps/test_order4.cub" "SUCCESS" "All elements packed together before map"

# Custom valid maps
run_test "maps/mexicano.cub" "SUCCESS" "Custom map - mexicano"
run_test "maps/john.cub" "SUCCESS" "Custom map - john"

# Print summary
echo -e "\n${BLUE}=== Test Summary ===${NC}"
echo -e "Total tests: $TOTAL"
echo -e "Passed: ${GREEN}$PASSED${NC}"
echo -e "Failed: ${RED}$((TOTAL-PASSED))${NC}"

if [ $PASSED -eq $TOTAL ]; then
    echo -e "\n${GREEN}All tests passed!${NC}"
    exit 0
else
    echo -e "\n${RED}Some tests failed.${NC}"
    exit 1
fi 