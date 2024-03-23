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
int total=0;
int hit_1=0;
int miss_1=0;
int hit_2=0;
int miss_2=0;
map<string,pair<int,vector<int>>> BTB;




void single_bit(string pc,string temp_word){
        vector<int> history;
        int label;
        int Taken;
         
       
       
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
                           miss_1++;
                        }
                        else{
                        hit_1++;
                        
                        }
       
                 }
                 else{
                   
                   //first visit
                   BTB[pc]={label,history};
                   
                 }

                BTB[pc].second.push_back(Taken);
       

                
}


void single_bit(string pc,string temp_word){
        vector<int> history;
        int label;
        int Taken;
         
       
       
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
                           miss_1++;
                        }
                        else{
                        hit_1++;
                        
                        }
       
                 }
                 else{
                   
                   //first visit
                   BTB[pc]={label,history};
                   
                 }

                BTB[pc].second.push_back(Taken);
       

                
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
         
         if(is_branch){
         total++;
         single_bit(pc,temp_word);
          
         }
         flag=1;
         is_branch=0;
    }

    }

float accuracy1= hit_1*100/(hit_1+miss_1);
float accuracy2= hit_2*100/(hit_2+miss_2);

cout<<"Accuracy(Single bit): "<<accuracy1<<endl;
cout<<"Accuracy(Two bit): "<<accuracy2<<endl;

return 0;

}

