/* 
 * File:   main.cpp
 * Author: Jackson Burger
 * Purpose: Main program
 * Created on June 15, 2021, 8:10 PM
 */

#include "Coronavirus.h"

//-------------------------------------------------------------------------
// Name:        search
// Parameters:  vector<Coronavirus> vector, const string county, const string state, const int low, const int high
// Returns:     integer (index of the vector of the searched item)
// Purpose:     Binary search goes through the vector until it find the county that was passed in, and returns an integer denoting the index 
//-------------------------------------------------------------------------
int search(vector<Coronavirus> vector, const string county, const string state, const int low, const int high)
{
    int mid = (low + high)/2; //Finds middle

    // check termination condition
    if (low > high)
    {
        return -1; //Not found
    }
    else if (vector[mid].getCountyName() == county && vector[mid].getState() == state) //If the passed in county is inside of the vector than return the index
    {
      return mid;  
    } //found


    // handle recursive cases
    else if (vector[mid].getCountyName() == county) //First checks to see if we are already found the county name, but need the proper state name
    {
        if (vector[mid].getState().compare(state) >= 0)  //Looking at the state: Left half of vector (state is higher alphabetically
            return search(vector, county, state, low, mid - 1);//Recursion searching again with the current middle -1 as the new high
        
        else if (vector[mid].getState().compare(state) <= 0) //Right half of vector (state is lower alphabetically
            return search(vector, county, state, mid + 1, high); //Recursion searching again with the current middle +1 as the new low
    }    
    else if (vector[mid].getCountyName().compare(county) >= 0) //left half of the vector (county name is higher alphabetically)
        return search(vector, county, state, low, mid - 1); //Recursion searching again with the current middle -1 as the new high

    else if (vector[mid].getCountyName().compare(county) <= 0) //right half of the vector (county name is lower alphabetically)
            return search(vector, county, state, mid + 1, high); //Recursion searching again with the current middle +1 as the new low
}

//-------------------------------------------------------------------------
// Name:        percentMarVsJun
// Parameters:  vector<Coronavirus> vector,const int index, int &count
// Returns:     float
// Purpose:     Counts each time a county had a lower percent increase through march than june recursively.
//-------------------------------------------------------------------------
float percentMarVsJun(vector<Coronavirus> vector,const int index, int &count)
{
    if (index == vector.size()) //Checks to see if there is any more counties to check through, if none are left then return the count
        return count;
    else if (vector[index].getPercentIncreaseJanMar() < vector[index].getPercentIncreaseJanJun()) //If the percent increase through march is lower than june
    {                                                                                             //then update the count and handle recursion
        count++;
        return(percentMarVsJun(vector,index + 1, count)); //Call the function again with index + 1 as the new vector location
    }
    else                                                  //There is no match so do not update count
        return(percentMarVsJun(vector,index + 1, count)); //Call the function again with index + 1 as the new vector location
}

using namespace std;
int main() 
{
    //Variables**************
    ifstream infile;
    string tempCountyName,tempState,tempNumJan,tempNumMar,tempNumJun;
    vector<Coronavirus> coronavirusVector;
    string userCounty, userState;
    char choice;
    int count = 0;
    //***********************
    
    //Reads and stores into vector from file
    infile.open("covid_data.txt"); //Opens file
    if (infile.is_open()) //Checks if file is open
    {
         while (getline(infile,tempCountyName,',') && getline(infile,tempState,',') && getline(infile,tempNumJan,',') && getline(infile,tempNumMar,',') && getline(infile,tempNumJun)) //Stores information using getline
         {
             Coronavirus tempCoronavirus(tempCountyName,tempState,stoi(tempNumJan),stoi(tempNumMar),stoi(tempNumJun)); //Creates a tempory coronavirus object and the stores the information read from the file
             coronavirusVector.push_back(tempCoronavirus); //Adds the temporary coronavirus object into the vector
         }
    }
    infile.close(); 
    //Closes file
    
    //User Interface
    while (choice != 'n')
    {    
        cout << "Please input county" << endl;    
        getline(cin,userCounty);
        cout << "Please input state" << endl;
        getline(cin,userState);
        int index = search(coronavirusVector,userCounty,userState,1,coronavirusVector.size()); //Searches using binary search using county name and state name inputted
        if (index != -1)
            coronavirusVector[index].print(); //If the county searched exist the print the contents of the object
        else
            cout << "There is no county with that name in this data" << endl; //If the county searched does not exist then say it doesnt exist
        
        cout << "Do you wish to continue? (y/n)" << endl;
        cin >> choice;
        tolower(choice);
        while (choice != 'y' && choice != 'n') //Needed in order to allow user to continue searching and printing information in the program
        {
            cout << "Please enter either (y/n)" << endl;
            cin >> choice;
        }
        cin.ignore();
    }
    
    //End of program, final output statement.
    percentMarVsJun(coronavirusVector,0,count); //Counts how many counties had lower percent increase in march than june and using pass by reference to store that amount in to variable "count"
    cout << "There were " << count << " counties who had a lower percent increase "
         << "in March Vs June out of the " << coronavirusVector.size() << " counties listed." << endl
         << "Thank you for using our system. Stay safe!" << endl;
            
    return 0;
}
