#include "speechManager.h"

// Constructor 
SpeechManager::SpeechManager()
{
	// initialize
	this->initSpeech();

	// create 12 players
	this->createSpeaker();

	// load pass result
	this->loadRecord();
}

// menu
void SpeechManager::show_Menu()
{
	cout << "**********************************************************" << endl;
	cout << "*************  Welcome to the speech contest *************" << endl;
	cout << "*************  1. Start speech contest       *************" << endl;
	cout << "*************  2. View past records          *************" << endl;
	cout << "*************  3. Clear contest record       *************" << endl;
	cout << "*************  0. Exit the contest program   *************" << endl;
	cout << "**********************************************************" << endl;
	cout << endl;
}

// exit the system
void SpeechManager::exitSystem() {
	cout << "Welcome to use next time" << endl;
	system("pause");
	exit(0);
}

void SpeechManager::initSpeech()
{
	// initialize
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->m_Speaker.clear();

	// initialize
	this->m_Index = 1;

	// initialize
	this->m_Record.clear();
}

// create 12 speakers
void SpeechManager::createSpeaker()
{
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameSeed.size(); i++)
	{
		string name = "player";
		name += nameSeed[i];

		// create player
		Speaker sp;
		sp.m_Name = name;

		for (int j = 0; j < 2; j++)
		{
			sp.m_Score[j] = 0;
		}

		// create player numbers and put them into v1
		this->v1.push_back(i + 10001);

		// put the player number and player into the map.
		this->m_Speaker.insert(make_pair(i + 10001, sp));
	}
}

//start the contest, this function controls the contest flow.
void SpeechManager::startSpeech() {
	// the first round begins

	// start drawing lots
	this->speechDraw();

	// contest
	this->speechContest();

	// show result
	this->showScore();

	// the second round begins
	this->m_Index++;

	// 1. start drawing lots
	this->speechDraw();

	// 2. contest
	this->speechContest();

	// 3. show result
	this->showScore();

	// 4. save score to file
	this->saveRecord();

	// initialize
	this->initSpeech();

	// create 12 players
	this->createSpeaker();

	// load pass result
	this->loadRecord();

	cout << "This contest is over." << endl;
	system("pause");
	system("cls");
}

// start drawing lots
void SpeechManager::speechDraw()
{
	cout << "The " << this->m_Index << " >> round players are being drawn." << endl;
	cout << "--------------------------" << endl;
	cout << "The order of speeches after the draw is as follows." << endl;

	if (this->m_Index == 1)
	{
		// The first round contest.
		random_shuffle(v1.begin(), v1.end());
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	else
	{
		// The second round contest.
		random_shuffle(v2.begin(), v2.end());
		for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}

	cout << "--------------------------" << endl;
	system("pause");
	cout << endl;
}

// contest
void SpeechManager::speechContest()
{
	cout << "----------- The " << this->m_Index << " round start. --------------" << endl;

	// save groups' scores
	multimap<double, int, greater<double>> groupScore;

	int num = 0; // 6 people in a group

	vector<int>v_Src;// players' container
	if (this->m_Index == 1)
	{
		v_Src = v1;
	}
	else
	{
		v_Src = v2;
	}

	// iterate over all players to compete.
	for (vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++)
	{
		num++;
		// score
		deque<double>d;
		for (int i = 0; i < 10; i++)
		{
			double score = (rand() % 401 + 600) / 10.f;   // 600 - 1000
			// cout << score << " ";
			d.push_back(score);
		}
		//cout << endl;

		sort(d.begin(), d.end(), greater<double>());
		d.pop_front(); // remove the highest score
		d.pop_back(); // remove the lowest score

		double sum = accumulate(d.begin(), d.end(), 0.0f); // sum
		double avg = sum / (double)d.size();  // average

		// 
		//cout << "number " << *it << " name " << this->m_Speaker[*it].m_Name << " average score " << avg << endl;

		// put the average score into the map
		this->m_Speaker[*it].m_Score[this->m_Index - 1] = avg;

		// put the score into the multimap
		groupScore.insert(make_pair(avg, *it)); // key is score, value is player id 

		// every 6 people take out the top 3
		if (num % 6 == 0)
		{
			cout << "The " << num / 6 << " group result." << endl;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end(); it++)
			{
				cout << "Player ID " << it->second << "  Name " << this->m_Speaker[it->second].m_Name << " score "
					<< this->m_Speaker[it->second].m_Score[this->m_Index - 1] << endl;
			}

			// get top 3
			int count = 0;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end() && count < 3; it++, count++)
			{
				if (this->m_Index == 1)
				{
					v2.push_back((*it).second);
				}
				else
				{
					vVictory.push_back((*it).second);
				}
			}

			groupScore.clear(); // clear
			cout << endl;

		}
	}

	cout << "------------------ The " << this->m_Index << "round end. --------------" << endl;
	system("pause");
}

