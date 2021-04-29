/*
 * main.cpp
 *
 * COSC 051 Fall 2018
 * Project #3
 *
 * Due on: NOV 5, 2018
 * Author: byy2
 *
 *
 * In accordance with the class policies and Georgetown's
 * Honor Code, I certify that, with the exception of the
 * class resources and those items noted below, I have neither
 * given nor received any assistance on this project.
 *
 * References not otherwise commented within the program source code.
 * Note that you should not mention any help from the TAs, the professor,
 * or any code taken from the class textbooks.
 */


#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>
#include <cctype>
#include <fstream>
#include <vector>
#include <cstdlib>
using namespace std;

/********************************************************************************
 *                                                                              *
 *                 Function prototypes for Project #3                           *
 *                                                                              *
 ********************************************************************************/

char displayMenu();

void uploadFile(string fName, bool &loadSuccess, vector<char> &sCode, 
                vector<double> &len, vector<double> &dep, vector<double> &hei,
                vector<int> &lenF, vector<int> &depF, 
                vector<string> &oNum, vector<string> &reg);

void allDetails(const vector<char> &sCode, const vector<double> &len, 
                const vector<double> &dep, const vector<double> &hei,
                const vector<int> &lenF, const vector<int> &depF, 
                const vector<string> &oNum, const vector<string> &reg);

void orderDetails(const vector<char> &sCode, const vector<double> &len,
                  const vector<double> &dep, const vector<double> &hei,
                  const vector<int> &lenF, const vector<int> &depF, 
                  const vector<string> &oNum, const vector<string> &reg);

void summaryByStone(const vector<char> &sCode, const vector<double> &len,
                    const vector<double> &dep, const vector<double> &hei,
                    const vector<int> &lenF, const vector<int> &depF, 
                    const vector<string> &oNum, const vector<string> &reg);

void summaryByRegion(const vector<char> &sCode, const vector<double> &len, 
                     const vector<double> &dep, const vector<double> &hei,
                     const vector<int> &lenF, const vector<int> &depF, 
                     const vector<string> &oNum, const vector<string> &reg);

bool clearAllVectors(vector<char> &sCode, vector<double> &len, vector<double> &dep,
                     vector<double> &hei, vector<int> &lenF, vector<int> &depF, 
                     vector<string> &oNum, vector<string> &reg);


// GLOBAL CONSTANTS
const double MARBLE_PRICE = 92.99;
const double GRANITE_PRICE = 78.99;
const double QUARTZ_PRICE = 56.99;
const double EDGE_FINISHING_RATE = 4.99;
const double WASTAGE_PERCENT = 0.26;
const double MAX_LENGTH = 25.0;
const double MIN_LENGTH = 5.0;
const double MAX_DEPTH = 25.0;
const double MIN_DEPTH = 5.0;
const int MIN_EDGES_FINISHED = 0;
const int MAX_EDGES_FINISHED = 2;
const int MONTH_DIFFERENCE = 8;
const double MIN_HEIGHT_FACTOR = 0.58;
const double MAX_HEIGHT_FACTOR = 0.80;
const int FOUR_MONTH_DIFFERENCE = 4;
const int TWO_YEAR_DIFFERENCE = 2;
const int ONE_YEAR_DIFFERENCE = 1;
const int FOUR_MONTH_DIFFERENCE_NEW_YEAR = -7;
const int TWELVE_MONTH_DIFFERENCE = 12;
const int ONE_ERROR = 1;
const int ZERO_ERRORS = 0;
const string NORTH = "North";
const string EAST = "East";
const string SOUTH = "South";
const string WEST = "West";
const string OTHER = "Other";

    
//START MAIN
int main()
{
    string fName = " ";
    bool loadSuccess = false;
    bool vectorsCleared = true;
    vector<char> sCode;
    vector<double> len;
    vector<double> dep;
    vector<double> hei;
    vector<int> lenF;
    vector<int> depF;
    vector<string> oNum;
    vector<string> reg;
    char userChoice = ' ';
    
    
    //DISPLAY WELCOME MESSAGE
    cout << "Welcome to Claude's Custom Counters, Inc. Calculator" << endl;
    cout << "This application calculates cost and fabrication" << endl;
    cout << "data based on sales data input files." << endl;
    cout << endl;
    
    //do-while loop to display menu until user wants to quit
    
    do
    {
        userChoice = displayMenu();
        
        if(toupper(userChoice)=='Q')
        {
            cout << "Thanks for using Claude's Custom Counters, Inc. Calculator." << endl;
        }
        
        //UPLOAD FILE
        if(toupper(userChoice)=='U')
        {
            //file name initiation
            cout << "Please enter the complete path and name of the file: ";
            cin >> fName;
            cout << endl;
            
            uploadFile(fName, loadSuccess, sCode, len, dep, hei, lenF, depF, oNum, reg);
        }
        
        //THESE FUNCTIONS CAN ONLY BE CALLED IF VECTORS HAVE AT LEAST ONE ELEMENT IN THEM
        if(loadSuccess) 
        {
            //DISPLAY ALL DETAILS
            if(toupper(userChoice)=='A')
            {
                allDetails(sCode, len, dep, hei, lenF, depF, oNum, reg);
            }

            //DISPLAY ORDER DETAILS
            else if(toupper(userChoice)=='O')
            {
                orderDetails(sCode, len, dep, hei, lenF, depF, oNum, reg);
            }

            //SUMMARY BY REGION
            else if(toupper(userChoice)=='R') 
            {
                summaryByRegion(sCode, len, dep, hei, lenF, depF, oNum, reg);
            }

            //SUMMARY BY STONE CODE
            else if(toupper(userChoice)=='S' )
            {
                summaryByStone(sCode, len, dep, hei, lenF, depF, oNum, reg);
            }

            //CLEAR ALL VECTORS
            else if(toupper(userChoice)=='C')
            {
                vectorsCleared = clearAllVectors(sCode, len, dep, hei, lenF, depF, oNum, reg);
                if(vectorsCleared)
                {
                    loadSuccess = false;
                }
            }
        }
        else
        {
            if(toupper(userChoice)=='A'||toupper(userChoice)=='O' ||toupper(userChoice)=='R'
               ||toupper(userChoice)=='S')
            {
                cout << "Please load at least one data file before trying to display data.";
                cout << endl;
                cout << endl;
            }
            if(toupper(userChoice)=='C')
            {
                cout << "Nothing to clear. Vectors are already empty." << endl;
                cout << endl;
            }
        }
    }while(toupper(userChoice)!= 'Q');

    return 0;
} //END FUNCTION MAIN



