#include <iostream>
#include <getopt.h>
#include <cstring>
#include <stdio.h>
#include <string>
using namespace std; 

#pragma once
class Status {
private:
	bool ifStackModeOn;
	bool ifChangeModeOn, ifLengthModeOn;
	bool ifWordModeOn;

	string beginWord;
	string endOWord;

	int n_s_flag, n_q_flag;
	int n_c_flag, n_l_flag;
	
public:

	Status() :
		ifStackModeOn(true),
		ifChangeModeOn(false), ifLengthModeOn(false),
		ifWordModeOn(true),
		beginWord(""), endOWord(""),
		n_s_flag(0), n_q_flag(0),
		n_c_flag(0), n_l_flag(0) {}

	// count the times that each flag appears
	void Meet_s() {
		++n_s_flag;
	}
	void Meet_q() {
		++n_q_flag;
	}
	void Meet_c() {
		++n_c_flag;
	}
	void Meet_l() {
		++n_l_flag;
	}
	void Meet_o(const extern char *optarg) {
		if (strcmp(optarg, "W") != 0 && strcmp(optarg, "M") != 0) {
			cerr << "The --output/-o flag is followed by an invalid character\n";
			exit(1);
		}
		else if (strcmp(optarg, "W") == 0)
			ifWordModeOn = true;
		else if (strcmp(optarg, "M") == 0)
			ifWordModeOn = false;
		else;
	}
	void Meet_b(const extern char *optarg) {
		beginWord = optarg;
	}
	void Meet_e(const extern char* optarg) {
		endOWord = optarg;
	}
	void Meet_h() {
		cout << "/*help contents*/\n"; // unfinished
		exit(1);
	}

	// decide if stack mode or quene mode should be turned on
	void SetStackOrQueue() {
		if ((n_s_flag != 1 && n_q_flag != 1) ||
			(n_s_flag == 1 && n_q_flag == 1)) {
			cerr << "More or less than one --stack/-s or --queue/-q on the command line\n";
			exit(1);
		}
		else if (n_s_flag == 1)
			ifStackModeOn = true;
		else if (n_q_flag == 1)
			ifStackModeOn = false;
		else;
	}

	// decide if change mode and length mode should be turned on
	void SetChangeAndLength() {
		if (!n_c_flag && !n_l_flag) {
			cerr << "No --change/-c or --length/-l on the command line\n";
			exit(1);
		}
		if (n_c_flag == 1) {
			ifChangeModeOn = true;
		}
		if (n_l_flag == 1)
			ifLengthModeOn = true;
	}

	void CheckIfWordsEntered() {
		if (beginWord.empty()) {// || endOWord.empty()) {
			cerr << "Start word is not specified\n";
			exit(1);
		}
		if (endOWord.empty()) {
			cerr << "End word is not specified\n";
			exit(1);
		}
	}
	// see if the input is impossible to accomplish
	void CheckImpossibleCase() {
		if (n_c_flag == 1 &&
			n_l_flag == 0 &&
			beginWord.length() != endOWord.length()) {
			cerr << "The --change/-c flag is specified but --length/-l is not, and the start/end word do not match in length, creating an impossible situation\n";
			exit(1);
		}
	}

	// final set up
	void SetUp() {
		SetStackOrQueue();
		SetChangeAndLength();
		CheckIfWordsEntered();
		CheckImpossibleCase();
	}

	// return the mode status
	bool ifStackMode() const {
		return ifStackModeOn;
	}
	bool ifChangeMode() const {
		return ifChangeModeOn;
	}
	bool ifLengthMode() const {
		return ifLengthModeOn;
	}
	bool ifWordMode() const {
		return ifWordModeOn;
	}

	// return start word
	const string & startWord() {
		return beginWord;
	}
	// return end word
	const string & endWord() {
		return endOWord;
	}

	~Status() {}
};

