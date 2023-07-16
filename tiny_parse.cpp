#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include "tinyxml2.h"
#include<fstream>
#include"Cpu_sheduling.h"
using namespace std;
using namespace tinyxml2;

int main(void)
{
    string code;

    // XML FILE READING START HERE//
    fstream mytxtfile;
    mytxtfile.open("Processes data.txt", ios::out);//write mode
    cout << "\n==============================READING XML FILE================================\n";
    XMLDocument file;
    file.LoadFile("shedulingfile.xml");
    XMLElement* AssignmentInput = file.FirstChildElement("AssignmentInput");
    XMLElement* Queues = AssignmentInput->FirstChildElement("QueueSet");
    XMLElement* SetName = Queues->FirstChildElement("SetName");
    cout << "Set Name = \t\t " << SetName->GetText() << endl;
    SetName = SetName->NextSiblingElement("UpgradePolicy");
    cout << "UpgradePolicy = \t " << SetName->GetText() << endl;
    SetName = SetName->NextSiblingElement("DowngradePolicy");
    cout << "DowngradePolicy = \t " << SetName->GetText() << endl;
    SetName = SetName->NextSiblingElement("QAllocPolicy");
    cout << "QAllocPolicy = \t\t " << SetName->GetText() << endl;
    SetName = SetName->NextSiblingElement("Queue");
    cout << endl;
    cout << "Queue ID = " << SetName->Attribute("id") << endl;
    XMLElement* firstSchedulingPolicy = SetName->FirstChildElement("SchedulingPolicy");
    cout << "SchedulingPolicy = " << firstSchedulingPolicy->GetText() << endl;

    SetName = SetName->NextSiblingElement("Queue");
    cout << "Queue ID = " << SetName->Attribute("id") << endl;
    XMLElement* secondSchedulingPolicy = SetName->FirstChildElement("SchedulingPolicy");
    cout << "SchedulingPolicy = " << secondSchedulingPolicy->GetText() << endl;
    cout << endl;

    //First Child Element of Queue Set end Here

    Queues = Queues->NextSiblingElement("Configuration");
    XMLElement* processes = Queues->FirstChildElement("Processes");
    cout << "Process Number = " << processes->Attribute("number") << endl << endl;

    XMLElement* process = processes->FirstChildElement("Process");
    cout << "Process ID = " << process->Attribute("ID") << endl;

    XMLElement* Time_Arrival = process->FirstChildElement("ArrivalTime");
    cout << "Arrival Time = " << Time_Arrival->GetText() << endl;
    
    if (mytxtfile.is_open())
    {
        code = Time_Arrival->GetText();
        mytxtfile << code << endl;
    }
    Time_Arrival = Time_Arrival->NextSiblingElement("Type");
    cout << "TYPE = " << Time_Arrival->GetText() << endl;
    if (mytxtfile.is_open())
    {
        code = Time_Arrival->GetText();
        mytxtfile << code;
    }
    Time_Arrival = Time_Arrival->NextSiblingElement("code");
    cout << Time_Arrival->GetText() << endl;
    
    if (mytxtfile.is_open())
    {
        code = Time_Arrival->GetText();
        mytxtfile << code;
     //   mytxtfile << "#\n";
       
    }
    cout << endl << endl;

    //First Child Element of Process 1 end here

    process = process->NextSiblingElement("Process");
    cout << "Process ID = "<<process->Attribute("ID")<<endl;
    XMLElement* FirstArrivalTime = process->FirstChildElement("ArrivalTime");
   cout << "Arrival Time = "<<FirstArrivalTime->GetText()<<endl;
   
   if (mytxtfile.is_open())
   {
        code = FirstArrivalTime->GetText();
        mytxtfile << code << endl;
   }

    FirstArrivalTime = FirstArrivalTime->NextSiblingElement("Type");
    cout << "TYPE = " << FirstArrivalTime->GetText()<<endl;
   if (mytxtfile.is_open())
   {
        code = FirstArrivalTime->GetText();
        mytxtfile<<code;
   }
    FirstArrivalTime = FirstArrivalTime->NextSiblingElement("code");
    cout<<FirstArrivalTime->GetText()<< endl;
   
    if (mytxtfile.is_open())
    {
        code = FirstArrivalTime->GetText();
        mytxtfile<<code;
   //     mytxtfile << "#";
        mytxtfile.close();
    }
    
    // XML FILE READING END HERE//
    //cout << "\n===============================================================\n"<< endl;
    //cout << "\n===============================================================\n"<< endl;
    cout << "\n===============================================================\n"<< endl;
    cout << "\n====================COLLECTING DATA FOR NODES==================\n"<< endl << endl;
    linked l;//link list object//
    string line="NULL";//string line//
    string w="NULL";//store work//
    string wt="NULL";//store work type//
    int at=0;//arrival time//
    int ct=0;//current time//
    int bt=0;//brust time//
    int rt=0;//remaining time//

    mytxtfile.open("Processes data.txt", ios::in);//read mode
   
    if (mytxtfile.is_open())
    {
        while (getline(mytxtfile, line))
        {
            //cout << line << endl;
            if (line>="0" && line<="9")//check number or not //
            {
          //  cout << "\nnumber chala\n";
            at=stoi(line);
            ct=at;
            }
            else if (line=="IO_Bound" || line=="CPU_Bound")//check process type //
            {
            //cout << "\nwork type chala\n";
            wt=line;
            }
            else if (line=="READKEYBOARD" || line == "READKEYBOARD " || line=="WRITEPRINTER" || line == "WRITEPRINTER " || line == "WRITESCREEN" || line == "WRITESCREEN ")// allocate brust time =3 and remaining time=3 and work//
            {
            //cout << "\nblocking chala\n";
            bt=3;
            rt=3;
            w=line;
        
            l.linked_add_process_node(at, rt, bt, wt, w);
            }
            else if (line == "COMPUTE" || line == "COMPUTE " || line == "READMEMORY" || line == "READMEMORY " || line == "WRITEMEMORY" || line == "WRITEMEMORY ")
            {
                //cout << "\nnon blocking chala\n";
                bt = 1;
                rt = 1;
                w = line;

                l.linked_add_process_node(at, rt, bt, wt, w);
            }
        }
        mytxtfile.close();
    }

    else
    {
        cout << "\nfile doesnot opened\n";
    }
    cout << "\n-------------------------------------------------------------------------------\n";
    l.show_process_node();
    cout << "\n############################\n";
    l.show_process_node_flow();
    cout << "\n############################\n";

    cout << "\n-------------------------------------------------------------------------------\n";
    cout << "\n#################################### FCFS #####################################\n";
    int no=0;
    bool check = 0;

    while (check==0)
    {
        l.ready_quee_add_node(no);
        cout << "\nREADY QUEUE\n";
        l.show_ready_quee_node_flow();
        cout << endl;
        l.fcfs_execution();
        cout << "\nEXECUTION   QUEUE\n";
        l.show_fcfs_execution_node_flow();
        cout <<"\n=============================================================================\n";
        //cout<<l.r_head->r_work << endl;
        //cout << l.r_last->r_work << endl;
        if (l.r_head == l.r_last)
        {
            check = 1;
        }
        ++no;
    }
    cout << "\n################################################################################\n";
   
    return 0;
}