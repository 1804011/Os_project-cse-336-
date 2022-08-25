#include<bits/stdc++.h>
#define f(i,n) for(i=0;i<n;i++)
#define pb push_back
using namespace std;
typedef long long ll;
void prioritySchedeuling();
struct job{
    ll arrival,burst,priority,idx;
};
bool operator<(job x,job y){
    if(x.priority>y.priority)
        return 1;
    if(x.priority==y.priority){
         if(x.arrival>y.arrival)
            return 1;
         if(x.arrival==y.arrival)
            return x.idx>y.idx;
         return 0;
    }
    return 0;
}
bool comp(job x,job y){
    if(x.arrival<y.arrival)
        return 1;
    if(x.arrival==y.arrival)
        return x.idx<y.idx;
    return 0;
}

int main(){

   prioritySchedeuling();

}
void prioritySchedeuling(){
    vector<job>vct;
priority_queue<job>Q;
ll i,u,v,w,n,taken=-1,current=0,finish[500],arrival[500],burst[500],turnaround[500],waiting[500],flag=0;
     cout<<"Enter the number of processes: ";cin>>n;
        f(i,n){
            cout<<"Enter the Arrival Time of P"<<i+1<<": ";cin>>u;
            cout<<"Enter the Burst Time of P"<<i+1<<": ";cin>>v;
            cout<<"Enter the Priority  of P"<<i+1<<": ";cin>>w;
            vct.pb({u,v,w,i});
            arrival[i]=u;
            burst[i]=v;


        }
      sort(vct.begin(),vct.end(),comp);
     cout<<"================================================================================================"<<endl;
     cout<<"Gantt chart"<<endl;
     ll idle=0;
      while(taken<n-1){
             taken++;
             Q.push(vct[taken]);
             ll t=vct[taken].arrival;
             for(i=taken+1;i<n;i++){
                if(vct[i].arrival==t){
                    Q.push(vct[i]);
                    taken++;
                }
             }

             if(flag==0&&t){
                cout<<0<<" idle ";
                idle+=t;
             }
             else if(t)
                {cout<<"idle "<<t<<" ";
                idle+=t-current;
                }
                current=t;
            while(!Q.empty()){
                job u=Q.top();
                Q.pop();
                if(flag==0){
                    cout<<current<<" P"<<u.idx+1<<" "<<current+u.burst<<" ";
                    flag=1;
                    current+=u.burst;
                }
                else {
                    cout<<"P"<<u.idx+1<<" "<<current+u.burst<<" ";
                    current+=u.burst;

                }
                finish[u.idx]=current;
                for(i=taken+1;i<n;i++){
                    if(vct[i].arrival<=current){
                        Q.push(vct[i]);
                        taken++;
                    }
                }
            }


      }
      cout<<endl;
      cout<<"================================================================================================"<<endl;
      float totalWaiting=0,totalTurnaround=0;
      cout<<endl;
      f(i,n){
           turnaround[i]=finish[i]-arrival[i];
           waiting[i]=turnaround[i]-burst[i];
           totalTurnaround+=turnaround[i];
           totalWaiting+=waiting[i];
           cout<<"Process P"<<i+1<<": End Time: "<<finish[i]<<" Turnaround Time: "<<turnaround[i]<<" Waiting Time: "<<waiting[i]<<endl;

      }
      cout<<"Average waiting time: "<<totalWaiting/n<<endl;
      cout<<"Average turnaround time: "<<totalTurnaround/n<<endl;
      cout<<"Idle Time: "<<idle<<endl;
       cout<<"================================================================================================"<<endl;
}

