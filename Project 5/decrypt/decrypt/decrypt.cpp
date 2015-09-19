//
//  main.cpp
//  decrypt
//
//  Created by Brian Wong on 5/17/15.
//  Copyright (c) 2015 Brian Wong. All rights reserved.
//

#include <iostream>
#include <cstring>
#include <cctype>
#include <stdio.h>
#include <string.h>
using namespace std;



//Gets crib length

int getCribLength(const char crib[])                //this counts how many words we have in the crib.
{
    int i=0;
    int charcounter=0;
    while(i<strlen(crib))
    {
        if (isalpha(crib[i]))
        {
            while (isalpha(crib[i]))
            {
                i++;
            }
            charcounter++;
        }
        i++;
        
    }
    return charcounter;
}

//Checks for length of crib
//
//int maxlength(const char crib[])
//
//{
//    int i=0;
//    int maxlen=0;
//    while (i<strlen(crib))
//    {
//        
//        
//        int charcount=0;
//        if (isalpha(crib[i]))
//        {
//            
//            while (isalpha(crib[i]))
//            {
//                i++;
//                charcount++;
//            }
//            
//        }
//        
//        if (charcount>maxlen)
//        {
//            maxlen=charcount;
//        }
//        
//        i++;
//    }
//    
//    return maxlen;
//    
//}

//Lowercase function for chars

void charToLower(char input[])
{
    int i=0;
    while (i<strlen(input))
    {
        if (isalpha(input[i]))
        {
            input[i]=tolower(input[i]);
            i++;
        }
        i++;
    }
    
}


//Valid key function
bool isTranslatable(char key[][2], int getCribLength)
{ int i=0;
    while (i<getCribLength)     //run through the key
    {
        int j=i+1;
        while (j<getCribLength)             //take the ith element, and check if there is duplicates of it
        {
            if (key[i][0]==key[j][0])        //if duplicates, check if the corresponding keys match
            {
                if (key[i][1]!=key[j][1])
                {
                    return false;
                }
            }
            j++;
        }
        i++;
    }
    
    
    int k=0;
    while (k<getCribLength)
    {
        int j=k+1;
        while (j<getCribLength)
        {
            if (key[k][1]==key[j][1])
            {
                if (key[k][0]!=key[j][0])
                {
                    return false;
                }
            }
            j++;
        }
        k++;
    }
    
    
    
    return true;
}


//Translation function

void translation(char text[], char key [][2], int keylength)
{
    
    
    for (int i=0; i<keylength; i++)                     //upper case all crib key
    {
        key[i][0]=toupper(key[i][0]);
    }
    
    int i=0;
    while (i<strlen(text))                              //match the key from ciphertext to crib key
    {
        int j=0;
        while (j<keylength)
        {
            if (text[i]==key[j][1])
            {
                text[i]=key[j][0];
                break;
            }
            j++;
        }
        
        i++;
        
    }
}


