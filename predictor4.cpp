#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include<sstream>
#include<map>



using namespace std;

long flag=1;
long is_branch=0;
long is_pos=0;
long total=0;
long always_taken=0;
long always_Not_taken=0;
long hit_1=0;
long miss_1=0;
long hit_2=0;
long miss_2=0;

map<string,pair<long,vector<long>>> BTBonebit;
map<string,pair<long,vector<long>>> BTBtwobit;




void single_bit(string pc,string temp_word,long Taken){


            //not first visit
            // cout<<"Hit:"<<hit;


                      if(BTBonebit[pc].second.back()!=Taken){
                         miss_1++;
                      }
                      else{
                      hit_1++;
            
                       }

               BTBonebit[pc].second.push_back(Taken);
       

}

void double_bit(string pc,string temp_word,long Taken){


            //not first visit
            // cout<<"Hit:"<<hit;
            long size=BTBtwobit[pc].second.size();
            long last=BTBtwobit[pc].second[size-1];
            
            long second_last=BTBtwobit[pc].second[size-2];
         
            if( (last==1&&second_last==1&&Taken==1) || (second_last==0&&last==0&&Taken==0)){
                hit_2++;
            }
            else if((last==1&&second_last==0&&Taken==0) || (second_last==1&&last==0&&Taken==1)){
                hit_2++;
            }
            else{
                miss_2++;
            }
            
               BTBtwobit[pc].second.push_back(Taken);
            

       

}



long count=0;
int main(){

// take input from the file

    string text;
    ifstream Myfile("qsort.asm");
    vector<string> instruction_set;

    

    while(getline(Myfile,text)){

      //   cout<<"Count: "<<count<<endl;
      //   count++;
        if(!text.empty()){

         stringstream ss(text);
         string temp_word;
         string pc;
         vector<long> history;
         while(getline(ss,temp_word,' ')){
            if(temp_word.substr(0,2)=="0x"&&flag==1){
                flag=1-flag;
                pc=temp_word;
            }
            if(temp_word=="pc"){
               is_branch=1;
            }
            // if(temp_word.find("pc")!=string::npos && temp_word!="auipc"){
            //    is_branch=1;
            // }
            if(temp_word.find('+')!=string::npos){
               is_pos=1;
            }
            
         }
        long label;
        long Taken;
         
        if(is_branch){
       
               //  cout<<temp_word<<endl;
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
          

                 if(BTBonebit.find(pc)!=BTBonebit.end()){

                           single_bit(pc,temp_word,Taken);
                           double_bit(pc,temp_word,Taken);
       
                 }
                 else{
                   
                   //first visit
                   history.push_back(Taken);
                   BTBonebit[pc]={label,history};
                   BTBtwobit[pc]={label,history};
                   
                   BTBonebit[pc].second.push_back(1);
                   BTBtwobit[pc].second.push_back(0);
                   BTBtwobit[pc].second.push_back(0);
                 }
       
                
               
       

                }

          
    }

         flag=1;
         is_branch=0;
         is_pos=0;

    }


// cout<<"hit1: "<<hit_1<<endl;
// cout<<"miss1: "<<miss_1<<endl;
// cout<<"hit2: "<<hit_2<<endl;
// cout<<"miss2: "<<miss_2<<endl;
float accuracy_Always_taken= always_taken*100.0/total;
float accuracy_Always_Not_Taken= always_Not_taken*100.0/total;
float accuracy1= hit_1*100.0/(hit_1+miss_1+1);
float accuracy2= hit_2*100.0/(hit_2+miss_2+1);

cout<<"Accuracy(Always Taken): "<<accuracy_Always_taken<<" %"<<endl;
cout<<"Accuracy(Always Not Taken): "<<accuracy_Always_Not_Taken<<" %"<<endl;
cout<<"Accuracy(Single bit): "<<accuracy1<<" %"<<endl;
cout<<"Accuracy(Two bit): "<<accuracy2<<" %"<<endl;

// cout<<"btb size 1: "<<BTBonebit.size()<<endl;
// cout<<"btb size 2: "<<BTBtwobit.size()<<endl;
return 0;

}

