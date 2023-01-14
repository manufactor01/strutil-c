#include "strutil.h"
#include <string.h>
#include "pruebas_strutil.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // isatty
#define ANSI_COLOR_LGH_RED	   "\x1b[1m\x1b[31m"
#define ANSI_COLOR_LGH_GREEN   "\x1b[1m\x1b[32m"
#define ANSI_COLOR_LGH_WHITE 	""
#define ANSI_COLOR_RESET   "\x1b[0m"

void print_title(char *mensaje){
	if(isatty(1) == 1) printf(ANSI_COLOR_LGH_RED);
	printf("%s\n", mensaje);
	if(isatty(1) == 1) printf(ANSI_COLOR_RESET);
}

void print_split(char **strv){
	size_t i = 0;
	printf("[");
	while(strv[i]){
		printf("\"%s\"", strv[i]);
		i++;
		if(strv[i]) printf(",");
	}
	printf("]\n");
}

void print_join(char *str){
	printf("\"%s\"\n", str);
}

void pruebas_split(){
	print_title("INICIO DE PRUEBAS SPLIT");
	
	/* Defino mis casos borde */
	char **strv1 = split("abc,,def", ',');
	char **strv2 = split("abc,def,", ',');
	char **strv3 = split(",abc,def", ',');
	char **strv4 = split("", ',');
	char **strv5 = split(",", ',');
	char **strv6 = split(",,,,,,,,", '\0');
	char **strv7 = split("1,,,,5", ',');

	print_split(strv1);
	print_split(strv2);
	print_split(strv3);
	print_split(strv4);
	print_split(strv5);
	print_split(strv6);
	print_split(strv7);

	/* Libero el espacio reservado para los arreglos */
	free_strv(strv1);
	free_strv(strv2);
	free_strv(strv3);
	free_strv(strv4);
	free_strv(strv5);
	free_strv(strv6);
	free_strv(strv7);
}

char *join_crear(char *str, char sep, char sep_new){
	char **strv = split(str, sep);
	char *str_new = join(strv, sep_new);
	free_strv(strv);
	return str_new;
}

/*	
	INICIO DE PRUEBAS JOIN	*/

void pruebas_join(){
	print_title("INICIO DE PRUEBAS JOIN");

	/* Declaro las variables a utilizar */
	char *str1 = join_crear("", ',', '.');
	char *str2 = join_crear(",", ',', '.');
	char *str3 = join_crear("abc", '\0', ',');
	char *str4 = join_crear("", '\0', ',');
	char *str5 = join_crear(",,,,,,", '\0', ',');

	/* Pruebo que join funciona correctamente */
	char **str_null = {NULL};
	char *str6 = join(str_null, ',');

	print_join(str1);
	print_join(str2);
	print_join(str3);
	print_join(str4);
	print_join(str5);
	print_join(str6);

	/* Libero las cadenas */
	free(str1);
	free(str2);
	free(str3);
	free(str4);
	free(str5);
	free(str6);
}

char *str_crear_10000(char sep, size_t n){
	char *str = calloc(n + 1, sizeof(char));
	if(!str) return NULL;
	for(size_t i = 0; i < n; i++){
		str[i] = sep;
	}
	return str;
}

void pruebas_join_10000(){
	size_t n = 10000;
	char *str = str_crear_10000(',', n);
	char **strv = split(str, ',');
	char *str_new = join(strv, '.');
	free_strv(strv);
	free(str);
	free(str_new);
}

void pruebas_strutil(){
	pruebas_split();
	pruebas_join();	
	pruebas_join_10000();
}