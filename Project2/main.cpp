#include <iostream>
#include <string>
using namespace std;

int main() {
	int i = 0;
	cout << "Hello world!" << endl;
	cout << "What is your name?" << endl;
	string userName;
	cin >> userName;
	while (cin >> userName) {
		if (userName == "Exit" || userName == "exit")
			break;
		else
			cout << userName << endl;
	}
	return 0;
}