#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>
using namespace std;

bool isAdelim(const char value, const string& delims)
{
        int idx = 0;
        bool ret = false;
        while(idx < delims.length())
        {
                if(value == delims.at(idx))
                {
                        ret = true;
                        break;
                }
                else
                {
                        ++idx;
                }
        }
        return ret;
}

string skim(int startPoint, int endPoint, const string& mainString)
{
        string newStr;
        newStr.clear();
        newStr.append(mainString,startPoint,endPoint);
        return newStr;
}

string tokenize(const string mainstring, const string& delims)
{
        vector<string> tokenizedVector;
        tokenizedVector.clear();
        if(!mainstring.length())
        {
                return "";
        }
        if(!delims.length())
        {
                tokenizedVector.push_back(mainstring);
                return mainstring;
        }
        int idx = 0;
        int startPoint = 0;
        int endPoint = -1;
                int len = 0;
        while(idx < mainstring.length())
        {
                if(isAdelim(mainstring.at(idx),delims))
                {
                        string subString = skim(startPoint, len-startPoint,mainstring);
                        tokenizedVector.push_back(subString);
                        subString.clear();
                        startPoint = idx+1;
                }
                if(idx == mainstring.length()-1)
                {
                        string subString = skim(startPoint, idx-1,mainstring);
                        tokenizedVector.push_back(subString);
                        subString.clear();
                }
                ++idx;
                len=idx;
        }
        return tokenizedVector[tokenizedVector.size()-1];
}

int main()
{
	ifstream infile;
	infile.open("C:\\MyStudy\\MyCpp\\BDFReader\\Input.txt",ios_base::app);
	if(!infile.is_open())
	{
		cout<<"\n"<<"File open failed.."<<"\n";
		exit(-1);
	}
	string fileString;
	string retString;
	vector<string> fileVector;
	while(getline(infile,fileString))
	{
		if(strstr(fileString.c_str(),".c") || strstr(fileString.c_str(),".cc"))
		{
			retString.clear();
			retString = tokenize(fileString, "=");
			fileVector.push_back(retString);			
		}
	}
	ofstream outFile;
	outFile.open("C:\\MyStudy\\MyCpp\\BDFReader\\Output.txt",ios_base::out);
    for(auto iter:fileVector)
    {
    	outFile<<iter<<"\n";
    	outFile.flush();
	}
    cout<<"\n";
}



                                                                                                                                                                        
