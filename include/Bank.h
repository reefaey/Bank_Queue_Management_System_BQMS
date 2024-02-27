#ifndef BANK_H
#define BANK_H

#include "CustomerQueue.h"
#include "Teller.h"
#include "Customer.h"
#include <windows.h>
#include <queue>
#include <fstream>

#include <iostream>
using namespace std;


enum Served {Yes, No};

class Bank
{
    public:

        Bank()
        {
            for(int i = 0; i < 3; i++)
            {
                TellerWindows[i] = new Teller(i + 1);
            }
        }

        //To Add customers
        void EnteringCustomer(string name, int AR, int ST)
        {
            Customer *newCust = new Customer(name, AR , ST);
            customerQueue.push(newCust);
        }

        void Simulate()
        {
            Customer *CurrentCustomer = customerQueue.Front();
            Teller *PotentialTeller; //the Lowest Last Served time
            int i = 0;
            while(CurrentCustomer != NULL)
            {
                //cout << CurrentCustomer->GetArrivalTime() <<endl;  for Test
                i = 0;
                PotentialTeller = TellerWindows[0];
                Target = No;

                while(i < 3 && Target == No)
                {
                    if(TellerWindows[i]->GetLST() <= CurrentCustomer->GetArrivalTime())
                    {
                        PotentialTeller = TellerWindows[i];
                        CurrentCustomer->SetWaitingTime(0);
                        CurrentCustomer->SetTellerNo(PotentialTeller->GetTellerNumber());
                        Target = Yes;
                    }
                    else
                    {
                        int potentialteller = PotentialTeller->GetLST();
                        int tellerWindow = TellerWindows[i]->GetLST();

                        if(PotentialTeller->GetLST() > TellerWindows[i]->GetLST())
                        {
                            PotentialTeller = TellerWindows[i];

                        }

                        CurrentCustomer->SetWaitingTime( (PotentialTeller->GetLST()) - (CurrentCustomer->GetArrivalTime()) );
                        CurrentCustomer->SetTellerNo(PotentialTeller->GetTellerNumber());
                    }
                    int arrivaltime = CurrentCustomer->GetArrivalTime();
                    int ServiceTime = CurrentCustomer->GetServiceTime();
                    i++;

                }

                AssignCustomer(PotentialTeller, CurrentCustomer);
                //for test
                //int CurrentCustomerr = CurrentCustomer->BackCustomer->GetArrivalTime();
                CurrentCustomer = CurrentCustomer->BackCustomer;

            }
        }


