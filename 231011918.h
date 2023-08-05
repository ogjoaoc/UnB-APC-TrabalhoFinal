/******************************************************************************
Aluno(a): João Carlos Gonçalves de Oliveira Filho
Matrícula: 231011918
Declaro que eu sou o(a) autor(a) deste trabalho e que o código não foi copiado
de outra pessoa nem repassado para alguém. Estou ciente de que poderei sofrer
penalizações na avaliação em caso de detecção de plágio.
*******************************************************************************/

#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <ctype.h>

// Definições da biblioteca.
#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

// Lista de definições para opções do menu.
#define CONSULTAR_MINIUSINA 1
#define CONSULTAR_CONSUMIDOR 2
#define LISTAR_MINIUSINAS 3
#define LISTAR_MINIUSINAS_OPERACAO_DECRESCENTE 4
#define LISTAR_RAS_ORDEM_DESCRESCENTE_QUANTIDADE_MINIUSINAS 5
#define LISTAR_RAS_ORDEM_CRESCENTE_CONTRATOS 6
#define LISTAR_RAS_ORDEM_DESCRESCENTE_CAPACIDADE_GERACAO 7
#define LISTAR_RAS_ORDEM_DESCRESCENTE_PERCENTUAL_ENERGIA_DISPONIVEL 8
#define SAIR 9

// Lista de definições para os tamanhos dos dados da miniusina.
#define TAM_MAX_CNPJ 19
#define TAM_MAX_NOME_MINIUSINA 100
#define TAM_MAX_ENERGIA_MINIUSINA 100
#define TAM_MAX_ID_RA_MINIUSINA 99
#define TAM_MAX_STATUS_MINIUSINA 10

// Lista de definições para os tamanhos dos dados dos contratos.
#define TAM_MAX_ID_CONTRATO 3
#define TAM_MAX_ID_CONSUMIDOR 19
#define TAM_MAX_DATA_CONTRATO 20

// Lista de definições para tamanho dos dados do consumidores.
#define TAM_MAX_ID_CONSUMIDOR 19
#define TAM_MAX_NOME_CONSUMIDOR 100
#define TAM_MAX_RA_CONSUMIDOR 100

// Definição do registro para representar um tipo miniusina no software.
struct miniusina {
    char cnpj[TAM_MAX_CNPJ];
    char nome[TAM_MAX_NOME_MINIUSINA];
    char energia[TAM_MAX_ENERGIA_MINIUSINA];
    char idra[TAM_MAX_ID_RA_MINIUSINA];
    int id_ra; // ID_RA em inteiro para comparar com o arquivo de RAs nos itens 7 e 8.
    char status[TAM_MAX_STATUS_MINIUSINA];
    float capacidade;
};

// Definição do registro para representar um tipo contrato no software.
struct contratos {
    char idcontrato[TAM_MAX_ID_CONTRATO];
    char idconsumidor[TAM_MAX_ID_CONSUMIDOR];
    char energia[TAM_MAX_ENERGIA_MINIUSINA];
    char cnpj[TAM_MAX_CNPJ];
    char datacontrato[TAM_MAX_DATA_CONTRATO];
    float energia_contratada; // Energia contratada utilizada no item 8 do menu.
};

// Definição do registro para representar um tipo ra no software.
struct ra {
    char idra[TAM_MAX_ID_RA_MINIUSINA];
    char nome_ra[TAM_MAX_NOME_CONSUMIDOR];
    int quantidade_de_miniusinas;
    int id_ra; // ID_RA em inteiro para comparar com o arquivo de miniusinas e consumidores.
    int quantidade_contratos;
    float capacidade_total;
    int energia_contratada;
    float taxa_contratada_ra;
};

// Definição do registro para representar um tipo consumidor no software.
struct consumidor {
    char id_consumidor[TAM_MAX_ID_CONSUMIDOR];
    char nome[TAM_MAX_NOME_CONSUMIDOR];
    char idra[TAM_MAX_ID_RA_MINIUSINA];
    int id_ra; // ID_RA em inteiro para comprar com o arquivo de RAs no item 6.
};

// Função para remover caracteres não numéricos de uma string.
void removerNaoNumericos(char * string) {
    int tamanho_da_string = strlen(string); // Calcula o tamanho da string.
    int posicao = 0; // Variável para controlar a posição dos caracteres da string.
    for (int i = 0; i < tamanho_da_string; i++) { // até o índice tamanho_da_string - 1.
        if (isdigit(string[i])) { // Verifica se o caractere atual é numérico com isdigit (ctype). https://www.programiz.com/c-programming/library-function/ctype.h/isdigit
            string[posicao++] = string[i]; // Copia o caractere numérico para a posição correta na string modificada.
        }
    }
    string[posicao] = '\0'; // Adiciona o caractere nulo na string modificada para indicar o fim da string.
}

// Função de validação de CPF.
int validarCPF(const char * cpf) {
    // Remover caracteres não numéricos (.-/).
    char cpfNumerico[12];
    strcpy(cpfNumerico, cpf);
    removerNaoNumericos(cpfNumerico);

    int digitos[11];
    int soma = 0, digito1, digito2;
    size_t i; // tipo de dados inteiro sem sinal.

    // Verifica se a quantidade de dígitos está correta.
    if (strlen(cpfNumerico) != 11) {
        return 0;
    }

    // Extrai os dígitos do CPF.
    for (i = 0; i < 11; i++) {
        digitos[i] = cpfNumerico[i] - '0';
    }

    // Calcula o primeiro dígito verificador.
    for (int i = 0, peso = 10; i < 9; i++) {
        soma += digitos[i] * peso--;
    }
    digito1 = (soma * 10) % 11;

    if (digito1 == 10) {
        digito1 = 0;
    }

    if (digitos[9] != digito1) {
        return 0; // CPF inválido.
    }

    // Calcula o segundo dígito verificador.
    soma = 0;
    for (int i = 0, peso = 11; i < 10; i++) {
        soma += digitos[i] * peso--;
    }
    digito2 = (soma * 10) % 11;

    if (digito2 == 10) {
        digito2 = 0;
    }

    if (digitos[10] != digito2) {
        return 0; // CPF inválido.
    }

    return 1; // CPF válido.
}

