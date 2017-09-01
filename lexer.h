#ifndef LEXER_H
#define LEXER_H

#include<iostream>
#include<fstream>
#include<cctype>
#include<vector>

using namespace std;

struct LexTok {
	string lexeme;
	string token;
};


LexTok lexer(ifstream &file) {//takes file reference



	string keywords[] = { "program", "begin", "end", "function", "read", "write", "if", "elsif", "else", "while", "do", "until", "return" };
	//string type[] = { "int", "real", "string" };

	vector<string> keyword(keywords, keywords + sizeof(keywords) / sizeof(string));
	//array of keywords to differentiate and compare for checking

	string lexStr = "";
	char ch;

	LexTok current;

	if (file >> ch) { //gets the first character from the buffer
		lexStr += ch;
		if (isalpha(ch)) { //checks the char to see if it is an identifier, keyword, or type
			ch = file.peek(); //peeks to the next char and takes it

			while (isalpha(ch) || isdigit(ch) || ch == '_') { //goes through the whole string until it hits white space
				ch = file.get();
				lexStr += ch;
				ch = file.peek();
			}

			current.lexeme = lexStr; //assigns the string as the lexeme

			//checks for keyword, type, or identifier
			if (current.lexeme.compare("int") == 0 || current.lexeme.compare("real") == 0 || current.lexeme.compare("string") == 0) { // check for type
				current.token = "Type";
			}

			else {//check for keyword
				for (int i = 0; i < keyword.size(); i++) { //for loop to go through the array of keywords
					if (current.lexeme.compare(keyword[i]) == 0) { //compares
						current.token = "Keyword"; //if it is, token is keyword and breaks from the loop
						break;
					}
					//if not keyword or type, assigns it as identifier
					else {
						current.token = "Identifier";
					}
				}
			}
			//returns the struct
			//return current;
		}

		else if (isdigit(ch)) {//check for intconst, realconst, or intconst.
			ch = file.peek(); //peeks at the next char
			while (isdigit(ch)) {
				ch = file.get();
				lexStr += ch;
				ch = file.peek();
			}
			current.lexeme = lexStr;
			current.token = "IntConst"; //assumes first instance as an intconst

			if (ch == '.') { //checks for real const

				ch = file.get();
				ch = file.peek();

				if (isdigit(ch)) { //checks if the character after the decimal is a digit, thus checking if it is a realConst
					lexStr += '.';
					ch = file.get();
					lexStr += ch;
					ch = file.peek();

					while (isdigit(ch)) {//recieves all the digits after the period
						ch = file.get();
						lexStr += ch;
						ch = file.peek();
					}
					current.lexeme = lexStr;
					current.token = "RealConst"; //sets the current lexeme as realConst

				}

				else {					//if not a realConst, returns the period and sets lexeme as IntConst
					file.putback(ch);
					current.lexeme = lexStr;
					current.token = "IntConst";
				}
			}
		}

		else if (ch == '"') { //checking for strConstants or eof by first finding the opening quote
			ch = file.peek(); //peeks ahead
			while (ch != '"' && !file.eof()) { //while the next char is not the closing quotes and is not at the eof, get all the characters for the string constant
				ch = file.get();
				lexStr += ch;
				ch = file.peek();
			}

			//CHECK IF THIS IS THE RIGHT POSITION for checking eof
			if (!file.eof()) { //assigns the end quote and lexeme as the strConstant
				ch = file.get();
				lexStr += ch;
				current.lexeme = lexStr;
				current.token = "StringConst";
			}
			else { //if eof, then return lexeme token as eof
				current.lexeme = "";
				current.token = "eof";
			}

			//return current;
		}

		//fix this code to make sure the assignments get after peek to move buffer forward! (fixed?)
		else if (ch == '=' || ch == '>' || ch == '<') { //check for relational operators
			if (ch == '=') { //check for equals
				current.lexeme = ch;
				current.token = "RelOp";
			}
			else if (ch == '>') { //check for greater than
				ch = file.peek();
				if (ch == '=') { //to check for greater than equal to
					//lexStr += ch;
					ch = file.get();
					lexStr += ch;
					current.lexeme = lexStr;
					current.token = "RelOp";
				}
				else { //default
					//lexStr += ch;
					current.lexeme = lexStr;
					current.token = "RelOp";
				}
			}
			else if (ch == '<') {

				ch = file.peek();
				if (ch == '=') { //to check for greater than equal to
					//lexStr += ch;
					ch = file.get();
					lexStr += ch;
					current.lexeme = lexStr;
					current.token = "RelOp";
				}
				else if (ch == '>') {
					//lexStr += ch;
					ch = file.get();
					lexStr += ch;
					current.lexeme = lexStr;
					current.token = "RelOp";
				}
				else { //default
					//lexStr += ch;
					current.lexeme = lexStr;
					current.token = "RelOp";
				}

			}
		}
		//check for normal operators
		else if (ch == '.' || ch == ',' || ch == ';' || ch == ':' || ch == '(' || ch == ')' || ch == '+' || ch == '-' || ch == '*' || ch == '/') { //check for operator list
			//lexStr += ch;
			ch = file.peek();
			if (lexStr.compare(":")==0 && ch == '=') {
				ch = file.get();
				lexStr += ch;
			}

			current.lexeme = lexStr;
			current.token = "Operator";
		}
		//if not anything above, then it is an error
		else {
			current.lexeme = ch;
			current.token = "error";
		}
		//returns the current lexeme token back to the program
		return current;
	}
	//covers eof
	else {
		current.lexeme = "";
		current.token = "eof";

		return current;
	}
}
#endif

