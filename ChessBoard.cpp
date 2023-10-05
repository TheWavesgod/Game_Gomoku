#include "ChessBoard.h"

// add the sound.
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

void ChessBoard::init_ChessBoard()
{
	initgraph(720, 755);	

	loadimage(0, "Resouces/chessboard.png");

	mciSendString("play Resouces/chq.mp3", 0, 0, 0);

	loadimage(&chessBlackImg, "Resouces/black.png");
	loadimage(&chessWhiteImg, "Resouces/white.png");

	chessBoardClear();

	playerFlag = true;
}

bool ChessBoard::clickBoard(int x, int y, chessPos* pos)
{
	return false;
}

void ChessBoard::chessMove(chessPos* pos, chess_kind_t chess_kind)
{
}

int ChessBoard::getGradeSize()
{
	return 0;
}

int ChessBoard::getChessData(chessPos* pos)
{
	return 0;
}

int ChessBoard::getChessData(int row, int col)
{
	return 0;
}

bool ChessBoard::checkOver()
{
	return false;
}

void ChessBoard::chessBoardClear()
{
	for (unsigned i = 0; i < gradeSize; ++i)
	{
		for (unsigned j = 0; j < gradeSize; ++j)
		{
			this->chessMap[i][j] = 0;
		}
	}
}

ChessBoard::ChessBoard(int gradeSize, int marginX, int marginY, float chessSize)
{
	this->gradeSize = gradeSize;
	this->margin_x = marginX;
	this->margin_y = marginY;
	this->chessSize = chessSize;

	playerFlag = true; 

	for (unsigned i = 0; i < gradeSize; ++i)
	{
		vector<int> temp;
		for (unsigned j = 0; j < gradeSize; ++j)
		{
			temp.push_back(0);
		}
		this->chessMap.push_back(temp);
	}
}
