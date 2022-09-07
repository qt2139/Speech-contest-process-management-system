#include <iostream>
using namespace std;
#include "speechManager.h"
#include<string>
#include<ctime>
int main()
{	
	// random
	srand((unsigned int)time(NULL));
	// create a management class object
	SpeechManager sm;

	int choice = 0; // save user input
	while (true) {
		sm.show_Menu();

		cout << "Please enter your selection:" << endl;
		cin >> choice; // receive user's options

		switch (choice)
		{
		case 1: // start speech contest
			sm.startSpeech();
			break;
		case 2: // view past records
			sm.loadRecord();
			break;
		case 3: // clear contest record
			sm.clearRecord();
			break;
		case 0: // exit the contest program
			sm.exitSystem();
			break;
		default:
			system("cls");
			break;
		}
	}
	system("pause");
	return 0;
}