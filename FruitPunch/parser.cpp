#include "parser.h"
#include <vector>
#include <iostream>

// disable dumb 'unsafe std::copy' warning
#define _SCL_SECURE_NO_WARNINGS

Closure* parse(int len, char* src) {
	return parseClosure(src, src + len);
}

bool hexdigit(char& c) {
	if (c < '0') return false;
	if (c <= '9') {
		c -= '0';
		return true;
	}
	if (c < 'A') return false;
	if (c <= 'F') {
		c -= 'A' - 10;
		return true;
	}
	if (c < 'a') return false;
	if (c <= 'f') {
		c -= 'a' - 10;
		return true;
	}
	return false;
}

Closure* parseClosure(char* start, char* end) {
	Closure* builder = new Closure();
	std::vector<char> bytecode;
#define ERROR(x) std::cout << "[synerr] " << x << std::endl; failure = true; goto FAILURE_LABEL;
#define POST(x) bytecode.push_back(x);
	char* c = start;
	char* token_start = nullptr;
	bool failure = false;
	while (c < end) {
		switch (*c) {
		case '\n':
		case ' ':
		case '\t':
		{
			if (token_start) {
				char* token_end = c - 1;
				// TODO process token
			}
			token_start = nullptr;
			c++;
			break;
		}
		// sub closures
		case '[':
		case '(':
		case '{':
		{
			// TODO recurse
			c++;
			break;
		}
		// quoted strings
		case '\'':
		case '\"':
		{
			if (token_start) {
				ERROR("unexpected quote mark mid token")
			}
			token_start = c + 1;
			char quote = *c;
			while (true) {
				switch (*++c) {
				case '\'':
				case '\"':
					// handle closing quotes
					if (*c == quote && *(c - 1) != '//') {
						char* token_end = c;
						POST(0x0B);
						for (char* p = token_start; p < token_end; p++)
							if (*p == '\\') {
								switch (*++p) {
								case '\\':
									POST('\\'); break;
								case '\'':
									POST('\''); break;
								case '\"':
									POST('\"'); break;
								case 'a':
									POST('\a'); break;
								case 'b':
									POST('\b'); break;
								case 'f':
									POST('\f'); break;
								case 'n':
									POST('\n'); break;
								case 't':
									POST('\t'); break;
								case 'v':
									POST('\v'); break;
								case 'x':
								{
									char hi = *++p;
									char lo = *++p;
									if (hexdigit(hi) && hexdigit(lo)) {
										POST(lo + hi * 0x10);
									} else {
										ERROR("escape code \\x must be followed by two numerals");
									}
								} break;
								default:
									ERROR("unrecognised escape code");
								}
							} else {
								POST(*p);
							}
						POST(0x00);
						c++;
						goto END_STR_LOOP;
					}
					break;
				}
			}
		END_STR_LOOP:
			break;
		}
		case '/':
		{
			char next = c[1];
			if (next == '/') {
				while (*++c != '\n'); c++;
			} else if (next == '*') {
				while (*++c != '*' && *++c != '/'); c++;
			} else {
				// TODO handle other case
			}
			break;
		}
		case '\\':
		case ')':
		case ']':
		case '}':
			ERROR("unexpected char in input stream")
			break;
		default:
			if (!token_start) {
				token_start = c;
			}
			c++;
		}
	}
	FAILURE_LABEL:
#undef POST
	builder->len = bytecode.size();
	builder->bytecode = new char[builder->len];
#pragma warning(disable: 4996)
	std::copy(bytecode.begin(), bytecode.end(), builder->bytecode);
	return builder;
}