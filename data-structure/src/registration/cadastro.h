/* 
* cadastro.h
*
* Arquivo de cabeçalhos e definições 
*/

#define MAXLIN 1000
#define MAXSTR 200

#define DADOS "./data/datasets/ed2020/cad2020.csv"
#define INDICE "./data/datasets/ed2020/cad2020.ind"

void extrai(char *lin, int elem, char *d);
void criaIndice(char *nomearq, char *nomeind);
int busca(char *nome);

typedef struct INDICECAD
{
	char nome[MAXSTR];
	unsigned long localiza;
} IndiceCadastro;

// Define números de campos do arquivo para ser usado como elem da função extrai()

#define Id_SERVIDOR_PORTAL 1
#define NOME 2
#define CPF 3
#define MATRICULA 4
#define DESCRICAO_CARGO 5
#define CLASSE_CARGO 6
#define REFERENCIA_CARGO 7
#define PADRAO_CARGO 8
#define NIVEL_CARGO 9
#define SIGLA_FUNCAO 10
#define NIVEL_FUNCAO 11
#define FUNCAO 12
#define CODIGO_ATIVIDADE 13
#define ATIVIDADE 14
#define OPCAO_PARCIAL 15
#define COD_UORG_LOTACAO 16
#define UORG_LOTACAO 17
#define COD_ORG_LOTACAO 18
#define ORG_LOTACAO 19
#define COD_ORGSUP_LOTACAO 20
#define ORGSUP_LOTACAO 21
#define COD_UORG_EXERCICIO 22
#define UORG_EXERCICIO 23
#define COD_ORG_EXERCICIO 24
#define ORG_EXERCICIO 25
#define COD_ORGSUP_EXERCICIO 26
#define ORGSUP_EXERCICIO 27
#define TIPO_VINCULO 28
#define SITUACAO_VINCULO 29
#define DATA_INICIO_AFASTAMENTO 30
#define DATA_TERMINO_AFASTAMENTO 31
#define REGIME_JURIDICO 32
#define JORNADA_DE_TRABALHO 33
#define DATA_INGRESSO_CARGOFUNCAO 34
#define DATA_NOMEACAO_CARGOFUNCAO 35
#define DATA_INGRESSO_ORGAO 36
#define DOCUMENTO_INGRESSO_SERVICOPUBLICO 37
#define DATA_DIPLOMA_INGRESSO_SERVICOPUBLICO 38
#define DIPLOMA_INGRESSO_CARGOFUNCAO 39
#define DIPLOMA_INGRESSO_ORGAO 40
#define DIPLOMA_INGRESSO_SERVICOPUBLICO 41
#define UF_EXERCICIO 42