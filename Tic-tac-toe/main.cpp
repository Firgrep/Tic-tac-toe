#include <iostream>
#include <cstdlib>
#include "fns.hpp"

int game()					//The game is determined as a function, which can be called again for rematch after the first playthrough. Returns an int based on the game outcome.
{
							//Benefit of doing the game as a function is that any return statement within the function immediately exits the function,
							//which is useful when one of the victory conditions have been achieved for either the user or the turn of the "AI".

	int victory = 0;							//Victory outcome is determined as int rather than bool, since we need 3 outcomes: user wins, AI wins or draw.
	bool no_collision = false;					//Bool used as flag to check whether user's input is correct.
	int mark_row = 0;							//User coordinates to be used for the row of the board.
	int mark_col = 0;							//User coordinates for the column of the board.
	std::vector<vector<int>> pos_list;			//2D int vector to list existing positions. Begins empty.
	std::vector<vector<int>> temp_pos;			//2D int vector to list user's input, which will then be checked against the pos_list for duplicates.
	std::vector<vector<char>> board =			//2D chat vector that manifests the board, used both visually and to keep track of user and AI current positions. 
	{
		{'_', '_', '_'},
		{'_', '_', '_'},
		{'_', '_', '_'}
	};
	std::vector<vector<int>> ai_pos_choice =		//2D int vector of possible non-duplicate positions for the "AI" to randomly select from.
	{
		{0,0}, {0,1}, {0,2}, {1,0}, {1,1}, {1,2}, {2,0}, {2,1}, {2,2}
	};

	greet();
	print_board(board);

	while (victory == 0)	//Once a victory condition is attained, the game whole function is existed, otherwise the loop repeats.
	{
		no_collision = false;			//Flag is reset at the user's turn.
		while (no_collision == false)	//Loop is broken insofar as the user inputs correct int inputs. 
		{
			while ((std::cout << "Please enter the row of your mark (1-3): ") && (!(std::cin >> mark_row) || mark_row < 1 || mark_row > 3)) //Notice 1-3 rather than 0-2 coordinates are asked for.
			{
				std::cout << "Invalid! Input must be a number of more than 0 and less than 4;\n"; //To avoid program shutdown on non-int inputs, the input as determined in two while loops.
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}

			while ((std::cout << "Please enter the column of your mark (1-3): ") && (!(std::cin >> mark_col) || mark_col < 1 || mark_col > 3))
			{
				std::cout << "Invalid! Input must be a number of more than 0 and less than 4;\n";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}

			mark_row = mark_row - 1; //The user's inputs are adjusted for the correct index coordinates. This is done out of user-friendliness.
			mark_col = mark_col - 1; //It's just more convenient and pleasant to think of rows and columns in 1-3 than 0-2.
			temp_pos = make_position(mark_row, mark_col); //The user coordinates are made into a temporary 2D int vector that hosts the user's position..
			no_collision = pos_checker(pos_list, temp_pos); //The temporary user position is checked against existing positons for duplicates. Function returns a bool value.

			if (no_collision == false) //If collisions were found above, the bool remains false and the user is asked to input a non-duplicate position. 
			{
				std::cout << "Kindly input an unoccupied position on the board. Cheers\n";
			}

			else //Otherwise, no collisions are found ... 
			{
				for (int i = 0; i < temp_pos.size(); i++)
				{
					pos_list.push_back(temp_pos[i]); //...and the temporary position is added to the list of positions.
					ai_pos_choice = ai_selection_update(ai_pos_choice, temp_pos[i]); //Additionally, the same position is removed on the list of possible choices for the "AI" turn.
				}
				
				board[mark_row][mark_col] = 'X'; //Lastly, the board is marked.
				//print_vector(ai_pos_choice); //For testing and debugging.
			}

			victory = victory_conditions(board); //After the user has successfully inputted a position, the game is checked to see if any victory conditions are achieved. 
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
		srand(time(NULL));													//Reset seed on program reset.
		int random = rand() % ai_pos_choice.size();							//Selection of a random index value based on the vector size.
		std::vector<int> sel_elem = ai_pos_choice[random];					//Using the random index int, an int vector (position) is selected and copied from the 2D vector list.
		int ai_row = sel_elem[0];											//Row coordinate is copied from the position vector based on index.
		int ai_col = sel_elem[1];											//Column coordinate is copied from the posoiton vector based on index.
		board[ai_row][ai_col] = 'O';										//Coordinates are then used to determine and modify the position on the board.
		pos_list.push_back(sel_elem);										//List of existing positions is updated with the new position from the "AI".
		ai_pos_choice = ai_selection_update(ai_pos_choice, sel_elem);		//Finally, the possible selection of "AI" positions is updated by erasing the position that has just been used.

		//print_vector(ai_pos_choice); //For testing and debugging.

		victory = victory_conditions(board); //After the "AI's" turn, the board is once more checked if any victory conditions have been achieved. 
		print_board(board);
		if (victory == 1)
		{
			return 1;
		}
		if (victory == 2)
		{
			return 2;
		}
		if (victory == 3)
		{
			return 3;
		}

		//print_vector(pos_list); //For testing and debugging.

		//With no victory conditions attained by either the user or the "AI", the game loop continues.
	}
}

int main()
{
	char answer;						//Used to ask the user if they want a rematch after the game has played.
	bool playing = true;				//Playing is set to true as the program starts.
	while (playing)						//This is the "playing" loop which is broken if the user inputs anything but 'y' at the rematch prompt.
	{
		int outcome = game();			//The game function is called and returns an int which will determine the following three outcomes: win, loss or draw.
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