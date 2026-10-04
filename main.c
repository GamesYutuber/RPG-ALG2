#include "personagem.h"

#include <stdio.h>
#include <string.h>

static void limpar_entrada(void) {
    int caractere;
    while ((caractere = getchar()) != '\n' && caractere != EOF) {
    }
}

static int ler_inteiro(const char *mensagem) {
    int valor;
    int lidos;

    do {
        printf("%s", mensagem);
        lidos = scanf("%d", &valor);
        if (lidos == EOF) {
            printf("\nEntrada encerrada.\n");
            return 0;
        }
        limpar_entrada();
        if (lidos != 1) {
            printf("Entrada invalida. Digite um numero inteiro.\n");
        }
    } while (lidos != 1);

    return valor;
}

static void ler_texto(const char *mensagem, char destino[], int tamanho) {
    size_t tamanho_lido;

    printf("%s", mensagem);
    if (fgets(destino, tamanho, stdin) == 0) {
        destino[0] = '\0';
        return;
    }

    tamanho_lido = strlen(destino);
    if (tamanho_lido > 0 && destino[tamanho_lido - 1] == '\n') {
        destino[tamanho_lido - 1] = '\0';
    } else {
        limpar_entrada();
    }
}

static void exibir_opcoes_raca(void) {
    printf("Racas: 1-Humano 2-Elfo 3-Anao 4-Halfling 5-Orc\n");
}

static void exibir_opcoes_classe(void) {
    printf("Classes: 1-Guerreiro 2-Ladino 3-Mago 4-Clerigo 5-Bardo\n");
}

static void exibir_opcoes_tipo_item(void) {
    printf("Tipos de item:\n");
    printf("1-Elmo 2-Peitoral 3-Manoplas 4-Calca 5-Botas 6-Anel 7-Colar 8-Cinto 9-Arma uma mao 10-Arma duas maos\n");
}

static void exibir_opcoes_slot(void) {
    printf("Slots: 1-Elmo 2-Peitoral 3-Manoplas 4-Calca 5-Botas 6-Anel 7-Colar 8-Cinto 9-Mao direita 10-Mao esquerda\n");
}

static Personagem ler_personagem(void) {
    int id;
    char nome[PERSONAGEM_NOME_TAMANHO];
    Raca raca;
    Classe classe;
    int nivel;
    int pv_maximos;
    int pv_atuais;
    int ataque;
    int defesa;
    int iniciativa;
    int poder;

    id = ler_inteiro("ID do personagem: ");
    ler_texto("Nome: ", nome, PERSONAGEM_NOME_TAMANHO);
    exibir_opcoes_raca();
    raca = (Raca)ler_inteiro("Raca: ");
    exibir_opcoes_classe();
    classe = (Classe)ler_inteiro("Classe: ");
    nivel = ler_inteiro("Nivel (1 a 20): ");
    pv_maximos = ler_inteiro("PV maximos (1 a 999): ");
    pv_atuais = ler_inteiro("PV atuais (0 ate PV maximos): ");
    ataque = ler_inteiro("Ataque (0 a 30): ");
    defesa = ler_inteiro("Defesa (1 a 30): ");
    iniciativa = ler_inteiro("Iniciativa (-5 a 20): ");
    poder = ler_inteiro("Poder (1 a 100): ");

    return personagem_criar_ficha_basica(id, nome, raca, classe, nivel, pv_maximos,
                                         pv_atuais, ataque, defesa, iniciativa, poder);
}

static Item ler_item(void) {
    Item item;

    memset(&item, 0, sizeof(item));
    item.id = ler_inteiro("ID do item: ");
    ler_texto("Nome do item: ", item.nome, ITEM_NOME_TAMANHO);
    exibir_opcoes_tipo_item();
    item.tipo = (TipoItem)ler_inteiro("Tipo: ");
    item.espacos = ler_inteiro("Espacos consumidos (1 a 50): ");
    item.bonus_ataque = ler_inteiro("Bonus de ataque: ");
    item.bonus_defesa = ler_inteiro("Bonus de defesa: ");
    item.bonus_vida = ler_inteiro("Bonus de vida: ");
    item.bonus_iniciativa = ler_inteiro("Bonus de iniciativa: ");
    item.poder = ler_inteiro("Poder do item (0 ou maior): ");

    return item;
}

static Personagem *selecionar_personagem(CadastroPersonagens *cadastro) {
    int id = ler_inteiro("ID do personagem: ");
    Personagem *personagem = cadastro_buscar_por_id(cadastro, id);

    if (personagem == 0) {
        printf("%s\n", resultado_operacao_para_texto(RESULTADO_NAO_ENCONTRADO));
    }

    return personagem;
}