/********************************************************************************
 *                                                                              *
 *                                                                              *                                                                              * 
 *                                                                              *
 *                                                                              *
 *                 Function Definitions for Project #3                          *
 *                                                                              *
 *                                                                              *
 *                                                                              *
 *                                                                              *
 ********************************************************************************/


/********************************************************************************
 *                                                                              *
 *                            Display Menu                                      *
 *                                                                              *
 ********************************************************************************/

char displayMenu()
{
    
    char choice = ' ';
    cout << setw(40) << "Upload a regional sales data file" << "\t" << "U" << endl;
    cout << setw(40) << "Display details (All loaded data)" << "\t" << "A" << endl;
    cout << setw(40) << "List details for specific Order number" << "\t" << "O" << endl;
    cout << setw(40) << "Display summary by Region" << "\t" << "R" << endl;
    cout << setw(40) << "Display summary by Stone code" << "\t" << "S" << endl;
    cout << setw(40) << "Clear all vectors" << "\t" << "C" << endl;
    cout << setw(40) << "Quit" << "\t" << "Q" << endl;   
    
    cout << endl;
    cout << "Please choose an option from the menu and enter the code: ";
    cin >> choice;
    cin.ignore(100000000, '\n');
    cout << endl;
    
    //if invalid input, display menu again
    while(toupper(choice)!='U' && toupper(choice)!='A' && toupper(choice)!='O'
          && toupper(choice)!='R' && toupper(choice)!='S' && toupper(choice)!='C'
          && toupper(choice)!='Q')
    {
        cout << endl;
        cout << "Invalid choice. Here are the valid choices: " << endl;
        cout << endl;
        cout << setw(40) << "Upload a regional sales data file" << "\t" << "U" << endl;
        cout << setw(40) << "Display details (All loaded data)" << "\t" << "A" << endl;
        cout << setw(40) << "List details for specific Order number" << "\t" << "O" << endl;
        cout << setw(40) << "Display summary by Region" << "\t" << "R" << endl;
        cout << setw(40) << "Display summary by Stone code" << "\t" << "S" << endl;
        cout << setw(40) << "Clear all vectors" << "\t" << "C" << endl;
        cout << setw(40) << "Quit" << "\t" << "Q" << endl;
        cout << endl;
        cout << "Please choose an option from the menu and enter the code: ";
        cin >> choice;
        cout << endl;
    }
    
    return choice;
}


/********************************************************************************
 *                                                                              *
 *                               Upload File                                    *
 *                                                                              *
 ********************************************************************************/

