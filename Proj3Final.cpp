//MERGE SORT LINES 48-105, CALL LINE 48
#include <iostream>
#include<fstream>
#include <string>
#include <iomanip>
//Hector Lopez Lopez    HXL190015   1337.002
using namespace std;

const string database = "numbers.txt";

struct Node{ //Structure for Nodes

    int Arabic; //Stores Arabic Numbers
    string Roman; // Stores Roman Numerals and line from file
    Node* next; //Next Node (basic)

};

void printListConsole(Node *head,int choice) {//Prints list into Console

    if(head == NULL ) return; //End once reaches end of List
    if(head->Arabic > 0){ //Only printing Nodes with values
        if(choice == 2){ //If choice was 2 only prints Arabic Values
            cout<< head->Arabic<<endl;
        }else if(choice == 1){//If choice was 1 only prints Roman Values
            cout<<head->Roman<<endl;
        }
        else if(choice == 3){//Choice if Exiting and printing out List onto Console (END OF PROGRAM)
            cout << head->Roman << setw(16-(int)head->Roman.length()) << head->Arabic<<endl;
        }
    }
    printListConsole(head->next,choice);
}


void linearSearch(Node *&head, string input){ //Searches through Array
    Node *traverse = head;
    if(input == "0"){
        cout<<input<<" not found\n";
        return;
    }
    while(traverse != NULL ){ // Stops looping before Node reaches end
        if(isdigit(input[0])){ //If its a digit search only arabic values
            if(traverse->Arabic == stoi(input)){ // Makes sure to check if searched value is in linked list, never 0s
                cout<<input<<" found\n";
                return;
            }
        }else if(traverse->Roman == input){//If not digit search only Roman values
            cout<<input<<" found\n";
            return;
        }
        traverse = traverse->next; //Traverses through list
    }
    cout<<input<<" not found\n";
}

void listSplit(Node *head, Node *&left, Node *&right){ //Splits Given Nodes Accordingly

    Node *curNode = head;
    Node *nxtNode = head->next;

    while(nxtNode != NULL){ //Goes through List
        nxtNode = nxtNode->next;
        if(nxtNode != NULL) {  //Keeps traversing the list
            curNode = curNode->next;
            nxtNode = nxtNode->next;
        }
    }
    //Assigns correct left and right bounds
    right = curNode->next;
    left = head;
    curNode->next = NULL;
}

Node* moveNodes(Node *leftSide, Node *rightSide, int choice){ //Sorts Nodes according to splits for specified Choice
    Node *newHead = NULL;

    //If Nodes are empty it returns the opposite node
    if(leftSide == NULL) return (rightSide);
    else if(rightSide == NULL) return (leftSide);

    if(choice == 1){
        if(leftSide->Roman <= rightSide->Roman) { //Compares and Sorts left and Right side of List for Roman Numerals
            newHead = leftSide;//Left Numeral is lower value and switches
            newHead->next = moveNodes(leftSide->next, rightSide,choice); //Recursively Calls to ensure that each split is sorted
        }else{
            newHead = rightSide;//Right Numeral is lower value and switches
            newHead->next = moveNodes(leftSide, rightSide->next,choice);//Recursively Calls to ensure that each split is sorted
        }
    }else if(choice == 2){
        if(leftSide->Arabic <= rightSide->Arabic) {//Compares and Sorts left and Right side of List for Arabic Numbers
            newHead = leftSide;//Left Number is lower value and switches
            newHead->next = moveNodes(leftSide->next, rightSide,choice);//Recursively Calls to ensure that each split is sorted
        }else{
            newHead = rightSide; //Right Number is lower value and switches
            newHead->next = moveNodes(leftSide, rightSide->next,choice);//Recusively Calls to ensure each split is sorted
        }
    }
    return newHead; //Returns start of the sorted Split (start of list)
}

void mergeSort(Node *&head, int choice){//Sorts Linked List according to Choice

    Node *left, *right;
    Node *start = head;

    if(start == NULL || start->next == NULL) return; //Makes sure list contains values
    listSplit(start, left, right); //Call for List Split

    mergeSort(left,choice); //Recursive Call to sort Left split
    mergeSort(right,choice); //Recursive Call to sort Right Split

    head = moveNodes(left, right,choice); //head of list is the start sorted left side of inputted choice
}

void createNode(Node *&head, string roman, int arabic){ //Creates a Linked list with lines from file

    Node* newNode = new Node;
    newNode->next = NULL;
    newNode->Arabic = arabic;
    newNode->Roman = roman;

    //Forms links between Nodes first Node in is last
    if(head == NULL) head = newNode;
    else{
        newNode->next = head;
        head = newNode;
    }
}

int romanTOArabic(string str){ // Converts Roman Numerals to Arabic integers takes in head of list (aka) last read line

    int sum = 0;
    for(unsigned int i = 0; i < str.length(); i++) { //Goes through the Roman Numeral and adds appropriate values to sum for Node
        if(str[i] == 'M') sum += 1000;
        if(str[i] == 'D') sum+=500;
        if(str[i] == 'C' && (str[i+1] == 'D' || str[i+1] == 'M')) sum -= 100;
        else if(str[i] == 'C')  sum += 100;
        if(str[i] == 'L')  sum += 50;
        if(str[i] == 'X' && (str[i+1] == 'L' || str[i+1] == 'C')) sum -= 10;
        else if(str[i] == 'X') sum += 10;
        if(str[i] == 'V')  sum += 5;
        if(str[i] == 'I' && (str[i+1] == 'X' || str[i+1] == 'V')) sum -= 1;
        else if(str[i] == 'I') sum += 1;
    }
    return sum; // Assigns value to Node
}

