#include <iostream>
/* String function for handling and returning strings */
#include <string>
using namespace std;

/* This file is to read the tags and string and then convert to HTML */

class converter {
	char tag;
	std::string text; /* String objects - Easier for manipulation*/

	public: 
			converter() {
				/* Haven't yet decided what to put here */
			}
			
			converter(char tags,std::string texts ) {
				tag=tags;   
				text=texts; 
			}

			converter(std::string texts ) {
				/* In case there are no need of tags. P tags are going to be used.*/
				text=texts; 
			}

			std::string variable_detect() {
				/* Used to detect variable presense and then remove them */
				int l=text.length();
				int i=l-1;
				if(text.at(l-1)=='>') {
					while(text.at(i)!='<'&&i!=0) {
						i--;
					}
					if(i==0) {
						/* No variables present. */
						return NULL;
					}
					else {
						/* Returns the variable */
						std::string variable=text.substr(i+1,l-i-2);
						text=text.substr(0,i); /*Removes the variable from texts*/
						return variable; 
					}

				}
			}

			std::string convert(std::string name, std::string section) {  //Operator overloading
				/* This method is invoked whenever a section is encountered */
				std::string convsec="<div id=\""+name+"\">"+section+"</div>";
				return convsec;
			}

			std::string convert() { 

				/* This function checks the tag passed and converts the text to HTML */

				std::string result="";
				std::string vari=variable_detect();
				if(!vari.empty()) {
					result="<span id=\""+vari+"\">";
				}
				
				switch(tag) {
					case 'b':	result+="<strong>"+text+"</strong>";
								break;
					case 'i':	result+="<em>"+text+"</em>";
								break;
					case 's':	result+="<strike>"+text+"</strike>";
								break;
					case 'c':	result+="<pre>"+text+"</pre>";
								break;
					case '1':	result+="<h1>"+text+"</h1>";
								break;
					case '2':	result+="<h2>"+text+"</h2>";
								break;
					case '3':	result+="<h3>"+text+"</h3>";
								break;
					case '4':	result+="<h4>"+text+"</h4";
								break;
					case '5':	result+="<h5>"+text+"</h5>";
								break;
					default:	result+="<p>"+text+"</p>"; /* If all else fails, it is a paragraph */
								break;
				}

				if(!vari.empty()) 
					result+="</span>";
				
				return result;
			}
};

int main () {
	/* For testing purposes. Delete when implementing */
	converter a('b', "WOW. THIS WORKS and is BOLD <df>");
	std::string c = a.convert();
	cout<<c;
}