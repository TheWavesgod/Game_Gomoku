#pragma once

#include "Player.h"
#include "AI.h"
#include "ChessBoard.h"

class GameMode
{
public:
	void mainMenu();

	// game start!
	void play();

	void setPlayerChess(bool playerChessFlag);

public:
	GameMode(Player* C_player, AI* C_ai, ChessBoard* C_chessBoard);

private:
	Player* player;
	AI* ai;
	ChessBoard* chessBoard;

	IMAGE mainMenuImg;

	// Indicate what chess kind player choose. true reps black, false reps white.
	bool playerFlag;
	// Indicate who the chess player is now. true reps player, false reps ai.
	bool flag;

	void checkWin();
};

