#define _DEFAULT_SOURCE
#define _DEFINE_SOURCE
#include <stdio.h>
#include "strutil.h"
#include <stdlib.h>
#include <string.h>

/* Funciones para el Split */
char *buffer_cargar(char *buffer, size_t largo){
	char *str = calloc(largo, sizeof(char));
	if(!str) return NULL;
	if(largo > 0){
		memcpy(str, buffer, largo);
	}
	return str;
}

char *buffer_crear(char *buff, size_t largo){
	if(buff) free(buff);
	char *buffer = calloc(largo, sizeof(char));
	if(!buffer) return NULL;
	return buffer;
}

char **strv_crear(const char *str, char sep, size_t largo_str){
	size_t largo_strv = 2;
	for(size_t i = 0; i <= largo_str; i++){
		if(str[i] == sep) largo_strv++;
	}
	char **strv = malloc(largo_strv*sizeof(char *));
	if(!strv) return NULL;
	return strv;
}

char **split(const char *str, char sep){ 
	size_t largo_str = strlen(str);
	char **strv = strv_crear(str, sep, largo_str);
	if(!strv) return NULL;

	char *buffer = buffer_crear(NULL, largo_str + 1);
	size_t k = 0, j = 0;
	for(size_t i = 0; i <= largo_str; i++){
		if(str[i] == sep || str[i] == '\0'){
			strv[k] = buffer_cargar(buffer, j + 1);
			buffer = buffer_crear(buffer, largo_str + 1);
			j = 0;
			k++;
		}else{
			buffer[j++] = str[i];
		}
	}
	free(buffer);
	strv[k] = NULL;
	return strv;
}

/* Funciones para Join */
size_t concatenar(char *buffer, char *str, size_t j){
	for(size_t i = 0; i < strlen(str); i++){
		buffer[j++] = str[i];
	}
	return j;
}

char *str_crear(char **strv){
	size_t largo_str = 1;
	if(strv){
		for(size_t i = 0; strv[i]; i++){
			largo_str += sizeof(strv[i]) / sizeof(char) + 1;
		}
	}
	char *str = calloc(largo_str + 1, sizeof(char));
	return str;
}

char *join(char **strv, char sep){
	char *str = str_crear(strv);
	size_t i = 0, j = 0;
	if(strv){
		while(strv[i] != NULL){
			j = concatenar(str, strv[i], j);
			i++;
			if(strv[i]){
				str[j++] = sep;
			}
		}
	}
	return str;
}
void free_strv(char *strv[]){
	for(size_t i = 0; strv[i] != NULL; i++){
		free(strv[i]);
	}
	free(strv);
}
