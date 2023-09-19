#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAMANHO_VETOR 32

typedef struct contato{
    char nome[50];
    char email[50];
    char numero[30];
} Contato;

void inicializa_lista(Contato *lista_contatos){
    for(int i = 0; i <= TAMANHO_VETOR; i++){
        memset(lista_contatos[i].numero, '\0', 30);
    }
}

Contato cria_contato(){
    Contato novo_contato;
    printf("Insira o nome do contato:\n");
    scanf(" %[^\n]", novo_contato.nome);
    printf("Insira o número de contato de %s:\n", novo_contato.nome);
    scanf(" %[^\n]", novo_contato.numero);
    printf("Insira o email de %s:\n", novo_contato.nome);
    scanf(" %[^\n]", novo_contato.email);
    return(novo_contato);
}

int hash_function(int key, int probe){
    return(((key % TAMANHO_VETOR)+ probe) % TAMANHO_VETOR);
}

int concatenacao(char c[]){
    int key = 0, i = 0;
    while(c[i] != '\0'){
        key += c[i];
        i++; 
    } 
    return key;
}

int retorna_index_vazio(Contato *lista_contatos, int numero_conc){
    int index, probe = 0;
    while (1)
    {
        index = hash_function(numero_conc, probe);
        if ((strcmp(lista_contatos[index].numero, "\0")) == 0)
        {
            return(index);
        }

        if ((strcmp(lista_contatos[index].numero, "\0")) != 0)
        {
            probe++;
        }

        if (index > TAMANHO_VETOR)
        {
            index = ((TAMANHO_VETOR - index) * -1);
        }
    }
}

int retorna_index_comparacao(Contato *lista_contatos, int numero_conc, char *elemento_comparado){
    int index, probe = 0;
    while (1)
    {
        index = hash_function(numero_conc, probe);
        if ((strcmp(lista_contatos[index].numero, elemento_comparado)) == 0)
        {
            return(index);
        }

        if ((strcmp(lista_contatos[index].numero, elemento_comparado)) != 0)
        {
            probe++;
        }

        if (index > TAMANHO_VETOR)
        {
            index = ((TAMANHO_VETOR - index) * -1);
        }

        if(probe == TAMANHO_VETOR){
            return(-1);
        }
    }
}


void insere_contato(Contato *lista_contatos, Contato novo_contato){
    int novo_concatenado = concatenacao(novo_contato.numero);
    int index_vazio = retorna_index_vazio(lista_contatos, novo_concatenado);
    lista_contatos[index_vazio] = novo_contato;
}


void deleta_contato(Contato *lista_contatos){
    char numero_deleta[30];
    printf("Insira o número do contato que deseja deletar:\n");
    scanf(" %[^\n]", numero_deleta);
    int cont_conc = concatenacao(numero_deleta); 
    int index = retorna_index_comparacao(lista_contatos, cont_conc, numero_deleta);
    if (index != (-1))
    {
        strcpy(lista_contatos[index].numero, "\0");
        strcpy(lista_contatos[index].nome, "\0");
        strcpy(lista_contatos[index].email, "\0");
    }
    else{
        printf("Contato não cadastrado.\n");
    }
}


void imprime_contatos(Contato *lista_contatos){
    for(int i = 0; i <= TAMANHO_VETOR; i++){
        if(lista_contatos[i].numero[0] != '\0'){
            printf("Nome: %s\nNúmero: %s\nEmail: %s\n\n", lista_contatos[i].nome, lista_contatos[i].numero, lista_contatos[i].email);
        }
    }
}


void buscar_contato(Contato *lista_contatos){
    char numero_busca[30];
    printf("Insira o número do contato que deseja buscar:\n");
    scanf(" %[^\n]", numero_busca);
    int cont_conc = concatenacao(numero_busca);
    int index = retorna_index_comparacao(lista_contatos, cont_conc, numero_busca);
    if(index != (-1)){
        printf("Nome: %s\nNúmero: %s\nEmail: %s\n\n", lista_contatos[index].nome, lista_contatos[index].numero, lista_contatos[index].email);
    }
    else{
        printf("Contato não encontrado.\n");
    }
}

void edita_contato(Contato *lista_contatos)
{
    char numero_edita[30];
    int var_controle = 0, var_confirma;
    printf("Insira o número do contato que deseja editar:\n");
    scanf(" %[^\n]", numero_edita);
    int cont_conc = concatenacao(numero_edita);
    int index = retorna_index_comparacao(lista_contatos, cont_conc, numero_edita);
    if (index != -1)
    {
        printf("Qual alteração você deseja fazer?\n1)Nome\n2)Número\n3)Email\n4)Sair\n");
        while (var_controle != 4)
        {
            switch (var_controle)
            {
            case 1:
                char novo_nome[50];
                printf("Insira o novo nome para atual contato %s:\n.", lista_contatos[index].nome);
                scanf(" %[^\n]", novo_nome);
                printf("Você irá mudar o nome do contato de %s para %s, tem certeza disso?\n1)Sim\t2)Não\n", lista_contatos[index].nome, novo_nome);
                scanf("%i", &var_confirma);
                if (var_confirma == 1)
                {
                    strcpy(lista_contatos[index].nome, novo_nome);
                }

            case 2:
                char novo_numero[30];
                printf("Insira o novo número para o atual contato de %s:\n", lista_contatos[index].nome);
                scanf(" %[^\n]", novo_numero);
                printf("Você irá mudar o número de contato de %s para %s, tem certeza disso?\n1)Sim\t2)Não\n", lista_contatos[index].nome, novo_numero);
                scanf("%i", &var_confirma);
                if (var_confirma == 1)
                {
                    memset(lista_contatos[index].numero, '\0', 30);
                    int novo_numero_conc = concatenacao(novo_numero);
                    int novo_index = retorna_index_vazio(lista_contatos, novo_numero_conc);
                    strcpy(lista_contatos[novo_index].numero, novo_numero);
                    strcpy(lista_contatos[novo_index].nome, lista_contatos[index].nome);
                    strcpy(lista_contatos[novo_index].email, lista_contatos[index].email);
                    memset(lista_contatos[index].nome, '\0', 49);
                    memset(lista_contatos[index].email, '\0', 49);
                }

            case 3:
                char novo_email[50];
                printf("Insira o novo email para atual contato %s:\n.", lista_contatos[index].nome);
                scanf(" %[^\n]", novo_email);
                printf("Você irá mudar o email do contato de %s para %s, tem certeza disso?\n1)Sim\t2)Não\n", lista_contatos[index].nome, novo_email);
                scanf("%i", &var_confirma);
                if (var_confirma == 1)
                {
                    strcpy(lista_contatos[index].email, novo_email);
                }
            case 4:
                continue;
            }
        }
    }
    else
    {
        printf("Contato não encontrado.\n");
    }
}