// Função de validação de CNPJ.
int validarCNPJ(const char * cnpj) {
    // Remover caracteres não numéricos (.-/).
    char cnpjNumerico[15];
    strcpy(cnpjNumerico, cnpj);
    removerNaoNumericos(cnpjNumerico);

    int digitos[14];
    int soma = 0, digito1, digito2;
    size_t i;

    // Verifica se a quantidade de dígitos está correta.
    if (strlen(cnpjNumerico) != 14) {
        return 0;
    }

    // Extrai os dígitos do CNPJ
    for (i = 0; i < 14; i++) {
        digitos[i] = cnpjNumerico[i] - '0';
    }

    // Calcula o primeiro dígito verificador.
    for (int i = 0, peso = 5; i < 12; i++) {
        soma += digitos[i] * peso--;
        if (peso < 2) {
            peso = 9;
        }
    }
    digito1 = (soma % 11 < 2) ? 0 : (11 - soma % 11);

    if (digitos[12] != digito1) {
        return 0; // CNPJ inválido.
    }

    // Calcula o segundo dígito verificador.
    soma = 0;
    for (int i = 0, peso = 6; i < 13; i++) {
        soma += digitos[i] * peso--;
        if (peso < 2) {
            peso = 9;
        }
    }
    digito2 = (soma % 11 < 2) ? 0 : (11 - soma % 11);

    if (digitos[13] != digito2) {
        return 0; // CNPJ inválido.
    }

    return 1; // CNPJ válido.
}

// Procedimento para consultar miniusinas cadastradas. (Opção 1).
void consultar_miniusina_cadastrada() {

    // Declaração de variáveis.
    FILE * arquivo_miniusinas;
    struct miniusina lista_miniusinas_cadastradas;
    char entrada_id[TAM_MAX_CNPJ];
    int encontrei_miniusina = 0;

    FILE * arquivo_contratos;
    struct contratos lista_contratos_cadastrados;
    int encontrei_contrato = 0;

    // Solicitar entrada para o usuário.
    printf("Digite o cnpj a ser consultado: ");
    scanf(" %[^\n]", entrada_id);

    // Remove caracteres não numéricos.
    removerNaoNumericos(entrada_id);

    if (strlen(entrada_id) != 14) {
        printf("\nEntrada incorreta (Digite apenas um CNPJ).\n");
        return;
    }

    // Validar CPF ou CNPJ.
    if (strlen(entrada_id) == 11) {
        int resultado_cpf = validarCPF(entrada_id);
        if (resultado_cpf) {
            printf("\nCPF válido.\n");
        } else {
            printf("\nCPF inválido.\n");
        }
    } else {
        int resultado_cnpj = validarCNPJ(entrada_id);
        if (resultado_cnpj) {
            printf("\nCNPJ válido.\n");
        } else {
            printf("\nCNPJ inválido.\n");
        }
    }

    // Abrir o arquivo das miniusinas.

    arquivo_miniusinas = fopen("miniusinas.csv", "r");

    // Verifica se conseguiu abrir o arquivo.

    if (arquivo_miniusinas != NULL) {
        char primeira_linha[1000];
        fscanf(arquivo_miniusinas, "%[^\n]\n", primeira_linha);
        while (!feof(arquivo_miniusinas)) {
            // Leitura do arquivo.
            fscanf(arquivo_miniusinas, "%[^;];%[^;];%[^;];%[^;];%[^\n]\n",
                lista_miniusinas_cadastradas.cnpj,
                lista_miniusinas_cadastradas.nome,
                lista_miniusinas_cadastradas.energia,
                lista_miniusinas_cadastradas.idra,
                lista_miniusinas_cadastradas.status);

            // Remover pontuações dos dados do arquivo.

            char miniusina_cnpj_original[TAM_MAX_CNPJ];
            strcpy(miniusina_cnpj_original, lista_miniusinas_cadastradas.cnpj); // Copia o cnpj lido no arquivo em uma nova variável auxiliar.
            removerNaoNumericos(lista_miniusinas_cadastradas.cnpj); // Remove os não numéricos do cnpj lido.

            // Caso o cnpj inserido pelo usuário seja igual ao do arquivo, mostrar na tela dados correspondentes.
            if (strcmp(entrada_id, lista_miniusinas_cadastradas.cnpj) == 0) { // Compara o CNPJ inserido pelo usuário já validado com o cnpj do arquivo sem não numéricos.

                printf("\nCnpj: %s\n", miniusina_cnpj_original);
                printf("Nome: %s\n", lista_miniusinas_cadastradas.nome);
                printf("Energia: %s kWh\n", lista_miniusinas_cadastradas.energia);
                printf("ID_RA: %s\n", lista_miniusinas_cadastradas.idra);
                printf("Status: %s\n\n", lista_miniusinas_cadastradas.status);
                encontrei_miniusina = 1;

            }
        }
        // Caso não tenha encontrado nenhuma miniusina com o cnpj inserido pelo usuário.
        if (encontrei_miniusina == 0) {
            printf("\nNão foi encontrada nenhuma miniusina com o cnpj %s.\n\n", entrada_id);
        }

    } else {
        // Caso não tenha conseguido abrir o arquivo...
        printf("\nNão foi possível abrir o arquivo de miniusinas.\n\n");
    }

    // Abrir o Arquivo de contratos

    arquivo_contratos = fopen("contratos.csv", "r");

    // Verifica se conseguiu abrir o arquivo
    if (arquivo_contratos != NULL) {

        while (!feof(arquivo_contratos)) {
            // Leitura do arquivo 
            fscanf(arquivo_contratos, "%[^;];%[^;];%[^;];%[^;];%[^\n]\n",
                lista_contratos_cadastrados.idcontrato,
                lista_contratos_cadastrados.idconsumidor,
                lista_contratos_cadastrados.cnpj,
                lista_contratos_cadastrados.datacontrato,
                lista_contratos_cadastrados.energia);

            char contrato_cnpj_original[TAM_MAX_CNPJ];
            strcpy(contrato_cnpj_original, lista_contratos_cadastrados.cnpj); // Copia o CNPJ lido no arquivo em uma nova variável auxiliar.
            removerNaoNumericos(lista_contratos_cadastrados.cnpj); // Remove os não numéricos do CNPJ lido no arquivo.

            // Caso o cnpj inserido pelo usuário tenha algum contrato vinculado no arquivo de contratos, mostrar os dados na tela.
            if (strcmp(entrada_id, lista_contratos_cadastrados.cnpj) == 0) { // Comparação entre o CNPJ digitado pelo usuário e o CNPJ lido no arquivo sem os não numéricos.
                printf("ID Contrato: %s\n", lista_contratos_cadastrados.idcontrato);
                printf("ID Consumidor: %s\n", lista_contratos_cadastrados.idconsumidor);
                printf("Data inicio contrato: %s\n", lista_contratos_cadastrados.datacontrato);
                printf("Energia Contratada: %s\n\n", lista_contratos_cadastrados.energia);
                encontrei_contrato = 1;
            }
        }
        // Caso não tenha encontrado nenhum contrato com o CNPJ inserido pelo usuário.
        if (encontrei_contrato == 0) {
            printf("Não foi encontrado nenhum contrato com o CNPJ %s.\n", entrada_id);
        }
    } else {
        // Caso não tenha conseguido abrir o arquivo dos contratos.
        printf("\nNão foi possível abrir o arquivo de contratos.\n");
    }

    fclose(arquivo_contratos);
    fclose(arquivo_miniusinas);

}

