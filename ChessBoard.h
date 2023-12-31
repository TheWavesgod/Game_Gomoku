#pragma once

#include <vector>
using namespace std;
// easy x graphics library
#include <graphics.h> 

struct chessPos
{
	int row;
	int col;
};

struct PixCdnt
{
	int x;
	int y;
};

typedef enum
{
	CHESS_WHITE = -1,
	CHESS_BLACK = 1
}chess_kind_t;

typedef enum
{
	CHESS_DOWN = 1,
	CHESS_REMOVE = 0
}chess_move_t;

class ChessBoard
{
public:

	void init_ChessBoard(bool playerFlag);

	// Check if the click is valid.
	// If valid, save the info into position of chessPos.
	bool clickBoard(int x, int y, chessPos* pos);

	void chessMove(chessPos *pos, chess_kind_t chess_kind);

	// Get the size of the chess board, return 13, 15, 17 or 19.
	int getGradeSize();

	int getChessData(chessPos* pos);
	int getChessData(int row, int col);
	  
	bool checkOver(chessPos lastMovePos, chess_kind_t lastMoveKind);

	void chessBoardClear();

	chess_kind_t getPlayerChessKind();

	IMAGE* getChessBoardImg();

public:
	ChessBoard(int gradeSize, int marginX, int marginY, float chessSize);

private:
	IMAGE chessBoardImg;
	IMAGE chessBlackImg;
	IMAGE chessWhiteImg;

	int gradeSize;	
	int margin_x;
	int margin_y;

	float chessSize;

	// Store the current chess game's piece distribution data 0 reps vacant , 1 reps black , -1 reps white
	vector<vector<int>> chessMap; 
		
	// Indicate who the chess player is now. true reps black, false reps white.
	bool playerFlag;

private:
	void putChessImagePNG(int x, int y, IMAGE* picture);

	PixCdnt getPixCdnt(chessPos* pos);
	PixCdnt getPixCdnt(int row, int col);

	void updateChessMap(chessPos* pos, chess_kind_t chess_kind,chess_move_t move_t);
};

