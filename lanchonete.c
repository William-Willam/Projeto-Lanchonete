#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nome[50];
    float preco;
    char categoria[20];
} Produto;

typedef struct {
    Produto produto;
    int quantidade;
} Pedido;

typedef struct{
    char nome[50];
    char CPF[15];
    char telefone[15];
} Cliente;

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void mostrarBemVindo() {
    system("cls"); 
    printf("=======================================================\n");
    printf("|                    DONALD FOOD                      |\n");
    printf("=======================================================\n\n");
}

// Funcao para coletar dados do cliente
void dadosDoCliente(Cliente *cliente){
    printf("Digite seu nome: ");
    fgets(cliente->nome, sizeof(cliente->nome), stdin);
    cliente->nome[strcspn(cliente->nome, "\n")] = 0;

    printf("Digite seu CPF: ");
    fgets(cliente->CPF, sizeof(cliente->CPF), stdin);
    cliente->CPF[strcspn(cliente->CPF, "\n")] = 0;

    printf("Digite seu telefone: ");
    fgets(cliente->telefone, sizeof(cliente->telefone), stdin);
    cliente->telefone[strcspn(cliente->telefone, "\n")] = 0;

    printf("\nBem-vindo, %s! Seu pedido será entregue em breve.\n", cliente->nome);
    printf("Pressione ENTER para continuar...");
    getchar();
    system("cls"); 
}

// Funcao para mostrar o cardapio
void mostrarCardapio(Produto cardapio[], int tamanho) {
    printf("====================================================\n");
    printf("                    CARDÁPIO                        \n");
    printf("====================================================\n\n");

    printf("--------------------- Trios ------------------------\n");
    printf("%-3s %-25s %10s\n", "Id", "Produto", "Preco");
    for (int i = 0; i < tamanho; i++)
        if (strcmp(cardapio[i].categoria, "Trio") == 0)
            printf("%-3d %-25s R$ %8.2f\n", i+1, cardapio[i].nome, cardapio[i].preco);
    printf("\n");

    printf("------------------- Sobremesas ---------------------\n");
    printf("%-3s %-25s %10s\n", "Id", "Produto", "Preco");
    for (int i = 0; i < tamanho; i++)
        if (strcmp(cardapio[i].categoria, "Sobremesa") == 0)
            printf("%-3d %-25s R$ %8.2f\n", i+1, cardapio[i].nome, cardapio[i].preco);
    printf("\n");

    printf("------------------ Hamburgueres --------------------\n");
    printf("%-3s %-25s %10s\n", "Id", "Produto", "Preço");
    for (int i = 0; i < tamanho; i++)
        if (strcmp(cardapio[i].categoria, "Hamburguer") == 0)
            printf("%-3d %-25s R$ %8.2f\n", i+1, cardapio[i].nome, cardapio[i].preco);
    printf("\n");

    printf("---------------------- Bebidas ------------------------\n");
    printf("%-3s %-25s %10s\n", "Id", "Produto", "Preco");
    for (int i = 0; i < tamanho; i++)
        if (strcmp(cardapio[i].categoria, "Bebida") == 0)
            printf("%-3d %-25s R$ %8.2f\n", i+1, cardapio[i].nome, cardapio[i].preco);
    printf("\n");
    
    printf("---------------------- Kids ------------------------\n");
    printf("%-3s %-25s %10s\n", "Id", "Produto", "Preço");
    for (int i = 0; i < tamanho; i++)
        if (strcmp(cardapio[i].categoria, "Kids") == 0)
            printf("%-3d %-25s R$ %8.2f\n", i+1, cardapio[i].nome, cardapio[i].preco);

    printf("\n====================================================\n");
}

// Funcao para realizar o pedido
float realizarPedido(Produto cardapio[], int tamanho, Pedido pedidos[], int *qtdPedidos) {
    int opcao, qtd;
    float total = 0;
    *qtdPedidos = 0;

    while (1) {
        system("cls"); 
        mostrarCardapio(cardapio, tamanho);
        printf("Escolha o número do produto (0 para finalizar): ");
        if (scanf("%d", &opcao) != 1) {
            printf("Entrada inválida!\n");
            limparBuffer();
            continue;
        }
        limparBuffer();

        if (opcao == 0) break;
        if (opcao < 1 || opcao > tamanho) {
            printf("Opção inválida!\n");
            printf("Pressione ENTER para continuar...");
            getchar();
            continue;
        }

        printf("Quantidade: ");
        if (scanf("%d", &qtd) != 1 || qtd <= 0) {
            printf("Quantidade inválida!\n");
            limparBuffer();
            printf("Pressione ENTER para continuar...");
            getchar();
            continue;
        }
        limparBuffer();

        pedidos[*qtdPedidos].produto = cardapio[opcao-1];
        pedidos[*qtdPedidos].quantidade = qtd;
        total += cardapio[opcao-1].preco * qtd;
        (*qtdPedidos)++;
        if (*qtdPedidos >= 20) {
            printf("Limite de itens atingido!\n");
            break;
        }
    }
    return total;
}

