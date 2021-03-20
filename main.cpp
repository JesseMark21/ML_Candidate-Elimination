#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <fstream>
#include <ostream>
using namespace std;

vector<string> splitString(string splitStr, string token){
        vector<string>result;
    while(splitStr.size()){
        int i = splitStr.find(token);
        if(i!=string::npos){
            result.push_back(splitStr.substr(0,i));
            splitStr = splitStr.substr(i+token.size());
            if(splitStr.size()==0)result.push_back(splitStr);
        }else{
            result.push_back(splitStr);
            splitStr = "";
        }
    }
    return result;
}

int main(int argc, char** argv)
{
    ifstream input("data.txt");
    string line;

    ofstream myfile;
    myfile.open("Output.txt");

    int numberFeatures;


    
    
    vector<string> targetConcept = {"Japan", "?", "?", "?", "Economy"};
    myfile<<"Target Concept: <"<< targetConcept[0] << ", " << targetConcept[1] << ", "<< targetConcept[2]<< ", " <<  targetConcept[3]<< ", " << targetConcept[4]<< ">" << endl;
    
    vector<string> compare;
    vector<string> specific = {"0", "0", "0", "0", "0"};
    vector< vector<string> > versionSpace;
    vector<string> generic(5);
    generic[0]="?";
    generic[1]="?";
    generic[2]="?";
    generic[3]="?";
    generic[4]="?";
    versionSpace.push_back(generic);

    myfile<<"specific: "<< "<" << specific[0]<< ", " << specific[1]<< ", " << specific[2]<< ", " << specific[3]<< ", " << specific[4] << ">" << endl;
    myfile<<"generic: <?, ?, ?, ?, ?>" << endl;
    myfile<<endl;
    int count = 0;
    while(!input.eof()){
        getline(input, line);
        compare = splitString(line, " ");
        

        for(int i = 0; i<specific.size(); i++){
            if(compare[5] == "Positive"){
                if(count == 0){
                    specific[i] = compare[i];
                }
                else if(compare[i]!=specific[i]){
                    if(!versionSpace.empty()){
                        for(int j =0; j< versionSpace.size(); j++){
                            for(int k =0; k<specific.size(); k++){
                                if(versionSpace[j][k]==specific[i]){
                                    versionSpace[j] = {"0", "0", "0", "0", "0"};
                                    
                                }
                            }
                        }
                    }

                    

                    specific[i] = "?";

                    
                }
                     
            }
            else{
                
                bool isH = false;
                
                for(int j = 0; j<specific.size(); j++){
                    
                    if(compare[j]!=specific[j]){
                        vector<string> temp = {"?", "?", "?", "?", "?"};
                        temp[j] = specific[j];

                        for(int k = 0; k<temp.size(); k++){
                            if(temp[k]!="?"){
                                isH = true;
                            }
                        }

                        if(isH){
                            versionSpace.push_back(temp);
                        }
                        isH = false;

                    }



                }
            }

        }
        count ++;
        myfile<<"Training Example "<< count << ": <" << compare[0] << ", " << compare[1] << ", "<< compare[2]<< ", " <<  compare[3]<< ", " << compare[4]<<">" << " Type: "  << compare[5] << endl;
        if(count!=5){
            myfile<<"specific: "<< "<" << specific[0]<< ", " << specific[1]<< ", " << specific[2]<< ", " << specific[3]<< ", " << specific[4] << ">" << endl;
        }
        else{
            myfile<<"specific: "<< "<" << specific[0]<< ", " << specific[1]<< ", " << specific[2]<< ", " << specific[3]<< ", " << specific[4] << ">";
        }
        
        sort(versionSpace.begin(), versionSpace.end());
        auto last = unique(versionSpace.begin(), versionSpace.end());
        versionSpace.erase(last, versionSpace.end());
        

        if(!versionSpace.empty()){
            
            if(count!=5){
                myfile<<"generic: ";

            }
            
            
            
            for(int i =0; i<versionSpace.size(); i++){
            vector<string> temp = versionSpace[i];
            if(temp[0]!="0"){
                if(i!=versionSpace.size() - 1){
                    myfile<< "<" << temp[0]<< ", " << temp[1]<< ", " << temp[2]<< ", " << temp[3]<< ", " << temp[4] << ">" << ", ";
                }
                else{
                    myfile<< "<" << temp[0]<< ", " << temp[1]<< ", " << temp[2]<< ", " << temp[3]<< ", " << temp[4] << ">" << endl;
                }
                

            }
            


        }

        }
        if(count==1){
            versionSpace.pop_back();
        }
        myfile << endl;
 
    }

    myfile<<"generic: "<< "<" << specific[0]<< ", " << specific[1]<< ", " << specific[2]<< ", " << specific[3]<< ", " << specific[4] << ">" << endl;
    myfile<<endl;
    myfile<<"Q2: 5";


}