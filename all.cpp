#include <iostream>
#include <string>
#include <fstream>
#include <iterator>
#include <windows.h>
#include <sstream>

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
                /* Below for loop is used to ignore spaces at the end. */
                for(int j=i;j>=0;j--) {
                    if(text.at(j)==' ')
                        continue;
                    else {
                        i=j; //Position where space ends and letter start.
                        break;
                    }
                }

                if(text.at(i)=='>') {
                    int j=i;
                    while(text.at(j)!='<'&&j!=0) {
                        j--;
                    }
                    if(j==0) {
                        /* No variables present. */
                        return NULL;
                    }
                    else {
                        /* Returns the variable */
                        std::string variable=text.substr(j+1,i-j-1);
                        text=text.substr(0,j); /*Removes the variable from texts*/
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
                    case 'b':   result+="<strong>"+text+"</strong>";
                                break;
                    case 'i':   result+="<em>"+text+"</em>";
                                break;
                    case 's':   result+="<strike>"+text+"</strike>";
                                break;
                    case 'c':   result+="<pre>"+text+"</pre>";
                                break;
                    case 'm':   result+="<img src=\""+text+"\">";
                                break;
                    case '1':   result+="<h1>"+text+"</h1>";
                                break;
                    case '2':   result+="<h2>"+text+"</h2>";
                                break;
                    case '3':   result+="<h3>"+text+"</h3>";
                                break;
                    case '4':   result+="<h4>"+text+"</h4";
                                break;
                    case '5':   result+="<h5>"+text+"</h5>";
                                break;
                    default:    result+="<p>"+text+"</p>"; /* If all else fails, it is a paragraph */
                                break;
                }

                if(!vari.empty())
                    result+="</span>";

                return result;
            }
            std::string askpolitely(char a, std::string b) { //set values for tag and string
                tag=a;
                text=b;
                std::string ans = this->convert();
                return ans;
            }
};


class findall                                             //This is the searching class
{
public:
    string end_s(char s[],int &i,char tag)                //takes in current position of i, character array and the ending tag
{
    string temp="";
    i++;
    while(s[i]!=tag)                                      //searches till end of the code
    {
        temp+=start_s(s,i);                               //checking for nested tags. If non found the current character is appended with the temp string
    }
    return temp;
}
    virtual string start_s(char s[],int &i)=0;            //pure virtual function as the tags are unknown yet

};

class Tags :public findall                                //The tags class inherits the find all class.
{
    bool p,b,h,i,co,sc;                                   //flags to find where the check starting and ending of tags

public:
    Tags()
    {
        p=false;b=false;i=false;h=false;co=false;sc=false;//initialize all tags to false initially using the constructor

    }
    string start_s(char s[],int &i)
    {
        converter c;                                      //object of converter class
        string st;                                        //this string is created in every cycle of the search
        char ch=s[i];
        switch (ch)
        {
            case '\n':getTagcontent(i,'\n',p,s,st);       //paragraph is isolated from the tags
                        st=c.askpolitely('\n',st);            //  html paragraph tags are added to the

            break;
            case  '*':getTagcontent(i,'*',b,s,st);        //bold is isolated from the tags
                        st=c.askpolitely('*',st);             //html strong tags are added to the

            break;
            case  '`':getTagcontent(i,'`',co,s,st);       //code is isolated from the tags
                        st=c.askpolitely('`',st);             //html code tags are added to the
            break;
            case  '~':getTagcontent(i,'~',sc,s,st);       //italics is isolated from the tags
                        st=c.askpolitely('~',st);             //html italics tags are added to the
            break;
            case '#': getTagcontent(i,s,st);              //The getTagcontent method is overloaded for head tags and the css part
            break;
            default:
                st+=s[i];
                i++;

        }
        return st;                                        //returns the converted string back


    }
    void getTagcontent(int &i,char endtg,bool &flag,char s[],string &st)
    {
        if(flag==false)
            {
                st+=end_s(s,i,endtg);                     //searches the
                i++;
                flag=true;
            }
            else
            {
                i++;
                st+=s[i];
                flag=false;
            }
    }
   void getTagcontent(int &i, char s[],string &st)
    {
        i++;
        converter c;
        char ch=s[i];
        switch(ch){

        case '1': st=end_s(s,i,'\n');
                    st=c.askpolitely(ch,st);
                                                          //pass the resulting string to h1 conversion
            break;
        case '2': st=end_s(s,i,'\n');
                    st=c.askpolitely(ch,st);
                                                          //pass the resulting string to h2 conversion
            break;
        case '3': st=end_s(s,i,'\n');
                                                          //pass the resulting string to h3 conversion
            break;
        case '4': st=end_s(s,i,'\n');
                                                          //pass the resulting string to h4 conversion
            break;
        case '5': st=end_s(s,i,'\n');
                                                          //pass the resulting string to h5 conversion
            break;
        case '6': st=end_s(s,i,'\n');
                                                          //pass the resulting string to h6 conversion
            break;

                                                          //for Parsing CSS codes
        }
    }
    string getSection(char s[], int &i)
    {
        string var,sections;

        if(s[i]=='#'&&s[i++]=='{')
            {
                i+=2;
                while(s[i]!='}')
                {
                    if(s[i]='^')/*^ is used for variables*/
                        while(s[++i]!='^')
                            var+=s[i];
                    else
                        sections+=s[i];
                }
            }
            //pass sections and variable to abhilash's function.
    }


};

