#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring>
#include <cctype>
#include <cassert>
using namespace std;

const int MAX_WORD_LENGTH = 20;

int standardizeRules(int distance[],  char word1[][MAX_WORD_LENGTH+1],  char word2[][MAX_WORD_LENGTH+1], int nRules);
int determineQuality(const int distance[],const char word1[][MAX_WORD_LENGTH+1],const char word2[][MAX_WORD_LENGTH+1],
                     int nRules,const char document[]);

int main()
{
    char document[200] = "I'm upset that on Nov. 15th, 2014, my 2 brand-new BMW 750Lis were stolen!!";
    int y = 4;
    int x[4] = {1,2,33,1};
    char word1[4][MAX_WORD_LENGTH+1] = {"yay", "tom", "nov", "pop"};   //does this work for the empty string
    char word2[4][MAX_WORD_LENGTH+1] = {"bappy", "bob", "brandnew", "dik"};   //i think this works
    int nRules = 4;     //the function doesnt change this
    int a = standardizeRules(x, word1, word2, 4);
    //    cout << a << endl;
    //     for(int k = 0; k < a; k++)
    //     {
    //     cout << x[k] << endl << word1[k]<< endl << word2[k] << endl;
    //     }
    cerr << determineQuality(x, word1, word2, nRules, document) << endl;
    
    
    const int TEST1_NCRITERIA = 4;
    int test1dist[TEST1_NCRITERIA] = {
        2,           4,          1,           13
    };
    char test1w1[TEST1_NCRITERIA][MAX_WORD_LENGTH+1] = {
        "mad",       "deranged", "nefarious", "have"
    };
    char test1w2[TEST1_NCRITERIA][MAX_WORD_LENGTH+1] = {
        "scientist", "robot",    "plot",      "mad"
    };
    assert(determineQuality(test1dist, test1w1, test1w2, TEST1_NCRITERIA,
                            "The mad UCLA scientist unleashed a deranged evil giant robot.") == 2);
    assert(determineQuality(test1dist, test1w1, test1w2, TEST1_NCRITERIA,
                            "The mad UCLA scientist unleashed    a deranged robot.") == 2);
    assert(determineQuality(test1dist, test1w1, test1w2, TEST1_NCRITERIA,
                            "**** 2014 ****") == 0);
    assert(determineQuality(test1dist, test1w1, test1w2, TEST1_NCRITERIA,
                            "  That plot: NEFARIOUS!") == 1);
    assert(determineQuality(test1dist, test1w1, test1w2, TEST1_NCRITERIA,
                            "deranged deranged robot deranged robot robot") == 1);
    assert(determineQuality(test1dist, test1w1, test1w2, TEST1_NCRITERIA,
                            "Two mad scientists suffer from deranged-robot fever.") == 0);
    cout << "All tests succeeded" << endl;
    
    
    
}

