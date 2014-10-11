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
            string comp = *((ancestor->getNext())[i]->getData()->getWord());
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
/*! \brief funkce radici do stromu
 *
 * \param
 * \param
 * \return
 *
 */
void insert_tree(TTree<Factor *> *t, Factor * new_factor, unsigned int Lps_length,
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
        TNode<Factor*> *newpal = new TNode<Factor*>(new_factor);
        ancestor->setNext(newpal);
    }
}
/*!
 * \brief insertPri
 *
 * funkce zajistuje razeni privilegovanych slov podle toho, ze ktereho slova byly stvoreny
 */
void insertPri(TTree<Factor *> * t, Factor* f)
{
    insert_tree(t,f,f->getLppsLength(),findPosPri);
}


/*!
 * \brief insertTurn
 *
 * funkce zajistuje razeni modifikovanych privilegovanych slov podle toho, ze ktereho slova byly stvoreny
 */
void insertTurn(TTree<Factor *> * t, Factor* f)
{
    insert_tree(t,f,f->getLptsLength(),findPosPri);
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
