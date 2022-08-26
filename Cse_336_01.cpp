#include<bits/stdc++.h>
#define f(i,n) for(i=0;i<n;i++)
#define pb push_back
#define pf push_front
using namespace std;
typedef long long ll;
 ll n,tc,i,u,v,tq;
 ll arrival[500],waiting[500],turnaround[500],burst[500],finish[500],response[500];
ll priority[500];
void roundRobin();
void prioritySchedeuling();
void preemptiveSJF();
void preemptivePriority();
void FCFS();
void SJF();
void proposed();
void roundRobin1();
void prioritySchedeuling1();
void preemptiveSJF1();
void preemptivePriority1();
void FCFS1();
void SJF1();
void proposed1();

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
        else if(x.arrival==y.arrival)
              return x.idx<y.idx;
    else return 0;
}
void takeInput(){
    ll w;
      cout<<"Enter The number Of Processes: ";cin>>n;
      cout<<"Enter Time Quantum: ";cin>>tq;
       for(i=0;i<n;i++){
        cout<<"Enter Arrival Time of P"<<i+1<<": ";cin>>u;
        cout<<"Enter Burst Time of P"<<i+1<<": ";cin>>v;
        cout<<"Enter the Priority  of P"<<i+1<<": ";cin>>w;

       arrival[i]=u;
       burst[i]=v;
       priority[i]=w;
 }
}
ll timeQuantum(deque<process>Q){
    map<ll,ll>mp;
    ll total=0,burst=0;
    while(!Q.empty()){
       process u=Q.front();
       ll burst=u.burst;
       if(mp.find(burst)==mp.end()) mp[burst]=1;
       else mp[burst]++;
       Q.pop_front(); 
    }
    for(auto itr=mp.begin();itr!=mp.end();itr++){
        ll fst=itr->first;
        ll scd=itr->second;
        total+=fst*scd;
        burst+=fst;
    }
    ll tq=total/burst;
    if(tq>0) return tq;
    else return 1;
}
void makeChoice(){
     ll choice;
     cout<<"1: FCFS\n2: Non-Preemptive-SJF\n3: Preemptive-SJF\n4: Non-Preemptive-Priority\n5: Preemptive-Priority\n6: Round-Robin\n7: Our-Proposed-Algorithm\n8: Compare-All\n9: Exit"<<endl;
   cout<<"Enter Your Choice: ";cin>>choice;
   switch(choice){
     case 1:
        FCFS(); break;
     case 2:
        SJF(); break;
     case 3:
        preemptiveSJF(); break;
     case 4:
         prioritySchedeuling(); break;
     case 5:
        preemptivePriority(); break;
     case 6:
        roundRobin();break;
     case 7:
        proposed();break;
     case 8:
         takeInput();
         FCFS1(); 
         SJF1();
         preemptiveSJF1();
         prioritySchedeuling1();
         preemptivePriority1();
         roundRobin1();
         proposed1();
        break;
     case 9:
        exit(0);
        break;

   }
   char ch;
   cout<<"Press any key for the home page\n";
   cin>>ch;
   makeChoice();


}
int main(){
     makeChoice();
}


