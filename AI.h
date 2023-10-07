#pragma once

#include "ChessBoard.h"

class AI
{
public:
	void init(ChessBoard *board);

	chessPos go();

private:
	ChessBoard* board;

	vector<vector<int>> scoreMap;

	chess_kind_t AIChess = CHESS_WHITE;

private:
	chessPos AIThink();

	void findBestMove(int& bestRow, int& bestCol);

	void clearScoreMap();

	int evaluateMove(int row, int col, chess_kind_t ai_chess_kind);

	void addScore(int countAI, int countOpponent,int &score);
};

