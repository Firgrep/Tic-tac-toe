#include <iostream>
#include <cstdlib>
#include "fns.hpp"

int game()
{
	int victory = 0;
	bool no_collision = false;
	int mark_row = 0;
	int mark_col = 0;
	std::vector<vector<int>> pos_list;
	std::vector<vector<int>> temp_pos;
	std::vector<vector<int>> temp_ai_pos;
	std::vector<vector<char>> board =
	{
		{'_', '_', '_'},
		{'_', '_', '_'},
		{'_', '_', '_'}
	};
	std::vector<vector<int>> ai_pos_choice =
	{
		{0,0}, {0,1}, {0,2}, {1,0}, {1,1}, {1,2}, {2,0}, {2,1}, {2,2}
	};

	greet();
	print_board(board);

	while (victory == 0)
	{
		no_collision = false;
		while (no_collision == false)
		{
			while ((std::cout << "Please enter the row of your mark (1-3): ") && (!(std::cin >> mark_row) || mark_row < 1 || mark_row > 3))
			{
				std::cout << "Invalid! Input must be a number of more than 0 and less than 4;\n";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}

			while ((std::cout << "Please enter the column of your mark (1-3): ") && (!(std::cin >> mark_col) || mark_col < 1 || mark_col > 3))
			{
				std::cout << "Invalid! Input must be a number of more than 0 and less than 4;\n";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}

			mark_row = mark_row - 1;
			mark_col = mark_col - 1;
			temp_pos = make_position(mark_row, mark_col);
			no_collision = pos_checker(pos_list, temp_pos);

			if (no_collision == false)
			{
				std::cout << "Kindly input an unoccupied position on the board. Cheers\n";
			}

			else
			{
				for (int i = 0; i < temp_pos.size(); i++)
				{
					pos_list.push_back(temp_pos[i]);
					ai_pos_choice = ai_selection_update(ai_pos_choice, temp_pos[i]);
				}

				board[mark_row][mark_col] = 'X';
				//print_vector(ai_pos_choice); //For testing and debugging.
			}

			victory = victory_conditions(board);
			if (victory == 1)
			{
				print_board(board);
				return 1;
			}
			if (victory == 2)
			{
				print_board(board);
				return 2;
			}
			if (victory == 3)
			{
				print_board(board);
				return 3;
			}

		}

		//AI's turn:
		srand(time(NULL));
		int random = rand() % ai_pos_choice.size();
		std::vector<int> sel_elem = ai_pos_choice[random];
		int ai_row = sel_elem[0];
		int ai_col = sel_elem[1];
		board[ai_row][ai_col] = 'O';
		pos_list.push_back(sel_elem);
		ai_pos_choice = ai_selection_update(ai_pos_choice, sel_elem);

		//print_vector(ai_pos_choice); //For testing and debugging.

		victory = victory_conditions(board);
		if (victory == 1)
		{
			print_board(board);
			return 1;
		}
		if (victory == 2)
		{
			print_board(board);
			return 2;
		}
		if (victory == 3)
		{
			print_board(board);
			return 3;
		}

		//print_vector(pos_list); //For testing and debugging.
		print_board(board);

	}
}

int main()
{
	char answer;
	bool playing = true;
	while (playing)
	{
		int outcome = game();
		if (outcome == 1)
		{
			std::cout << "Congratulations! You won the game! Would you like to play again? (y/n)";
			std::cin >> answer;
			if (answer == 'y')
			{
				continue;
			}

			else
			{
				std::cout << "Thank you for playing Tic, tac, toe today! Come back to crush soon!;\n";
				break;
			}
		}

		else if (outcome == 2)
		{
			std::cout << "Alas! The AI beat you! Take your revenge now by playing again! (y/n)";
			std::cin >> answer;
			if (answer == 'y')
			{
				continue;
			}

			else
			{
				std::cout << "Thank you for playing Tic, tac, toe today! Come back to crush soon!;\n";
				break;
			}
		}

		else if (outcome == 3)
		{
			std::cout << "What!? A draw!? This cannot stand. Play again to show who's the victor? (y/n)";
			std::cin >> answer;
			if (answer == 'y')
			{
				continue;
			}

			else
			{
				std::cout << "Thank you for playing Tic, tac, toe today! Come back to crush soon!;\n";
				break;
			}
		}
	}
}