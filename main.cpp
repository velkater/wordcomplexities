#include <iostream>
#include "word.h"
#include "word_gen.h"
#include <fstream>
using namespace std;


int statistics(Word &a, fstream &f)
{
    cout << a.getName() << endl;
    cout << a << endl;
    f<< a.getName() << endl;
    f << a << endl;
    a.wordStats();
    return 0;
}

int main()
{

    try
    {

        fstream f("slova.txt", ios_base::out);

        //Word unif(64, generate_unif_mark_subs,"Uniform_marked");
        //statistics(unif,f);

        /*Word abc(64, generate_abc,"periodicka");
        statistics(abc,f);*/

        Word fib(200, generate_Fibonacci,"Fibonnaci_Word");
        statistics(fib,f);

        /*Word thue(100, generate_ThueMorse,"Thue_Morse_Word");
        statistics(thue,f);*/

        /*Word w123(64, generate_RS, "Rudin_Shapir_Word");
        statistics(w123,f);

        Word gamma(64, generate_gamma,"Gamma_word");
        statistics(gamma,f);

        Word beta(64, generate_beta,"Beta_word");
        statistics(beta,f);

        Word chacon(64, generate_lambda,"Lambda_Chacon_word");
        statistics(chacon,f);

        Word uzero(64, generate_kappa,"Kappa_word");
        statistics(uzero,f);

        Word ber(64, generate_mu,"Mu_Berstel09_word");
        statistics(ber,f);*/

        //Word pseudofib(64, generate_pseudoFibonacci, "Pseudo_Fib_word");
        //statistics(pseudofib,f);

        /*Word caccb(1000, generate_caccb, "Caccb64");
        statistics(caccb,f);*/

        //Word r1(64, generate_R1, "a_aab__b_ac__c_a64");
        //statistics(r1,f);

        //Word r2(64, generate_R2, "a_aab__b_c__c_ab64");
        //statistics(r2,f);

        //Word deltafib(64, generate_delta_fibonacci, "Delta_Fibonacci");
        //statistics(deltafib,f);

        //Word fileword(20, generate_fromfile, "File_Fibonacci");
        //statistics(fileword,f);

        Word modifib(200, generate_modifFibonacci, "Modifikovany_Fibonacci");
        statistics(modifib,f);

        //Word st(64, generate_st, "SaT");
        //statistics(st,f);

        f.close();

    }
    catch(exception &e)
    {
        cerr << "exception : " << e.what() << endl;
    }
    return 0;
}
