#include "Player.h"
#include <vector>
#include <array>
class Player_EF : public Player
{
public:
	Player_EF();
	Player_EF(int no);
	~Player_EF();

	/**
	 * Calculates the next move.
	 * @return the index of the square of choice (1 to 16) or -1 if no placement is possible
	 */
	int getNextMove(int fld_status[]);
};

class Helper {
private:
	std::vector<int> corners; //The vector to store position of board corners
public:
	Helper();


	std::array<std::array<int, 4>, 10> win_pos; // 2 - dimensional array to store coordinate information for each row, columnand diagonal

	/*The arrays for tarcking own player moves on board.
	* The arrays is defined as std::vector<int> for save changing in the getCurrSit function.*/
	std::vector<int> curr_sit_1; // array for  player_1 moves
	std::vector<int> curr_sit_2; // array for  player_2 moves

	int move_count; // variable for counting the number of moves made

	/*Check if current position is available.
	* true - if position is avaiable (equals to 0) to choose,
	* false - if position is busy (equals to any not zero number) to choose.
	* @return The cell availability as bool*/
	bool isFree(int field[], int pos);

	/**
	* Return avaiable position index of the corner.
	* @return The position index of the corner as int.
	* If there is no free cell will return 0.
	*/
	int getCorner(int field[]);

	/**
	* Calculate current numbers of the moves at lanes and calculate current move number.
	* @param The recieved array of the field.
	* Changing curr_sit_my and curr_sit_op arrays and a current move number.
	* return nothing, just changing global variables in the Player_EF.cpp file
	*/
	void getCurrSit(int field[]);
};
