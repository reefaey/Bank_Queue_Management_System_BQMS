#ifndef TELLER_H
#define TELLER_H
#include "Customer.h"
//Enum ??

enum Avaliablility {Busy, Idle};

class Teller
{
    int TellerNumber;
    Avaliablility status;
    int TotalServedCustomer;
    int LastServedTime;
    Customer *ServingCustomer;

    public:

        Teller(int TellerNum)
        {
            TellerNumber = TellerNum;
            status = Idle;
            ServingCustomer = NULL;
            TotalServedCustomer = LastServedTime = 0;
        }

        void IncreaseTSC()
        {
            TotalServedCustomer++;
        }

        void SetLST(Customer *c)
        {
            LastServedTime = c->GetLeavingTime();
        }

        int GetLST()
        {
            return LastServedTime;
        }

        int GetTellerNumber()
        {
            return TellerNumber;
        }

        int GetTotalServedCustomer()
        {
            return TotalServedCustomer;
        }

        int GetAvailability()
        {
            return status;
        }

};

#endif // TELLER_H