// Procedimento para consultar consumidores cadastrados. (Opção 2)
void consultar_consumidor_cadastrado() {

    // Declaração de variáveis e uso de ponteiros.
    FILE * arquivo_consumidor;
    struct consumidor consumidor_cadastrado;
    char entrada_id[TAM_MAX_CNPJ];
    int encontrei_consumidor = 0;

    FILE * arquivo_contratos;
    struct contratos contrato_cadastrado;
    int encontrei_contrato = 0;

    // Solicita o CPF ou CNPJ ao usuário.
    printf("Digite o CNPJ ou CPF a ser consultado: ");
    scanf(" %[^\n]", entrada_id);

    // Remove caracteres não numéricos (.-/).
    removerNaoNumericos(entrada_id);

    // Verifica se o tamanho da entrada é válido.

    if (strlen(entrada_id) != 11 && strlen(entrada_id) != 14) {
        printf("\nErro na entrada (Digite apenas um CPNJ ou CPF).\n");
        return;
    }

    // Validar CPF ou CNPJ.

    if (strlen(entrada_id) == 11) {
        int resultado_cpf = validarCPF(entrada_id);
        if (resultado_cpf) {
            printf("\nCPF correto.\n");
        } else {
            printf("\nCPF incorreto.\n");
        }
    } else {
        int resultado_cnpj = validarCNPJ(entrada_id);
        if (resultado_cnpj) {
            printf("\nCNPJ correto.\n");
        } else {
            printf("\nCNPJ incorreto.\n");
        }
    }

    // Abertura do arquivo.

    arquivo_consumidor = fopen("consumidores.csv", "r");

    // Caso não tenha conseguido abrir o arquivo.

    if (arquivo_consumidor != NULL) {

        // Loop para percorrer o arquivo até o final.

        while (!feof(arquivo_consumidor)) {

            // Leitura das informações do consumidor.

            fscanf(arquivo_consumidor, "%[^;];%[^;];%[^\n]\n",
                consumidor_cadastrado.id_consumidor,
                consumidor_cadastrado.nome,
                consumidor_cadastrado.idra);

            // Remover pontuações dos dados do arquivo.
            char idconsumidor_original[TAM_MAX_CNPJ];
            strcpy(idconsumidor_original, consumidor_cadastrado.id_consumidor);
            removerNaoNumericos(consumidor_cadastrado.id_consumidor);

            // Verifica se o ID do consumidor é igual à entrada (Comparação de strings). https://www.tutorialspoint.com/c_standard_library/c_function_strcmp.htm

            if (strcmp(entrada_id, consumidor_cadastrado.id_consumidor) == 0) {
                printf("\n\nID do consumidor: %s\n", idconsumidor_original);
                printf("Nome: %s\n", consumidor_cadastrado.nome);
                printf("ID_RA: %s\n", consumidor_cadastrado.idra);
                encontrei_consumidor = 1;
            }
        }

        // Caso tenha encontrado o consumidor.

        if (encontrei_consumidor == 0) {
            printf("\nNenhum consumidor encontrado com o ID %s.\n\n", entrada_id);
        }
    } else {
        printf("\nNão foi possível abrir o arquivo de consumidores.\n\n");
    }

    // Abertura do arquivo.

    arquivo_contratos = fopen("contratos.csv", "r");

    // Caso não tenha conseguido abrir o arquivo.

    if (arquivo_contratos != NULL) {

        // Loop para percorrer o arquivo até o final.

        while (!feof(arquivo_contratos)) {

            // Leitura das informações do contrato do arquivo.

            fscanf(arquivo_contratos, "%[^;];%[^;];%[^;];%[^;];%[^\n]\n",
                contrato_cadastrado.idcontrato,
                contrato_cadastrado.idconsumidor,
                contrato_cadastrado.cnpj,
                contrato_cadastrado.datacontrato,
                contrato_cadastrado.energia);

            // Remover pontuações dos dados do arquivo.

            char idconsumidor_original[TAM_MAX_CNPJ];
            strcpy(idconsumidor_original, contrato_cadastrado.idconsumidor);
            removerNaoNumericos(contrato_cadastrado.idconsumidor);

            // Verifica se o ID do consumidor é igual à entrada (Comparação de Strings).

            if (strcmp(entrada_id, contrato_cadastrado.idconsumidor) == 0) {
                printf("\nID Contrato: %s\n", contrato_cadastrado.idcontrato);
                printf("ID Consumidor: %s\n", idconsumidor_original);
                printf("Cnpj da miniusina: %s\n", contrato_cadastrado.cnpj);
                printf("Data de início do contrato: %s\n", contrato_cadastrado.datacontrato);
                printf("Energia Contratada: %s kWh\n\n", contrato_cadastrado.energia);
                encontrei_contrato = 1;
            }
        }

        // Caso não tenha encontrado o arquivo.

        if (encontrei_contrato == 0) {
            printf("\nNenhum contrato encontrado com o ID %s.\n", entrada_id);
        }
    } else {
        printf("\nNão foi possível abrir o arquivo de contratos.\n");
    }

    // Fechar arquivos.

    fclose(arquivo_consumidor);
    fclose(arquivo_contratos);
}

