#ifndef WORD_H_INCLUDED
#define WORD_H_INCLUDED

#include <string>
using namespace std;
#include "tree.h"


class Factor
{
public:
    Factor(int s, string * d):size(s), data(d) {}
    ~Factor();
    int getSize()
    {
        return size;
    }
    int getLppsLength()
    {
        return LPPP_length;
    }
    int getLptsLength()
    {
        return LPTP_length;
    }
    int getLpprisLength()
    {
        return LPPriP_length;
    }
    int getLpepLength()
    {
        return LPEP_length;
    }
    string * getWord()
    {
        return data;
    }
    friend class Word;
    bool IsEpalindrome(unsigned int &);
    bool IsPalindrome(unsigned int &);
    bool IsPrivileged(unsigned int &);
    bool IsTurned(unsigned int &);
private:
    bool IsEpal(string);
    bool IsPal(string);
    unsigned int size;
    string * data;
    unsigned int LPPriP_length = 1;
    unsigned int LPTP_length = 1;
    unsigned int LPPP_length = 1;
    unsigned int LPEP_length = 0;

};



class Word
{
public:
    enum Type {PAL, PRI, TURN, EPAL};
    Word(int l, void (*gen) (unsigned int L, string* s),string name);
    ~Word()
    {
        if(code)
            delete code;
        if(privileged_tree)
            delete privileged_tree;
        if(turn_tree)
            delete turn_tree;
        if(palindrom_tree)
            delete palindrom_tree;
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
    void privilegedStat(void);
    void palindromStat(void);
    void turnedStat(void);
    void epalStat(void);
    void basicStats(TTree<Factor *> * tree, Type filetype, const string title);
    void fprintPriTree(void)
    {
        this->privileged_tree->print();
    }
    void fprintTurnTree(void)
    {
        this->turn_tree->print();
    }
    void fprintPalTree(void)
    {
        this->palindrom_tree->print();
    }
    void fprintEpalTree(void)
    {
        if(this->epal_tree)
            this->epal_tree->print();
    }
    void wordStats(void);
    void printAlphabet(void)
    {
        for(unsigned int i = 0; i < alphabet.size(); i++) cout << alphabet[i] << " ";
    }
private:
    TTree<Factor*> * palindrom_tree;
    TTree<Factor*> * privileged_tree;
    TTree<Factor*> * turn_tree;
    TTree<Factor*> * epal_tree;
    void basicStats(void);
    unsigned int Length;
    string* code;                               //obsah nagenerovaneho slova
    string Name;
    vector<char> alphabet;

};

ostream& operator<<(ostream &ost, Word & u);    //pretizeny operator aby rovnou vypisoval slovo, kdyz dostane na nej ukazatel


#endif // WORD_H_INCLUDED
