#include <iostream>

#include "GameMode.h"

int main(void)
{
	Player player;
	AI ai;
	ChessBoard chessBoard(15, 23, 27, 48.143);

	GameMode game(&player, &ai, &chessBoard);

	game.mainMenu();

	return 0;
}