//
//  main.cpp
//  Project 5
//
//  Created by Brian Wong on 5/10/15.
//  Copyright (c) 2015 Brian Wong. All rights reserved.
//

#include <iostream>
#include <string>
#include <cstring>
#include <cctype>
using namespace std;

void toLowerCase(char a[]);
void toUpperCase(char a[]);
bool decrypt(/*const char ciphertext[], const char crib[]*/);
void print(char store[][81], int n);
void split(char store[][81], char sent[], int&nWords);
bool isTranslatable(


int main(){
    decrypt();
}

void split(char store[][81]/*store into this*/, char sent[]/*what we read in*/, int&nWords){//Splits any sentence into separate words
    int row = 0;
    int col = 0;
    int i = 0;
    
    while(!isalpha(sent[i])){//For spaces or non chars in beginning of a word
        if(sent[i] == '\0'){//Dont move forward if this is the end of a sentence
            break;
        } else {
        i++;
        }
    }
    while(sent[i] != '\0'){
        if(sent[i] == ' '|| !isalpha(sent[i])){
            row++;
            col=0; //Start at first char
            while(!isalpha(sent[i])){//Skips over consective non alphas
                i++;
            }
            continue;//Initiates rest of loop when we get to next word - Basically, forcing us to go into       else after we move over the consecutive spaces
        }else{
            if(isalpha(sent[i])){
                store[row][col] = sent[i];
                col++;
                }
            }
            i++;
    }
    nWords = row+1;
}




bool decrypt(const char ciphertext[], const char crib[]){
    
    if (strlen(crib) > 80 || strlen(crib) == 0) {
        return false;
    }
    char myCipher[strlen(ciphertext)];
    strcpy(myCipher, ciphertext);
    myToLower(myCipher);
    
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
    
    char cribCopy[strlen(crib)];
    strcpy(cribCopy, crib);
    char cribSplit[40][81] = {'\0'};//Max space needed to hold all of a crib or ciphertext's valid words
    int numCrib;
    split(cribSplit, cribCopy, numCrib);

    char cipherSent[81];
    
    int c = 0;
    while(c<strlen(ciphertext)){//Splits the ciphertexts sentences
        int p = 0;
    
        while(ciphertext[c] != '\0' && ciphertext[c] != '\n'){
            cipherSent[p] = ciphertext[c];
            p++;
            c++;
        }
        cipherSent[p] ='\0';
        split(cipherSplit, cipherSent, numText);
        c++;
    }
    
    
    char key[4500][2];
    int cribkey=0;
    int textkey=0;
    int keylength=0;
    
    int p=0;
    while (p<numText)
    {
        if (strlen(pureText[p])==strlen(pureCrib[0]))
        {
            
            //if too late to match up
            if (p+cribWordNumber>numText)
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
            
            
            
            //======================================STORE CAP CRIB LETTER IN 0TH COLUMN================================
            
            
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
                
                
                
                //==================================STORE MATCHED TEXT LETTER IN 1ST COLUMN================================
                
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
                
                //==========================DOUBLE CHECK IF GOOD MATCH, TRANSLATE========================================
                
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
    
    
    


           
/*bool getNextSentence(char ciphertext[], char sent[], int startPos){
    int i = startPos;
    int pos = 0;
    while(ciphertext[i]!='\n' || ciphertext[i] != '\0'){
        sent[pos] = ciphertext[i];
        i++;
        pos++;
    }
    if()
}*/
        
void print(char store[][81], int n/*For nWords*/){
    cout<<"------------"<<endl;
    for (int i=0; i<n; i++){
        cout<<store[i]<<"#"<<endl;
    }
    cout<<"------------"<<endl;
}




