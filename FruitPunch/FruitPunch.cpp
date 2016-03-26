// FruitPunch.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <string>
#include "version.h"

int main()
{
	using namespace std;
	// print app info
	cout << APP_NAME << ' ' << FP_VERSION << " (" << COMPILER_NAME << ')' << endl;

	// repl loop
	while (true) {
		// show prompt
		cout << "> ";
		// get user input
		string line;
		getline(cin, line);
		// allow user to exit repl (if they guess the magic password)
		if (line == ":q") break;
		// TODO: magic evaluation stuff goes here
		cout << line << endl; // for now just echoing input
	}

	return 0;
}

