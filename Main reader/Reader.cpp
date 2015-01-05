#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <cstring>
#include <iomanip>
#include <cstdio>

using namespace std;

#define space setw(25)

struct data
{
    string str;
    int counter1;
    bool flagC;
    bool flagW;
    unsigned int charCount;
};

struct compareLength
{
    bool operator()(const string& lhs, const string& rhs)
    {
        return lhs.size() < rhs.size();
    }
};

struct compareFlagC
{
    bool operator()(const data& lhs, const data& rhs)
    {
        return lhs.flagC < rhs.flagC;
    }
};

struct compareFlagW
{
    bool operator()(const data& lhs, const data& rhs)
    {
        return lhs.flagW < rhs.flagW;
    }
};

bool keepUppers(char c);
int main()
{
    char junk[] = "1234567890`~!@#$%^&*()_+=[]{}:;\'\",./<>?\\";
    vector <int> newlines;
    vector<string> input;
    vector<string> fCopy;
    vector<string>wList;
    vector<string>commons;
    vector<data> countedData;
    vector<data> important;
    ifstream readFile("input.txt");
    ifstream wordList;
    ifstream commonWords;
    ofstream writeFile;
    ofstream debug; //Remember to remove this once the program works
    debug.open("debug.log");
    writeFile.open("output.txt");
    bool leave;
    bool needPush;
    bool flip;
    compareLength c;
    compareFlagC cc;
    compareFlagW cw;

    unsigned int counter = 0;

    leave = false;
    needPush = false;

    wordList.open("wordlist.txt", ifstream::in);

    if (!wordList.good())
    {
        vector<string>rawDict;

        ofstream writeList;
        ifstream dictionary("dictionary.txt");
        cout << "Wordlist has not been populated. Please wait...\nThis will take several minutes.\n";

        copy(istream_iterator<string>(dictionary), {}, back_inserter(rawDict));
        for (unsigned int i = 0; i < rawDict.size(); i++)
        {
            rawDict[i].erase(remove_if(rawDict[i].begin(), rawDict[i].end(), keepUppers), rawDict[i].end());
        }

        sort(rawDict.begin(), rawDict.end(), c);

        for (unsigned int i = 0; i < rawDict.size();i++)
        {
            if (rawDict[i].size() == 4)
            {
                counter = i;
                break;
            }
        }

        rawDict.erase(rawDict.begin(), rawDict.begin() + counter);

        for (unsigned int i = 0; i < rawDict.size(); i++)
        {
            transform(rawDict[i].begin(), rawDict[i].end(), rawDict[i].begin(), ::tolower);
        }


        writeList.open("wordlist.txt");

        for (unsigned int i = 0; i < rawDict.size(); i++)
        {
            writeList << rawDict[i] << endl;
        }


    }

    else if(wordList.good())
    {
        copy(istream_iterator<string>(wordList), {}, back_inserter(wList));
    }

    commonWords.open("top500.txt", ios::in);

    if (!commonWords.good())
    {
        cout << "Common Words list not populated... please wait.\nThis may take several minutes.\n";

        ifstream rawCommons("google-10000-english.txt");
        ofstream outCommons;
        vector<string>tempCommons;
        unsigned int x;
        unsigned int length;

        copy(istream_iterator<string>(rawCommons), {}, back_inserter(tempCommons));

        counter = 0;

        for (unsigned int i = 0; i < tempCommons.size(); i++)
        {
            if (tempCommons[i].length()>= 4)
            {
                counter++;
            }

            if (counter == 500)
            {
                length = i;
            }
        }

        counter = 0;

        reverse(tempCommons.begin(), tempCommons.end());

        x = (tempCommons.size() - length);

        tempCommons.erase(tempCommons.begin(), tempCommons.begin() + x);

        reverse(tempCommons.begin(), tempCommons.end());

        sort(tempCommons.begin(), tempCommons.end(), c);

        for (unsigned int i; i < tempCommons.size(); i++)
        {
            if(tempCommons[i].length() == 4)
            {
                counter = i;
                break;
            }
        }

        tempCommons.erase(tempCommons.begin(), tempCommons.begin() + counter);

        outCommons.open("top500.txt");

        for(unsigned int i = 0; i < tempCommons.size(); i++)
        {
            outCommons << tempCommons[i] << endl;
        }
    }

    if (commonWords.good())
    {
        copy(istream_iterator<string>(commonWords), {}, back_inserter(commons));
    }



    copy(istream_iterator<string>(readFile), {}, back_inserter(input));
    cout << "Vector Size is now " << input.size() << endl;

    //for purposes of debugging
    for (unsigned int i = 0; i < input.size(); i++)
    {
        writeFile << i + 1 << "          " << input[i] << endl;
    }

    for (unsigned int i = 0; i < input.size(); i++)
    {
        for (unsigned int j = 0; j < strlen(junk); ++j)
        {
            //input[i].erase(remove(input[i].begin(), input[i].end(), junk[j]), input[i].end());
            (remove(input[i].begin(), input[i].end(), junk[j]), input[i].end());
        }
    }

    do
    {
        for (unsigned int i = 0; i < input.size(); i++)
        {
            if (input.at(i).length() == 0)
            {
                debug << i << ": DEBUG MESSAGE, IF ENTERED, ELEMENT SIZE IS " << input[i].length() << endl;
                input.erase(input.begin() + i);
                leave = false;
                break;
            }
            else
            {
                debug << i << ": DEBUG MESSAGE, IF NOT ENTERED, ELEMENT SIZE IS " << input[i].length() << endl;
                leave = true;
                continue;
            }
        }


    } while (!leave);

    cout << "Vector Size is now " << input.size() << endl;


    cout << "Printing fully sanitized file to output. \a\n";

    for (unsigned int i = 0; i < input.size(); i++)
    {
        transform(input[i].begin(), input[i].end(), input[i].begin(), ::tolower);
    }

    writeFile << "FIRST PASS OUTPUT \n\n";

    for (unsigned int i = 0; i < input.size(); i++)
    {
        writeFile << i + 1 << "          " << input[i] << endl;
    }

    writeFile << endl << endl;

    copy(input.begin(), input.end(), back_inserter(fCopy));

    sort(fCopy.begin(), fCopy.end(), c);

    writeFile << "SECOND PASS OUTPUT\n\n";

    for (unsigned int i = 0; i < fCopy.size();i++)
    {
        if (fCopy[i].size() == 4)
        {
            counter = i;
            break;
        }
    }

    fCopy.erase(fCopy.begin(), fCopy.begin() + counter);

    for (unsigned int i = 0; i < fCopy.size(); i++)
    {
        writeFile << i + 1 << "          " << fCopy[i] << endl;
    }

    writeFile << endl << endl;

    cout << "Counter Value is: " << counter << endl;

    for (unsigned int i = 0; i < fCopy.size(); i++)
    {
        // If vector is empty, initialize it with the first string in fCopy
        if (countedData.empty())
        {
            data temp;
            temp.counter1 = 1;
            temp.str = fCopy[i];
            temp.charCount = temp.str.length();
            temp.flagC = false;             //Innocent until proven guilty
            temp.flagW = false;
            countedData.push_back(temp);
        }

        // Else create a loop that traverses Counted Data to increment the counter.
        else
        {
            for (unsigned int j = 0; j < countedData.size(); j++)
            {
                needPush = false;

                if(countedData[j].str == fCopy[i])
                {
                    countedData[j].counter1 += 1;
                    break;
                }
                else if(fCopy[i].compare(0,countedData[j].str.length(), countedData[j].str) == 0)
                {
                    countedData[j].counter1 += 1;
                    break;
                }
                else
                {
                    needPush = true;
                }
            }

            if (needPush)
            {
                data temp;
                temp.counter1 = 1;
                temp.str = fCopy[i];
                temp.charCount = temp.str.length();
                temp.flagC = false;             //Innocent until proven guilty
                temp.flagW = false;
                countedData.push_back(temp);
                needPush = false;
            }
        }
    }

    writeFile << "THIRD PASS: COUNTED INPUT\n\n";

    for (unsigned int i = 0; i < countedData.size(); i++)
    {
        writeFile << i + 1 << "          " << countedData[i].str << "          " << "Character length: "<< countedData[i].charCount << "        " <<"Count is: " << countedData[i].counter1 << endl;
    }

    writeFile << endl << endl;

    counter = 0;

    for (unsigned int i = 0; i < countedData.size(); i++)
    {
        counter += countedData[i].counter1;
    }

    cout << endl << endl << "Word Counter is : " << counter << " Compared to unreduced input: " << fCopy.size() << endl << endl;

    for (unsigned int i = 0; i < countedData.size(); i++)
    {
        if ((countedData[i].counter1 >= 5) || (countedData[i].charCount >=7))
        {
            important.push_back(countedData[i]);
        }
    }

    cout << "There are " << important.size() << " words deemed possibly important in this document.\n";

    writeFile << "THE FOLLOWING WORDS ARE JUDGED TO POSSIBLY BE IMPORTANT\n\n";

    for (unsigned int i = 0; i < important.size(); i++)
    {
        writeFile << i +1 << ":     " << important[i].str << "    Character Count:  " << important[i].charCount << "    Number of occurrences in the document: " << important[i].counter1 << endl;
    }

    counter = 0;

    for(unsigned int i =0; i < important.size(); i++)
    {
        for (unsigned int j = 0; j < commons.size(); j++)
        {
            if (important[i].str == commons[j])
            {
                important[i].flagC = true;
                cout << important[i].str << " deemed common.\n";
                counter++;
                break;
            }
        }
    }

    sort(important.begin(), important.end(), cc);

    reverse(important.begin(), important.end());

    important.erase(important.begin(), important.begin() + counter);

    writeFile << "\nTHE ABOVE WORDS, WITH THOSE APPEARING IN THE TABLE OF 500 MOST COMMON WORDS REMOVED\n\n";

    for (unsigned int i = 0; i < important.size(); i++)
    {
        writeFile << setw(5) << left << i + 1 << space << left << important[i].str << endl;
    }

    for (unsigned int i = 0; i < important.size(); i++)
    {
        flip = false;

        for (unsigned int j = 0; j < wList.size(); j++)
        {
            if (important[i].str == wList[j])
            {
                flip = false;
                break;
            }
            else if(wList[j].compare(0,important[i].str.length(), important[i].str) == 0)
            {
                flip = false;
                break;
            }
            else if(important[i].str.compare(0, wList[j].length(), wList[j]) == 0)
            {
                flip = false;
                break;
            }
            else
            {
                flip = true;
            }
        }

        if (flip)
        {
            important[i].flagW = true;
            flip = false;
        }

    }

    writeFile << "\nAFTER DICTIONARY SEARCH\n\n";

    for (unsigned int i = 0; i < important.size(); i++)
    {
        if (important[i].flagW)
        {
            writeFile << setw(5) << left << i + 1 << space << left << important[i].str << space << left << "Not in dictionary" << endl;
        }
        else
        {
             writeFile << setw(5) << left << i + 1 << space << left << important[i].str << space << left << "Found in dictionary" << endl;
        }
    }



    debug.close();
    readFile.close();
    writeFile.close();

    return 0;
}

bool keepUppers(char c)
{
    switch(c)
    {
    case 'A':
    case 'B':
    case 'C':
    case 'D':
    case 'E':
    case 'F':
    case 'G':
    case 'H':
    case 'I':
    case 'J':
    case 'K':
    case 'L':
    case 'M':
    case 'N':
    case 'O':
    case 'P':
    case 'Q':
    case 'R':
    case 'S':
    case 'T':
    case 'U':
    case 'V':
    case 'W':
    case 'X':
    case 'Y':
    case 'Z':
        return false;
    default:
        return true;

    }
}
