#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

const string dFlag = "DICT";
const string spacer = "==========";

size_t posFlag(string in);

int main()
{
    vector<string> lines;
    ifstream inEnglish;
    ofstream outEnglish;
    string templine;

    inEnglish.open("english.txt");

    if (inEnglish.good())
    {
        while (getline(inEnglish, templine))
        {
            lines.push_back(templine);
        }
    }

    else
    {
        cerr << "FILE NOT FOUND";
        return -1;
    }

    inEnglish.close();

    for(unsigned int i = 0; i < lines.size(); i++)
    {
        if ((lines[i] == dFlag) || (lines[i] == spacer))
        {
            continue;
        }

        else
        {
            size_t pFlag;

            pFlag = posFlag(lines[i]);

            if (pFlag == string::npos)
            {
                continue;
            }

            else
            {
                string tempStr = lines[i];

                tempStr.assign(lines[i].begin()+pFlag, lines[i].end());

                lines[i] = tempStr;
            }
        }
    }

    outEnglish.open("english2.txt");

    for (unsigned int i = 0; i < lines.size(); i++)
    {
        outEnglish << lines[i] << endl;
    }

    return 0;
}

size_t posFlag(string in)
{
    vector<size_t> locations;
    size_t toTest;
    size_t retVal;

    string partsOfSpeech[11];

    partsOfSpeech[0] = "n.";
    partsOfSpeech[1] = "prep.";
    partsOfSpeech[2] = "v.t.";
    partsOfSpeech[3] = "adv.";
    partsOfSpeech[4] = "pl.";
    partsOfSpeech[5] = "p.p.";
    partsOfSpeech[6] = "a.";
    partsOfSpeech[7] = "v.i.";
    partsOfSpeech[8] = "pron.";
    partsOfSpeech[9] = "conj.";
    partsOfSpeech[10] = "interj.";

    for (int i = 0; i < 11; i++)
    {
        toTest = in.find(partsOfSpeech[i]);

        if(toTest != string::npos)
        {
            locations.push_back(toTest);
        }

    }

    if (locations.size() != 0)
    {
        retVal = locations[0];

        for (unsigned int i = 0; i < locations.size(); i++)
        {
            if (retVal == locations[i])
                continue;

            else if (retVal <= locations[i])
                continue;

            else if (retVal > locations[i])
            {
                retVal = locations[i];
                continue;
            }
        }
    }
    else
    {
        retVal = string::npos;
    }

    return retVal;


}
