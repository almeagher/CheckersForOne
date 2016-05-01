/*
 * game.cpp
 *
 *      Author: Harrison
 */

#include <assert.h>
#include <algorithm>
#include <cctype>
#include <iostream>
#include "game.h"
#include <iostream>
#include <limits>
#include <list>
#include "board.h"
#include <time.h>


using std::cin;
using std::cout;
using std::endl;
using std::max;
using std::min;
using std::list;

//highly unlikely to be able to search to depth 20 within maximum time limit
const int game::maxIterDepth = 20;

//game's constructor
game::game(): currentB(sptr<board>(new board())), bestM(NULL), tempBestM(NULL), maxdepth(0),
		cdepth(0), timeUp(false), gameOver(false), reachedEnd(false), startTime(0), endTime(0),
		startTimeD(0), endTimeD(0) {}

//generates more turns and starts up the game
void game::playTheGame(bool p1, bool p2, Driver &driver, Checkerboard &chk){
	gameOver = false;
	currentB->startup(p1, p2);
	while (!gameOver)
		printGame(driver, chk);
}

//message for game over
//prompts user to play again or not
//calls playTheGame if answer is yes
void game::endMessage(Driver &driver){
	gameOver = true;
	cout << "The game is over." << endl;
	cout << endl;
	if (currentB->getTurn() == 'r'){
		cout << "Player 1 wins." << endl;
		for(int i = 0; i < 4; i++){
			for(int j = 0; j < 4; j++){
				ledBoard[i][j].r = 0;
				ledBoard[i][j].g = 128;
				ledBoard[i][j].b = 0;
			}
		}
		driver.writeToLeds(ledBoard);
	}
	else{
		cout << "Player 2 wins." << endl;
		for(int i = 5; i < 8; i++){
			for(int j = 5; j < 8; j++){
				ledBoard[i][j].r = 0;
				ledBoard[i][j].g = 128;
				ledBoard[i][j].b = 0;
			}
		}
		driver.writeToLeds(ledBoard);
	}
}