static void administrar_inventario(CadastroPersonagens *cadastro) {
    Personagem *personagem = selecionar_personagem(cadastro);
    int opcao;

    if (personagem == 0) {
        return;
    }

    do {
        printf("\nInventario de %s\n", personagem->nome);
        printf("1 - Adicionar item\n");
        printf("2 - Buscar item por ID\n");
        printf("3 - Remover item\n");
        printf("4 - Listar inventario\n");
        printf("5 - Informar ocupacao\n");
        printf("0 - Voltar\n");
        opcao = ler_inteiro("Opcao: ");

        if (opcao == 1) {
            Item item = ler_item();
            ResultadoOperacao resultado = personagem_adicionar_item(personagem, item);
            printf("%s\n", resultado_operacao_para_texto(resultado));
        } else if (opcao == 2) {
            int id_item = ler_inteiro("ID do item: ");
            const Item *item = inventario_buscar_item_por_id(&personagem->inventario, id_item);
            if (item == 0) {
                printf("%s\n", resultado_operacao_para_texto(RESULTADO_ITEM_NAO_ENCONTRADO));
            } else {
                printf("ID %d | %s | %s | espacos %d\n",
                       item->id, item->nome, tipo_item_para_texto(item->tipo), item->espacos);
            }
        } else if (opcao == 3) {
            int id_item = ler_inteiro("ID do item: ");
            ResultadoOperacao resultado = personagem_remover_item(personagem, id_item, 0);
            printf("%s\n", resultado_operacao_para_texto(resultado));
        } else if (opcao == 4) {
            personagem_listar_inventario(personagem);
        } else if (opcao == 5) {
            printf("Ocupacao atual: %d/%d\n",
                   inventario_obter_ocupacao(&personagem->inventario),
                   INVENTARIO_MAX_ESPACOS);
        } else if (opcao != 0) {
            printf("Opcao invalida.\n");
        }
    } while (opcao != 0);
}

static void exibir_menu_principal(void) {
    printf("\n=== Sistema Auxiliar de Mestre de RPG ===\n");
    printf("1 - Cadastrar personagem\n");
    printf("2 - Consultar personagem por ID\n");
    printf("3 - Alterar personagem\n");
    printf("4 - Remover personagem\n");
    printf("5 - Listar personagens\n");
    printf("6 - Administrar inventario\n");
    printf("7 - Consultar equipamentos\n");
    printf("8 - Equipar item\n");
    printf("9 - Desequipar item\n");
    printf("10 - Exibir atributos totais\n");
    printf("0 - Encerrar\n");
}

int main(void) {
    CadastroPersonagens cadastro;
    int opcao;

    cadastro_inicializar(&cadastro);

    do {
        exibir_menu_principal();
        opcao = ler_inteiro("Opcao: ");

        if (opcao == 1) {
            Personagem personagem = ler_personagem();
            ResultadoOperacao resultado = cadastro_cadastrar(&cadastro, personagem);
            printf("%s\n", resultado_operacao_para_texto(resultado));
        } else if (opcao == 2) {
            Personagem *personagem = selecionar_personagem(&cadastro);
            if (personagem != 0) {
                personagem_exibir(personagem);
            }
        } else if (opcao == 3) {
            int id_atual = ler_inteiro("ID atual do personagem: ");
            Personagem novos_dados = ler_personagem();
            ResultadoOperacao resultado = cadastro_alterar(&cadastro, id_atual, novos_dados);
            printf("%s\n", resultado_operacao_para_texto(resultado));
        } else if (opcao == 4) {
            int id = ler_inteiro("ID do personagem a remover: ");
            ResultadoOperacao resultado = cadastro_remover(&cadastro, id);
            printf("%s\n", resultado_operacao_para_texto(resultado));
        } else if (opcao == 5) {
            cadastro_listar(&cadastro);
            printf("Total: %d personagem(ns).\n", cadastro_obter_quantidade(&cadastro));
        } else if (opcao == 6) {
            administrar_inventario(&cadastro);
        } else if (opcao == 7) {
            Personagem *personagem = selecionar_personagem(&cadastro);
            if (personagem != 0) {
                personagem_exibir_equipamentos(personagem);
            }
        } else if (opcao == 8) {
            Personagem *personagem = selecionar_personagem(&cadastro);
            if (personagem != 0) {
                int id_item = ler_inteiro("ID do item no inventario: ");
                SlotEquipamento slot;
                exibir_opcoes_slot();
                slot = (SlotEquipamento)ler_inteiro("Slot de destino: ");
                printf("%s\n", resultado_operacao_para_texto(personagem_equipar_item(personagem, id_item, slot)));
            }
        } else if (opcao == 9) {
            Personagem *personagem = selecionar_personagem(&cadastro);
            if (personagem != 0) {
                SlotEquipamento slot;
                exibir_opcoes_slot();
                slot = (SlotEquipamento)ler_inteiro("Slot a desequipar: ");
                printf("%s\n", resultado_operacao_para_texto(personagem_desequipar_item(personagem, slot)));
            }
        } else if (opcao == 10) {
            Personagem *personagem = selecionar_personagem(&cadastro);
            if (personagem != 0) {
                personagem_exibir_atributos_totais(personagem);
            }
        } else if (opcao != 0) {
            printf("Opcao invalida.\n");
        }
    } while (opcao != 0);

    printf("Programa encerrado.\n");
    return 0;
}