string arabicTORoman(int num){// Converts Arabic Numbers to Roman Numerals takes in head of list (aka) last read line

    string romanSum = "";

    int thousands = num/1000;
    int hundreds = num%1000/100;
    int tens = num%1000%100/10;
    int ones = num%1000%100%10;

    //Goes through each value and Assigns proper character to string according to calculation
    for(int i = 0; i < thousands; i++) romanSum.append("M");
    if(hundreds < 4) for(int i = 0; i < hundreds; i++) romanSum.append("C");
    if(hundreds == 4)  romanSum.append("CD");
    if(hundreds == 5)  romanSum.append("D");
    if(hundreds > 5 && hundreds < 9)
    {
        romanSum.append("D");
        for(int i = 5; i < hundreds; i++) romanSum.append("C");
    }
    if(hundreds == 9) romanSum.append("CM");
    if(tens < 4) for(int i = 0; i < tens; i++) romanSum.append("X");
    if(tens == 4) romanSum.append("XL");
    if(tens == 5) romanSum.append("L");
    if(tens > 5 && tens < 9)
    {
        romanSum.append("L");
        for(int i = 5; i < tens; i++) romanSum.append("X");
    }
    if(tens == 9) romanSum.append("XC");
    if(ones < 4) for(int i = 0; i < ones; i++) romanSum.append("I");
    if(ones == 4) romanSum.append("IV");
    if(ones == 5) romanSum.append("V");
    if(ones > 5 && ones < 9)
    {
        romanSum.append("V");
        for(int i = 5; i < ones; i++) romanSum.append("I");
    }
    if(ones == 9) romanSum.append("IX");

   return romanSum;
}

void printList(Node *head, ofstream& output){ //Writes list onto file recursively

    if(head == NULL ) return; //Ends once end of list

    //Only printing Nodes with values
    if(head->Arabic > 0) output << head->Roman
        << setw(16-(int)head->Roman.length()) << head->Arabic<<endl;

    printList(head->next, output ); //Recursive Call
}
bool validRoman(string str) {//Validates given string as Roman
    for(unsigned int i = 0; i < str.length(); i++){
        //Compares string with all known Roman Numerals
        if(str[i] != 'M' && str[i] != 'D' && str[i] != 'C' && str[i] != 'L'
        && str[i] != 'X' && str[i] != 'V' && str[i] != 'I') return false;
    }
    return true;
}

bool validArabic(string str) { //Ensures that given String is a valid Arabic
    if(str[0] == '0') return false; //if String null char it is not valid
    else{
        for(unsigned int i = 0; i < str.length(); i++){ //Goes through string
            if( !( isdigit(str[i]) || isblank(str[i])) ) return false; //If string is not a digit or blank  it's not valid
        }
    }
    return true;
}

int main()
{
    /* ################  DO NOT MODIFY CODE IN THIS BLOCK ###################### */
    string temp;  //variable for database filename
    string batch; //variable for batch filename

    cout<<"Enter File Name: ";
    cin>>temp;

    ifstream infile(temp, ios::binary);
    ofstream outfile(database, ios::binary);
    string line;
    if (infile)
        while (infile.good())
        {
            getline(infile, line);
            if (line != "")
                outfile << line << "\n";
        }

    infile.close();
    outfile.close();
    /* ################  DO NOT MODIFY CODE IN THIS BLOCK ###################### */

    //Open File and declare starting variables
    fstream file("numbers.txt",fstream::in | fstream::out | fstream::binary);
    Node* head = nullptr;
    string fileline;

    if(file){ //Opens file
        while(file.good()){ //Runs until end of file
            getline(file, fileline);
            int x = (int)fileline.find(' ');//Find value where first white space is in line
            if( (fileline[0] == ' ' && validArabic(fileline)) && fileline != "0" && stoi(fileline)<4999){ //Determines if Roman or Arabic
                string roman = arabicTORoman(stoi(fileline));
                createNode(head,roman,stoi(fileline));//Creates node with conversion
            }else if(validRoman(fileline.substr(0,x))){ //Validates line if it is a Roman Numeral
                int arabic = romanTOArabic(fileline.substr(0,x));//Converts last read in line
                if(arabic < 4999) createNode(head,fileline.substr(0,x),arabic);//Creates node with conversion
            }
        }
        head = head->next;
        //Opens file and deletes all values to allow writing of linked list
    }else{ //File cannot be opened
        cout << "!!! FILE CANNOT BE OPENED !!!";
        return -1;
    }
    file.close();//Close file

   // USER MENU
    char choice;
    do{
        cout<<
        "-----Menu-----\n"
        " 1.Search\n"
        " 2.Sort\n"
        " 3.Exit\n";
        cin>>choice;

        switch(choice){
            case '1':{
                string value;
                cout<<"\nEnter Value:: ";
                cin >> value;
                linearSearch(head,value);
                break;
            }case '2':{
                int choice;
                cout<<"Sort by: \n";
                cout<<" 1. Roman\n";
                cout<<" 2. Arabic\n";
                cin >> choice;
                mergeSort(head,choice);
                printListConsole(head,choice);
                break;
            }case '3':{
                printListConsole(head,3);
                cout<< "\n";
                break;
            }default:
                cout<<"\n Invalid Selection\n";
                break;
        }
    }while(choice != '3');
    ofstream writefile;
    writefile.open("numbers.txt", std::ofstream::out | std::ofstream::trunc);
    printList(head, writefile);

    return 0;

}