//computer's turn
//calls alpha beta search
//if there's only one available move, makes that move immediately
//prints out depth searched to, time searching, and move made afterwards through outputMessage
void game::computerTurn(Driver &driver, Checkerboard &chk){
	//moves for current board are already created in printGame function
	//game over scenario also taken care of in printGame
	currentB->printMoves(driver, chk);
	cout << "The computer will make a move." << endl;

	//if there's only one move to make, make it immediately
	//this may occur for jump moves
	if (currentB->mlist.size() == 1){
		bestM = currentB->mlist.front();
		time(&startTime);
		time(&endTime);
		cdepth = 0;
	}
	else{
		//start the timer for the search
		time(&startTime);
		for (int i = 1; i != maxIterDepth; ++i){
			//keep track of amount of time searched up to a specific depth
			time(&startTimeD);

			//changes maxdepth
			maxdepth = i;

			//calls alpha beta search up to depth maxdepth, with alpha = -infinity and beta = infinity
			alphabeta(currentB, i, std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
			time(&endTimeD);

			//if the search up to a specific depth took more than half the time limit
			//terminate the search by breaking out of the loop
			if (difftime(endTimeD, startTimeD) >= ((board::timeLimit)/2)){
				time(&endTime);
				timeUp = true;
				break;
			}

			//break out of loop if time's up
			//if time isn't up, either the remaining game space has been explored
			//or search to maxIterDepth was completed; sets bestM = tempBestM
			if (timeUp)
				break;
			else
				bestM = tempBestM;

			//test if alpha beta is done searching remaining game space, no need to go deeper/repeat
			if (reachedEnd)
				break;
		}
	}
	assert(bestM != NULL);

	//output appropriate message for computer's search results
	outputMessage(driver, chk);
}

//prints out computer's move
//also resets bestM, tempBestM, timeUp, and reachedEnd
void game::outputMessage(Driver &driver, Checkerboard &chk){
	currentB->makeMove(bestM);
	cout << "The chosen move is: ";
	board::convertCommand(bestM->command, driver, chk);
	vector<int> p = (board:: getPossible());
	string compMove = to_string(p[0]) + " " + to_string(p[1]) + " " + to_string(p[2]) + " " + to_string(p[3]);
	cout <<"Comp moved: " << compMove << endl;
	board::setLEDBoard(board::getPossible(), driver, chk);
	
	cout << endl;
	
	
	
	/*if(chk.getPieceMoved() == compMove){
		
	}*/
	
	
	//resets everything used for next alpha-beta search
	bestM = NULL;
	tempBestM = NULL;
	timeUp = false;
	reachedEnd = false;
}

//prints the game board
//outputs game over message if necessary;
//generates moves for current player's turn if there are any
//if the game has not ended, it
//makes the computer make a move
//or prompts user to make a move
void game::printGame(Driver &driver, Checkerboard &chk){
	currentB->printBoard();
	if (currentB->terminalTest())
		endMessage(driver);
	else if (currentB->isComputerTurn())
		computerTurn(driver, chk);
	else
		currentB->inputCommand(driver, chk);
}

//fail-hard alpha beta
//returns alpha / beta instead of value
int game::alphabeta(sptr<board>& b, int depth, int alpha, int beta){
	if (depth != maxdepth && b->terminalTest()){	//don't need to compute moves for depth 0
		//b->printBoard();
		reachedEnd = true;	//set reached end as true
		cdepth = maxdepth;
		if (b->getTurn() == 'r')
			return std::numeric_limits<int>::max();
		else return std::numeric_limits<int>::min();
	}
	reachedEnd = false;	//set reached end as false, means that remaining game space still isn't fully explored
	if (depth == 0)
		return b->evaluate();
	list<moveBoard*>::iterator iter = b->mlist.begin();

	int localalpha = std::numeric_limits<int>::min();
	int localbeta = std::numeric_limits<int>::max();

	//max's turn
	if (b->getTurn() == 'b'){
		for (; iter != b->mlist.end(); ++iter){
			//update the end time
			time(&endTime);

			//check if time's up
			//if it is, break out of the loop
			if (difftime(endTime, startTime) >= (board::timeLimit - 1))
			{
				timeUp = true;
				break;
			}

			//make the move
			//create a new board using the copy constructor
			//the move has been made for the new board
			//and pass it as a parameter to alpha beta,
			//along with depth reduced by one
			//undo the move and revert the turn
			//this is because undoMove doesn't change turn
			b->makeMove(*iter);
			sptr<board> newB(new board(*b));
			int value = alphabeta(newB, depth-1, alpha, min(localbeta, beta));
			b->undoMove(*iter);
			b->changeTurn();

			//found best move
			if (value > alpha){
				alpha = value;
				if (depth == maxdepth)
					tempBestM = (*iter);
			}

			//cut off
			if (alpha >= beta && depth < maxdepth)
				return alpha;
		}

		//search has been completed to depth = maxdepth
		//update cdepth to be equal to maxdepth
		if (!timeUp && depth == maxdepth)
			cdepth = depth;

		//this is max's best move
		return alpha;
	}

	// turn = 'r'
	//min's turn
	//almost identical to max's
	//returns beta instead of alpha
	//tests value < beta instead of if value > alpha
	//for finding best move
	else{
		for (; iter != b->mlist.end(); ++iter){
			time(&endTime);
			if (difftime(endTime, startTime) >= (board::timeLimit - 1)){
				timeUp = true;
				break;
			}
			b->makeMove(*iter);
			sptr<board> newB(new board(*b));
			int value = alphabeta(newB, depth-1, max(localalpha, alpha), beta);
			b->undoMove(*iter);
			b->changeTurn();

			//found best move for min
			if (value < beta){
				beta = value;
				if (depth == maxdepth)
					tempBestM = (*iter);
			}

			//cut off
			if (alpha >= beta)
				return beta;
		}

		//search has been completed to depth = maxdepth
		//update cdepth to be equal to maxdepth
		if (!timeUp && depth == maxdepth)
			cdepth = depth;

		//this is min's best move
		return beta;
	}
}
