#include <iostream>
#include <getopt.h>
using namespace std;

// This program takes in two arguments:
// argc: the number of things on the command line
// argv: an array of C-strings that are on the command line
int main(int argc, char **argv) {
	// --choiceA or -a does not have a required argument
	// --choiceB or -b DOES have a required argument
	// --help or -h has no required arguments

	struct option longOpts[] = {
			{ "choiceA", no_argument, NULL, 'a' },
			{ "choiceB", required_argument, NULL, 'b' },
			{ "help", no_argument, NULL, 'h' },
	};

	// Turn getopt error message on (true) or off (false)
	// opterr is declared in getopt.h, is on by default
	opterr = false;

	char *remember = nullptr;

	int opt = 0, index = 0;
	// "ab:h" repeats the allowed flags
	// The : after b dontes the required argument for option b
	while ((opt = getopt_long(argc, argv, "ab:h", longOpts, &index)) != -1) {
		switch (opt) {
		case 'a':
			cout << "You chose A\n";
			break;
		case 'b':
			// optarg is defined in getopt.h
			cout << "You chose B with option " << optarg << "\n";
			remember = optarg;
			break;
		case 'h':
			cout << "You want help?  This program accepts:\n";
			cout << "  -a, --choiceA       The first choice\n";
			cout << "  -b, --choiceB ARG   This choice needs an argument\n";
			cout << "  -h, --help          This help page\n";
			break;
		default:
			cout << "I didn't recognize one of your flags!\n";
		}
	}

	if (remember)
		cout << "I remember this string: " << remember << endl;

	return 0;
}