#include<iostream>
using namespace std;

class os102
{
private:
    int q1size,q2size,noOfProcess,et,tt,qt,sc;//endtime,totalTime
    bool q1empty,q2empty;
    int *nat;//next arrival_time
    int q1index,q2index;
    struct node
    {
        int at;//arrival_time
        int bt;//burst time
        int ct;//completed time
        int id;
        int rt;//remaining time
        bool placed;
    }*all,*q1,*q2;

public:
    os102();
    void get_data();
    void add_arrived_process();
    void sort_q1_q2();
    int pop_arrival_time();
    void process_data();
    void put_data();
    ~os102();
};

os102::os102()
{
    tt=0;et=0;qt=2,sc=0;
    q1index=-1;q2index=-1;
    // q1empty=true;q2empty=true;
    get_data();
    process_data();
    put_data();
}

void os102::get_data(){
    cout<<"enter number of processes: ";
    cin>>noOfProcess;
    all = new node[noOfProcess];
    nat = new int[noOfProcess];
    q1 = new node[noOfProcess/2];
    q2 = new node[noOfProcess-(noOfProcess/2)];
    for(int i = 0; i < noOfProcess; i++)
    {
        cout<<"enter arrival time and burst time of p"<<i+1<<": ";
        cin>>all[i].at>>all[i].bt;
        all[i].placed=false;
        all[i].id=i;
        all[i].rt=all[i].bt;
        nat[i]=all[i].at;
        tt+=all[i].bt;
    }
    // std::cout << tt << '\n';
}

void os102::add_arrived_process() {
  for (int i = 0; i < noOfProcess; i++) {
    // cout<<"\nsus1\n";
    if(i<(noOfProcess/2)){
      if (all[i].at<=et&&all[i].placed==false) {
        // for (int j = 0; j < (noOfProcess/2)-1; j++) {
        //   // cout<<"\nsus2\n";
        //   q1[j+1]=q1[j];
        // }
        // std::cout << "ch1" << '\n';
        // q1index++;
        all[i].placed=true;
        //q1[q1index]=all[i];
        q1[0]=all[i];
      }
    }
    else {
      if (all[i].at<=et&&all[i].placed==false){
        // for (int k = 0; k < (noOfProcess-(noOfProcess/2)); k++) {
        //   // cout<<"\nsus3\n";
        //   q2[k+1]=q2[k];
        // }
        // std::cout << "ch2" << '\n';
        // q2index++;
        all[i].placed=true;
        // q2[q2index]=all[i];
        q2[0]=all[i];
      }
    }
  }
}

void os102::sort_q1_q2() {
  //q1
  node temp;
  for(int i=0;i<(noOfProcess/2);i++)
{
  // cout<<"\nsus4\n";
  for(int j=0;j<(noOfProcess/2);j++)
  {
    // cout<<"\nsus5\n";
    if(q1[i].rt<q1[j].rt){
      temp = q1[i];
      q1[i]=q1[j];
      q1[j]=temp;
    }
   }
}
  //q2
  for(int i=0;i<(noOfProcess-(noOfProcess/2));i++)
{
  // cout<<"\nsus6\n";
  for(int j=0;j<(noOfProcess-(noOfProcess/2));j++)
  {
    // cout<<"\nsus7\n";
    if(q2[i].rt<q2[j].rt){
      temp = q2[i];
      q2[i]=q2[j];
      q2[j]=temp;
    }
   }
}
}

int os102::pop_arrival_time(){
  // for (int i = 0; i < noOfProcess; i++) {
  //   // cout<<"\nsus8\n";
  //   if(nat[i]<=et){
  //     for (int j = i; j < noOfProcess-1; j++) {
  //       // cout<<"\nsus9\n";
  //       nat[j]=nat[j+1];
  //     }
  //     cout<<"nat"<<nat1<<"\n";
  //     break;
  //   }
  // }
  int smallest = 999;
  for (int i = 0; i < noOfProcess; i++) {
    if((all[i].at-et)>0){
       if(smallest>(all[i].at)){
         smallest=(all[i].at);
       }
    }
  }
  return smallest;
}

void os102::process_data(){
  int nat1;
  while(tt>=et){
    // cout<<"\n"<<et<<"\n";
    add_arrived_process();
    sort_q1_q2();
    nat1=pop_arrival_time();
    for (int i = 0; i < (noOfProcess/2); i++) {
      // cout<<q1[i].id<<"q1\n";
    }
    for (int i = 0; i < noOfProcess-(noOfProcess/2); i++) {
      // cout<<q2[i].id<<"q2\n";
    }
    // et++;
    //transverse q1
    q1empty = true;
    for (int i = 0; i < (noOfProcess/2); i++) {
      // cout<<"\nsus11\n";
      if(q1[i].rt>0){
        // cout<<"\nck1\n";
        if(q1[i].rt>(nat1-et)){
          // cout<<"\nck2\n";
          if((nat1-et)<qt){
            // cout<<"\nck3\n";
            et+=(nat1-et);
            q1[i].rt-=(nat1-et);
            q1[i].ct=et;
          }
          else{
            // cout<<"\nck4\n";
            et+=qt;
            q1[i].ct=et;
            q1[i].rt-=qt;
          }
        }
        else{
          // cout<<"\nck5\n";
          if(q1[i].rt>=qt){
            // cout<<"\nck6\n";
            et+=qt;
            q1[i].ct=et;
            q1[i].rt-=qt;
          }
          else{
            // cout<<"\nck7\n";
            et+=q1[i].rt;
            q1[i].ct=et;
            q1[i].rt-=q1[i].rt;
          }
        }
        q1empty=false;
        break;
      }
    }
    //transverse q2
    q2empty = true;
    if (q1empty) {
      for (int i = 0; i < noOfProcess-(noOfProcess/2); i++) {
        // cout<<"\nsus12\n";
        if(q2[i].rt>0){
          // cout<<"\nc1\n";
          if(q2[i].rt>(nat1-et)){
            // cout<<"\nc2\n";
            if((nat1-et)<qt){
              // cout<<"\nc3\n";
              et+=(nat1-et);
              q2[i].rt-=(nat1-et);
              q2[i].ct=et;
            }
            else{
              // cout<<"\nc4\n";
              et+=qt;
              q2[i].ct=et;
              q2[i].rt-=qt;
            }
          }
          else{
            // cout<<"\nc5\n";
            if(q2[i].rt>=qt){
              // cout<<"\nc6\n";
              et+=qt;
              q2[i].ct=et;
              q2[i].rt-=qt;
            }
            else{
              // cout<<"\nc7\n";
              et+=q2[i].rt;
              q2[i].ct=et;
              q2[i].rt-=q2[i].rt;
            }
          }
          q2empty=false;
          break;
        }
      }
    }
    if (q2empty&&q1empty) {
      et++;
      sc++;
    }
  }
}

void os102::put_data(){
  for (int i = 0; i < (noOfProcess/2); i++) {
    all[q1[i].id].ct=q1[i].ct;
  }
  for (int i = 0; i < noOfProcess-(noOfProcess/2); i++) {
    all[q2[i].id].ct=q2[i].ct;
  }
  for(int i = 0; i < noOfProcess; i++)
  {
    // cout<<"\nsus13\n";
      cout<<"P"<<i+1<<" | "<<all[i].at<<" | "<<all[i].bt<<" | "
      <<(all[i].ct-all[i].at-all[i].bt)+sc
      <<" | "<<(all[i].ct-all[i].at)<<"\n";
  }
}

os102::~os102()
{
}

int main(int argc, char const *argv[]) {
  os102 obj;
  return 0;
}
