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
int always_taken=0;
int always_Not_taken=0;
int hit_1=0;
int miss_1=0;
int hit_2=0;
int miss_2=0;

map<string,pair<int,vector<int>>> BTB;




void single_bit(string pc,string temp_word,int Taken){


            //not first visit
            // cout<<"Hit:"<<hit;


                      if(BTB[pc].second.back()!=Taken){
                         miss_1++;
                      }
                      else{
                      hit_1++;
            
                       }

       

}
void double_bit(string pc,string temp_word,int Taken){


            //not first visit
            // cout<<"Hit:"<<hit;
            int size=BTB[pc].second.size();
            int last=BTB[pc].second[size-1];
            if(size>1){
                     int second_last=BTB[pc].second[size-2];
         
                     if((last==Taken&&second_last==Taken)||(last!=Taken&&second_last==Taken))
                     {
                               hit_2++;
         
                     }
                     else{
                              miss_2++;
         
                     }
                     
            }
            else{

                if(BTB[pc].second.back()!=Taken){
                               hit_2++;
                }
                else{
                              miss_2++;
                
                }
            }

       

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
                total++;

                if(label==4 && is_pos==1){
                  Taken=0;
                  always_Not_taken++;
                }
                else{
                  Taken=1;
                  always_taken++;
                }
          

                 if(BTB.find(pc)!=BTB.end()){

                           single_bit(pc,temp_word,Taken);
                           double_bit(pc,temp_word,Taken);
       
                 }
                 else{
                   
                   //first visit
                   history.push_back(Taken);
                   BTB[pc]={label,history};
                   
                 }
       
                

               BTB[pc].second.push_back(Taken);
       

                }

          
         flag=1;
         is_branch=0;
    }

    }

float accuracy_Always_taken= always_taken*100/total;
float accuracy_Always_Not_Taken= always_Not_taken*100/total;
float accuracy1= hit_1*100/(hit_1+miss_1);
float accuracy2= hit_2*100/(hit_2+miss_2);

cout<<"Accuracy(Always Taken): "<<accuracy_Always_taken<<" %"<<endl;
cout<<"Accuracy(Always Not Taken): "<<accuracy_Always_Not_Taken<<" %"<<endl;
cout<<"Accuracy(Single bit): "<<accuracy1<<" %"<<endl;
cout<<"Accuracy(Two bit): "<<accuracy2<<" %"<<endl;


return 0;

}