void uploadFile(string fName, bool &loadSuccess, vector<char> &sCode, vector<double> &len,
                vector<double> &dep, vector<double> &hei, vector<int> &lenF, vector<int> &depF, 
                vector<string> &oNum, vector<string> &reg)
{
    //variables for reading a file
    ifstream inFile;

    //order date variables
    int ODYear = 0;
    int ODMonth = 0;
    int ODDay = 0;
    
    //delivery date variables
    int DDYear = 0;
    int DDMonth = 0;
    int DDDay = 0;
    
    //variable for slash between date
    char ch = ' '; 
    
    //variable to read over first line and "get it over with"
    string firstLine = " ";
    
    //variable to read rest of line (address, state code, name, etc)
    string restOfLine = " ";

    //data and calculation variables
    char stoneCode = ' ';
    double length = 0.0;
    double depth = 0.0;
    double height = 0.0;
    int numLengthEdgesFinished = 0;
    int numDepthEdgesFinished = 0;
    double minHeight = 0.0;
    double maxHeight = 0.0;
    string orderNumber = "";
    string stateCode = "";
    string region = "";
    string nameAddress = "";
            
    //variables to count number of records with errors
    int totalErrorCount = 0;
    int OrderDeliverySame = 0;
    int DeliveryDateTooFar = 0;
    int invalidStoneCode = 0;
    int invalidLength = 0;
    int invalidDepth = 0;
    int invalidHeight =0;
    int invalidLengthEdges = 0;
    int invalidDepthEdges = 0;
    
    //variables to count number of records without errors
    int marbleRecords = 0;
    int graniteRecords = 0;
    int quartzRecords = 0;
    int totalNonError = 0;
    int totalRecords = 0;

    //total count of all errors in all records
    int totalErrors = 0;

    //count of records with multiple errors
    int multipleErrorRecords = 0;

    
    //OPEN FILE
    inFile.open(fName.c_str());

    if(!inFile)
    {
        cout << "Error loading the file." << endl;
        cout << endl;
    }
    else
    {
        //PRINT HEADINGS
        cout << setw(8)<< "Order" << setw(17) << "Delivery" << setw(8) << "S";
        cout << setw(48) << "L" << "\t";
        cout << "D" << endl;
        cout << setw(8) << "Date" << setw(17) << "Date" <<"\t" << "C" << setw(15) << "Len.";
        cout << setw(14) << "Dep." << setw(12) << "Hei." << "\t" << "E" << "\t" << "E" << endl;
        cout << "_____________________________________________________________________________";
        cout << "__________________________________________\n";
        
        //read and ignore column headings
        getline(inFile, firstLine);
        
        //process the file until end of the file is reached
        while (inFile >> ODYear >> ch >> ODMonth >> ch >> ODDay >> DDYear >> ch 
                >> DDMonth >> ch >> DDDay >> stoneCode >> length >> depth >> height
                >> numLengthEdgesFinished >> numDepthEdgesFinished >> orderNumber >> region 
                >> stateCode && getline(inFile, nameAddress))
        {
            //count number of total records in the file
            totalRecords++;
            
            //print data            
            //print order date
            cout << ODYear << ch;
            if(ODMonth <=9)
            {
                cout << "0" << ODMonth << ch;
            }
            else
            {
                cout << ODMonth << ch;
            }
            
            if(ODDay <=9)
            {
                cout << "0" << ODDay << "\t";
            }
            else
            {
                cout << ODDay << "\t";
            }
            
            //print delivery date
            cout << DDYear << ch;
            if(DDMonth <=9)
            {
                cout << "0" << DDMonth << ch;
            }
            else
            {
                cout << DDMonth << ch;
            }
            
            if(DDDay <=9)
            {
                cout << "0" << DDDay << "\t";
            }
            else
            {
                cout << DDDay << "\t";
            }
            
            cout << stoneCode << "\t";
            cout << fixed << setprecision(2) << setw(8) << length << "\t" << setw(6) << depth;
            cout << "\t" << setw(10) << height << "\t";
            cout << numLengthEdgesFinished << "\t" << numDepthEdgesFinished << "\t";
            
            /*         
            Test data validity and display error messages as necessary.
            
            Variable to count number of errors within one record
            in the while loop because it must be reset before reading every record
            to count number of errors within each record
            */
            
            int individualErrorCount = 0;
            
            //order date and delivery date are equal
            if(ODYear == DDYear && ODMonth == DDMonth && ODDay == DDDay)
            {
                cout << endl;
                cout << "\t";
                cout << "ERROR: order date and delivery date are equal.";
                individualErrorCount ++;
                OrderDeliverySame ++;
                totalErrors ++;
            }
            
            //order date and delivery date are too far apart
            
            if(DDYear >= ODYear && DDYear < ODYear + TWO_YEAR_DIFFERENCE)
            {
                if (DDYear == ODYear)
                {
                    if(DDMonth-ODMonth > FOUR_MONTH_DIFFERENCE)
                    {
                        cout << endl;
                        cout << "\t";
                        cout << "ERROR: order date and delivery date are too far apart.";
                        individualErrorCount ++;                       
                        DeliveryDateTooFar ++;
                        totalErrors ++;
                    } 
                }
                if (DDYear == ODYear + ONE_YEAR_DIFFERENCE)
                {
                    if(DDMonth-ODMonth >= FOUR_MONTH_DIFFERENCE_NEW_YEAR 
                            && DDMonth-ODMonth < TWELVE_MONTH_DIFFERENCE)
                    {
                        cout << endl;
                        cout << "\t";
                        cout << "ERROR: order date and delivery date are too far apart.";
                        individualErrorCount ++;
                        DeliveryDateTooFar ++;
                        totalErrors ++;
                    }
                }
            }
            else if(DDYear >= ODYear + TWO_YEAR_DIFFERENCE)
            {
                cout << endl;
                cout << "\t";
                cout << "ERROR: order date and delivery date are too far apart.";
                individualErrorCount ++;
                DeliveryDateTooFar ++;
                totalErrors ++;
            }
            

            //test stone type validity - stone code must be g, G, m, M, q, or Q
            if((toupper(stoneCode)!= 'G')&&(toupper(stoneCode)!= 'M')
               &&(toupper(stoneCode)!= 'Q'))
            {
                cout << endl;
                cout << "\t" << "ERROR: stone code is not a valid value.";
                individualErrorCount ++;
                invalidStoneCode ++;
                totalErrors ++;
            }
            
            //test length validity - MIN_LENGTH < length < MAX_LENGTH
            if((length < MIN_LENGTH) || (length > MAX_LENGTH))
            {
                cout << endl;
                cout << "\t" << "ERROR: Invalid length.";    
                individualErrorCount ++;
                invalidLength ++;
                totalErrors ++;
            }
            
            
            //test depth validity - MIN_DEPTH < depth < MAX_DEPTH and depth <=length
            if((depth < MIN_DEPTH) || (depth > MAX_DEPTH) || (depth > length))
            {
                cout << endl;
                cout << "\t" << "ERROR: Invalid depth.";
                individualErrorCount ++;
                invalidDepth ++;
                totalErrors ++;
            }
            
            //initialize range for min and max height
            minHeight = MIN_HEIGHT_FACTOR*depth;
            maxHeight = MAX_HEIGHT_FACTOR*depth;
            
            //test height entry validity
            if((height < minHeight) || (height > maxHeight))
            {
                cout << endl;
                cout << "\t" << "ERROR: Invalid height value."; 
                individualErrorCount ++;
                invalidHeight ++;
                totalErrors ++;
            }
            
            //test for validity of number of finished length edges
            if(numLengthEdgesFinished < MIN_EDGES_FINISHED
                    || numLengthEdgesFinished > MAX_EDGES_FINISHED)
            {
                cout << endl;
                cout << "\t";
                cout << "ERROR: The number of length edges you want ";
                cout << "finished is out of our range.";

                individualErrorCount ++;
                invalidLengthEdges ++;
                totalErrors ++;
            }
            
            //test for validity of number of finished depth edges
            if(numDepthEdgesFinished < MIN_EDGES_FINISHED
                    || numDepthEdgesFinished > MAX_EDGES_FINISHED)
            {
                cout << endl;
                cout << "\t";
                cout << "ERROR: The number of depth edges you want ";
                cout << "finished is out of our range.";
                individualErrorCount ++;
                invalidDepthEdges ++;
                totalErrors ++;
            }

            
            if (individualErrorCount > ZERO_ERRORS) 
            {
                cout << endl;
                totalErrorCount ++;
                if (individualErrorCount > ONE_ERROR)
                {
                    multipleErrorRecords ++;                    
                }
            }            
            else
            {
                //if the record has no error, then count it toward total number of
                //records without errors
                totalNonError++;
                
                //if row of data passes all validation checks, add data to appropriate vectors
                sCode.push_back(stoneCode);
                len.push_back(length);
                dep.push_back(depth);
                hei.push_back(height);
                lenF.push_back(numLengthEdgesFinished);
                depF.push_back(numDepthEdgesFinished);
                oNum.push_back(orderNumber);
                reg.push_back(region);

                cout << "\t";
                cout << endl;
            }
        } //END while loop
        
        
        //close the file
        inFile.close();
        
        
        //print out summary data
        cout << endl;
        cout << "Counts: " << "\t";
        cout << "Total Records = " << totalRecords << "\t";
        cout << "Records with Errors = " << totalErrorCount <<  "\t";
        cout << "Records without Errors = " << totalNonError << "\t" << endl;
        cout << endl;
        
        
        cout << "\t\t" << "*****************************************************" << endl;
        cout << "\t\t" << "*               Count of Overall Errors             *" << endl;
        cout << "\t\t" << "*****************************************************" << endl;
        cout << endl;
        
        cout << setw(25) << totalErrorCount << " - records with errors." << endl;
        cout << setw(25) << totalNonError << " - records without errors." << endl;
        cout << "\t\t" << "____________________________________________________" << endl;
        cout << setw(25) << totalRecords << " - total records." << endl;
        cout << endl;

        
        cout << "\t\t" << "*****************************************************" << endl;
        cout << "\t\t" << "*             Count of Individual Errors            *" << endl;
        cout << "\t\t" << "*****************************************************" << endl;
        cout << endl;
        
        cout << setw(25) << OrderDeliverySame << " - order date and delivery date same" << endl;
        cout << setw(25) << DeliveryDateTooFar << " - delivery date too far in future" << endl;
        cout << setw(25) << invalidStoneCode << " - stone code not valid." << endl;
        cout << setw(25) << invalidLength << " - length not valid" << endl;
        cout << setw(25) << invalidDepth << " - depth not valid" << endl;
        cout << setw(25) << invalidHeight << " - height not valid" << endl;
        cout << setw(25) << invalidLengthEdges << " - length edges to finish not valid" << endl;
        cout << setw(25) << invalidDepthEdges << " - depth edges to finish not valid" << endl;
        cout << "\t\t" << "____________________________________________________" << endl;
        cout << setw(25) << totalErrors << " - total count of all errors in all records" << endl;
        cout << setw(25) << multipleErrorRecords;
        cout << " - count of records with multiple errors" << endl;
        cout << endl;
        cout << endl;
        
        cout << setw(25) << totalNonError << " added to vectors,   ";
        cout << sCode.size() << " total records now loaded." << endl;
        cout << endl;
        cout << endl;
        
    } //END else part of if(!inputFile) 
    
    //set boolean variable LOADSUCCESS
    if(sCode.size()>0)
    {
        loadSuccess = true;
    }
    else
    {
        loadSuccess = false;
    }    
}


