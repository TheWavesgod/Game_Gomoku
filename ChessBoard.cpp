#include "ChessBoard.h"
#include <math.h>

// add the sound.
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

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

void ChessBoard::init_ChessBoard(bool playerFlag)
{
	Resize(NULL, 1024, 1024);
	loadimage(NULL, "Resources/chessboard.png",1024,1024,true);

	//mciSendString("play Resources/chq.mp3", 0, 0, 0);

	loadimage(&chessBlackImg, "Resources/black.png", 44, 44, true);
	loadimage(&chessWhiteImg, "Resources/white.png", 44, 44, true);

	chessBoardClear();

	this->playerFlag = playerFlag;
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
	PixCdnt Ppos = getPixCdnt(pos);

	int offset = 22;

	if (chess_kind == CHESS_WHITE)
	{
		putChessImagePNG(Ppos.x - offset, Ppos.y - offset, &chessWhiteImg);
	}
	else
	{
		putChessImagePNG(Ppos.x - offset, Ppos.y - offset, &chessBlackImg);
	}

	mciSendString("play Resources/chess.wav", 0, 0, 0);

	updateChessMap(pos, chess_kind, CHESS_DOWN);

}

int ChessBoard::getGradeSize()
{
	return gradeSize;
}

int ChessBoard::getChessData(chessPos* pos)
{
	return this->chessMap[pos->row][pos->col];
}

int ChessBoard::getChessData(int row, int col)
{
	return this->chessMap[row][col];
}

bool ChessBoard::checkOver(chessPos lastMovePos, chess_kind_t lastMoveKind)
{
	int row = lastMovePos.row;
	int col = lastMovePos.col;

	int countNum = 0;

	// Horizontal check
	for (int i = col - 4; i <= col + 4; ++i)
	{	
		if (i >= 0 && i < gradeSize)
		{
			if (chessMap[row][i] == lastMoveKind)
			{
				++countNum;
			}
			else
			{
				countNum = 0;
			}
		}
		if (countNum == 5)
		{
			return true;
		}
	}

	// Vertical check
	countNum = 0;
	for (int i = row - 4; i <= row + 4; ++i)
	{
		if (i >= 0 && i < gradeSize)
		{
			if (chessMap[i][col] == lastMoveKind)
			{
				++countNum;
			}
			else
			{
				countNum = 0;
			}
		}
		if (countNum == 5)
		{
			return true;
		}
	}

	// left Diagonal check
	countNum = 0;
	for (int i = row - 4, j = col - 4; i <= row + 4; ++i, ++j)
	{
		if (i >= 0 && i < gradeSize && j >= 0 && j < gradeSize)
		{
			if (chessMap[i][j] == lastMoveKind)
			{
				++countNum;
			}
			else
			{
				countNum = 0;
			}
		}
		if (countNum == 5)
		{
			return true;
		}
	}

	// right Diagonal check
	countNum = 0;
	for (int i = row - 4, j = col + 4; i <= row + 4; ++i, --j)
	{
		if (i >= 0 && i < gradeSize && j >= 0 && j < gradeSize)
		{
			if (chessMap[i][j] == lastMoveKind)
			{
				++countNum;
			}
			else
			{
				countNum = 0;
			}
		}
		if (countNum == 5)
		{
			return true;
		}
	}

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

chess_kind_t ChessBoard::getPlayerChessKind()
{
	return this->playerFlag? CHESS_BLACK : CHESS_WHITE;
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

void ChessBoard::updateChessMap(chessPos* pos, chess_kind_t chess_kind, chess_move_t move_t)
{
	chessMap[pos->row][pos->col] = move_t ? chess_kind : 0;
}

void ChessBoard::putChessImagePNG(int x, int y, IMAGE* picture) //xΪ����ͼƬ��X���꣬yΪY����
{
	// ������ʼ��
	DWORD* dst = GetImageBuffer();    // GetImageBuffer()���������ڻ�ȡ��ͼ�豸���Դ�ָ�룬EASYX�Դ�
	DWORD* draw = GetImageBuffer();
	DWORD* src = GetImageBuffer(picture); //��ȡpicture���Դ�ָ��
	int picture_width = picture->getwidth(); //��ȡpicture�Ŀ�ȣ�EASYX�Դ�
	int picture_height = picture->getheight(); //��ȡpicture�ĸ߶ȣ�EASYX�Դ�
	int graphWidth = getwidth();       //��ȡ��ͼ���Ŀ�ȣ�EASYX�Դ�
	int graphHeight = getheight();     //��ȡ��ͼ���ĸ߶ȣ�EASYX�Դ�
	int dstX = 0;    //���Դ������صĽǱ�

	// ʵ��͸����ͼ ��ʽ�� Cp=��p*FP+(1-��p)*BP �� ��Ҷ˹���������е���ɫ�ĸ��ʼ���
	for (int iy = 0; iy < picture_height; iy++)
	{
		for (int ix = 0; ix < picture_width; ix++)
		{
			int srcX = ix + iy * picture_width; //���Դ������صĽǱ�
			int sa = ((src[srcX] & 0xff000000) >> 24); //0xAArrggbb;AA��͸����
			int sr = ((src[srcX] & 0xff0000) >> 16); //��ȡRGB���R
			int sg = ((src[srcX] & 0xff00) >> 8);   //G
			int sb = src[srcX] & 0xff;              //B
			if (ix >= 0 && ix <= graphWidth && iy >= 0 && iy <= graphHeight && dstX <= graphWidth * graphHeight)
			{
				dstX = (ix + x) + (iy + y) * graphWidth; //���Դ������صĽǱ�
				int dr = ((dst[dstX] & 0xff0000) >> 16);
				int dg = ((dst[dstX] & 0xff00) >> 8);
				int db = dst[dstX] & 0xff;
				draw[dstX] = ((sr * sa / 255 + dr * (255 - sa) / 255) << 16)  //��ʽ�� Cp=��p*FP+(1-��p)*BP  �� ��p=sa/255 , FP=sr , BP=dr
					| ((sg * sa / 255 + dg * (255 - sa) / 255) << 8)         //��p=sa/255 , FP=sg , BP=dg
					| (sb * sa / 255 + db * (255 - sa) / 255);              //��p=sa/255 , FP=sb , BP=db
			}
		}
	}
}
