// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO (AVENTUREIRO)
// ============================================================================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> // necessário para srand(time(NULL)) e obter aleatoriedade

// --- Constantes Globais ---
#define MAX_TERRITORIO 50
#define TAM_STRING 100

// --- Estrutura de Dados ---
struct territorio
{
    char nome[TAM_STRING];
    char cor[TAM_STRING];
    int numTropas;
};

// --- Protótipos das Funções ---
void limparBufferEntrada();
struct territorio* criarMapaDinamico(int capacidade);
void liberarMemoria(struct territorio* mapa);
void cadastrar5Territorios(struct territorio* mapa, int* totalTerritorio);
void listarTerritorios(struct territorio* mapa, int totalTerritorio);
void atacar(struct territorio* atacante, struct territorio* defensor);
int validarIndice(int idx, int total);

// --- Função para limpar o buffer de entrada ---
void limparBufferEntrada()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

// --- Cria (aloca) dinamicamente um vetor de territorios ---
struct territorio* criarMapaDinamico(int capacidade)
{
    struct territorio* mapa = (struct territorio*)calloc(capacidade, sizeof(struct territorio));
    if (mapa == NULL)
    {
        printf("Erro: nao foi possivel alocar memoria para o mapa!\n");
        exit(1);
    }
    return mapa;
}

// --- Libera a memoria alocada dinamicamente ---
void liberarMemoria(struct territorio* mapa)
{
    if (mapa != NULL)
    {
        free(mapa);
    }
}

// --- Cadastra 5 territorios ---
// Usa ponteiro para mapa e ponteiro para totalTerritorio para atualizar o contador
void cadastrar5Territorios(struct territorio* mapa, int* totalTerritorio)
{
    if (*totalTerritorio + 5 > MAX_TERRITORIO)
    {
        printf("Limite de territorios atingido! Nao e possivel cadastrar 5 a mais.\n");
        return;
    }

    for (int i = 0; i < 5; i++)
    {
        printf("Cadastro do territorio %d:\n", *totalTerritorio + 1);

        printf("Nome do territorio: ");
        fgets(mapa[*totalTerritorio].nome, TAM_STRING, stdin);
        mapa[*totalTerritorio].nome[strcspn(mapa[*totalTerritorio].nome, "\n")] = 0;

        printf("Cor do exercito: ");
        fgets(mapa[*totalTerritorio].cor, TAM_STRING, stdin);
        mapa[*totalTerritorio].cor[strcspn(mapa[*totalTerritorio].cor, "\n")] = 0;

        printf("Numero de tropas: ");
        scanf("%d", &mapa[*totalTerritorio].numTropas);
        limparBufferEntrada();

        (*totalTerritorio)++;

        printf("Territorio cadastrado com sucesso!\n\n");
    }
}

// --- Lista territorios cadastrados ---
void listarTerritorios(struct territorio* mapa, int totalTerritorio)
{
    printf("--- Lista de Territorios ---\n\n");
    if (totalTerritorio == 0)
    {
        printf("Nenhum territorio cadastrado!\n");
        return;
    }
    for (int i = 0; i < totalTerritorio; i++)
    {
        printf("-----------------------------\n");
        printf("Territorio %d:\n", i + 1);
        printf("Nome: %s\n", mapa[i].nome);
        printf("Cor do exercito: %s\n", mapa[i].cor);
        printf("Numero de tropas: %d\n", mapa[i].numTropas);
    }
    printf("-----------------------------\n");
}

// --- Valida se o indice escolhido esta no intervalo valido ---
int validarIndice(int indice, int total)
{
    if (indice < 1 || indice > total)
        return 0;
    return 1;
}