/********************************************************************************
 *                                                                              *
 *                           Display All Details                                *
 *                                                                              *
 ********************************************************************************/

void allDetails(const vector<char> &sCode, const vector<double> &len,
                const vector<double> &dep, const vector<double> &hei,
                const vector<int> &lenF, const vector<int> &depF, 
                const vector<string> &oNum, const vector<string> &reg)
{
    char stoneCode = ' ';
    double stonePriceRate = 0.0;
    double length = 0.0;
    double depth = 0.0;
    double height = 0.0;
    int numLengthEdgesFinished = 0;
    int numDepthEdgesFinished = 0;
    double totalFinishingLength = 0.0;
    double counterArea = 0.0;
    double totalMaterialSqFt = 0.0;
    double totalMaterialCost = 0.0;
    double edgeFinishingCost = 0.0;
    double totalCost = 0.0;

    
    //total square feet
    double totalSqFtMarble = 0.0;
    double totalSqFtGranite = 0.0;
    double totalSqFtQuartz = 0.0;
    
    
    //number of records for each stone type
    int graniteRecords = 0;
    int quartzRecords = 0;
    int marbleRecords = 0;
    
    //total cost
    double totalCostMarble = 0.0;
    double totalCostGranite = 0.0;
    double totalCostQuartz = 0.0;
    
    int totalRecords = 0;
    
    //PRINT HEADINGS
    cout << setw(13) << "Order" << setw(17) << "S" << setw(37) << "L";
    cout << setw(7) <<  "D" << setw(12) << "Sq." << setw(16) << "Total" << endl;
    
    
    cout << setw(13) << "Number" << setw(10) << "Region" << setw(7) << "C";
    cout << "\t" << setw(8) << "Len." << setw(10) << "Dep.";
    cout << setw(10) << "Hei." << setw(7)<< "E";
    cout << setw(7) << "E"<< setw(12) << "Ft." << setw(16) << "Cost" << endl;
    cout << "______________________________________________________________";
    cout << "_________________________________________________________\n";
    cout << endl;

    //print all VALID data and calculated data WITHOUT DATES
    for(int i = 0; i<sCode.size(); i++)
    {
        totalRecords++;
        cout << fixed << setprecision(2);
        cout << setw(13) << oNum.at(i) << setw(10) << reg.at(i) << setw(7);
        cout << sCode.at(i);
        cout << setw(10) << len.at(i) << setw(10) << dep.at(i);
        cout << setw(10) << hei.at(i) << setw(7);
        cout << lenF.at(i) << setw(7) << depF.at(i);
        
        
        length = len.at(i);
        depth = dep.at(i);
        height = hei.at(i);
        numLengthEdgesFinished = lenF.at(i);
        numDepthEdgesFinished = depF.at(i);
        //print data            
            
        //set price rates for stone
        //if stone is Granite
        if(toupper(sCode.at(i)) == 'G')
        {
            stonePriceRate = GRANITE_PRICE;
        }
        //if stone is Marble
        if(toupper(sCode.at(i)) == 'M')
        {
            stonePriceRate = MARBLE_PRICE;
        }
        //if stone is Quartz
        if(toupper(sCode.at(i)) == 'Q')
        {
            stonePriceRate = QUARTZ_PRICE;
        }
        
        //calculate total square feet and total cost
        counterArea = length * height;

        //calculate total square feet of material and round up to nearest whole number
        totalMaterialSqFt = ceil(counterArea * (1 + WASTAGE_PERCENT));

        totalMaterialCost = totalMaterialSqFt * stonePriceRate;
        totalFinishingLength = numLengthEdgesFinished * length + 
                               numDepthEdgesFinished * depth;
        edgeFinishingCost = totalFinishingLength * EDGE_FINISHING_RATE;
        totalCost = totalMaterialCost + edgeFinishingCost;
        
        //print total square feet and total cost in the data table 
        //if all values are valid
        cout << setw(12) << totalMaterialSqFt;
        cout << setw(16) << totalCost << endl;

        if(toupper(sCode.at(i)) == 'G')
        {
            graniteRecords++;
            //total cost of granite = sum of total cost for each granite record
            totalCostGranite += totalCost;
            //total square feet of granite = sum of total sq ft of granite in each
            //granite record
            totalSqFtGranite += totalMaterialSqFt;
        }
        else if(toupper(sCode.at(i)) == 'M')
        {
            marbleRecords++;
            totalCostMarble += totalCost;
            totalSqFtMarble += totalMaterialSqFt;
        }
        else if(toupper(sCode.at(i)) == 'Q')
        {
            quartzRecords++;
            totalCostQuartz += totalCost;
            totalSqFtQuartz += totalMaterialSqFt;
        }
    }

    //print out summary data
    cout << endl;
    cout << "Counts: " << "\t";
    cout << "Total Records = " << totalRecords << "\t";
    cout << endl;
     
    cout << "\t\t\t" << "TOTALS" << endl;
    cout << setw(15) << "Stone" << setw(15) << "Count" << setw(20) << "Square Feet";
    cout << setw(25) << "Cost" << endl;
    cout << "______________________________________________________________________________";
    cout << "____________________";
    cout << endl;
        
        
    //print marble data
    cout << setw(15) << "Marble" << setw(15) << marbleRecords;
    cout << setw(20) << totalSqFtMarble << setw(30) <<totalCostMarble;
    cout << endl;
    
        
    //print granite data
    cout << setw(15) << "Granite" << setw(15) << graniteRecords;
    cout << setw(20) << totalSqFtGranite << setw(30) <<totalCostGranite;
    cout << endl;
        
        
    //print quartz data
    cout << setw(15) << "Quartz" << setw(15) << quartzRecords;
    cout << setw(20) << totalSqFtQuartz << setw(30) << totalCostQuartz;
    cout << endl;     
    cout << "______________________________________________________________________________";
    cout << "____________________" << endl;
    cout << endl;
}



