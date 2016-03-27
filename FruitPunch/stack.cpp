#include "stack.h"
#include <iostream>
#include <cstdio>

void Stack::print_debug() {
	using namespace std;
	cout << '[' << stack.size() << "] (";
	for (int i = 0; i < stack.size(); i++) {
		if (i > 0) cout << ", ";
		auto v = stack[i];
		//cout << v->get_debug_string() << ":" << v->get_debug_type();
		printf("%s:%s", v->get_debug_string(), v->get_debug_type());
	}
	cout << ")" << endl;
}
