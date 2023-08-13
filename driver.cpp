#include <iostream>
#include <string>
#include <fstream>
using namespace std;
// opening files to write the output
ofstream outputFile1("patternMatchOutput_1.txt");
ofstream outputFile2("patternMatchOutput_2.txt");
ofstream outputFile3("patternMatchOutput_3.txt");
// opening the test data files
ifstream TextFile1("text1.txt");
ifstream TextFile2("text2.txt");
ifstream TextFile3("text3.txt");
ifstream PatternFile1("pattern1.txt");
ifstream PatternFile2("pattern2.txt");
ifstream PatternFile3("pattern3.txt");

// function to find the max of an array
int findMax(int *arr, int size)
{
    int maxValue = arr[0]; // Initialize with the first element

    for (int i = 1; i < size; i++)
    {
        if (arr[i] > maxValue)
        {
            maxValue = arr[i];
        }
    }
    return maxValue;
}

// pre-computation of the prefix function (LPS = logest prefix which is also a suffix)
int matchLPS(string subString)
{
    // this function accepts sub-strings of the pattern and returns the length of the LPS of that subString

    int matching_PS_lengths[subString.length() - 1]; // array to store lengths of matching prefix-suffix pairs
    for (int i = 0; i < subString.length() - 1; i++) // initialize all elements of 'matching_PS_lengths' to zero
    {
        matching_PS_lengths[i] = 0;
    }

    string prefixes[subString.length() - 1]; // array to store prefixes of the sub-string
    string suffixes[subString.length() - 1]; // array to store suffixes of the sub-string

    for (int i = 1; i < subString.length(); i++) // for loop to store the prefixes of the sub-string
    {
        prefixes[i - 1] = subString.substr(0, i);
    }
    for (int i = 1; i < subString.length(); i++) // for loop to store the suffixes of the sub-string
    {
        suffixes[i - 1] = subString.substr(subString.length() - i, i);
    }

    for (int i = 0; i < subString.length() - 1; i++) // iterate through prefixes[]
    {
        for (int j = 0; j < subString.length() - 1; j++) // iterate through suffixes[]
        {
            if (prefixes[i] == suffixes[j]) // if there is a matching PS pair, get the length
                matching_PS_lengths[i] = i + 1;
        }
    }
    return findMax(matching_PS_lengths, subString.length() - 1);
}

// implementation of the KMP algorithm
// void KMP_patternMatching(string str, string pat, int *PiArray)
// {
//     int matches; // number of character matches
//     int pos = 0; // current postion
//     int ENP;     // Earliest Next Position
//     do
//     {
//         matches = 0;
//         for (int i = 0; i < pat.length(); i++)
//         {
//             if (pat[i] == str[pos + i])
//             {
//                 matches++;
//                 if (matches == pat.length())
//                 {
//                     cout << "match found at position " << pos + 1 << endl;
//                     break;
//                 }
//             }
//             else
//                 break;
//         }
//         if (matches == 0)
//         {
//             ENP = ENP + 1;
//             pos = ENP;
//         }
//         else
//         {
//             ENP = pos + (matches - PiArray[matches - 1]);
//             pos = ENP;
//         }
//     } while (!(ENP > str.length() - pat.length()));
// }

// implementation of the KMP algorithm for regex with '?'
void KMP_forQuestionMark(string str, string pat, int *PiArray)
{
    int matches; // number of character matches
    int pos = 0; // current postion
    int ENP;     // Earliest Next Position
    do
    {
        matches = 0;
        for (int i = 0; i < pat.length(); i++)
        {
            if (pat[i] == str[pos + i])
            {
                matches++;
                if (matches > pat.length() - 2)
                {
                    outputFile2 << "match found at position " << pos << endl;
                    cout << "match found at position " << pos << endl;
                    break;
                }
            }
            else
                break;
        }
        if (matches == 0)
        {
            ENP = ENP + 1;
            pos = ENP;
        }
        else
        {
            ENP = pos + (matches - PiArray[matches - 1]);
            pos = ENP;
        }
    } while (!(ENP > str.length() - pat.length()));
}

// implementation of the KMP algorithm for regex with '+'
void KMP_for_Plus(string str, string pat, int *PiArray)
{
    int matches; // number of character matches
    int pos = 0; // current postion
    int ENP = 0; // Earliest Next Position
    do
    {
        matches = 0;
        for (int i = 0; i < pat.length(); i++)
        {
            if (pat[i] == str[pos + i])
            {
                matches++;
                if (matches == pat.length())
                {
                    outputFile1 << "match found at position " << pos << endl;
                    cout << "match found at position " << pos << endl;
                    int rep = 0;
                    while (str[pos + pat.length() + rep] == pat[pat.length() - 1])
                    {
                        ENP = ENP + 1;
                        pos = ENP;
                        rep++;
                    }
                    break;
                }
            }
            else
                break;
        }
        if (matches == 0)
        {
            ENP = ENP + 1;
            pos = ENP;
        }
        else
        {
            ENP = pos + (matches - PiArray[matches - 1]);
            pos = ENP;
        }
    } while (!(ENP > str.length() - pat.length()));
}