/********************************************************************************
 *                                                                              *
 *                       Display Specific Order Detail                          *
 *                                                                              *
 ********************************************************************************/

void orderDetails(const vector<char> &sCode, const vector<double> &len, 
                  const vector<double> &dep, const vector<double> &hei,
                  const vector<int> &lenF, const vector<int> &depF, 
                  const vector<string> &oNum, const vector<string> &reg)
{
    double stonePriceRate = 0.0;
    double length = 0.0;
    double depth = 0.0;
    double height = 0.0;
    int numLengthEdgesFinished = 0;
    int numDepthEdgesFinished = 0;
    double totalFinishingLength = 0.0;
    double counterArea = 0.0;
    double totalMaterialSqFt = 0.0;
    double totalMaterialCost = 0.0;
    double edgeFinishingCost = 0.0;
    double totalCost = 0.0;

    
    string orderNumberData = " ";
    bool matchNotFound = true;
    string orderNumberUser = " ";
    cout << "Please enter the order number of the order you want to see: ";
    cin >> orderNumberUser;
    
    //PRINT HEADINGS
    cout << setw(13) << "Order" << setw(17) << "S" << setw(37) << "L";
    cout << setw(7) <<  "D" << setw(12) << "Sq." << setw(16) << "Total" << endl;
    
    
    cout << setw(13) << "Number" << setw(10) << "Region" << setw(7) << "C";
    cout << "\t" << setw(8) << "Len." << setw(10) << "Dep.";
    cout << setw(10) << "Hei." << setw(7)<< "E";
    cout << setw(7) << "E"<< setw(12) << "Ft." << setw(16) << "Cost" << endl;
    cout << "______________________________________________________________";
    cout << "_________________________________________________________\n";
    cout << endl;
    
    for(int i=0; i<oNum.size(); i++)
    {
        if(oNum.at(i) == orderNumberUser)
        {
            cout << fixed << setprecision(2);
            cout << setw(13) << oNum.at(i) << setw(10) << reg.at(i) << setw(7);
            cout << sCode.at(i);
            cout << setw(10) << len.at(i) << setw(10) << dep.at(i);
            cout << setw(10) << hei.at(i) << setw(7);
            cout << lenF.at(i) << setw(7) << depF.at(i);

            length = len.at(i);
            depth = dep.at(i);
            height = hei.at(i);
            numLengthEdgesFinished = lenF.at(i);
            numDepthEdgesFinished = depF.at(i);
            //print data            

            //set price rates for stone
            //if stone is Granite
            if(toupper(sCode.at(i)) == 'G')
            {
                stonePriceRate = GRANITE_PRICE;
            }
            //if stone is Marble
            if(toupper(sCode.at(i)) == 'M')
            {
                stonePriceRate = MARBLE_PRICE;
            }
            //if stone is Quartz
            if(toupper(sCode.at(i)) == 'Q')
            {
                stonePriceRate = QUARTZ_PRICE;
            }

            //calculate total square feet and total cost
            counterArea = length * height;

            //calculate total square feet of material and round up to nearest whole number
            totalMaterialSqFt = ceil(counterArea * (1 + WASTAGE_PERCENT));

            totalMaterialCost = totalMaterialSqFt * stonePriceRate;
            totalFinishingLength = numLengthEdgesFinished * length + 
                                   numDepthEdgesFinished * depth;
            edgeFinishingCost = totalFinishingLength * EDGE_FINISHING_RATE;
            totalCost = totalMaterialCost + edgeFinishingCost;

            //print total square feet and total cost in the data table 
            //if all values are valid
            cout << setw(12) << totalMaterialSqFt;
            cout << setw(16) << totalCost << endl;
            cout << endl;

            orderNumberData = orderNumberUser;
            matchNotFound = false;
        }
    }
    
    if(orderNumberData == " " && matchNotFound == true)
    {
        cout << "Order number not found." << endl;
        cout << endl;
    }
}


/********************************************************************************
 *                                                                              *
 *                     Display a Summary by Stone Code                          *
 *                                                                              *
 ********************************************************************************/