void roundRobin(){
    ll n,tc,i,u,v,tq;
ll arrival[500],waiting[500],turnaround[500],burst[500],finish[500],response[500];
  f(i,500) response[i]=500;

vector<process>vct;
      cout<<"Enter The number Of Processes: ";cin>>n;
      cout<<"Enter Time Quantum: ";cin>>tq;
      for(i=0;i<n;i++){
        cout<<"Enter Arrival Time of P"<<i+1<<": ";cin>>u;
       cout<<"Enter Burst Time of P"<<i+1<<": ";cin>>v;
       vct.pb({u,v,i});
       arrival[i]=u;
       burst[i]=v;

      }
      sort(vct.begin(),vct.end(),fcfs);
   deque<process>Q;
   cout<<"=========================================="<<endl;
   cout<<"Gantt Chart"<<endl;
    ll current=vct[0].arrival;
    ll taken=-1;
    ll flag=0;
    ll sz=vct.size();
    ll idle=0;
  while(taken<n-1){
        taken++;
        Q.push_front(vct[taken]);
        ll t=vct[taken].arrival;
        if(flag==0&&t){
            cout<<0<<" "<<"idle ";
            idle+=t;
            flag=1;
        }
        else if(t)
            {cout<<"idle "<<t<<" ";
            idle+=t-current;
            }
            current=t;

    while(!Q.empty()){
      process top=Q.front();
      if(top.burst<=tq){
            if(flag==0){
        cout<<current<<" "<<"P"<<top.idx+1<<" "<<current+top.burst<<" ";
          response[top.idx]=min(response[top.idx],current);
        flag=1;
            }
            else {
                cout<<"P"<<top.idx+1<<" "<<current+top.burst<<" ";
              response[top.idx]=min(response[top.idx],current);

            }
           finish[top.idx]=current+top.burst;
          Q.pop_front();
          current+=top.burst;

                 for(i=taken+1;i<sz;i++){
        if(vct[i].arrival<=current){
                    taken++;
                    Q.pb(vct[i]);

                }

          }

      }
      else{
        if(flag==0){
            cout<<current<<" "<<"P"<<top.idx+1<<" "<<current+tq<<" ";
            response[top.idx]=min(response[top.idx],current);

            flag=1;
        }
        else {
            cout<<"P"<<top.idx+1<<" "<<current+tq<<" ";
                      response[top.idx]=min(response[top.idx],current);

        }
        current+=tq;
        top.burst-=tq;
        Q.pop_front();
               for(i=taken+1;i<sz;i++){
        if(vct[i].arrival<=current){
                    taken++;
                    Q.pb(vct[i]);

                }

          }
          Q.pb(top);



      }




    }
  }
     cout<<"\n=========================================="<<endl;
     float totalWaiting=0,totalTurnaround=0;
         for(i=0;i<n;i++){
            turnaround[i]=finish[i]-arrival[i];
            waiting[i]=turnaround[i]-burst[i];
            totalTurnaround+=turnaround[i];
            totalWaiting+=waiting[i];
                    cout<<"Process P"<<i+1<<" End Time: "<<finish[i]<<" Response Time: "<<response[i]<<" Waiting Time: "<<waiting[i]<<" Turnaround Time: "<<turnaround[i]<<endl;

         }
         cout<<"Average Turnaround Time: "<<totalTurnaround/n<<endl;
         cout<<"Average Waiting Time: "<<totalWaiting/n<<endl;
         cout<<"Idle Time: "<<idle<<endl;
}
void prioritySchedeuling(){
    vector<job>vct;
priority_queue<job>Q;
ll response[500],i,u,v,w,n,taken=-1,current=0,finish[500],arrival[500],burst[500],turnaround[500],waiting[500],flag=0;
      for(i=0;i<500;i++) response[i]=1000000000000;
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
                    response[u.idx]=min(current,response[u.idx]);
                    current+=u.burst;
                }
                else {
                    cout<<"P"<<u.idx+1<<" "<<current+u.burst<<" ";
                    response[u.idx]=min(current,response[u.idx]);
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
        cout<<"Process P"<<i+1<<" End Time: "<<finish[i]<<" Response Time: "<<response[i]<<" Waiting Time: "<<waiting[i]<<" Turnaround Time: "<<turnaround[i]<<endl;

      }
      cout<<"Average waiting time: "<<totalWaiting/n<<endl;
      cout<<"Average turnaround time: "<<totalTurnaround/n<<endl;
      cout<<"Idle Time: "<<idle<<endl;
       cout<<"================================================================================================"<<endl;
}
void FCFS(){
    ll n,i,j,u,v;
    vector<process>vct;
ll arrival[500],burst[600],waiting[500],response[500],turnaround[500],finish[500],flag=0,current=0,idle=0;
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
           response[vct[i].idx]=vct[i].arrival;
            current=vct[i].arrival+vct[i].burst;
            finish[vct[i].idx]=current;
       }
       else {
            if(flag==0){
                flag=1;
                cout<<current<<" P"<<vct[i].idx+1<<" "<<current+vct[i].burst<<" ";
               response[vct[i].idx]=current;
                current+=vct[i].burst;

            }
            else {
                cout<<"P"<<vct[i].idx+1<<" "<<current+vct[i].burst<<" ";
                response[vct[i].idx]=current;
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
        cout<<"Process P"<<i+1<<" End Time: "<<finish[i]<<" Response Time: "<<response[i]<<" Waiting Time: "<<waiting[i]<<" Turnaround Time: "<<turnaround[i]<<endl;
        totalWaiting+=waiting[i];
        totalTurnaround+=turnaround[i];

    }
    cout<<"Average Waiting Time: "<<totalWaiting/n<<endl;
    cout<<"Average Turnaround Time: "<<totalTurnaround/n<<endl;
    cout<<"Idle Time: "<<idle<<endl;
    cout<<endl;
}
void preemptivePriority(){
    ll response[500],i,u,v,w,n,taken=-1,current=0,finish[500],arrival[500],burst[500],turnaround[500],waiting[500],flag=0;
    f(i,500) response[i]=1e16;
    vector<job>vct;
             cout<<"Enter the number of processes: ";cin>>n;
        f(i,n){
            cout<<"Enter the Arrival Time of P"<<i+1<<": ";cin>>u;
            cout<<"Enter the Burst Time of P"<<i+1<<": ";cin>>v;
            cout<<"Enter the Priority of P"<<i+1<<": ";cin>>w;
            vct.pb({u,v,w,i});
            arrival[i]=u;
            burst[i]=v;

         }
         sort(vct.begin(),vct.end(),comp);
              cout<<"================================================================================================"<<endl;
     cout<<"Gantt chart"<<endl;
     ll idle=0;
     priority_queue<job>Q;
     while(taken<n-1){
             taken++;
             Q.push(vct[taken]);
             ll t=vct[taken].arrival;
             for(i=taken+1;i<n;i++){
                if(vct[i].arrival==t){
                    Q.push(vct[i]);
                    taken++;
                }
                else break;
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
               if(taken<n-1){
                 ll tq=vct[taken+1].arrival-current;
                 ll mn=min(tq,u.burst);

                        if(flag==0){
                            cout<<current<<" P"<<u.idx+1<<" "<<current+mn<<" ";
                            flag=1;
                        }
                        else {
                            cout<<"P"<<u.idx+1<<" "<<current+mn<<" ";
                        }
                      response[u.idx]=min(response[u.idx],current);

                        current+=mn;
                        u.burst-=mn;
                        Q.pop();
                        for(i=taken+1;i<n;i++){
                            if(vct[i].arrival<=current){
                                Q.push(vct[i]);
                                taken++;
                            }
                        }
                        if(u.burst)
                             Q.push(u);
                       else finish[u.idx]=current;


                  }
               else {
                  Q.pop();
                if(flag==0){
                    cout<<current<<" P"<<u.idx+1<<" "<<current+u.burst<<" ";
                    flag=1;
                    response[u.idx]=min(response[u.idx],current);

                    current+=u.burst;
                }
                else {
                    cout<<"P"<<u.idx+1<<" "<<current+u.burst<<" ";
                response[u.idx]=min(response[u.idx],current);
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
        cout<<"Process P"<<i+1<<" End Time: "<<finish[i]<<" Response Time: "<<response[i]<<" Waiting Time: "<<waiting[i]<<" Turnaround Time: "<<turnaround[i]<<endl;

      }
      cout<<"Average waiting time: "<<totalWaiting/n<<endl;
      cout<<"Average turnaround time: "<<totalTurnaround/n<<endl;
      cout<<"Idle Time: "<<idle<<endl;
       cout<<"================================================================================================"<<endl;
}
void SJF(){
    ll response[500],i,u,v,w,n,taken=-1,current=0,finish[500],arrival[500],burst[500],turnaround[500],waiting[500],flag=0;
    vector<job>vct;
priority_queue<job>Q;
            cout<<"Enter the number of processes: ";cin>>n;
        f(i,n){
            cout<<"Enter the Arrival Time of P"<<i+1<<": ";cin>>u;
            cout<<"Enter the Burst Time of P"<<i+1<<": ";cin>>v;
            vct.pb({u,v,v,i});
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
                    response[u.idx]=current;
                    flag=1;
                    current+=u.burst;
                }
                else {
                    cout<<"P"<<u.idx+1<<" "<<current+u.burst<<" ";
                    response[u.idx]=current;
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
    cout<<"Process P"<<i+1<<" End Time: "<<finish[i]<<" Response Time: "<<response[i]<<" Waiting Time: "<<waiting[i]<<" Turnaround Time: "<<turnaround[i]<<endl;

      }
      cout<<"Average waiting time: "<<totalWaiting/n<<endl;
      cout<<"Average turnaround time: "<<totalTurnaround/n<<endl;
      cout<<"Idle Time: "<<idle<<endl;
       cout<<"================================================================================================"<<endl;
}
void preemptiveSJF(){
    ll response[500],i,u,v,w,n,taken=-1,current=0,finish[500],arrival[500],burst[500],turnaround[500],waiting[500],flag=0;
     for(ll i=0;i<500;i++) response[i]=1000000000000;
    vector<job>vct;
             cout<<"Enter the number of processes: ";cin>>n;

        f(i,n){
            cout<<"Enter the Arrival Time of P"<<i+1<<": ";cin>>u;
            cout<<"Enter the Burst Time of P"<<i+1<<": ";cin>>v;

            vct.pb({u,v,v,i});
            arrival[i]=u;
            burst[i]=v;

         }
         sort(vct.begin(),vct.end(),comp);
              cout<<"================================================================================================"<<endl;
     cout<<"Gantt chart"<<endl;
     ll idle=0;
     priority_queue<job>Q;
     while(taken<n-1){
             taken++;
             Q.push(vct[taken]);
             ll t=vct[taken].arrival;
             for(i=taken+1;i<n;i++){
                if(vct[i].arrival==t){
                    Q.push(vct[i]);
                    taken++;
                }
                else break;
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
               if(taken<n-1){
                 ll tq=vct[taken+1].arrival-current;
                 ll mn=min(tq,u.burst);

                        if(flag==0){
                            cout<<current<<" P"<<u.idx+1<<" "<<current+mn<<" ";
                             response[u.idx]=min(current,response[u.idx]);
                            flag=1;
                        }
                        else {
                            cout<<"P"<<u.idx+1<<" "<<current+mn<<" ";
                            response[u.idx]=min(current,response[u.idx]);
                        }
                        current+=mn;
                        u.burst-=mn;
                        Q.pop();
                        for(i=taken+1;i<n;i++){
                            if(vct[i].arrival<=current){
                                Q.push(vct[i]);
                                taken++;
                            }
                        }
                        if(u.burst)
                             Q.push(u);
                       else finish[u.idx]=current;


                  }
               else {
                  Q.pop();
                if(flag==0){
                    cout<<current<<" P"<<u.idx+1<<" "<<current+u.burst<<" ";
                    flag=1;
                response[u.idx]=min(current,response[u.idx]);

                    current+=u.burst;
                }
                else {
                    cout<<"P"<<u.idx+1<<" "<<current+u.burst<<" ";
                response[u.idx]=min(current,response[u.idx]);
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
    cout<<"Process P"<<i+1<<" End Time: "<<finish[i]<<" Response Time: "<<response[i]<<" Waiting Time: "<<waiting[i]<<" Turnaround Time: "<<turnaround[i]<<endl;

      }
      cout<<"Average waiting time: "<<totalWaiting/n<<endl;
      cout<<"Average turnaround time: "<<totalTurnaround/n<<endl;
      cout<<"Idle Time: "<<idle<<endl;
       cout<<"================================================================================================"<<endl;
}
void proposed(){
     ll n,tc,i,u,v,tq;
ll arrival[500],waiting[500],turnaround[500],burst[500],finish[500],response[500];
  f(i,500) response[i]=500;

vector<process>vct;
      cout<<"Enter The number Of Processes: ";cin>>n;
    
      for(i=0;i<n;i++){
        cout<<"Enter Arrival Time of P"<<i+1<<": ";cin>>u;
       cout<<"Enter Burst Time of P"<<i+1<<": ";cin>>v;
       vct.pb({u,v,i});
       arrival[i]=u;
       burst[i]=v;

      }
      sort(vct.begin(),vct.end(),fcfs);
   deque<process>Q;
   cout<<"=========================================="<<endl;
   cout<<"Gantt Chart"<<endl;
    ll current=vct[0].arrival;
    ll taken=-1;
    ll flag=0;
    ll sz=vct.size();
    ll idle=0;
  while(taken<n-1){
        taken++;
        Q.push_front(vct[taken]);
        tq=timeQuantum(Q);
        ll t=vct[taken].arrival;
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
      process top=Q.front();
     tq=timeQuantum(Q);
      if(top.burst<=tq){
            if(flag==0){
        cout<<current<<" "<<"P"<<top.idx+1<<" "<<current+top.burst<<" ";
          response[top.idx]=min(response[top.idx],current);
        flag=1;
            }
            else {
                cout<<"P"<<top.idx+1<<" "<<current+top.burst<<" ";
              response[top.idx]=min(response[top.idx],current);

            }
           finish[top.idx]=current+top.burst;
          Q.pop_front();
          current+=top.burst;

                 for(i=taken+1;i<sz;i++){
        if(vct[i].arrival<=current){
                    taken++;
                    Q.pb(vct[i]);

                }

          }
     
      }
      else{
        if(flag==0){
            cout<<current<<" "<<"P"<<top.idx+1<<" "<<current+tq<<" ";
            response[top.idx]=min(response[top.idx],current);

            flag=1;
        }
        else {
            cout<<"P"<<top.idx+1<<" "<<current+tq<<" ";
                      response[top.idx]=min(response[top.idx],current);

        }
        current+=tq;
        top.burst-=tq;
        Q.pop_front();
               for(i=taken+1;i<sz;i++){
        if(vct[i].arrival<=current){
                    taken++;
                    Q.pb(vct[i]);

                }

          }
          Q.pb(top);
          
    


      }

    }
  }
     cout<<"\n=========================================="<<endl;
     float totalWaiting=0,totalTurnaround=0;
         for(i=0;i<n;i++){
            turnaround[i]=finish[i]-arrival[i];
            waiting[i]=turnaround[i]-burst[i];
            totalTurnaround+=turnaround[i];
            totalWaiting+=waiting[i];
                    cout<<"Process P"<<i+1<<" End Time: "<<finish[i]<<" Response Time: "<<response[i]<<" Waiting Time: "<<waiting[i]<<" Turnaround Time: "<<turnaround[i]<<endl;

         }
         cout<<"Average Turnaround Time: "<<totalTurnaround/n<<endl;
         cout<<"Average Waiting Time: "<<totalWaiting/n<<endl;
         cout<<"Idle Time: "<<idle<<endl;

}

void roundRobin1(){
     f(i,500) response[i]=500;
     vector<process>vct;
     for(i=0;i<n;i++)
       vct.pb({arrival[i],burst[i],i});
      
      sort(vct.begin(),vct.end(),fcfs);
    deque<process>Q;
    ll current=vct[0].arrival;
    ll taken=-1;
    ll flag=0;
    ll sz=vct.size();
    ll idle=0;
  while(taken<n-1){
        taken++;
        Q.push_front(vct[taken]);
        ll t=vct[taken].arrival;
        if(flag==0&&t){
          idle+=t;
        }
        else if(t)
            {
            idle+=t-current;
            }
            current=t;

    while(!Q.empty()){
      process top=Q.front();
      if(top.burst<=tq){
            if(flag==0){
          response[top.idx]=min(response[top.idx],current);
        flag=1;
            }
            else {
              response[top.idx]=min(response[top.idx],current);
            }
           finish[top.idx]=current+top.burst;
          Q.pop_front();
          current+=top.burst;
            for(i=taken+1;i<sz;i++){
            if(vct[i].arrival<=current){
                    taken++;
                    Q.pb(vct[i]);

                }
    }
  }
      else{
        if(flag==0){
            response[top.idx]=min(response[top.idx],current);
            flag=1;
        }
        else {
        response[top.idx]=min(response[top.idx],current);
        }
        current+=tq;
        top.burst-=tq;
        Q.pop_front();
               for(i=taken+1;i<sz;i++){
        if(vct[i].arrival<=current){
                    taken++;
                    Q.pb(vct[i]);

                }

          }
          Q.pb(top);
   }
    }
  }
     float totalWaiting=0,totalTurnaround=0;
         for(i=0;i<n;i++){
            turnaround[i]=finish[i]-arrival[i];
            waiting[i]=turnaround[i]-burst[i];
            totalTurnaround+=turnaround[i];
            totalWaiting+=waiting[i];

         }
    float avgWaiting=totalWaiting/n,avgTurnaround=totalTurnaround/n;
    cout<<"Algorithm 6: Average Waiting Time: "<<avgWaiting<<"\t   Average Turnaroundtime: "<<avgTurnaround<<endl;
}
void prioritySchedeuling1(){
    vector<job>vct;
priority_queue<job>Q;
ll taken=-1,current=0,flag=0;
      for(i=0;i<500;i++) response[i]=1e16;
        f(i,n)
        vct.pb({arrival[i],burst[i],priority[i],i});
      sort(vct.begin(),vct.end(),comp);
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
              
                idle+=t;
             }
             else if(t)
                {
                idle+=t-current;
                }
                current=t;
            while(!Q.empty()){
                job u=Q.top();
                Q.pop();
                if(flag==0){
                    flag=1;
                    response[u.idx]=min(current,response[u.idx]);
                    current+=u.burst;
                }
                else {
                    response[u.idx]=min(current,response[u.idx]);
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
      float totalWaiting=0,totalTurnaround=0;
      f(i,n){
           turnaround[i]=finish[i]-arrival[i];
           waiting[i]=turnaround[i]-burst[i];
           totalTurnaround+=turnaround[i];
           totalWaiting+=waiting[i];

      }
      float avgWaiting=totalWaiting/n,avgTurnaround=totalTurnaround/n;
    cout<<"Algorithm 4: Average Waiting Time: "<<avgWaiting<<"\t   Average Turnaroundtime: "<<avgTurnaround<<endl;

}
void FCFS1(){
    vector<process>vct;
ll flag=0,current=0,idle=0;
float totalWaiting=0,totalTurnaround=0;
    for(i=0;i<n;i++)
         vct.pb({arrival[i],burst[i],i}); 
    sort(vct.begin(),vct.end(),fcfs);
    f(i,n){
       if(vct[i].arrival>current){
            idle+=vct[i].arrival-current;
            if(flag==0){
                flag=1;    
            }
            response[vct[i].idx]=vct[i].arrival;
            current=vct[i].arrival+vct[i].burst;
            finish[vct[i].idx]=current;
       }
       else {
            if(flag==0){
                flag=1;
               response[vct[i].idx]=current;
                current+=vct[i].burst;

            }
            else {
                response[vct[i].idx]=current;
                current+=vct[i].burst;
            }
            finish[vct[i].idx]=current;
       }
    }
    f(i,n){
        turnaround[i]=finish[i]-arrival[i];
        waiting[i]=turnaround[i]-burst[i];
        totalWaiting+=waiting[i];
        totalTurnaround+=turnaround[i];

    }
    float avgWaiting=totalWaiting/n,avgTurnaround=totalTurnaround/n;
    cout<<"Algorithm 1: Average Waiting Time: "<<avgWaiting<<"\t   Average Turnaroundtime: "<<avgTurnaround<<endl;
}
void preemptivePriority1(){
ll taken=-1,current=0,flag=0;
    f(i,500) response[i]=1e16;
    vector<job>vct;
        f(i,n)
             vct.pb({arrival[i],burst[i],priority[i],i});
       sort(vct.begin(),vct.end(),comp);         
     ll idle=0;
     priority_queue<job>Q;
     while(taken<n-1){
             taken++;
             Q.push(vct[taken]);
             ll t=vct[taken].arrival;
             for(i=taken+1;i<n;i++){
                if(vct[i].arrival==t){
                    Q.push(vct[i]);
                    taken++;
                }
                else break;
             }

             if(flag==0&&t){
                idle+=t;
             }
             else if(t)
                {
                idle+=t-current;
                }
                current=t;
           while(!Q.empty()){
               job u=Q.top();
               if(taken<n-1){
                 ll tq=vct[taken+1].arrival-current;
                 ll mn=min(tq,u.burst);

                        if(flag==0){
                            flag=1;
                        }
                      response[u.idx]=min(response[u.idx],current);
                        current+=mn;
                        u.burst-=mn;
                        Q.pop();
                        for(i=taken+1;i<n;i++){
                            if(vct[i].arrival<=current){
                                Q.push(vct[i]);
                                taken++;
                            }
                        }
                        if(u.burst)
                             Q.push(u);
                       else finish[u.idx]=current;


                  }
               else {
                  Q.pop();
                if(flag==0){
                    flag=1;
                    response[u.idx]=min(response[u.idx],current);
                    current+=u.burst;
                }
                else {
                response[u.idx]=min(response[u.idx],current);
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


     }
            float totalWaiting=0,totalTurnaround=0;
      f(i,n){
           turnaround[i]=finish[i]-arrival[i];
           waiting[i]=turnaround[i]-burst[i];
           totalTurnaround+=turnaround[i];
           totalWaiting+=waiting[i];
      }
      float avgWaiting=totalWaiting/n,avgTurnaround=totalTurnaround/n;
    cout<<"Algorithm 5: Average Waiting Time: "<<avgWaiting<<"\t   Average Turnaroundtime: "<<avgTurnaround<<endl;

    
}
void SJF1(){
    vector<job>vct;
priority_queue<job>Q;
ll taken=-1,current=0,flag=0;
      for(i=0;i<500;i++) response[i]=1e16;
        f(i,n)
        vct.pb({arrival[i],burst[i],burst[i],i});
      sort(vct.begin(),vct.end(),comp);
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
              
                idle+=t;
             }
             else if(t)
                {
                idle+=t-current;
                }
                current=t;
            while(!Q.empty()){
                job u=Q.top();
                Q.pop();
                if(flag==0){
                    flag=1;
                    response[u.idx]=min(current,response[u.idx]);
                    current+=u.burst;
                }
                else {
                    response[u.idx]=min(current,response[u.idx]);
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
      float totalWaiting=0,totalTurnaround=0;
      f(i,n){
           turnaround[i]=finish[i]-arrival[i];
           waiting[i]=turnaround[i]-burst[i];
           totalTurnaround+=turnaround[i];
           totalWaiting+=waiting[i];

      }
      float avgWaiting=totalWaiting/n,avgTurnaround=totalTurnaround/n;
    cout<<"Algorithm 2: Average Waiting Time: "<<avgWaiting<<"\t   Average Turnaroundtime: "<<avgTurnaround<<endl;
}
void preemptiveSJF1(){
    ll taken=-1,current=0,flag=0;
    f(i,500) response[i]=1e16;
    vector<job>vct;
        f(i,n)
             vct.pb({arrival[i],burst[i],burst[i],i});
       sort(vct.begin(),vct.end(),comp);         
     ll idle=0;
     priority_queue<job>Q;
     while(taken<n-1){
             taken++;
             Q.push(vct[taken]);
             ll t=vct[taken].arrival;
             for(i=taken+1;i<n;i++){
                if(vct[i].arrival==t){
                    Q.push(vct[i]);
                    taken++;
                }
                else break;
             }

             if(flag==0&&t){
                idle+=t;
             }
             else if(t)
                {
                idle+=t-current;
                }
                current=t;
           while(!Q.empty()){
               job u=Q.top();
               if(taken<n-1){
                 ll tq=vct[taken+1].arrival-current;
                 ll mn=min(tq,u.burst);

                        if(flag==0){
                            flag=1;
                        }
                      response[u.idx]=min(response[u.idx],current);
                        current+=mn;
                        u.burst-=mn;
                        Q.pop();
                        for(i=taken+1;i<n;i++){
                            if(vct[i].arrival<=current){
                                Q.push(vct[i]);
                                taken++;
                            }
                        }
                        if(u.burst)
                             Q.push(u);
                       else finish[u.idx]=current;


                  }
               else {
                  Q.pop();
                if(flag==0){
                    flag=1;
                    response[u.idx]=min(response[u.idx],current);
                    current+=u.burst;
                }
                else {
                response[u.idx]=min(response[u.idx],current);
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


     }
            float totalWaiting=0,totalTurnaround=0;
      f(i,n){
           turnaround[i]=finish[i]-arrival[i];
           waiting[i]=turnaround[i]-burst[i];
           totalTurnaround+=turnaround[i];
           totalWaiting+=waiting[i];
      }
      float avgWaiting=totalWaiting/n,avgTurnaround=totalTurnaround/n;
    cout<<"Algorithm 3: Average Waiting Time: "<<avgWaiting<<"\t   Average Turnaroundtime: "<<avgTurnaround<<endl;
}
void proposed1(){
     f(i,500) response[i]=500;
     vector<process>vct;
     for(i=0;i<n;i++)
       vct.pb({arrival[i],burst[i],i});
      
      sort(vct.begin(),vct.end(),fcfs);
    deque<process>Q;
    ll current=vct[0].arrival;
    ll taken=-1;
    ll flag=0;
    ll sz=vct.size();
    ll idle=0;
  while(taken<n-1){
        taken++;
        Q.push_front(vct[taken]);
        ll t=vct[taken].arrival;
        if(flag==0&&t){
          idle+=t;
        }
        else if(t)
            {
            idle+=t-current;
            }
            current=t;

    while(!Q.empty()){
      process top=Q.front();
      tq=timeQuantum(Q);
      if(top.burst<=tq){
            if(flag==0){
          response[top.idx]=min(response[top.idx],current);
        flag=1;
            }
            else {
              response[top.idx]=min(response[top.idx],current);
            }
           finish[top.idx]=current+top.burst;
          Q.pop_front();
          current+=top.burst;
            for(i=taken+1;i<sz;i++){
            if(vct[i].arrival<=current){
                    taken++;
                    Q.pb(vct[i]);

                }
    }
  }
      else{
        if(flag==0){
            response[top.idx]=min(response[top.idx],current);
            flag=1;
        }
        else {
        response[top.idx]=min(response[top.idx],current);
        }
        current+=tq;
        top.burst-=tq;
        Q.pop_front();
               for(i=taken+1;i<sz;i++){
        if(vct[i].arrival<=current){
                    taken++;
                    Q.pb(vct[i]);

                }

          }
          Q.pb(top);
   }
    }
  }
     float totalWaiting=0,totalTurnaround=0;
         for(i=0;i<n;i++){
            turnaround[i]=finish[i]-arrival[i];
            waiting[i]=turnaround[i]-burst[i];
            totalTurnaround+=turnaround[i];
            totalWaiting+=waiting[i];

         }
    float avgWaiting=totalWaiting/n,avgTurnaround=totalTurnaround/n;
    cout<<"Algorithm 7: Average Waiting Time: "<<avgWaiting<<"\t   Average Turnaroundtime: "<<avgTurnaround<<endl;

}
     