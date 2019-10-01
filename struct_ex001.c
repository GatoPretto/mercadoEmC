// === SISTEMA DE CONTROLE DE PRODUTOS E ESTOQUE DE MERCADO. ===

#include <stdio.h>
#include <string.h> //Manipulação de strings
#include <locale.h> //Caracteres.
#include <stdlib.h> //Alocação de memória
#include <time.h>   //Timer
#include <unistd.h> //sleep
#include <stdbool.h>

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
    printf("\n============== LISTA PRODUTOS ===============\n\n\n");
    FILE * fileRead;
	char nomeTxt[100];
	int verificador = 0;
	strcpy(nomeTxt, "c:\\HutCode\\banco\\cadastros.txt");
	fileRead = fopen(nomeTxt,"r");
	char string = ' ';
	string = fgetc(fileRead);
	while(string != EOF){
		printf("%c", string);
		if(string == '\n'){
			printf("\n");
			verificador = 1;
		}
		string = fgetc(fileRead);
	}
	if(lst->id == 0 && verificador != 1){
		printf("\n*** NÃO HÁ PRODUTOS CADASTRADOS. ***\n");
	}
	fclose(fileRead);
	printf("\n\n\n");
	system("pause");
}

/*void cadastraEstoque(int *lst){
	
}*/

void cadastraProduto(PRODUTO *lst){
    system("cls");
    printf("\n========== CADASTRO DE PRODUTOS =============\n");
	lst->id = pegaIdAtual();
	lst[lst->id].id = lst->id; //lista[0] = 0
	printf("\nID [%d]\n", lst[lst->id].id);
    printf("Nome do produto:\n> ");
    scanf(" %[^\n]s",lst[lst->id].nome);
    fflush(stdin);
	printf("Qnt Produtos:\n> ");
	scanf("%d", &lst[lst->id].estoque);
    cadastraNoBancoDeDados(lst);
}

int pegaIdAtual(){
	FILE * verificaTxt;
	FILE * fileWrite;
	char nomeTxt[100];
	strcpy(nomeTxt, "c:\\HutCode\\banco\\cadastros.txt");
	if(verificaTxt = fopen(nomeTxt, "r")){
	//Consequentemente não entra no Else.
	}else{
		///Criando o arquivo .txt
		if((fileWrite = fopen(nomeTxt, "w"))==NULL){
			fileWrite = fopen(nomeTxt, "w");
			fclose(fileWrite);
		}	 
		if((fileWrite = fopen(nomeTxt, "w"))==NULL){
	 		printf("Arquivo não pode ser aberto\n");
	 		system("pause");
	 		exit(1);
		}
	}
	//Anexando informação.
	FILE * fileAppend;
	FILE * fileRead;
	char string = ' ';
	int contadorDeLinhas = 1;
	fileRead = fopen(nomeTxt, "r");
		
	//Faz primeiro a leitura do documento
	string = fgetc(fileRead);
	while(string != EOF){
		if(string == '\n'){
			contadorDeLinhas++;
		}
		string = fgetc(fileRead);		
	}
	fclose(fileRead);
	if(contadorDeLinhas == 1){
		fileAppend = fopen(nomeTxt, "a");
		//fprintf(fileAppend, "\n");
		fclose(fileAppend);
		return contadorDeLinhas--;
	}else{
		return contadorDeLinhas-=1;
	}	
}

void criaDiretorio(){
	char caminhoPasta[150];
	strcpy(caminhoPasta,"mkdir c:\\HutCode\\banco");
	system(caminhoPasta);
	//CRIAR UMA CONDIÇÃO PARA MOSTRAR CASO NÃO TENHA SIDO CRIADO UMA PASTA.
}

void cadastraNoBancoDeDados(PRODUTO *lst){  
    char nomePastaBD[100], nomeTxt[100];   
    //Cria o arquivo .txt
    FILE *fileWrite;
    FILE *verificaTxt;
    strcpy(nomeTxt, "c:\\HutCode\\banco\\cadastros.txt");
    //Se o verificaTxt conseguir ler o arquivo é porque ele existe.
	if(verificaTxt = fopen(nomeTxt, "r")){
	//Consequentemente não entra no Else.
	}else{
		///Criando o arquivo .txt
		if((fileWrite = fopen(nomeTxt, "w"))==NULL){
			fileWrite = fopen(nomeTxt, "w");
			fclose(fileWrite);
		}	
	    
		if((fileWrite = fopen(nomeTxt, "w"))==NULL){
	 		printf("Arquivo não pode ser aberto\n");
	 		system("pause");
	 		exit(1);
		}
	}     
		
	//Anexando informação.
	FILE * fileAppend;
	FILE * fileRead;
	char string = ' ';
	fileRead = fopen(nomeTxt, "r");
	int criarOuNaoMenu = 0, inserirInf = 0;
	
	//Faz primeiro a leitura do documento
	string = fgetc(fileRead);
	while(string != EOF){
		//Se já existir um "I" no txt. Não cria novamente o menu.
		if(string == 'I'){
			printf("ENTROU");
			criarOuNaoMenu = 1;
		}
		string = fgetc(fileRead);		
	}
	
	//De acordo com as condições, adiciona informações.
	if(criarOuNaoMenu == 0){
			fileAppend = fopen(nomeTxt, "a");
			fprintf(fileAppend, "    ID      NOME     ESTOQUE\n");
			fclose(fileAppend);
	}
	fileAppend = fopen(nomeTxt, "a");
	char str[12];
	//converte inteiro para char.
	char stringID[5], stringEstoque[5];
	itoa(lst->id, stringID, 10);
	itoa(lst[lst->id].estoque, stringEstoque, 10);
	fprintf(fileAppend, "\n    [");
	fprintf(fileAppend, stringID);
	fprintf(fileAppend, "]     ");
	fprintf(fileAppend, lst[lst->id].nome);
	fprintf(fileAppend, "          ");
	fprintf(fileAppend, stringEstoque);
	fclose(fileAppend);
	fclose(fileRead);
	
	//fprintf = passa toda uma frase.
	//fputs = passa vetor de string
	//fputc = passa apenas um caractere.
	 
}