void summaryByStone(const vector<char> &sCode, const vector<double> &len,
                    const vector<double> &dep, const vector<double> &hei,
                    const vector<int> &lenF, const vector<int> &depF, 
                    const vector<string> &oNum, const vector<string> &reg)
{
    double stonePriceRate = 0.0;
    double length = 0.0;
    double depth = 0.0;
    double height = 0.0;
    int numLengthEdgesFinished = 0;
    int numDepthEdgesFinished = 0;
    double totalFinishingLength = 0.0;
    double counterArea = 0.0;
    double totalMaterialSqFt = 0.0;
    double totalMaterialCost = 0.0;
    double edgeFinishingCost = 0.0;
    double totalCost = 0.0;


    //total square feet
    double totalSqFtMarble = 0.0;
    double totalSqFtGranite = 0.0;
    double totalSqFtQuartz = 0.0;
    
    
    //number of records for each stone type
    int graniteRecords = 0;
    int quartzRecords = 0;
    int marbleRecords = 0;
    
    //total cost
    double totalCostMarble = 0.0;
    double totalCostGranite = 0.0;
    double totalCostQuartz = 0.0;
    
    int totalRecords = 0;
    
    //print the granite records
    for(int i = 0; i<sCode.size(); i++)
    {
        if(toupper(sCode.at(i))=='G')
        {
            totalRecords++;
            graniteRecords++;

            length = len.at(i);
            depth = dep.at(i);
            height = hei.at(i);
            numLengthEdgesFinished = lenF.at(i);
            numDepthEdgesFinished = depF.at(i);
            
            //set price rates for stone
            stonePriceRate = GRANITE_PRICE;

            //calculate total square feet and total cost
            counterArea = length * height;
            //calculate total square feet of material and round up to nearest whole number
            totalMaterialSqFt = ceil(counterArea * (1 + WASTAGE_PERCENT));

            totalMaterialCost = totalMaterialSqFt * stonePriceRate;
            totalFinishingLength = numLengthEdgesFinished * length + 
                                   numDepthEdgesFinished * depth;
            edgeFinishingCost = totalFinishingLength * EDGE_FINISHING_RATE;
            totalCost = totalMaterialCost + edgeFinishingCost;

            //total cost of granite = sum of total cost for each granite record
            totalCostGranite += totalCost;
            //total square feet of granite = sum of total sq ft of granite in each
            //granite record
            totalSqFtGranite += totalMaterialSqFt;
        }
    }
    
    //print the quartz records
    for(int i = 0; i<sCode.size(); i++)
    {   
        if(toupper(sCode.at(i))=='Q')
        {
            totalRecords++;
            quartzRecords++;
            
            length = len.at(i);
            depth = dep.at(i);
            height = hei.at(i);
            numLengthEdgesFinished = lenF.at(i);
            numDepthEdgesFinished = depF.at(i);

            //set price rates for stone
            stonePriceRate = QUARTZ_PRICE;

            //calculate total square feet and total cost
            counterArea = length * height;
            //calculate total square feet of material and round up to nearest whole number
            totalMaterialSqFt = ceil(counterArea * (1 + WASTAGE_PERCENT));

            totalMaterialCost = totalMaterialSqFt * stonePriceRate;
            totalFinishingLength = numLengthEdgesFinished * length + 
                                   numDepthEdgesFinished * depth;
            edgeFinishingCost = totalFinishingLength * EDGE_FINISHING_RATE;
            totalCost = totalMaterialCost + edgeFinishingCost;

            totalCostQuartz += totalCost;
            totalSqFtQuartz += totalMaterialSqFt;
        }
    }

    //print the marble records 
    for(int i = 0; i<sCode.size(); i++)
    {
        if(toupper(sCode.at(i))=='M')
        {
            totalRecords++;
            marbleRecords++;
            
            length = len.at(i);
            depth = dep.at(i);
            height = hei.at(i);
            numLengthEdgesFinished = lenF.at(i);
            numDepthEdgesFinished = depF.at(i);

            //set price rates for stone
            stonePriceRate = MARBLE_PRICE;

            //calculate total square feet and total cost
            counterArea = length * height;
            //calculate total square feet of material and round up to nearest whole number
            totalMaterialSqFt = ceil(counterArea * (1 + WASTAGE_PERCENT));

            totalMaterialCost = totalMaterialSqFt * stonePriceRate;
            totalFinishingLength = numLengthEdgesFinished * length + 
                                   numDepthEdgesFinished * depth;
            edgeFinishingCost = totalFinishingLength * EDGE_FINISHING_RATE;
            totalCost = totalMaterialCost + edgeFinishingCost;

            totalCostMarble += totalCost;
            totalSqFtMarble += totalMaterialSqFt;
        }
    }
    
    //print out summary data
    cout << endl;
    cout << "Counts: " << "\t";
    cout << "Total Records = " << totalRecords << "\t";
    cout << endl;
     
    cout << setw(25) << "TOTALS (All Loaded Files)" << endl;
    cout << setw(15) << "Stone" << setw(15) << "Count" << setw(20) << "Square Feet";
    cout << setw(15) << "Cost" << endl;
    cout << "______________________________________________________________________________";
    cout << "____________________";
    cout << endl;
        
        
    //print marble data
    cout << setw(15) << "Marble" << setw(15) << marbleRecords;
    cout << setw(20) << totalSqFtMarble << setw(20) <<totalCostMarble;
    cout << endl;
    
        
    //print granite data
    cout << setw(15) << "Granite" << setw(15) << graniteRecords;
    cout << setw(20) << totalSqFtGranite << setw(20) <<totalCostGranite;
    cout << endl;
        
        
    //print quartz data
    cout << setw(15) << "Quartz" << setw(15) << quartzRecords;
    cout << setw(20) << totalSqFtQuartz << setw(20) << totalCostQuartz;
    cout << endl;     
    cout << "______________________________________________________________________________";
    cout << "____________________" << endl;
    cout << endl;
}   

/********************************************************************************
 *                                                                              *
 *                     Display a Summary by Region                              *
 *                                                                              *
 ********************************************************************************/

