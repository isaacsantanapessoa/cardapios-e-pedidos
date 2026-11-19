#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define tam 37
#define maxProdutos 50
#define maxMesas 50

struct Produto {
    char nome[60];
    char categoria[30];
    float preco;
};

struct Mesa {
    int aberta;
};

struct Produto cardapio[maxProdutos] = {
    {"Heineken 600ml", "Cervejas", 17.00},
    {"Long Neck Heineken", "Cervejas", 11.00},
    {"Long Neck Heineken Zero", "Cervejas", 11.00},
    {"Amstel 600ml", "Cervejas", 12.00},
    {"Amstel Lata", "Cervejas", 6.00},
    {"Devassa 600ml", "Cervejas", 10.00},

    {"Tripa Suina", "Tira-Gosto", 49.00},
    {"Carne do Sol", "Tira-Gosto", 50.00},
    {"Carne do Sol Especial", "Tira-Gosto", 68.00},
    {"Camarao ao Alho e Oleo", "Tira-Gosto", 58.00},
    {"Sarapatel", "Tira-Gosto", 33.00},
    {"Salame Fatiado", "Tira-Gosto", 19.00},
    {"Prato de Frios", "Tira-Gosto", 39.00},

    {"Caldo de Sururu", "Caldos", 18.00},
    {"Caldo de Camarao", "Caldos", 18.00},
    {"Caldo de Aipim", "Caldos", 18.00},
    {"Caldo de Feijao", "Caldos", 18.00},

    {"Pasteis Recheados (8 un)", "Pasteis", 30.00},
    {"Batata Frita", "Porcoes", 30.00},

    {"Whisky Red Label", "Drinques", 15.00},
    {"Whisky Ballantines", "Drinques", 15.00},
    {"Campari", "Drinques", 11.00},
    {"Montilla", "Drinques", 9.00},
    {"Bacardi", "Drinques", 9.00},
    {"Vodka", "Drinques", 7.00},
    {"Cachaca Cabare", "Drinques", 7.00},
    {"Ice Cabare Limao", "Drinques", 11.00},
    {"Beats", "Drinques", 10.00},

    {"Refrigerante Lata", "Bebidas", 5.00},
    {"Refrigerante 1 Litro", "Bebidas", 10.00},
    {"Suco Del Valle", "Bebidas", 6.00},
    {"H2O", "Bebidas", 7.00},
    {"Red Bull", "Bebidas", 13.00},
    {"TNT Energy", "Bebidas", 11.00},
    {"Agua Tonica", "Bebidas", 7.00},
    {"Agua com Gas", "Bebidas", 4.00},
    {"Agua sem Gas", "Bebidas", 3.00}
};

struct Mesa mesas[maxMesas + 1] = {0};

int pedidos[maxMesas + 1][maxProdutos] = {0};

int qtdProdutos = tam;
int mesaAtiva = 0;

void listarCardapio() {
    int i;

    printf("\n====== CARDAPIO ======\n");

    for (i = 0; i < qtdProdutos; i++) {
        printf("\n%d - %s", i + 1, cardapio[i].nome);
        printf(" | Categoria: %s", cardapio[i].categoria);
        printf(" | R$ %.2f\n", cardapio[i].preco);
    }
}

void cadastrarProduto() {
    if (qtdProdutos >= maxProdutos) {
        printf("\nLimite de produtos atingido!\n");
        return;
    }

    printf("\nNome do produto: ");
    scanf(" %59[^\n]", cardapio[qtdProdutos].nome);

    printf("Categoria: ");
    scanf(" %29[^\n]", cardapio[qtdProdutos].categoria);

    printf("Preco: R$ ");
    scanf("%f", &cardapio[qtdProdutos].preco);

    if (cardapio[qtdProdutos].preco <= 0) {
        printf("\nO preco informado e invalido!\n");
        return;
    }

    qtdProdutos++;

    printf("\nProduto cadastrado!\n");
}