// Funcao para pagamento
void pagamento(float total) {
    int opcao;
    printf("\nTotal a pagar: R$ %.2f\n", total);
    printf("Escolha a forma de pagamento:\n1 - Pix\n2 - Cartão\nOpção: ");
    if (scanf("%d", &opcao) != 1) {
        printf("Opção inválida! Pagamento não realizado.\n");
        exit(1);
    }
    limparBuffer();
    if (opcao == 1) {
        printf("Mostrando QR Code do Pix...\nPagamento realizado!\n");
    } else if (opcao == 2) {
        printf("Insira o cartão...\nPagamento aprovado!\n");
    } else {
        printf("Opção inválida! Pagamento não realizado.\n");
        exit(1);
    }
}

// Luis Eduardo: Sua tarefa é melhorar o codigo abaixo.
// O Objetivo é colocar o nome do cliente, CPF e telefone na nota fiscal.
// Também colocar o nome da lanchonete no topo da nota fiscal.
// Exibir na nota a forma de pagamento escolhida pelo cliente.
// E Deixar a nota fiscal mais bonita, com bordas e espaçamento adequado.(Se não for trabalhoso!)
void gerarNotaFiscal(Pedido pedidos[], int qtdPedidos, float total) {
    FILE *arquivo = fopen("nota_fiscal.txt", "w");
    if (!arquivo) {
        printf("Erro ao gerar nota fiscal!\n");
        return;
    }
    fprintf(arquivo, "==== NOTA FISCAL ====\n");
    for (int i = 0; i < qtdPedidos; i++) {
        fprintf(arquivo, "%s x%d - R$ %.2f\n", pedidos[i].produto.nome, pedidos[i].quantidade, pedidos[i].produto.preco * pedidos[i].quantidade);
    }
    fprintf(arquivo, "Total: R$ %.2f\n", total);
    fclose(arquivo);
    printf("Nota fiscal gerada: nota_fiscal.txt\n");
}

// metodo principal
int main() {
    Produto cardapio[] = {
        // Trios
        {"Trio Big Donald", 28.00, "Trio"},
        {"Trio Cheddar",    26.00, "Trio"},
        // Sobremesas
        {"Sundae", 10.00, "Sobremesa"},
        {"Casquinha", 6.00, "Sobremesa"},
        // Hamburgueres
        {"Big Donald",     18.00, "Hamburguer"},
        {"Cheddar Burger", 16.00, "Hamburguer"},
        {"Chicken Burger", 15.00, "Hamburguer"},
        // Kids
        {"Mini Burger", 12.00, "Kids"},
        {"Nuggets Kids", 13.00, "Kids"}

        // João Vitor: Sua tarefa é adicionar mais 5 produtos no cardápio.
        // Criar um ARRAY para Bebidas e adicionar 5 bebidas diferentes e seus preços.
        // Exemplo: {"Refrigerante", 5.00, "Bebida"}
        // Desafio: No struct Produto, criar uma nova variavel chamada "descricao" 
        // e adicionar uma descrição para cada produto.
    };
    Pedido pedidos[20];
    int qtdPedidos;
    float total;
    Cliente cliente;

    mostrarBemVindo();
    dadosDoCliente(&cliente);
    total = realizarPedido(cardapio, 9, pedidos, &qtdPedidos);
    if (total == 0) {
        printf("Nenhum pedido realizado.\n");
        return 0;
    }
    pagamento(total);
    gerarNotaFiscal(pedidos, qtdPedidos, total);

    return 0;

    // Guilherme: Sua tarefa é tirar os acentos do codigo.
    // Exemplo: "Pagamento não realizado." deve ser "Pagamento nao realizado."
    // Motivo: O gcc não aceita acentos.
}