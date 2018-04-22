#include <iostream>

using namespace std;

int main(void){
  int testcases;
  int cupcakes;
  cin >> testcases;
  while(testcases--){
    cin >> cupcakes;
    cout << cupcakes/2+1 << "\n";
  }
  return 0;
}
