#include <string>
using namespace std;
#include <iostream>
using namespace std;
#include "word.h"
#include "tree.h"
#include <fstream>
#include "tree_functions.h"

/*!
 * \file Faktory
 * \class Factor
 * \brief faktor
 *
 * Trida reprezentujici faktory, tj. konecne casti slov
 */
/*! \brief
 *
 * \param
 * \param
 * \return
 *
 */

bool Factor::IsPal(string s)
{
    unsigned int c = s.size();
    if (c==1)
        return true;
    for(unsigned int i = 0; i<(c/2); i++)
    {
        if(s[i] != s[c-1-i])
            return false;
    }
    return true;
}
/*!
 *  \brief funkce IsPalindrome
 *  overuje jestli je faktor palindrom
 */
bool Factor::IsPalindrome(unsigned int &lpps)
{
    unsigned int c = this->getSize();
    string s = *(this->getWord());
    unsigned int i = c-1;
    while((i > 1) && (this->IsPal(s.substr(0,i))== false))
    {
        i--;
    }
    lpps = i;
    bool result = IsPal(s);
    return result;
}
/*!
 *  \brief funkce IsPalindrome
 *  overuje jestli je faktor privilegovane slovo
 */
bool Factor::IsPrivileged(unsigned int &lpps)
{
    unsigned int c = this->data->size();
    string w = *(this->data);
    unsigned int T[c];
    unsigned int p = 1;
    if (c==1)
        return true;
    else
    {
        T[0]=0;
        int j;
        for(unsigned int i=1; i<c; i++)
        {
            j = T[i-1];
            while(true)
            {
                if(w[j] == w[i])
                {
                    T[i] = j+1;
                    if(T[i]== p)
                    {
                        lpps = p;
                        p=i+1;
                    }
                    break;
                }
                else if(j==0)
                {
                    T[i]=0;
                    break;
                }
                j = T[j-1];
            }
        }
        if(p==c)
            return true;
        else
            return false;
    }
}

bool Factor::IsTurned(unsigned int &lpts)
{
    unsigned int c = this->data->size();
    string w = *(this->data);
    unsigned int p=1; // do p ukadame delku l
    lpts=p;
    if(c==1)
        return true;
    else
    {
        for(unsigned int i=1; i<c; i++)
        {
            unsigned int j=0;
            while(j<p)
            {
                if(w[j] == w[i-j])
                    j++;
                else
                    break;
            }
            if(j==p)
            {
                lpts = p;
                p=i+1;
            }
        }
        //cout << w << endl;
        string w2= w.substr(0,w.size()-1);
        //cout << w2 << endl;
        string u= w.substr(0,lpts);
        if((p==c) && (w2.find(u,1) == string::npos))
            return true;
        else
            return false;
    }
}
Factor::~Factor(void) // tady to něco nejspíš špatně
{
    if(this->data)
    {
        delete this->data;
    }
}

/*!
 * \class Word
 * \brief Slovo
 *
 * Trida reprezentuje nekonecne slovo, ktere muze byt bud pevnym bodem substituce \
 * nebo generovane nejakou jinou funkci
 */
/*!
 * \brief Konstruktor
 * vytvori pomoci generujici funkce nove slovo delky L
 * \param l delka slova
 * \param gen funkce ze ktere se slovo generuje
 */
Word::Word(int l, void (*gen) (unsigned int L, string* s),string name)
{
    try
    {
        this->code = new(nothrow) string;
        if(!code)
            throw(bad_alloc());

        gen(l, code);
        this->Length = code->length();
        this->Name = name;
        this->privileged_tree = nullptr;
        this->turn_tree = nullptr;
        this->palindrom_tree = nullptr;
    }
    catch(exception &e)
    {
        cerr << "exception : " << e.what() << endl;
        throw(bad_alloc());
    }
}
/*!
 * \brief operator <<
 * pretezuje operator << aby se slovo rovnou vypsalo
 */