// Procedimento para buscar e mostrar na tela os dados das miniusinas cadastradas. (Opção 3)
void listar_miniusinas() {

    // Declaração de variáveis.

    FILE * arquivo_miniusinas;
    struct miniusina miniusina_lida;
    // Abrir o arquivo.
    arquivo_miniusinas = fopen("miniusinas.csv", "r");

    // Verifica se conseguiu abrir o arquivo.

    if (arquivo_miniusinas != NULL) {
        char primeira_linha[1000];
        fscanf(arquivo_miniusinas, "%[^\n]\n", primeira_linha);
        while (!feof(arquivo_miniusinas)) {

            // Leitura dos dados do arquivo.

            fscanf(arquivo_miniusinas, "%[^;];%[^;];%[^;];%[^;];%[^\n]\n",
                miniusina_lida.cnpj,
                miniusina_lida.nome,
                miniusina_lida.energia,
                miniusina_lida.idra,
                miniusina_lida.status);

            // Mostrar na tela os dados lidos.

            printf("Cnpj: %s\n", miniusina_lida.cnpj);
            printf("Nome: %s\n", miniusina_lida.nome);
            printf("Energia: %s kWh\n", miniusina_lida.energia);
            printf("ID_RA: %s\n", miniusina_lida.idra);
            printf("Status: %s\n\n", miniusina_lida.status);

        }
    } else {

        // Caso não tenha conseguido abrir o arquivo.

        printf("\nErro, não foi possível abrir o arquivo de miniusinas.\n");
    }

}

// Algoritmo de ordenação em quantidade de energia das miniusinas (decrescente). 
void SortMiniusinasPorCapacidadeDecrescente(struct miniusina lista_miniusinas[], int quantidade_miniusinas) { // Recebe uma lista e seu resectivo tamanho.
    int i, j, auxiliar; // Declaração de variáveis.
    struct miniusina temp; // Variável temporária do tipo miniusina.
    for (i = 0; i < quantidade_miniusinas - 1; i++) { // Início do loop que percorre a lista de miniusinas.
        auxiliar = i; // Pegue o índice do elemento com maior energia no momento.
        for (j = i + 1; j < quantidade_miniusinas; j++) { // Início do loop interno para verificação e substituição.
            if (strcmp(lista_miniusinas[j].energia, lista_miniusinas[auxiliar].energia) > 0) { // Compara as energias entre as posições.
                auxiliar = j; // Atualização do valor indicando posição de maior energia.
            }
        }
        // Troca de posições.
        if (auxiliar != i) { // se foi encontrada uma miniusina com energia maior do que a miniusina atual (troca).
            temp = lista_miniusinas[i];
            lista_miniusinas[i] = lista_miniusinas[auxiliar];
            lista_miniusinas[auxiliar] = temp;
        }
    }
}

