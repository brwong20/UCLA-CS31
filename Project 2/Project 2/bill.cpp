//
//  main.cpp
//  Project 2
//
//  Created by Brian Wong on 4/9/15.
//  Copyright (c) 2015 Brian Wong. All rights reserved.
//

#include <iostream>
#include <string>
using namespace std;

int main() {
    
    //Gets the intial meter reading and prints error if it is negative.
    cout << "What is your initial meter reading? " << endl;
    double initialReading;
    cin >> initialReading;
    if(initialReading < 0){
        cout << "---" << endl;
        cout << "The intial meter reading must be nonnegative." << endl;
        return 0;
    }
    
    //Gets final meter reading and prints error if it's less than intial reading.
    cout << "What is your final meter reading? " << endl;
    double finalReading;
    cin >> finalReading;
    if (finalReading < initialReading) {
        cout << "---" << endl;
        cout << "The final reading must be at least as large as the initial reading." << endl;
        return 0;
    }
    cin.ignore(10000, '\n');
    
    //Gets customer name and prints error if nothing is entered.
    cout << "What is your name? " << endl;
    string personsName;
    getline(cin, personsName);
    if(personsName == ""){
        cout << "---" << endl;
        cout << "You must enter a customer name." << endl;
        return 0;
    }
    
    //Gets month number
    cout << "What month is it? (1=Jan, 2=Feb, 3=Mar, etc.) " << endl;
    int monthNumber;
    cin >> monthNumber;
    cout << "Month number: " << monthNumber << endl;
    if(monthNumber <=0 || monthNumber > 12){
        cout << "---" << endl;
        cout << "The month number must be in the range 1 through 12." << endl;
        return 0;
    }
    
    //Difference (Usage of water)
    double waterUsed;
    waterUsed = (finalReading - initialReading);
    
    //Rate for high usage season
    double billValue = 0.0;
    if((monthNumber>=4 || monthNumber <=10) && waterUsed <= 44){
        billValue = waterUsed * 2.75;
        
    } else if((monthNumber >= 4 || monthNumber <=10) && waterUsed > 44){
        billValue = (44 * 2.75) + ((waterUsed-44) * 3.38);
        
    }
    cout.setf(ios::fixed);
    cout.precision(2);
    
    //Rate for low usage season
    if((monthNumber >= 11 || monthNumber <=3) && waterUsed <=31){
        billValue = waterUsed * 2.75;
        
    } else if((monthNumber >= 11 || monthNumber <=3) && waterUsed > 31){
        billValue = (31*2.75) + ((waterUsed-31)*2.89);
        
    }
    cout.setf(ios::fixed);
    cout.precision(2);
    
    //Bill Sheet
    cout << "Initial meter reading: " << initialReading << endl;
    cout << "Final meter reading: " << finalReading <<endl;
    cout << "Customer name: " << personsName << endl;
    cout << "Month number: " << monthNumber << endl;
    cout << "You have used " << waterUsed << " HCF of water this month." << endl;
    cout << "---" << endl;
    cout << "The bill for " << personsName << " is " << "$" << billValue << endl;
    
    
    
}