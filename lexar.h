#idndef LEXAR_H
#define LEXAR_H

#include<iostream>
#include<cctype>


using namespace std;

struct LexToc{
	string lexeme;
	string token;
};

string keywords[] = {"program", "begin", "end", "function", "read", "write", "if", "elsif", "else", "while", "do", "until", "return"};
//array of keywords to differentiate and compare for checking

LexToc lexar(ifstream file){
	string lexStr = "";
	char ch;
	
	LexToc current;
	
	if(file >> ch){ //gets the first character from the buffer
		lexStr += ch;
		if(ch.isAlpha()){ //checks the char to see if it is an identifier, keyword, or type
			ch = file.peek(); //peeks to the next char and takes it
			
			while(ch.isAlpha() || isDigit(ch) || ch == '_'){ //goes through the whole string until it hits white space
				ch = file.get();
				lexStr += ch;
				ch = file.peek();
			}
			
			current.lexeme = lexStr; //assigns the string as the lexeme
			
			//checks for keyword, type, or identifier
			if(lexeme == "int" || lexeme == "real" || lexeme == "string"){ // check for type
				current.token = "type";
			}
			//check for keyword
			for(int i = 0; i < keywords.size(); i++){ //for loop to go through the array of keywords
				elseif(lexeme == keywords[i]){ //compares
					current.token = "keyword"; //if it is, token is keyword and breaks from the loop
					break;
				}
			}
			//if not keyword or type, assigns it as identifier
			else{
				current.token = "identifier";
			}
			
			//returns the struct
			return current;
		}
	
	
	
	}
}



#endif
