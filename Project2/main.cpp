#include <iostream>
#include <getopt.h>
#include <vector>
#include <string>
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
	Dictionary dic(length);
	_(cout << "Got dic!\n";)
	return 0;
}