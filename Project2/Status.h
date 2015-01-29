#include <iostream>
#include <getopt.h>
#include <string>
#include <cstring>
#include <cassert>

#ifdef DEBUG
#define _(args) args
#else
#define _(args)
#endif

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
	void Meet_o(const char *optarg) {
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
	void Meet_b(const char *optarg) {
		beginWord = optarg;
	}
	void Meet_e(const char* optarg) {
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

	void SetUpStatus(int argc, char **argv) {
		struct option longOpts[] = {
				{ "stack", no_argument, NULL, 's' },
				{ "queue", no_argument, NULL, 'q' },
				{ "change", no_argument, NULL, 'c' },
				{ "length", no_argument, NULL, 'l' },
				{ "output", required_argument, NULL, 'o' },
				{ "begin", required_argument, NULL, 'b' },
				{ "end", required_argument, NULL, 'e' },
				{ "help", no_argument, NULL, 'h' },
		};

		// Turn getopt error message on (true) or off (false)
		// opterr is declared in getopt.h, is on by default
		opterr = true;
		char *remember = nullptr;
		int opt = 0, index = 0;

		// "sqclo:b:e:h" repeats the allowed flags
		// The : after 0 dontes the required argument for option o
		while ((opt = getopt_long(argc, argv, "sqclo:b:e:h", longOpts, &index)) != -1) {
			switch (opt) {
			case 's':
				Meet_s();
				break;
			case 'q':
				Meet_q();
				break;
			case 'c':
				Meet_c();
				break;
			case 'l':
				Meet_l();
				break;
			case 'o':
				Meet_o(optarg);
				break;
			case 'b':
				Meet_b(optarg);
				break;
			case 'e':
				Meet_e(optarg);
				break;
			case 'h':
				Meet_h();
				break;
			default:
				break;
			}
		}
		// do the final set up for the status to determine the modes and start/end word
		SetUp();
		_(cout << "Successfully implemented SetUpStatus\n";)
	}

public:

	Status(int argc_in, char** argv_in) :
		ifStackModeOn(true),
		ifChangeModeOn(false), ifLengthModeOn(false),
		ifWordModeOn(true),
		beginWord(""), endOWord(""),
		n_s_flag(0), n_q_flag(0),
		n_c_flag(0), n_l_flag(0) {
		SetUpStatus(argc_in, argv_in);
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

