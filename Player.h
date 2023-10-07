#pragma once

#include "ChessBoard.h" 

class Player
{
public:
	void init(ChessBoard* board);

	chessPos go();

private:
	ChessBoard* board;
	chess_kind_t playerChess;
};

