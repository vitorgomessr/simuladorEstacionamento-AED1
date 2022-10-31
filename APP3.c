#include <stdio.h>
#include <time.h>
#include "TAD3.h"
#include <string.h>
#include <stdlib.h>


#define QNT 3

int gera_entrada()
{
    int horario_entrada;
    int X;

    setbuf(stdin, NULL);
    struct tm *data_hora_atual;
    time_t segundos;
    time(&segundos);
    data_hora_atual = localtime(&segundos);
    printf("\nHora chegada: %d:",data_hora_atual->tm_hour);
    printf("%d\n",data_hora_atual->tm_min);

    int M, H;
    H = data_hora_atual->tm_hour;
    M = data_hora_atual->tm_min;

    H = H * 60;

    horario_entrada = H + M;

    X = horario_entrada;

    return X;
}


void LeString (char * Placa)
{

    int i = 0;
    for (i = 0; i < 10; i++)
    {
        scanf("%c", &Placa[i]);

        if(Placa[i]=='\n')
        {
            break;
        }

    }

    Placa[i] = '\0';

}

void sai_veiculo(Fila box[], struct carros * achar)
{
    int tempo_saida = achar->horario_saida;
    int tempo_entrada = achar->horario_entrada;

    int horaent = tempo_entrada /60;
    int minent = tempo_entrada %60;
    int hora = tempo_saida / 60;
    int min = tempo_saida % 60;

    float total;

    int diferenca = achar->horario_saida - achar->horario_entrada;

    int horadif = diferenca/60;
    int mindif = diferenca%60;

    if(achar->servico == 'M')
    {
        printf("Plano mensal confirmado. Obrigado pela preferência!\n");
    }
    else
    {
        printf("horario de entrada:%d:%d\n", horaent, minent);
        printf("horário de saida: %d:%d\n",hora,min);
        printf("diferença: %d:%d\n", horadif,mindif);

        if(mindif > 15)
        {
            horadif = horadif + 1;
            printf("Tolerância de 15 min ultrapassada! Será cobrado uma hora a mais!\n");
        }


        if(horadif < 1)
        {
            printf("Não teve uma hora de estacionamento! Mesmo assim ficou R$5,00. De graca não fica rs\n");
        }
        else if( horadif == 1)
        {
            printf("Uma hora de estacionamento. R$5,00\n");
        }
        else if(horadif > 1)
        {

            total = 5 + 2*(horadif-1);
            printf("Valor a ser pago é: R$%2.f\n", total);
        }
    }


}




void print_estacionamento(Fila box)
{
    struct carros printa;
    Fila aux = cria_fila();

    while(fila_vazia(box)== 0)
    {
        remove_ini(box, &printa);
        printf("Placa do carro: %s\n", printa.placa);
        insere_fim(aux, printa);
    }

    while(fila_vazia(aux) == 0)
    {
        remove_ini(aux, &printa);
        insere_fim(box, printa);
    }

    apaga_fila(&aux);

}

void entra_veiculo(Fila box)
{
    struct carros C;


    printf("Digite a placa do seu veiculo: \n");
    scanf("%s", C.placa);
    setbuf(stdin, NULL);

    printf("Digite o tipo de servico, sendo: 'A' para avulso e 'M' para mensal\n");
    scanf("%c", &C.servico);
    setbuf(stdin, NULL);

    int horario_ent = gera_entrada();

    C.horario_entrada = horario_ent;  //em min

    if(insere_fim(box, C) == 1)
    {
        printf("Carro guardado com sucesso!\n");

    }
    else
    {
        printf("Não foi possivel guardar seu carro.\n");
    }

}



int simula_HoraSaida(Fila box[], struct carros * achar)
{

    int Y = achar->horario_entrada;
    int sort_min, sort_hr;

    srand(time(NULL));
    sort_min = rand() % 59;
    srand(time(NULL));
    sort_hr = rand() % 10;

    sort_hr = sort_hr * 60;

    Y = Y + sort_min + sort_hr;

    return Y;
}

int
main()
{
    int  horario_entrada, menor;
    Fila box[3];
    int i, op;

    for(i=0; i< QNT; i++)
    {
        box[i] = cria_fila();
        if(box[i] == NULL)
        {
            printf("Não foi possivel criar o box %d", i+1);
        }
        else
        {
            printf("Fila %d criada\n", i+1);
        }
    }

    do
    {
        printf("\n---------------- BEM-VINDO AO ESTACIONAMENTO AED1--------------\n\n");

        printf("Escolha uma opcao: \n");
        printf("[1] ENTRAR COM O VEICULO\n");
        printf("[2] SAIR COM O VEICULO\n");
        printf("[3] VISUALIZAR ESTACIONAMENTO\n");
        printf("[4] SAIR DO PROGRAMA\n");

        printf("Digite a sua opcao: ");
        scanf("%d", &op);


        if(op < 1 || op > 4)
        {
            printf("Digite um comando correto, por gentileza!");
        }

        if(op == 1)
        {
            menor = 0;


            for(i=0; i< QNT; i++)
            {
                if(fila_vazia(box[i]) == 1)
                {
                    menor = i;

                    break;
                }

                if(fila_cheia(box[i]) == 0)
                {
                    if(tamanho(box[i]) < tamanho(box[menor]))
                    {
                        menor = i;

                    }


                }
            }

            printf("Seu veiculo será estacionado no box %d\n", menor+1);
            entra_veiculo(box[menor]);

        }

        else if (op == 2)
        {
            struct carros achar;
            char remove[20];
            int X, Y;
            int j;
            int i;

            setbuf(stdin, NULL);
            printf("Digite a placa a ser retirada: \n");

            LeString(remove);

            setbuf(stdin, NULL);
            printf("\nProcurando placa:%s\n", remove);

            for(i=0; i < QNT; i++)
            {
                for(j=0; j<tamanho(box[i]); j++)
                {

                    remove_ini(box[i], &achar);

                    if(strcmp(remove, achar.placa) == 0)
                    {
                        printf("o veiculo de placa: %s foi encontrada e removida do box %d\n", remove, i+1);
                        achar.horario_saida = simula_HoraSaida(box, &achar);

                        sai_veiculo(box, &achar);
                        break;
                    }
                    else
                    {
                        insere_fim(box[i], achar);

                    }
                }
            }
        }

        else if(op == 3)
        {

            for(i=0; i< QNT; i++)
            {
                if(fila_vazia(box[i]) == 1)
                {
                    printf("\nbox %d esta vazio\n", i+1);
                }
                else
                {
                    printf("box %d: \n", i+1);
                    print_estacionamento(box[i]);
                }

            }
        }


    } while (op != 4);




    for(i=0; i< QNT; i++)
    {
        apaga_fila(&box[i]);
    }

    printf("Obrigado pela confianca. Até a próxima!.\n");

    return 0;

}
