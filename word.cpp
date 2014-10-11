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

/*!
 *  \brief funkce IsPalindrome
 *  overuje jestli je faktor palindrom
 */
bool Factor::IsPalindrome(void)
{
    unsigned int c = this->data->size();
    if (c==1)
        return true;
    for(unsigned int i = 0; i<(c/2); i++)
    {
        if((*(this->data))[i] != (*(this->data))[c-1-i])
            return false;
    }
    return true;
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
 * \brief privileged_stat
 * vyhleda privilegovana slova, vypise je do souboru a rekne pocty pro jednotlie delky a ulozi je do stromu
 */
void Word::privileged_stat(void)
{
    TTree<Factor *> * tree = new TTree<Factor *>(insertPri,printTree,"Pri"+this->getName()); //vytvarime strom
    string s = *(this->code);
    const string filename = "Pri"+this->getName()+".txt";
    fstream f(filename, ios_base::out);
    f << "===================="<< endl;
    f << "Privileged Words - " << this->getName() << endl;
    f << "===================="<< endl;
    int array[s.length()+1];                                    //slouzi na ukladani poctu pro jednotlive delky
    for(unsigned int k=0; k< s.length()+1; k++)
        array[k] = 0;
    for (unsigned int i=0; i< this->Length; i++)                // dva cykly vyzkousi vsechny  vsechny faktory slova
    {
        vector<string> vect;                                    //slouzi k tomu abychom kazdy vyskyt pocitali a zapisovali jen jednou
        for(unsigned int j=0; j < (this->Length)-i; j++)
        {
            string data = s.substr(j,i+1);
            string * dat = new string(data);
            //cout << dat->size() << endl;
            Factor *fac = new Factor(i+1,dat);
            bool erased = false;
            if(fac->IsPrivileged(fac->LPPS_length))
            {
                bool absent = true;                             //kouka se, jestli je to novy pri nebo jestli uz ho v seznamu mame
                unsigned int h=0;
                while((h<vect.size())&&(absent == true))
                {
                    absent = data.compare(vect[h]);
                    h++;
                }
                if(absent==true)                                //pridame novy pri
                {
                    array[i+1] +=1;
                    vect.push_back(data);
                    tree->insert(fac);
                    erased = true;//ukladame do stromu
                }
                else
                {
                    delete dat;
                    delete fac;
                    erased = true;
                }

            }
            if (not erased)
            {
                delete dat;
                delete fac;
            }

        }
        for(unsigned int h=0; h<vect.size(); h++)               //vypisujeme pri slova delky i
        {
            f << vect[h] << endl;
        }
        vect.clear();

    }
    for(unsigned int k=0; k< (s.length()+1); k++)               //vypisujeme pocet pri jednotlive delky
        f << k << "\t" << array[k] << endl;
    f.close();
    this->privileged_tree = tree;

}
/*!
 * \brief palindrom_stat
 * vyhleda privilegovana slova, vypise je do souboru a rekne pocty pro jednotlie delky a ulozi je do stromu
 */
void Word::palindrom_stat(void)
{
    string s = *(this->code);
    unsigned int total = 0;
    const string filename = "Pal"+this->getName()+".txt";
    fstream f(filename, ios_base::out);
    f << "===================="<< endl;
    f << "Palindroms - " << this->getName() << endl;
    f << "===================="<< endl;
    int array[s.length()+1];                            //slouzi na ukladani poctu pal jednotlive delky
    for(unsigned int k=0; k< s.length()+1; k++)
        array[k] = 0;
    for (unsigned int i=0; i< this->Length; i++)
    {
        vector<string> vect;                            //slouzi k tomu abychom kazdy vyskyt pocitali a zapisovali jen jednou
        for(unsigned int j=0; j < (this->Length)-i; j++)
        {
            string dat = s.substr(j,i+1);
            Factor *fac = new Factor(i+1,&dat);
            if(fac->IsPalindrome())
            {
                bool absent = true;                     //kouka se, jestli je to novy pal nebo jestli uz ho v seznamu mame
                unsigned int h=0;
                while((h<vect.size())&&(absent == true))
                {
                    absent = dat.compare(vect[h]);
                    h++;
                }
                if(absent==true)                        //pridame novy pal
                {
                    array[i+1] +=1;
                    vect.push_back(dat);
                    total++;
                }
            }
            delete fac;
        }
        for(unsigned int h=0; h<vect.size(); h++)       //vypisujeme palindromy delky i
        {
            f << vect[h] << endl;
        }
        vect.clear();
    }
    for(unsigned int k=0; k< (s.length()+1); k++)       //vypisujeme pocet pal jednotlive delky
        f << k << "\t" << array[k] << endl;
    f << "pro delku " << this->Length << " pocet " << total << endl;
    //cout << "pro delku" << this->Length << "pocet" << total << endl;
    f.close();
}

/*!
    \brief turned_stat
    vyhleda modifikovane privilegovana slova, vypise je to souboru a rekne pocty pro jednotlive delky a ulozi je do    stromu
*/
void Word::turned_stat(void)
{
    TTree<Factor *> * tree = new TTree<Factor *>(insertTurn,printTree,"Turn"+this->getName()); //vytvarime strom
    string s = *(this->code);
    unsigned int total = 0;
    const string filename = "Turn"+this->getName()+".txt";
    fstream f(filename, ios_base::out);
    f << "===================="<< endl;
    f << "Privileged Turn Words - " << this->getName() << endl;
    f << "===================="<< endl;
    int array[s.length()+1];                                    //slouzi na ukladani poctu pro jednotlive delky
    for(unsigned int k=0; k< s.length()+1; k++)
        array[k] = 0;
    for (unsigned int i=0; i< this->Length; i++)                // dva cykly vyzkousi vsechny  vsechny faktory slova
    {
        vector<string> vect;                                    //slouzi k tomu abychom kazdy vyskyt pocitaly a zapisovali jen jednou
        for(unsigned int j=0; j < (this->Length)-i; j++)
        {
            string data = s.substr(j,i+1);
            string * dat = new string(data);
            //cout << dat->size() << endl;
            Factor *fac = new Factor(i+1,dat);
            bool erased = false;
            if(fac->IsTurned(fac->LPTS_length))
            {
                bool absent = true;                             //kouka se, jestli je to novy pri nebo jestli uz ho v seznamu mame
                unsigned int h=0;
                while((h<vect.size())&&(absent == true))
                {
                    absent = data.compare(vect[h]);
                    h++;
                }
                if(absent==true)                                //pridame novy pri
                {
                    array[i+1] +=1;
                    vect.push_back(data);
                    tree->insert(fac);
                    total++;
                    erased = true;//ukladame do stromu
                }
                else
                {
                    delete dat;
                    delete fac;
                    erased = true;
                }

            }
            if (not erased)
            {
                delete dat;
                delete fac;
            }

        }
        for(unsigned int h=0; h<vect.size(); h++)               //vypisujeme pri slova delky i
        {
            f << vect[h] << endl;
        }
        vect.clear();

    }
    for(unsigned int k=0; k< (s.length()+1); k++)               //vypisujeme pocet pri jednotlive delky
        f << k << "\t" << array[k] << endl;
    f << "pro delku " << this->Length << " pocet " << total << endl;
    //cout << "pro delku" << this->Length << "pocet turn" << total << endl;
    f.close();
    this->turn_tree = tree;

}



















































