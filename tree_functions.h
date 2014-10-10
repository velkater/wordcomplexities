#ifndef TREE_FUNCTIONS_H_INCLUDED
#define TREE_FUNCTIONS_H_INCLUDED

#include <string>
using namespace std;
#include <iostream>
using namespace std;
#include "word.h"
#include <exception>
using namespace std;
#include "tree.h"
#include <fstream>
using namespace std;
/*!
 * \file Funkce pracujici se stromem
 * \brief insertPri
 *
 * funkce zajistuje razeni privilegovanych slov podle toho, ze ktereho slova byly stvoreny
 */
void insertPri(TTree<Factor *> * t, Factor* f)
{
    if(t->getRoot()==nullptr)   // pridavame prazdne slovo jako koren stromu
    {
        string * eps = new string("e");
        Factor *r = new Factor(0,eps);
        TNode<Factor*> *newroot = new TNode<Factor*>(r);
        t->setRoot(newroot);
    }

    if(f->getSize()==1) // pridavame pismena abecedy jako prvky nasledujici koren, podle nich se bude dal radit
    {
        TNode<Factor*> *newpal = new TNode<Factor*>(f);
        t->getRoot()->setNext(newpal);
    }
    else
    {
        string word = *(f->getWord()); // slovo ktere zarazujeme
        string lpps = word.substr(0,f->getLpps()); // nejdelsi vl priv sufix
        TNode<Factor*> *tmp = t->getRoot(); // zaciname od hlavy

        int i = 0;
        //hledame za ktery prvek budeme ve stroome ukladat
        while(lpps.compare(*(tmp->getData()->getWord())) != 0)
        {
            unsigned int act_size = (tmp->getNext())[i]->getData()->getSize(); // velikost dalsiho prvku se kterym se bude porovnavat
            string comp = *((tmp->getNext())[i]->getData()->getWord());

            //koukame se, ze ktereheho prvku slovo vychazi, porovnavame
            //slova ve strome a prefix odpovidajici delky
            while((word.substr(0,act_size)).compare(*((tmp->getNext())[i]->getData()->getWord())) != 0)
            {
                i++;
                act_size = (tmp->getNext())[i]->getData()->getSize();
            }
            tmp = (tmp->getNext())[i];
            i = 0;
        }
        TNode<Factor*> *newpal = new TNode<Factor*>(f);
        tmp->setNext(newpal);
    }
}
/*!
 * \brief insertTurn
 *
 * funkce zajistuje razeni modifikovanych privilegovanych slov podle toho, ze ktereho slova byly stvoreny
 */
void insertTurn(TTree<Factor *> * t, Factor* f)
{
    if(t->getRoot()==nullptr)   // pridavame prazdne slovo jako koren stromu
    {
        string * eps = new string("e");
        Factor *r = new Factor(0,eps);
        TNode<Factor*> *newroot = new TNode<Factor*>(r);
        t->setRoot(newroot);
    }

    if(f->getSize()==1) // pridavame pismena abecedy jako prvky nasledujici koren, podle nich se bude dal radit
    {
        TNode<Factor*> *newpal = new TNode<Factor*>(f);
        t->getRoot()->setNext(newpal);
    }
    else
    {
        string word = *(f->getWord()); // slovo ktere zarazujeme
        string lpts = word.substr(0,f->getLpts()); // nejdelsi vl priv sufix
        TNode<Factor*> *tmp = t->getRoot(); // zaciname od hlavy

        int i = 0;
        //hledame za ktery prvek budeme ve stroome ukladat
        while(lpts.compare(*(tmp->getData()->getWord())) != 0)
        {
            unsigned int act_size = (tmp->getNext())[i]->getData()->getSize(); // velikost dalsiho prvku se kterym se bude porovnavat
            string comp = *((tmp->getNext())[i]->getData()->getWord());

            //koukame se, ze ktereheho prvku slovo vychazi, porovnavame
            //slova ve strome a prefix odpovidajici delky
            while((word.substr(0,act_size)).compare(*((tmp->getNext())[i]->getData()->getWord())) != 0)
            {
                i++;
                act_size = (tmp->getNext())[i]->getData()->getSize();
            }
            tmp = (tmp->getNext())[i];
            i = 0;
        }
        TNode<Factor*> *newpal = new TNode<Factor*>(f);
        tmp->setNext(newpal);
    }
}
/*!
 * tiskne obsah uzlu do souboru
 */
void printNode(TNode<Factor*> *n, fstream &f)
{

    if(n)
    {
        for(unsigned int i=0; i< n->getNext().size(); i++)
        {
            string s = *(n->getData()->getWord())+" "+ *((n->getNext())[i]->getData()->getWord());
            f << s << endl;
        }

        for(unsigned int i=0; i< n->getNext().size(); i++)
            printNode((n->getNext())[i],f);
    }


}
/*!
 * tiskne slovo do souboru tak, aby z nej sel sestavit v Mathematice graf (vypise vsechny hrany)
 */
void printPri(TTree<Factor *> * t)
{
    string treename = t->getId();
    fstream f("grafy/txt/grafPri"+treename+".txt", ios_base::out);
    printNode(t->getRoot(),f);
    f.close();
}

void printTurn(TTree<Factor *> * t)
{
    string treename = t->getId();
    fstream f("grafy/txt/grafTurn"+treename+".txt", ios_base::out);
    printNode(t->getRoot(),f);
    f.close();
}

#endif // TREE_FUNCTIONS_H_INCLUDED
