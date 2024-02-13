#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_TABULEIRO 20

typedef struct
{
    int x;
    int y;
} Posicao;

void imprimir_tabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], Posicao cobra[], int comprimento);

void moverCobra(Posicao cobra[], int comprimento, char direcao);

int verificarColisao(Posicao cobra[], int comprimento);

int comeu(Posicao cobra[], int x, int y);

int main()
{

    int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO];
    int i, j, x, y;

    for (i = 0; i < TAM_TABULEIRO; i++)
    {
        for (j = 0; j < TAM_TABULEIRO; j++)
            tabuleiro[i][j] = 0;
    }

    Posicao cobra[TAM_TABULEIRO * TAM_TABULEIRO];
    cobra[0].x = 0;
    cobra[0].y = 0;
    int comprimentoCobra = 1;

    int comida = 0;

    char direcao = 'd';

    while (direcao != 'x')
    {
        // tentando criar a comida no tabuleiro
        while (comida == 0)
        {
            srand(time(NULL));
            x = rand() % TAM_TABULEIRO;
            y = rand() % TAM_TABULEIRO;

            // checando se a comida vai ser criada em algum lugar fora da zona ocupada pelo corpo da cobra
            i = 0;
            while (i < comprimentoCobra)
            {
                // se a comida for criada emcima de alguma parte da cobra, geramos uma nova posição para a comida e checamos toda a cobra novamente para garantir que a comida aparece em outro lugar que não seja em cima da cobra
                if (cobra[i].x == x && cobra[i].y == y)
                {
                    //-1 que somando com ++ vai para zero
                    i = -1;
                    x = rand() % TAM_TABULEIRO;
                    y = rand() % TAM_TABULEIRO;
                }
                i++;
            }
            comida = 1;
        }

        tabuleiro[x][y] = 1;
        imprimir_tabuleiro(tabuleiro, cobra, comprimentoCobra);

        printf("\n\nSua jogada [w,a,s,d]: ");
        setbuf(stdin, NULL);
        scanf("%c", &direcao);

        moverCobra(cobra, comprimentoCobra, direcao);

        if (comeu(cobra, x, y))
        {
            printf("\nFaze concluida com sucesso!\n");
            comprimentoCobra++;
            comida = 0;
            tabuleiro[x][y] = 0;
        }

        if (verificarColisao(cobra, comprimentoCobra))
        {
            printf("\nGame Over - Cobra Colidiu\n");
            direcao = 'x';
        }
    }
    return 0;
}

void imprimir_tabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], Posicao cobra[], int comprimento)
{
    printf("Pontuacao: %d\n", comprimento - 1);

    int i, j, k;
    // Paredes superiores e inferiores
    for (j = 0; j < TAM_TABULEIRO + 2; j++)
        printf("_ ");

    printf("\n");

    for (i = 0; i < TAM_TABULEIRO; i++)
    {
        printf("| "); // Parede esquerda
        for (j = 0; j < TAM_TABULEIRO; j++)
        {
            if (tabuleiro[i][j] == 1)
                printf("F "); // Representação da comida
            else
            {
                int eCobra = 0;
                for (k = 0; k < comprimento; k++)
                {
                    if (cobra[k].x == i && cobra[k].y == j)
                    {
                        if (k == 0)
                            printf("@ "); // Cabeça da cobra
                        else
                            printf("* "); // Corpo da cobra
                        eCobra = 1;
                        break;
                    }
                }
                if (!eCobra)
                    printf(". "); // Espaço
            }
        }
        printf("|\n"); // Parede direita
    }

    // Parede inferior
    for (j = 0; j < TAM_TABULEIRO + 2; j++)
        printf("- ");

    printf("\n");
}
void moverCobra(Posicao cobra[], int comprimento, char direcao)
{
    int i;

    if (direcao != 'w' && direcao != 's' && direcao != 'a' && direcao != 'd')
    {
        printf("Opcao invalida\n");
    }
    else
    {
        for (i = comprimento - 1; i > 0; i--)
            cobra[i] = cobra[i - 1];

        switch (direcao)
        {
            case 'w':
                cobra[0].x--;
                break;
            case 's':
                cobra[0].x++;
                break;
            case 'a':
                cobra[0].y--;
                break;
            case 'd':
                cobra[0].y++;
                break;
            default:
                printf("opcao invalida\n");
                break;
            }
        }
}

int verificarColisao(Posicao cobra[], int comprimento)
{
    int colidiu = 0;

    if (cobra[0].x < 0 || cobra[0].x >= TAM_TABULEIRO || cobra[0].y < 0 || cobra[0].y >= TAM_TABULEIRO)
        colidiu = 1;

    for (int i = 1; i < comprimento; i++)
    {
        if (cobra[0].x == cobra[i].x && cobra[0].y == cobra[i].y)
            colidiu = 1;
    }

    return colidiu;
}

int comeu(Posicao cobra[], int x, int y)
{
    int resultado = 0;
    if (cobra[0].x == x && cobra[0].y == y)
    {
        resultado = 1;
    }

    return resultado;
}
