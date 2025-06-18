#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char nome[50];
    char descricao[100]; // NOVO
    float preco;
    char categoria[50];
} Produto;

typedef struct
{
    Produto produto;
    int quantidade;
} Pedido;

typedef struct
{
    char nome[50];
    char CPF[15];
    char telefone[15];
} Cliente;

void limparBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

void mostrarBemVindo() {
    system("cls"); // Somente no Windows!
    printf("=======================================================\n");
    printf("|                    DONALD FOOD                      |\n");
    printf("=======================================================\n\n");
}

// Funcao para coletar dados do cliente
void dadosDoCliente(Cliente *cliente)
{
    printf("Digite seu nome: ");
    fgets(cliente->nome, sizeof(cliente->nome), stdin);
    cliente->nome[strcspn(cliente->nome, "\n")] = 0;

    printf("Digite seu CPF: ");
    fgets(cliente->CPF, sizeof(cliente->CPF), stdin);
    cliente->CPF[strcspn(cliente->CPF, "\n")] = 0;

    printf("Digite seu telefone: ");
    fgets(cliente->telefone, sizeof(cliente->telefone), stdin);
    cliente->telefone[strcspn(cliente->telefone, "\n")] = 0;

    printf("\nBem-vindo, %s! Seu pedido sera entregue em breve.\n", cliente->nome);
    printf("Pressione ENTER para continuar...");
    getchar();
    system("cls");
}

void mostrarCardapio(Produto cardapio[], int tamanho)
{
    printf("====================================================\n");
    printf("                    CARDAPIO                        \n");
    printf("====================================================\n\n");

    printf("--------------------- Trios ------------------------\n");
    printf("%-3s %-25s %10s\n", "Id", "Produto", "Preco");
    for (int i = 0; i < tamanho; i++)
        if (strcmp(cardapio[i].categoria, "Trio") == 0)
            printf("%-3d %-25s R$ %8.2f\n", i + 1, cardapio[i].nome, cardapio[i].preco);
    printf("\n");

    printf("------------------- Sobremesas ---------------------\n");
    printf("%-3s %-25s %10s\n", "Id", "Produto", "Preco");
    for (int i = 0; i < tamanho; i++)
        if (strcmp(cardapio[i].categoria, "Sobremesa") == 0)
            printf("%-3d %-25s R$ %8.2f\n", i + 1, cardapio[i].nome, cardapio[i].preco);
    printf("\n");

    printf("------------------ Hamburgueres --------------------\n");
    printf("%-3s %-25s %10s\n", "Id", "Produto", "Preco");
    for (int i = 0; i < tamanho; i++)
        if (strcmp(cardapio[i].categoria, "Hamburguer") == 0)
            printf("%-3d %-25s R$ %8.2f\n", i + 1, cardapio[i].nome, cardapio[i].preco);
    printf("\n");

    printf("---------------------- Bebidas ------------------------\n");
    printf("%-3s %-25s %10s\n", "Id", "Produto", "Preco");
    for (int i = 0; i < tamanho; i++)
        if (strcmp(cardapio[i].categoria, "Bebida") == 0)
            printf("%-3d %-25s R$ %8.2f\n", i + 1, cardapio[i].nome, cardapio[i].preco);
    printf("\n");
    
    printf("---------------------- Kids ------------------------\n");
    printf("%-3s %-25s %10s\n", "Id", "Produto", "Preco");
    for (int i = 0; i < tamanho; i++)
        if (strcmp(cardapio[i].categoria, "Kids") == 0)
            printf("%-3d %-25s R$ %8.2f\n", i + 1, cardapio[i].nome, cardapio[i].preco);

    printf("\n====================================================\n");
}

float realizarPedido(Produto cardapio[], int tamanho, Pedido pedidos[], int *qtdPedidos)
{
    int opcao, qtd;
    float total = 0;
    *qtdPedidos = 0;

    while (1)
    {
        system("cls");
        mostrarCardapio(cardapio, tamanho);
        printf("Escolha o numero do produto (0 para finalizar): ");
        if (scanf("%d", &opcao) != 1) {
            printf("Entrada invalida!\n");
            limparBuffer();
            continue;
        }
        limparBuffer();

        if (opcao == 0) break;
        if (opcao < 1 || opcao > tamanho) {
            printf("Opcao invalida!\n");
            printf("Pressione ENTER para continuar...");
            getchar();
            continue;
        }

        printf("Quantidade: ");
        if (scanf("%d", &qtd) != 1 || qtd <= 0) {
            printf("Quantidade invalida!\n");
            limparBuffer();
            printf("Pressione ENTER para continuar...");
            getchar();
            continue;
        }
        limparBuffer();

        pedidos[*qtdPedidos].produto = cardapio[opcao - 1];
        pedidos[*qtdPedidos].quantidade = qtd;
        total += cardapio[opcao - 1].preco * qtd;
        (*qtdPedidos)++;
        if (*qtdPedidos >= 20)
        {
            printf("Limite de itens atingido!\n");
            break;
        }
    }
    return total;
}