// Procedimento para listar as miniusinas em ordem decrescente de energia. (Opção 4)
void listar_miniusinas_ordenadas_por_capacidade_decrescente() {

    // Declaração de variáveis.

    FILE * arquivo_miniusinas;
    struct miniusina lista_miniusinas[12];
    FILE * arquivo_ras;
    struct ra ra_lida;

    // Abertura do arquivo.

    arquivo_miniusinas = fopen("miniusinas.csv", "r");

    // Caso não tenha conseguido abrir o arquivo.

    if (arquivo_miniusinas != NULL) {
        char primeira_linha[1000];
        fscanf(arquivo_miniusinas, "%[^\n]\n", primeira_linha);
        int quantidade_miniusinas = 0;

        while (!feof(arquivo_miniusinas)) // Leitura do arquivo de miniusinas até o final.
        {
            fscanf(arquivo_miniusinas, "%[^;];%[^;];%[^;];%[^;];%[^\n]\n", // Armazenar os dados da miniusina nos campos da lista.
                lista_miniusinas[quantidade_miniusinas].cnpj,
                lista_miniusinas[quantidade_miniusinas].nome,
                lista_miniusinas[quantidade_miniusinas].energia,
                lista_miniusinas[quantidade_miniusinas].idra,
                lista_miniusinas[quantidade_miniusinas].status);

            quantidade_miniusinas++; // Conforme a leitura de informações, incrementar a contagem de miniusinas.
        }

        // Chamar a função selectionSort para ordenar a lista de miniusinas por energia em ordem decrescente.
        SortMiniusinasPorCapacidadeDecrescente(lista_miniusinas, quantidade_miniusinas);

        // Início do laço para impressão de informações da miniusina.
        for (int i = 0; i < quantidade_miniusinas; i++) {
            printf("\nCnpj: %s\n", lista_miniusinas[i].cnpj);
            printf("Nome: %s\n", lista_miniusinas[i].nome);
            printf("Energia: %s kWh\n", lista_miniusinas[i].energia);
            printf("Status: %s\n", lista_miniusinas[i].status);

            arquivo_ras = fopen("ra.csv", "r"); // Abertura do arquivo de RAs.

            if (arquivo_ras != NULL) // Verifica se conseguiu abrir o arquivo.
            {
                char primeira_linha_2[1000];
                fscanf(arquivo_ras, "%[^\n]\n", primeira_linha_2);
                while (!feof(arquivo_ras)) // Enquanto percorre o arquivo das RAs, armazenar nome e ID de cada RA.
                {
                    fscanf(arquivo_ras, "%[^;];%[^\n]\n",
                        ra_lida.idra,
                        ra_lida.nome_ra);

                    if (strcmp(lista_miniusinas[i].idra, ra_lida.idra) == 0) // Comparação entre o ID da RA no arquivo de miniusinas e o ID do arquivo de RAs, com o objetivo de encontrar o respectivo Nome da RA de cada miniusina.
                    {
                        printf("Nome da Ra: %s\n\n", ra_lida.nome_ra);
                    }
                }
                fclose(arquivo_ras);
            }
        }

        fclose(arquivo_miniusinas);

    } // Caso não tenha conseguido abrir o arquivo.
    else {
        printf("Erro, nao foi possivel abrir o arquivo de miniusinas.\n");
    }
}

// Algoritmo de ordenação em quantidade de miniusinas em cada RA (decrescente).
void SortRasPorMiniusinasDecrescente(struct ra * ras, int quantidade_ras) {
    int i, j, auxiliar;
    struct ra temp;

    for (i = 0; i < quantidade_ras - 1; i++) {
        auxiliar = i;
        for (j = i + 1; j < quantidade_ras; j++) {
            if (ras[j].quantidade_de_miniusinas > ras[auxiliar].quantidade_de_miniusinas) {
                auxiliar = j;
            }
        }

        if (auxiliar != i) {
            temp = ras[i];
            ras[i] = ras[auxiliar];
            ras[auxiliar] = temp;
        }
    }
}

// Procedimento para listar as RAs em ordem decrescente de quantidade de miniusinas. (Opção 5)
void listar_ras_ordenadas_por_miniusinas_decrescente() {

    FILE * arquivo_miniusinas;
    FILE * arquivo_ras;
    struct miniusina miniusina_lida;
    struct ra lista_ras[35];
    int quantidade_ras = 0; // Variável para contar a quantidade de RAs.

    // Abertura dos arquivos
    arquivo_miniusinas = fopen("miniusinas.csv", "r");
    arquivo_ras = fopen("ra.csv", "r");

    if (arquivo_miniusinas != NULL && arquivo_ras != NULL) {
        char primeira_linha_miniusinas[1000];
        fscanf(arquivo_miniusinas, "%[^\n]\n", primeira_linha_miniusinas);
        char primeira_linha[1000];
        fscanf(arquivo_ras, "%[^\n]\n", primeira_linha);

        // Inicializa a quantidade de miniusinas de cada RAS como 0 por meio do loop.
        for (int i = 0; i < 35; i++) {
            lista_ras[i].quantidade_de_miniusinas = 0;
        }

        // Leitura das informações das miniusinas e contagem da quantidade por RAS.
        while (fscanf(arquivo_miniusinas, "%[^;];%[^;];%[^;];%[^;];%[^\n]\n",
                miniusina_lida.cnpj,
                miniusina_lida.nome,
                miniusina_lida.energia,
                miniusina_lida.idra,
                miniusina_lida.status) == 5) {
            int i;
            for (i = 0; i < quantidade_ras; i++) { // Inicialização de um loop para comparar e verificar a miniusina lida e identificar sua respectiva RA.
                if (strcmp(miniusina_lida.idra, lista_ras[i].idra) == 0) {
                    lista_ras[i].quantidade_de_miniusinas++; // Incrementa a quantidade de miniusinas da sua respectiva RA.
                    break;
                }
            }

            if (i == quantidade_ras) { // Verificação se o loop interno percorreu todas as RAs encontradas até o momento e não encontrou uma correspondência para a miniusina lida.
                strcpy(lista_ras[quantidade_ras].idra, miniusina_lida.idra);
                lista_ras[quantidade_ras].quantidade_de_miniusinas = 1;
                quantidade_ras++;
            }
        }

        // Leitura dos nomes das RAS.
        rewind(arquivo_ras); // Volta para o início do arquivo.
        fscanf(arquivo_ras, "%[^\n]\n", primeira_linha);

        while (!feof(arquivo_ras)) {

            fscanf(arquivo_ras, "%[^;];%[^\n]\n",
                miniusina_lida.idra,
                miniusina_lida.nome);

            int ra_encontrada = 0;
            for (int i = 0; i < quantidade_ras; i++) {
                if (strcmp(miniusina_lida.idra, lista_ras[i].idra) == 0) {
                    ra_encontrada = 1;
                    strcpy(lista_ras[i].nome_ra, miniusina_lida.nome);
                    break;
                }
            }

            if (!ra_encontrada) { // Verifica se a RA não foi encontrada anteriormente
                strcpy(lista_ras[quantidade_ras].idra, miniusina_lida.idra);
                strcpy(lista_ras[quantidade_ras].nome_ra, miniusina_lida.nome);
                lista_ras[quantidade_ras].quantidade_de_miniusinas = 0;
                quantidade_ras++;
            }
        }

        // Ordenação das RAs por quantidade de miniusinas.
        SortRasPorMiniusinasDecrescente(lista_ras, quantidade_ras);

        // Exibição das RAs
        for (int i = 0; i < quantidade_ras; i++) {
            printf("\nID_RA: %s\n", lista_ras[i].idra);
            printf("Nome da RA: %s\n", lista_ras[i].nome_ra);
            printf("Quantidade de Miniusinas: %d\n", lista_ras[i].quantidade_de_miniusinas);
        }

        // Fechamento dos arquivos.
        fclose(arquivo_miniusinas);
        fclose(arquivo_ras);
    } else {
        printf("Erro, não foi possível abrir os arquivos de miniusinas ou RAs.\n");
    }
}

