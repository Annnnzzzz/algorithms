#include <iostream>
#include <vector>
#include<fstream>
 
using namespace std;

//Подсчет сочетаний с помощью динамического программирования 
vector<vector<long long>> c;
void C(){
    c[1][0]=1;
    c[1][1]=1;
    for (int i=2; i<c.size(); ++i){
        for (int j=0; j<c[i].size(); ++j){
            if (j==0){
                c[i][j]=c[i-1][j];
            }
            else{
                c[i][j] = c[i - 1][j] + c[i - 1][j - 1];
            }
        }
    }
}