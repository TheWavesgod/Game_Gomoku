#pragma once

#include "ChessBoard.h"

class AI
{
public:
	void init(ChessBoard *board);

	void go();

private:
	ChessBoard* board;

	vector<vector<int>> scoreMap;

private:
	void findBestMove(int& bestRow, int& bestCol);

	void clearScoreMap();

	int evaluateMove(int row, int col, chess_kind_t ai_chess_kind);

	void addScore(int countAI, int countOpponent,int &score);
};

