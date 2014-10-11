#ifndef WORD_H_INCLUDED
#define WORD_H_INCLUDED

#include <string>
using namespace std;
#include "tree.h"


class Factor
{
public:
    Factor(int s, string * d):size(s), data(d),LPPS_length(0) {}
    ~Factor();
    int getSize()
    {
        return size;
    }
    int getLppsLength()
    {
        return LPPS_length;
    }
    int getLptsLength()
    {
        return LPTS_length;
    }
    string * getWord()
    {
        return data;
    }
    friend class Word;
    bool IsPalindrome(void);
    bool IsPrivileged(unsigned int &p);
    bool IsTurned(unsigned int &p);
private:
    unsigned int size;
    string * data;                              //ukazatel na obsah faktoru
    unsigned int LPPS_length;       //delka nejdelsiho vlastniho privilegovaneho sufixu
    unsigned int LPTS_length;
};



class Word
{
public:
    Word(int l, void (*gen) (unsigned int L, string* s),string name);
    ~Word()
    {
        delete code;
        if(privileged_tree)
            delete privileged_tree;
        if(turn_tree)
            delete turn_tree;
    }
    unsigned int getLength(void)
    {
        return this->Length;
    }
    string * getWord(void)
    {
        return this->code;
    }
    string getName(void)
    {
        return this->Name;
    }
    void privileged_stat(void);
    void palindrom_stat(void);
    void turned_stat(void);
    void fprint_pri_tree(void)
    {
        this->privileged_tree->print();
    }
    void fprint_turn_tree(void)
    {
        this->turn_tree->print();
    }
private:
    TTree<Factor*> * privileged_tree;
    TTree<Factor*> * turn_tree;
    unsigned int Length;
    string* code;                               //obsah nagenerovaneho slova
    string Name;

};

ostream& operator<<(ostream &ost, Word & u);    //pretizeny operator aby rovnou vypisoval slovo, kdyz dostane na nej ukazatel


#endif // WORD_H_INCLUDED