void summaryByRegion(const vector<char> &sCode, const vector<double> &len,
                     const vector<double> &dep, const vector<double> &hei,
                     const vector<int> &lenF, const vector<int> &depF, 
                     const vector<string> &oNum, const vector<string> &reg)
{
    double stonePriceRate = 0.0;
    double length = 0.0;
    double depth = 0.0;
    double height = 0.0;
    int numLengthEdgesFinished = 0;
    int numDepthEdgesFinished = 0;
    double totalFinishingLength = 0.0;
    double counterArea = 0.0;
    double totalMaterialSqFt = 0.0;
    double totalMaterialCost = 0.0;
    double edgeFinishingCost = 0.0;
    double totalCost = 0.0;

    
    //variables to count number of records without errors
    int totalRecords = 0;
    int northRecords = 0;
    int eastRecords = 0;
    int southRecords = 0;
    int westRecords = 0;
    int otherRecords = 0;
    
    //total square feet
    double totalSqFtNorth = 0.0;
    double totalSqFtEast = 0.0;
    double totalSqFtSouth = 0.0;
    double totalSqFtWest = 0.0;
    double totalSqFtOther = 0.0;
    
    //total cost
    double totalCostNorth = 0.0;
    double totalCostEast = 0.0;
    double totalCostSouth = 0.0;
    double totalCostWest = 0.0;
    double totalCostOther = 0.0;
    
    
    //PRINT DATA BY REGION
    
    //NORTH RECORDS
    for(int i = 0; i<reg.size(); i++)
    {

        if(reg.at(i) == NORTH)
        {
            totalRecords++;
            northRecords++;
            
            length = len.at(i);
            depth = dep.at(i);
            height = hei.at(i);
            numLengthEdgesFinished = lenF.at(i);
            numDepthEdgesFinished = depF.at(i);          

            //set price rates for stone
            //if stone is Granite
            if(toupper(sCode.at(i)) == 'G')
            {
                stonePriceRate = GRANITE_PRICE;
            }
            //if stone is Marble
            if(toupper(sCode.at(i)) == 'M')
            {
                stonePriceRate = MARBLE_PRICE;
            }
            //if stone is Quartz
            if(toupper(sCode.at(i)) == 'Q')
            {
                stonePriceRate = QUARTZ_PRICE;
            }

            //calculate total square feet and total cost
            counterArea = length * height;

            //calculate total square feet of material and round up to nearest whole number
            totalMaterialSqFt = ceil(counterArea * (1 + WASTAGE_PERCENT));

            totalMaterialCost = totalMaterialSqFt * stonePriceRate;
            
            totalFinishingLength = numLengthEdgesFinished * length + 
                                   numDepthEdgesFinished * depth;
            
            edgeFinishingCost = totalFinishingLength * EDGE_FINISHING_RATE;
            totalCost = totalMaterialCost + edgeFinishingCost;

            totalCostNorth +=totalCost;
            totalSqFtNorth +=totalMaterialSqFt;
        }
    }
    
    //SOUTH RECORDS
    for(int i = 0; i<reg.size(); i++)
    {
        if(reg.at(i) == SOUTH)
        {
            totalRecords++;
            southRecords++;
            
            length = len.at(i);
            depth = dep.at(i);
            height = hei.at(i);
            numLengthEdgesFinished = lenF.at(i);
            numDepthEdgesFinished = depF.at(i);

            //set price rates for stone
            //if stone is Granite
            if(toupper(sCode.at(i)) == 'G')
            {
                stonePriceRate = GRANITE_PRICE;
            }
            //if stone is Marble
            if(toupper(sCode.at(i)) == 'M')
            {
                stonePriceRate = MARBLE_PRICE;
            }
            //if stone is Quartz
            if(toupper(sCode.at(i)) == 'Q')
            {
                stonePriceRate = QUARTZ_PRICE;
            }

            //calculate total square feet and total cost
            counterArea = length * height;

            //calculate total square feet of material and round up to nearest whole number
            totalMaterialSqFt = ceil(counterArea * (1 + WASTAGE_PERCENT));

            totalMaterialCost = totalMaterialSqFt * stonePriceRate;
            
            totalFinishingLength = numLengthEdgesFinished * length + 
                                   numDepthEdgesFinished * depth;
            
            edgeFinishingCost = totalFinishingLength * EDGE_FINISHING_RATE;
            
            totalCost = totalMaterialCost + edgeFinishingCost;

            totalCostSouth +=totalCost;
            totalSqFtSouth +=totalMaterialSqFt;
        }
    }
    
    //EAST RECORDS
    for(int i = 0; i<reg.size(); i++)
    {
        if(reg.at(i) == EAST)
        {
            totalRecords++;
            eastRecords++;
            
            length = len.at(i);
            depth = dep.at(i);
            height = hei.at(i);
            numLengthEdgesFinished = lenF.at(i);
            numDepthEdgesFinished = depF.at(i);
                        
            //set price rates for stone
            //if stone is Granite
            if(toupper(sCode.at(i)) == 'G')
            {
                stonePriceRate = GRANITE_PRICE;
            }
            //if stone is Marble
            if(toupper(sCode.at(i)) == 'M')
            {
                stonePriceRate = MARBLE_PRICE;
            }
            //if stone is Quartz
            if(toupper(sCode.at(i)) == 'Q')
            {
                stonePriceRate = QUARTZ_PRICE;
            }

            //calculate total square feet and total cost
            counterArea = length * height;

            //calculate total square feet of material and round up to nearest whole number
            totalMaterialSqFt = ceil(counterArea * (1 + WASTAGE_PERCENT));
            
            totalMaterialCost = totalMaterialSqFt * stonePriceRate;            
            
            totalFinishingLength = numLengthEdgesFinished * length + 
                                   numDepthEdgesFinished * depth;            
            
            edgeFinishingCost = totalFinishingLength * EDGE_FINISHING_RATE;            
            
            totalCost = totalMaterialCost + edgeFinishingCost;            
            
            totalCostEast +=totalCost;
            totalSqFtEast +=totalMaterialSqFt;
        }
    }

    //WEST RECORDS
    for(int i = 0; i<reg.size(); i++)
    {
        if(reg.at(i) == WEST)
        {
            totalRecords++;
            westRecords++;

            length = len.at(i);
            depth = dep.at(i);
            height = hei.at(i);
            numLengthEdgesFinished = lenF.at(i);
            numDepthEdgesFinished = depF.at(i);

            //set price rates for stone
            //if stone is Granite
            if(toupper(sCode.at(i)) == 'G')
            {
                stonePriceRate = GRANITE_PRICE;
            }
            //if stone is Marble
            if(toupper(sCode.at(i)) == 'M')
            {
                stonePriceRate = MARBLE_PRICE;
            }
            //if stone is Quartz
            if(toupper(sCode.at(i)) == 'Q')
            {
                stonePriceRate = QUARTZ_PRICE;
            }

            //calculate total square feet and total cost
            counterArea = length * height;

            //calculate total square feet of material and round up to nearest whole number
            totalMaterialSqFt = ceil(counterArea * (1 + WASTAGE_PERCENT));

            totalMaterialCost = totalMaterialSqFt * stonePriceRate;
            
            totalFinishingLength = numLengthEdgesFinished * length + 
                                   numDepthEdgesFinished * depth;
            
            edgeFinishingCost = totalFinishingLength * EDGE_FINISHING_RATE;
            
            totalCost = totalMaterialCost + edgeFinishingCost;

            totalCostWest +=totalCost;
            totalSqFtWest +=totalMaterialSqFt;
        }   
    }
    
    //OTHER RECORDS
    for(int i = 0; i<reg.size(); i++)
    {
        if(reg.at(i) == OTHER)
        {
            totalRecords++;
            otherRecords++;

            length = len.at(i);
            depth = dep.at(i);
            height = hei.at(i);
            numLengthEdgesFinished = lenF.at(i);
            numDepthEdgesFinished = depF.at(i);
            
            //set price rates for stone
            //if stone is Granite
            if(toupper(sCode.at(i)) == 'G')
            {
                stonePriceRate = GRANITE_PRICE;
            }
            //if stone is Marble
            if(toupper(sCode.at(i)) == 'M')
            {
                stonePriceRate = MARBLE_PRICE;
            }
            //if stone is Quartz
            if(toupper(sCode.at(i)) == 'Q')
            {
                stonePriceRate = QUARTZ_PRICE;
            }

            //calculate total square feet and total cost
            counterArea = length * height;

            //calculate total square feet of material and round up to nearest whole number
            totalMaterialSqFt = ceil(counterArea * (1 + WASTAGE_PERCENT));

            totalMaterialCost = totalMaterialSqFt * stonePriceRate;
            
            totalFinishingLength = numLengthEdgesFinished * length + 
                                   numDepthEdgesFinished * depth;
            
            edgeFinishingCost = totalFinishingLength * EDGE_FINISHING_RATE;
            
            totalCost = totalMaterialCost + edgeFinishingCost;
            
            totalCostOther+=totalCost;
            totalSqFtOther +=totalMaterialSqFt;
        }   
    }

    //print out summary data
    cout << endl;
    cout << "Counts: " << "\t";
    cout << "Total Records = " << totalRecords << "\t";
    cout << endl;
     
    cout << setw(25) << "TOTALS (All Loaded Files)" << endl;
    cout << setw(15) << "Region" << setw(15) << "Count" << setw(20) << "Square Feet";
    cout << setw(15) << "Cost" << endl;
    cout << "______________________________________________________________________________";
    cout << "____________________";
    cout << endl;
        
        
    //print North data
    cout << setw(15) << "North" << setw(15) << northRecords;
    cout << setw(20) << totalSqFtNorth << setw(20) <<totalCostNorth;
    cout << endl;
    
    //print South data
    cout << setw(15) << "South" << setw(15) << southRecords;
    cout << setw(20) << totalSqFtSouth << setw(20) << totalCostSouth;
    cout << endl;
    
    //print East data
    cout << setw(15) << "East" << setw(15) << eastRecords;
    cout << setw(20) << totalSqFtEast << setw(20) <<totalCostEast;
    cout << endl;

    //print West data
    cout << setw(15) << "West" << setw(15) << westRecords;
    cout << setw(20) << totalSqFtWest << setw(20) <<totalCostWest;
    cout << endl;
    
    //print Other data
    cout << setw(15) << "Other" << setw(15) << otherRecords;
    cout << setw(20) << totalSqFtOther << setw(20) <<totalCostOther;
    cout << endl;
    
    cout << "______________________________________________________________________________";
    cout << "____________________" << endl;
    cout << endl;
}
    

