#include <iostream>
#include <string>
using namespace std;

int appendToAll(string a[], int n, string value);
int lookup(const string a[], int n, string target);
int positionOfMax(const string a[], int n);
int rotateLeft(string a[], int n, int pos);
int rotateRight(string a[], int n, int pos);
int flip(string a[], int n);
int differ(const string a1[], int n1, const string a2[], int n2);
int subsequence(const string a1[], int n1, const string a2[], int n2);
int lookupAny(const string a1[], int n1, const string a2[], int n2);
int separate(string a[], int n, string separator);

int main()
{
    string cast3[6] = { "glenn", "carl", "carol", "rick", "maggie", "daryl" };
    string cast[6] = {"maggie", "carl", "daryl", "rick", "michonne", "carol"};
    string characters[5] = { "rosita", "bob", "sasha", "glenn", "michonne" };
    string roles[6] = { "abraham", "tara", "", "daryl", "carol", "tyreese" };
    string roles2[6] = {"abraham", "tara", "", "daryl", "carol"};
    string group[5] = { "abraham", "tara", "tyreese", "", "maggie" };
    string names[10] = { "sasha", "rick", "bob", "glenn", "beth", "michonne" };
    string names1[3] = { "rick", "tita", "john"};
    string set1[10] = { "maggie","bob", "glenn", "rick" };
    string set2[10] = { "daryl", "carol" };
    string numbers[10] = { "4", "6", "3", "2", "9", "5", "8", "7", "1", "0"};
    string cast2[4] = { "carol", "rick", "michonne", "daryl" };
    /*int j = appendToAll(cast, -2, "!!!");
     cerr << j << endl;*/
    /*int x = lookup(names, 10, "michonne");
     cerr << x << endl;*/
    /*int y = positionOfMax(cast3, 6);
     cerr << y << endl;*/
    /*int q = rotateLeft(cast, 3, 1);
     cerr << q << endl;
     for(int x = 0; x < 6; x++)
     {
     cerr << cast[x] << endl;
     }*/
    /*int w = rotateRight(cast, 6, 2);
     for(int x = 0; x < 6; x++)
     {
     cerr << cast[x] << endl;
     }
     cerr << w << endl;*/
    /*int m = flip(roles, 3);
     for(int x = 0; x < 6; x++)
     {
     cerr << roles[x] << endl;
     }
     cerr << m << endl;*/
    
    int r = differ(roles, 1, roles2, 4);  //  returns 2
    int s = differ(roles, 2, group, 1);
    cerr << r << endl;
    cerr << s << endl;
    /*int t = subsequence(names, 10, names1, 0);// returns 1
     cerr << t << endl;*/
    /*int v = lookupAny(names, 5, set1, 4);  // returns 1 (a1 has "rick" there)
     cerr << v << endl;*/
    /*int x = separate(cast, 6, "glenn");
     cerr << x << endl;*/
    /*for(int x = 0; x < 10; x++)
     {
     cerr << cast[x] << endl;
     }*/
}



int appendToAll(string a[], int n, string value)
{
    if(n < 0)      //n cannot be negative
        return -1;
    for(int i = 0; i != n; i++)     //visit each element
    {
        a[i] += value;        //append
        cerr << a[i] << endl;
    }
    return n;
}

int lookup(const string a[], int n, string target)
{
    if(n < 0)          //n cannot be negative
        return -1;
    int k = 0;
    for(k = 0; k != n; k++)
    {
        if (a[k] == target) //run through each element, if equal to target, return k
        {
            return k;
        }
    }
    return -1;  //if not return -1
}

int positionOfMax(const string a[], int n)
{
    if(n <= 0)         //if n is negative or 0 this doesnt make sense
        return -1;
    int i = 0;
    int k = 0;
    string maximumValue = "";   //initialize maximumValue to empty string
    
    while(i != n)      //i cannot be the size of n because the max index number should be 1 less than n
    {
        if(a[i] > maximumValue)
        {
            k = i;                  //if i is greater than max value, change max value so it matches a[i]
            maximumValue = a[k];
        }
        i++;
    }
    return k;  //return position of max value
    
}