void buscarProduto() {
    char busca[60];
    int i, encontrado = 0;

    printf("\nDigite o nome do produto: ");
    scanf(" %59[^\n]", busca);

    for (i = 0; i < qtdProdutos; i++) {
        if (strcmp(busca, cardapio[i].nome) == 0) {
            printf("\nProduto encontrado!");
            printf("\nNome: %s", cardapio[i].nome);
            printf("\nCategoria: %s", cardapio[i].categoria);
            printf("\nPreco: R$ %.2f\n", cardapio[i].preco);

            encontrado = 1;
            break;
        }
    }

    if (encontrado == 0) {
        printf("\nProduto nao encontrado!\n");
    }
}

void realizarPedido() {
    int numero;

    printf("\nInforme o numero da mesa (1 a 50): ");
    
    if (scanf("%d", &numero) != 1) {
        printf("\nDigite apenas o numero da mesa!\n");
        while (getchar() != '\n');
        return;
    }

    if (numero < 1 || numero > maxMesas) {
        printf("\nNumero de mesa invalido!\n");
        return;
    }

    if (mesas[numero].aberta == 1) {
        printf("\nEssa mesa ja possui um pedido aberto.\n");
        printf("Pedido da mesa %d selecionado!\n", numero);
    } else {
        mesas[numero].aberta = 1;
        printf("\nPedido iniciado na mesa %d!\n", numero);
    }

    mesaAtiva = numero;
}

void adicionarItemPedido() {
    int codigo, quantidade;

    if (mesaAtiva == 0 || mesas[mesaAtiva].aberta == 0) {
        printf("\nRealize um pedido primeiro!\n");
        return;
    }

    listarCardapio();

    printf("\nCodigo do produto: ");

    if (scanf("%d", &codigo) != 1) {
        printf("\nDigite apenas o numero do produto!\n");
        while (getchar() != '\n');
        return;
    }

    if (codigo < 1 || codigo > qtdProdutos) {
        printf("\nCodigo invalido!\n");
        return;
    }

    printf("Quantidade: ");

    if (scanf("%d", &quantidade) != 1) {
        printf("\nDigite uma quantidade valida!\n");
        while (getchar() != '\n');
        return;
    }

    if (quantidade <= 0) {
        printf("\nQuantidade invalida!\n");
        return;
    }

    pedidos[mesaAtiva][codigo - 1] += quantidade;

    printf("\nItem adicionado ao pedido!\n");
}

void removerItemPedido() {
    int codigo, quantidade;

    if (mesaAtiva == 0 || mesas[mesaAtiva].aberta == 0) {
        printf("\nNenhum pedido ativo!\n");
        return;
    }

    listarCardapio();

    printf("\nCodigo do produto: ");

    if (scanf("%d", &codigo) != 1) {
        printf("\nDigite apenas o numero do produto!\n");
        while (getchar() != '\n');
        return;
    }

    if (codigo < 1 || codigo > qtdProdutos) {
        printf("\nCodigo invalido!\n");
        return;
    }

    if (pedidos[mesaAtiva][codigo - 1] == 0) {
        printf("\nEsse produto nao esta no pedido!\n");
        return;
    }

    printf("Quantidade que deseja remover: ");

    if (scanf("%d", &quantidade) != 1) {
        printf("\nDigite uma quantidade valida!\n");
        while (getchar() != '\n');
        return;
    }

    if (quantidade <= 0 ||
        quantidade > pedidos[mesaAtiva][codigo - 1]) {
        printf("\nQuantidade invalida!\n");
        return;
    }

    pedidos[mesaAtiva][codigo - 1] -= quantidade;

    printf("\nItem removido do pedido!\n");
}

float calcularTotalPedido() {
    int i;
    float total = 0;

    for (i = 0; i < qtdProdutos; i++) {
        total += pedidos[mesaAtiva][i] * cardapio[i].preco;
    }

    return total;
}

