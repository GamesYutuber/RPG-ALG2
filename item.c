#include "item.h"

#include <string.h>

int tipo_item_eh_valido(TipoItem tipo) {
    return tipo >= TIPO_ITEM_ELMO && tipo <= TIPO_ITEM_ARMA_DUAS_MAOS;
}

const char *tipo_item_para_texto(TipoItem tipo) {
    switch (tipo) {
        case TIPO_ITEM_ELMO: return "Elmo";
        case TIPO_ITEM_PEITORAL: return "Peitoral";
        case TIPO_ITEM_MANOPLAS: return "Manoplas";
        case TIPO_ITEM_CALCA: return "Calca";
        case TIPO_ITEM_BOTAS: return "Botas";
        case TIPO_ITEM_ANEL: return "Anel";
        case TIPO_ITEM_COLAR: return "Colar";
        case TIPO_ITEM_CINTO: return "Cinto";
        case TIPO_ITEM_ARMA_UMA_MAO: return "Arma de uma mao";
        case TIPO_ITEM_ARMA_DUAS_MAOS: return "Arma de duas maos";
        default: return "Tipo desconhecido";
    }
}

int item_validar(const Item *item) {
    if (item == 0) {
        return 0;
    }

    return item->id > 0
        && item->nome[0] != '\0'
        && strlen(item->nome) < ITEM_NOME_TAMANHO
        && tipo_item_eh_valido(item->tipo)
        && item->espacos >= 1
        && item->espacos <= 50
        && item->poder >= 0;
}
