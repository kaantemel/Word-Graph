//
//  main.cpp
//  wordgraph
//
//  Created by Kaan Temel on 12/25/21.
//

#include <iostream>
#include <unordered_map>
#include <fstream>
#include <iomanip>
#include <vector>
#include <stack>
using namespace std;

struct myStruct{
    string word;  // Stores the actual word
    bool known;   // Tracks whether the word has been explored in the graph
    int dist;     // Distance from the start word
    myStruct *path;  // Pointer to previous node in the path for backtracking
};

// Checks if two words can be transformed into each other with one simple edit
bool check(string a, string b)
{
    int counter=0;  // Counts the number of differing characters
    if (a.length()==b.length())
    {
        // Check for one character substitution
        for (int i =0; i<a.length(); i++)
        {
            if (a[i]!=b[i])
            {
                counter++;
            }
        }
    }
    else if (a.length()==b.length()+1 || a.length()+1==b.length())
    {
        // Check for one character insertion or deletion by comparing substrings
        for (int u = 0; u<max(a.length(), b.length()); u++)
        {
            string mystr="";
            for (int y=0; y<max(a.length(), b.length()); y++)
            {
                if (u!=y)
                {
                    mystr += (y < a.length() ? a[y] : b[y]);  // Construct substring without the u-th character
                }
            }
            if (mystr == (a.length() > b.length() ? b : a))
            {
                return true;
            }
        }
    }
    return counter==1;  // Return true if exactly one substitution
}

// Sets initial distances and explores all connections in the word graph
void distanceBuilder(vector<myStruct*> vec, string myword)
{
    myStruct *temp;
    // Find the start word in the vector and initialize
    for (int i = 0; i<vec.size(); i++)
    {
        if (vec[i]->word == myword)
        {
            temp = vec[i];
            temp->dist = 0;  // Set distance from start word to itself as 0
        }
    }

    // Using a breadth-first search approach to explore all connections
    for (int currDist=0; currDist<vec.size(); currDist++)
    {
        for (int y = 0; y<vec.size(); y++)
        {
            if (!vec[y]->known&&vec[y]->dist==currDist)
            {
                vec[y]->known = true;
                for (int a = 0; a<vec.size(); a++)
                {
                    if (check(vec[a]->word,vec[y]->word))
                    {
                        if (vec[a]->dist==-1)
                        {
                            vec[a]->dist = currDist+1;
                            vec[a]->path = vec[y];  // Set path for backtracking
                        }
                    }
                }
            }
        }
    }
}

// Helper to find a structure by word
myStruct* finder(vector<myStruct*>vec, string wo)
{
    for (int i = 0; i<vec.size(); i++)
    {
        if (vec[i]->word==wo)
        {
            return vec[i];
        }
    }
    return NULL;
}

// Checks if a word exists in the vector
bool wordFinder(vector<myStruct*>vec, string wo)
{
    for (int i = 0; i<vec.size(); i++)
    {
        if (vec[i]->word==wo)
        {
            return true;
        }
    }
    return false;
}

// Resets all nodes for a new search
void cleaner(vector<myStruct*> vec)
{
    for (int i = 0; i<vec.size(); i++)
    {
        vec[i]->path = NULL;
        vec[i]->dist = -1;
        vec[i]->known = false;
    }
}

// Prints the specific transformation between two words
void differenceprint(string a, string b)
{
    if (a.length()==b.length()&&a!=b)
    {
        for (int i =0; i<a.length(); i++)
        {
            if (a[i]!=b[i])
            {
                cout<<b<<" (change "<<a[i]<<" at position "<<i+1<<" to "<<b[i]<<")"<<endl;
            }
        }
    }
    else if (a.length()==b.length()+1)
    {
        for (int u = 0; u<a.length(); u++)
        {
            string mystr="";
            for (int y=0; y<a.length(); y++)
            {
                if (u!=y)
                {
                    mystr=mystr+a[y];
                }
            }
            if (mystr==b)
            {
                cout<<b<<" (deleted "<<a[u]<<" at position "<<u+1<<")"<<endl;
            }
        }
    }
    else if (a.length()+1==b.length())
    {
        for (int u = 0; u<b.length(); u++)
        {
            string mystr="";
            for (int y=0; y<b.length(); y++)
            {
                if (u!=y)
                {
                    mystr=mystr+b[y];
                }
            }
            if (mystr==a)
            {
                cout<<b<<" (inserted "<<b[u]<<" after position "<<u<<")"<<endl;
            }
        }
    }
    else
    {
        cout<<a<<endl;
    }
}

// Main function: sets up and manages the word transformation process
int main() {
    vector<myStruct *> myVec;
    ifstream file;
    file.open("words.txt");
    string words;
    // Read words from file and initialize structures
    while(file>>words)
    {
        myStruct *temp = new myStruct;
        temp->word = words;
        temp->known = false;
        temp->dist = -1;
        myVec.push_back(temp);
    }
    string start,end;
    cout<<"enter the words: ";
    cin>>start>>end;
    while (start[0]!='*')
    {
        stack<string> myStack;
        // Start the transformation process if both words are found
        if (wordFinder(myVec,start)&&wordFinder(myVec,end))
        {
            distanceBuilder(myVec, start);
            myStruct* mytemp = finder(myVec, end);
            while(mytemp->dist!=0)
            {
                myStack.push(mytemp->word);
                mytemp= mytemp->path;
            }
            myStack.push(mytemp->word);
            if (myStack.top()==start) {
                
                string mycheckword = start;
                cout<<"---Transformation Result---"<<endl;
                while (!myStack.empty())
                {
                    string asd =myStack.top();
                    differenceprint(mycheckword, asd);
                    mycheckword=asd;
                    myStack.pop();
                }
                
            }
            else
                cout<<"No Path"<<endl;
            cleaner(myVec);
        }
        else
            cout<<"wrong input"<<endl;
        cout<<endl;
        cout<<"enter the words: ";
        cin>>start>>end;
    }
    
    return 0;
}

