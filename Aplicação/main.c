#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <conio.h>
/*
** CENTRO UNIVERSIT�RIO DOS GUARARAPES - UNIFG
** T�cnicas de Programa��o
** Atividade Pr�tica Supervisionada - APS
** Autores:
** 	Erik Nathan - 202002721
** 	J�lio Cesar - 202002088
**	Arthur Mandel - 2020030300
**
** Vers�o: 1.2
** Programa de envio de mensagens pela intranet de uma empresa atrav�s de login.
*/

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

//Estruturas de usuarios
typedef struct contas CONTAS;
struct contas{
	char ip[15];
	char usuario[10];
	char senha[10];
};
CONTAS user;

//Estrutura de mensagens
typedef struct mensagem MENSAGEM;
struct mensagem{
	char ip[15];
	char assunto[50];
	char msg[100];
};
MENSAGEM msgv[1000];

//Tela de login
void login(){
//	limpando tela
	system("cls");
	FILE *usuarios;
	
//	declarando
	int i;
	char req_usuario[10];
	char req_senha[10];
	char errologin[10];
	
//	tela 
	printf("\nPrograma de Mensagens\n");
	
//	pegando usuario
	printf("\nLogin: ");
	fflush(stdin);
	gets(req_usuario);
	
//	Pegando senha
	printf("\nSenha: ");
	fflush(stdin);
	gets(req_senha);
	
//	Abrindo arquivo
	usuarios = fopen("usuarios.dat","rb");
	
//	Verificando se tem acesso ao arquivo
	if (usuarios == NULL){
		printf("\nArquivo de usuarios n�o encontrado.\n");
		printf("Por favor, cadastre usuarios primeiro.\n\n");
		system("pause");
	}
	else {
//		Autentica��o
		while(fread(&user, sizeof(CONTAS), 1, usuarios)==1){
			if (strcmp(req_usuario, user.usuario )==0 && strcmp(req_senha, user.senha)==0){
//				redirecionando ao menu
				menu();
			}
		}
		//	Fechando o arquivo
		fclose(usuarios);
//		redirecionando ao login
		login();
	};
	

};

//Menu de op��es
void menu(){
	int op;
	do{
//		Op��es na tela
		system("cls");
		printf("\n### MENU ###\n");
		printf("\n1. Enviar mensagem");
		printf("\n2. Listar mensagens enviadas");
		printf("\n3. Apagar arquivo de mensagens enviadas");
		printf("\n0. Sair\n");
		printf("\n	### Digite apenas n�meros ou ser� deslogado ###	\n");
		
//		Recebendo a Op��o
	
		printf("\nEscolha uma Op��o: ");
		scanf("%d",&op);
		
	switch (op){
		
//				Op��o invalida
		default:
			system("cls");
			printf("\nEscolha uma op��o v�lida.\n\n");	
			system("pause");
			op = 0;
			
//				Enviar mensagem
		case 1:
			enviar();
			
//				Listar mensagens apagadas
		case 2:
			listar();
			
//				apagar arquivo de mensagens enviadas
		case 3:
			apagar();
			
//				sair
		case 0:
			login();

	}
	}while(op != 0);
	menu();
}

//enviar mensagem
void enviar(){
	int i;
	FILE *msgm;
	msgm = fopen ("mensagens.dat", "ab"); 
		if(msgm == NULL){
			printf("Arquivo n�o encontrado.");
		}
		else{
			do{
				system("cls");
				printf("\nOl�, %s, seja bem vindo!\n",user.usuario);

				strcpy(msgv[i].ip,user.ip);

				fflush(stdin);
				printf("\nDigite o assunto da mensagem: ");
				gets(msgv[i].assunto);
				
				fflush(stdin);
				printf("\nDigite sua mensagem aqui: ");
				gets(msgv[i].msg);
				
				fwrite(&msgv[i], sizeof(MENSAGEM), 1,msgm);
				
				printf("\nDeseja escrever outra mensagem (s / n) ?\n");
				
			}while(getche() == 's');
			fclose(msgm);
			menu();
		}	
}

//listar mensagem
void listar(){
	int i;
	int cm ;
	FILE *msgm;
	msgm = fopen("mensagens.dat", "rb");
	
	if(msgm == NULL){
		system("cls");
		printf("\n	Arquivo est� vazio.\n\nTente novamente ap�s enviar uma mensagem.\n\n\n");
		system("pause");
		menu();
	}
	else{
		system("cls");
		printf("LISTA DE MENSAGENS ENVIADAS\n");
		while( fread(&msgv[i], sizeof(MENSAGEM), 1, msgm)==1){
			
			fflush(stdin);
			printf("\nN� -> %d�\n",cm+1);
			printf("\nIP.....: %s",msgv[i].ip);
			printf("\nASSUNTO: %s", msgv[i].assunto);
			printf("\nMENSAGEM: %s", msgv[i].msg);
			printf("\n-----------------------------------\n\n");
			
			cm++;
		}
		fclose(msgm);
		system("pause");
		menu();
	}
}

//Apagar mensagens
void apagar(char *mensagem){
	int resposta;
	
	do{
		system("cls");
		printf("\nEXCLUIR BACKUP DE MENSAGENS\n");
		printf("\nDeseja excluir o arquivo 'mensagens.dat' (1-Sim/0-N�o) ? ");
		scanf("%d",&resposta);
		
		switch (resposta){
			case 0:
				system("cls");
				printf("\nRemo��o cancelada.\n\n");
				system("pause");
				menu();				
			case 1:
				if(remove("mensagens.dat")==0){
					printf("\nArquivo apagado com sucesso.\n\n");
					system("pause");
					menu();
				}
				else{
					system("cls");
					printf("\n	Arquivo n�o encontrado.\nTente novamente ap�s enviar uma mensagem.\n\n");
					system("pause");
					menu();
				}
			default:
				printf("\nOp��o invalida\n\n");
				system("pause");
				break;
			}
	}while(resposta != 0);

}
//MAIN
int main() {
	setlocale(LC_ALL, "");
//	Come�ando na tela de login
	login();
}