void editarProduto(char id, char *nameTxt){
	FILE *fileRead;
	FILE *fileBackup;
	FILE *fileAppend;
	int condicao = 0;
	char recebeRead = ' ', passaBackup = ' ';
	
	fileRead = fopen(nameTxt, "r+");
	fileAppend = fopen("c:\\HutCode\\banco\\backup.txt", "w");
	
	while(recebeRead != EOF){
		if(recebeRead == '['){
			fputc('[', fileAppend);
			recebeRead = fgetc(fileRead);
			if(recebeRead == id){
				char novoNome[50];
				char novoEstoque[10];
				printf("\n\nNome: \n> ");
				scanf(" %[^\n]s",novoNome);
				printf("Estoque \n> ");
				scanf(" %[^\n]s", novoEstoque);
				
				
				while(recebeRead != '\n' && recebeRead != EOF){
					if(condicao == 0){
						fputc(recebeRead, fileAppend);
						fputc(']', fileAppend);
						fputs("     ", fileAppend);
						condicao = 1;
					}else if(condicao == 1){						
						recebeRead = fgetc(fileRead);
						if(recebeRead != ' '){
							fputs(novoNome, fileAppend);
							condicao = 2;
						 	recebeRead = fgetc(fileRead);			
						}
					}else if(condicao == 2){
						recebeRead = fgetc(fileRead);
						if(recebeRead != ' '){
							fputs("\t\t", fileAppend);
							fputs(novoEstoque, fileAppend);
							id = -1;
							condicao = -1;
						}	
					}
					fputc(' ', fileAppend);
					recebeRead = fgetc(fileRead);
				}
				
			}
		}
		fputc(recebeRead, fileAppend);
		recebeRead = fgetc(fileRead);
	}
	fclose(fileRead);	
	fclose(fileAppend);
	
	//PASSANDO OS DADOS ATUALIZADOS.
	fileRead = fopen(nameTxt, "w");
	fileAppend = fopen("c:\\HutCode\\banco\\backup.txt", "r+");
	passaBackup = fgetc(fileAppend);
	while(passaBackup != EOF){
		fputc(passaBackup, fileRead);
		passaBackup = fgetc(fileAppend);
	}
	fclose(fileRead);
	fclose(fileAppend);
	remove("c:\\HutCode\\banco\\backup.txt");
	
	//Excluindo backup;
	
}

void escolhaProdutoEditar(PRODUTO *lst){
	lst->id = pegaIdAtual()-1;
	//int id_produto = 0;
	char id_produto = ' ', stringID[10];
	char nomeTxt[100], string = ' ';
	FILE * fileRead;
	
	system("cls");
	printf("\n========== EDITAR PRODUTOS =============\n\n");
	strcpy(nomeTxt, "c:\\HutCode\\banco\\cadastros.txt");
	fileRead = fopen(nomeTxt,"r+");
	string = fgetc(fileRead);
	while(string != EOF){
		printf("%c", string);
		if(string == '\n'){
			printf("\n");
		}
		string = fgetc(fileRead);
	}
	printf("\n\n\nInforme a ID do produto que deseja alterar\n> ");
	scanf(" %c", &id_produto);//Lembrar de jogar o %c >>
	//Conversão de inteiro para char.
	itoa(lst->id, stringID, 10);
	rewind(fileRead);
	string = fgetc(fileRead);
	while(string != EOF){
		if(string == '['){
			string = fgetc(fileRead);
			if(string == id_produto ){
				system("clear");
				printf("\n========== EDITANDO PRODUTO =============\n\n");
				printf("\nID\t      Nome\t\t\tEstoque\n[");
				while(string != '\n' && string != EOF){
					if(string == ' '){
						printf(" ");
					}
					printf("%c", string);
					string = fgetc(fileRead);
					
				}
				fclose(fileRead);
				editarProduto(id_produto, nomeTxt);
				printf("\n");
				id_produto = 0;
				stringID[0] = -1;
				system("pause");
			}
		}
		string = fgetc(fileRead);
	}			
	if(string == '\n'){
		printf("\n");
	}
	
}
	
int main(){
    setlocale(LC_ALL, "Portuguese");
    //Cria lista.
    PRODUTO * lista[100];
    *lista = criarLista(&lista);
    //Configura Diretório
    criaDiretorio();
    while(1){
    	int escolhaMenu = 0;
    	system("cls");
    	mostraHoraMinutos();
    	printf("\n            [MENU]\n");
        printf("\n[0] Sair.\n[1] Cadastrar um novo produto.\n[2] Listar Produtos Cadastrados.");
		printf("\n[3] Editar Produto\n > ");
        scanf("%d", &escolhaMenu);
        if(escolhaMenu == 0){
    		return 0;
		}else if(escolhaMenu == 1){
        	cadastraProduto(lista);
		}else if(escolhaMenu == 2 ){
			listaOsProdutos(lista);
		}else if(escolhaMenu == 3){
			escolhaProdutoEditar(lista);
		}

   	}


    return 0;
}
