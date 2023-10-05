#pragma once

#include "Player.h"
#include "AI.h"
#include "ChessBoard.h"

class GameMode
{
public:

	// game start!
	void play();

public:
	GameMode(Player* C_player, AI* C_ai, ChessBoard* C_chessBoard);

private:
	Player* player;
	AI* ai;
	ChessBoard* chessBoard;

};