// Algoritmo para ordenar as RAs em ordem crescente de número de contratos.
void SortRasPorContratosCrescente(struct ra * ras, int quantidade_ras) {
    int i, j, auxiliar;
    struct ra temp;

    for (i = 0; i < quantidade_ras - 1; i++) {
        auxiliar = i;
        for (j = i + 1; j < quantidade_ras; j++) {
            if (ras[j].quantidade_contratos < ras[auxiliar].quantidade_contratos) {
                auxiliar = j;
            }
        }

        if (auxiliar != i) {
            temp = ras[i];
            ras[i] = ras[auxiliar];
            ras[auxiliar] = temp;
        }
    }
}

// Procedimento para listar as RAs em ordem crescente de número de contratos. (Opção 6)
void listar_ras_ordenadas_por_contratos_crescente() {

    FILE * arquivo_consumidores;
    FILE * arquivo_contratos;
    FILE * arquivo_ra;
    struct consumidor lista_consumidores[100];
    struct contratos lista_contratos[100];
    struct ra lista_ras[100];
    int quantidade_consumidores = 0;
    int quantidade_contratos = 0;
    int quantidade_ras = 0;

    // Abertura dos arquivos.
    arquivo_consumidores = fopen("consumidores.csv", "r");
    arquivo_contratos = fopen("contratos.csv", "r");
    arquivo_ra = fopen("ra.csv", "r");

    if (arquivo_consumidores != NULL && arquivo_contratos != NULL && arquivo_ra != NULL) {
        // Leitura dos consumidores.
        char linha_consumidor[1000];
        fscanf(arquivo_consumidores, "%[^\n]\n", linha_consumidor); // Ignora a primeira linha.

        while (fscanf(arquivo_consumidores, "%[^;];%[^;];%d\n",
                lista_consumidores[quantidade_consumidores].id_consumidor,
                lista_consumidores[quantidade_consumidores].nome, &lista_consumidores[quantidade_consumidores].id_ra) == 3) {
            quantidade_consumidores++;
        }

        // Leitura dos contratos.
        char linha_contrato[1000];
        fscanf(arquivo_contratos, "%[^\n]\n", linha_contrato); // Ignora a primeira linha.

        while (fscanf(arquivo_contratos, "%[^;];%[^;];%[^;];%[^;];%f\n",
                lista_contratos[quantidade_contratos].idcontrato,
                lista_contratos[quantidade_contratos].idconsumidor,
                lista_contratos[quantidade_contratos].cnpj,
                lista_contratos[quantidade_contratos].datacontrato, &
                lista_contratos[quantidade_contratos].energia_contratada) == 5) {
            quantidade_contratos++;
        }

        // Leitura das RAs.
        char linha_ra[1000];
        fscanf(arquivo_ra, "%[^\n]\n", linha_ra); // Ignora a primeira linha.

        while (fscanf(arquivo_ra, "%d;%[^\n]\n", &
                lista_ras[quantidade_ras].id_ra,
                lista_ras[quantidade_ras].nome_ra) == 2) {
            lista_ras[quantidade_ras].quantidade_contratos = 0;
            quantidade_ras++;
        }

        // Verificação dos contratos para cada consumidor.
        for (int i = 0; i < quantidade_consumidores; i++) {
            for (int j = 0; j < quantidade_contratos; j++) {
                if (strcmp(lista_consumidores[i].id_consumidor, lista_contratos[j].idconsumidor) == 0) {
                    for (int k = 0; k < quantidade_ras; k++) {
                        if (lista_consumidores[i].id_ra == lista_ras[k].id_ra) {
                            lista_ras[k].quantidade_contratos++;
                            break;
                        }
                    }
                    break;
                }
            }
        }

        // Ordenação das RAs por quantidade de contratos.
        SortRasPorContratosCrescente(lista_ras, quantidade_ras);

        // Exibição das RAs
        for (int i = 0; i < quantidade_ras; i++) {
            printf("\nID_RA: %d\n", lista_ras[i].id_ra);
            printf("Nome da RA: %s\n", lista_ras[i].nome_ra);
            printf("Quantidade de Contratos: %d\n", lista_ras[i].quantidade_contratos);
        }

        // Fechamento dos arquivos.
        fclose(arquivo_consumidores);
        fclose(arquivo_contratos);
        fclose(arquivo_ra);
    } else {
        printf("Erro, não foi possível abrir os arquivos.\n");
    }
}

