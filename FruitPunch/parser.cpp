#include "parser.h"
#include <vector>
#include <iostream>
#include <cstdint>
#include "symbols.h"


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

bool is_ident_head(char q) {
	return (q >= 'a' && q <= 'z') || (q >= 'A' && q <= 'Z');
}

bool is_ident_tail(char q) {
	return (q >= 'a' && q <= 'z') || (q >= 'A' && q <= 'Z') || (q >= '0' && q <= '9');
}

Closure* parseClosure(char* start, char* end) {
	Closure* builder = new Closure();
	std::vector<char> bytecode;
#define ERROR(x) std::cout << "[synerr] " << x << std::endl; failure = true; goto FAILURE_LABEL;
#define POST(x) bytecode.push_back(x);
#define CASE_WS case '\n': case ' ': case '\t': case '\0'
#define CASE_NUMERAL case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9'
#define CASE_LOW_ALPHA case 'a': case 'b': case 'c': case 'd': case 'e': case 'f': case 'g': case 'h': case 'i': case 'j': case 'k': case 'l': case 'm': case 'n': case 'o': case 'p': case 'q': case 'r': case 's': case 't': case 'u': case 'v': case 'w': case 'x': case 'y': case 'z'
#define CASE_HIGH_ALPHA case 'A': case 'B': case 'C': case 'D': case 'E': case 'F': case 'G': case 'H': case 'I': case 'J': case 'K': case 'L': case 'M': case 'N': case 'O': case 'P': case 'Q': case 'R': case 'S': case 'T': case 'U': case 'V': case 'W': case 'X': case 'Y': case 'Z'
#define CASE_ALPHA CASE_LOW_ALPHA: CASE_HIGH_ALPHA
#define POST_MULTI(value, n_bytes) unsigned char* p = reinterpret_cast<unsigned char*>(&value); for (int i = 0; i < n_bytes; i++) {POST(p[i])};
#define POST_SYM(opcode) token_start = c; while (is_ident_tail(*++c)); char q = *c; *c = 0; symbol_t sym = symbol(token_start); POST(opcode); POST_MULTI(sym, sizeof(symbol_t)); *c = q;

	char* c = start;
	char* token_start = nullptr;
	bool failure = false;
	while (c <= end) {
		switch (*c) {
		CASE_WS:
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
					if (*c == quote && *(c - 1) != '\\') {
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
				case '\0':
					ERROR("end of string expected")
				}
			}
		END_STR_LOOP:
			break;
		}
		case '/':
		{
			char next = c[1];
			if (next == '/') {
				while (*++c != '\n' && *c != '\0'); c++;
			} else if (next == '*') {
				while (*++c != '*' || *++c != '/'); c++;
			} else {
				// TODO handle other case
			}
			break;
		}
		CASE_NUMERAL:
		{
			char q;
			bool decimal = false;
			token_start = c;
			while (true) {
				q = *c;
				switch (q) {
				CASE_NUMERAL: break;
				case '.':
					if (decimal) {
						ERROR("double decimal point in number")
					} else {
						decimal = true;
					}
					break;
				CASE_WS:
					if (decimal)
						goto FLOAT_CASE;
					else {
						*c = 0; // set end of number to null
						POST(0x02); // INT32 opcode
						uint32_t v = atol(token_start);
						POST_MULTI(v, 4);
						*c = q; // restore end of number
						goto END_NUM_LOOP;
					}
				case 'l':
				{
					*c = 0; // set end of number to null
					// TODO make this actually use INT64
					POST(0x02); // INT32 opcode
					uint64_t v = atol(token_start);
					POST_MULTI(v, 4);
					*c = q; // restore end of number
					goto END_NUM_LOOP;
				}
			FLOAT_CASE:
				case 'f':
				{
					*c = 0; // set end of number to null
					POST(0x04); // FLOAT opcode
					float v = atof(token_start);
					POST_MULTI(v, 4);
					*c = q; // restore end of number
					goto END_NUM_LOOP;
				} break;
				case 'd':
				{
					*c = 0; // set end of number to null
					POST(0x05); // DOUBLE opcode
					double v = atof(token_start);
					POST_MULTI(v, 8);
					*c = q; // restore end of number
					goto END_NUM_LOOP;
				} break;
				default:
					ERROR("unexpected char in number");
				}
				c++;
			}
		END_NUM_LOOP:
			break;
		}
		case '\\':
		case ')':
		case ']':
		case '}':
			ERROR("unexpected char in input stream")
			break;
		case '$':
			if (is_ident_head(*++c)) {
				POST_SYM(0x11)
			} else {
				ERROR("expected identifier following $");
			}
			break;
		case '>':
		{
			char q = *++c;
			if (q == '>') {
				if (is_ident_head(*++c)) {
					POST_SYM(0x13);
				} else {
					ERROR("expected identifier following >>");
				}
			} else if (is_ident_head(q)) {
				POST_SYM(0x12)
			} else {
				ERROR("expected identifier following >");
			}
			break;
		}
		default:
			if (is_ident_head(*c)) {
				POST_SYM(0x10);
			} else {
				if (!token_start) {
					token_start = c;
				}
				c++;
			}
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