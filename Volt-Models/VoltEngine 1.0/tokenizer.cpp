#include <iostream>
#include <fstream>
#include <string>
int main(){
    /*
    std::ifstream dataset("dataset.txt");
    std::string content;
    std::string delimiter="<partion>";
    std::string line;
    while (std::getline(dataset,line)){
        content+=line+"\n";
    }
    size_t pos=content.find(delimiter);
    if(pos!=std::string::npos){
        std::string destination = content.substr(0,pos);
        std::cout<<destination<<"\n";
    } else {
        std::cout<<content<<"\n";
    } */
    std::ifstream dataset("dataset.txt");

    std::string content;
    std::string delimiter = "<EOW>";
    std::string line;

    while (std::getline (dataset, line)) {
        content += line + "\n";
    }
    size_t pos = content.find(delimiter);
    
    if (pos != std::string::npos) {
        std::string destination = content.substr(0,pos);
        std::cout << destination << "\n";
    } else {
        std::cout << content << "\n";
    }
    return 0;
}