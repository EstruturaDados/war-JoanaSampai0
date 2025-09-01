// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
// ============================================================================
//        
// ============================================================================
//
// OBJETIVOS:
// - Modularizar completamente o código em funções especializadas.
// - Implementar um sistema de missões para um jogador.
// - Criar uma função para verificar se a missão foi cumprida.
// - Utilizar passagem por referência (ponteiros) para modificar dados e
//   passagem por valor/referência constante (const) para apenas ler.
// - Foco em: Design de software, modularização, const correctness, lógica de jogo.
//
// ============================================================================

// Inclusão das bibliotecas padrão necessárias para entrada/saída, alocação de memória, manipulação de strings e tempo.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- Constantes Globais ---
// Definem valores fixos para o número de territórios, missões e tamanho máximo de strings, facilitando a manutenção.
#define MAX_TERRITORIO 50
#define TAM_STRING 100


// --- Estrutura de Dados ---
// Define a estrutura para um território, contendo seu nome, a cor do exército que o domina e o número de tropas.
struct territorio {
    char nome[TAM_STRING];
    char cor[TAM_STRING];
    int numTropas;
};
// Função para limpar o buffer de entrada ---
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// --- Protótipos das Funções ---
// Declarações antecipadas de todas as funções que serão usadas no programa, organizadas por categoria.
// Funções de setup e gerenciamento de memória:
// Funções de interface com o usuário:
// Funções de lógica principal do jogo:
// Função utilitária:

// --- Função Principal (main) ---
// Função principal que orquestra o fluxo do jogo, chamando as outras funções em ordem.
int main() {
    struct territorio tabuleiro[MAX_TERRITORIO];
    int totalTerritorio = 0;
    int opcao;

    // --- Laço principal do menu ---
    do {
        //Exibe o menu de opções
        printf("=============================\n");
        printf(" Cadastrar os 5 territorios iniciais \n");
        printf("=============================\n");
        printf("1 - Cadastrar territorio \n");
        printf("2 - Listar territorio\n");
        printf("0 - Sair\n");
        printf("-----------------------------\n");
        printf("Escolha uma opcao: ");

        // Lê a opção do usuário
        scanf("%d", &opcao);
        limparBufferEntrada(); // Limpa o'\n' deixando pelo scanf

        switch (opcao) {
            case 1: // Cadastro de territorio
            printf("--- Cadastro de Novo Territorio ---\n\n");

            if(totalTerritorio < MAX_TERRITORIO) {
                printf("Nome do territorio: ");
                fgets(tabuleiro[totalTerritorio].nome, TAM_STRING, stdin);

                printf("Cor do exercito: ");
                fgets(tabuleiro[totalTerritorio].cor, TAM_STRING, stdin);

                tabuleiro[totalTerritorio].nome[strcspn(tabuleiro[totalTerritorio].nome, "\n")] = 0; // Remove o '\n' do final
                tabuleiro[totalTerritorio].cor[strcspn(tabuleiro[totalTerritorio].cor, "\n")] = 0; // Remove o '\n' do final
               
                printf("Numero de tropas: ");
                scanf("%d", &tabuleiro[totalTerritorio].numTropas);
                limparBufferEntrada(); // Limpa o'\n' deixando pelo scanf

                totalTerritorio++;

                printf("Territorio cadastrado com sucesso!\n");
              } else {
                printf("Limite de territorios atingido!\n");
            }

            printf("\n Pressione ENTER para continuar...");
            getchar(); // Pausa para o usuário ler a mensagem antes de voltar ao menu
            break;

            case 2: // Listar territorios
            printf("--- Lista de Territorios ---\n\n");
            if(totalTerritorio == 0) {
                printf("Nenhum territorio cadastrado!\n");
            } else {
                for(int i = 0; i < totalTerritorio; i++) {
                    printf("-----------------------------\n");
                    printf("Territorio %d:\n", i + 1);
                    printf("Nome: %s\n", tabuleiro[i].nome);
                    printf("Cor do exercito: %s\n", tabuleiro[i].cor);
                    printf("Numero de tropas: %d\n", tabuleiro[i].numTropas);
                    
                }
                printf("-----------------------------\n");
            }
            
            // A pausa é crucial para que o usuário veja a lista antes
            // do próximo loop limpar a tela
            printf("\nPressione ENTER para continuar...");
            getchar();
            break;

            case 0: // Sair
            printf("\n Saindo do Sistema...\n");
            break;

            default: // Opção inválida
            printf("\nOpcao invalida! Tente novamente.\n");
            printf("\nPressione ENTER para continuar...");
            getchar();
            break;

        }
    } while (opcao != 0);

    return 0;
}