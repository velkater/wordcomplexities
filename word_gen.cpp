#include<iostream>
using namespace std;
#include "word_gen.h"
#include <exception>
using namespace std;

/*!
 * \file Word Generators
 * \brief funkce generujici slova
 *
 * Trida reprezentuje nekonecne slovo, ktere muze byt bud pevnym bodem substituce \
 * nebo generovane nejakou jinou funkci
 */
/*!
 * \namespace symb
 * \brief funkce generujici slova z pismen nebo symbolu
 */
namespace symb
{
void generate_abc(unsigned int L, string * s)
{
    char a[3] = {'a','b','c'};
    for(unsigned int i = 0; i<L; i++)
    {
        *(s) += a[i%3];
    }
}

}
/*!
 * \namespace binary
 * \brief funkce generujici binarni slova
 */
namespace binary
{
/*!
 * \brief Funkce generujici L prvnich pismen Fibonacciho slova
 * \param L delka slova
 * \param s ukazatal na string kde sebude slovo ukladat
 */
void generate_Fibonacci(unsigned int L, string * s)
{
    string tmp1 = "0";
    *(s) = "01";
    string tmp2;
    while(s->length() < L)
    {
        tmp2 = tmp1;
        tmp1 = *(s);
        *(s) += tmp2;
    }
    s->resize(L);
}
/*!
 * \brief Funkce generujici L prvnich pismen Thue-Morseova slova
 * \param L delka slova
 * \param s ukazatal na string kde sebude slovo ukladat
 */
void generate_ThueMorse(unsigned int L, string * s)
{
    string tmp1 = "0";
    string tmp2;
    while(s->length() < L)
    {
        tmp2 = tmp1;
        *(s) += tmp2;
        tmp1 = *(s);
        for(unsigned int i=0; i<tmp1.length() ; i++)
        {
            if(tmp1[i] =='1')
                tmp1[i] = '0';
            else
                tmp1[i] = '1';
        }
    }
    s->resize(L);

}
/*!
 * \brief Funkce generujici L prvnich pismen Rudin-Shapirova slova
 * \param L delka slova
 * \param s ukazatal na string kde sebude slovo ukladat
 */
void generate_RS(unsigned int L, string *s)
{
    *(s) = "01";
    for(unsigned int i = 1; i< L/2; i++)
    {
        switch ((*s)[i])
        {
        case '0':
            *(s) += "01";
            break;
        case '1':
            *(s) += "02";
            break;
        case '2':
            *(s) += "31";
            break;
        case '3':
            *(s) += "32";
            break;
        }
    }
    s->resize(L);
}
/*!
 * \brief Funkce generujici L prvnich pismen Gamma slova
 * \param L delka slova
 * \param s ukazatal na string kde sebude slovo ukladat
 */
void generate_gamma(unsigned int L, string *s)
{
    *(s) = "aca";
    for(unsigned int i = 1; i < L; i++)
    {
        switch((*s)[i])
        {
        case 'a':
            *(s) += "aca";
            break;
        case 'b':
            *(s) += "cab";
            break;
        case 'c':
            *(s) += "b";
            break;
        }
    }
    s->resize(L);
}
/*!
 * \brief Funkce generujici L prvnich pismen Beta slova
 * \param L delka slova
 * \param s ukazatal na string kde sebude slovo ukladat
 */
void generate_beta(unsigned int L, string *s)
{
    *(s) = "00120210";
    for(unsigned int i = 1; i < L; i++)
    {
        switch((*s)[i])
        {
        case '0':
            *(s) += "00120210";
            break;
        case '1':
            *(s) += "00";
            break;
        case '2':
            *(s) += "0";
            break;
        }
    }
    s->resize(L);
}
/*!
 * \brief Funkce generujici L prvnich pismen Chaconova slova
 * \param L delka slova
 * \param s ukazatal na string kde sebude slovo ukladat
 */
void generate_lambda(unsigned int L, string *s)
{
    *(s) = "0010";
    for(unsigned int i = 1; i < L; i++)
    {
        switch((*s)[i])
        {
        case '0':
            *(s) += "0010";
            break;
        case '1':
            *(s) += "1";
            break;
        }
    }
    s->resize(L);
}
/*!
 * \brief Funkce generujici L prvnich pismen Kappa slova
 * \param L delka slova
 * \param s ukazatal na string kde sebude slovo ukladat
 */
void generate_kappa(unsigned int L, string *s)
{
    *(s) = "00101100";
    string p1;
    for(unsigned int i = 1; i < L/8; i++)
    {
        p1 = *(s);
        for(unsigned int j = 0; j< i-1; j++)
            *(s) = p1+"0";
        *(s) += p1;
    }
    s->resize(L);
}
/*!
 * \brief Funkce generujici L prvnich pismen Berstelova slova
 * \param L delka slova
 * \param s ukazatal na string kde sebude slovo ukladat
 */
void generate_mu(unsigned int L, string *s)
{
    string p1;
    string p2 = "01";
    for(unsigned int i = 1; i < L/6; i++)
    {
        p1 = p2;
        p2 = p1+"23";
        p1 = string ( p1.rbegin(), p1.rend() );
        p2 += p1;

    }
    for(unsigned int i = 0; i < L/3; i++)
    {
        switch(p2[i])
        {
        case '0':
            *(s) += "101";
            break;
        case '1':
            *(s) += "1001";
            break;
        case '2':
            *(s) += "10001";
            break;
        case '3':
            *(s) += "100001";
            break;

        }
    }
    s->resize(L);
}
void generate_pseudoFibonacci(unsigned int L, string *s)
{
    string tmp1;
    generate_Fibonacci(L/2 +1, &tmp1);
    int i=0;
    while(s->length() < L)
    {
        if(tmp1[i] == '0')
            *(s) += "01";
        else
            *(s) += "10";
        i++;
    }

    s->resize(L);
}

void generate_unif_mark_subs(unsigned int L,string *s)
{
    *(s) = "001";
    for(unsigned int i = 1; i < L; i++)
    {
        switch((*s)[i])
        {
        case '0':
            *(s) += "001";
            break;
        case '1':
            *(s) += "110";
            break;
        }
    }
    s->resize(L);
}

void generate_abc(unsigned int L, string * s)
{
    char a[5] = {'a','b','c','c','d'};
    for(unsigned int i = 0; i<L; i++)
    {
        *(s) += a[i%5];
    }
}












































}
