int standardizeRules(int distance[], char word1[][MAX_WORD_LENGTH+1], char word2[][MAX_WORD_LENGTH+1], int nRules)
{
    //check the line that is equal to nRules - 1;
    bool remove = false;
    for(int i = 0; i < nRules; i++)
    {
        if(distance[nRules - 1] <= 0)           //if the last thing is messed up just decrement nRules
        {
            nRules--;
            continue;
        }
        if(distance[i] <= 0)          //if distance is neg or zero
        {
            if(distance[nRules-1] <= 0)
            {
                nRules--;
                continue;
            }
            for(int y = i; y < nRules-1; y++)      //remove that line by shifting everything after the error to the left
            {
                distance[y] = distance[y+1];
                strcpy(word1[y], word1[y+1]);
                strcpy(word2[y], word2[y+1]);
                
            }
            nRules--;
            i--;                 //decrement i because after you push everything back you need to recheck that position
            continue;            //star from the outermost for-loop
        }
        if(strcmp(word1[i],"") == 0 || strcmp(word2[i],"") == 0)   //check for blank c-string
        {
            if(strcmp(word1[nRules-1],"") == 0 || strcmp(word2[nRules-1],"") == 0)
            {
                nRules--;
                continue;
            }
            for(int w = i; w < nRules-1; w++)
            {
                distance[w] = distance[w+1];          //remove that line by shifting everything after the error to the left
                strcpy(word1[w], word1[w+1]);
                strcpy(word2[w], word2[w+1]);
            }
            nRules--;
            remove = true;                         //reassign boolean
        }
        
        
        for(int z = 0; word1[i][z] != '\0' ;z++)
        {
            if(isalpha(word1[i][z]))                //make sure every c-string in word1 contains only letters
                word1[i][z] = tolower(word1[i][z]); //make letter lowercase
            else if(!(isalpha(word1[nRules-1][z])))
            {
                nRules--;
                continue;
            }
            else
            {
                for(int k = i; k < nRules-1; k++)        //if not letters, remove line by shifting everything after the error
                {
                    distance[k] = distance[k+1];
                    strcpy(word1[k], word1[k+1]);
                    strcpy(word2[k], word2[k+1]);
                }
                nRules--;
                remove = true;         //reassign boolean
                break;
            }
        }
        
        if(remove)            //this allows you to go back up to the outer for loop to start from the beginning
        {
            i--;
            remove=false;
            continue;
        }
        
        for(int a = 0; word2[i][a] != '\0' ;a++)
        {
            if(isalpha(word2[i][a]))                //make sure every c-string in word1 contains only letters
                word2[i][a] = tolower(word2[i][a]); //make lowercase
            else if(!(isalpha(word1[nRules-1][a])))
            {
                nRules--;
                continue;
            }
            else
            {
                for(int b = i; b < nRules-1; b++)      //if not remove by shifting
                {
                    distance[b] = distance[b+1];
                    strcpy(word1[b], word1[b+1]);
                    strcpy(word2[b], word2[b+1]);
                }
                nRules--;
                remove=true;                      //reassign boolean
                break;
            }
        }
        
        if(remove)              //allows you to go back up to the outer for loop
        {
            i--;
            remove = false;
            continue;
        }
        
        
        
    }
    for(int i = 0; i < nRules; i++)
    {
        
        for(int j = i+1; j < nRules; j++)
        {
            if(strcmp(word1[i], word1[j]) == 0 && strcmp(word2[i], word2[j]) == 0)   //if word1[i] and word2[i]
            {
                if(distance[i] > distance[j])      //are equal then only keep the one that has the greater distance
                {
                    if(i == nRules-1)
                    {
                        nRules--;
                        continue;
                    }
                    for(int r = j; r < nRules-1; r++)
                    {
                        distance[r] = distance[r+1];          //remove the line with the smaller distance by shifting
                        strcpy(word1[r], word1[r+1]);
                        strcpy(word2[r], word2[r+1]);
                    }
                    nRules--;                    //decrement appropriately
                    i--;
                }
                else
                {
                    if(i == nRules-1)
                    {
                        nRules--;
                        continue;
                    }
                    for(int r = i; r < nRules; r++)
                    {
                        distance[r] = distance[r+1];       //remove the line with the smaller distance by shifting
                        strcpy(word1[r], word1[r+1]);
                        strcpy(word2[r], word2[r+1]);
                    }
                    nRules--;
                    i--;
                }
                
            }
            else if(strcmp(word1[i], word2[j]) == 0 && strcmp(word2[i], word1[j]) == 0) //if both rules are the same but
            {                                                   //in reverse order
                if(distance[i] > distance[j])
                {
                    if(i == nRules-1)
                    {
                        nRules--;
                        continue;
                    }
                    
                    for(int r = j; r < nRules; r++)           //remove line with smaller distance
                    {
                        distance[r] = distance[r+1];
                        strcpy(word1[r], word1[r+1]);
                        strcpy(word2[r], word2[r+1]);
                    }
                    nRules--;                                //decrement appropriately
                    i--;
                }
                else
                {
                    if(i == nRules-1)
                    {
                        nRules--;
                        continue;
                    }
                    for(int r = i; r < nRules; r++)          //remove line with smaller distance
                    {
                        distance[r] = distance[r+1];
                        strcpy(word1[r], word1[r+1]);
                        strcpy(word2[r], word2[r+1]);
                    }
                    nRules--;
                    i--;
                }
                
            }
            
        }
    }
    
    return nRules;
}


int determineQuality(const int distance[],const char word1[][MAX_WORD_LENGTH+1],const char word2[][MAX_WORD_LENGTH+1],
                     int nRules,const char document[])
{
    char translation[200] = "";         //make a new c-string
    int pos = 0;
    for (int docPos = 0; document[docPos] != 0; docPos++)
    {
        if(isalpha(document[docPos]) == true || document[docPos] == ' ')   //if the character is a letter or space
        {                                                                  //add it to the translation
            translation[pos] = document[docPos];
            translation[pos] = tolower(translation[pos]);              //make the translation all lower case
            pos++;
            
        }
        if(document[docPos] == 0)//once it hits the 0 byte break out of it
        {
            break;
        }
        
        
    }
    //now we want to check each of the words in the translation to see if they match any of the words in word1[] or word2[]
    int r = 0;
    char *isSpace;
    char *newDocument[200];  //creates new c-strings for each word in translation
    for(int g = 0; g < 200; g++)
    {
        newDocument[g] = new char[MAX_WORD_LENGTH+1];
    }
    isSpace = strtok (translation," ");        //you know its a word when you hit a space
    while (isSpace != NULL)
    {
        strcpy(newDocument[r], isSpace);/////newDocument[r] = isSpace;
        isSpace = strtok (NULL, " ");
        //cerr << newDocument[r] << endl;
        r++;
    }
    
    
    
    int counter = 0;
    for(int wordpos = 0; wordpos < nRules; wordpos++)  //visit each position in word1/word2
    {
        bool ruleWasTrue = false;
        for(int compare = 0; compare < r; compare++)    //compare every word in word1/word2 with every word in newDocument
        {
            if(strcmp(newDocument[compare], word1[wordpos]) == 0) //if there is a match
            {
                for (int y = compare+1; (y-compare) <= distance[wordpos] && y < r; y++) //check for another match
                {                                                                       //distance away
                    if(strcmp(newDocument[y], word2[wordpos]) == 0)
                    {
                        counter++;                      //if you hit a match increment counter
                        ruleWasTrue = true;
                        break;
                    }
                }
            }
            if(ruleWasTrue == true)         //if match was found, break to outer for loop
                break;
            
            if(strcmp(newDocument[compare], word2[wordpos]) == 0)   //exact same structre as above, just checks if
            {                                       //newDocument matches with a word from word2 first
                for (int y = compare+1; (y-compare) <= distance[wordpos] && y < r; y++)
                {
                    if(strcmp(newDocument[y], word1[wordpos]) == 0)
                    {
                        counter++;
                        ruleWasTrue = true;
                        break;
                    }
                }
            }
            if(ruleWasTrue == true)
                break;
        }
    }
    
    return counter;
}
