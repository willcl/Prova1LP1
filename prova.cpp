/**!
 *  Program usado na avaliação de LP1, 2017.1
 *  @date 11 de abrill de 2017
 */

#include <iostream>  // cout, endl
#include <iomanip>   // setw
#include <iterator>  // distance
#include <cstdlib>   // memset, memcmp, memcpy
#include <cassert>   // assert()
#include <cstring>



// ================================================================================

namespace prova
{
    // Tipos basicos utiizados pelas funções.
    using byte = unsigned char;
    using Compare = int(const void*, const void*);
    using UnaryPredicate = bool(const void*);

    // Questão 1
    bool eh_particionada( const void * first, const void * last, size_t size,
            UnaryPredicate *p )
    {
        // TODO: seu código vai aqui

		byte *first_ = (byte *) first;
		byte *last_ = (byte *) last;
		byte *tru = (byte *) first;
		byte *fal = (byte *) last;
		while (first_ != last_){
			if (p(first_)) tru = first_;
			else fal = first_;
			if(tru > fal) return false;
			first_+=size;
		}
        return true; // stub, substituir por seu código
    }

    // Questão 2-a
    const void * limite_inferior( const void *first, const void *last,
            size_t size, const void * value, Compare *cmp )
    {
        // TODO: seu código vai aqui
        byte *first_ = (byte *) first;
		byte *last_ = (byte *) last;
		if (first_ == last_) return last_;
		
		int n = (std::distance(first_ , last_))/(size*2);
		std::cout << n << " ";
		auto m = first_+(n*size);
		std::cout << (int)*m << "\n";
		if(cmp( m , value ) == -1) return prova::limite_inferior( m+size, last_ , size , value , cmp );
		return prova::limite_inferior(first_, m , size , value , cmp );


        // stub, substituir por seu código
    }

    // Questão 2-b
    const void * limite_superior( const void *first, const void *last,
            size_t size, const void * value, Compare *cmp )
    {
        // TODO: seu código vai aqui
        byte *first_ = (byte *) first;
		byte *last_ = (byte *) last;
		if (first_ == last_) return last_;

		int n = (std::distance(first_ , last_))/(size*2);
		std::cout << n << " ";
		auto m = first_+(n*size);
		std::cout << (int)*m << "\n";
		if (cmp( m , value ) == 1 ) return prova::limite_superior(first_, m , size , value , cmp );
		return prova::limite_superior( m+size, last_ , size , value , cmp );
         // stub, substituir por seu código
    }

    // Questão 3
    void * remove( const void *first, const void *last, const void *first_r,
               const void *last_r, size_t size )
    {
        // TODO: seu código vai aqui

		byte *last1 = (byte *) last;
		byte *first2 = (byte *) first_r;
		byte *last2 = (byte *) last_r;
		while (last2 != last1){
			memcpy(first2 , last2 , size);
			first2+=size;
			last2+=size;
		}
		return first2;

        return (void*) last;  // stub, substituir por seu código
    }

    // Questão 4
    bool contem( const void *first1, const void *last1, const void *first2,
            const void *last2, size_t size, Compare *cmp )
    {
        // TODO: seu código vai aqui
        return false; // stub, substituir por seu código
    }

    // Questão 5
    void * remove_repetidos( const void *first, const void *last, const void *value,
            size_t size, Compare *cmp )
    {
        // TODO: seu código vai aqui
        return (void*) last; // stub, substituir por seu código
    }
} // namespace prova


// ================================================================================
// CLIENT CODE
// ================================================================================

bool eh_impar( const void *a )
{
    // TODO: seu código vai aqui
    int *b = (int *) a;
    if(*b % 2 == 0) return false;
    return true; // Stub, substituir...
}

bool acima_20( const void *a )
{
    // TODO: seu código vai aqui
    int *b = (int *) a;
    if(*b > 20) return true;
    
    return false; // Stub, substituir...
}

int compare_ints( const void * a, const void * b )
{
    // TODO: seu código vai aqui
    int *a_ = (int *) a;
    int *b_ = (int *) b;
    if(*a_ < *b_) return -1;
    else if (*a_ > *b_) return 1;
    return 0;
}



