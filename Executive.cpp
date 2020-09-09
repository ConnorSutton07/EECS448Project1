#include "Executive.h"
#include "Player.h"
#include <iostream>
using namespace std;

int Executive::charToInt(char c) {return ((toupper(c) - 65));}

bool Executive::validColumn(char c)
{
	if (!isalpha(c))
	{
		cout << "Invalid input! Column must be A-I!: ";
		return false;
	}
	else if (toupper(c) < 65 || toupper(c) > 73)
	{
		cout << "Must be between A-I!: ";
		return false;
	} // 65-73
	else
	{
		return true;
	}
}

void Executive::run()
{
	int shipnum = 0;
	
	Player player1;
	Player player2;
	int row, col;
	char c_col; // char version of the column

	chooseShipNum1:
		cout << "How many ships do you want to place in the grid? (choose from 1 to 5)\n";
		cin >> shipnum;
		player1.SetNumShips(shipnum); //decalers number of ships for both players
	
		
		if (shipnum < 1 || shipnum > 5)
		{
			cout << "Invaild number of ships!\n";
			goto chooseShipNum1;
		}

		for (int i = 1; i <= shipnum; i++)
		{
			chooseShipPosition1:
				
				player1.PrintMyShips(); //blank Board
				char direction = 'u'; //default direction is up

				if (i == 1)
				{
					cout << "Player 1, Where do you want to place 1X" << i << " on the grid? ((row(1-9) col(A-I)): ";
					while(!(cin >> row))
					{
						cout << "Invalid input! Row must be 1-9!: ";
						cin.clear();
						cin.ignore(123, '\n');
					}
					cout << "Now enter a column A-I: ";
					cin >> c_col;
					while(!validColumn(c_col))
					{
						cin >> c_col;
					}
					col = charToInt(c_col);
				}
				else
				{
					cout << "Choose a pivot coordinate for 1X" << i << " ship on the grid ((row(1-9) col(A-I)): ";
					while (!(cin >> row))
					{
						cout << "Invalid input! Row must be 1-9!: ";
						cin.clear();
						cin.ignore(123, '\n');
					}
					cout << "Now enter a column A-I: ";
					cin >> c_col;
					while (!validColumn(c_col))
					{
						cin >> c_col;
					}
					cout << "Up, Down, Left, or Right from pivot? (U, D, L, R): ";
					cin >> direction;
				}
				col = charToInt(c_col); // convert char to int
				row--; // decrement row by 1 for indexing array
				direction = toupper(direction); 
		
				if (direction != 'U' && direction != 'D' && direction != 'L' && direction != 'R') 
				{
					cout << "Invalid direction input!\n";
					goto chooseShipPosition1;
				}
				if (!player1.PlaceShip(i, row, col, direction))
				{
					cout << "ship could not be placed there. \n";
					goto chooseShipPosition1;
				}
		}

		player1.PrintMyShips(); //  print last time so player can see 1x5 ship placed	

		cout << " Now switch to Player2\n \n \n \n \n";
		player2.SetNumShips(shipnum);

		for (int i = 1; i <= shipnum; i++)
		{
			chooseShipPosition2:

				player2.PrintMyShips();
				char direction = 'u';

				if (i == 1)
				{
					cout << "Player 2, Where do you want to place 1X" << i << " on the grid? ((row(1-9) col(A-I)): ";
					while (!(cin >> row))
					{
						cout << "Invalid input! Row must be 1-9!: ";
						cin.clear();
						cin.ignore(123, '\n');
					}
					cout << "Now enter a column A-I: ";
					cin >> c_col;
					while (!validColumn(c_col))
					{
						cin >> c_col;
					}
					col = charToInt(c_col);
				}
				else
				{
					cout << "Choose a pivot coordinate for 1X" << i << " ship on the grid ((row(1-9) col(A-I)): ";
					while (!(cin >> row))
					{
						cout << "Invalid input! Row must be 1-9!: ";
						cin.clear();
						cin.ignore(123, '\n');
					}
					cout << "Now enter a column A-I: ";
					cin >> c_col;
					while (!validColumn(c_col))
					{
						cin >> c_col;
					}
					cout << "Up, Down, Left, or Right from pivot? (U, D, L, R): ";
					cin >> direction;
				}
				col = charToInt(c_col);
				row--;
				direction = toupper(direction);
		
				if (direction != 'U' && direction != 'D' && direction != 'L' && direction != 'R') 
				{
					cout << "Invalid direction input!\n";
					goto chooseShipPosition2;
				}
				if (!player2.PlaceShip(i, row, col, direction))
				{
					cout << "ship could not be placed there. \n";
					goto chooseShipPosition2;
				}
		}
		player2.PrintMyShips();
	

		cout << " Now play the battle ship\n";

		bool winner = false;
		int p1Sunk = 0;
		int p2Sunk = 0;
		int round = 1;

		while (!winner)
		{
			if (round % 2 == 1)
			{
				cout << "Player 1's turn!\n";
				player1.PrintEnemyShips();
				cout << "\n \n";
				cout << "Your Ships \n";
				player1.PrintMyShips();		//Print 2 board before fire

				cout << "Choose the coordinate that you want to fire : ((row(1 - 9) col(A - I))\n";
				cin >> row >> c_col;
				col = charToInt(c_col);
				row --;

				if (player2.CheckHit(row, col))
				{
					cout << "HIT!\n";
					player1.UpdateEnemyBoard(row, col, true);
				}
				else
				{
					cout << "MISS!\n";
					player1.UpdateEnemyBoard(row, col, false);
				}
			}
			else
			{
				cout << "Player 2's turn!\n";
				player2.PrintEnemyShips();
				cout << "\n \n";
				cout << "Your Ships \n";
				player2.PrintMyShips();		//Print 2 board before fire
			
				cout << "Choose the coordinate that you want to fire : ((row(1 - 9) col(A - I))\n";
				cin >> row >> c_col;
				col = charToInt(c_col);
				row --;

				if (player1.CheckHit(row, col))
				{
					cout << "HIT!\n";
					player2.UpdateEnemyBoard(row, col, true);
				}
				else
				{
					cout << "MISS!\n";
					player2.UpdateEnemyBoard(row, col, false);
				}
			}

			round++;
	/*
			if (numofhit1 == myplayer2.getShipnum())
			{
				cout << "Player1 Wins!\n";
				winner = true;
			}

			else ( numofhit2 == player1.getShipnum())
			{
				cout << "Player2 Wins!\n";
				winner = true;
			}
	*/
		}

}