#include <iostream>
#include <fstream>
#include <streambuf>
#include <vector>
#include <optional>
#include <unordered_set>
#include <algorithm>

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

void createGroups(int size, unordered_set<string> absent) {
    vector<string>attended;
    for(int i=0;i<students.size();i++){
        if(absent.find(students[i])==absent.end()){
            attended.push_back(students[i]);
        }
    }
    random_shuffle(attended.begin(),attended.end());
    int num=attended.size()/size;
    int remain=attended.size()-num*size;
    cout<<"groups:"<<endl;
    int index=0;
    for(int i=1;i<=size;i++){
        cout<<i<<". ";
        for(int j=0;j<num;j++){
            cout<<attended[index]<<endl;
            index++;
        }
        if(remain>0){
            cout<<attended[index]<<endl;
            index++;
            remain--;
        }
    }
}

int main(int argc, char** argv) {
    string fileText = getFileText();
    string studentDescriptionHeader = "Student# Name    Email   Major   Lvl Opt Notes";
    int startIndex = fileText.find(studentDescriptionHeader) + studentDescriptionHeader.length() + 2;
    int endIndex =  fileText.find("Total: ");
    cout << startIndex << " " << endIndex << endl;

    do {
        startIndex = getPerson(startIndex, fileText, endIndex);
    } while(startIndex != -1);

    for(string s:students){cout<<s<<" hello";}
    cout<<"group size:";
    int groupSize,absentNumber;
    cin>>groupSize;
    cout<<"absent students:";
    cin>>absentNumber;
    unordered_set<string>absent;
    for(int i=0;i<absentNumber;i++){
        string tmp;
        getline(cin,tmp);
        absent.insert(tmp);
    }
    createGroups(groupSize,absent);
    return 0;
}