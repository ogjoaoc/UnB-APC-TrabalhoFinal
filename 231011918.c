/******************************************************************************
Aluno(a): João Carlos Gonçalves 
Matrícula: 231011918
Declaro que eu sou o(a) autor(a) deste trabalho e que o código não foi copiado
de outra pessoa nem repassado para alguém. Estou ciente de que poderei sofrer
penalizações na avaliação em caso de detecção de plágio.
*******************************************************************************/

#include <stdio.h>

#include <string.h>

#include <stdlib.h>

#include "231011918.h"

// Função principal do programa.
// responsável por carregar a biblioteca de funções, que guarda as opções do menu.

int main() {
    int opcao;
    int resultado;

    #if defined(_WIN32) || defined(_WIN64)
    system("chcp 65001");
    #endif

    do {
        // Mostrar menu
        menu();
        fflush(stdin);
        resultado = scanf("%d", & opcao);

        if (resultado == 0) {
            printf("\n\n");
        }

        switch (opcao) {

        case CONSULTAR_MINIUSINA:
            // Opção para consultar os dados de uma miniusina cadastrada a partir do CNPJ.
            printf("\n");
            consultar_miniusina_cadastrada();
            limpar_buffer();
            pause();
            limpar_tela();
            break;

        case CONSULTAR_CONSUMIDOR:
            // Opção para consultar consumidor cadastrado.
            printf("\n");
            consultar_consumidor_cadastrado();
            limpar_buffer();
            pause();
            limpar_tela();
            break;

        case LISTAR_MINIUSINAS:
            // Opção para listar os dados das miniusinas cadastradas.
            printf("\n");
            listar_miniusinas();
            limpar_buffer();
            pause();
            limpar_tela();
            break;

        case LISTAR_MINIUSINAS_OPERACAO_DECRESCENTE:
            // Opção para listar miniusinas em ordem decrescente.
            printf("\n");
            listar_miniusinas_ordenadas_por_capacidade_decrescente();
            limpar_buffer();
            pause();
            limpar_tela();
            break;

        case LISTAR_RAS_ORDEM_DESCRESCENTE_QUANTIDADE_MINIUSINAS:
            // Opção para listar RAs em ordem decrescente de quantidade de miniusinas.
            printf("\n");
            listar_ras_ordenadas_por_miniusinas_decrescente();
            limpar_buffer();
            pause();
            limpar_tela();
            break;

        case LISTAR_RAS_ORDEM_CRESCENTE_CONTRATOS:
            // Opção para listar as RAs em ordem crescente de número de contratos.
            printf("\n");
            listar_ras_ordenadas_por_contratos_crescente();
            printf("\n");
            limpar_buffer();
            pause();
            limpar_tela();
            break;

        case LISTAR_RAS_ORDEM_DESCRESCENTE_CAPACIDADE_GERACAO:
            // Opção para listar as RAs em ordem decrescente de capacidade de geração.
            printf("\n");
            listar_ras_ordenadas_por_capacidade_de_geracao_decrescente();
            printf("\n");
            limpar_buffer();
            pause();
            limpar_tela();
            break;

        case LISTAR_RAS_ORDEM_DESCRESCENTE_PERCENTUAL_ENERGIA_DISPONIVEL:
            // Opção para listar as RAs em ordem decrescente de percentual de energia disponível.
            printf("\n");
            listar_ras_por_percentual_decrescente();
            printf("\n");
            limpar_buffer();
            pause();
            limpar_tela();
            break;

        case SAIR:
            printf("\nEncerrando sistema...\n\n");
            break;

        default:
            limpar_tela();
            printf("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
            printf(" Entrada incorreta (Digite apenas um número referente a opção do menu) \n");
            printf("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
            printf("\n");
            limpar_buffer();
            pause();
            limpar_tela();
        }

    } while (opcao != SAIR);

    return 1;

}