//Aditya's
void replaceAll( string &s, const string &search, const string &replace )      //Replaces SubString
{
    for( size_t pos = 0; ; pos += replace.length() ) {
        // Locate the substring to replace
        pos = s.find( search, pos );
        if( pos == string::npos ) break;
        // Replace by erasing and inserting
        s.erase( pos, search.length() );
        s.insert( pos, replace );
    }
}
string getCurrentDirectory()
{
    unsigned long maxDir = 260;
    char currentDir[maxDir];
    GetCurrentDirectory(maxDir, currentDir);
    return string(currentDir);
}
class Equip_Necessary
{
    string str1,str2,str3,dir,str;
    void CreateFolder(char *path)                               //Directory Creator Function
    {
        if(!CreateDirectory(path,NULL))
        {
            cout<<"Directory Creation Failed";
            exit(0);
        }
        else
            cout<<"Directory Creation Successful\n";
    }
    public:
    friend void replaceAll();
    friend string getCurrentDirectory();
    void create(string path)                       //Creates all the constant files necessary for
    {
        str=path;                                 //website in the path directory passed as parameter
        char *ch=&str[0];
        CreateFolder(ch);
        str+="\\\\";

        str1=str+"css";
        char *c1=&str1[0];
        CreateFolder(c1);

        str1+="\\\\";
        string Input1="C:\\website\\bootstrap.css";
        string CopiedFile1="bootstrap.css";
        string OutputFolder1=str1;
        CopyFile(Input1.c_str(),string(OutputFolder1+CopiedFile1).c_str(), TRUE);

        dir=getCurrentDirectory();
        replaceAll(dir,"\\","\\\\");
        dir+="\\\\";
        string Input4=(dir+"\\style.css");
        string CopiedFile4="style.css";
        CopyFile(Input4.c_str(),string(OutputFolder1+CopiedFile4).c_str(), TRUE);

        str2=str+"js";
        char *c2=&str2[0];
        CreateFolder(c2);

        str2+="\\\\";
        string Input2="C:\\website\\bootstrap.js";
        string CopiedFile2="bootstrap.js";
        string OutputFolder2=str2;
        CopyFile(Input2.c_str(),string(OutputFolder2+CopiedFile2).c_str(), TRUE);

        str2+="\\\\";                                         //Copying File, Jquery.js to JS Directory
        string Input3 = "C:\\website\\jquery-1.11.2.js";
        string CopiedFile3 = "jquery-1.11.2.js";
        CopyFile(Input3.c_str(), string(OutputFolder2+CopiedFile3).c_str(), TRUE);

        str3=str+"\\\\media";
        char *c3=&str3[0];
        CreateFolder(c3);
    }
};
/* This class is used to provide HTML header, footer and style to the output files. */

class provide_htmlcss {

    public:
    friend string getCurrentDirectory();
        std::string allstyle;                   /* used for storing all the css */

        provide_htmlcss() {
            allstyle="";
        }

