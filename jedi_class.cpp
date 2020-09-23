#include <string>
#include <iostream>

using namespace std;

class Jedi
{
    public:
        string name;
    
    Jedi(string n)
    {
        name = n;
    }

    void say_hi()
    {
        cout << "Hello, my name is " << name << "\n";
    }
};

int main(int argc, char** argv)
{ 
    Jedi j("ObiWan");
    j.say_hi();
    return 0;
}