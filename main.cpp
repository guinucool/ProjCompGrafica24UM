#include <iostream>
#include <string>

using namespace std;

int main(int argc, char ** argv) {

    for (int i = 0; i < argc; i++)
    {
        string arg(argv[i]);

        cout << arg << endl;
    }
    
    return 0;
}