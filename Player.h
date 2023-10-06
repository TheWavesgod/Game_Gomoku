#pragma once

#include "ChessBoard.h" 

class Player
{
public:
	void init(ChessBoard* board);

	void go();

private:
	ChessBoard* board;
};

