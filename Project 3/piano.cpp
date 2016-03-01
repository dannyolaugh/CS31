#include <iostream>
#include <string>
using namespace std;

bool isTuneWellFormed(string tune);
int translateTune(string tune, string& instructions, int& badBeat);
bool isTunePlayable(string tune);
char translateNote(int octave, char noteLetter, char accidentalSign);
int main()
{
    string tune = "C/C/G/G/A/A/G/";
    string instructions;
    int badBeat;
    if(isTuneWellFormed(tune))
        cout<< "working" << endl;
    else
        cout<< "broken" << endl;
    int x = translateTune(tune, instructions, badBeat);
    cout << "Instructions are " << instructions << endl;
    cout << "Return value " << x << endl;
    cout << "Bad beat is " << badBeat << endl;
    
    
}

bool isLetter(char letter)
{
    if(letter == 'A' || letter == 'B' || letter == 'C' || letter == 'D' || letter == 'E' || letter == 'F' || letter == 'G')
        return true;
    else
        return false;
}

bool isTuneWellFormed(string tune)
{
    
    int i= 0;
    if(tune == "")
        return true;
    if (tune[tune.size() - 1] != '/')
        
        return false; // if last thing is not a slash it will break out of the loop and return false.
    
    while(i < tune.size())  //run through each character of tune.
    {
        
        char position = tune[i];
        if (position == '/')
            i++;
        else if (isLetter(position)) //if first char is not a slash check if its a letter, followed by accidental
            //followed by number
        {
            position = tune[i+1];
            if(position == 'b' || position == '#')
            {
                position = tune[i+2];
                if(position == '0' || position == '1' || position == '2' || position == '3' || position == '4' || position == '5'|| position == '6' || position == '7' || position == '8' || position == '9')
                    i +=3; // increment by 3 to get to the next unread char
                else
                    i +=2;//if there is no number you need only increment by 2 to get to the next note.
            }
            else if (position == '0' || position == '1' || position == '2' || position == '3' || position == '4' || position == '5'|| position == '6' || position == '7' || position == '8' || position == '9')
                i+=2; //if followed by just number, increment by 2 to get to the next unread character
            else
                i++;
        }
        else if(!(isLetter(position))) //if the first thing isnt a slash or a letter it cannot be well formed
        {
            return false;
        }
    }
    
    return true;
}

/*note: in the following function when the character zero is subtracted from another character it turns the character into an integer by using the according ASCII values*/
int translateTune(string tune, string& instructions, int& badBeat) //these are just copies
{
    string translation = "";
    if(isTuneWellFormed(tune)== false)
        return 1;
    if(tune == "")
    {
        instructions = translation;  //if the tune is blank, so is the translation
        return 0;
    }
    
    int i = 0;
    int beatcounter = 1;
    int translationcounter=0;
    
    while(i < tune.size())  //visit each character
    {
        if(tune[i] == '/')
        {
            beatcounter++;
            if(translationcounter== 0)
                translation += " "; //append a space to translation
            if(translationcounter > 1)
            {
                translation.insert((translation.size() - translationcounter) , "[");
                translation += "]";
                
            }
            translationcounter = 0; //reset translation counter after adding brackets
            i++;
            
            
        }
        else if (isLetter(tune[i]) && (tune[i+1] == 'b' || tune[i+1] == '#') && isdigit(tune[i+2]))
            // letter,accidental,number
        {
            translation += translateNote(tune[i+2]- '0', tune[i], tune[i+1]); //append
            if(translateNote(tune[i+2]- '0', tune[i], tune[i+1]) == ' ')
            {
                badBeat = beatcounter;  //to see what beat the badBeat is in
                return 2;
            }
            i += 3;   //increment by three to get to next unread character
            translationcounter++; //this tells how many notes there have been since a slash. to see if
            //you should add brackets
            
        }
        
        else if (isLetter(tune[i]) && (tune[i+1] == 'b' || tune[i+1] == '#') && !isdigit(tune[i+2])) //letter,accidental
        {
            translation += translateNote(4, tune[i], tune[i+1]);
            
            if(translateNote(4, tune[i], tune[i+1]) == ' ')
            {
                badBeat = beatcounter;
                return 2;
            }
            i += 2; //increment by two to get to next unread character
            translationcounter++;
            
        }
        
        else if (isLetter(tune[i]) && (tune[i+1] != 'b' || tune[i+1] != '#') && !isdigit(tune[i+1])) //just a letter
        {
            translation += translateNote(4, tune[i], ' ');
            if(translateNote(4, tune[i], ' ') == ' ')
            {
                badBeat = beatcounter;
                return 2;
            }
            i += 1; //increment by one to get to next character
            translationcounter++;
            
        }
        else
        {
            translation += translateNote(tune[i+1] - '0', tune[i], ' ');
            if(translateNote(tune[i+1] - '0', tune[i], ' ') == ' ')
            {
                badBeat = beatcounter;
                return 2;
            }
            i += 2;
            translationcounter++;
        }
        
    }
    instructions = translation;
    
    return 0;
    
}


char translateNote(int octave, char noteLetter, char accidentalSign)
{
    // This check is here solely to report a common CS 31 student error.
    if (octave > 9)
    {
        cerr << "********** translateNote was called with first argument = "
        << octave << endl;
    }
    
    // Convert Cb, C, C#/Db, D, D#/Eb, ..., B, B#
    //      to -1, 0,   1,   2,   3, ...,  11, 12
    
    int note;
    switch (noteLetter)
    {
        case 'C':  note =  0; break;
        case 'D':  note =  2; break;
        case 'E':  note =  4; break;
        case 'F':  note =  5; break;
        case 'G':  note =  7; break;
        case 'A':  note =  9; break;
        case 'B':  note = 11; break;
        default:   return ' ';
    }
    switch (accidentalSign)
    {
        case '#':  note++; break;
        case 'b':  note--; break;
        case ' ':  break;
        default:   return ' ';
    }
    
    // Convert ..., A#1, B1, C2, C#2, D2, ... to
    //         ..., -2,  -1, 0,   1,  2, ...
    
    int sequenceNumber = 12 * (octave - 2) + note;
    
    string keymap = "Z1X2CV3B4N5M,6.7/A8S9D0FG!H@JK#L$Q%WE^R&TY*U(I)OP";
    if (sequenceNumber < 0  ||  sequenceNumber >= keymap.size())
        return ' ';
    return keymap[sequenceNumber];
}
