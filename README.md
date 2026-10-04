Sistema Auxiliar de Mestre de RPG - Mini-Tarefa 1

Identificacao da equipe
Mathias Silva Cunha (Unico)

Resumo da etapa atual
Esta entrega implementa o modulo de cadastro de personagens em memoria para a Mini-Tarefa 1. O sistema permite cadastrar, consultar, alterar, remover e listar fichas, alem de administrar inventario, equipamentos, armas e atributos totais calculados a partir dos itens equipados.

Estrutura do projeto
- item.h / item.c: definem o tipo Item, TipoItem, validacao e nomes textuais dos tipos.
- inventario.h / inventario.c: controlam o vetor de itens, ocupacao por espacos, busca, insercao, remocao e listagem.
- personagem.h / personagem.c: definem fichas, cadastro, equipamentos, CRUD, equipar, desequipar e calculo de atributos totais.
- main.c: programa de demonstracao com menu textual usando apenas a interface publica.
- readme.md: arquivo original com as instrucoes da atividade.
- TP-Etapa-1.txt e TP-Geral.txt: enunciados fornecidos.

Comando de compilacao
gcc -std=c11 -Wall -Wextra -pedantic main.c personagem.c inventario.c item.c -o personagens_temp; .\personagens_temp.exe

Tambem pode ser usado o exe (Esta somente na versão do github para evitar problemas na entrega do classroom!)

Execucao
No Windows/PowerShell:
.\personagens.exe

No Linux/macOS:
./personagens

Decisoes relevantes
- O cadastro suporta ate 20 personagens por meio da constante CADASTRO_MAX_PERSONAGENS.
- Cada inventario aceita ate 50 itens e ate 50 espacos consumidos, usando INVENTARIO_MAX_ITENS e INVENTARIO_MAX_ESPACOS.
- Raca, classe, tipo de item, slot de equipamento e codigos de retorno usam enum.
- O cadastro e sempre passado por parametro; nao ha variavel global para armazenar personagens.
- Os registros de personagens e itens permanecem contiguos apos remocoes.
- Itens equipados deixam de aparecer no inventario e nao consomem seus espacos enquanto equipados.
- Armas de duas maos ocupam e bloqueiam as duas maos. O bonus de uma arma de duas maos e contado uma unica vez.
- As trocas de equipamento verificam antes se o item antigo pode voltar ao inventario, preservando a atomicidade.
- Os atributos totais sao calculados sob demanda e nao ficam armazenados como copia permanente.



Checklist do TP-1 (Principais pedidos.)
- [x] Struct de personagem com todos os campos obrigatorios.
- [x] Cadastro com vetor estatico, quantidade e capacidade maxima 20.
- [x] Validacao de ID positivo, nome, raca, classe, nivel, PV, ataque, defesa, iniciativa e poder.
- [x] CRUD de personagens com ID unico e remocao contigua.
- [x] Struct de item com ID, nome, tipo, espacos, bonus e poder.
- [x] Inventario com capacidade de 50 espacos calculada por funcao.
- [x] Adicao, busca, remocao, listagem e ocupacao do inventario.
- [x] Equipamentos fixos: elmo, peitoral, manoplas, calca, botas, anel, colar, cinto e duas maos.
- [x] Compatibilidade entre tipo de item e slot de equipamento.
- [x] Regra de arma de duas maos bloqueando as duas maos.
- [x] Desequipar recusado quando nao ha espaco suficiente no inventario.
- [x] Calculo de ataque, defesa, iniciativa, PV maximos e poder totais usando apenas itens equipados.
- [x] Interface publica em personagem.h e implementacao em personagem.c.
- [x] Separacao adicional em item.h/.c e inventario.h/.c.
- [x] Menu textual com todas as operacoes minimas exigidas.
- [x] Leitura textual com fgets, sem uso de gets.
