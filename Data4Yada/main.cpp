// Data4Yada
// main.cpp
// 9/4/17

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "vector.h"
#include "strlib.h"

int main(int argc, char** argv)
{
	// Variables
    Vector<std::string> dialogueList; // Vector storing each meaningful chunk of dialogue
    std::string currDialogue; // Stores what is currently being said and concatonates each new line to create a meaningful chunk of dialogue. Adds each completed chunk of dialogue to to dialogueList when speaker is finished and clears for new speaker.
    std::string fname = ""; // User inputed filename
    bool someoneSpeaking = false; // Checks if someone was speaking in previous line
    
    // Prompt for input
    std::cout << "What is the file name of the transcript you would like? ";
    std::getline(std::cin, fname);
    
    // Check for a bad file
    std::ifstream file(fname);
    if (!file.is_open())
    {
        std::cout << "Error: File does not exist" << std::endl;
        return 0;
    }
    
    // Read each line until the end of the file
    while (!file.eof())
    {
        // Read current line from file and stores as String "tempLine"
        std::string tempLine;
        std::getline(file, tempLine);
        
        // Check whether or not someone was speaking
        if (!someoneSpeaking)
        {
            // If no one is speaking, check if this is the beginning of new dialogue
            if (tempLine.find("COUNSELOR") != std::string::npos || tempLine.find("PATIENT") != std::string::npos)
            {
                // Store what is currently being said in currDialogue
                currDialogue = tempLine;
                
                // Note that someone is now speaking
                someoneSpeaking = true;
            }
        }
        // If someone was speaking, do the following:
        else
        {
            // If someone was speaking, and now someone new is speaking do the following:
            if (tempLine.find("COUNSELOR") != std::string::npos || tempLine.find("PATIENT") != std::string::npos)
            {
                // Add the full dialogue of the person who was speaking to the vector
                dialogueList.add(currDialogue);
                
                // Clear currDialogue and fill with new speech
                currDialogue = tempLine;
            }
            
            // If someone was speaking, and this is a break in meaningful content, do the following:
            else if (tempLine == "" || tempLine.find("http://ezproxy") != std::string::npos)
            {
                // Note that no one is speaking anymore
                someoneSpeaking = false;
                
                // Add what was said to our vector of dialogue
                dialogueList.add(currDialogue);
                
                // Clear currDialogue
                currDialogue = "";
            }
            
            // If someone was speaking, and they still are speaking, do the following:
            else
            {
                // Add this new line to what they had been saying
                currDialogue += " " + tempLine;
            }
        }
    }
    
    // Print full vector to show what we have now saved.
    for (int i = 0; i < dialogueList.size(); i++)
    {
        std::cout << dialogueList[i] << std::endl;
    }

    return 0;
    
}


