int rotateLeft(string a[], int n, int pos)
{
    if(n <= 0 || pos >= n || pos < 0)  //n cant be neg, pos cant be greater than n, and pos cant be neg
        return -1;
    
    string temp = a[pos];       //to hold value of a[pos]
    
    for(int i = pos; i < (n-1); i++)
    {
        a[i] = a[i + 1];    //the element to the left now has the value of the element that was on its right
    }
    a[n-1] = temp;    //last element gets temp
    
    return pos;
}

int rotateRight(string a[], int n, int pos)   //n cant be neg, pos cant be greater than n, and pos cant be neg
{
    if(n < 0 || pos >= n || pos < 0)
        return -1;
    
    string temp = a[pos];    //to hold value of a[pos]
    
    for(int i = pos; i > 0; i--)
    {
        a[i] = a[i-1];     //the element to the right now has the value of the element that was on its left
        
        
    }
    a[0] = temp;     //first element gets temp
    return pos;
}

int flip(string a[], int n)
{
    if(n <= 0)     //wont make sense if n is neg or zero
        return -1;
    int i = 0;
    int x = n-1;      //last position
    while (i < x)
    {
        string temp = a[i];     //temp holds value of a[i]
        a[i] = a[x];            //swap values
        a[x] = temp;
        x--;                    //decrement and increment
        i++;
        
    }
    
    return n;
}

int differ(const string a1[], int n1, const string a2[], int n2) //test this with another set of arrays
{
    int smaller;
    if(n1 < 0 || n2 < 0)        //cant be neg
        return -1;
    if(n1 < n2)                  //find out if n1 or n2 is smaller in order to return the correct value
        smaller = n1;
    else if(n1 > n2)
        smaller = n2;
    else
    {
        smaller = n1;
    }
    
    for(int i = 0; i < smaller; i++)
    {
        if(a1[i] == a2[i])            //if they do not differ check next element
            i++;
        else if(a1[i] != a2[i])       //if they do not equal return the position i where they differ
            return i;
        
    }
    return smaller;
}

int subsequence(const string a1[], int n1, const string a2[], int n2)
{
    if(n1 < 0 || n2 <0)
        return -1;
    if(n2 > n1)
        return -1;
    if(n2 == 0)
        return 0;
    if(n1 == 0 && n2==0)
        return 0;
    for(int i = 0; i < n1; i++)      //goes through a1
    {
        
        int positionHolder=0;
        
        
        if(a1[i] == a2[0])     //check the position of a1[i] against the first element of a2
        {
            positionHolder = i;    //holds position where subsequence begins
            
            int x = 0;
            while( x < n2)
            {
                if(a1[i+x] != a2[x]) //i is position where a1 started to match a2[0] so if a1[i+x] != a2[x] break
                {
                    break;
                    
                }
                if(x == n2 -1)
                {
                    return positionHolder;   //return the position in a1 where subsequece begins
                }
                x++;
            }
        }
    }
    return -1;
}


int lookupAny(const string a1[], int n1, const string a2[], int n2)
{
    
    if(n1 < 0 || n2 < 0)
        return -1;
    int i = 0;     //initialization
    int k = 0;
    
    // checks each element in the a1 against every element in the a2
    //k iterates slower than i
    while(k < n1)
    {
        while(i < n2)
        {
            if(a1[k] == a2[i])
                return k;     //return position in a1 where a match is found
            i++;
        }
        i = 0;
        k++;
        
    }
    return -1;
}


int separate(string a[], int n, string separator)
{
    if(n <= 0)
        return -1;
    string newarray[100000];     //make array extremely big so it works for all practical uses
    int k = 0;
    for(int i = 0; i < n; i++)
    {
        if(a[i] < separator)
        {
            newarray[k] = a[i];   //store all values that are less than separator in newarray
            k++;
        }
    }
    int y = k;                  //you left off at position k, so store that in y
    for(int i = 0; i < n; i++)
    {
        if(a[i] == separator)
        {
            newarray[y] = a[i];   //store all values that are equal to separator in newarray
            y++;
        }
    }
    int x = y;           //left off at position y, so store that in x
    
    for(int i = 0; i < n; i++)
    {
        if(a[i] > separator)
        {
            newarray[x] = a[i];  //store all values that are greater than separator in newarray
            x++;
        }
    }
    for(int i=0; i < n; i++)
    {
        a[i] = newarray[i];       //storing new array into the original
        //cerr << a[i] << endl;
    }
    
    return k;
}














