#pragma once
#include <iostream>
#include <string>
#include <fstream>
using namespace std;


class processnode
{
public:
    int p_arrival_time;
    int p_remaining_time;
    int p_brust_time;
    int p_finist_time;
    string p_work_type;
    string p_work;
    string p_status;
    processnode* p_next;

    processnode()
    {
        p_arrival_time = 0;
        p_remaining_time = 0;
        p_brust_time = 0;
        p_finist_time = 0;
        p_work_type = "NULL";
        p_work = "NULL";
        p_status = "ASSIGN";
        p_next = NULL;
    }
    processnode(int at, int rt, int bt, string wt, string w)
    {
        p_arrival_time = at;
        p_remaining_time = rt;
        p_brust_time = bt;
        p_finist_time = 0;
        p_work_type = wt;
        p_work = w;
        p_status = "ASSIGN";
        p_next = NULL;
    }
};

//=============================//

class readyquenode
{
public:
    int r_arrival_time;
    int r_remaining_time;
    int r_brust_time;
    int r_finist_time;
    string r_work_type;
    string r_work;
    string r_status;
    readyquenode* r_next;

    readyquenode()
    {
        r_arrival_time = 0;
        r_remaining_time = 0;
        r_brust_time = 0;
        r_finist_time = 0;
        r_work_type = "NULL";
        r_work = "NULL";
        r_status = "WAITING IN READY QUEU";
        r_next = NULL;
    }
    readyquenode(int at, int rt, int bt, string wt, string w)
    {
        r_arrival_time = at;
        r_remaining_time = rt;
        r_brust_time = bt;
        r_finist_time = 0;
        r_work_type = wt;
        r_work = w;
        r_status = "WAITING IN READY QUEU";
        r_next = NULL;
    }

};
class fcfs_execution_node
{
public:
    int fe_arrival_time;
    int fe_remaining_time;
    int fe_brust_time;
    int fe_finist_time;
    string fe_work_type;
    string fe_work;
    string fe_status;
    fcfs_execution_node* fe_next;

    fcfs_execution_node()
    {
        fe_arrival_time = 0;
        fe_remaining_time = 0;
        fe_brust_time = 0;
        fe_finist_time = 0;
        fe_work_type = "NULL";
        fe_work = "NULL";
        fe_status = "EXECUTION STATE";
        fe_next = NULL;
    }
    fcfs_execution_node(int at, int rt, int bt, string wt, string w)
    {
        fe_arrival_time = at;
        fe_remaining_time = rt;
        fe_brust_time = bt;
        fe_finist_time = 0;
        fe_work_type = wt;
        fe_work = w;
        fe_status = "EXECUTION STATE";
        fe_next = NULL;
    }

};
//=============================//


class linked
{
public:
    processnode* p_head;//pointer on head node//
    readyquenode* r_head;//ready quee head//
    readyquenode* r_last;//ready quee last//
    fcfs_execution_node* fe_head;//fcfs quee head//

    linked()
    {
        p_head  = NULL;
        r_head  = NULL;
        r_last  = NULL;
        fe_head = NULL;
    }
    //------------------------------------------//
    void linked_add_process_node(int at, int rt, int bt, string wt, string w)
    {
        processnode* n = new processnode(at, rt, bt, wt, w);

        if (p_head == NULL)
        {
            p_head = n;
            return;
        }
        else
        {
            processnode* temp = p_head;

            while (temp->p_next != NULL)
            {
                temp = temp->p_next;
            }
            temp = temp->p_next = n;
        }
    }

