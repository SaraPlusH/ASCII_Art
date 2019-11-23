/* File: proj1.cpp
   Project: CMSC 202 Project 1, Spring 2019
   Author: Sarah Lunn
   Date: 2/13/2019
   Section: 02
   E-mail: sarahl2@umbc.edu

   This file contains program for Project 1, which reads in a file, creates, 
   and manipulates ASCII art, as directed in the project description.
*/

#include <iostream>
#include <fstream> 
using namespace std;

//Constants
const int MAX_X = 75; //Maximum length of X dimension
const int HALF_X = (MAX_X / 2); // the middle line in the X-direction
const int MAX_Y = 75; //Maximum height of Y dimension
const int HALF_Y = (MAX_Y / 2); // the middle line in the Y-direction
const char BLANK = ' '; //Blank space holder

//Function prototypes
//--------------------
// Name: mainMenu
// Pre-Condition: Must have baseArray (to pass through and valid menu choice
// Post-Condition:  will make menu selection
//--------------------
void mainMenu(char baseArray[][MAX_Y], int);

//--------------------
// Name: printMenu
// Pre-Condition: no inputs
// Post-Condition: will print the main menu list and return a
//                 selected menu option
//--------------------
int printMenu();

//--------------------
// Name: loadArt
// Pre-Condition: Must be files (.txt) available to load
// Post-Condition: File loaded into 2D array,
//                 or user informed that file was absent/wasn't loaded
//--------------------
void loadArt(char baseArray[][MAX_Y]);

//--------------------
// Name: createArray
// Pre-Condition: The max X&Y constants must be available,
//                and the spaceholder must be specified
// Post-Condition: 2D array is created with blank space holders
//--------------------
void createArray(char baseArray[][MAX_Y], int numRows, char icon);

//--------------------
// Name: printArray
// Pre-Condition: print function, will print array even if blank
// Post-Condition: prints array as it is currently loaded
//--------------------
void printArray(char baseArray[][MAX_Y], int numRows);

//--------------------
// Name: createArt
// Pre-Condition: baseArray must exist;
//                user must enter X-Y coordinates and single character
// Post-Condition: The 2D array is updated as user indicated with new symbols
//--------------------
void createArt(char baseArray[][MAX_Y]);

//--------------------
// Name: inversion
// Pre-Condition: There should be a baseArray to invert
// Post-Condition: This will invert the image, put it in a temp 2D array;
//                 then replace the original array with the inverted  image
//--------------------
void inversion(char baseArray[][MAX_Y]);

//--------------------
// Name: validation
// Pre-Condition: the input being verified must be an integer
// Post-Condition: returns a number that falls within a specified range
//--------------------
int validation(int, int);

//--------------------
// Name: rotate
// Pre-Condition: There should be a baseArray and a
// Post-Condition: The image/2D array will be rotated 90 degrees clockwise
//--------------------
void rotate(char baseArray[][MAX_Y]);

//Main function
int main (){

  int menuSelect = 0;
  char baseArray[MAX_X][MAX_Y];
  
  //create and populate empty 2D array
  createArray(baseArray, MAX_Y, BLANK);
  
  cout << "Welcome to ASCII art!" << endl;
  
  //access main menu
  do
    {
      menuSelect = printMenu();
      mainMenu(baseArray, menuSelect);
    }while(menuSelect != 6);

  cout << "Goodbye" << endl;
  return 0;
}

//functions
//--------------------
// Name: printMenu
// Pre-Condition: no inputs
// Post-Condition: will print the main menu list and return a
//                 selected menu option
//--------------------
int printMenu(){
  int menuSelect;
  
  cout << "What would you like to do?" << endl;
  cout << endl;
  cout << "1. Load ASCII art from a file" << endl;
  cout << "2. Create ASCII art manually" << endl;
  cout << "3. Display current art" << endl;
  cout << "4. Rotate current art" << endl;
  cout << "5. Invert current art" << endl;
  cout << "6. Exit" << endl;

  menuSelect = validation(1, 6);
  return menuSelect;
}

