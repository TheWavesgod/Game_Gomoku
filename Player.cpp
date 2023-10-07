#include "Player.h"

#include<iostream>

void Player::init(ChessBoard* board)
{
	this->board = board;
	playerChess = board->getPlayerChessKind();
}

chessPos Player::go()
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

	//cout << pos.row << " " << pos.col << " " << endl;

	board->chessMove(&pos, playerChess);

	return pos;
}
