#include<iomanip>
#include<ios>
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<vector>
#include<algorithm>


using namespace std;
/*
function to check for valid flag name.(-LL,-IN)
*/
bool checkArg(string &flag)
{
    string st1="-LL";
   	string st2="-IN";   		
    if((flag.find(st1)==string::npos)&&(flag.find(st2)==string::npos))
    {
       return false;
    }
    return true;    
}
/*
function to check for equal sign in flag.
*/
bool checkEqual(string &flag)
{
    char equal='=';
    if((flag.find(equal)==string::npos))
    {
        return false;
    }
    return true;  
}
/*
function to check if flag have digit or not.
*/
bool checkDigit(string &s)
{
    string msg= s.substr(4,s.length()-1);
    for(char i: msg)
    {
        if(isdigit(i)==0)
        {
            return false;
        }
    	if(isdigit(i) != 0 && stoi(msg)<=0)
        {
            return false;
        }
    }
	return true;
}
/*
function to get line length.
*/
int getLinelength(vector<string> &LLvec)
{
    int length=0;
    if(LLvec.empty())
    {
        length = 40;
    }
    else if(!(LLvec.empty()))
    {
        for(int i=0;i<LLvec.size();i++)
        {
            string temp=LLvec.back();
            length=stoi(temp.substr(4,temp.length()-1));
        }
    }
    return length;
    
}
/*
function to get indent.
*/
int getIndent(vector<string> &INvec)
{
    int indent=0;
    if(INvec.empty())
    {
        indent = 8;
    }
    else if(!(INvec.empty()))
    {
        for(int i=0;i<INvec.size();i++)
        {
            string temp=INvec.back();
            indent=stoi(temp.substr(4,temp.length()-1));
        }
    }
    return indent;
    
}

/*
function to formate line and indent.
*/
void formate(vector<string> &paragraph,int &indent,int &linelength)
{
    string word,line;
    string holdstr;
   //looping and output all paragraph except last paragraph.
    for(int j=0;j<paragraph.size()-1;j++)
    {
        holdstr = paragraph.at(j);
        for(int i=0;i<indent;i++)
    	{
        	cout<<" ";
    	}
        stringstream ss(holdstr);
   
    	bool resultOut=false;
    	int size=indent;
    	while(ss>>word)
    	{
       
        if(!resultOut)
        {
            cout<<word;
            size += word.length();
            resultOut= true;
        }
    	else
        {
            if((size + word.length()+1) <= linelength)
    		{
            	cout<<" "<<word;
             	size += word.length()+1;
   			}
            else if((size + word.length() +1) >= linelength)
            {              
                cout<<"\n"<<word;
                size = word.length();
            } 
        }       
    }
       cout<<endl<<endl;
        
    } 
    
    //looping for last paragraph.
    for(int i=0;i<indent;i++)
   	{
      cout<<" ";
     
    }
        
    string lastparagraph = paragraph.back();
    string last;
    stringstream last_p(lastparagraph);
    bool result=false;
    int newsize=indent;
    while(last_p>>last)
    {
        if(!result)
        {
            cout<<last;
            newsize += last.length();
            result= true;
        }
    	else
        {
            if((newsize + last.length()+1) <= linelength)
    		{
            	cout<<" "<<last;
             	newsize += last.length()+1;
   			}
            else if((newsize + last.length() +1) >= linelength)
            {
               
                cout<<"\n"<<last;
                newsize = last.length();
            }
            
        }     
    }
       cout<<endl;  
}
    
/*
Driver functon main()
*/
int main(int argc, char *argv[])
{
    vector<string> file;
    vector<string> flag;
    vector<string> LL;
    vector<string> IN;
    vector<string>finalparavec;
    ifstream fin;
    istream *in=&cin;
   
     
    
    //put files together.
    for(int i=1; i<argc; i++)
    {
        string name(argv[i]);
        
        if(name.substr(0,1) != "-")
        {
            file.push_back(name);
        }
        
    }
    //put flags together.
    for(int i=1; i<argc; i++)
    {
        string argument(argv[i]);
        if(argument.substr(0,1) == "-")
        {
            flag.push_back(argument);
        }
           
    }
    //seaprate LL and IN.
    for(int i=0; i<flag.size();i++)
    {
        string argument = flag.at(i);
        if(argument.substr(0,3)=="-LL")
        {
            LL.push_back(argument);
        }
        if(argument.substr(0,3)=="-IN")
        {
            IN.push_back(argument);
        }
    }
    if(file.size() > 1)
    {
        cout<<"TOO MANY FILENAMES"<<endl;
       
        return -1;        
    }
    
   
   if(argc>=1)
   {
        string file_op;
       
        for(int i=0;i<file.size();i++)
        {
            file_op =file.at(i);            
        	fin.open(file_op);
            in=&fin;
        
           
        
        if((!fin))
        {
            cout<<"UNABLE TO OPEN FILE "<< file_op<<endl;
            return -1;
        } 
       		
        }
         
        
    
   	}
   //Part 1: check for Errors!
    for(int i=0; i < flag.size(); i ++)
        {
          string arg=flag.at(i);
           
           if(!checkEqual(arg))
           	{
               cout<<"MISSING = SIGN "<<arg<<endl;
      		   return -1;
           	}
            if(!checkArg(arg))
    		{
              cout<<"UNRECOGNIZED FLAG "<<arg<<endl; 
              return -1;
    		}
            if(!(checkDigit(arg)))
            {
                cout<<"VALUE NOT INTEGER > 0 "<<arg<<endl;
                return -1;
            } 
        }
     //Part 2: read from file, and generate output as desire.
    	int linelength=getLinelength(LL);
   		int indent =getIndent(IN);
    	
     	
    		string line;
            string result;
    		vector<string> paravec;
    		vector<string> emptyvec;
    
    	getline(*in,line);
    	if(line.empty())
      	{
          cout<<endl;
            return -1;
        }
    	else
        {
            //read first paragraph:
          if(line.empty() && !result.empty())
       		{
        	   paravec.push_back(result);
           	   result="";
        	}
       		 if(!line.empty())
    		{
            result += (line+" ");             
        	}
        	cin.clear();
    	 //read from second to last paragraph:
        while(*in)
 	   	{
       	 getline(*in,line);
        
       	if(line.empty() && !result.empty())
       	{
           paravec.push_back(result);
            result="";
        }
        if(line.empty() && result.empty())
        {  
            continue;
        }
        if(!line.empty())
    	{
            result += (line+" ");             
        }
        cin.clear();
    	}
        if(!result.empty())
        {
          paravec.push_back(result);
           result="";
		}
        }        
    	formate(paravec,indent,linelength);

  return 0;
}