void SpeechManager::showScore()
{
	cout << "------------------ The round " << this->m_Index << " winners are as follows -------------------" << endl;

	vector<int>v;
	if (this->m_Index == 1)
	{
		v = v2;
	}
	else
	{
		v = vVictory;
	}

	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << "Player ID: " << *it << " name: " << this->m_Speaker[*it].m_Name << " score: " <<
			this->m_Speaker[*it].m_Score[this->m_Index - 1] << endl;
	}
	cout << endl;

	system("pause");
	system("cls");
	this->show_Menu();
}

void SpeechManager::saveRecord()
{
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app); //  write the file in append mode.

	// write everyone's data to the file.
	for (vector<int>::iterator it = vVictory.begin(); it != vVictory.end(); it++)
	{
		ofs << *it << "," << this->m_Speaker[*it].m_Score[1] << ",";
	}
	ofs << endl;

	// close file
	ofs.close();
	cout << "result has been saved" << endl;

	this->fileIsEmpty = false;
}

void SpeechManager::loadRecord()
{
	ifstream ifs("speech.csv", ios::in); // read file

	if (!ifs.is_open())
	{
		this->fileIsEmpty = true;
		//cout << "file does not exist." << endl;
		ifs.close();
		return;
	}

	// file is empty
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//cout << "file is empty" << endl;
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}

	// file is not empty
	this->fileIsEmpty = false;

	ifs.putback(ch); //  put the read characters back.

	string data;
	int index = 0;

	while (ifs >> data)
	{
		//cout << data << endl;
		//10002,86.675,10009,81.3,10007,78.55,

		vector<string>v; // save 6 players' score

		int pos = -1; // find ',' position
		int start = 0;

		while (true)
		{
			pos = data.find(",", start);
			if (pos == -1)
			{
				// not find
				break;
			}
			string temp = data.substr(start, pos - start);
			//cout << temp << endl;
			v.push_back(temp);
			start = pos + 1;
		}

		this->m_Record.insert(make_pair(index, v));
		index++;
	}

	ifs.close();

}

// show pass results
void SpeechManager::showRecord()
{
	if (this->fileIsEmpty)
	{
		cout << "The file is empty or the file does not exist." << endl;
	}
	else
	{
		for (int i = 0; i < this->m_Record.size(); i++)
		{
			cout << "The " << i + 1 << " Contest "
				<< " Championship number: " << this->m_Record[i][0] << " score: " << this->m_Record[i][1] << " "
				<< "Number two: " << this->m_Record[i][2] << " score: " << this->m_Record[i][3] << " "
				<< "Number three: " << this->m_Record[i][4] << " score: " << this->m_Record[i][5] << endl;
		}
	}


	system("pause");
	system("cls");
}

// clear record
void SpeechManager::clearRecord()
{
	cout << "Are you sure you want to clear the file?" << endl;
	cout << "1. Yes" << endl;
	cout << "2. No" << endl;

	int select = 0;

	cin >> select;

	if (select == 1)
	{
		// clear
		ofstream ofs("speech.csv", ios::trunc);
		ofs.close();

		// initialize
		this->initSpeech();

		// create 12 players
		this->createSpeaker();

		// load pass result
		this->loadRecord();

		cout << "cleared successfully" << endl;
	}

	system("pause");
	system("cls");
}

// Destructor 
SpeechManager::~SpeechManager()
{

}