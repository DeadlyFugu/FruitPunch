#include "symbols.h"
#include <map>
#include <string>
#include <iostream>

std::map<std::string, symbol_t> sym_lookup;
std::map<symbol_t, std::string> sym_name_lookup;
symbol_t next_sym = 0;

symbol_t symbol(char* name) {
	std::string name_str(name);
	auto it = sym_lookup.find(name_str);
	if (it == sym_lookup.end()) {
		return sym_lookup[name_str] = next_sym++;
	} else {
		return it->second;
	}
}

const char* symbol_name(symbol_t sym) {
	auto it = sym_name_lookup.find(sym);
	if (it == sym_name_lookup.end()) {
		return nullptr;
	} else {
		return it->second.c_str();
	}
}

void dump_symbol_table() {
	using namespace std;
	cout << "[SYMTAB]" << endl;
	for (auto it = sym_lookup.begin(); it != sym_lookup.end(); it++) {
		cout << it->first << " [" << it->second << "]" << endl;
	}
}