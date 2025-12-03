#include <iostream>
using namespace std;

int main(){
    int n;
    cin>>n;
    for(int mask=0;mask<(1<<n);mask++){
        for(int submask=mask;submask>=0;--submask){
            submask&=mask;
        }
    }
}
