#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>

int main()
{

	int opcao,i = 0,encontrado = 0;
	float valor[50][50];
	char produto[50][50],busca[50];
	char cardapio[50][50] = {
		"PASTEL = R$ 30.00",
		"FRITAS = R$ 45.00",
		"HEINEKEN = R$ 15.00",
		"COXINHA = R$ 20.00"
	};
	do
	{
		printf("\n====== MENU PRINCIPAL ======");
		printf("\n1 - Cadastrar produto");
		printf("\n2 - Listar Cardapio");
		printf("\n3 - Buscar Produto");
		printf("\n4 - Realizar Pedido");
		printf("\n5 - Adicionar Item do Pedido");
		printf("\n6 - Remover Item do Pedido");
		printf("\n7 - Calcular Total do Pedido");
		printf("\n8 - Listar Pedido");
		printf("\n9 - Cancelar Pedido");
		printf("\n10 - Finalizar Pedido");
		printf("\n0 - Sair ");
		printf("\n");
		scanf("%d",&opcao);
		
		switch(opcao)
		{
			case 1:
				{
					printf("Informe um produto a ser cadastrado: ");
					scanf("%s",&produto[i]);
					
					printf("\nInforme o valor do produto informado: ");
					scanf("%f",&valor[i]);
					break;
				}
			case 2:
				{
					printf("====== CARDAPIO ======\n");
					printf("1 - %s\n", cardapio[0]);
					printf("2 - %s\n", cardapio[1]);
					printf("3 - %s\n", cardapio[2]);
					printf("4 - %s\n", cardapio[3]);
					break;
				}
			case 3:
				{
					encontrado = 0;
					printf("Digite o produto que deseja buscar: ");
					scanf("%s", busca);

					for (i = 0; i < 4; i++)
					{
					    if (strcmp(busca, cardapio[i]) == 0)
					    {
    					    printf("Produto encontrado: %s\n", cardapio[i]);
       						encontrado = 1;
        					break;
    					}
					}

						if (encontrado == 0)
						{
    						printf("Produto nao encontrado.\n");
						}
					break;
				}
			case 4:
				{
					printf("\nRealizar Pedido: ");
				}
			case 5:
				{
					printf("\nAdicionar Item do Pedido: ");
				}
			case 6:
				{
					printf("\nRemover Item do Pedido: ");
				}
			case 7:
				{
					printf("\nCalcular Total do Pedido: ");
				}
			case 8:
				{
					printf("\nListar Pedido: ");
				}
			case 9:
				{
					printf("\nCancelar PEdido: ");
				}
			case 10:
				{
					printf("\nFinalizar Pedido: ");
				}
		}
		
	} while (opcao != 0);
	
	return 0;
}
