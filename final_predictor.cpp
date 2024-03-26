#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include<sstream>
#include<map>
#include<iomanip>



using namespace std;

int tester=0;
long flag=1;
long flag_2=1;
long is_branch=0;
long is_pos=0;
long total=0;
long always_taken=0;
long always_Not_taken=0;
long hit_1=0;
long miss_1=0;
long hit_2=0;
long miss_2=0;

map<string,pair<string,vector<long>>> BTBonebit;
map<string,pair<string,vector<long>>> BTBtwobit;

string last_instruction="";

string decimalToHex(unsigned int decimalNumber) {
    stringstream ss;
    ss << "0x" << setfill('0') << setw(8) << hex << decimalNumber;
    return ss.str();
}

void printBTBonebit(const map<string, pair<string, vector<long>>>& BTBonebit) {
    cout << setw(18) << left << "PC" << setw(18) << left << "Target Address" << "Branch History" << endl;
    for (const auto& entry : BTBonebit) {
        cout << setw(18) << left << entry.first << setw(18) << left << entry.second.first;
        for (int i = max(0, (int)entry.second.second.size() - 30); i < entry.second.second.size(); ++i) {
            cout << entry.second.second[i];
        }
        cout << endl;
    }
}


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
    ifstream Myfile("fact.asm");
    vector<string> instruction_set;

    
    int unconditional=0;

    while(getline(Myfile,text)){
    // cout<<"line: "<<tester<<endl;
    // tester++;
      //   cout<<"Count: "<<count<<endl;
      //   count++;
        string temp=text;
        text=last_instruction;
        if(!text.empty()){
         stringstream ss(text);
         stringstream ss2(temp);
         string temp_word;
         string temp_word_2;
         string pc;
         string pc_present;
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
            if(temp_word=="ret"){
                unconditional=1;
            }
            if(temp_word.find('+')!=string::npos){
               is_pos=1;
            }
            
         }
      
         while(getline(ss2,temp_word_2,' ')){
            if(temp_word_2.substr(0,2)=="0x"&&flag_2==1){
            // cout<<temp_word_2<<endl;
            // cout<<"test"<<endl;
                flag_2=1-flag_2;
                pc_present=temp_word_2;
            }
            
         }

       

        long label;
        long Taken;

    //    if(unconditional==1){
    //     total++;
    //     always_taken++;
    //     Taken=1;
    //     // cout<<"here"<<endl;
    //     // single_bit(pc,temp_word,Taken);
    //     // double_bit(pc,temp_word,Taken);
       
    //    }

        string target_address;

        if((is_branch&&temp.find("core")!=string::npos)||unconditional==1){
                // cout<<tester<<endl;
                // cout<<temp_word_2<<endl;
                if(unconditional!=1){
                label=stol(temp_word);
                
                uint32_t dec_last_pc=stoll(pc,nullptr,16);
                uint32_t res;
                // cout<<"pc: "<<pc<<endl;
                if(is_pos){
                res=dec_last_pc+label;
                }
                else{
                res=dec_last_pc-label;
                    }
                // cout<<"current pc: "<<pc_present<<endl;
                target_address=decimalToHex(res);
                uint32_t dec_curr=stoll(pc_present,nullptr,16);
                // cout<<"pc: "<<pc<<endl;
                total++;
                // cout<<"label: "<<label<<"prev_pc: "<<pc<<"currpc: "<<pc_present<<endl;
                if(dec_curr!=res){
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
                //    history.push_back(Taken);
                   BTBonebit[pc]={target_address,history};
                   BTBtwobit[pc]={target_address,history};
                   
                   BTBonebit[pc].second.push_back(1);
                   BTBtwobit[pc].second.push_back(0);
                   BTBtwobit[pc].second.push_back(0);
                 }
                
                }
                else{
                    
                    total++;
                    always_taken++;
                    Taken=1;
                          if(BTBonebit.find(pc)!=BTBonebit.end()){
                                   single_bit(pc,temp_word,Taken);
                                   double_bit(pc,temp_word,Taken);
                          }
                          else{

                                   history.push_back(Taken);
                                   BTBonebit[pc]={target_address,history};
                                   BTBtwobit[pc]={target_address,history};
                          }

                }
                
               
       

                }

          
    }

         flag=1;
         flag_2=1;
         is_branch=0;
         is_pos=0;
         unconditional=0;
         
         
        last_instruction=temp;



    }


// cout<<"hit1: "<<hit_1<<endl;
// cout<<"miss1: "<<miss_1<<endl;
// cout<<"hit2: "<<hit_2<<endl;
// cout<<"miss2: "<<miss_2<<endl;
float accuracy_Always_taken= always_taken*100.0/total;
float accuracy_Always_Not_Taken= always_Not_taken*100.0/total;
float accuracy1= hit_1*100.0/(hit_1+miss_1);
float accuracy2= hit_2*100.0/(hit_2+miss_2);

cout<<"Accuracy(Always Taken): "<<accuracy_Always_taken<<" %"<<endl;
cout<<"Accuracy(Always Not Taken): "<<accuracy_Always_Not_Taken<<" %"<<endl;
cout<<"Accuracy(Single bit): "<<accuracy1<<" %"<<endl;
cout<<"Accuracy(Two bit): "<<accuracy2<<" %"<<endl;
// cout<<"total: "<<total<<endl;
// cout<<"taken: "<<always_taken<<endl;

// cout<<"btb size 1: "<<BTBonebit.size()<<endl;
// cout<<"btb size 2: "<<BTBtwobit.size()<<endl;

cout<<"ONE BIT BTB: "<<endl;
printBTBonebit(BTBonebit);
cout<<endl;
cout<<endl;
cout<<"TWO BIT BTB: "<<endl;
printBTBonebit(BTBtwobit);



return 0;

}
