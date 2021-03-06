#include <stack.h>
#include <bst.h>

#ifndef REGISTRATION_HEAD
#define REGISTRATION_HEAD 1

#define MAX_LINE_LEN 1000
#define MAX_DATA_LEN 200

char *extract_register_data(char *line, int data_type);
Stack *find_registers(char *name, BST *data);

#define ID 1
#define ID_SERVIDOR_PORTAL 1 + 1
#define NOME 2 + 1
#define CPF 3 + 1
#define MATRICULA 4 + 1
#define DESCRICAO_CARGO 5 + 1
#define CLASSE_CARGO 6 + 1
#define REFERENCIA_CARGO 7 + 1
#define PADRAO_CARGO 8 + 1
#define NIVEL_CARGO 9 + 1
#define SIGLA_FUNCAO 10 + 1
#define NIVEL_FUNCAO 11 + 1
#define FUNCAO 12 + 1
#define CODIGO_ATIVIDADE 13 + 1
#define ATIVIDADE 14 + 1
#define OPCAO_PARCIAL 15 + 1
#define COD_UORG_LOTACAO 16 + 1
#define UORG_LOTACAO 17 + 1
#define COD_ORG_LOTACAO 18 + 1
#define ORG_LOTACAO 19 + 1
#define COD_ORGSUP_LOTACAO 20 + 1
#define ORGSUP_LOTACAO 21 + 1
#define COD_UORG_EXERCICIO 22 + 1
#define UORG_EXERCICIO 23 + 1
#define COD_ORG_EXERCICIO 24 + 1
#define ORG_EXERCICIO 25 + 1
#define COD_ORGSUP_EXERCICIO 26 + 1
#define ORGSUP_EXERCICIO 27 + 1
#define TIPO_VINCULO 28 + 1
#define SITUACAO_VINCULO 29 + 1
#define DATA_INICIO_AFASTAMENTO 30 + 1
#define DATA_TERMINO_AFASTAMENTO 31 + 1
#define REGIME_JURIDICO 32 + 1
#define JORNADA_DE_TRABALHO 33 + 1
#define DATA_INGRESSO_CARGOFUNCAO 34 + 1
#define DATA_NOMEACAO_CARGOFUNCAO 35 + 1
#define DATA_INGRESSO_ORGAO 36 + 1
#define DOCUMENTO_INGRESSO_SERVICOPUBLICO 37 + 1
#define DATA_DIPLOMA_INGRESSO_SERVICOPUBLICO 38 + 1
#define DIPLOMA_INGRESSO_CARGOFUNCAO 39 + 1
#define DIPLOMA_INGRESSO_ORGAO 40 + 1
#define DIPLOMA_INGRESSO_SERVICOPUBLICO 41 + 1
#define UF_EXERCICIO 42 + 1

#endif