ostream& operator<<(ostream & ost, Word &u)
{
    ost << *(u.getWord());
    return ost;
}
/*!
 * \brief palindrom_stat
 * vyhleda privilegovana slova, vypise je do souboru a rekne pocty pro jednotlie delky a ulozi je do stromu
 */
void Word::palindromStat(void)
{
    TTree<Factor *> * tree = new TTree<Factor *>(insertPal,printTree,"Pal"+this->getName());
    this->basicStats(tree, this->PAL, "seznamy/pal/");
    this->palindrom_tree = tree;
}
/*!
 * \brief privileged_stat
 * vyhleda privilegovana slova, vypise je do souboru a rekne pocty pro jednotlie delky a ulozi je do stromu
 */
void Word::privilegedStat(void)
{
    TTree<Factor *> * tree = new TTree<Factor *>(insertPri,printTree,"Pri"+this->getName());
    this->basicStats(tree, this->PRI, "seznamy/pri/");
    this->privileged_tree = tree;

}
/*!
    \brief turned_stat
    vyhleda modifikovane privilegovana slova, vypise je to souboru a rekne pocty pro jednotlive delky a ulozi je do    stromu
*/
void Word::turnedStat(void)
{
    TTree<Factor *> * tree = new TTree<Factor *>(insertTurn,printTree,"Turn"+this->getName());
    this->basicStats(tree, this->TURN, "seznamy/turn/");
    this->turn_tree = tree;
}

void Word::basicStats(TTree<Factor *> * tree, Type filetype, const string filepath)
{
    string s = *(this->code);
    unsigned int total = 0;
    fstream f(filepath + this->getName() + ".txt", ios_base::out);
    f << "===================="<< endl;
    switch(filetype)
    {
    case PAL:
        f << "Palindroms -- ";
        break;
    case PRI:
        f << "Privileges words -- ";
        break;
    case TURN:
        f << "Turn words -- ";
        break;
    }
    f << this->getName() << endl;
    f << "===================="<< endl;
    //slouzi na ukladani poctu pro jednotlive delky
    int array[s.length()+1];
    for(unsigned int k=0; k< s.length()+1; k++)
        array[k] = 0;
    // dva cykly vyzkousi vsechny  vsechny faktory slova
    for (unsigned int i=0; i< this->Length; i++)
    {
        vector<string> vect;
        //slouzi k tomu abychom kazdy vyskyt pocitaly a zapisovali jen jednou
        for(unsigned int j=0; j < (this->Length)-i; j++)
        {
            string data = s.substr(j,i+1);
            string * dat = new string(data);
            Factor *fac = new Factor(i+1,dat);
            bool istype = false;
            bool inserted  = false;
            switch(filetype)
            {
            case PAL :
                istype = fac->IsPalindrome(fac->LPPS_length);
                break;
            case PRI :
                istype = fac->IsPrivileged(fac->LPPriS_length);
                break;
            case TURN :
                istype = fac->IsTurned(fac->LPTS_length);
                break;
            }
            if(istype)
            {
                unsigned int h=0;
                while((h<vect.size())&&(data.compare(vect[h]) != 0))
                {
                    h++;
                }
                //ukladame do stromu jen pokud se vyskytuje poprve
                if(h == vect.size())
                {
                    array[i+1] +=1;
                    vect.push_back(data);
                    tree->insert(fac);
                    inserted = true;
                    total++;
                }
            }
            if(inserted == false)
            {
                delete fac;
            }
        }
        for(unsigned int h=0; h<vect.size(); h++)
        {
            f << vect[h] << endl;
        }
        vect.clear();
    }
    for(unsigned int k=0; k< (s.length()+1); k++)
        f << k << "\t" << array[k] << endl;
    f << "Pro delku prefixu " << this->Length << " pocet " << total << endl;
    f.close();
}
void Word::wordStats(void)
{
    this->privilegedStat();
    this->fprintPriTree();
    this->palindromStat();
    this->fprintPalTree();
    this->turnedStat();
    this->fprintTurnTree();
}