/********************************************************************************
 *                                                                              *
 *                             Clear All Vectors                                *
 *                                                                              *
 ********************************************************************************/

bool clearAllVectors(vector<char> &sCode, vector<double> &len, vector<double> &dep, 
                     vector<double> &hei, vector<int> &lenF, vector<int> &depF, 
                     vector<string> &oNum, vector<string> &reg)
{
    bool vectorsCleared = false;
    sCode.clear();
    len.clear();
    dep.clear();
    hei.clear();
    lenF.clear();
    depF.clear();
    oNum.clear();
    reg.clear();
    cout << "All vectors have been cleared." << endl;

    
    if(sCode.size()!=0 && len.size()!=0 && dep.size()!=0  && hei.size()!=0 && lenF.size()!=0
        && depF.size()!=0 && oNum.size()!=0 && reg.size()!=0)
    {
        for(int i = sCode.size()-1; i>=0; i--)
        {
            sCode.pop_back();
        }
        
        for(int i = len.size()-1; i>=0; i--)
        {
            len.pop_back();
        }
        
        for(int i = dep.size()-1; i>=0; i--)
        {
            dep.pop_back();
        }
        
        for(int i = hei.size()-1; i>=0; i--)
        {
            hei.pop_back();
        }
        
        for(int i = lenF.size()-1; i>=0; i--)
        {
            lenF.pop_back();
        }
        
        for(int i = depF.size()-1; i>=0; i--)
        {
            depF.pop_back();
        }
        
        for(int i = oNum.size()-1; i>=0; i--)
        {
            oNum.pop_back();
        }
        
        for(int i = reg.size()-1; i>=0; i--)
        {
            reg.pop_back();
        }
    }
    cout << endl;
    if(sCode.size()==0 && len.size()==0 && dep.size()==0  && hei.size()==0 && lenF.size()==0
        && depF.size()==0 && oNum.size()==0 && reg.size()==0)
    {
        vectorsCleared = true;
    }
    else
    {
        vectorsCleared = false;
    }
    return vectorsCleared;
}