void listarPedido() {
    int i, encontrou = 0;

    if (mesaAtiva == 0 || mesas[mesaAtiva].aberta == 0) {
        printf("\nNenhum pedido ativo!\n");
        return;
    }

    printf("\n====== PEDIDO DA MESA %d ======\n", mesaAtiva);

    for (i = 0; i < qtdProdutos; i++) {
        if (pedidos[mesaAtiva][i] > 0) {
            printf("\nProduto: %s", cardapio[i].nome);
            printf("\nQuantidade: %d", pedidos[mesaAtiva][i]);
            printf("\nSubtotal: R$ %.2f\n",
                   pedidos[mesaAtiva][i] * cardapio[i].preco);

            encontrou = 1;
        }
    }

    if (encontrou == 0) {
        printf("\nO pedido ainda esta vazio!\n");
    }

    printf("\nTotal: R$ %.2f\n", calcularTotalPedido());
}

void cancelarPedido() {
    int i;

    if (mesaAtiva == 0 || mesas[mesaAtiva].aberta == 0) {
        printf("\nNenhum pedido ativo!\n");
        return;
    }

    for (i = 0; i < qtdProdutos; i++) {
        pedidos[mesaAtiva][i] = 0;
    }

    mesas[mesaAtiva].aberta = 0;

    printf("\nPedido da mesa %d cancelado!\n", mesaAtiva);

    mesaAtiva = 0;
}

void finalizarPedido() {
    float total;
    int i;

    if (mesaAtiva == 0 || mesas[mesaAtiva].aberta == 0) {
        printf("\nNenhum pedido ativo!\n");
        return;
    }

    total = calcularTotalPedido();

    printf("\n====== FINALIZACAO DO PEDIDO ======\n");
    printf("\nMesa: %d", mesaAtiva);
    printf("\nTotal a pagar: R$ %.2f\n", total);

    mesas[mesaAtiva].aberta = 0;

    for (i = 0; i < qtdProdutos; i++) {
        pedidos[mesaAtiva][i] = 0;
    }

    printf("\nPedido finalizado com sucesso!\n");

    mesaAtiva = 0;
}

int main() {
    int opcao;

    setlocale(LC_ALL, "Portuguese");

    do {
        printf("\n====== MENU PRINCIPAL ======\n");
        printf("\n1 - Cadastrar produto");
        printf("\n2 - Listar cardapio");
        printf("\n3 - Buscar produto");
        printf("\n4 - Realizar pedido");
        printf("\n5 - Adicionar item ao pedido");
        printf("\n6 - Remover item do pedido");
        printf("\n7 - Calcular total do pedido");
        printf("\n8 - Listar pedido");
        printf("\n9 - Cancelar pedido");
        printf("\n10 - Finalizar pedido");
        printf("\n0 - Sair");

        printf("\n\nEscolha uma opcao: ");

        if (scanf("%d", &opcao) != 1) {
            printf("\nDigite uma opcao valida!\n");
            while (getchar() != '\n');
            continue;
        }

        switch (opcao) {
            case 1:
                cadastrarProduto();
                break;

            case 2:
                listarCardapio();
                break;

            case 3:
                buscarProduto();
                break;

            case 4:
                realizarPedido();
                break;

            case 5:
                adicionarItemPedido();
                break;

            case 6:
                removerItemPedido();
                break;

            case 7:
                if (mesaAtiva != 0 && mesas[mesaAtiva].aberta == 1) {
                    printf("\nTotal do pedido: R$ %.2f\n",
                           calcularTotalPedido());
                } else {
                    printf("\nNenhum pedido ativo!\n");
                }
                break;

            case 8:
                listarPedido();
                break;

            case 9:
                cancelarPedido();
                break;

            case 10:
                finalizarPedido();
                break;

            case 0:
                printf("\nEncerrando o sistema...\n");
                break;

            default:
                printf("\nOpcao invalida! Tente novamente.\n");
        }

    } while (opcao != 0);

    system("pause");

    return 0;
}
