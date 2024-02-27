#include <iostream>

#include <fstream>

#include "Bank.h"
using namespace std;

//void ReadClientData(const string& filename, Bank *bank)
void ReadClientData(ifstream& data, Bank *bank)
{
    if (data.is_open())
    {
        string name;
        int AR , ST;

        while(data >> name >> AR >> ST)
        {
            bank->EnteringCustomer(name, AR, ST);
        }
    }
    else
    {
        cerr << "Error: Could not open the file.\n";
    }
}

int main()
{
    Bank cib;

    ifstream data("files/Data.txt");
    ReadClientData(data, &cib);


    /*cib.EnteringCustomer("Ahmed", 1, 30);
    cib.EnteringCustomer("Mohamed", 10, 20);
    cib.EnteringCustomer("Ali", 1, 14);
    cib.EnteringCustomer("Eslam", 4, 4);
    cib.EnteringCustomer("Hassan", 3, 32);
    cib.EnteringCustomer("Selim", 7, 9);
    cib.EnteringCustomer("Nour", 6, 19);
    cib.EnteringCustomer("Hany", 4, 17);
    cib.EnteringCustomer("Rady", 12, 28);
    cib.EnteringCustomer("Samy", 8, 14);
    */

    cib.Display();



    return 0;
}
