#ifndef PERSONAGEM_H
#define PERSONAGEM_H

#include "inventario.h"

#define CADASTRO_MAX_PERSONAGENS 20
#define PERSONAGEM_NOME_TAMANHO 50

typedef enum {
    RACA_HUMANO = 1,
    RACA_ELFO,
    RACA_ANAO,
    RACA_HALFLING,
    RACA_ORC
} Raca;

typedef enum {
    CLASSE_GUERREIRO = 1,
    CLASSE_LADINO,
    CLASSE_MAGO,
    CLASSE_CLERIGO,
    CLASSE_BARDO
} Classe;

typedef enum {
    SLOT_ELMO = 1,
    SLOT_PEITORAL,
    SLOT_MANOPLAS,
    SLOT_CALCA,
    SLOT_BOTAS,
    SLOT_ANEL,
    SLOT_COLAR,
    SLOT_CINTO,
    SLOT_MAO_DIREITA,
    SLOT_MAO_ESQUERDA
} SlotEquipamento;

typedef enum {
    RESULTADO_OK,
    RESULTADO_CADASTRO_CHEIO,
    RESULTADO_ID_DUPLICADO,
    RESULTADO_NAO_ENCONTRADO,
    RESULTADO_DADOS_INVALIDOS,
    RESULTADO_INVENTARIO_SEM_ESPACO,
    RESULTADO_ITEM_INCOMPATIVEL,
    RESULTADO_ITEM_NAO_ENCONTRADO,
    RESULTADO_CONFLITO_ARMA_DUAS_MAOS
} ResultadoOperacao;

typedef struct {
    Item item;
    int ocupado;
} ItemEquipado;

typedef struct {
    ItemEquipado elmo;
    ItemEquipado peitoral;
    ItemEquipado manoplas;
    ItemEquipado calca;
    ItemEquipado botas;
    ItemEquipado anel;
    ItemEquipado colar;
    ItemEquipado cinto;
    ItemEquipado mao_direita;
    ItemEquipado mao_esquerda;
    int arma_duas_maos_equipada;
} Equipamentos;

typedef struct {
    int ataque;
    int defesa;
    int iniciativa;
    int pontos_vida_maximos;
    int poder;
} AtributosTotais;

typedef struct {
    int id;
    char nome[PERSONAGEM_NOME_TAMANHO];
    Raca raca;
    Classe classe;
    int nivel;
    int pontos_vida_maximos;
    int pontos_vida_atuais;
    int ataque;
    int defesa;
    int iniciativa;
    int poder;
    Inventario inventario;
    Equipamentos equipamentos;
} Personagem;

typedef struct {
    Personagem personagens[CADASTRO_MAX_PERSONAGENS];
    int quantidade;
} CadastroPersonagens;

void cadastro_inicializar(CadastroPersonagens *cadastro);
int cadastro_obter_quantidade(const CadastroPersonagens *cadastro);
int cadastro_buscar_indice_por_id(const CadastroPersonagens *cadastro, int id_personagem);
Personagem *cadastro_buscar_por_id(CadastroPersonagens *cadastro, int id_personagem);
const Personagem *cadastro_buscar_por_id_const(const CadastroPersonagens *cadastro, int id_personagem);
ResultadoOperacao cadastro_cadastrar(CadastroPersonagens *cadastro, Personagem personagem);
ResultadoOperacao cadastro_alterar(CadastroPersonagens *cadastro, int id_atual, Personagem novos_dados);
ResultadoOperacao cadastro_remover(CadastroPersonagens *cadastro, int id_personagem);
void cadastro_listar(const CadastroPersonagens *cadastro);

Personagem personagem_criar_ficha_basica(int id, const char *nome, Raca raca, Classe classe,
                                         int nivel, int pv_maximos, int pv_atuais,
                                         int ataque, int defesa, int iniciativa, int poder);
int personagem_validar_dados_basicos(const Personagem *personagem);
ResultadoOperacao personagem_adicionar_item(Personagem *personagem, Item item);
ResultadoOperacao personagem_remover_item(Personagem *personagem, int id_item, Item *item_removido);
ResultadoOperacao personagem_equipar_item(Personagem *personagem, int id_item, SlotEquipamento slot);
ResultadoOperacao personagem_desequipar_item(Personagem *personagem, SlotEquipamento slot);
AtributosTotais personagem_calcular_atributos_totais(const Personagem *personagem);
void personagem_listar_inventario(const Personagem *personagem);
void personagem_exibir(const Personagem *personagem);
void personagem_exibir_equipamentos(const Personagem *personagem);
void personagem_exibir_atributos_totais(const Personagem *personagem);

const char *raca_para_texto(Raca raca);
const char *classe_para_texto(Classe classe);
const char *slot_para_texto(SlotEquipamento slot);
const char *resultado_operacao_para_texto(ResultadoOperacao resultado);
int raca_eh_valida(Raca raca);
int classe_eh_valida(Classe classe);
int slot_eh_valido(SlotEquipamento slot);

#endif
