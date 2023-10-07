#include "GameMode.h"

// add sound
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

#include <conio.h>

GameMode::GameMode(Player* C_player, AI* C_ai, ChessBoard* C_chessBoard)
{
	this->player = C_player;
	this->ai = C_ai;
	this->chessBoard = C_chessBoard;

	this->player->init(chessBoard);

	initgraph(1024, 1024);
	loadimage(NULL, "Resources/MainMenu.png", 1024, 1024, true);
	//loadimage(&mainMenuImg, "Resources/MainMenu.png", 1024, 1024, true);

	mciSendString("play Resources/bgm.mp3", 0, 0, 0);

}

void GameMode::mainMenu()
{
	//putimage(1024, 1024, &mainMenuImg, SRCCOPY);

	_getch();

	play();

}

void GameMode::checkWin()
{
	if (flag == true)
	{
		mciSendString("play Resources/success.mp3", 0, 0 ,0);
		// put image
	}
	else
	{
		mciSendString("play Resources/lose.mp3", 0, 0, 0);
	}
}

void GameMode::play()
{
	setPlayerChess(true);

	chessBoard->init_ChessBoard(playerFlag);

	player->init(this->chessBoard);
	ai->init(this->chessBoard);

	chessPos lastMovePos;

	while (1)
	{
		chess_kind_t lastMoveKind;

		if (flag)
		{
			lastMovePos = player->go();
			lastMoveKind = playerFlag ? CHESS_BLACK : CHESS_WHITE;
		}
		else
		{
			lastMovePos = ai->go();
			lastMoveKind = playerFlag ? CHESS_WHITE : CHESS_BLACK;
		}

		if (chessBoard->checkOver(lastMovePos, lastMoveKind) == true)
		{
			break;
		}
		flag = !flag;
	}

	Sleep(1000);

	checkWin();

	_getch();
}

void GameMode::setPlayerChess(bool playerChessFlag)
{
	playerFlag = playerChessFlag;
	flag = playerChessFlag ? true : false;
}
