#pragma once 
#include <iostream>
using namespace std;
#include <vector>
#include <map>
#include "speaker.h"
#include <algorithm>
#include <deque>
#include <functional>
#include <numeric>
#include <string>
#include <fstream>

class SpeechManager
{
public:
	// constructor 
	SpeechManager();

	// menu
	void show_Menu();

	// exit the system
	void exitSystem();

	// destructor 
	~SpeechManager();

	// initialize container and properties
	void initSpeech();

	// create 12 speakers
	void createSpeaker();

	//start the contest, this function controls the contest flow.
	void startSpeech();

	// start drawing lots
	void speechDraw();

	// contest
	void speechContest();

	// show result
	void showScore();

	// save result
	void saveRecord();

	// load result
	void loadRecord();

	// show pass results
	void showRecord();

	// clear results
	void clearRecord();

	// check if the file is empty
	bool fileIsEmpty;

	// save past records
	map<int, vector<string>>m_Record;

	// save the first round results
	vector<int>v1;

	// the number of the winner of the first round.
	vector<int>v2;

	// the number of the top three winners
	vector<int>vVictory;

	// save numbers and players
	map<int, Speaker>m_Speaker;

	// number of rounds
	int m_Index;
};
