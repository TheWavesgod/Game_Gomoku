#include <iostream>

#include "GameMode.h"

int main(void)
{
	Player player;
	AI ai;
	ChessBoard chessBoard(15, 174, 216, 48.143);

	GameMode game(&player, &ai, &chessBoard);

	game.mainMenu();

	return 0;
}