//
//  main.cpp
//  guitar
//
//  Created by Brian Wong on 4/22/15.
//  Copyright (c) 2015 Brian Wong. All rights reserved.
//

#include <iostream>
#include <string>
#include <cctype>
#include <cassert>
using namespace std;

bool isTuneWellFormed(string tune);
int translateTune(string tune, string& instructions, int& badBeat);



int main()
{
  
}


const char END_OF_BEAT = '/';
    

//isTuneWellFormed Function

    
bool isTuneWellFormed(string tune)
        {
        // Empty tune with no spaces is ok.
        
        if (tune.size() == 0)
            return true;
        
        // Tune has to end with a '/'.
        
        if (tune[tune.size()-1] != END_OF_BEAT)
            return false;
    
        
        // 1 loop = 1 beat.
        
        size_t k = 0;
        while (k != tune.size())
        {
            // If beat doesn't end, continue with the string
            
            if (tune[k] == END_OF_BEAT)
            {
                k++;
                continue;
            }
            
            // First digit.
            
            if (isdigit(tune[k]))
            {
                k++;
                
                // Second digit.
                
                if (isdigit(tune[k]))
                    k++;
            }
            
            // Get color letter.
            
            char color = tolower(tune[k]);
            if (color != 'g'  &&  color != 'r'  &&  color != 'y'  &&
                color != 'b'  &&  color != 'o'){
                return false;
            }else{
                k++;
            }
        
            
            // Check end of beat.
            
            if (tune[k] != END_OF_BEAT){
                return false;
            }else{
                k++;
            }
            
        }
        
        return true; //Tune passes all tests if true
        
}
    

//translateTune Function

    
int translateTune(string tune, string& instructions, int& badBeat)
    {
        // Return and error returns
        
        const int NO_PROBLEM = 0;
        const int NOT_WELL_FORMED = 1;
        const int WRONG_SUSTAINED_LENGTH = 2;
        const int SUSTAINED_NOTE_NOT_SUSTAINED = 3;
        const int PREMATURE_END = 4;
        
        // Stops here if tune wasn't well formed.
        
        if (!isTuneWellFormed(tune))
            return NOT_WELL_FORMED;
        
        
        
        string finalTune;
        
        int sustainedBeats = 0;  // Tracks number of beats (/ = x) in a sustained note
        char sustainedColor; // Color of a sustained note
        
        
        // One loop = one beat.
        
        int beatNumber;
        size_t k = 0;
        for (beatNumber = 1; k != tune.size(); beatNumber++)
        {
            // If there is a beat, it's either: a sustained beat or an 'x' beat.
            
            if (tune[k] == END_OF_BEAT)
            {
                if (sustainedBeats> 0)
                {
                    // Continue current sustained note
                    finalTune += sustainedColor;
                    sustainedBeats--;
                }
                else
                {
                  finalTune += 'x';
                }
                k++;
                continue;//If the beat is a '/', this if statement is skipped
            }
            
            // A sustained note can't be happening if only one slash is read            
            if (sustainedBeats > 0)
            {
                badBeat = beatNumber;
                return SUSTAINED_NOTE_NOT_SUSTAINED;
            }
            
            // If the beat starts with a digit, it's specifying a sustained note.
            // Determine the sustained note length.
            
            if (isdigit(tune[k]))
            {
                sustainedBeats = tune[k] - '0';
                k++;
                if (isdigit(tune[k]))
                {
                    sustainedBeats = 10 * sustainedBeats + tune[k] - '0';
                    k++;
                }
                
                // Sustained note length can't be < 2.
                if (sustainedBeats < 2)
                {
                    badBeat = beatNumber;
                    return WRONG_SUSTAINED_LENGTH;
                }
                
                //Translating lowercase note to uppercase (sustainedNote). Do this for as many times as the digit calls for from above(sustainedBeats)
                sustainedColor = toupper(tune[k]);
                finalTune += sustainedColor;
                sustainedBeats--;
            }
            else  //If not a sustained note, has to be a regular note.
            {
                finalTune += tolower(tune[k]);
            }
            
            // Avoids counting the end of a beat or a beat after a color as X.
            
            k += 2;
        }
        
        // If tune is done, but there is still a sustained beat = premature end.
        
        if (sustainedBeats > 0)
        {
            badBeat = beatNumber+1; //ASK ABOUT THIS: Do I use size or add 1 to current string?
            return PREMATURE_END;
        }
        
        instructions = finalTune;
        
        return NO_PROBLEM; //Only happens when all other test cases succeed.
}

    
