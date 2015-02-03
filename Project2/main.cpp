#include <iostream>
#include <getopt.h>
#include <vector>
#include <string>
#include <deque>
#include "Status.h"
#include "Dictionary.h"

#ifdef DEBUG
#define _(args) args
#else
#define _(args)
#endif

#include <cassert>

using namespace std;

//void Path(Status & status, Dictionary & dic);

/*void SetUpStatus(Status & status, int argc, char **argv) {

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
			status.Meet_s();
			break;
		case 'q':
			status.Meet_q();
			break;
		case 'c':
			status.Meet_c();
			break;
		case 'l':
			status.Meet_l();
			break;
		case 'o':
			status.Meet_o(optarg);
			break;
		case 'b':
			status.Meet_b(optarg);
			break;
		case 'e':
			status.Meet_e(optarg);
			break;
		case 'h':
			status.Meet_h();
			break;
		default:
			break;
		}
	}

	// do the final set up for the status to determine the modes and start/end word
	status.SetUp();

	/*_(cout << "Successfully implemented SetUpStatus\n";)
	_(assert(!status.ifStackMode() &&
			 status.ifLengthMode() && 
			 status.ifChangeMode() &&
			 status.ifWordMode() &&
			 status.startWord() == "start2" &&
			 status.endWord() == "end2");)*/
//}*/

//void dfs(Dictionary::lemma start, Dictionary::lemma end, deque<deque<Dictionary::lemma>*> & output, Status & status);
void bfs(Dictionary::lemma start, Dictionary::lemma end, deque<deque<Dictionary::lemma>*> & output, Dictionary & dic);
void printOutput1(const deque<deque<Dictionary::lemma>*> & output);
// This program takes in two arguments:
// argc: the number of things on the command line
// argv: an array of C-strings that are on the command line
int main(int argc, char **argv) {
	// turn off the synchronized I/O
	ios_base::sync_with_stdio(false);

	// determine the modes from given flags
	Status status(argc, argv);

	_(assert(!status.ifStackMode() &&
		status.ifLengthMode() &&
		status.ifChangeMode() &&
		!status.ifWordMode() &&
		status.startWord() == "start2" &&
		status.endWord() == "end2");)

	unsigned int length = 0;
	cin >> length;
	cin.ignore();
	Dictionary dic(status, length);
	_(cout << "Got dic!\n";)

	deque<deque<Dictionary::lemma>*> output;
	bfs(dic.beginWord, dic.endWord, output, dic);
	printOutput1(output);
	return 0;
}

//void bfs(const Dictionary::lemma start,const Dictionary::lemma end, deque<Dictionary::lemma> & output, Status & status) {
void bfs(Dictionary::lemma start, Dictionary::lemma end, deque<deque<Dictionary::lemma>*> & output, Dictionary & dic) {
	start.setVisited(true);
	assert(output.empty());
	auto startTemp = new deque < Dictionary::lemma > ;
	startTemp->push_back(start);
	output.push_back(startTemp);
	startTemp = nullptr;
	while (!output.empty()) {
		if (output.back()->empty()) {
			output.pop_back();
			if (!output.empty())
				output.back()->pop_front();
			else
				break;
		}
		auto suc = output.back()->front().getUnvisitedSuccessors(dic);
		if (suc->empty())
			output.back()->pop_front();
		else
			output.push_back(suc);
		suc = nullptr;
		if (output.back()->front() == end)
			break;
	}
}

void printOutput1(deque<deque<Dictionary::lemma>*> &output) {
	while (!output.empty()) {
		cout << output.front()->front().getContent() << "\n";
		delete output.front(); output.front() = nullptr;
		output.pop_front();
	}
}