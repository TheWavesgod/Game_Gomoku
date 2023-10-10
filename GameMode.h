#pragma once

#include "Player.h"
#include "AI.h"
#include "ChessBoard.h"

class GameMode
{
public:
	int mainMenu();

	// game start!
	void play();

	void setPlayerChess(bool playerChessFlag);

public:
	GameMode(Player* C_player, AI* C_ai, ChessBoard* C_chessBoard);

private:
	Player* player;
	AI* ai;
	ChessBoard* chessBoard;

	IMAGE mainMenuImg;
	IMAGE startGameImg;
	IMAGE gameOverImg;

	IMAGE startGameMagImg;
	IMAGE gameOverMagImg;

	IMAGE GameWinImg;
	IMAGE GameLoseImg;

	IMAGE Blink;

	IMAGE AgainImg;
	IMAGE returnMainMenuImg;

	// Indicate what chess kind player choose. true reps black, false reps white.
	bool playerFlag;
	// Indicate who the chess player is now. true reps player, false reps ai.
	bool flag;

	void initMainMenu();

	void checkWin();

	void putImagePNG(int x, int y, IMAGE* picture);

	void mouseMove(MOUSEMSG& msg, bool& startGameFlag, bool& gameOverFlag);

	bool isMouseOnStartGame(int x, int y);
	bool isMouseOnGameOver(int x, int y);

	bool isMouseOnBlackChess(int x, int y);
	bool isMouseOnWhiteChess(int x, int y);

	void setPlayerChessBlack();
	void setPlayerChessWhite();

	void changeStartGameImageStation(bool Flag);
	void changeGameOverImageStation(bool Flag);

	int gameOver();
	void mouseMoveOverMenu(MOUSEMSG& msg, bool& againFlag, bool& returnFlag);

	bool isMouseOnAgain(int x, int y);
	bool isMouseOnReturn(int x, int y);

	void changeAgainImageStation(bool Flag);
	void changeReturnImageStation(bool Flag);
};

