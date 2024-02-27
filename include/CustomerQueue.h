#ifndef CUSTOMERQUEUE_H
#define CUSTOMERQUEUE_H

#include "Customer.h"

class CustomerQueue
{
    Customer *head, *tail;
    int size;
    public:
        CustomerQueue()
        {
            head = tail = NULL;
            size = 0;
        }

        bool Isempty()
        {
            if(head == NULL)
            {
                return true;
            }
            else
            {
                return false;
            }
        }


        Customer* Front()
        {
            return head;
        }

        int GetTotalCustomer()
        {
            return size;
        }

        void push(Customer *c)
        {
            Customer *cust = new Customer(c->Name, c->GetArrivalTime(), c->GetServiceTime());
            /*

            //only for test

            string testt = cust->Name;
            int AR = cust->GetArrivalTime();
            int ST = cust->GetServiceTime();

            */


            if(head == NULL)
            {
                head = tail = cust;
                //AR = head->GetArrivalTime();
                //ST = head->GetServiceTime();
            }
            else
            {
                if(cust->GetArrivalTime() < tail->GetArrivalTime())
                {

                    if(head == tail)
                    {
                        tail->FrontCustomer = cust;
                        cust->BackCustomer = tail;
                        head = cust;
                        //tail = cust->BackCustomer;

                        /* //only for test
                        AR = head->GetArrivalTime();
                        ST = head->GetServiceTime();
                        AR = tail->GetArrivalTime();
                        ST = tail->GetServiceTime();

                        */
                    }
                    else
                    {
                        Customer *current = tail;

                        while(cust->GetArrivalTime() < current->GetArrivalTime())
                        {
                            if(current != head)
                            {
                                if(current!=tail)
                                {
                                    //Customer *temp = cust->BackCustomer;
                                    current->BackCustomer = cust->BackCustomer;
                                    cust->BackCustomer->FrontCustomer = current;
                                }
                                    cust->FrontCustomer = current->FrontCustomer;
                                    current->FrontCustomer->BackCustomer = cust;
                                    cust->BackCustomer = current;
                                    current->FrontCustomer = cust;
                            }
                            else
                            {
                                Customer *temp = current;
                                cust->BackCustomer = temp;

                                head = cust;
                                current->FrontCustomer = head;

                            }
                            /*
                               only for test
                            int AR_Front = cust->FrontCustomer->GetArrivalTime();
                            int ST_Front= cust->FrontCustomer->GetServiceTime();
                            int AR_Back = cust->BackCustomer->GetArrivalTime();
                            int ST_Back = cust->BackCustomer->GetServiceTime();
                            */


                            current = cust->FrontCustomer;


                        }
                    }
                }
                else
                {
                    cust->FrontCustomer = tail;
                    tail->BackCustomer = cust;
                    tail = cust;
                    tail->BackCustomer = NULL;

                        //AR = cust->FrontCustomer->GetArrivalTime();
                        //ST = cust->FrontCustomer->GetServiceTime();
                        //AR = tail->GetArrivalTime();
                        //ST = tail->GetServiceTime();

                       //only for test
                       // int AR_Front = cust->FrontCustomer->GetArrivalTime();
                       // int ST_Front= cust->FrontCustomer->GetServiceTime();
                       // int AR_Back = cust->BackCustomer->GetArrivalTime();
                       // int ST_Back = cust->BackCustomer->GetServiceTime();
                }
            }
            size++;
        }

        void Pop()
        {
            if(head->BackCustomer == NULL)
            {
                delete head;
                head = NULL;
                return;
            }
            else
            {
                Customer *NewFront = head->BackCustomer;
                delete head;
                head = NewFront;
                return;
            }
        }
};

#endif // CUSTOMERQUEUE_H

