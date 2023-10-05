#include "GameMode.h"

GameMode::GameMode(Player* C_player, AI* C_ai, ChessBoard* C_chessBoard)
{
	this->player = C_player;
	this->ai = C_ai;
	this->chessBoard = C_chessBoard;
}


void GameMode::play()
{
	chessBoard->init_ChessBoard();


	while (1)
	{
		player->go();

		if (chessBoard->checkOver() == true)
		{

		}

		ai->go();

		if (chessBoard->checkOver() == true)
		{

		}	
	}
}