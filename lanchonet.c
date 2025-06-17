#include <stdio.h>
#include <stdlib.h>

#define MAX_ITENS 100

// Estrutura de item
typedef struct {
    int codigo;
    char nome[40];
    float preco;
} Item;

// Cardápio simplificado
Item cardapio[] = {
    {101, "Classico Smash",      24.90},
    {102, "Duplo Bacon",         34.50},
    {201, "Batata Tradicional",  12.90},
    {202, "Onion Rings",         16.90},
    {301, "Refrigerante (lata)",  6.50},
    {302, "Agua (500ml)",         5.00}
};
const int N = sizeof(cardapio) / sizeof(cardapio[0]);

int pedido_cod[N];
int pedido_qt[N];
int n_ped = 0;

void limparTela() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void exibirMenu() {
    printf("+--------------------------------------+\n");
    printf("|      CANTINHO DO DONALD - PEDIDOS     |\n");
    printf("+--------------------------------------+\n");
    printf("| Código | Descrição              | Preço |");
    printf("\n+--------------------------------------+\n");
    for (int i = 0; i < N; i++) {
        printf("| %3d    | %-18s | %6.2f |\n",
            cardapio[i].codigo,
            cardapio[i].nome,
            cardapio[i].preco);
    }
    printf("+--------------------------------------+\n");
    printf("| Digite 0 para finalizar o pedido     |\n");
    printf("+--------------------------------------+\n");
}

int busca(int codigo) {
    for (int i = 0; i < N; i++) {
        if (cardapio[i].codigo == codigo) return i;
    }
    return -1;
}

int main() {
    int cod, qt;
    limparTela();
    exibirMenu();
    while (1) {
        printf("\nInforme código: ");
        if (scanf("%d", &cod) != 1) { break; }
        if (cod == 0) break;
        int idx = busca(cod);
        if (idx < 0) {
            printf("Código inválido!\n");
            continue;
        }
        printf("Quantidade: ");
        if (scanf("%d", &qt) != 1 || qt <= 0) {
            printf("Quantidade inválida!\n");
            continue;
        }
        pedido_cod[n_ped] = idx;
        pedido_qt[n_ped++] = qt;
        printf("Adicionado: %d x %s\n", qt, cardapio[idx].nome);
    }
    limparTela();
    printf("\n======= RESUMO =======\n");
    float total = 0;
    for (int i = 0; i < n_ped; i++) {
        int idx = pedido_cod[i];
        float sub = cardapio[idx].preco * pedido_qt[i];
        printf(" %d x %-18s = R$ %6.2f\n",
               pedido_qt[i], cardapio[idx].nome, sub);
        total += sub;
    }
    printf("------------------------\n");
    if (total > 50) {
        float d = total * 0.05;
        total -= d;
        printf("Desconto 5%%:      -R$%6.2f\n", d);
    }
    printf("TOTAL:            R$%6.2f\n", total);
    printf("========================\n");
    printf("Obrigado pelo pedido!\n");
    return 0;
}
