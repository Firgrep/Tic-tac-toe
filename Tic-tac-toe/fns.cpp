#include <iostream>
#include <vector>
using namespace std;

void print_board(std::vector<vector<char>> board) //Prints the board to the console.
{
	std::cout << " " << endl;
	for (int i = 0; i < board.size(); i++)
	{
		for (int j = 0; j < board[i].size(); j++)
		{
			std::cout << board[i][j] << ' ';
		}
		std::cout << endl;
	}
	std::cout << endl;
}

void print_vector(std::vector<vector<int>> vect) //Prints a 2D int vector to the console. Helpful for testing and debugging.
{
	std::cout << "Here is the vector within the vector:" << endl;
	for (int i = 0; i < vect.size(); i++)
	{
		for (int j = 0; j < vect[i].size(); j++)
		{
			std::cout << vect[i][j] << ' ';
		}
		std::cout << endl;
	}
}

void greet() //Initial flavour text.
{
	std::cout << endl;
	std::cout << "|==X====0====X==|" << endl;
	std::cout << "|               |" << endl;
	std::cout << "| Tic, tac, toe!|" << endl;
	std::cout << "|               |" << endl;
	std::cout << "|==0====X====0==|" << endl;
	std::cout << endl;
}

vector<vector<int>> make_position(int row, int col) //Generates a 2D vector position out of two coordinates.
{
	std::vector<vector<int>> temp_pos;
	temp_pos.push_back({ row, col });
	return temp_pos;
}

bool pos_checker(vector<vector<int>> pos_list, vector<vector<int>> temp_pos) //Checks two 2D vectors for duplicates. Returns true when no duplicates found, otherwise false.
{
	if (pos_list.empty())
	{
		return true;
	}

	else
	{
		for (int i = 0; i < pos_list.size(); i++)
		{
			for (int j = 0; j < temp_pos.size(); j++)
			{
				if (pos_list[i] == temp_pos[j])
				{
					//std::cout << "Collision in vectors found.\n"; //For testing.
					return false;
				}
			}
		}
		return true;
	}
}

std::vector<vector<int>> ai_selection_update(std::vector<vector<int>> ai_pos_list, std::vector<int> pos) //Updates (overwrites) the list of possible non-duplicate positions for the "AI" to randomly choose from on its turn. 
{
	for (int i = 0; i < ai_pos_list.size(); i++)
	{
		if (ai_pos_list[i] == pos)
		{
			ai_pos_list.erase(ai_pos_list.begin() + i);
		}
	}
	return ai_pos_list;
}

int victory_conditions(vector<vector<char>> board) //Conditions for winning the game. These are statically determined based on elements on the board.
{
	//---User victory conditions---
	//Horizontal user:
	if (board[0][0] == 'X' && board[0][1] == 'X' && board[0][2] == 'X')
	{
		//std::cout << "vic 1.1\n";
		return 1;
	}

	if (board[1][0] == 'X' && board[1][1] == 'X' && board[1][2] == 'X')
	{
		//std::cout << "vic 1.2\n";
		return 1;
	}

	if (board[2][0] == 'X' && board[2][1] == 'X' && board[2][2] == 'X')
	{
		//std::cout << "vic 1.3\n";
		return 1;
	}

	//Vertical user:
	if (board[0][0] == 'X' && board[1][0] == 'X' && board[2][0] == 'X')
	{
		//std::cout << "vic 1.4\n";
		return 1;
	}

	if (board[0][1] == 'X' && board[1][1] == 'X' && board[2][1] == 'X')
	{
		//std::cout << "vic 1.5\n";
		return 1;
	}

	if (board[0][2] == 'X' && board[1][2] == 'X' && board[2][2] == 'X')
	{
		//std::cout << "vic 1.6\n";
		return 1;
	}

	//Diagonal user:
	if (board[0][0] == 'X' && board[1][1] == 'X' && board[2][2] == 'X')
	{
		//std::cout << "vic 1.7\n";
		return 1;
	}

	if (board[0][2] == 'X' && board[1][1] == 'X' && board[2][0] == 'X')
	{
		//std::cout << "vic 1.8\n";
		return 1;
	}

	//---AI victory conditions---
	//Horizontal AI:
	if (board[0][0] == 'O' && board[0][1] == 'O' && board[0][2] == 'O')
	{
		//std::cout << "vic 2.1\n";
		return 2;
	}

	if (board[1][0] == 'O' && board[1][1] == 'O' && board[1][2] == 'O')
	{
		//std::cout << "vic 2.2\n";
		return 2;
	}

	if (board[2][0] == 'O' && board[2][1] == 'O' && board[2][2] == 'O')
	{
		//std::cout << "vic 2.3\n";
		return 2;
	}

	//Vertical AI:
	if (board[0][0] == 'O' && board[1][0] == 'O' && board[2][0] == 'O')
	{
		//std::cout << "vic 2.4\n";
		return 2;
	}

	if (board[0][1] == 'O' && board[1][1] == 'O' && board[2][1] == 'O')
	{
		//std::cout << "vic 2.5\n";
		return 2;
	}

	if (board[0][2] == 'O' && board[1][2] == 'O' && board[2][2] == 'O')
	{
		//std::cout << "vic 2.6\n";
		return 2;
	}

	//Diagonal user:
	if (board[0][0] == 'O' && board[1][1] == 'O' && board[2][2] == 'O')
	{
		//std::cout << "vic 2.7\n";
		return 2;
	}

	if (board[0][2] == 'O' && board[1][1] == 'O' && board[2][0] == 'O')
	{
		//std::cout << "vic 2.8\n";
		return 2;
	}

	//Board is full: draw.
	if
		(
			(board[0][0] == 'X' || board[0][0] == 'O') &&
			(board[0][1] == 'X' || board[0][1] == 'O') &&
			(board[0][2] == 'X' || board[0][2] == 'O') &&
			(board[1][0] == 'X' || board[1][0] == 'O') &&
			(board[1][1] == 'X' || board[1][1] == 'O') &&
			(board[1][2] == 'X' || board[1][2] == 'O') &&
			(board[2][0] == 'X' || board[2][0] == 'O') &&
			(board[2][1] == 'X' || board[2][1] == 'O') &&
			(board[2][2] == 'X' || board[2][2] == 'O')
			)
	{
		//std::cout << "vic 3.1\n";
		return 3;
	}


	//No victory conditions achieved:
	else
	{
		//std::cout << "vic 0\n";
		return 0;
	}
}

