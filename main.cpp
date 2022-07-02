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
    string word;
    bool known;
    int dist;
    myStruct *path;
};
bool check(string a, string b)
{
    int counter=0;
    if (a.length()==b.length())
    {
        for (int i =0; i<a.length(); i++)
        {
            if (a[i]!=b[i])
            {
                counter++;
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
                return true;
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
                return true;
            }
        }
    }
    if (counter==1)
    {
        return true;
    }
    return false;
    
}

void distanceBuilder(vector<myStruct*> vec, string myword)
{
    myStruct *temp;
    for (int i = 0; i<vec.size(); i++)
    {
        if (vec[i]->word == myword)
        {
            temp = vec[i];
        }
    }
    temp->dist = 0;
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
                            vec[a]->path = vec[y];
                        }
                    }
                }
                
            }
        }
    }
}
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
void cleaner(vector<myStruct*> vec)
{
    for (int i = 0; i<vec.size(); i++)
    {
        vec[i]->path = NULL;
        vec[i]->dist = -1;
        vec[i]->known = false;
    }
}
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
int main() {
    vector<myStruct *> myVec;
    ifstream file;
    file.open("words.txt");
    string words;
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
                    //cout<<" "<<asd;
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
