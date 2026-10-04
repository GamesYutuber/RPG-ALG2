#include "inventario.h"

#include <stdio.h>

void inventario_inicializar(Inventario *inventario) {
    if (inventario != 0) {
        inventario->quantidade = 0;
    }
}

int inventario_obter_ocupacao(const Inventario *inventario) {
    int ocupacao = 0;
    int i;

    if (inventario == 0) {
        return 0;
    }

    for (i = 0; i < inventario->quantidade; i++) {
        ocupacao += inventario->itens[i].espacos;
    }

    return ocupacao;
}

int inventario_obter_espacos_livres(const Inventario *inventario) {
    return INVENTARIO_MAX_ESPACOS - inventario_obter_ocupacao(inventario);
}

int inventario_buscar_indice_por_id(const Inventario *inventario, int id_item) {
    int i;

    if (inventario == 0) {
        return -1;
    }

    for (i = 0; i < inventario->quantidade; i++) {
        if (inventario->itens[i].id == id_item) {
            return i;
        }
    }

    return -1;
}

const Item *inventario_buscar_item_por_id(const Inventario *inventario, int id_item) {
    int indice = inventario_buscar_indice_por_id(inventario, id_item);
    if (indice < 0) {
        return 0;
    }

    return &inventario->itens[indice];
}

ResultadoInventario inventario_adicionar_item(Inventario *inventario, Item item) {
    if (inventario == 0 || !item_validar(&item)) {
        return INVENTARIO_DADOS_INVALIDOS;
    }

    if (inventario->quantidade >= INVENTARIO_MAX_ITENS) {
        return INVENTARIO_CHEIO;
    }

    if (inventario_buscar_indice_por_id(inventario, item.id) >= 0) {
        return INVENTARIO_ID_DUPLICADO;
    }

    if (inventario_obter_ocupacao(inventario) + item.espacos > INVENTARIO_MAX_ESPACOS) {
        return INVENTARIO_SEM_ESPACO;
    }

    inventario->itens[inventario->quantidade] = item;
    inventario->quantidade++;
    return INVENTARIO_OK;
}

ResultadoInventario inventario_remover_item(Inventario *inventario, int id_item, Item *item_removido) {
    int indice;
    int i;

    if (inventario == 0 || id_item <= 0) {
        return INVENTARIO_DADOS_INVALIDOS;
    }

    indice = inventario_buscar_indice_por_id(inventario, id_item);
    if (indice < 0) {
        return INVENTARIO_ITEM_NAO_ENCONTRADO;
    }

    if (item_removido != 0) {
        *item_removido = inventario->itens[indice];
    }

    for (i = indice; i < inventario->quantidade - 1; i++) {
        inventario->itens[i] = inventario->itens[i + 1];
    }

    inventario->quantidade--;
    return INVENTARIO_OK;
}

void inventario_listar(const Inventario *inventario) {
    int i;

    if (inventario == 0) {
        printf("Inventario indisponivel.\n");
        return;
    }

    printf("Itens no inventario: %d\n", inventario->quantidade);
    printf("Espacos ocupados: %d/%d | Livres: %d\n",
           inventario_obter_ocupacao(inventario),
           INVENTARIO_MAX_ESPACOS,
           inventario_obter_espacos_livres(inventario));

    if (inventario->quantidade == 0) {
        printf("Nenhum item guardado.\n");
        return;
    }

    for (i = 0; i < inventario->quantidade; i++) {
        const Item *item = &inventario->itens[i];
        printf("ID %d | %s | %s | espacos %d | atk %+d def %+d vida %+d ini %+d poder %d\n",
               item->id,
               item->nome,
               tipo_item_para_texto(item->tipo),
               item->espacos,
               item->bonus_ataque,
               item->bonus_defesa,
               item->bonus_vida,
               item->bonus_iniciativa,
               item->poder);
    }
}

const char *resultado_inventario_para_texto(ResultadoInventario resultado) {
    switch (resultado) {
        case INVENTARIO_OK: return "Operacao realizada com sucesso.";
        case INVENTARIO_CHEIO: return "Inventario sem posicoes livres.";
        case INVENTARIO_ID_DUPLICADO: return "Ja existe um item com esse ID no personagem.";
        case INVENTARIO_ITEM_NAO_ENCONTRADO: return "Item nao encontrado.";
        case INVENTARIO_SEM_ESPACO: return "Inventario sem espaco suficiente.";
        case INVENTARIO_DADOS_INVALIDOS: return "Dados do item invalidos.";
        default: return "Resultado desconhecido.";
    }
}