// Algoritmo para ordenar a lista de RAs por ordem decrescente de capacidade de geração total da RA.
void SortRasPorCapacidadeDecrescente(struct ra ras[], int quantidade_ras) {
    int i, j;
    struct ra temp;

    for (i = 0; i < quantidade_ras - 1; i++) {
        for (j = i + 1; j < quantidade_ras; j++) {
            if (ras[j].capacidade_total > ras[i].capacidade_total) {
                temp = ras[i];
                ras[i] = ras[j];
                ras[j] = temp;
            }
        }
    }
}

// Procedimento para listar as RAs por ordem decrescente de capacidade de geração total da RA. (Opção 7)
void listar_ras_ordenadas_por_capacidade_de_geracao_decrescente() {
    FILE * arquivo_miniusinas;
    FILE * arquivo_ras;
    struct miniusina miniusinas[100];
    struct ra lista_ras[100];
    int quantidade_ras = 0;

    // Abertura dos arquivos.
    arquivo_miniusinas = fopen("miniusinas.csv", "r");
    arquivo_ras = fopen("ra.csv", "r");

    if (arquivo_miniusinas != NULL && arquivo_ras != NULL) {
        char primeira_linha_miniusinas[1000];
        fscanf(arquivo_miniusinas, "%[^\n]\n", primeira_linha_miniusinas);
        char primeira_linha[1000];
        fscanf(arquivo_ras, "%[^\n]\n", primeira_linha);

        // Leitura dos nomes das RAS.
        while (fscanf(arquivo_ras, "%d;%[^\n]\n", &
                lista_ras[quantidade_ras].id_ra,
                lista_ras[quantidade_ras].nome_ra) == 2) {

            quantidade_ras++;

        }

        // Inicializa a capacidade total de cada RAS como 0.
        for (int i = 0; i < quantidade_ras; i++) {
            lista_ras[i].capacidade_total = 0;
        }

        // Leitura das miniusinas e soma da capacidade total por RAS.
        while (fscanf(arquivo_miniusinas, "%[^;];%[^;];%f;%d;%[^\n]\n",
                miniusinas[quantidade_ras].cnpj,
                miniusinas[quantidade_ras].nome, 
                &miniusinas[quantidade_ras].capacidade, 
                &miniusinas[quantidade_ras].id_ra,
                miniusinas[quantidade_ras].status) == 5) {
            for (int i = 0; i < quantidade_ras; i++) {
                if (miniusinas[quantidade_ras].id_ra == lista_ras[i].id_ra) {
                    lista_ras[i].capacidade_total += miniusinas[quantidade_ras].capacidade;
                    break;
                }
            }
        }

        // Ordenação das RAs por capacidade total de geração.
        SortRasPorCapacidadeDecrescente(lista_ras, quantidade_ras);

        // Exibição das RAs
        for (int i = 0; i < quantidade_ras; i++) {
            printf("ID_RA: %d\n", lista_ras[i].id_ra);
            printf("Nome da RA: %s\n", lista_ras[i].nome_ra);
            printf("Capacidade Total de Geração: %.2f kWh\n\n", lista_ras[i].capacidade_total);
        }

        // Fechamento dos arquivos.
        fclose(arquivo_miniusinas);
        fclose(arquivo_ras);
    } else {
        printf("Erro, nao foi possivel abrir os arquivos de miniusinas ou RAs.\n");
    }
}