//--------------------
// Name: mainMenu
// Pre-Condition: Must have baseArray (to pass through and valid menu choice
// Post-Condition:  will make menu selection
//--------------------
void mainMenu(char baseArray[][MAX_Y], int menuChoice){

  switch(menuChoice)
    {
    case 1: //"Load ASCII art from a file"
      loadArt(baseArray);
      break;
    case 2: //"Create ASCII art manually"
      createArt(baseArray);
      break;
    case 3: //"Display Art"
      printArray(baseArray, MAX_Y);
      break;
    case 4: //"Rotate Art":  90d clockwise
      rotate(baseArray);
      break;
    case 5: //"Invert Art"
      inversion(baseArray);
      break;
    default: //"Exit"
      cout << endl;
    }
}

//--------------------
// Name: rotate
// Pre-Condition: There should be a baseArray and a  
// Post-Condition: The image/2D array will be rotated 90 degrees clockwise
//--------------------
void rotate(char baseArray[][MAX_Y]){

  //create new blank 2D array to hold new rotated image
  char rotateArray[MAX_X][MAX_Y];
  createArray(rotateArray, MAX_Y, BLANK);

  //lift symbol from baseArray -- insert into new spot in rotateArray
  //move y-coord into new x-coord; edit the x-coord to make the new y-coord
  for(int i = 0; i < MAX_X; i++){
    for(int j = 0; j < MAX_Y; j++){
      if(i < HALF_X){
	int diffInI = (HALF_X - i);
	int newJ = (HALF_X + diffInI);
	rotateArray[j][newJ] = baseArray[i][j];	
      }else if(i > HALF_X){
	int diffInI = (i - HALF_X);
        int newJ = (HALF_X - diffInI);
        rotateArray[j][newJ] = baseArray[i][j];
      }else{
	rotateArray[j][i] = baseArray[i][j];}
    }
  }
 
  //convert rotateArray into baseArray so accessable other places
  for(int i = 0; i < MAX_X; i++){
    for(int j = 0; j < MAX_Y; j++){
      baseArray[i][j] = rotateArray[i][j];}
  }
}

//--------------------
// Name: inversion
// Pre-Condition: There should be a baseArray to invert
// Post-Condition: This will invert the image, put it in a temp 2D array;
//                 then replace the original array with the inverted  image
//--------------------
void inversion(char baseArray[][MAX_Y]){

  //Pick which way to invert the image
  int invertChoice;
  cout << endl;
  cout << "Do you want to invert the image:" << endl;
  cout << "1. Horizontally" << endl;
  cout << "2. Vertically" << endl;
  invertChoice = validation(1, 2);

  //create new blank 2D array to hold new inverted image
  char invertArray[MAX_X][MAX_Y];
  createArray(invertArray, MAX_Y, BLANK);

  //lift symbol from baseArray -- insert into new spot in invertArray
  if(invertChoice == 1){
    //flip horizontally (switch the y-coord; leave the x-coord)
    for(int i = 0; i < MAX_X; i++){
      for(int j = 0; j < MAX_Y; j++){
	if(j < HALF_Y){
	  int diffInJ = (HALF_Y - j);
	  int newJ = (HALF_Y + diffInJ);
	  invertArray[i][newJ] = baseArray[i][j];
	}else{
	  int diffInJ = (j - HALF_Y);
	  int newJ = (HALF_Y - diffInJ);
	  invertArray[i][newJ] = baseArray[i][j];}
      }
    }
    //convert invertArray into baseArray so accessable other places
    for(int i = 0; i < MAX_X; i++){
      for(int j = 0; j < MAX_Y; j++){
	baseArray[i][j] = invertArray[i][j];}
    }
  }else{
    //flip vertically (switch the x-coord; leave the y-coord)
    rotate(baseArray);
    rotate(baseArray);

    /*code from alt menthod of vertical inversion;
    told to do above (double rotation) during class 
    commented out to keep original code 
    for(int i = 0; i < MAX_X; i++){
      for(int j = 0; j < MAX_Y; j++){
        if(i < HALF_X){
          int diffInI = (HALF_X - i);
          int newI = (HALF_X + diffInI);
          invertArray[newI][j] = baseArray[i][j];
        }else{
          int diffInI = (i - HALF_X);
          int newI = (HALF_X - diffInI);
          invertArray[newI][j] = baseArray[i][j];}
      }
    } */
  }
}

