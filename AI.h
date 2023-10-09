#pragma once

#include "ChessBoard.h"

class AI
{
public:
	void init(ChessBoard *board);

	chessPos go();

private:
	ChessBoard* board;

	chess_kind_t AIChess = CHESS_WHITE;

private:
	chessPos AIThink();

	void findBestMove(int& bestRow, int& bestCol);

	int evaluateMove(int row, int col, chess_kind_t ai_chess_kind);

	int horizontalEvaluate(int row, int col, chess_kind_t ai_chess_kind);
	int verticalEvaluate(int row, int col, chess_kind_t ai_chess_kind);
	int diagonalEvaluateFrwd(int row, int col, chess_kind_t ai_chess_kind);
	int diagonalEvaluateBkwd(int row, int col, chess_kind_t ai_chess_kind);

	int calculateScore(int oppocount, int count, int left, int right);

	int tenNpower(int n);
};

