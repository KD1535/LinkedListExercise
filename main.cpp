#include <iostream>
#include <fstream>

using namespace std;

// employee struct linked list
struct Employee
{
    string firstName;
    string lastName;
    int phoneNumber;
    Employee *next;
};

// Inserts node into list in sorted location
// Pre: Valid pointer for list and prefilled NodePtr
// Post: Sorted list
void AddNode(/* IN/OUT */Employee *&headPtr,/* IN */ Employee *newNodePtr);

// Create and return a new node.
// Pre: None
// Post: Returns a pointer to NodeType with component set to user input and next set to nullptr
Employee *CreateNode();


// Stores data from program into given output file.
// Pre: fileName is initilzied with a valid file and file stream is valid
//      counter contains correct length of employee array
//      employee array is intialized and delcared      
// Post: data at every index in employee array is output into outData
void StoreData(/* IN */string fileName, /* IN/OUT */ ofstream &outData,/* IN */Employee *employee);

// Prints out list
// Pre: Valid nodeptr
void PrintList(/* IN */Employee *employeePtr);

// Deletes the node containing the passed string. 
// Pre: NodePtr points to valid linked list and string points to a valid string
// Post: Node containing the passed string has been removed from the list.
void DeleteNode(/* IN/OUT */Employee *&headPtr);

// Takes a string, making the first letter uppercase and remainder lowercase
// Pre: Valid string passed as argument
// Post: Returns a normalized string
string NormalizeString(string &str);

// Returns a pointer to the node with matching last name. 
// Pre: Valid NodePtr and string.
// Post: Returns pointer to matching node or nullptr if not found.
void FindNode (/* IN/OUT */Employee *headPtr);

int main()
{
    // outgoing file from linked list (contacts.dat)
    ofstream outData;
    // holds outgoing file name (contacts.dat) 
    string fileName = "contacts.dat";
    // head of linekd list
    Employee *employee;
    //setting to null pointer (list is empty)
    employee = nullptr;
    // continue adding contacts
    char choice;

    // add contacts to linked list while choice is 'y'
    do
    {
        AddNode(employee,CreateNode());
        cout << "continue?\n";
        cin >> choice;
    } while (tolower(choice) != 'n');
    
    // display current data in linked list
    PrintList(employee);
    cout<<endl;

    // remove node from list
    DeleteNode(employee);
    cout<<endl;

    // refreshing list
    PrintList(employee);
    cout<<endl;

    // look up contacts by last name
    FindNode(employee);

    // check if linked list is empty
    if(employee != nullptr)
        // store data from linked list into file "contacts.dat"
        StoreData(fileName,outData,employee);
    return 0;
}

void StoreData(/* IN */string fileName, /* IN/OUT */ ofstream &outData,/* IN */Employee *employee)
{
    Employee *currPtr = employee;
    outData.open(fileName.c_str());
    if (currPtr != nullptr)
    {
        outData << currPtr->lastName << "," << currPtr->firstName << "," << currPtr->phoneNumber; 
    }
    while(currPtr->next != nullptr)
    {
        currPtr = currPtr->next;
        outData << '\n' << currPtr->lastName << "," << currPtr->firstName << "," << currPtr->phoneNumber;
    }
}

void AddNode(/* IN/OUT */Employee *&headPtr, /* IN */Employee *newNodePtr)
{  
    Employee *currPtr = headPtr;

    // checking if headPtr = nullptr
    //      if yes, make newNodePtr the head
    // or check if headPtr is greater than newNodePtr
    //      if yes, make newNodePtr the head and switch links
    if (headPtr == nullptr || newNodePtr->lastName <= headPtr->lastName)  
    {
        newNodePtr->next = headPtr;  
        headPtr = newNodePtr;
    }  
    else
    {  
        // working node
        // starting at the head of the list
        currPtr = headPtr;
        // Traverse through links until the spot of inserting  
        while (currPtr->next!=nullptr)  
        {  
            currPtr = currPtr->next;  
        } 
        //inserting new node in sorted location
        newNodePtr->next=currPtr->next;
        currPtr->next = newNodePtr;  
    }
}

// Creates a node
// Pre: None
// Post: Returns a a node
Employee *CreateNode()
{
    // data for new node to create
    Employee *newNodePtr = new Employee;

    // get last name and store into newNodePtr of employee
    cout << "Last name: ";
    while(!(cin >> newNodePtr->lastName))
    {
        cout << "INVALID ENTRY. INPUT ONLY ALPHABETIC CHARACTERS." << endl;
        cin.clear();
        cin.ignore(1000,'\n');
    };
    NormalizeString(newNodePtr->lastName);
    // clears input stream
    cin.clear();
    cin.ignore(1000,'\n');

    // get first name and store into newNodePtr of employee
    cout << "First name: ";
    while(!(cin >> newNodePtr->firstName))
    {
        cout << "INVALID ENTRY. INPUT ONLY ALPHABETIC CHARACTERS." << endl;
        cin.clear();
        cin.ignore(1000,'\n');
    };
    NormalizeString(newNodePtr->firstName);
    // clears input stream
    cin.clear();
    cin.ignore(1000,'\n');

    // get phone number of employee and store into phoneNumber
    cout << "Phone number (NUMBERS ONLY): " << endl;
    while(!(cin>>newNodePtr->phoneNumber))
    {
        cout << "INVALID ENTRY. INPUT ONLY INTEGERS";
    }
    // clears input stream
    cin.clear();
    cin.ignore(1000,'\n');

    // sets link to null ptr
    newNodePtr->next = nullptr;

    return newNodePtr;
}

