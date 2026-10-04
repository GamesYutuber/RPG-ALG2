#ifndef INVENTARIO_H
#define INVENTARIO_H

#include "item.h"

#define INVENTARIO_MAX_ITENS 50
#define INVENTARIO_MAX_ESPACOS 50

typedef enum {
    INVENTARIO_OK,
    INVENTARIO_CHEIO,
    INVENTARIO_ID_DUPLICADO,
    INVENTARIO_ITEM_NAO_ENCONTRADO,
    INVENTARIO_SEM_ESPACO,
    INVENTARIO_DADOS_INVALIDOS
} ResultadoInventario;

typedef struct {
    Item itens[INVENTARIO_MAX_ITENS];
    int quantidade;
} Inventario;

void inventario_inicializar(Inventario *inventario);
int inventario_obter_ocupacao(const Inventario *inventario);
int inventario_obter_espacos_livres(const Inventario *inventario);
int inventario_buscar_indice_por_id(const Inventario *inventario, int id_item);
const Item *inventario_buscar_item_por_id(const Inventario *inventario, int id_item);
ResultadoInventario inventario_adicionar_item(Inventario *inventario, Item item);
ResultadoInventario inventario_remover_item(Inventario *inventario, int id_item, Item *item_removido);
void inventario_listar(const Inventario *inventario);
const char *resultado_inventario_para_texto(ResultadoInventario resultado);

#endif
