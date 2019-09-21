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

/*#include <stdio.h>
#include <string.h>
#include <locale.h>*/
#define  CAPACIDADEMAXESTOQUE 100

typedef struct{
    char nome[100];
    int estoque;
    float preco;
    int desconto;
    float totalDesconto;
    int totalEstoque;
}PRODUTO;


void listaOsProdutos(PRODUTO *lista, int *i){
    printf("\n============ LISTA PRODUTOS ===============");
    for(int a = 0; a<*i; a++){
        printf("\nNome = %s\n", lista[a].nome);
        printf("Qtd Estoque = %d\n", lista[a].estoque);
        printf("Preço = %.2f\n", lista[a].preco);
        printf("Desconto de %d%\n", lista[a].desconto);
        lista[a].totalDesconto = lista[a].preco-((lista[a].desconto * lista[a].preco) / 100);
        printf("Valor do %s com desconto de %d%  = %.2f\n", lista[a].nome, lista[a].desconto, lista[a].totalDesconto);
    }
    if(int a = 0 == *i){
        printf("\n\n\n        Nenhum Produto Cadastrado.\n\n");
    }
    
}

void listaEstoque(PRODUTO *lista, int *i){
    printf("\n============ LISTA ESTOQUE ===============\n");
    lista->totalEstoque = 0;
    for(int a = 0; a<*i; a++){
        printf("\n%s = %d",lista[a].nome, lista[a].estoque);
        lista->totalEstoque += lista[a].estoque;
    }
    printf("\n\nO Estoque está com um total de %d/%d produtos cadastrados.\n\n", lista->totalEstoque, CAPACIDADEMAXESTOQUE);
}

int main(){
    setlocale(LC_ALL, "Portuguese");
    PRODUTO produtos[4];
    int i = 0;
    while(true){
        //Condições de execução.
        if(i == 3){
            printf("\nLimite maximo de produtos atingido\n\n");
            return false;
        }
        printf("\n===========================================\n                 [MENU]");
        printf("\n[0] Sair.\n[1] Cadastrar um novo produto\n[2] Listar Produtos Cadastrados\n");
        printf("[3] Mostrar Estoque\n>>");
        int escolha;
        scanf("%d", &escolha);
        if(escolha == 0){
            return false;
        }else if(escolha == 1){
            printf("\n===========================================\n");
            printf("Nome do produto:\n>");
            scanf("%s", produtos[i].nome);
            printf("Qnt Estoque:\n>");
            scanf("%d", &produtos[i].estoque);
            printf("Preço:\n>");
            scanf("%f", &produtos[i].preco);
            printf("Desconto:\n>%");
            scanf("%d", &produtos[i].desconto);
            i++;
        }else if(escolha == 2){
            listaOsProdutos(produtos, &i);
        }else if(escolha ==3){
             listaEstoque(produtos, &i);
        }
    }

    return 0;
}