//--------------------
// Name: createArt
// Pre-Condition: baseArray must exist;
//                user must enter X-Y coordinates and single character
// Post-Condition: The 2D array is updated as user indicated with new symbols 
//--------------------
void createArt(char baseArray[][MAX_Y]){

  int xCoord, yCoord, repeating;
  char icon;

  //input symbol at spot directed
  do{
    cout << endl;
    cout << "This will modify the current art." << endl;
    cout << "Please provide a X-coordinate between 0 and " << (MAX_X - 1)
	 << " of the space you would like to modify." << endl;
    xCoord = validation(0, MAX_X);
    cout << "Please provide a Y-coordinate between 0 and " << (MAX_Y - 1)
	 << " of the space you would like to modify." << endl;
    yCoord = validation(0, MAX_Y);
    
    cout << "What symbol would you like to place at ("
	 << xCoord << ", " << yCoord << ")?" << endl;
    cout << "Symbol: ";
    cin >> icon;
    cout << endl;

    baseArray[xCoord][yCoord] = icon;

    //does the user want to keep editing? or exit loop
    cout << "Would you like to continue editing? "
	 << "(Enter 1 to edit; 2 to exit editor)" << endl;
    repeating = validation(1, 2);
  }while(repeating == 1);
}

//--------------------
// Name: loadArt
// Pre-Condition: Must be files (.txt) available to load
// Post-Condition: File loaded into 2D array,
//                 or user informed that file was absent/wasn't loaded
//--------------------
void loadArt(char baseArray[MAX_X][MAX_Y]){

  char fileName[80];
  char icon;
  int xCoord, yCoord;

  //request file name
  cout << endl;
  cout << "What data file do you want to load? " <<
    "Please include file extension." << endl;
  cin >> fileName;

  fstream inputStream;
  inputStream.open(fileName);

  //verify file exists and load symbols into 2D array file coordinates
   if(inputStream.is_open()){
     while(inputStream >> xCoord >> yCoord >> icon){
      baseArray[xCoord][yCoord] = icon;
     }
  }else{
    cout << "That file does not exist." << endl;
    }
  inputStream.close();
}

//--------------------
// Name: createArray
// Pre-Condition: The max X&Y constants must be available,
//                and the spaceholder must be specified
// Post-Condition: 2D array is created with blank space holders
//--------------------
void createArray(char baseArray[][MAX_X], int MAX_Y, char icon){

  //Create blank array using blank space const and max dimensions 
  for(int i = 0; i < MAX_X; i++){
    for(int j = 0; j < MAX_Y; j++){
      baseArray[i][j] = icon;}
  }
}

//--------------------
// Name: printArray
// Pre-Condition: print function, will print array even if blank
// Post-Condition: prints array as it is currently loaded
//--------------------
void printArray(char baseArray[][MAX_Y], int MAX_Y){
  
  cout << endl;
  //print array line by line
  for(int i = 0; i < MAX_X; i++){
    for(int j = 0; j < MAX_Y; j++){
      cout << baseArray[i][j];}
    cout << endl;}
}

//--------------------
// Name: validation
// Pre-Condition: the input being verified must be an integer
// Post-Condition: returns a number that falls within a specified range
//--------------------
int validation(int mini, int maxi){

  int inputNum;
  cin >> inputNum;

  //request new number if it's outside range
  while(inputNum < mini or inputNum > maxi){
    cout << "Enter a number between " << mini << " and " << maxi << endl;
    cin >> inputNum;}

  return inputNum;
}