void PrintList(/* IN */Employee *employeePtr)
{
    // if head of linked list is nullptr then alert user list is empty
    if (employeePtr == nullptr)
        cout << "CONTACT LIST IS EMPTY!\n";

    // Loop until we've reached the end of the list (Or it's an empty list)
    while (employeePtr != nullptr) {
        
        // Print value of current node
        cout << "Last name: " << employeePtr->lastName << ", " << "First name: " << employeePtr->firstName << ", " << "Phone number: " << employeePtr->phoneNumber<< endl;
        // Advance currPtr to point at next node
        employeePtr = employeePtr->next;
    } 
}                         

// Removes value from list
// Pre: intialized and declared headPtr
// Post: deletes node with respective value
void DeleteNode(/* IN/OUT */Employee *&headPtr)
{
    Employee *currPtr = headPtr; // working pointer, currentPtr
    //NodeType *nextPtr = nullptr; // keep track of the next pointer of currPtr
    Employee *prevPtr = nullptr; // keep track of pointer behind current
    bool flag = false; // flag for input validation
    string delLast; // last name of employee to delete from list
    string delFirst; // first name of employee to delete from list

    // check if node is empty
    //      if yes, notify user there is nothing in the list to delete
    if(currPtr == NULL){
        cout << "\nEMPLOYEE LIST IS EMPTY. NO CHANGES MADE.\n";
        return;
    }

    // take user input for value to delete from list and store into value variable
    cout << "LAST NAME of contact to delete: ";
    cin >> delLast;
    NormalizeString(delLast);
    cout << "FIRST NAME of contact to delete: ";
    cin >> delFirst;
    NormalizeString(delFirst);

    // if currPtr is equal to value to find and prevPtr = nullptr then value to delete is the headPtr
    if (currPtr->lastName == delLast && currPtr->firstName == delFirst && prevPtr == nullptr)
    {
        headPtr=currPtr->next;
        delete currPtr;
        cout << "\n*** Contact " << delLast << " " << delFirst << " REMOVED FROM SCHEDULE. ***\n";
        return;
    }
    
    // while currPtr is in a intialized list
    while (currPtr != nullptr )
    {   
        // check if currPtr is equal to value to delete
        if( currPtr->lastName == delLast && currPtr->firstName == delFirst)
        {
            // get location of the next linked node from current pointer
            prevPtr->next=currPtr->next;
            // delete node that currPtr points to
            delete currPtr;
            // set flag to true
            // input is not invalid
            flag = true;
            cout << "\n*** Contact" << delLast << " " << delFirst << " REMOVED FROM SCHEDULE. ***\n";
            break;
        }
        // traversing through the list until value to delete is found
        prevPtr = currPtr;
        currPtr = currPtr->next;
    }

    // alert user if value entered is not within the list
    if (!flag)
    {
        cout << "\n*** Contact " << delLast << " " << delFirst << " NOT FOUND. NO CHANGES MADE. ***\n";
    }

}

void FindNode (/* IN/OUT */Employee *headPtr)
{
    // last name of contact/employee to find
    string findLast;
    // user input to search again
    char choice;
    // if employee was found
    bool found = false;

    Employee *currPtr;

    if(headPtr == nullptr)
    {
        cout << "CONTACT LIST IS EMPTY!\n";
        return;
    }

    do
    {
        currPtr = headPtr;
        cout << "Enter last name of contact to look up\n";
        cout << "Last name: ";
        while(!(cin >> findLast))
        {
            cout << "Please enter a valid contact last name.";
        };
        cin.clear();
        cin.ignore(1000,'\n');
        NormalizeString(findLast);

        while(currPtr != nullptr)
        {
            if(currPtr->lastName == findLast)
            {
                cout << "First name: " << currPtr->firstName << ", "<< "Last name: " << currPtr->lastName << ", "<< "Phone number: " << currPtr->phoneNumber << endl;
                found = true;
                break;
            }
            currPtr = currPtr->next;
        }
        if (!found)
        {
            cout << "\n*** Employee " << findLast << " not found ***\n";
        }
        
        cout << "Continue looking-up contacts? (y/n): ";
        cin >> choice;
    }while(toupper(choice) != 'N');


    
}

string NormalizeString(string &str)
{   
    // loop through every index of a string to capatilize first letter 
    str[0] = toupper(str[0]);    
    for (int i = 1; i < str.length(); i++)
    {        
        str[i] = tolower(str[i]);    
    }    
    return str;
    }