    void ready_quee_add_node(int t)
    {
        processnode* temp = p_head;

        while (temp != NULL)
        {
            if (temp->p_arrival_time == t)
            {
                int at = temp->p_arrival_time;
                int rt = temp->p_remaining_time;
                int bt = temp->p_brust_time;

                string wt = temp->p_work_type;
                string w = temp->p_work;

                readyquenode* n = new readyquenode(at, rt, bt, wt, w);

                if (r_head == NULL)
                {
                    r_head = n;
                    r_last = n;
                }
                else
                {
                    readyquenode* temp = r_head;

                    while (temp->r_next != NULL)
                    {
                        temp = temp->r_next;
                    }
                    temp->r_next = n;
                    r_last = n;
                }
            }
            else
            {

            }

            temp = temp->p_next;
        }
    }
    void fcfs_execution()
    {
        readyquenode* r_temp = r_head;//ready quee ka first element//
        //ready quee ka head update krna ha 
       
        if (r_temp->r_remaining_time >= 1)
        {
            cout << "****" << r_temp->r_remaining_time << "***\n";
            r_temp->r_remaining_time = r_temp->r_remaining_time - 1;
            int at = r_temp->r_arrival_time;
            int rt = r_temp->r_remaining_time;
            int bt = r_temp->r_brust_time;
            string wt = r_temp->r_work_type;
            string w = r_temp->r_work;

            fcfs_execution_node* n = new fcfs_execution_node(at, rt, bt, wt, w); // new node of fcfs execution//
            if (fe_head == NULL)
            {
                fe_head = n;
            }
            else
            {
                fcfs_execution_node* fe_temp = fe_head;

                while (fe_temp->fe_next != NULL)
                {
                    fe_temp = fe_temp->fe_next;
                }
                fe_temp->fe_next = n;
            }

        }
        else
        {
           
            r_head = r_temp->r_next;
            delete r_temp;
            readyquenode* r_temp = r_head;
            cout << "****" << r_temp->r_remaining_time << "***\n";
            r_temp->r_remaining_time = r_temp->r_remaining_time - 1;
    
            int at = r_temp->r_arrival_time;
            int rt = r_temp->r_remaining_time;
            int bt = r_temp->r_brust_time;
            string wt = r_temp->r_work_type;
            string w = r_temp->r_work;

            fcfs_execution_node* n = new fcfs_execution_node(at, rt, bt, wt, w); // new node of fcfs execution//
            if (fe_head == NULL)
            {
                fe_head = n;
            }
            else
            {
                fcfs_execution_node* fe_temp = fe_head;

                while (fe_temp->fe_next != NULL)
                {
                    fe_temp = fe_temp->fe_next;
                }
                fe_temp->fe_next = n;
            }

        }
    }
       //---------------------------------------------------------------------------------//
    void show_process_node()
    {
        processnode* temp = p_head;
        while (temp != NULL)
        {
            cout << "\n------------------------------------\n";
            cout << "ARRIVIAL TIME  = " << temp->p_arrival_time << endl;
            cout << "REMAINING TIME = " << temp->p_remaining_time << endl;
            cout << "BRUST TIME     = " << temp->p_brust_time << endl;
            cout << "WORK TYPE      = " << temp->p_work_type << endl;
            cout << "WORK           = " << temp->p_work << endl;
            cout << "STATUS         = " << temp->p_status << endl;

            cout << "\n-------------------------------------\n";
            temp = temp->p_next;
        }
    }
    void show_ready_quee_node()
    {
        readyquenode* temp = r_head;
        while (temp != NULL)
        {
            cout << "\n------------------------------------\n";
            cout << "ARRIVIAL TIME  = " << temp->r_arrival_time << endl;
            cout << "REMAINING TIME = " << temp->r_remaining_time << endl;
            cout << "BRUST TIME     = " << temp->r_brust_time << endl;
            cout << "WORK TYPE      = " << temp->r_work_type << endl;
            cout << "WORK           = " << temp->r_work << endl;
            cout << "STATUS         = " << temp->r_status << endl;
            cout << "\n-------------------------------------\n";
            temp = temp->r_next;
        }
    }
    void show_fcfs_execution_node() {}

    //----------------------------------------------------//
    void show_process_node_flow()
    {
        processnode* temp = p_head;

        while (temp != NULL)
        {
            cout << temp->p_work << " ---> ";
            temp = temp->p_next;
        }
    }
    void show_ready_quee_node_flow()
    {
        readyquenode* temp = r_head;

        while (temp != NULL)
        {
            cout << temp->r_work << " ---> ";
            temp = temp->r_next;
        }
    }
    void show_fcfs_execution_node_flow() 
    {
       fcfs_execution_node * temp = fe_head;

        while (temp != NULL)
        {
            cout << temp->fe_work << " --> ";
            temp = temp->fe_next;
        }
    }

};
