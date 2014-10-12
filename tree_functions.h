#ifndef TREE_FUNCTIONS_H_INCLUDED
#define TREE_FUNCTIONS_H_INCLUDED

#include <string>
#include <iostream>
#include "word.h"
#include <exception>
#include "tree.h"
#include <fstream>
#include <cstdlib>
using namespace std;

/*! \brief
 *
 * \param
 * \param
 * \return
 *
 */
TNode<Factor*> * findPosPri(TTree<Factor *> * t, string word, unsigned int lps_length)
{
    //najdeme lpps nebo lpts
    string lps = word.substr(0,lps_length);
    //zacneme u hlavy
    TNode<Factor*> *ancestor = t->getRoot();
    int i = 0;
    //hledame za ktery prvek budeme ve stroome ukladat
    while(lps.compare(*(ancestor->getData()->getWord())) != 0)
    {
        // velikost dalsiho prvku se kterym se bude porovnavat
        unsigned int act_size = (ancestor->getNext())[i]->getData()->getSize();
        //koukame se, ze ktereheho prvku slovo vychazi, porovnavame
        //slova ve strome a prefix odpovidajici delky
        while((word.substr(0,act_size)).compare(*((ancestor->getNext())[i]->getData()->getWord())) != 0)
        {
            i++;
            act_size = (ancestor->getNext())[i]->getData()->getSize();
        }
        ancestor = (ancestor->getNext())[i];
        i = 0;
    }
    return ancestor;
}
/*! \brief
 *
 * \param
 * \param
 * \return
 *
 */
TNode<Factor*> * findPosPal(TTree<Factor *> * t, string word, unsigned int lps_length)
{
    //zacneme u hlavy
    TNode<Factor*> *ancestor = t->getRoot();
    int i = 0;
    if(word.size() == 2)
    {
        return ancestor;
    }
    else
    {
        unsigned int wsize = word.size();
        string palroot = word.substr(1,(word.size()-2));
        while(palroot.compare(*(ancestor->getData()->getWord())) != 0)
        {
            string compared = *((ancestor->getNext())[i]->getData()->getWord());
            unsigned int act_size = (ancestor->getNext())[i]->getData()->getSize();
            while(act_size%2 != wsize %2)
            {
                i++;
                act_size = (ancestor->getNext())[i]->getData()->getSize();
                compared = *((ancestor->getNext())[i]->getData()->getWord());
            }
            string tmp = word.substr(wsize/2 - act_size/2,act_size);
            while( compared.compare(tmp)!=0 )
            {
                i++;
                act_size = (ancestor->getNext())[i]->getData()->getSize();
                while(act_size%2 != wsize %2)
                {
                    i++;
                    act_size = (ancestor->getNext())[i]->getData()->getSize();
                }
                compared = *((ancestor->getNext())[i]->getData()->getWord());
                tmp = word.substr(wsize/2 - act_size/2,act_size);
            }
            ancestor = (ancestor->getNext())[i];
            i = 0;

        }
        return ancestor;
    }
}

/*! \brief funkce radici do stromu
 *
 * \param
 * \param
 * \return
 *
 */
void insertTree(TTree<Factor *> *t, Factor * new_factor, unsigned int Lps_length,
                 TNode<Factor*> * (*find_pos)(TTree<Factor *> *, string , unsigned int))
{
    //pridavame prazdne slovo jako koren stromu
    if(t->getRoot()==nullptr)
    {
        string * eps = new string("e");
        Factor *r = new Factor(0,eps);
        TNode<Factor*> *newroot = new TNode<Factor*>(r);
        t->setRoot(newroot);
    }

    // pridavame pismena abecedy jako prvky nasledujici koren,
    //podle nich se bude dal radit
    if(((new_factor->getWord())->size())==1)
    {
        TNode<Factor*> *newletter = new TNode<Factor*>(new_factor);
        t->getRoot()->setNext(newletter);
    }
    else
    {
        TNode<Factor*> *ancestor = find_pos(t,*(new_factor->getWord()), Lps_length);
        TNode<Factor*> *newnode = new TNode<Factor*>(new_factor);
        ancestor->setNext(newnode);
    }
}
/*!
 * \brief insertPri
 *
 * funkce zajistuje razeni privilegovanych slov podle toho, ze ktereho slova byly stvoreny
 */
void insertPal(TTree<Factor *> * t, Factor* f)
{
    insertTree(t,f,f->getLppsLength(),findPosPal);
}
/*!
 * \brief insertPri
 *
 * funkce zajistuje razeni privilegovanych slov podle toho, ze ktereho slova byly stvoreny
 */
void insertPri(TTree<Factor *> * t, Factor* f)
{
    insertTree(t,f,f->getLpprisLength(),findPosPri);
}


/*!
 * \brief insertTurn
 *
 * funkce zajistuje razeni modifikovanych privilegovanych slov podle toho, ze ktereho slova byly stvoreny
 */
void insertTurn(TTree<Factor *> * t, Factor* f)
{
    insertTree(t,f,f->getLptsLength(),findPosPri);
}

/*!
 * tiskne obsah uzlu do souboru
 */
void printNodes(TNode<Factor*> *n, fstream &f)
{
    if(n)
    {
        for(unsigned int i=0; i< n->getNext().size(); i++)
        {
            string s = *(n->getData()->getWord())+" -> "+ *((n->getNext())[i]->getData()->getWord())+";";
            f << s << endl;
        }

        for(unsigned int i=0; i< n->getNext().size(); i++)
            printNodes((n->getNext())[i],f);
    }
}
/*!
 * tiskne slovo do souboru tak, aby z nej sel sestavit v Mathematice graf (vypise vsechny hrany)
 */
void printTree(TTree<Factor *> * t)
{
    string treename = t->getId();
    string filepath = "grafy/dot/" + treename + ".dot";
    fstream f(filepath, ios_base::out);
    f << "digraph G {" << endl;
    f << "node [fontname = \"DejaVuSans\"];" << endl;
    printNodes(t->getRoot(),f);
    f << "}" << endl;
    f.close();
    string command = "dot -Tpdf " + filepath + " -o grafy/pdf/" + treename + ".pdf";
    system(command.c_str());

}

#endif // TREE_FUNCTIONS_H_INCLUDED
