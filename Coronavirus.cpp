/* 
 * File:   Coronavirus.cpp
 * Author: Jackson Burger
 * Purpose: Coronavirus class implementation
 * Created on June 15, 2021, 8:19 PM
 */

#include "Coronavirus.h"

//Default Constructor
//Purpose: Initializes all private variables
Coronavirus::Coronavirus()
{
    countyName = "none";
    state = "none";
    numCasesJan19 = -1;
    numCasesMar30 = -1;
    numCasesJun8 = -1;
    percentIncreaseJanMar = -1;
    percentIncreaseJanJun = -1;
}

//Copy Constructor
//Purpose: Copies the contents of another coronavirus vector to the newly created one
Coronavirus::Coronavirus(const Coronavirus& copyMe)
{
    countyName = copyMe.countyName;
    state = copyMe.state;
    numCasesJan19 = copyMe.numCasesJan19;
    numCasesMar30 = copyMe.numCasesMar30;
    numCasesJun8 = copyMe.numCasesJun8;
    percentIncreaseJanMar = copyMe.percentIncreaseJanMar;
    percentIncreaseJanJun = copyMe.percentIncreaseJanJun;
}

//Setter Constructor 
//Purpose: Allows the user to set the information into the private variables by passing in parameters rather than calling the setter methods
Coronavirus::Coronavirus(const string county, const string stat, const int numJan, const int numMar, const int numJun)
{
    countyName = county;
    state = stat;
    numCasesJan19 = numJan;
    numCasesMar30 = numMar;
    numCasesJun8 = numJun;
    percentIncreaseJanMar = (numCasesMar30 - numCasesJan19) / (numCasesJan19 * 1.0) * 100; //Did numCasesJan19 * 1.0 to make sure that the calculations was a float
    percentIncreaseJanJun = (numCasesJun8 - numCasesJan19) / (numCasesJan19 * 1.0) * 100;
}

Coronavirus::~Coronavirus()
{
    //not needed since we are not allocating any memory
}

// Getter Methods:
//Purpose: Giving access to the Coronavirus privates variables and returns it in each respected datatype
string Coronavirus::getCountyName()const
{
    return countyName;
}

string Coronavirus::getState()const
{
    return state;
}
    
int Coronavirus::getNumCasesJan19()const
{
    return numCasesJan19;
}
    
int Coronavirus::getNumCasesMar30()const
{
    return numCasesMar30;
}

int Coronavirus::getNumCasesJun8()const
{
    return numCasesJun8;
}

float Coronavirus::getPercentIncreaseJanMar()const
{
    return percentIncreaseJanMar;
}

float Coronavirus::getPercentIncreaseJanJun()const
{
    return percentIncreaseJanJun;
}

//**************************************************
//Setter Methods
//Purpose: Allows to set the values of Coronavirus private variables through the main program by passing in a parameter of same datatype
void Coronavirus::setCountyName(const string county)
{
    countyName = county;
}

void Coronavirus::setState(const string stat)
{
    state = stat;
}

void Coronavirus::setNumCasesJan19(const int numJan)
{
    numCasesJan19 = numJan;
}

void Coronavirus::setNumCasesMar30(const int numMar)
{
    numCasesMar30 = numMar;
}

void Coronavirus::setNumCasesJun8(const int numJun)
{
    numCasesJun8 = numJun;
}
//*****************************************

//Print Method
//Prints the contents of the private variables of the coronavirus object
void Coronavirus::print()const
{
    cout << countyName << ", " << state
         << "\n\tNumber of cases January 19: " << numCasesJan19
         << "\n\tNumber of cases March 30  : " << numCasesMar30 
         << " (" <<setprecision(4) << fixed << percentIncreaseJanMar << "% from January 19)"
         << "\n\tNumber of cases June 8    : " << numCasesJun8
         << " (" << setprecision(4) << fixed << percentIncreaseJanJun << "% from January 19)" << endl;
}
