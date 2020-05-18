//// Created by Lian Gh on 03/12/2019.//#ifndef HW1_DATACENTERMANAGER_H#define HW1_DATACENTERMANAGER_H#include <stdlib.h>#include <assert.h>#include <stdio.h>#include <stdlib.h>#include <string.h>#include "library1.h"#include"List.h"#include "AVLTree.h"#define  LINUX 0#define WINDOWS 1///--------------------- OSnode - Tree Node -------------------------------//////**************************************************************************class OSnode{private:    int dataCenterID;    int numOfServers;public:    OSnode() :dataCenterID(-1) ,numOfServers(-1) {}//default constructor    OSnode(int dataCenterID, int numOfServers=0) :dataCenterID(dataCenterID),numOfServers(numOfServers){}//constructor    ~OSnode() = default;    int GetDataCenterID(){        return dataCenterID;    }    friend bool operator<(const OSnode& first, const OSnode& second);    friend bool operator>(const OSnode& first, const OSnode& second);    friend bool operator==(const OSnode& first, const OSnode& second);};//logical operators for the classbool operator<(const OSnode& first, const OSnode& second);bool operator>(const OSnode& first, const OSnode& second); bool operator==(const OSnode& first, const OSnode& second);///**************************************************************************///--------------------- Data Center Class -------------------------------//////**************************************************************************class DataCenter{private:    int dataCenterID;    int numOfServers;public:    List<int,int> Linux_List;    List<int, int> Windows_List;    ListNode<int,int>** ptr_array;    int * serverOS_array;    int linux_Counter ;    int windows_Counter;    DataCenter( int dataCenterID , int numOfServers=1) :dataCenterID(dataCenterID),numOfServers(numOfServers),Linux_List(),Windows_List(),    linux_Counter(numOfServers),windows_Counter(0){        ptr_array= new ListNode<int,int>* [numOfServers];        serverOS_array=new int[numOfServers];        for(int i=numOfServers-1 ; i>=0; i--){            ptr_array[i]= Linux_List.AddNode(i,i);            serverOS_array[i]=LINUX;        }    }    DataCenter()= default;    //constructor    ~DataCenter(){        delete[] ptr_array;        delete[] serverOS_array;    }    int GetnumOfServers(){        return numOfServers;    }    int GetdataCenterID(){        return dataCenterID;    }    friend bool operator<(const DataCenter& first, const DataCenter& second);    friend bool operator>(const DataCenter& first, const DataCenter& second);    friend bool operator==(const DataCenter& first, const DataCenter& second);};//logical operators for the classbool operator<(const DataCenter& first, const DataCenter& second);bool operator>(const DataCenter& first, const DataCenter& second);bool operator==(const DataCenter& first, const DataCenter& second);///**************************************************************************///----------------------DATA CENTER MANAGER --------------------------------class DataCenterManager {private:    AVLTree<DataCenter*,int> DataCentersTree;    AVLTree<OSnode*,OSnode> Linux_Tree;    AVLTree<OSnode*,OSnode> Windows_Tree;   void updateWindowsAdd(DataCenter* data_center);   void updateLinuxAdd(DataCenter* data_center);public:    DataCenterManager(): DataCentersTree(), Linux_Tree(), Windows_Tree() {};    ~DataCenterManager() = default;    ///---------------------DATA CENTER FUNCTIONS ------------------------------    StatusType AddDataCenter( int dataCenterID, int numOfServers);    StatusType RemoveDataCenter( int dataCenterID);    StatusType RequestServer( int dataCenterID, int serverID, int os, int *assignedID);    StatusType FreeServer( int dataCenterID, int serverID);    StatusType GetDataCentersByOS( int os, int **dataCenters, int* numOfDataCenters);};///**************************************************************************#endif //HW1_DATACENTERMANAGER_H