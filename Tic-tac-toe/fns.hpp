#pragma once
#include <vector>
using namespace std;

int game();
void print_board(std::vector<vector<char>> board);
void greet();
vector<vector<int>> make_position(int row, int col);
void print_vector(std::vector<vector<int>> board);
bool pos_checker(vector<vector<int>> pos_list, vector<vector<int>> temp_pos);
int victory_conditions(vector<vector<char>> board);
std::vector<vector<int>> ai_selection_update(std::vector<vector<int>> ai_pos_list, std::vector<int> pos);