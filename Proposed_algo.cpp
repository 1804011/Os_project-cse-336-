#include<bits/stdc++.h>
#define pb push_back
using namespace std;
typedef long long ll;
void proposed();
struct job{
    ll arrival,burst,priority,idx;
};
bool operator<(job x,job y){
    if(x.priority>y.priority)
          return 1;
    else if(x.priority==y.priority){
         if(x.arrival>y.arrival)
              return 1;
         if(x.arrival==y.arrival)
             return x.idx>y.idx;
         return 0;
    }
    else return 0;
}
bool comp(job x,job y){
    if(x.arrival<y.arrival)
         return 1;
        else if(x.arrival==y.arrival)
              return x.idx<y.idx;
    else return 0;
}

ll arrival[500],waiting[500],turnaround[500],burst[500],finish[500],taken=-1,flag=0,current=0;
int main(){
      proposed();


}

void proposed(){
    ll n,tc,i,u,v,tq;
    ll arrival[500],waiting[500],turnaround[500],burst[500],finish[500],taken=-1,flag=0,current=0;
        vector<job>vct;
         cout<<"Enter The number Of Processes: ";cin>>n;
      cout<<"Enter Time Quantum: ";cin>>tq;
      for(i=0;i<n;i++){
        cout<<"Enter Arrival Time of P"<<i+1<<": ";cin>>u;
       cout<<"Enter Burst Time of P"<<i+1<<": ";cin>>v;
       vct.pb({u,v,v,i});
         arrival[i]=u;
         burst[i]=v;

      }
      sort(vct.begin(),vct.end(),comp);
      priority_queue<job>Q;
         cout<<"==================================================================================="<<endl;
   cout<<"Gantt Chart"<<endl;
   ll idle=0;
      while(taken<n-1){
            taken++;
              Q.push(vct[taken]);
            ll t=vct[taken].arrival;
            for(i=taken+1;i<n;i++){
                if(vct[i].arrival<=t){
                    Q.push(vct[i]);
                    taken++;
                }
            }
                    if(flag==0&&t){
            cout<<0<<" "<<"idle ";
            idle+=t;
        }
        else if(t)
            {cout<<"idle "<<t<<" ";
               idle+=t-current;
            }
    current=t;
         while(!Q.empty()){
               job top=Q.top();
            if(top.burst<=tq){
            if(flag==0){
        cout<<current<<" "<<"P"<<top.idx+1<<" "<<current+top.burst<<" ";
        flag=1;
            }
            else {
                cout<<"P"<<top.idx+1<<" "<<current+top.burst<<" ";
            }
           finish[top.idx]=current+top.burst;
          Q.pop();
          current+=top.burst;

                 for(i=taken+1;i<n;i++){
        if(vct[i].arrival<=current){
                    taken++;
                    Q.push(vct[i]);

                }

          }

      }
                else{
        if(flag==0){
            cout<<current<<" "<<"P"<<top.idx+1<<" "<<current+tq<<" ";
            flag=1;
        }
        else {
            cout<<"P"<<top.idx+1<<" "<<current+tq<<" ";
        }
        current+=tq;
        top.burst-=tq;
        Q.pop();
               for(i=taken+1;i<n;i++){
        if(vct[i].arrival<=current){
                    taken++;
                    Q.push(vct[i]);

                }

          }
          Q.push(top);



      }
         }

      }
      float totalWaiting=0,totalTurnaround=0;
cout<<"\n==================================================================================="<<endl;
        for(i=0;i<n;i++){
                 turnaround[i]=finish[i]-arrival[i];
                 waiting[i]=turnaround[i]-burst[i];
                  totalWaiting+=waiting[i];
                  totalTurnaround+=turnaround[i];
            cout<<"process P"<<i+1<<" End time: "<<finish[i]<<" Turn around Time: "<<turnaround[i]<<" Waiting time: "<<waiting[i]<<endl;
         }
         cout<<"Average Turnaround Time: "<<totalTurnaround/n<<endl;
         cout<<"Average Waiting Time: "<<totalWaiting/n<<endl;
         cout<<"Total Idle Time: "<<idle<<endl;
         cout<<"\n==================================================================================="<<endl;

}
