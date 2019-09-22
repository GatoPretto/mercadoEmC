/* 01) Escrever um programa em C que cadastre o nome, a
quantidade em estoque, o preço e o desconto de um 
determinado produto. Em seguida imprima todos os dados
e o valor de venda, com o devido desconto. COnsidere que cada
produto é uma estrutura conforme a seguir:
    typedef struct{
        char[100] nome;
        int estoque;
        float preco;
        int desconto;
    }PRODUTO;

*/

#include <stdio.h>
#include <string.h>
#include <locale.h>
#define  CAPACIDADEMAXESTOQUE 100
#define  CAPACIDADEPRODUTOS 5
int sequencial = 0;

typedef struct{
    int id;
    char nome[100];
    int estoque;
    float preco;
    int desconto;
    float totalDesconto;
    int totalEstoque;
    int tamanhoLista;
}PRODUTO;

typedef struct{
    int sequencialParaEditar;
}CRUD;



void listaOsProdutos(PRODUTO *lista, int *id){
    printf("\n============ LISTA PRODUTOS ===============");
    for(int a = 0; a<*id; a++){
        printf("\nId[%d]", lista[a].id);
        printf("\nNome = %s\n", lista[a].nome);
        printf("Qtd Estoque = %d\n", lista[a].estoque);
        printf("Preço = %.2f\n", lista[a].preco);
        printf("Desconto de %d%\n", lista[a].desconto);
        lista[a].totalDesconto = lista[a].preco-((lista[a].desconto * lista[a].preco) / 100);
        printf("Valor do %s com desconto de %d%  = %.2f\n", lista[a].nome, lista[a].desconto, lista[a].totalDesconto);
    }
    if(int a = 0 == *id){
        printf("\n\n\n        Nenhum Produto Cadastrado.\n\n");
    }
    
}

void listaEstoque(PRODUTO *lista, int *i){
    printf("\n============ LISTA ESTOQUE ===============\n");
    int a = 0;
    for(; a<*i; a++){
        printf("\nTotal de %d %s em estoque.\n",lista[a].estoque, lista[a].nome);
    }
    printf("\nO Estoque está com um total de %d/%d produtos cadastrados.\n", lista->totalEstoque, CAPACIDADEMAXESTOQUE);    
}


void cadastraEstoque(PRODUTO *lista, int *i){
    lista->totalEstoque += lista[*i].estoque ;
    while(lista->totalEstoque > CAPACIDADEMAXESTOQUE){
        printf("\nValor de i = %d", *i);
        printf("\nCapacidade Maxima de estoque atingida %d/%d\nInsira uma quantidade menor de produtos\n>>", lista->totalEstoque, CAPACIDADEMAXESTOQUE);
        lista->totalEstoque -= lista[*i].estoque;
        scanf("%d", &lista[*i].estoque);
        lista->totalEstoque += lista[*i].estoque;
    }
    lista->tamanhoLista += 1;       
}

void listaNomeProdutosCadastrados(PRODUTO *lista, int *i){
    int a = 0;
    printf("ID    | Nome");
    for(; a<*i; a++){
        printf("\n[%d]     %s", a+1, lista[a].nome);
    }
}

void detalhesProduto(PRODUTO *lista, int *i){
    printf("Valor de i = %d\n", *i);
    printf("\nId[%d]", lista->id);
    printf("\nNome = %s\n", lista[*i-1].nome);
    printf("Qtd Estoque = %d\n", lista[*i-1].estoque);
    printf("Preço = %.2f\n", lista[*i-1].preco);
    printf("Desconto de %d%\n", lista[*i-1].desconto);
    lista[*i].totalDesconto = lista[*i].preco-((lista[*i-1].desconto * lista[*i-1].preco) / 100);
    printf("Valor do %s com desconto de %d%  = %.2f\n", lista[*i-1].nome, lista[*i-1].desconto, lista[*i-1].totalDesconto);
}

void editarProduto(CRUD *edicao, PRODUTO *lista, int *i){
    printf("\n============ EDITAR PRODUTO ===============\n");
    if(strlen(lista->nome) == NULL){
        printf("\n            Nada para ser editado\n");
    }else{
        printf("Editar Qual Produto ?\n");
        fflush(stdin);
        listaNomeProdutosCadastrados(lista, i);
        printf("\n\nEscolha a ID do produto que deseja editar \n> ");
        scanf("%d", &edicao->sequencialParaEditar);
        for(int i = 0; i < lista->tamanhoLista; i++){
            if(lista[i].id == edicao->sequencialParaEditar-1){
                printf("\n============ ALTERAR %s ===============\n", lista[i].nome);
                detalhesProduto(lista, &edicao->sequencialParaEditar);
                printf("\n\nNovo Nome do produto:\n> ");
                scanf("%s", lista[i].nome);
                printf("Qnt Produtos:\n> ");
                lista[i].totalEstoque -= lista[i].estoque;
                scanf("%d", &lista[i].estoque);
                fflush(stdin);
                __ptr_t(stdin);
                cadastraEstoque(lista, &i);
                printf("Valor Un:\nR$ ");
                scanf("%f", &lista[i].preco);
                printf("Desconto:\n%% ");
                scanf("%d", &lista[i].desconto);
            }
        }
    }
    
}

void cadastraProduto(PRODUTO * lista, int *id){
    printf("\n===========================================\n");
            printf("\nid [%d]\n", *id+1);
            lista[*id].id = *id;
            printf("Nome do produto:\n> ");
            scanf("%s", lista[*id].nome);
            printf("Qnt Produtos:\n> ");
            scanf("%d", &lista[*id].estoque);
            fflush(stdin);
            __ptr_t(stdin);
            cadastraEstoque(lista, id);
            printf("Valor Un:\nR$ ");
            scanf("%f", &lista[*id].preco);
            printf("Desconto:\n%% ");
            scanf("%d", &lista[*id].desconto);
            *id += 1;
}

int main(){
    setlocale(LC_ALL, "Portuguese");
    PRODUTO produtos[4];
    CRUD editar[4];


    while(true){
        //Condições de execução.
        if(sequencial == CAPACIDADEPRODUTOS){
            printf("\nLimite maximo de produtos atingido\n\n");
            return false;
        }
        printf("\n===========================================\n                 [MENU]");
        printf("\n[0] Sair.\n[1] Cadastrar um novo produto\n[2] Listar Produtos Cadastrados\n");
        printf("[3] Mostrar Estoque\n[4] Editar Produto.\n> ");
        int escolha;
        scanf("%d", &escolha);
        if(escolha == 0){
            return false;
        }else if(escolha == 1){
            cadastraProduto(produtos, &sequencial);
        }else if(escolha == 2){
            listaOsProdutos(produtos, &sequencial);
        }else if(escolha == 3){
            listaEstoque(produtos, &sequencial);
        }else if(escolha == 4){
            editarProduto(editar ,produtos, &sequencial);
        }
    }

    return 0;
}