        void Display()
        {
            ofstream Report("files/Report.txt");

            Simulate();

            float TotalWaitingTime = 0;
            float TotalServiceTime = 0;

            system("Color 17");
            cout << "\t\t\t\t       Bank Queue Management System (BQMS)" <<endl;
            cout << "\t\t\t\t     |<===================================>|\n" <<endl;
            cout << "\t+-----------+------------+----------------+----------------+----------------+---------------+" << endl;
            cout << "\t| Teller No |   Client   |  Arrival Time  |  Waiting Time  |  Service Time  | Leaving Time  |" << endl;
            cout << "\t+-----------+------------+----------------+----------------+----------------+---------------+" << endl;

            Report  << "\t\t\t\t       Bank Queue Management System (BQMS)" <<endl;
            Report  << "\t\t\t\t     |<===================================>|\n" <<endl;
            Report  << "\t+-----------+------------+----------------+----------------+----------------+---------------+" << endl;
            Report  << "\t| Teller No |   Client   |  Arrival Time  |  Waiting Time  |  Service Time  | Leaving Time  |" << endl;
            Report  << "\t+-----------+------------+----------------+----------------+----------------+---------------+" << endl;

            while(!customerQueue.Isempty())
            {

                Customer *CurrentCustomer = customerQueue.Front();

                cout << "\t|     " <<CurrentCustomer->GetTellerNumber() << "      \t ";
                cout << CurrentCustomer->Name << "      \t ";
                cout << CurrentCustomer->GetArrivalTime() << "           \t ";
                cout <<  " " << CurrentCustomer->GetWaitingTime() << "         \t ";
                cout << "  " << CurrentCustomer->GetServiceTime() << "          \t ";
                cout << "  " <<CurrentCustomer->GetLeavingTime() << "\t    |" << endl;
                cout << "\t+-----------+------------+----------------+----------------+----------------+---------------+" << endl;

                Report << "\t|     " <<CurrentCustomer->GetTellerNumber() << "      \t ";
                Report << CurrentCustomer->Name << "      \t ";
                Report << CurrentCustomer->GetArrivalTime() << "           \t ";
                Report <<  " " << CurrentCustomer->GetWaitingTime() << "         \t ";
                Report << "  " << CurrentCustomer->GetServiceTime() << "          \t ";
                Report << "  " <<CurrentCustomer->GetLeavingTime() << "\t    |" << endl;
                Report << "\t+-----------+------------+----------------+----------------+----------------+---------------+" << endl;

                TotalWaitingTime += CurrentCustomer->GetWaitingTime();
                TotalServiceTime += CurrentCustomer->GetServiceTime();

                //cout << CurrentCustomer->GetClient() << " \t "<< endl;

                customerQueue.Pop();
            }

            int TotalCustomer = customerQueue.GetTotalCustomer();

            cout << "\n\t\t\t\t\t       <<Some Statistics>>" << endl;
            cout << "\t\t\t\t\t       ===================\n" <<endl;
            cout << "\n\t Total Served Customer: " << TotalCustomer << endl;
            cout << "\t Average Waiting Time: " << TotalWaitingTime/TotalCustomer << " minutes" << endl;
            cout << "\t Average Service Time: " << TotalServiceTime/TotalCustomer << " minutes" << endl;
            cout << "\t Total Served Customer By Teller #1 equal " << TellerWindows[0]->GetTotalServedCustomer() << " Customer" <<endl;
            cout << "\t Total Served Customer By Teller #2 equal " << TellerWindows[1]->GetTotalServedCustomer() << " Customer" <<endl;
            cout << "\t Total Served Customer By Teller #3 equal " << TellerWindows[2]->GetTotalServedCustomer() << " Customer" <<endl;

            Report << "\n\t\t\t\t\t       <<Some Statistics>>" << endl;
            Report << "\t\t\t\t\t       ===================\n" <<endl;
            Report << "\n\t Total Served Customer: " << TotalCustomer << endl;
            Report << "\t Average Waiting Time: " << TotalWaitingTime/TotalCustomer << " minutes" << endl;
            Report << "\t Average Service Time: " << TotalServiceTime/TotalCustomer << " minutes" << endl;
            Report << "\t Total Served Customer By Teller #1 equal " << TellerWindows[0]->GetTotalServedCustomer() << " Customer" <<endl;
            Report << "\t Total Served Customer By Teller #2 equal " << TellerWindows[1]->GetTotalServedCustomer() << " Customer" <<endl;
            Report << "\t Total Served Customer By Teller #3 equal " << TellerWindows[2]->GetTotalServedCustomer() << " Customer" <<endl;

            if(!Report.is_open())
            {
                cerr << "Error: Could not open the output file.\n";
            }

        }


        void AssignCustomer(Teller *t, Customer *c)
        {
            t->IncreaseTSC();
            c->SetLeavingTime();
            //for test
            int arrivaltime = c->GetArrivalTime();
            int Waitingtime = c->GetWaitingTime();
            int ServiceTime = c->GetServiceTime();
            int LeavingTime = c->GetLeavingTime();
            t->SetLST(c);
            //for test
            int lst = t->GetLST();

        }


    private:
        //list<Teller> TellerWindows;
        Teller *TellerWindows[3];
        CustomerQueue customerQueue;
        queue<Customer> Queue;
        Served Target;
};

#endif // BANK_H
