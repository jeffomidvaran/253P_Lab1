#include <iostream>
#include <fstream>
#include <streambuf>
#include <vector>
#include <optional>

using namespace std;

struct Person {
    string firstName = "Empty";
    string lastName = "Empty";

    Person(string firstName, string lastName) {
        this->firstName = firstName; 
        this->lastName = lastName;
    } 
};

vector<string> students; 

string getFileText() {
    ifstream myFile("roster.txt"); 
    string str((istreambuf_iterator<char>(myFile)), istreambuf_iterator<char>());
    myFile.close();
    return str;
}

int getPerson(int startIndex, string fileText, int endIndex) {
    
    int startIndexLastName = fileText.find("\t", startIndex) + 1;
    if (startIndexLastName > endIndex) { 
        return -1; 
    }
    int endIndexLastName = fileText.find(",", startIndexLastName); 
    string lastName = fileText.substr(startIndexLastName, endIndexLastName - startIndexLastName);
    
    int startIndexFirstName = endIndexLastName + 2;
    int endIndexFirstName = fileText.find("\t", startIndexFirstName); 
    string firstName = fileText.substr(startIndexFirstName, endIndexFirstName - startIndexFirstName);

    cout << firstName << " " << lastName << endl;
    students.push_back(firstName + " " + lastName);
    return fileText.find("\n", endIndexLastName);
}

int main(int argc, char** argv) {
    string fileText = getFileText();
    string studentDescriptionHeader = "Student#	Name	Email	Major	Lvl	Opt	Notes";
    int startIndex = fileText.find(studentDescriptionHeader) + studentDescriptionHeader.length() + 2; 
    int endIndex =  fileText.find("Total: ");

    do {
        startIndex = getPerson(startIndex, fileText, endIndex);
    } while(startIndex != -1);
    return 0;
}