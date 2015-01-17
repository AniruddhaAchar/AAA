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

			std::string convert() { 

				/* This function checks the tag passed and converts the text to HTML */

				std::string result;

				switch(tag) {
					case 'b':	result="<strong>"+text+"</strong>";
								break;
					case 'i':	result="<em>"+text+"</em>";
								break;
					case 's':	result="<strike>"+text+"</strike>";
								break;
					case 'c':	result="<pre>"+text+"</pre>";
								break;
					case '1':	result="<h1>"+text+"</h1>";
								break;
					case '2':	result="<h2>"+text+"</h2>";
								break;
					case '3':	result="<h3>"+text+"</h3>";
								break;
					case '4':	result="<h4>"+text+"</h4";
								break;
					case '5':	result="<h5>"+text+"</h5>";
								break;
					default:	result="<p>"+text+"</p>";
								break;
				}

				return result;
			}
};

int main () {
	/* For testing purposes. Delete when implementing */
	converter a('b', "WOW. THIS WORKS and is BOLD");
	std::string c = a.convert();
	cout<<c;
}