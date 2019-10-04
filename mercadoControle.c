// === SISTEMA DE CONTROLE DE PRODUTOS E ESTOQUE DE MERCADO. ===

#include <stdio.h>
#include <string.h> //Manipulação de strings
#include <locale.h> //Caracteres.
#include <stdlib.h> //Alocação de memória
#include <time.h>   //Timer
#include <unistd.h> //sleep
#include <stdbool.h>

typedef struct _produto PRODUTO;

struct _produto{
    int id ;
    char nome[100];
    int estoque;
    int estoqueTotal;
    float preco;
    int desconto;
    float totalDesconto;
    PRODUTO *next;
};


static PRODUTO *list_init(void){
	PRODUTO *mem = malloc(sizeof(PRODUTO));
	if(!mem){
		perror("malloc");
		exit(1);
	}else{
		/*memset esta função é utilizada para preencher
		determinada área de memória com o caracter definido pelo usuário
		no argumento c.Basicamente, quando criamos variáveis do tipo vetor
		ou estruturas de dados, devemos limpar aárea de memória antes
		de utilizar.*/
		memset(mem, 0, sizeof(PRODUTO));
		return mem;
	}
}

static PRODUTO *list_add(int estoque, char *nome, PRODUTO *primeiraPosLista){
	/*‘pos_inicioDaLista’ sempre aponta para o início da lista*/
	PRODUTO *inicio,*temp;	

	/*ao adicionar o primeiro membro precisamos*criar a lista*/
	if(inicio == NULL){
		inicio = temp = list_init();
	  	
	/*caso a lista já exista, devemos alocar memória no último membro*/
	}else {
		inicio = temp = primeiraPosLista;
		while(temp)
			if(temp->next == NULL){
				break;	
			} 	
			else{
				temp = temp->next;	
			} 
					
			/*agora temp->next é um membro vazio e será utilizado*/
			temp->next = list_init();
			temp = temp->next;				
	}
	/*copia os dados no novo membro da lista*/
	temp[temp->id].estoque = estoque;
	strncpy(temp[temp->id].nome, nome, sizeof(temp[temp->id].nome));
	return inicio;	
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
        if(data_hora_atual->tm_min < 10 && data_hora_atual->tm_min >= 0){
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

void cadastraEstoque(int *lst){
	
}

void cadastraNoBancoDeDados(PRODUTO *list){  
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
	itoa(list->id, stringID, 10);
	itoa(list[list->id].estoque, stringEstoque, 10);
	fprintf(fileAppend, "\n    [");
	fprintf(fileAppend, stringID);
	fprintf(fileAppend, "]     ");
	fprintf(fileAppend, list[list->id].nome);
	fprintf(fileAppend, "          ");
	fprintf(fileAppend, stringEstoque);
	fclose(fileAppend);
	fclose(fileRead);
	
	//fprintf = passa toda uma frase.
	//fputs = passa vetor de string
	//fputc = passa apenas um caractere.
	 
}

int cadastraProduto(PRODUTO *lst){
	PRODUTO *pos_inicioDaLista, *bkp;
	lst->id = pegaIdAtual();
    system("cls");
    printf("\n========== CADASTRO DE PRODUTOS =============\n");	
	lst[lst->id].id = lst->id; 
	printf("\nID [%d]\n", lst[lst->id].id);
	
    fprintf(stdout, "Nome do produto:\n> ");
    scanf(" %[^\n]s" , lst[lst->id].nome);
    snprintf(lst[lst->id].nome, sizeof(lst[lst->id].nome), lst[lst->id].nome); 
    
    fprintf(stdout, "Quantidade Estoque: \n");
    scanf("%d", &lst[lst->id].estoque);
    
    printf("\n\n");
	system("pause");
	//Manda as variáveis para tratar alocação de memória.
	pos_inicioDaLista = list_add(lst[lst->id].estoque, lst[lst->id].nome, pos_inicioDaLista);
	
	//1-) Bkp recebe posição anterior.
	//2-) Posição inicial, recebe a prox Posição.
	//3-) Limpa a memória de Bkp.
	while(pos_inicioDaLista){
		if(pos_inicioDaLista->next){
			bkp = pos_inicioDaLista;
			pos_inicioDaLista = pos_inicioDaLista->next;
			free(bkp);
		}else{
			free(pos_inicioDaLista);
			pos_inicioDaLista = NULL;
			break;
		}
	}
	cadastraNoBancoDeDados(lst);
	return 1;
    
}

int pegaIdAtual(){
	FILE * verificaTxt;
	FILE * fileWrite;
	char nomeTxt[100];
	strcpy(nomeTxt, "c:\\HutCode\\banco\\cadastros.txt");
	if(verificaTxt = fopen(nomeTxt, "r")){
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

void excluirProduto(char id, char *nameTxt){
	FILE *fileRead;
	FILE *fileReadFuturo;
	FILE *fileBackup;
	FILE *fileAppend;
	int condicao = 0;
	char recebeRead = ' ', passaBackup = ' ';
	char recebeReadFuturo = ' ';

	
	fileAppend = fopen("c:\\HutCode\\banco\\backup.txt", "w");
	if((fileAppend = fopen("c:\\HutCode\\banco\\backup.txt", "w"))==NULL){
			fileAppend = fopen("c:\\HutCode\\banco\\backup.txt", "w");
			fclose(fileAppend);
			if((fileAppend = fopen("c:\\HutCode\\banco\\backup.txt","w"))==NULL){
				printf("\nNão foi possivel criar o arquivo de backup, contate o administrador do sistema.\n");
			}
	}
	fclose(fileAppend);
	
	fileReadFuturo = fopen(nameTxt, "r");
	fileRead = fopen(nameTxt, "r");
	fileAppend = fopen("c:\\HutCode\\banco\\backup.txt", "r+");
	
	recebeReadFuturo = fgetc(fileReadFuturo);
	while(recebeRead != EOF){
		if(recebeRead == '[' && recebeReadFuturo != id){
			fputc('[', fileAppend);
			while(recebeRead != EOF && recebeRead != '\n'){
				recebeRead = fgetc(fileRead);
				putc(recebeRead, fileAppend);
				recebeReadFuturo = fgetc(fileReadFuturo);
			}
				
		}else{
			if(recebeReadFuturo == id){
				while(recebeRead != '\n' && recebeRead != EOF){
					fputc(' ', fileAppend);
					recebeRead = fgetc(fileRead);
					recebeReadFuturo = fgetc(fileReadFuturo);				
				}
			}	
				
		}	
	
		fputc(recebeRead, fileAppend);
		recebeRead = fgetc(fileRead);
		recebeReadFuturo = fgetc(fileReadFuturo);
	}
	fclose(fileRead);	
	fclose(fileAppend);
	fclose(fileReadFuturo);
	
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
	fclose(fileReadFuturo);
	//Excluindo backup;
	remove("c:\\HutCode\\banco\\backup.txt");
}

void escolherExclusaoProduto(PRODUTO *lst){
	lst->id = pegaIdAtual()-1;
	char id_produto = ' ', stringID[10], decisaoExclusaoProduto;
	char nomeTxt[100], string = ' ';
	FILE * fileRead;
	
	system("cls");
	printf("\n========== EDITANDO PRODUTOS =============\n\n");
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
	printf("\n\n\nInforme a ID do produto que deseja Excluir\n> ");
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
				printf("\n========== EXCLUINDO PRODUTO =============\n\n");
				printf("\nID\t      Nome\t\t\tEstoque\n[");
				while(string != '\n' && string != EOF){
					if(string == ' '){
						printf(" ");
					}
					printf("%c", string);
					string = fgetc(fileRead);
					
				}
				fclose(fileRead);
				printf("\n\nTem certeza que deseja excluir esse produto ? [S/N]\n> ");
				scanf(" %c", &decisaoExclusaoProduto);
				if(decisaoExclusaoProduto == 's' || decisaoExclusaoProduto == 'S'){
					printf("\n\nAguarde a exclusão do produto...\n\n");
					sleep(2);	
					excluirProduto(id_produto, nomeTxt);
				}
				
				id_produto = 0;
			}
		}
		string = fgetc(fileRead);
	}			
	if(string == '\n'){
		printf("\n");
	}
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
	//Excluindo backup;
	remove("c:\\HutCode\\banco\\backup.txt");
}

void escolhaProdutoEditar(PRODUTO *lst){
	lst->id = pegaIdAtual()-1;
	char id_produto = ' ', stringID[10];
	char nomeTxt[100], string = ' ';
	FILE * fileRead;
	
	system("cls");
	printf("\n========== EDITANDO PRODUTOS =============\n\n");
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
    PRODUTO *lista = malloc(sizeof(PRODUTO));
    memset(lista,0,sizeof(lista));
    //Configura Diretório
    criaDiretorio();
    
    while(1){
    	int escolhaMenu = 0;
    	system("cls");
    	mostraHoraMinutos();
    	printf("\n            [MENU]\n");
        printf("\n[0] Sair.\n[1] Cadastrar um novo produto.\n[2] Listar Produtos Cadastrados.");
		printf("\n[3] Editar Produto\n[4] Excluir Produto\n > ");
        scanf("%d", &escolhaMenu);
        if(escolhaMenu == 0){
    		return 0;
		}else if(escolhaMenu == 1){
        	cadastraProduto(lista);
		}else if(escolhaMenu == 2 ){
			listaOsProdutos(lista);
		}else if(escolhaMenu == 3){
			escolhaProdutoEditar(lista);
		}else if(escolhaMenu == 4){
			escolherExclusaoProduto(lista);
		}
		
   	}


    return 0;
}
