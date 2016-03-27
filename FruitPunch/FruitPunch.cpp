// FruitPunch.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <string>
#include "version.h"
#include "parser.h"
#include <cstdio>

bool _isprint(char q) {
	return (q >= 0x20 && q < 0x7F);
}

void printDebugHex(unsigned char* start, unsigned char* end) {
	using namespace std;
	printf("[HEXDUMP] from 0x%08lX to 0x%08lX\n", start, end);
	for (unsigned char* c = start; c < end; c += 16) {
		printf("[%08lX] ", c);
		for (unsigned char* q = c; q < c + 16; q++) {
			if (q < end) {
				if ((q - c) % 4 == 3) {
					printf("%02X  ", *q);
				} else {
					printf("%02X ", *q);
				}
			} else {
				if ((q - c) % 4 == 3) {
					printf("    ", *q);
				} else {
					printf("   ", *q);
				}
			}
		}
		printf("   ");
		for (unsigned char* q = c; q < end && q < c + 16; q++) {
			if (_isprint(*q)) {
				printf("%c",*q);
			} else {
				printf(".");
			}
		}
		printf("\n");
	}
}
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
		//line = " 'Lorem ipsum dolor sit amet, consectetur adipiscing elit. Maecenas in nibh a ipsum tempus tristique at ac mauris. Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos. Vestibulum sit amet rhoncus dui, sit amet vulputate justo. Nam efficitur lectus et ex pulvinar malesuada. Curabitur convallis luctus condimentum. Mauris non sapien ac ligula aliquam auctor. Pellentesque finibus ornare luctus. Etiam ante nunc, eleifend vestibulum tincidunt fermentum, dignissim ac massa. Ut urna nunc, venenatis commodo ullamcorper vel, pellentesque a libero. Proin tincidunt elit sapien, nec elementum libero varius sed. Pellentesque semper volutpat sapien, in lobortis ipsum rutrum feugiat. Aenean venenatis condimentum lacus, placerat sodales velit egestas vestibulum. Sed aliquam mi ut purus rutrum, sed ullamcorper lorem pellentesque. Donec tristique mi orci, ac tristique lectus feugiat nec. Nam neque nulla, euismod luctus bibendum eu, imperdiet nec felis. Proin magna ex, semper ac vehicula eget, aliquet vitae arcu. Sed magna purus, efficitur vitae porta rhoncus, vestibulum id elit. Mauris scelerisque elementum vehicula. Pellentesque ut luctus tortor. Curabitur pellentesque elit eget libero auctor aliquet. Suspendisse in volutpat felis. Praesent et porttitor sapien. Pellentesque interdum ullamcorper velit ac posuere. Aliquam semper tempus ipsum non lobortis. Morbi sagittis nibh nec ultrices dictum. Curabitur eleifend leo ligula, vitae efficitur urna facilisis quis. Quisque non dolor vel purus vestibulum convallis et id turpis. Aenean eget ipsum accumsan, porta nisl at, elementum mauris. Curabitur tempus, risus ut mollis rutrum, mi ipsum molestie erat, eget porttitor felis sapien vitae tortor. Donec accumsan vel elit ut rhoncus. Duis eget rutrum ipsum, gravida posuere purus. Nulla a ipsum vitae sem accumsan vehicula. Suspendisse tincidunt magna non nisi commodo hendrerit. Proin malesuada sem nec risus tincidunt ultricies. Nullam aliquet aliquam massa vitae dictum. Interdum et malesuada fames ac nullam.'";
		// allow user to exit repl (if they guess the magic password)
		if (line == ":q") break;
		// TODO: magic evaluation stuff goes here
		cout << line << endl; // for now just echoing input
		// debug parser print
		char* c_str = &line[0];
		Closure* clos = parseClosure(c_str, c_str + line.length());
		printDebugHex((unsigned char*) clos->bytecode, (unsigned char*) clos->bytecode + clos->len);
		delete clos;
	}

	return 0;
}

