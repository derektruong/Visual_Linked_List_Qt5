#ifndef SINGLE_LIST_H
#define SINGLE_LIST_H
#include<iostream>
#include<node.h>
template<typename T>
class single_list:public node
{
public:
    single_list()
    {
        this->SizeOfList=0;
    }

    void Initialize(single_list &list){
        list.pHead=list.pTail=nullptr;
    }
    node *Createnode(T d){
        node *pnode=new node;
          if(pnode!=nullptr){
            pnode->data=d;
            pnode->pNext=nullptr;
          }
          else std::cout<<"Error allocated memory!";
        return pnode;
    }
    void PrintList(single_list list){
        node *pTemp=list.pHead;
          if(pTemp==nullptr){
            std::cout<<"List is empty!!\n";
            return;
          }
          while(pTemp!=nullptr){
            std::cout<<pTemp->data<<"\t";
            pTemp=pTemp->pNext;
          }
          std::cout<<std::endl;
    }
    void InsertFirst(single_list &list,T d){
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
    void InsertTail(single_list &list,T d){
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
    void InsertMid(single_list &list,T d,int pos){
        node *pnode=Createnode(d);
          node *pTemp=list.pHead;
          node *pPre=new node;
          node *pIns=new node;
          int count=2;
          if(pos>list.SizeOfList||pos<1){
            std::cout<<"Unknown location error\n";
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
    void Delnode(single_list &list,int pos){
          node *pTemp=list.pHead;
          node *pPre=new node;
          node *pDel=new node;
          int count=2;
          if(pos>list.SizeOfList||pos<1){
            std::cout<<"Unknown location error\n";
            return;
          }
          if(list.pHead==nullptr){
            std::cout<<"List is empty!!\n";
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
    node *pSearchnode(single_list &list,T d){
        node *pTemp=list.pHead;
         while(pTemp!=nullptr){
           if(pTemp->data==d){
             break;
           }
           pTemp=pTemp->pNext;
         }
         return pTemp;
    }
private:
    int SizeOfList=0;
    node *pHead;
    node *pTail;
};

#endif // SINGLE_LIST_H
