#include "GameMode.h"

GameMode::GameMode(Player* C_player, AI* C_ai, ChessBoard* C_chessBoard)
{
	this->player = C_player;
	this->ai = C_ai;
	this->chessBoard = C_chessBoard;

	this->player->init(chessBoard);
}


void GameMode::play()
{
	chessBoard->init_ChessBoard();

	player->init(this->chessBoard);
	ai->init(this->chessBoard);

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