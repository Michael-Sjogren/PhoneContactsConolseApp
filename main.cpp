#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm> 
#include <cctype>
#include <locale>

struct Contact {
    std::string fullName;
    std::string phoneNUmber;
};

std::vector<Contact> contacts;
// An app which reads/writes names and phone numbers in a plain TXT file.
static inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
        return !std::isspace(ch);
    }));
}
void ReadContactsAndFillArray(){
    std::ifstream contacts_file("contacts.txt");
    std::string line = "";
    if(contacts_file)
    {
        while(std::getline(contacts_file, line)){
            size_t delimiter_index = line.rfind(':');
            Contact c;
            c.fullName = line.substr(0, delimiter_index-1);
            c.phoneNUmber = line.substr(delimiter_index+1 , line.length());
            ltrim(c.phoneNUmber);
            ltrim(c.fullName);
            contacts.push_back(c);
        }
    }
    contacts_file.close();
}

void WriteToContactToFile(Contact c){
    std::ofstream contacts_file;
    contacts_file.open("contacts.txt",std::ios::app);
    if(contacts_file){
        contacts_file << c.fullName << " : " << c.phoneNUmber << "\n";
    }
    contacts_file.close();
}
int main(){
    ReadContactsAndFillArray();
    std::cout << "Current list of contacts: " << "\n";
    std::cout << "-------------------------" << "\n";
    for(size_t i = 0; i < contacts.size(); i++){
        Contact c = contacts.at(i);
        std::cout << c.fullName << " : " << c.phoneNUmber << "\n";
    }
    std::cout << "-------------------------" << "\n";
    bool stop = false;
    while(stop != true){
        char answer;
        Contact c;
        std::cout << "Add a new contact to your adress book? , press any key to continue." << "\n";
        std::cin.get();
        std::cout<<"Enter a phone number: " << "\n";
        std::getline(std::cin, c.phoneNUmber);
        std::cout<<"Enter a name: " << "\n";
        std::getline(std::cin, c.fullName);
        system("clear");
        std::cout << "Added contact: " << c.fullName << " : " << c.phoneNUmber << "\n";
        WriteToContactToFile(c);
        std::cout<<"Do you want to quit adding contacts? Y/N: " << "\n";
        std::cin >> answer;
        if(tolower(answer) != 'n'){
            stop = true;
        }
        std::cout.clear();
        std::cin.clear();
    }
    return 0;
}