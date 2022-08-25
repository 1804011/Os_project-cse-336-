#include<bits/stdc++.h>
#define pb push_back
#define pf push_front
#define f(i,n) for(i=0;i<n;i++)
using namespace std;
typedef long long ll;
void FCFS();
struct process{
    ll arrival,burst,idx;
};
bool fcfs(process x,process y){
     if(x.arrival<y.arrival){
        return 1;
     }
     if(x.arrival==y.arrival){
        return x.idx<y.idx;
     }
     return 0;
}

int main(){

FCFS();

}
void FCFS(){
    ll n,i,j,u,v;
    vector<process>vct;
ll arrival[500],burst[600],waiting[500],turnaround[500],finish[500],flag=0,current=0,idle=0;
float totalWaiting=0,totalTurnaround=0;
    cout<<"Enter the number of processes: ";cin>>n;
    for(i=0;i<n;i++){
         cout<<"Enter arrival time of P"<<i+1<<": ";cin>>u;
         cout<<"Enter burst time of P"<<i+1<<": ";cin>>v;
         vct.pb({u,v,i});
         arrival[i]=u;
         burst[i]=v;


    }
    sort(vct.begin(),vct.end(),fcfs);
    cout<<endl<<"Gantt Chart"<<endl<<"==========================================================================================="<<endl;
    f(i,n){
       if(vct[i].arrival>current){
            idle+=vct[i].arrival-current;
            if(flag==0){
                flag=1;
                cout<<current<<" idle "<<vct[i].arrival<<" ";
            }
            else {
                cout<<"idle "<<vct[i].arrival<<" ";
            }
           cout<<"P"<<vct[i].idx+1<<" "<<vct[i].arrival+vct[i].burst<<" ";
            current=vct[i].arrival+vct[i].burst;
            finish[vct[i].idx]=current;
       }
       else {
            if(flag==0){
                flag=1;
                cout<<current<<" P"<<vct[i].idx+1<<" "<<current+vct[i].burst<<" ";
                current+=vct[i].burst;

            }
            else {
                cout<<"P"<<vct[i].idx+1<<" "<<current+vct[i].burst<<" ";
                current+=vct[i].burst;
            }
            finish[vct[i].idx]=current;
       }
    }
    cout<<endl<<"==========================================================================================="<<endl;
    cout<<endl;
    f(i,n){
        turnaround[i]=finish[i]-arrival[i];
        waiting[i]=turnaround[i]-burst[i];
        cout<<"Process P"<<i+1<<" End Time: "<<finish[i]<<" Turnaround Time: "<<turnaround[i]<<" Waiting Time: "<<waiting[i]<<endl;
        totalWaiting+=waiting[i];
        totalTurnaround+=turnaround[i];

    }
    cout<<"Average Waiting Time: "<<totalWaiting/n<<endl;
    cout<<"Average Turnaround Time: "<<totalTurnaround/n<<endl;
    cout<<"Idle Time: "<<idle<<endl;
    cout<<endl;
}