        std::string header(std::string title)
        {
            std::string head="<!DOCTYPE html>\n<html lang=\"en\">\n<head>\n<meta charset=\"utf-8\">\n<meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">\n<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n<title>"+title+"</title>\n<!-- Bootstrap -->\n<link href=\"css/bootstrap.css\" rel=\"stylesheet\">\n<link href=\"css/style.css\" rel=\"stylesheet\">\n<script src=\"js/jquery-1.11.2.js\"></script>\n<script src=\"js/bootstrap.js\"></script>\n<!-- HTML5 shim and Respond.js for IE8 support of HTML5 elements and media queries -->\n<!-- WARNING: Respond.js doesn't work if you view the page via file:// -->\n<!--[if lt IE 9]>\n<script src=\"js/html5shiv.js\"></script>\n<script src=\"js/respond.js\"></script>\n<![endif]-->\n</head>\n<body>\n";
            return head;
        }

        std::string footer()
        {
            std::string footer = "</body>\n<credits> This webpage is generated by the ALANG Markdown to HTML converter. Not for commerical use.</credits>";
            return footer;
        }

        void addstyle(std::string newstyle)
        {
            allstyle=allstyle+"\n";
        }
        void File_append(string s, ofstream&);

        /*~provide_htmlcss()
        {   /* Destructor */
            /* Modify this */
            //Aditya.addcss(allstyle);
        //}

};
void provide_htmlcss::File_append(string str, ofstream &file2)          //This function appends
{                                                                       //the string str to file
    file2<<str<<endl;
}

void move_file(string dir, ofstream &file)
{
    dir+="\\\\";
    string direc;
    direc=getCurrentDirectory();
    replaceAll(direc,"\\","\\\\");
    direc+="\\\\";
    string Input4=direc+"\\\\Index.html";
    string CopiedFile4="Index.html";
    string OutputFolder=dir;
    CopyFile(Input4.c_str(),string(OutputFolder+CopiedFile4).c_str(), TRUE);
}

std::string getinputandsend(string path) {
    string text;
    ifstream fin("input.alg", ios::in);
    ofstream fout("userfile.txt", ios::out);
    while(getline(fin,text))
    {
        if(text.empty())
        fout<<endl;
        else
        {
            replaceAll(text,"\'","\\\'");
            replaceAll(text,"\'","\\\"");
            fout<<text<<endl;
        }
    }
    fin.close();
    fout.close();
    ifstream file3("userfile.txt", ios::in);                 //This Edited File is being sent as String
    stringstream buffer;
    buffer << file3.rdbuf();
    text=buffer.str();
    file3.close();
    return text;
}


/* ACTUAL INT MAIN */

int main() {

    string dir,title;
    Equip_Necessary b;
    cout<<" \n *** ALANG CONVERTER ***\n";
    cout<<"\n\n\nEnter Alang file path: ";
    string path;
    cin>>path;
    cout<<"\nEnter Website Title: ";
    cin>>title;
    cout<<"\nWhere do you Want to Create the Website Directory? (Eg: C:\\Test) :  ";
    cin>>dir;
    b.create(dir);
    ofstream file;
    file.open("Index.html", ios:: out);
    string str,str1,str2,str3;

    provide_htmlcss a;
    str1=a.header(title);
    str2=a.footer();

    /* Aniruddha's content goes here */
    string text=getinputandsend(path);
    /*char *c=new char[text.size()+1];
    memcpy(c,text.c_str(),text.size());*/
    char *ch=&text[0] ;

    //char st[]="#1Head one\nThis is a paragraph with *bold*`code` and ~italics~\n ";
    string s="";
    Tags t;
    int i=0;
    while(i<sizeof(text)){
            s+=t.start_s(ch,i);
    }

    str=str1+s+str2;                                     //+str3 - Body Contents
    file<<str;
    //file<<Body Contents of Index.html from Aniruddha//
    /*The Following code relates to the css style append fn alone*/
    ofstream file1;
    string style="/* Style.css Generated by ALANG */";      //style string passes all the code
    file1.open("style.css", ios::out);                     //relatd to style.css
    a.File_append(style,file1);
    file1.close();
    cout<<dir;
    move_file(dir, file);
    file.close();


}
