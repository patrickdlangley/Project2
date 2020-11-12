// Jared Smith
// CIS 1111
// 11/22/2019
// Final project
/* This program runs an AI for the game Captain Sonar with different type of AI  */
// Last revision 12/13/2019 10:50pm

#include <iostream>
#include <string>
#include <iomanip>
#include <thread>
#include <future>   
#include <exception>
#include <cstdlib>    
#include <ctime>
#include <time.h>
#include <windows.h> 
#include <conio.h>
#include <random>
#include <fstream> 

// Data storage variables
int mapNumber;


using namespace std;

bool mapBoundries[15][15]; // This will only hold the map boundries and no ones path
int userSonarHints[4]; // TODO Set up Radio OP use of sonar hints

int userPositionCount;
int userSurfacePosition[3]; // TODO Set up the Radio OP's use of Surface Position

string userPositions[50]; // Saves every move the user makes

int triedPosition[51][2]; // counts how long the user has gone and is the active position the Radio OP is editing

bool positionsSaved[4] = { false,false,false,false }; // Says if a position has a saved variable or not
int userPossibleLocation[4][4];// Global variable so that others can read it while only Radio OP can edit it

bool AIRadipOPTriedSpaces[15][15]; // MAY NOT BE NEEDED NOW BUT FUTURE USE

int radioCertainty = 0; // How certain the Radio AI is about where the user is
int surfaceTime = 0; // How long the Captain has to wait until his play can resume

bool AIMap[15][15]; // Saves the map boundries and the path of the AI

int userReadTries = 0; // A variable that is updated when the Radio OP is told to stop. It is the read head of the user
bool userDeadZones[15][15]; // Saves the map boundries and the path of the user (For what the Radio OP think he has gone)
int AIPath[50][2]; // Saves the AI's path 
string AICompass[30]; // Saves the AI's compass head for north, south, east, and west
int nextPath = 0; // Next write location for the AIPath


const int KEY_ARROW_CHAR1 = 224;
const int KEY_ARROW_UP = 72;
const int KEY_ARROW_DOWN = 80;
const int KEY_ARROW_LEFT = 75;
const int KEY_ARROW_RIGHT = 77;

bool XFailed[2]; // These three may be able to be put into own function. Probably should
bool YFailed[2];
bool XorY;

// engineer variables
bool shouldSurface = false;
int engNextPath = 1; // instead of using nextPath that the captain uses the engineer is special and gets his own
int engineerUses; // How many more times the engineer has to work until waiting for more work
bool moveForWant[4]; // Suggests where the captain should move to keep wants active

// first mate variables
bool firstMateListMade = false; // It's his christmas list
int firstMateUses; // How many times the first mate has to go until being done

// captain variables
bool AICalled[8];
bool wants[3]; // Wants means guns detection or silence
int activeMine = 0;
int beInRangeofUser = 0; // For personality of AI. Sometimes he just want's to be closer ok?
int AIHealth = 4;
int userTorpedoPosition[2];
int minesPosition[5][2]; // Saves captains Mines
int mineCount = 0; // Named accordingly


bool mapChosen = false; // All of these bools are for a couple of things that can't really be put in there own function
bool AISurfaced = false;// TODO Go over bools and remove what doesn't need to be there
bool AIFirstPosition = false;
bool keepUserPosition = false;
bool added;
bool writePathDone;
bool menuDone;
bool gameover;
bool movementDone;
bool AICalledStop = true;


bool gunsBroke; // These are used by the captain and the First mate and maybe somewhere else
bool detectionBroke;
bool specialBroke;

char YNInputs() { // Allows the user to enter a letter and get instant feedback
	bool givenInput = false;
	while (!givenInput) {
		if (_kbhit()) {
			switch (_getch()) {
			case 'n':
				return 'n';
				break;
			case 'y':
				return 'y';
				break;
			}
		}
	}
	return 'n';
}
struct AITypes { // This is the struct holding this whole program together. It saves the AiTypes and data about them
	int difficulty = 1;
	string type = "Easy";
	int responseTime = 20;
	bool done;

}captain, engineer, firstMate, radioOP;
