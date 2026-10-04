#ifndef ITEM_H
#define ITEM_H

#define ITEM_NOME_TAMANHO 50

typedef enum {
    TIPO_ITEM_ELMO = 1,
    TIPO_ITEM_PEITORAL,
    TIPO_ITEM_MANOPLAS,
    TIPO_ITEM_CALCA,
    TIPO_ITEM_BOTAS,
    TIPO_ITEM_ANEL,
    TIPO_ITEM_COLAR,
    TIPO_ITEM_CINTO,
    TIPO_ITEM_ARMA_UMA_MAO,
    TIPO_ITEM_ARMA_DUAS_MAOS
} TipoItem;

typedef struct {
    int id;
    char nome[ITEM_NOME_TAMANHO];
    TipoItem tipo;
    int espacos;
    int bonus_ataque;
    int bonus_defesa;
    int bonus_vida;
    int bonus_iniciativa;
    int poder;
} Item;

int item_validar(const Item *item);
const char *tipo_item_para_texto(TipoItem tipo);
int tipo_item_eh_valido(TipoItem tipo);

#endif
