#include <iostream>
#include <string>
using namespace std;

int main()
{
    int minutesUsed = 0;
    int numberTexts = 0;
    string customerName;
    int monthNumber = 0;
    cout.setf(ios::fixed);
    cout.precision(2);
    
    cout << "Minutes used: ";
    cin >> minutesUsed;
    cout << "Text messages: ";
    cin >> numberTexts;
    cin.ignore(10000,'\n');
    cout << "Customer name: ";
    getline (cin, customerName);
    cout << "Month number (1=Jan, 2=Feb, etc.): ";
    cin >> monthNumber;
    cout << "---" << endl;
    
    double minuteCost = 0;
    if (minutesUsed > 500)
        minuteCost = (minutesUsed - 500) * .45;
    
    double textCost = 0;
    if (numberTexts > 200 && numberTexts <= 400)
    {
        if ((monthNumber <= 9) && (monthNumber >= 6))
            textCost = (numberTexts - 200) * .02;
        else
            textCost = (numberTexts - 200) * .03;
    }
    
    double textCost2 = 0;
    if (numberTexts > 400)
        textCost2 = (numberTexts - 400) * .11;
    
    double fix = 0;
    if (numberTexts > 400 && monthNumber <= 9 && monthNumber >= 6)
        fix = 4.00;
    else if (numberTexts > 400 && ((monthNumber >= 1 && monthNumber < 6) || (monthNumber > 9 && monthNumber <= 12)))
        fix = 6.00;
    else
        fix = 0.00;
    
    
    double totalCost;
    totalCost = 40.00 + minuteCost + textCost + textCost2 + fix;
    
    if (minutesUsed < 0)
        cout << "The number of minutes used must be nonnegative." << endl;
    else if (numberTexts < 0)
        cout << "The number of text messages must be nonnegative." << endl;
    else if (customerName == "")
        cout << "You must enter a customer name." << endl;
    else if (monthNumber < 1 || monthNumber > 12)
        cout << "The month number must be in the range 1 through 12." << endl;
    else
        cout << "The bill for " << customerName << " is $" << totalCost << endl;
    
}