// --- Função que simula ataque entre territórios usando ponteiros ---
// Regras implementadas:
// - Não permite atacar território da mesma cor
// - Atacante precisa ter mais de 1 tropa para atacar
// - Rola um dado (1 a 6) para atacante e defensor com rand()
// - Se atacante vencer: defensor muda de cor para a do atacante e recebe metade
//   das tropas do atacante; o atacante fica com o restante (subtraído).
// - Se defensor vencer ou empatar: atacante perde 1 tropa.
void atacar(struct territorio* atacante, struct territorio* defensor)
{
    // Valida se ambos ponteiros são válidos
    if (atacante == NULL || defensor == NULL)
    {
        printf("Erro: ponteiro nulo na funcao atacar.\n");
        return;
    }

    // Validação: não atacar território da mesma cor
    if (strcmp(atacante->cor, defensor->cor) == 0)
    {
        printf("\nNao e possivel atacar um territorio da propria cor (%s).\n", atacante->cor);
        return;
    }

    // Atacante precisa ter mais de 1 tropa (assim sobra ao menos 1 para ocupar)
    if (atacante->numTropas <= 1)
    {
        printf("\nO atacante precisa ter mais de 1 tropa para iniciar o ataque. Tropas do atacante: %d\n", atacante->numTropas);
        return;
    }

    // Rolagem dos dados (1 a 6)
    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;

    printf("\nRolagem de dados:\n");
    printf("Atacante (%s) rolou: %d\n", atacante->nome, dadoAtacante);
    printf("Defensor  (%s) rolou: %d\n", defensor->nome, dadoDefensor);

    if (dadoAtacante > dadoDefensor)
    {
        // Atacante vence
        printf("\nO atacante venceu a batalha!\n");
        // Transfere cor
        strncpy(defensor->cor, atacante->cor, TAM_STRING - 1);
        defensor->cor[TAM_STRING - 1] = '\0';
        // Transfere metade das tropas do atacante para defensor
        int tropasTransferidas = atacante->numTropas / 2; // metade inteira
        if (tropasTransferidas < 1) tropasTransferidas = 1; // garante ao menos 1
        defensor->numTropas = tropasTransferidas;
        atacante->numTropas = atacante->numTropas - tropasTransferidas;
        if (atacante->numTropas < 0) atacante->numTropas = 0;
        printf("Defensor agora pertence a cor '%s' e passa a ter %d tropas.\n", defensor->cor, defensor->numTropas);
        printf("Atacante agora possui %d tropas restantes.\n", atacante->numTropas);
    }
    else
    {
        // Defensor vence ou empata
        printf("\nO defensor resistiu ao ataque!\n");
        atacante->numTropas -= 1;
        if (atacante->numTropas < 0) atacante->numTropas = 0;
        printf("Atacante perde 1 tropa. Tropas restantes do atacante: %d\n", atacante->numTropas);
    }
}

// --- Função Principal (main) ---
int main()
{
    // Substituímos o array estático por um mapa alocado dinamicamente
    struct territorio* tabuleiro = criarMapaDinamico(MAX_TERRITORIO);
    int totalTerritorio = 0;
    int opcao;

    
    srand((unsigned int)time(NULL));

    // --- Laço principal do menu ---
    do
    {
        // Exibe o menu de opções
        printf("=============================\n");
        printf(" Cadastrar os 5 territorios iniciais \n");
        printf("=============================\n");
        printf("1 - Cadastrar territorio (5 de cada vez)\n");
        printf("2 - Listar territorio\n");
        printf("3 - Simular ataque entre territorios\n");
        printf("0 - Sair\n");
        printf("-----------------------------\n");
        printf("Escolha uma opcao: ");

        if (scanf("%d", &opcao) != 1)
        {
            limparBufferEntrada();
            printf("Opcao invalida! Digite um numero.\n");
            continue;
        }
        limparBufferEntrada();

        switch (opcao)
        {
        case 1: // Cadastro de territorios (5 de uma vez)
            printf("--- Cadastro dos 5 Territorios Iniciais ---\n\n");
            cadastrar5Territorios(tabuleiro, &totalTerritorio);
            printf("\nPressione ENTER para continuar...");
            getchar();
            break;

        case 2: // Listar territorios
            printf("--- Lista de Territorios ---\n\n");
            listarTerritorios(tabuleiro, totalTerritorio);
            printf("\nPressione ENTER para continuar...");
            getchar();
            break;

        case 3: // Simular ataque
        {
            if (totalTerritorio < 2)
            {
                printf("Para simular um ataque e necessario ter ao menos 2 territorios cadastrados.\n");
                printf("\nPressione ENTER para continuar...");
                getchar();
                break;
            }

            listarTerritorios(tabuleiro, totalTerritorio);

            int a, d;
            printf("\nEscolha o numero do territorio atacante: ");
            if (scanf("%d", &a) != 1) { limparBufferEntrada(); printf("Entrada invalida!\n"); break; }
            printf("Escolha o numero do territorio defensor: ");
            if (scanf("%d", &d) != 1) { limparBufferEntrada(); printf("Entrada invalida!\n"); break; }
            limparBufferEntrada();

            if (!validarIndice(a, totalTerritorio) || !validarIndice(d, totalTerritorio))
            {
                printf("Territorio invalido! Escolha indices entre 1 e %d.\n", totalTerritorio);
            }
            else if (a == d)
            {
                printf("O atacante e o defensor nao podem ser o mesmo territorio.\n");
            }
            else
            {
                // Chama atacar passando ponteiros para os territorios escolhidos
                atacar(&tabuleiro[a - 1], &tabuleiro[d - 1]);

                // Exibe o estado atualizado após o ataque
                printf("\n--- Estado apos o ataque ---\n");
                listarTerritorios(tabuleiro, totalTerritorio);
            }

            printf("\nPressione ENTER para continuar...");
            getchar();
            break;
        }

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

    // Libera memoria alocada dinamicamente antes de sair
    liberarMemoria(tabuleiro);

    return 0;
}
