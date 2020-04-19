#include<iostream>
#include "single_list.h"
//#include"node.h"
using namespace std;
single_list::single_list()
{
    this->SizeOfList=0;
}

void single_list::Initialize(single_list &list){
    list.pHead=list.pTail=nullptr;
}
node single_list::*Createnode(int d){
    node *pnode=new node;
      if(pnode!=nullptr){
        pnode->data=d;
        pnode->pNext=nullptr;
      }
      else cout<<"Error allocated memory!";
    return pnode;
}
void single_list::PrintList(single_list list){
    node *pTemp=list.pHead;
      if(pTemp==nullptr){
        cout<<"List is empty!!\n";
        return;
      }
      while(pTemp!=nullptr){
        cout<<pTemp->data<<"\t";
        pTemp=pTemp->pNext;
      }
      cout<<endl;
}
void single_list::InsertFirst(single_list &list,int d){
    node *pnode=Createnode(d);
      if(list.pHead==nullptr){
        list.pHead=pnode;
        list.pTail=pnode;
        list.SizeOfList++;
        return;
      }
      while(list.pHead!=nullptr){
        pnode->pNext=list.pHead;
        list.pHead=pnode;
        list.SizeOfList++;
        return;
      }
}
void single_list::InsertTail(single_list &list,int d){
    node *pnode=Createnode(d);
      if(list.pTail==nullptr){
        list.pHead=pnode;
        list.pTail=pnode;
        list.SizeOfList++;
        return;
      }
      while(list.pTail!=nullptr){
        list.pTail->pNext=pnode;
        list.pTail=pnode;
        list.SizeOfList++;
        return;
      }
}
void single_list::InsertMid(single_list &list,int d,int pos){
    node *pnode=Createnode(d);
      node *pTemp=list.pHead;
      node *pPre=new node;
      node *pIns=new node;
      int count=2;
      if(pos>list.SizeOfList||pos<1){
        cout<<"Unknown location error\n";
        return;
      }
      if(list.pHead==nullptr){
        list.pHead=pnode;
        list.pTail=pnode;
        return;
      }
      if(pos==1) InsertFirst(list,d);
      while(pTemp!=nullptr){
        if(count==pos){
          pPre=pTemp;
          pIns=pTemp->pNext;
          pPre->pNext=pnode;
          pnode->pNext=pIns;
          list.SizeOfList++;
          return;
        }
        count++;
        pTemp=pTemp->pNext;
      }
}
void single_list::Delnode(single_list &list,int pos){
      node *pTemp=list.pHead;
      node *pPre=new node;
      node *pDel=new node;
      int count=2;
      if(pos>list.SizeOfList||pos<1){
        cout<<"Unknown location error\n";
        return;
      }
      if(list.pHead==nullptr){
        cout<<"List is empty!!\n";
        return;
      }
      if(pos==1){
        list.pHead=pTemp->pNext;
        delete pTemp;
        pTemp=nullptr;
        return;
      }
      while(pTemp!=nullptr){
        if(count==pos){
          pPre=pTemp;
          pDel=pTemp->pNext;
          pPre->pNext=pDel->pNext;
          delete pDel;
          pDel=nullptr;
          return;
        }
        count++;
        pTemp=pTemp->pNext;
      }
}
node single_list::*pSearchnode(single_list &list,int d){
    node *pTemp=list.pHead;
     while(pTemp!=nullptr){
       if(pTemp->data==d){
         break;
       }
       pTemp=pTemp->pNext;
     }
     return pTemp;
}
