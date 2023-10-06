#include "AI.h"

void AI::init(ChessBoard* board)
{
	this->board = board;

	for (unsigned i = 0; i < board->getGradeSize(); ++i)
	{
		vector<int> temp;
		for (unsigned j = 0; j < board->getGradeSize(); ++j)
		{
			temp.push_back(0);
		}
		this->scoreMap.push_back(temp);
	}
}

void AI::go()
{
}

void AI::findBestMove(int& bestRow, int& bestCol)
{
	this->clearScoreMap();

	int maxScore = -1;

	bestRow = -1;
	bestCol = -1;

	int size = board->getGradeSize();

	for (unsigned row = 0; row < size; ++row)
	{
		for (unsigned col = 0; col < size; ++col)
		{
			if (board->getChessData(row, col) == 0)
			{
				int score = evaluateMove(row, col);
				if (score > maxScore)
				{
					maxScore = score;
					bestRow = row;
					bestCol = col;
				}
			}
		}
	}
}

void AI::clearScoreMap()
{
	for (auto i = scoreMap.begin(); i != scoreMap.end(); ++i)
	{
		for (auto j = i->begin(); j != i->end(); ++j)
		{
			*(j) = 0;
		}
	}
}

int AI::evaluateMove(int row, int col, chess_kind_t ai_chess_kind)
{
	int score = 0;

	// Horizontal direction
	for (int i = col - 4; i < col; ++i)
	{
		if (i >= 0 && i + 4 <= board->getGradeSize())
		{
			int countAI = 0;
			int countOpponent = 0;

			for (int j = i; j < i + 5; ++j)
			{
				if (board->getChessData(row, j) == ai_chess_kind)
				{
					++countAI;
				}
				else if (board->getChessData(row, j) != 0)
				{
					++countOpponent;
				}
			}

			addScore(countAI, countOpponent, score);
		}
	}

	// Vertical direction
	for (int i = row - 4; i < row; ++i)
	{
		if (i >= 0 && i + 4 <= board->getGradeSize())
		{
			int countAI = 0;
			int countOpponent = 0;

			for (int j = i; j < i + 5; ++j)
			{
				if (board->getChessData(j, col) == ai_chess_kind)
				{
					++countAI;
				}
				else if (board->getChessData(j, col) != 0)
				{
					++countOpponent;
				}
			}

			addScore(countAI, countOpponent, score);
		}
	}

	// Diagonal direction
	for (int i = row - 4; i < row; ++i)
	{
		if (i >= 0 && i + 4 <= board->getGradeSize())
		{
			int countAI = 0;
			int countOpponent = 0;

			for (int j = i; j < i + 5; ++j)
			{
				if (board->getChessData(j, col) == ai_chess_kind)
				{
					++countAI;
				}
				else if (board->getChessData(j, col) != 0)
				{
					++countOpponent;
				}
			}

			addScore(countAI, countOpponent, score);
		}
	}

	
}

void AI::addScore(int countAI, int countOpponent, int& score)
{
	if (countAI == 5) {
		score += 10000; // 五子连珠，胜利
	}
	else if (countAI == 4 && countOpponent == 0) {
		score += 1000; // 活四
	}
	else if (countAI == 3 && countOpponent == 0) {
		score += 100; // 活三
	}
	else if (countAI == 2 && countOpponent == 0) {
		score += 10; // 活二
	}
	else if (countAI == 1 && countOpponent == 0) {
		score += 1; // 活一
	}
	else if (countOpponent == 4 && countAI == 0) {
		score += 500; // 冲四，防守
	}
}
