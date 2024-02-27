#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <iostream>
using namespace std;

enum Type {Normal , VIP};

class Customer
{
    int ArrivalTime;
    int WaitingTime;
    int ServiceTime;
    int LeavingTime;
    int TellerNo;
    //Type Client;

    public:
        string Name;
        Customer *FrontCustomer;
        Customer *BackCustomer;

        Customer(string name, int AR, int ST)
        {
            Name = name;
            ArrivalTime = AR;
            ServiceTime = ST;
            FrontCustomer = BackCustomer = NULL;
        }

        void SetWaitingTime(int time)
        {
            WaitingTime = time;
        }

        void SetLeavingTime()
        {
            LeavingTime = ArrivalTime + WaitingTime + ServiceTime ;
        }

        void SetTellerNo(int n)
        {
            TellerNo = n;
        }

        /*Type GetClient()
        {
            return Client;
        }*/

        int GetTellerNumber()
        {
            return TellerNo;
        }

        string GetName()
        {
            return Name;
        }

        int GetWaitingTime()
        {
            return WaitingTime;
        }

        int GetServiceTime()
        {
            return ServiceTime;
        }

        int GetLeavingTime()
        {
            SetLeavingTime();
            return LeavingTime;
        }

        int GetArrivalTime()
        {
            return ArrivalTime;
        }


};

#endif // CUSTOMER_H
