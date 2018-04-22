#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    //cout << "Hello world!" << endl;
    int t;
    cin >>t;
    int n[t];
    cout << "Insert values in array: " << endl;
    for(int i=0; i<t; i++){
        cin >> n[i];
    }
    sort(n, n+t);
    for(int i=0; i<t; i++){
        cout << n[i] << endl;
    }
    return 0;
}
