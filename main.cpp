#include <iostream>
using namespace std;
#include "word.h"
#include "word_gen.h"
using namespace binary;
#include <fstream>
using namespace std;


int statistics(Word &a, fstream &f)
{
    cout << a.getName() << endl;
    cout << a << endl;
    f<< a.getName() << endl;
    f << a << endl;
    a.privileged_stat();
    a.fprint_pri_tree();
    a.palindrom_stat();
    a.turned_stat();
    a.fprint_turn_tree();
    return 0;
}

int main()
{

    try
    {
        fstream f("slova.txt", ios_base::out);

        Word abc(64, generate_abc,"periodicka");
        statistics(abc,f);

        Word unif(64, generate_unif_mark_subs,"Uniform_marked");
        statistics(unif,f);

        Word fib(64, generate_Fibonacci,"Fibonnaci_Word");
        statistics(fib,f);

        Word thue(64, generate_ThueMorse,"Thue_Morse_Word");
        statistics(thue,f);

        Word w123(64, generate_RS, "Rudin_Shapir_Word");
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
        statistics(ber,f);

        Word pseudofib(128, generate_pseudoFibonacci, "Pseudo_Fib_word");
        statistics(pseudofib,f);

        f.close();

    }
    catch(exception &e)
    {
        cerr << "exception : " << e.what() << endl;
    }
    return 0;
}
