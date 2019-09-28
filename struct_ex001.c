/*
        === SISTEMA DE CONTROLE DE PRODUTOS E ESTOQUE DE MERCADO. ===
*/

#include <stdio.h>
#include <string.h> //Manipulação de strings
#include <locale.h> //Caracteres.
#include <stdlib.h> //Alocação de memória
#include <time.h>   //Timer
#include <unistd.h> //sleep

#define  CAPACIDADEMAXESTOQUE 100
#define  CAPACIDADEPRODUTOS 5
int sequencial = 0;

typedef struct{
    int id ;
    char nome[100];
    int estoque;
    int estoqueTotal;
    float preco;
    int desconto;
    float totalDesconto;
}PRODUTO;


PRODUTO * criarLista(PRODUTO *lst){
    PRODUTO * lista = (PRODUTO *)malloc(sizeof(PRODUTO));
    if(lista == NULL){
    	printf("Memoria Insuficiente");
    	exit(1);
	}
	lst->id = 0;
	lst->estoque = 0;
	lst->estoqueTotal = 0;
	lst->preco = 0;
	return lst->id;
}


void mostraHoraMinutos(){
	    //SETANDO DATA E HORA
        //ponteiro para struct que armazena data e hora
        struct tm *data_hora_atual;
        //variável do tipo time_t para armazenar o tempo em segundos
        time_t segundos;
        //obtendo o tempo em segundos
        time(&segundos);
        //converter de segundos para o tempo local
        data_hora_atual = localtime(&segundos);
        //printf("\n %d/%d/%d", data_hora_atual->tm_mday, data_hora_atual->tm_mon, data_hora_atual->tm_year+1900);
        if(data_hora_atual->tm_min < 10 && data_hora_atual->tm_min > 0){
            printf("\n %d:0%d", data_hora_atual->tm_hour, data_hora_atual->tm_min);
        }else{
            printf("\n %d:%d", data_hora_atual->tm_hour, data_hora_atual->tm_min);
        }

}

void listaOsProdutos(PRODUTO *lst){
    system("cls");
    printf("\n============== LISTA PRODUTOS ===============\n");
    if(lst[lst->id].id != 0){
    	int i = 1;
        for(; i <= lst->id; i++){
            printf("\nId[%d]", lst[i].id);
            printf("\nNome = %s\n", lst[i].nome);
            printf("Qtd Estoque = %d\n\n", lst[i].estoque);
        }
        system("pause");



    }else{
        printf("\n\n*** Não há produtos cadastrados. ***\n");
        sleep(2);
        system("clear");

    }

}
void cadastraEstoque(PRODUTO *lst){
    lst->estoqueTotal += lst[lst->id].estoque;
    while(lst->estoqueTotal > CAPACIDADEMAXESTOQUE){
        printf("\nCapacidade max de estoque esgotoada [Estoque %d/%d]\nInsira um valor menor.\n> ", lst->estoqueTotal, CAPACIDADEMAXESTOQUE);
        lst->estoqueTotal -= lst[lst->id].estoque;
        scanf("%d", &lst[lst->id].estoque);
        lst->estoqueTotal += lst[lst->id].estoque;
    };
}



void cadastraProduto(PRODUTO *lst){
    system("cls");
    printf("\n========== CADASTRO DE PRODUTOS =============\n");
	lst->id++;
	lst[lst->id].id = lst->id; //lista[0] = 0
	printf("\nID [%d]\n", lst[lst->id].id);
    printf("Nome do produto:\n> ");
    scanf("%s", lst[lst->id].nome);
	printf("Qnt Produtos:\n> ");
	scanf("%d", &lst[lst->id].estoque);
    cadastraEstoque(lst);
}



int main(){
    setlocale(LC_ALL, "Portuguese");
    PRODUTO * lista[100];
    *lista = criarLista(&lista);
    while(1){
    	int escolhaMenu = 0;
    	system("cls");
    	mostraHoraMinutos();
    	printf("\n            [MENU]\n");
        printf("\n[1] Cadastrar um novo produto\n[2] Listar Produtos Cadastrados\n > ");
        scanf("%d", &escolhaMenu);
        if(escolhaMenu == 1){
        	cadastraProduto(lista);
		}else if(escolhaMenu == 2 ){
			listaOsProdutos(lista);
		}

   	}


    return 0;
}


