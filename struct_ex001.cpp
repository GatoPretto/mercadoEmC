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

typedef struct produto PRODUTO[100];

struct produto{
    int id = 0;
    char nome[100];
    int estoque;
    int estoqueTotal = 0;
    float preco;
    int desconto;
    float totalDesconto;
};



PRODUTO * criarLista(){
    PRODUTO * criarLista = (PRODUTO *)malloc(sizeof(PRODUTO));
}

void mostraHoraMinutos(){
    /*SETANDO DATA E HORA*/
        //ponteiro para struct que armazena data e hora 
        struct tm *data_hora_atual;
        //variável do tipo time_t para armazenar o tempo em segundos
        time_t segundos;
        //obtendo o tempo em segundos 
        time(&segundos);  
        //converter de segundos para o tempo local  
        data_hora_atual = localtime(&segundos);
        //printf("\n %d/%d/%d", data_hora_atual->tm_mday, data_hora_atual->tm_mon, data_hora_atual->tm_year+1900);
        if(data_hora_atual->tm_min < 10 and data_hora_atual->tm_min > 0){
            printf("\n %d:0%d", data_hora_atual->tm_hour, data_hora_atual->tm_min);
        }else{
            printf("\n %d:%d", data_hora_atual->tm_hour, data_hora_atual->tm_min);
        }
        
}

void listaOsProdutos(PRODUTO lista){
    system("clear");
    printf("\n============== LISTA PRODUTOS ===============\n");
    if(lista->id != 0){
        for(int i = 1; i<= lista->id; i++){
            printf("\nId[%d]", lista[i].id);
            printf("\nNome = %s\n", lista[i].nome);
            printf("Qtd Estoque = %d\n", lista[i].estoque);
        }
        printf("\nPressione ENTER para voltar ao MENU.\n> ");
        char c;
        scanf("%c%*c", &c); //Importantissimo ! Pausa tanto em Linux como windows.
        if(sizeof(c)!= 0){
            system("clear");
        }

        
        
    }else{
        printf("\n\n*** Não há produtos cadastrados. ***\n");
        sleep(2);
        system("clear");
        
    }
    
}

void cadastraEstoque(PRODUTO lista){
    lista->estoqueTotal += lista[lista->id].estoque;
    while(lista->estoqueTotal > CAPACIDADEMAXESTOQUE){
        printf("\nCapacidade max de estoque esgotoada [Estoque %d/%d]\nInsira um valor menor.\n> ", lista->estoqueTotal, CAPACIDADEMAXESTOQUE);
        lista->estoqueTotal -= lista[lista->id].estoque;
        scanf("%d", &lista[lista->id].estoque);
        lista->estoqueTotal += lista[lista->id].estoque;
    };
    //printf("\nEstoque %d/%d", lista->estoqueTotal, CAPACIDADEMAXESTOQUE);
}

void cadastraProduto(PRODUTO lista){
    system("clear");
    printf("\n========== CADASTRO DE PRODUTOS =============\n");
            lista->id++;  
            lista[lista->id].id = lista->id; //lista[0] = 0
            printf("\nID [%d]\n", lista[lista->id].id);
            printf("Nome do produto:\n> ");
            scanf("%s", &lista[lista->id].nome); //lista[0].nome
            printf("Qnt Produtos:\n> ");
            scanf("%d", &lista[lista->id].estoque);
            cadastraEstoque(lista);       
}

int main(){
    setlocale(LC_ALL, "Portuguese");
    PRODUTO * lista = criarLista();
    while(true){
        int escolhaMenu = 0;
        system("clear");

        mostraHoraMinutos();
        printf("\n            [MENU]\n");
        printf("\n[1] Cadastrar um novo produto\n[2] Listar Produtos Cadastrados\n > ");
        scanf("%d", &escolhaMenu);
        if(escolhaMenu == 1){
            cadastraProduto(*lista);
        }else if(escolhaMenu == 2){
            listaOsProdutos(*lista);
        }
    }

    return 0;
}