// NOVA função para gerar nota fiscal mais bonita
void gerarNotaFiscal(Pedido pedidos[], int qtdPedidos, float total, Cliente cliente, char* formaPagamento) {
    FILE *arquivo = fopen("nota_fiscal.txt", "w");
    if (!arquivo) {
        printf("Erro ao gerar nota fiscal!\n");
        return;
    }

    fprintf(arquivo, "+================================================================================+\n");
    fprintf(arquivo, "|                             DONALD FOOD                                        |\n");
    fprintf(arquivo, "+================================================================================+\n");
    fprintf(arquivo, "| Cliente: %-65s |\n", cliente.nome);
    fprintf(arquivo, "| CPF: %-70s |\n", cliente.CPF);
    fprintf(arquivo, "| Telefone: %-64s |\n", cliente.telefone);
    fprintf(arquivo, "+--------------------------------------------------------------------------------+\n");
    fprintf(arquivo, "| Qtd | Produto             | Preço   | Total   | Categoria                     |\n");
    fprintf(arquivo, "+--------------------------------------------------------------------------------+\n");

    for (int i = 0; i < qtdPedidos; i++) {
        float subt = pedidos[i].produto.preco * pedidos[i].quantidade;
        fprintf(arquivo, "| %-3d | %-19s | R$%6.2f | R$%6.2f | %-28s |\n",
                pedidos[i].quantidade,
                pedidos[i].produto.nome,
                pedidos[i].produto.preco,
                subt,
                pedidos[i].produto.categoria);
    }

    fprintf(arquivo, "+--------------------------------------------------------------------------------+\n");
    fprintf(arquivo, "| Forma de Pagamento: %-53s |\n", formaPagamento);
    fprintf(arquivo, "| TOTAL A PAGAR: R$ %9.2f                                           |\n", total);
    fprintf(arquivo, "+================================================================================+\n");

    fclose(arquivo);
    printf("Nota fiscal gerada: nota_fiscal.txt\n");
}



int main()
{
    Produto cardapio[] = {
        // Trios
        {"Trio Big Donald", "Trio com hamburguer, batata e refri", 28.00, "Trio"},
        {"Trio Cheddar", "Trio com cheddar burger, batata e refri", 26.00, "Trio"},
        // Sobremesas
        {"Sundae", "Sorvete com calda", 10.00, "Sobremesa"},
        {"Casquinha", "Casquinha de baunilha", 6.00, "Sobremesa"},
        // Hamburgueres
        {"Big Donald", "Hamburguer classico", 18.00, "Hamburguer"},
        {"Cheddar Burger", "Hamburguer com cheddar", 16.00, "Hamburguer"},
        {"Chicken Burger", "Hamburguer de frango", 15.00, "Hamburguer"},
        {"Patolino Picante", "Hamburguer apimentado", 21.00, "Hamburguer"},
        {"Super tio patinhas", "Hamburguer gigante", 32.00, "Hamburguer"},
        {"Lago cheddar", "Hamburguer com cheddar duplo", 18.00, "Hamburguer"},

        // Bebidas
        {"Patolino suico", "Limao suico gelado", 7.00, "Bebida"},
        {"Frozen do Pato", "Frozen sabor pato", 9.00, "Bebida"},
        {"Pato gelado", "Bebida gelada sabor pato", 10.00, "Bebida"},
        {"Refri do Lago", "Refrigerante tradicional", 6.00, "Bebida"},
        {"Refrigerante", "Coca-cola 350ml", 5.00, "Bebida"},
        {"Suco de Laranja", "Suco natural 300ml", 6.50, "Bebida"},
        {"Agua", "Agua mineral sem gas", 3.00, "Bebida"},
        {"Cha gelado", "Chá gelado limão 300ml", 6.00, "Bebida"},
        {"Milk-shake", "Milk-shake de chocolate 300ml", 11.00, "Bebida"},

        // Kids
        {"Mini Burger", "Hamburguer kids", 12.00, "Kids"},
        {"Nuggets Kids", "Nuggets kids", 13.00, "Kids"}
    };

    Pedido pedidos[20];
    int qtdPedidos;
    float total;
    Cliente cliente;
    char formaPagamento[20];

    int tamanhoCardapio = sizeof(cardapio)/sizeof(cardapio[0]);

    mostrarBemVindo();
    dadosDoCliente(&cliente);
    total = realizarPedido(cardapio, tamanhoCardapio, pedidos, &qtdPedidos);
    if (total == 0)
    {
        printf("Nenhum pedido realizado.\n");
        return 0;
    }

    printf("\nTotal a pagar: R$ %.2f\n", total);
    printf("Escolha a forma de pagamento:\n1 - Pix\n2 - Cartao\n3 - Dinheiro\nOpcao: ");
    int opcaoPagamento;
    if (scanf("%d", &opcaoPagamento) != 1)
    {
        printf("Opcao invalida! Pagamento nao realizado.\n");
        exit(1);
    }
    limparBuffer();
    if (opcaoPagamento == 1)
        strcpy(formaPagamento, "Pix");
    else if (opcaoPagamento == 2)
        strcpy(formaPagamento, "Cartao");
    else if (opcaoPagamento == 3)
        strcpy(formaPagamento, "Dinheiro");
    else
    {
        printf("Opcao invalida! Pagamento nao realizado.\n");
        exit(1);
    }

    gerarNotaFiscal(pedidos, qtdPedidos, total, cliente, formaPagamento);

    return 0;
}