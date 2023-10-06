#include "Player.h"

#include<iostream>

void Player::init(ChessBoard* board)
{
	this->board = board;
}

void Player::go()
{
	MOUSEMSG msg;
	chessPos pos;

	while (1)
	{
		msg = GetMouseMsg();
		if (msg.uMsg == WM_LBUTTONDOWN && board->clickBoard(msg.x, msg.y, &pos))
		{

			break;
		}
	}

	cout << pos.row << " " << pos.col << " " << endl;

	board->chessMove(&pos, CHESS_BLACK);

}