// implementation of the Naive String matching algorithm
void naiveStringSearch(string &text, char targetChar)
{
    int textLength = text.length();

    for (int i = 0; i < textLength; i++)
    {
        if (text[i] == targetChar)
        {
            outputFile3 << "match found at position " << i << endl;
            cout << "match found at position " << i << endl;
        }
    }
}

// function to extract the pattern from the regular expression
void preparePattern(string txt, string pat)
{
    if (pat[pat.length() - 2] == '+')
    {
        string pattern = pat.substr(1, pat.length() - 3);
        int prefixFunction[pattern.length()]; // prefix array (Pi function)
        string subStrings[pattern.length()];  // string array to store sub-strings of pattern
        for (int i = 0; i < pattern.length(); i++)
        {
            subStrings[i] = pattern.substr(0, i + 1);
        }
        // building the prefix function
        for (int i = 0; i < pattern.length(); i++)
        {
            if (subStrings[i].length() == 1)
                prefixFunction[i] = 0; // cannot match PS pairs for a single character, first elemet of prefix array is 0
            else
                prefixFunction[i] = matchLPS(subStrings[i]);
        }
        KMP_for_Plus(txt, pattern, prefixFunction);
    }

    else if (pat[pat.length() - 2] == '?')
    {
        string pattern = pat.substr(1, pat.length() - 3);
        int prefixFunction[pattern.length()]; // prefix array (Pi function)
        string subStrings[pattern.length()];  // string array to store sub-strings of pattern
        for (int i = 0; i < pattern.length(); i++)
        {
            subStrings[i] = pattern.substr(0, i + 1);
        }
        // building the prefix function
        for (int i = 0; i < pattern.length(); i++)
        {
            if (subStrings[i].length() == 1)
                prefixFunction[i] = 0; // cannot match PS pairs for a single character, first elemet of prefix array is 0
            else
                prefixFunction[i] = matchLPS(subStrings[i]);
        }
        KMP_forQuestionMark(txt, pattern, prefixFunction);
    }

    else if (pat[pat.length() - 2] == ']')
    {
        char beg = pat[pat.length() - 5];
        int b = static_cast<int>(beg);
        char end = pat[pat.length() - 3];
        int e = static_cast<int>(end);

        for (int i = b; i < e + 1; i++)
        {
            char pat_ = static_cast<char>(i);
            naiveStringSearch(txt, pat_);
        }
    }
}

// main function of the program
int main()
{
    // checking if all external files can be opened
    if (!TextFile1.is_open() || !TextFile2.is_open() || !TextFile3.is_open() || !PatternFile1.is_open() || !PatternFile2.is_open() || !PatternFile3.is_open())
    {
        cout << "Failed to open a file." << endl;
        return 1;
    }
    // checking if all external files can be opened
    if (!outputFile1.is_open() || !outputFile2.is_open() || !outputFile3.is_open())
    {
        cout << "Failed to open a file for writing." << endl;
        return 1;
    }

    string text_1;
    string pattern_1;
    string text_2;
    string pattern_2;
    string text_3;
    string pattern_3;

    // opening text1.txt and pattern1.txt
    if (getline(TextFile1, text_1) && getline(PatternFile1, pattern_1))
    {
        cout << "String: " << text_1 << endl;
        cout << "Regular Expression: " << pattern_1 << endl;
        preparePattern(text_1, pattern_1);
        cout << endl;
    }
    else
    {
        cout << "End of file reached or an error occurred while reading." << endl;
        cout << endl;
    }

    // opening text2.txt and pattern2.txt
    if (getline(TextFile2, text_2) && getline(PatternFile2, pattern_2))
    {
        cout << "String: " << text_2 << endl;
        cout << "Regular Expression: " << pattern_2 << endl;
        preparePattern(text_2, pattern_2);
        cout << endl;
    }
    else
    {
        cout << "End of file reached or an error occurred while reading." << endl;
        cout << endl;
    }

    // opening text2.txt and pattern2.txt
    if (getline(TextFile3, text_3) && getline(PatternFile3, pattern_3))
    {
        cout << "String: " << text_3 << endl;
        cout << "Regular Expression: " << pattern_3 << endl;
        preparePattern(text_3, pattern_3);
        cout << endl;
    }
    else
    {
        cout << "End of file reached or an error occurred while reading." << endl;
        cout << endl;
    }

    TextFile1.close();
    TextFile2.close();
    TextFile3.close();

    PatternFile1.close();
    PatternFile2.close();
    PatternFile3.close();

    outputFile1.close();
    outputFile2.close();
    outputFile3.close();

    return 0;
}
