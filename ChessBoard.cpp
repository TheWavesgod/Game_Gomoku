#include "ChessBoard.h"
#include <math.h>

// add the sound.
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

void ChessBoard::init_ChessBoard()
{
	initgraph(720, 755, EX_SHOWCONSOLE);

	loadimage(0, "Resouces/chessboard.png");

	mciSendString("play Resouces/chq.mp3", 0, 0, 0);

	loadimage(&chessBlackImg, "Resouces/black.png");
	loadimage(&chessWhiteImg, "Resouces/white.png");

	chessBoardClear();

	playerFlag = true;
}

bool ChessBoard::clickBoard(int x, int y, chessPos* pos)
{
	int LU_col = (x - margin_x) / chessSize;
	int LU_row = (y - margin_y) / chessSize;

	int offset = chessSize * 0.4;
	bool ret = false;
	int len;

	do 
	{
		PixCdnt LU_Pix = getPixCdnt(LU_row, LU_col);

		len = sqrt((x - LU_Pix.x) * (x - LU_Pix.x) + (y - LU_Pix.y) * (y - LU_Pix.y));
		
		if (len < offset && chessMap[LU_row][LU_col] == 0)
		{
			pos->col = LU_col;
			pos->row = LU_row;
			ret = true;
			break;
		}
		
		PixCdnt LD_Pix = getPixCdnt(LU_row + 1, LU_col);

		len = sqrt((x - LD_Pix.x) * (x - LD_Pix.x) + (y - LD_Pix.y) * (y - LD_Pix.y));

		if (len < offset && chessMap[LU_row + 1][LU_col] == 0)
		{
			pos->col = LU_col;
			pos->row = LU_row + 1;
			ret = true;
			break;
		}

		PixCdnt RU_Pix = getPixCdnt(LU_row, LU_col + 1);

		len = sqrt((x - RU_Pix.x) * (x - RU_Pix.x) + (y - RU_Pix.y) * (y - RU_Pix.y));

		if (len < offset && chessMap[LU_row][LU_col + 1] == 0)
		{
			pos->col = LU_col + 1;
			pos->row = LU_row;
			ret = true;
			break;
		}

		PixCdnt RD_Pix = getPixCdnt(LU_row + 1, LU_col + 1);

		len = sqrt((x - RD_Pix.x) * (x - RD_Pix.x) + (y - RD_Pix.y) * (y - RD_Pix.y));

		if (len < offset && chessMap[LU_row + 1][LU_col + 1] == 0)
		{
			pos->col = LU_col + 1;
			pos->row = LU_row + 1;
			ret = true;
			break;
		}
	} while (0);

	return ret;
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

PixCdnt ChessBoard::getPixCdnt(chessPos* pos)
{
	PixCdnt temp;

	temp.x = margin_x + pos->col * chessSize;
	temp.y = margin_y + pos->row * chessSize;

	return temp;
}

PixCdnt ChessBoard::getPixCdnt(int row, int col)
{
	PixCdnt temp;

	temp.x = margin_x + col * chessSize;
	temp.y = margin_y + row * chessSize;

	return temp;
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
