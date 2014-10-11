#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED

#include <vector>
using namespace std;

/*!
 * \file Sablona stromu, kde kazdy uzel ma libovolny pocet potomku
 */

template<class T>
class TNode
{
public:
    TNode(T d) : data(d) {}
    ~TNode();
    T getData()
    {
        return data;
    }
    vector<TNode<T>*> getNext()
    {
        return next;
    }
    void setNext(TNode<T> * n)
    {
        next.push_back(n);
    }
    void setData(T d)
    {
        data = d;
    }
    template<typename> friend class TTree;
private:
    T data;
    vector<TNode<T>*> next;

};
template<class T>
TNode<T>::~TNode()
{
    if(data)
    {
        if(data->getWord())
        {
            delete data->getWord();
        }
        delete data;

    }
}

template<class T>
class TTree
{
public:
    TTree(void(*ins)(TTree<T> *, T),void(*printfunction)(TTree<T> *),string name);
    ~TTree();
    void insert(T &);
    void print(void);
    TNode<T> * getRoot()
    {
        return root;
    }
    void setRoot(TNode<T> * r)
    {
        root = r;
    }
    string getId(void)
    {
        return this->id;
    }
private:
    void clearTree(TNode<T> *);
    void (*insertfunction)(TTree<T> *, T);
    void (*printfunction)(TTree<T> *);
    string id;
    TNode<T> *root;
};
template<class T>
TTree<T>::TTree(void (*ins)(TTree<T> *, T),void (*prt)(TTree<T> *),string name)
{
    root = 0;
    id = name;
    insertfunction = ins;
    printfunction = prt;
}
template<class T>
TTree<T>::~TTree()
{
    if(root)
        clearTree(root);
}
template<class T>
void TTree<T>::clearTree(TNode<T> *n)
{
    if(n)
    {
        for(unsigned int i=0; i< n->next.size(); i++)
        {
            clearTree(n->next[i]);
        }
            delete n;
    }
}
template<class T>
void TTree<T>::insert(T &d)
{
    insertfunction(this, d);
}
template<class T>
void TTree<T>::print(void)
{
    printfunction(this);
}


#endif // TREE_H_INCLUDED