int main( )
{
    size_t score = 0;
    size_t total = 65; // Pontos das 2 primeiras questões.
    std::cout << ">>> Voce inicia a prova com " << score << " pontos (de " << total << ").\n\n";

    // ================================================================================
    // Questao 1 - teste: vetor está particionado
    // ================================================================================
    {
        std::cout << ">>> Q1-a: testando a funcao eh_particionada()\n";

        int A[] = { 1, 3, 5, 7, 9, 2, 4, 6, 8, 10 };

        // Verificando se o vetor estah particionado com os impares na frente dos pares.
        auto result = prova::eh_particionada( std::begin(A), std::end(A), sizeof(int), eh_impar );
        if ( result == false )
        {
            std::cout << "    Sua resposta estah incorreta!\n";
        }
        else
        {
            score += 10;
            std::cout << "    Sua resposta estah correta!\n";
        }
    }
    std::cout << ">>> Seus pontos: " << score << " (de " << total << ").\n\n";

    // ================================================================================
    // Questao 1 - teste:  vetor NÃO está particionado
    // ================================================================================
    {
        std::cout << ">>> Q1-b: testando a funcao eh_particionada()\n";

        int A[] = { 21, 41, 54, 38, 6, 5, 21, 4, 1, -3 };

        // Verificando se o vetor estah particionado com os valores acima de 20 na frente.
        auto result = prova::eh_particionada( std::begin(A), std::end(A), sizeof(int), acima_20 );

        if ( result == true )
        {
            std::cout << "    Sua resposta estah incorreta!\n";
        }
        else
        {
            score += 10;
            std::cout << "    Sua resposta estah correta!\n";
        }
    }
    std::cout << ">>> Seus pontos: " << score << " (de " << total << ").\n\n";

    // ================================================================================
    // Questao 2
    // ================================================================================
    {
        std::cout << ">>> Q2-a: testando a funcao limite_inferior(): limite inferior no meio\n";

        int A[] = { 1, 1, 2, 3, 3, 3, 3, 4, 4, 4, 5, 5, 6 };
        auto target(4);

        // buscando o limite inferior
        auto li = (int *) prova::limite_inferior( std::begin(A), std::end(A), sizeof(int),
                &target, compare_ints );

        if ( *li == 4 and std::distance(std::begin(A), li) == 7 )
        {
            score += 5;
            std::cout << "    Sua resposta estah correta!\n";
        }
        else
        {
            std::cout << "    Sua resposta estah incorreta!\n";
        }
    }
    std::cout << ">>> Seus pontos: " << score << " (de " << total << ").\n\n";


    {
        std::cout << ">>> Q2-b: testando a funcao limite_inferior(): valor ausente mas limite inferior no intervalo\n";

        int A[] = { 1, 1, 2, 3, 3, 3, 3, 3, 3, 3, 5, 5, 6 };
        auto target(4);

        // buscando o limite inferior
        auto li = (int *) prova::limite_inferior( std::begin(A), std::end(A), sizeof(int),
                &target, compare_ints );

        if ( *li == 5 and std::distance(std::begin(A), li) == 10)
        {
            std::cout << "    Sua resposta estah correta!\n";
            score += 5;
        }
        else
        {
            std::cout << "    Sua resposta estah incorreta!\n";
        }
    }
    std::cout << ">>> Seus pontos: " << score << " (de " << total << ").\n\n";


    {
        std::cout << ">>> Q2-c: testando a funcao limite_inferior(): limite inferior fora do intervalo\n";

        int A[] = { 1, 1, 2, 3, 3, 3 };
        auto target(5);

        // buscando o limite inferior
        auto li = (int *) prova::limite_inferior( std::begin(A), std::end(A), sizeof(int),
                &target, compare_ints );

        if ( li == std::end(A) )
        {
            std::cout << "    Sua resposta estah correta!\n";
            score += 5;
        }
        else
        {
            std::cout << "    Sua resposta estah incorreta!\n";
        }
    }
    std::cout << ">>> Seus pontos: " << score << " (de " << total << ").\n\n";


    {
        std::cout << ">>> Q2-d: testando a funcao limite_inferior(): limite inferior no inicio\n";

        int A[] = { 1, 1, 2, 3, 3, 3 };
        auto target(1);

        // buscando o limite inferior
        auto li = (int *) prova::limite_inferior( std::begin(A), std::end(A), sizeof(int),
                &target, compare_ints );

        if ( li == std::begin(A) )
        {
            std::cout << "    Sua resposta estah correta!\n";
            score += 5;
        }
        else
        {
            std::cout << "    Sua resposta estah incorreta!\n";
        }
    }
    std::cout << ">>> Seus pontos: " << score << " (de " << total << ").\n\n";


    {
        std::cout << ">>> Q2-e: testando a funcao limite_superior(): valor presente, limite inferior no meio do vetror.\n";

        int A[] = { 1, 1, 2, 3, 3, 3, 3, 4, 4, 4, 5, 5, 6 };
        auto target(4);

        // buscando o limite inferior
        auto li = (int *) prova::limite_superior( std::begin(A), std::end(A), sizeof(int),
                &target, compare_ints );

        if ( *li == 5 and std::distance(std::begin(A), li) == 10 )
        {
            std::cout << "    Sua resposta estah correta!\n";
            score += 5;
        }
        else
        {
            std::cout << "    Sua resposta estah incorreta!\n";
        }
    }
    std::cout << ">>> Seus pontos: " << score << " (de " << total << ").\n\n";


    {
        std::cout << ">>> Q2-f: testando a funcao limite_superior(): valor ausente, limite superior presente.\n";

        int A[] = { 1, 1, 2, 3, 3, 3, 3, 5, 5, 6 };
        auto target(4);

        // buscando o limite inferior
        auto li = (int *) prova::limite_superior( std::begin(A), std::end(A), sizeof(int),
                &target, compare_ints );

        if ( *li == 5 and std::distance(std::begin(A), li) == 7 )
        {
            std::cout << "    Sua resposta estah correta!\n";
            score += 5;
        }
        else
        {
            std::cout << "    Sua resposta estah incorreta!\n";
        }
    }
    std::cout << ">>> Seus pontos: " << score << " (de " << total << ").\n\n";


    {
        std::cout << ">>> Q2-g: testando a funcao limite_superior(): valor ausente, limite superior fora do intervalo.\n";

        int A[] = { 1, 1, 2, 3, 3, 3, 3, 5, 5, 6 };
        auto target(7);

        // buscando o limite inferior
        auto li = (int *) prova::limite_superior( std::begin(A), std::end(A), sizeof(int),
                &target, compare_ints );

        if ( li == std::end(A) )
        {
            std::cout << "    Sua resposta estah correta!\n";
            score += 5;
        }
        else
        {
            std::cout << "    Sua resposta estah incorreta!\n";
        }
    }
    std::cout << ">>> Seus pontos: " << score << " (de " << total << ").\n\n";


    {
        std::cout << ">>> Q2-h: testando a funcao limite_superior(): valor no inicio\n";

        int A[] = { 1, 1, 2, 3, 3, 3, 3, 5, 5, 6 };
        auto target(1);

        // buscando o limite inferior
        auto li = (int *) prova::limite_superior( std::begin(A), std::end(A), sizeof(int),
                &target, compare_ints );

        if ( *li == 2 and std::distance( std::begin(A), li ) == 2 )
        {
            std::cout << "    Sua resposta estah correta!\n";
            score += 5;
        }
        else
        {
            std::cout << "    Sua resposta estah incorreta!\n";
        }
    }
    std::cout << ">>> Seus pontos: " << score << " (de " << total << ").\n\n";

    {
        std::cout << ">>> Q2-i: testando a funcao limite_superior(): valor menor que início do intervalo.\n";

        int A[] = { 1, 1, 2, 3, 3, 3, 3, 5, 5, 6 };
        auto target(0);

        // buscando o limite inferior
        auto li = (int *) prova::limite_superior( std::begin(A), std::end(A), sizeof(int),
                &target, compare_ints );

        if ( *li == 1 and li == std::begin(A) )
        {
            std::cout << "    Sua resposta estah correta!\n";
            score += 5;
        }
        else
        {
            std::cout << "    Sua resposta estah incorreta!\n";
        }
    }
    std::cout << ">>> Seus pontos: " << score << " (de " << total << ").\n\n";

    // ================================================================================
    // TODO: Inclua aqui seus testes para as questões 3, 4 e 5.
    // ================================================================================
    	std::cout <<"questão 3" << "\n";
    	{
    		int A[] = { 1, 1, 2, 3, 3, 3, 3, 5, 5, 6 };
    		auto li = (int *) prova::remove(std::begin(A),std::end(A) , std::begin(A) , std::end(A) , sizeof(int));
    		std::cout << "[ ";
    		for(auto i = std::begin(A); i<li;++i)
    			std::cout << *i << " ";
    		std::cout << "]";
    	}




    std::cout << "\n\n>>> Normal exiting...\n";

    return EXIT_SUCCESS;

}
