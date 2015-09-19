//
//  main.cpp
//  Practice
//
//  Created by Brian Wong on 5/19/15.
//  Copyright (c) 2015 Brian Wong. All rights reserved.
//

#include <iostream>
#include <string>
#include <cstring>
#include <cctype>

using namespace std;

int main()
{
    const char* str = "C+ B+ B- A C A- D+ C- B+ D B";
    int count = 0;
    const char* p;
    for (p = str; *p != '\0'  &&  count < 6; p++)
        if (*p == ' ')
            count++;
    for ( ; *p != '\0'  &&  *p != ' '; p++)
        cout << *p;
    cout << '\n';
}

