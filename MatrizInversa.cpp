/*
 * Matriz_Inversa.cpp
 *
 * Copyright 2014 Rafael Andrade <rafaelsandrade@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 * 16/10/2011
 * Calcula a matriz inversa
 */


#include <cstdio>
#include <cstdlib>

////    Calcula a Inversa da matriz
void MatrizInversa( double *r, const double *m, int ordem)
{
    double *inv = new double[ordem * ordem];
    double *temp = new double[ordem * ordem];

    if (!inv || !temp)
    {
        printf("\n\nERRO: falha na alocação de memoria\n\n");
        exit(1);
    }

    // Copia para 'temp' o conteúdo de 'm'
    for( int i = 0; i < ordem * ordem; i++ )
    {
        temp[ i ] = m[ i ];
    }

    // Transforma 'inv' na matriz identidade
    int j = 0;

    for( int i = 0; i < ordem * ordem; i++ )
    {
        if( i == (j * (ordem + 1)) )
        {
            inv[i] = 1.0;
            j++;
        }
        else inv[i] = 0.0;
    }

    //////  Escalona a parte inferior
    j = 0;
    double pivo;

    for ( int i = 0; i < ordem; i++ )
    {
        if ( temp[ i * ( ordem + 1 ) ] == 0.0 ) /// Verifica se o pivo é nulo
        {
            for ( j = i + 1; j < ordem; j++ )   /// Procura o valor não nulo abaixo do pivo
            {
                if ( temp[ i + j * ordem ] != 0.0 )
                {
                    for ( int k = 0; k < ordem; k++ )
                    {
                        /// Soma a linha do pivo nulo com a linha abaixo
                        temp[ k + i * ordem ] += temp[ k + j * ordem ];
                        inv[ k + i * ordem ] += inv[ k + j * ordem ];
                    }
                    break;
                }
            }

            if ( j == ordem )   /// Se não achar retorna matriz nula
            {
                delete[] temp;
                delete[] inv;
                printf("\n\nERRO: Matriz nao possui inversa\n\n");
                return;
            }
        }

        for ( j = i + 1; j < ordem; j++ )   /// Zera os elementos abaixo do pivô
        {
            if ( temp[ i + j * ordem ] != 0.0 ) /// Ignora se elemento é nulo
            {
                pivo = temp[ i + j * ordem ] / temp[ i * ( ordem + 1 ) ];
                for( int k = 0; k < ordem; k++ )
                {
                    temp[ k + j * ordem ] -= temp[ k + i * ordem ] * pivo;
                    inv[ k + j * ordem ] -= inv[ k + i * ordem ] * pivo;
                }
            }
        }
    }

    //////// Escalona a parte superior
    for( int i = ordem - 1; i >= 0; i-- )
    {
        for( j = i - 1; j >= 0; j-- )   /// Zera os elementos abaixo do pivô
        {
            if( temp[ i + j * ordem ] != 0.0 )  /// Ignora se elemento é nulo
            {
                pivo = temp[ i + j * ordem ] / temp[ i * ( ordem + 1 ) ];
                for( int k = ordem - 1; k >= 0; k-- )
                {
                    temp[ k + j * ordem ] -= temp[ k + i * ordem ] * pivo;
                    inv[ k + j * ordem ] -= inv[ k + i * ordem ] * pivo;
                }
            }
        }
    }

    //////// Transformando os elementos da coluna principal de 'temp' em '1'
    for( int i = 0; i < ordem; i++ )
    {
        pivo = temp[ i * ( ordem + 1 ) ];
        for( j = 0; j < ordem; j++ )
        {
            temp[ j + i * ordem ] /= pivo;
            inv[ j + i * ordem ] /= pivo;
        }
    }

    // Copia os elementos de 'inv' para 'r'
    for ( int i = 0; i < ordem * ordem; i++ )
    {
        r[i] = inv[i];
    }

    delete[] inv;
    delete[] temp;
}

int main(int argc, char **argv)
{
    double M[9], A[9] = {    -1, 5, -7, // Matriz de ordem 3 a ser invertida
                              3, -2, 3,
                             -2, 3, 7      };

    // Exibe a matriz A
    printf("A = ");
    for (int i = 0; i < 9; i++)
    {
        if( i % 3 == 0) printf("\n");
        printf("%13G", A[i]);

    }

    MatrizInversa(M, A, 3);

    // Exibe a matriz inversa de A
    printf ("\n\n\n  -1\n(A) =");
    for (int i = 0; i < 9; i++)
    {
        if( i % 3 == 0) printf("\n");
        printf("%13G", M[i]);

    }

    return 0;
}
