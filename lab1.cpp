#include <iostream>
#include <fstream>
#include <streambuf>
#include <vector>
#include <optional>
#include <unordered_set>
#include <algorithm>
#include <string>
#include <boost/algorithm/string.hpp>

using namespace std;

vector<string> students; 
vector<string> absentStudents;

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

    // take out absent students before they are added in. 
    string currentStudent = firstName + " " + lastName;
    for(string absent: absentStudents) {
        if (absent == currentStudent) {
            return fileText.find("\n", endIndexLastName);
        } 
    }
    students.push_back(currentStudent);
    return fileText.find("\n", endIndexLastName);
}



void getAbsentStudents() {
    string absentStudent; 
    do {
        cout << "Enter the name of an absent Student (Type \"end\" to stop entering absent students): "; 
        getline(cin, absentStudent); 
        if(absentStudent != "end") {
            absentStudent = boost::to_upper_copy(absentStudent);
            absentStudents.push_back(absentStudent);
        }
    }while(absentStudent != "end");
}

void getStudentsFromFileText(string fileText) {
    string studentDescriptionHeader = "Student#	Name	Email	Major	Lvl	Opt	Notes";
    int startIndex = fileText.find(studentDescriptionHeader) + studentDescriptionHeader.length() + 2;
    int endIndex =  fileText.find("Total: ");

    do {
        startIndex = getPerson(startIndex, fileText, endIndex);
    } while(startIndex != -1);
}

void printVector(std::vector <string> const &a) {
   std::cout << "The vector elements are : ";

   for(int i=0; i < a.size(); i++){
    std::cout << a.at(i) << ' '; 
   }
   cout << endl;
}

void createGroups(int size) {
    random_shuffle(students.begin(),students.end());
    int num=students.size()/size;
    int remain=students.size()-num*size;
    cout<<"groups:"<<endl;
    int index=0;
    for(int i=1;i<=size;i++){
        cout<<i<<". \n";
        for(int j=0;j<num;j++){
            cout<< "\t" << students[index] << endl;
            index++;
        }
        if(remain>0){
            cout<< "\t" << students[index] << endl;
            // cout<<students[index]<<endl;
            index++;
            remain--;
        }
    }
}


int main(int argc, char** argv) {    
    /*
        group size comes in from stdin argv[1]
        absent students is entered by the user via command line
    */
    getAbsentStudents();
    string fileText = getFileText();
    getStudentsFromFileText(fileText);
    createGroups(stoi(argv[1]));
    return 0;
}




// Ray Klefstad