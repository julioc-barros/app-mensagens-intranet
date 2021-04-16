#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <conio.h>

typedef struct contas CONTAS;
struct contas{
	char ip [15];
	char usuario[10];
	char senha[10];
};

int main () {
	setlocale(LC_ALL, "");
	FILE *usuarios;
	usuarios = fopen("usuarios.dat","ab");
	CONTAS user;
	do{
		system("cls");
		fflush(stdin);
		printf("\nDigite o IP da máquina: ");
		gets(user.ip);
		
		fflush(stdin);
		printf("\nDigite o usuario: ");
		gets(user.usuario);
		
		fflush(stdin);
		printf("\nDigite a senha: ");
		gets(user.senha);
		
		fwrite(&user, sizeof(CONTAS),1,usuarios);
		
		printf("\nDeseja continuar (s/n)? ");
		
		
	}while (getche() == 's');
	fclose(usuarios);
}