// Procedimento para listar as RAs por percentual de energia disponível em ordem decrescente. (Opção 8)
void listar_ras_por_percentual_decrescente() {
    FILE * arquivo_miniusinas;
    FILE * arquivo_ras;
    struct miniusina miniusinas[100];
    struct ra lista_ras[100];
    int quantidade_miniusinas = 0;
    int quantidade_ras = 0;

    // Abertura dos arquivos.
    arquivo_miniusinas = fopen("miniusinas.csv", "r");
    arquivo_ras = fopen("ra.csv", "r");

    if (arquivo_miniusinas != NULL && arquivo_ras != NULL) {
        char primeira_linha_miniusinas[1000];
        fscanf(arquivo_miniusinas, "%[^\n]\n", primeira_linha_miniusinas);
        // Leitura das miniusinas.

        while (fscanf(arquivo_miniusinas, "%[^;];%[^;];%f;%d;%[^\n]\n",
                miniusinas[quantidade_miniusinas].cnpj,
                miniusinas[quantidade_miniusinas].nome, &
                miniusinas[quantidade_miniusinas].capacidade, &
                miniusinas[quantidade_miniusinas].id_ra,
                miniusinas[quantidade_miniusinas].status) == 5) {
            quantidade_miniusinas++;
        }

        // Leitura das RAs.
        char linha_ra[1000];
        fscanf(arquivo_ras, "%[^\n]\n", linha_ra); // Ignora a primeira linha.

        while (fscanf(arquivo_ras, "%d;%[^\n]\n", &
                lista_ras[quantidade_ras].id_ra,
                lista_ras[quantidade_ras].nome_ra) == 2) {
            quantidade_ras++;
        }

        // Cálculo da capacidade total de geração para cada RA e a taxa contratada pela RA.
        for (int i = 0; i < quantidade_ras; i++) {
            lista_ras[i].capacidade_total = 0;
            lista_ras[i].energia_contratada = 0;
            int contador_miniusinas = 0;
            int tem_miniusina_com_contrato = 0;

            for (int j = 0; j < quantidade_miniusinas; j++) {
                if (miniusinas[j].id_ra == lista_ras[i].id_ra) {
                    lista_ras[i].capacidade_total += miniusinas[j].capacidade;
                    contador_miniusinas++;

                    // Verifica se há contrato para a miniusina.
                    FILE * arquivo_contratos = fopen("contratos.csv", "r");
                    if (arquivo_contratos != NULL) {
                        char linha_contrato[1000];
                        fscanf(arquivo_contratos, "%[^\n]\n", linha_contrato); // Ignora a primeira linha.

                        char cnpj_contrato[20];
                        float energia_contratada;

                        while (fscanf(arquivo_contratos, "%*d;%*[^;];%[^;];%*[^;];%f\n", // Ignorar dado do arquivo durante a leitura com *.
                                cnpj_contrato, & energia_contratada) == 2) {
                            if (strcmp(cnpj_contrato, miniusinas[j].cnpj) == 0) {
                                // Encontrou o CNPJ da miniusina no contrato, armazena a energia contratada.
                                lista_ras[i].energia_contratada += energia_contratada;
                                tem_miniusina_com_contrato = 1;
                            }
                        }

                        fclose(arquivo_contratos);
                    } else {
                        printf("Erro, não foi possível abrir o arquivo de contratos.\n");
                    }
                }
            }

            // Verifica os casos de energia contratada e taxa_contratada_ra.
            if (contador_miniusinas == 0) {
                lista_ras[i].energia_contratada = 0;
                lista_ras[i].taxa_contratada_ra = 0;
            } else if (!tem_miniusina_com_contrato) {
                lista_ras[i].energia_contratada = 0;
                lista_ras[i].taxa_contratada_ra = 100;
            } else {
                lista_ras[i].taxa_contratada_ra = ((lista_ras[i].capacidade_total - lista_ras[i].energia_contratada) / lista_ras[i].capacidade_total) * 100;
            }
        }

        // Ordenação das RAs por taxa_contratada_ra em ordem decrescente usando Selection Sort.
        for (int i = 0; i < quantidade_ras - 1; i++) {
            int auxiliar = i;

            for (int j = i + 1; j < quantidade_ras; j++) {
                if (lista_ras[j].taxa_contratada_ra > lista_ras[auxiliar].taxa_contratada_ra) {
                    auxiliar = j;
                }
            }

            // Troca as posições dos elementos.
            struct ra temp = lista_ras[auxiliar];
            lista_ras[auxiliar] = lista_ras[i];
            lista_ras[i] = temp;
        }

        // Impressão dos resultados ordenados.
        for (int i = 0; i < quantidade_ras; i++) {
            printf("ID_RA: %d\n", lista_ras[i].id_ra);
            printf("Nome da RA: %s\n", lista_ras[i].nome_ra);
            printf("Capacidade Total de Geração: %.2f kWh\n", lista_ras[i].capacidade_total);
            printf("Energia Contratada pela RA: %.2d kWh\n", lista_ras[i].energia_contratada);
            printf("Percentual de energia disponivel: %.2f%%\n\n", lista_ras[i].taxa_contratada_ra);
        }

        // Fechamento dos arquivos.
        fclose(arquivo_miniusinas);
        fclose(arquivo_ras);
    } else {
        printf("Erro, não foi possível abrir os arquivos.\n");
    }
}

// Este procedimento substitui a chamada à função fflush(stdin), a qual não funciona no OnlineGDB
void limpar_buffer() {
    // As duas linhas abaixo servem para limpar
    // o buffer e possibilitar a leitura do nome
    char ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}
// Procedimento para mostrar uma mensagem e aguardar o usuário pressionar qualquer tecla
// No Windows, até poderia chamar a função system("pause");
// Porém, não vai funcionar no Linux porque não tem o comando pause.
void pause() {
    printf("\n");
    printf("Pressione enter para continuar...");
    getc(stdin);
}
// Este procedimento é útil para limpar a tela antes de voltar ao menu principal.
// 0 comando para limpar a tela no prompt do Windows é cls. Já no Linux, o comando é cls.
void limpar_tela() {
    #ifdef _WIN32
    system("cls");
    #else
    system("clear");
    #endif
}
// Procedimento para mostrar o menu de opções na tela.
void menu() {

    printf("\n    Bem vindo ao SINGDF - Sistema de Informações sobre Geração e Distribuição Fotovoltáica (SINGDF)\n");
    printf("\n");
    printf("    Opções de consulta:\n");
    printf("\n");
    printf("    1) Consultar miniusina cadastrada\n");
    printf("    2) Consultar consumidor cadastrado\n");
    printf("    3) Listar as miniusinas cadastradas\n");
    printf("    4) Listar as miniusinas em operação por ordem decrescente de capacidade de geração de energia\n");
    printf("    5) Listar as RAs por ordem decrescente de quantidade de miniusinas\n");
    printf("    6) Listar as RAs por ordem crescente de número de contratos\n");
    printf("    7) Listar as RAs por ordem decrescente de capacidade de geração\n");
    printf("    8) Listar as RAs por ordem decrescente de percentual de energia disponível\n");
    printf("    9) Sair do programa\n");

}

#endif // BIBLIOTECA_H
