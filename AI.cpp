#include "AI.h"

void AI::init(ChessBoard* board)
{
	this->board = board;

	AIChess = board->getPlayerChessKind() == CHESS_BLACK ? CHESS_WHITE : CHESS_BLACK;
}

chessPos AI::go()
{
	chessPos movePos = AIThink();

	// pretend to be thinking
	Sleep(1000);

	board->chessMove(&movePos, AIChess);

	return movePos;
}

chessPos AI::AIThink()
{
	chessPos movePos;

	this->findBestMove(movePos.row, movePos.col);

	return movePos;
}

void AI::findBestMove(int& bestRow, int& bestCol)
{
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
				int score = evaluateMove(row, col, AIChess);
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

int AI::evaluateMove(int row, int col, chess_kind_t ai_chess_kind)
{
	int score = 0;
	vector<int> pieces;

	// Horizontal direction
	int temp = horizontalEvaluate(row, col, ai_chess_kind);
	score = temp > score ? temp : score;

	// vertical direction
	temp = verticalEvaluate(row, col, ai_chess_kind);
	score = temp > score ? temp : score;

	// Diagonal direction forward
	temp = diagonalEvaluateFrwd(row, col, ai_chess_kind);
	score = temp > score ? temp : score;

	// Diagonal direction backward
	temp = diagonalEvaluateBkwd(row, col, ai_chess_kind);
	score = temp > score ? temp : score;

	return score;
}

inline int AI::horizontalEvaluate(int row, int col, chess_kind_t ai_chess_kind)
{
	int oppocount = 0;
	int count = 0;
	int left = 0;
	int right = 0;

	// Horizontal direction
	// left
	for (int i = col - 1; i >= 0; --i)
	{
		const int& temp = board->getChessData(row, i);
		if (temp == ai_chess_kind)
		{
			++count;
			if (count >= 4)
			{
				break;
			}
		}
		else if (temp == 0)
		{
			++left;
			break;
		}
		else
		{
			if (count == 0)
			{
				++oppocount;
			}
			else
			{
				break;
			}
		}
	}
	// right
	for (int i = col + 1; i < board->getGradeSize(); ++i)
	{
		const int& temp = board->getChessData(row, i);
		if (temp == ai_chess_kind)
		{
			++count;
			if (count >= 4)
			{
				break;
			}
		}
		else if (temp == 0)
		{
			++right;
			break;
		}
		else
		{
			if (count == 0)
			{
				++oppocount;
			}
			else
			{
				break;
			}
		}
	}

	return calculateScore(oppocount, count, left, right);
}

int AI::verticalEvaluate(int row, int col, chess_kind_t ai_chess_kind)
{
	int oppocount1 = 0;
	int oppocount2 = 0;
	int count = 0;
	int left = 0;
	int right = 0;

	// vertical direction
	// up
	for (int i = row - 1; i >= 0; --i)
	{
		const int& temp = board->getChessData(i, col);
		if (temp == ai_chess_kind)
		{
			if (oppocount1 != 0)
			{
				break;
			}
			++count;
			if (count >= 4)
			{
				break;
			}
		}
		else if (temp == 0)
		{
			++left;
			break;
		}
		else
		{
			if (count == 0)
			{
				++oppocount1;
			}
			else
			{
				break;
			}
		}
	}
	// down
	for (int i = row + 1; i < board->getGradeSize(); ++i)
	{
		const int& temp = board->getChessData(i, col);
		if (temp == ai_chess_kind)
		{
			if (oppocount2 != 0)
			{
				break;
			}
			++count;
			if (count >= 4)
			{
				break;
			}
		}
		else if (temp == 0)
		{
			++right;
			break;
		}
		else
		{
			if (count == 0)
			{
				++oppocount2;
			}
			else
			{
				break;
			}
		}
	}

	return calculateScore(oppocount1 + oppocount2, count, left, right);
}

int AI::diagonalEvaluateFrwd(int row, int col, chess_kind_t ai_chess_kind)
{
	int oppocount1 = 0;
	int oppocount2 = 0;
	int count = 0;
	int left = 0;
	int right = 0;

	// diagonal direction forward
	// up
	int i = row;
	int j = col;
	while (i >= 0 && j >= 0)
	{
		const int& temp = board->getChessData(i, j);
		if (temp == ai_chess_kind)
		{
			if (oppocount1 != 0)
			{
				break;
			}
			++count;
			if (count >= 4)
			{
				break;
			}
		}
		else if (temp == 0)
		{
			++left;
			break;
		}
		else
		{
			if (count == 0)
			{
				++oppocount1;
			}
			else
			{
				break;
			}
		}

		--i;
		--j;
	}

	//down
	i = row;
	j = col;
	while (i < board->getGradeSize() && j < board->getGradeSize())
	{
		const int& temp = board->getChessData(i, j);
		if (temp == ai_chess_kind)
		{
			if (oppocount2 != 0)
			{
				break;
			}
			++count;
			if (count >= 4)
			{
				break;
			}
		}
		else if (temp == 0)
		{
			++left;
			break;
		}
		else
		{
			if (count == 0)
			{
				++oppocount2;
			}
			else
			{
				break;
			}
		}

		++i;
		++j;
	}

	return calculateScore(oppocount1 + oppocount2, count, left, right);
}

int AI::diagonalEvaluateBkwd(int row, int col, chess_kind_t ai_chess_kind)
{
	int oppocount1 = 0;
	int oppocount2 = 0;
	int count = 0;
	int left = 0;
	int right = 0;

	// diagonal direction backward
	// up
	int i = row;
	int j = col;
	while (i >= 0 && j < board->getGradeSize())
	{
		const int& temp = board->getChessData(i, j);
		if (temp == ai_chess_kind)
		{
			if (oppocount1 != 0)
			{
				break;
			}
			++count;
			if (count >= 4)
			{
				break;
			}
		}
		else if (temp == 0)
		{
			++left;
			break;
		}
		else
		{
			if (count == 0)
			{
				++oppocount1;
			}
			else
			{
				break;
			}
		}

		--i;
		++j;
	}

	//down
	i = row;
	j = col;
	while (i < board->getGradeSize() && j >= 0)
	{
		const int& temp = board->getChessData(i, j);
		if (temp == ai_chess_kind)
		{
			if (oppocount2 != 0)
			{
				break;
			}
			++count;
			if (count >= 4)
			{
				break;
			}
		}
		else if (temp == 0)
		{
			++left;
			break;
		}
		else
		{
			if (count == 0)
			{
				++oppocount2;
			}
			else
			{
				break;
			}
		}

		++i;
		--j;
	}

	return calculateScore(oppocount1 + oppocount2, count, left, right);
}

int AI::calculateScore(int oppocount, int count, int left, int right)
{
	int score = 0;
	if (count > 1)
	{
		if (left == 1 && right == 1)
		{
			int temp = tenNpower(count);
			score = temp > score ? temp : score;
		}
		else if (left == 1 || right == 1)
		{
			int temp = tenNpower(count - 1);
			score = temp > score ? temp : score;
		}
	}

	int temp = tenNpower(oppocount) - 1;
	score = temp > score ? temp : score;

	return score;
}

int AI::tenNpower(int n)
{
	int x = 1;
	for (int i = 0; i < n; ++i)
	{
		x *= 10;
	}
	return x;
}