bool decrypt(const char ciphertext[], const char crib[])
{
    
    //check if the crib word length is longer than 80 or no crib at all
    
    if (strlen(crib)>80 ||  strlen(crib) == 0)
    {
        return false;
    }
    
    
    //2D array for crib
    
    
    char myCrib[strlen(crib)];
    strcpy(myCrib, crib);
    charToLower(myCrib);
    
    
    int cribLetter=getCribLength(myCrib);
    char pureCrib[cribLetter][81];
    int cribWordNumber=0;
    
    int i=0;
    while (i<strlen(myCrib))
    {
        if (isalpha(myCrib[i]))
        {
            int j=0;
            while (isalpha(myCrib[i]))
            {
                pureCrib[cribWordNumber][j]=myCrib[i];
                j++;
                i++;
            }
            
            pureCrib[cribWordNumber][j]='\0';
            
            
            if (!isalpha(myCrib[i]))
            {
                while (!isalpha(myCrib[i]))
                {
                    i++;
                }
                cribWordNumber++;
                i--;
            }
        }
        i++;
    }
    
    
    
    
    //2D array for ciphertext
    char myCipher[strlen(ciphertext)];
    strcpy(myCipher, ciphertext);
    charToLower(myCipher);
    
    char pureText[4500][85];
    int textWordNumber=0;
    
    int m=0;
    while (m<strlen(myCipher))
    {
        if (isalpha(myCipher[m]))
        {
            int n=0;
            while (isalpha(myCipher[m]))
            {
                pureText[textWordNumber][n]=myCipher[m];
                n++;
                m++;
            }
            pureText[textWordNumber][n]='\0';
            
            
            if (myCipher[m]=='\n')
            {
                textWordNumber++;
                int n=0;
                pureText[textWordNumber][n]='\0';
                m++;
            }
            
            
            if (!isalpha(myCipher[m])&& myCipher[m]!='\n')
            {
                
                while (!isalpha(myCipher[m])&& myCipher[m]!='\n')
                {
                    m++;
                }
                textWordNumber++;
                m--;
            }
            
        }
        m++;
    }
    
    
    
    
    //Compare the crib to text
    
    
    
    char key[4500][2];
    int cribkey=0;
    int textkey=0;
    int keylength=0;
    
    int p=0;
    while (p<textWordNumber)
    {
        if (strlen(pureText[p])==strlen(pureCrib[0]))
        {
            
            //if we're too far into the text to match the crib
            if (p+cribWordNumber>textWordNumber)
            {
                return false;
            }
            
            //If matching consecutively
            int q=0;
            int matchcounter=0;
            while ((strlen(pureText[p])==strlen(pureCrib[q]))&&q<cribWordNumber)
            {
                matchcounter++;
                p++;
                q++;
                
            }
            
            
            if (matchcounter!=cribWordNumber)
            {
                p-=matchcounter;
            }
            
            
            
            //Store crib letters
            
            
            if (matchcounter==cribWordNumber)
            {
                int x=0;
                while (x<cribWordNumber)
                {
                    int y=0;
                    while (y<strlen(pureCrib[x]))
                    {
                        
                        key[cribkey][0]=pureCrib[x][y];
                        cribkey++;
                        y++;
                    }
                    x++;
                }
                
                
                
                //Store text letters
                
                int z=p-cribWordNumber;
                while (z<p)
                {
                    int y=0;
                    while (y<strlen(pureText[z]))
                    {
                        key[textkey][1]=pureText[z][y];
                        textkey++;
                        y++;
                    }
                    z++;
                }
                
                //Check if key is valid and translate
                
                if (textkey==cribkey)
                {
                    keylength=cribkey;
                    
                    if (isTranslatable(key, keylength))
                    {
                        
                        translation(myCipher, key, keylength);
                        
                        cout<<myCipher<<endl;
                        
                        return true;
                    }
                    else
                    {
                        cribkey=0;
                        textkey=0;
                        
                    }
                    
                    
                }
                
                
            }
            
        }
        
        
        p++;
    }
    
    return false;
    
}





void runtest(const char ciphertext[], const char crib[])
{
    cout << "====== " << crib << endl;
    bool result = decrypt(ciphertext, crib);
    cout << "Return value: " << result << endl;
}

int main()
{
    cout.setf(ios::boolalpha); // output bools as "true"/"false"
    
    //runtest("Hirdd ejsy zu drvtry od.\nO'z fodvtrry.\n", "my secret");
    //runtest("Hirdd ejsy zu drvtry od.\nO'z fodvtrry.\n", "shadow");
    
    //puctuations
    //runtest("Hirdd ejsy dr d^^^645847r dr dr dr vtry od.\nO'z fodvtrry.\n", "ni haip");
    
    //halfmatching
    //runtest("Hirdd ejsy dr dr dr dr dr vtry od.\nO'z fodvtrry.\n", "ni haip");
    //runtest("Hirdd hi hey hi hey hi halo od.\nO'z fodvtrry.\n", "pi pey pi palo");
    //runtest("am kzm hi hey hi halo od.\nO'z fodvtrry.\n", "pi pey pi palo");
    
    
    //newline match
    //runtest("bwra wmwt\n qeirtk spst\n", "alan turing");
    
    //newline match
    //runtest("bwra wmwt QEirtk spSt\n", "alan tuRIng");
    
    //one char crib
    
    //runtest("Hirdd ejsy dr d dr dr dr vtry od.\nO'z fodvtrry.\n", "a");
    
    //pure words
    //runtest("fodvtr Hirdd ejsy dr d^^^645847r dr dr dr vtry od.\nO'z .\n", "hzrdd");
    
    //Pure words Wrong key
    //runtest("Hirdd ejsy dr d^^^645847r dr dr dr vtry od.\nO'z ftdvtr.\n", "nihalp");
    
    //Bad key first, good match later
    //runtest("Hirdd ejsy ftdvtr dr d^^^645847r dr dr dr vtry od.\nO'z ftdvir.\n", "nihalp");
    //
    //long match
    //runtest("Hirdd ejsy ftdvtr dr d^^^645847r dr dr dr vtry od.\nO'z ftdvir.\n", " orihh wpsy tfhqfi hi");
    
    
    //crib words longer than text
    //runtest(" ftdvtr.\n", "nihaip to");
    
    
    //same char text
    //runtest("rrrrrr rr rrr r.\nO'z fodvtr.\n", " pp ppp p");
    
    
    
    //emptystring
    //runtest("rrrrrr rr rrr r.\nO'z fodvtr.\n", "");
}