#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#define flag "==========\n\n==========\n\nDICT\n\n"

using namespace std;

bool isNum(char c);

int main()
{
    vector<string>rawDict;

    string templine;

    ifstream inDict;
    ofstream outDict;

    inDict.open("dictionary.txt");

    if (inDict.is_open())
    {
        while (getline(inDict, templine))
        {
            rawDict.push_back(templine);
        }

        inDict.close();
    }

    cout << "Vector contains " << rawDict.size() << " elements.\n" << flag;

    outDict.open("english.txt");

    for (unsigned int i = 0; i < rawDict.size(); i++)
    {
        bool detected = false;
        string temp2;

        temp2 = rawDict[i];

        for (unsigned int j = 0; j < temp2.length(); j++)
        {
            if (islower(temp2[j]))
            {
                detected = false;
                break;
            }
            else if (isNum(temp2[j]))
            {
                detected = false;
                break;
            }
            else
            {
                detected = true;
            }
        }

        if(detected)
        {
            outDict << flag << rawDict[i] << endl;
        }
        else
        {
            outDict << rawDict[i] << endl;
        }
    }
    return 0;
}

bool isNum(char c)
{
    switch (c)
    {
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
    case '0':
        return true;
    default:
        return false;
    }
}
