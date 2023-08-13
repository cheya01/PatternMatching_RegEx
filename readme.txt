The file named 'driver.cpp' is the runnable source file.
You should have C++ compiler installed in-order to run the source file
All data files including texts and patterns are in the same folder.
Save all files locally and make sure your IDE supports all necessary types of files.

I have implemented the use of Regular Expressions (regex) using the Knuth-Morris-Ptratt Algorithm with slight variations. Also I have employeed 
the Naive-String-Matching Algorithm when I have to search for a single character in a string.
These are the regular expressions I have chosen to implement,

    1. Plus Sign ' + '  example /abc+/ /[a-c]/
This should match sequences where "abc" is followed by one or more occurrences of the letter "c". For example, it would match strings
like "abcc", "abccc", "abcccc", and so on.

    2. Question Mark ' ? '  example /ab?/ /[a-c]/
This should match either the character "b" followed by an optional "c", or just the character "b" alone.
Examples of strings that would match:
"bc" (because "b" is followed by "c")
"b" (because "c" is optional)

    3. Range (class) ' - '  example /[a-c]/
This is a character class. It matches any single character that falls within the range of "a" to "c", inclusive. It's like saying
"match either 'a', 'b', or 'c'."

The KMP algorithm employees a prefix function to efficiently search through a text. I used a functions called 'matchLPS'
(LPS = logest prefix which is also a suffix) and 'findMax' to pre-computate the prefix-array (Pi-array).

In all three implementations, I have used a function called 'preparePattern' to extract the pattern from the regular expression.
Then I checked the special symbol(+,? or -) of the regex and Then passed the pattern to different KMP based functions.

To implement the regex with the + sign,
I have employed a function called 'KMP_for_Plus' which is a KMP algorithm but with a slight difference.
When it finds a match, it further checks for repetitions of the last character of the pattern while increasing the ENP (Earliest Next Position)
while (str[pos + pat.length() + rep] == pat[pat.length() - 1]){
    ENP = ENP + 1;
    pos = ENP;
    rep++;
}

To implement the regex with the ? sign,
I have employed a function called 'KMP_forQuestionMark' which is a KMP algorithm with a slight difference.
When the number of character matches exceeds (length_of_pattern - 1) it identifies it as a match.
if (matches > pat.length() - 2)
{
    cout << "match found at position " << pos << endl;
    break;
}

To implement the regex with the - sign,
I have employed a function called 'naiveStringSearch' which is a Naive-String-Matching algorithm.
I have used that function with each and every character in the extracted range of characters.






