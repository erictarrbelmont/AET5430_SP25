//
//  main.cpp
//  HelloWorld
//
//  Created by Eric Tarr on 1/9/25.
//


#include <iostream>
#include <vector>

using namespace std;

int main(int argc, const char * argv[]) {
    
    int x; // declare the variable
    x = 5; // define its value
    x = 7;
    
    int y = 6; // declare and define in same step
    
    // 32-bit floating point number (used for fractional values)
    float z = 10.0f; // 10.f
    
    // 64-bit floating point number
    double w = 10.0;
    
    auto q = 10.f;
    
    char c = 'c'; // single piece of text data
    string myString = "Whatever";
    
    // Primitive arrays
    int i[4]; // array with 4 elements
    i[0] = 100;
    i[1] = 200;
    i[2] = 300;
    i[3] = 400;
    
    float r[3] = {0.f};
    float s[3] = {4.f,5.f,6.f};
    
    // C++ "for" loop
    // for n = 1:4
    //
    // end
    for (int n = 0; n < 4 ; ++n){
        i[n] = n * 2;
    }
    
    // incrementing in C++
    int n = 1;
    int m = 5 + (n++); // use "n" in expression before incrementing it
    
    n = 1;
    m = 5 + (++n);           // increment and then use "n" in expression
    
    float g[2][3][3][6];
    g[1][2][1][1] = 8.4f;
    
    
    vector<float> k;
    k.push_back(2.f); // vector can change size
    k.push_back(3.f);
    int sz = k.size();
    k.push_back(4.f);
    sz = k.size();
    float val = k[4]; // k.at(4); // k[1]
    
    // insert code here...
    cout << "Hello, World!" << endl;
    cout << "AET 4220\n";
    cout << i[2] << endl;
    cout << i[4] << endl;
    return 0;
}
