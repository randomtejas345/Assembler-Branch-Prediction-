#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include<sstream>
#include<map>



using namespace std;

int flag=1;
int is_branch=0;
int is_pos=0;
int hit=0;
int miss=0;
map<string,pair<int,vector<int>>> BTB;




void single_bit(string pc){
    
}




int main(){

// take input from the file

    string text;
    ifstream Myfile("code.asm");
    vector<string> instruction_set;

    

    while(getline(Myfile,text)){

        if(!text.empty()){

         stringstream ss(text);
         string temp_word;
         string pc;
         vector<int> history;
         while(getline(ss,temp_word,' ')){
            if(temp_word.substr(0,2)=="0x"&&flag==1){
                flag=1-flag;
                pc=temp_word;
            }
            if(temp_word.find("pc")!=string::npos){
               is_branch=1;
            }
            if(temp_word.find('+')!=string::npos){
               is_pos=1;
            }
            
         }
        int label;
        int Taken;
         
        if(is_branch){
       
                // cout<<"tempword: "<<temp_word<<endl;
                label=stoi(temp_word);

                if(label==4 && is_pos==1){
                  Taken=0;
                }
                else{
                  Taken=1;
                }
       
       
                if(BTB.find(pc)!=BTB.end()){
                        //not first visit
                        // cout<<"Hit:"<<hit;
                        if(BTB[pc].second.back()!=Taken){
                           miss++;
                        }
                        else{
                        hit++;
                        
                        }
       
                 }
                 else{
                   
                   //first visit
                   BTB[pc]={label,history};
                   
                 }

                BTB[pc].second.push_back(Taken);
       

                }

          
         flag=1;
         is_branch=0;
    }

    }

cout<<"miss : "<<miss<<endl;
cout<<"Accuracy: "<<hit*100/(hit+miss);

return 0;

}

