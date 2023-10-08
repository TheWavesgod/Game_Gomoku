#include "GameMode.h"

// add sound
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

#include <conio.h>
#include <iostream>

GameMode::GameMode(Player* C_player, AI* C_ai, ChessBoard* C_chessBoard)
{
	this->player = C_player;
	this->ai = C_ai;
	this->chessBoard = C_chessBoard;

	this->player->init(chessBoard);

	initgraph(1024, 1024);
	loadimage(NULL, "Resources/MainMenu.png", 1024, 1024, true);
	loadimage(&mainMenuImg, "Resources/MainMenu.png", 1024, 1024, true);

	float k = 0.38;
	loadimage(&startGameImg, "Resources/startgame.png", k * 902, k * 320);
	loadimage(&gameOverImg, "Resources/gameover.png", k * 902, k * 320);

	float j =0.45;
	loadimage(&startGameMagImg, "Resources/startgame.png", j * 902, j * 320);
	loadimage(&gameOverMagImg, "Resources/gameover.png", j * 902, j * 320);

	putImagePNG(70, 550, &startGameImg);
	putImagePNG(70, 750, &gameOverImg);

	// background music
	mciSendString("play Resources/bgm.mp3 repeat", 0, 0, 0);

}

int GameMode::mainMenu()
{
	MOUSEMSG msg;
	bool startGameFlag = true;
	bool gameOverFlag = true;

	while (1)
	{
		msg = GetMouseMsg();
		switch (msg.uMsg)
		{
		case WM_MOUSEMOVE:
			mouseMove(msg, startGameFlag, gameOverFlag);
			break;

		case WM_LBUTTONDOWN:
			if (isMouseOnStartGame(msg.x, msg.y) == true)
			{
				mciSendString("play Resources/btn.wav", 0, 0, 0);
				Sleep(500);
				play();
			}
			if (isMouseOnGameOver(msg.x, msg.y) == true)
			{
				mciSendString("play Resources/btn.wav", 0, 0, 0);
				Sleep(500);
				return 0;
			}
			break;
		}
	}

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

void GameMode::putImagePNG(int x, int y, IMAGE* picture)
{
	// 变量初始化
	DWORD* dst = GetImageBuffer();    // GetImageBuffer()函数，用于获取绘图设备的显存指针，EASYX自带
	DWORD* draw = GetImageBuffer();
	DWORD* src = GetImageBuffer(picture); //获取picture的显存指针
	int picture_width = picture->getwidth(); //获取picture的宽度，EASYX自带
	int picture_height = picture->getheight(); //获取picture的高度，EASYX自带
	int graphWidth = getwidth();       //获取绘图区的宽度，EASYX自带
	int graphHeight = getheight();     //获取绘图区的高度，EASYX自带
	int dstX = 0;    //在显存里像素的角标

	// 实现透明贴图 公式： Cp=αp*FP+(1-αp)*BP ， 贝叶斯定理来进行点颜色的概率计算
	for (int iy = 0; iy < picture_height; iy++)
	{
		for (int ix = 0; ix < picture_width; ix++)
		{
			int srcX = ix + iy * picture_width; //在显存里像素的角标
			int sa = ((src[srcX] & 0xff000000) >> 24); //0xAArrggbb;AA是透明度
			int sr = ((src[srcX] & 0xff0000) >> 16); //获取RGB里的R
			int sg = ((src[srcX] & 0xff00) >> 8);   //G
			int sb = src[srcX] & 0xff;              //B
			if (ix >= 0 && ix <= graphWidth && iy >= 0 && iy <= graphHeight && dstX <= graphWidth * graphHeight)
			{
				dstX = (ix + x) + (iy + y) * graphWidth; //在显存里像素的角标
				int dr = ((dst[dstX] & 0xff0000) >> 16);
				int dg = ((dst[dstX] & 0xff00) >> 8);
				int db = dst[dstX] & 0xff;
				draw[dstX] = ((sr * sa / 255 + dr * (255 - sa) / 255) << 16)  //公式： Cp=αp*FP+(1-αp)*BP  ； αp=sa/255 , FP=sr , BP=dr
					| ((sg * sa / 255 + dg * (255 - sa) / 255) << 8)         //αp=sa/255 , FP=sg , BP=dg
					| (sb * sa / 255 + db * (255 - sa) / 255);              //αp=sa/255 , FP=sb , BP=db
			}
		}
	}
}

void GameMode::mouseMove(MOUSEMSG& msg, bool& startGameFlag, bool& gameOverFlag)
{
	if (isMouseOnStartGame(msg.x, msg.y) == true)
	{
		if (startGameFlag == true)
		{
			changeStartGameImageStation(startGameFlag);
			startGameFlag = false;
		}
	}
	else
	{
		if (startGameFlag == false)
		{
			changeStartGameImageStation(startGameFlag);
			startGameFlag = true;
		}
	}

	if (isMouseOnGameOver(msg.x, msg.y) == true)
	{
		if (gameOverFlag == true)
		{
			changeGameOverImageStation(gameOverFlag);
			gameOverFlag = false;
		}
	}
	else
	{
		if (gameOverFlag == false)
		{
			changeGameOverImageStation(gameOverFlag);
			gameOverFlag = true;
		}
	}
}

bool GameMode::isMouseOnStartGame(int x, int y)
{
	if (x - 70 > 0 && x - 70 < 342 && y - 550 > 0 && y - 550 < 121)
	{
		return true;
	}
	return false;
}

bool GameMode::isMouseOnGameOver(int x, int y)
{
	if (x - 70 > 0 && x - 70 < 342 && y - 750 > 0 && y - 750 < 121)
	{
		return true;
	}
	return false;
}

void GameMode::changeStartGameImageStation(bool Flag)
{
	if (Flag == true)
	{
		putimage(70, 550, 342, 121, &mainMenuImg, 70, 550);
		putImagePNG(40, 540, &startGameMagImg);
	}
	else
	{
		putimage(40, 540, 405, 144, &mainMenuImg, 40, 540);
		putImagePNG(70, 550, &startGameImg);
	}
}

void GameMode::changeGameOverImageStation(bool Flag)
{
	if (Flag == true)
	{
		putimage(70, 750, 342, 121, &mainMenuImg, 70, 750);
		putImagePNG(40, 740, &gameOverMagImg);
	}
	else
	{
		putimage(40, 740, 405, 144, &mainMenuImg, 40, 740);
		putImagePNG(70, 750, &gameOverImg);
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
