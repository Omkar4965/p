#include <bits/stdc++.h>
using namespace std;

int fifo(int pages[], int n , int capacity){
    unordered_set <int> s;
    queue <int> q;

    int miss = 0;
    for (int i = 0; i < n; i++)
    {
        if(s.size() < capacity)
        {
            if(s.find(pages[i]) == s.end())
            {
                s.insert(pages[i]);
                miss++;
                q.push(pages[i]);
            }
        }
        else{ 
            int val = q.front();
            q.pop();
            s.erase(val);
            s.insert(pages[i]);
            q.push(pages[i]);
            miss++;
        }
    }

    return miss;
}


int LRU(int pages[], int n, int capacity){
    unordered_set <int> s;
    unordered_map <int,int> m;

    int miss =0;

    for(int i=0;i<n;i++){

        if(s.size()<capacity){

            if(s.find(pages[i]) == s.end()){
                s.insert(pages[i]);
                miss++;        
            }
            m[pages[i]]++;
        }
        else{
            if(s.find(pages[i]) == s.end())
            {
                int lru = INT_MAX, val;
                for(auto it = s.begin(); it!=s.end(); it++){
                    if(m[*it] < lru){
                        lru = m[*it];
                        val = *it;
                    }
                }
                s.erase(val);
                s.insert(pages[i]);
                miss++;
            }
            m[pages[i]]++;
        }
    }

    return miss;
}

bool search(int key, vector<int>& fr){
    for(int i=0;i<fr.size();i++)
    {
        if(fr[i] == key)
        return true;
    }
    return false;
}

int predict(int pages[], vector<int>&fr, int pn, int index){
    int res =-1, farthest = index;
    for(int i=0;i<fr.size();i++){
        int j;
        for(j=index;j<pn;j++){
            if(fr[i] == pages[j]){
                if(j> farthest){
                    farthest = j;
                    res = i;
                }
                break;
            }   
        }
        if(j == pn){
        return i;
        }
    }

    return (res == -1) ? 0 :res;
    
}

void optimalPage(int pages[], int pn, int fn){
    vector <int> fr;
    int hit=0;
    for(int i=0;i<pn;i++){
        if(search(pages[i],fr)){
            hit++;
            continue;
        }

        if(fr.size()<fn){
            fr.push_back(pages[i]);
        }
        else{
            int j = predict(pages,fr,pn,i+1);
            fr[j] = pages[i];
        }
    }
    cout<<"Hits "<<hit<<endl;
    cout<<"miss "<<pn-hit<<endl;

}

int main(){
    int pages[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};
    int n = sizeof(pages)/sizeof(pages[0]);
    optimalPage(pages, n, 4);
    return 0;
}