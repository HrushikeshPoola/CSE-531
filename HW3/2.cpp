/*
    Mailbox madness

*/

#include <vector>
#include <iostream>
#include <map>
using namespace std;
int solve(map<int, vector< vector<int> > > &mailboxToCrackersMap,int k,int start, int end) {
    if(k == 0) return 1e9;
    if(k == 1) return ((end)*(end+1)/2 - (start)*(start + 1)/2);
    if(start == end) return 0;

    if(mailboxToCrackersMap[k][start][end] == -1) {
        int min_crackers = 1e9;
        for(int i = start + 1; i <= end; i++) {
            /*
                if i crackers are used when there are k mailboxes to test
                    - can blast for i crackers -> threshold is on start and i with (k-1) mailboxes
                    - not blast for i crackers -> threshold is on i and end with k mailboxes
            */
            int count_if_blast = solve(mailboxToCrackersMap,k-1,start,i-1);
            int count_if_no_blast = solve(mailboxToCrackersMap,k,i,end);
            
            int crackers_i = i + max(count_if_blast, count_if_no_blast);
            min_crackers = min(min_crackers,crackers_i);
        }
        mailboxToCrackersMap[k][start][end] = min_crackers;
    }

    return mailboxToCrackersMap[k][start][end];
}
int main() {

    map<int, vector< vector<int> > > mailboxToCrackersMap;
    int test_cases;
    cin>>test_cases;

    while(test_cases--) {
        // solve minimum crackers required for each test case
        // each line of test case input is k and m
        int k,m;
        cin>>k>>m;
        for(int i=1;i<=k;i++) {
            vector< vector<int> > crackersMemo(101,vector<int>(101,-1));
            mailboxToCrackersMap[i] = crackersMemo;
        }

        cout<<solve(mailboxToCrackersMap,k,0,m)<<endl;
        mailboxToCrackersMap.clear();

    }
    return 0;
}