

typedef struct fila * Fila;

struct carros
{
    char placa[10];
    char servico;
    float horario_entrada;
    float horario_saida;
};

Fila cria_fila();
int fila_vazia(Fila F);
int fila_cheia(Fila F);
int insere_fim(Fila F, struct carros C);
int remove_ini(Fila F, struct carros * C);
int tamanho(Fila F);
int apaga_fila(Fila* F);