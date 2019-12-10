#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>

//Declaração de Registros
typedef struct Endereco
{
	char rua[10];
	char casa[5];
	char bairro[10];
}Endereco;

typedef struct Caixa
{
	char nome[30];
	int matricula;
	char telefone[15];
	Endereco endereco;
}Caixa;

typedef struct Produto
{
	char nome_produto[20]; 
	float preco;
	int quantidade;
	int cod_barra;
	char validade[8];	
}Produto;

typedef struct Venda
{
	Caixa caixa;
	Produto produto;
	char nome_produto[20],nome_cliente[30];
	int quant, cod_barra;
	float vtotal;
}Venda;

//Declaração de variavel global
FILE *a_caixa, *a_produto, *a_venda;

//Declaração de assinaturas de metodos e funções
void Formato(int a);
//Realizar Vendas
void Vendas();
//Menus
void Login();
void Menu_Gerente();
void Menu_Funcionario();
void Menu_Relatorio();
int Menu_Secundario();
int Menu_UD();
//Cadastros
void Cadastro_Caixa();
void Cadastro_Produto();
//Pesquisas
void Pesquisar_Caixa();
void Pesquisar_Produto();
//Alterar
void Alterar_Caixa(int matricula);
void Alterar_Produto(int codigo);
//Excluir
void Excluir_Caixa(int matricula);
void Excluir_Produto(int codigo);
//Verificação de disponibilidade em estoque para venda
bool Estoque(int quantidade);
//Calculo do troco
void Troco(float total, float pago);
//Relatorios
void Relatorio_Vendas();
//void Relatorio_Estoque();

//Metodo pricipal main
main()
{
	Login();
}
//Fim da main

//Funções e Metodos

//Formatação
void Formato(int a)
{
	switch(a)
	{
		case 1:
			//Menus limpa a tela e muda a cor para o padrão de menu (funcdo branco, letras pretas)
			system("cls");
			system("Color f0");
		break;
			
		case 2:
			//Opção invalida menssagem de erro e muda a cor para o padrão de erro (fundo vermelho, letras brancas)
			system("cls");
			system("color 4f");
			printf("\n\t\tOpcao invalida!\n\n");
			Sleep(2000);
		break;
			
		case 3:
			//Pesquisa invalida menssagem de erro se a a busca não tiver resultado cor padrão de erro (fundo vermelho, letras brancas)
			system("cls");
			system("color 4f");
			printf("\n\t\tResultado da pesquisa: Nao encontra-se cadastrado\n\n");
			Sleep(2000);
		break;
			
		case 4:
			//Realizar algum metodo do menu limpa a tela e muda a cor para o padrão de realização de procedimento (funcdo azul, letras brancas)
			system("cls");
			system("Color b0");
		break;
			
		case 5:
			//Tela de confirmação de termino bem sucedido de alguma funcionalidade (Cadastrar, Alterar, Excluir e Realizar Venda)
			system("cls");
			system("Color a0");
			printf("\n\t\tOperacao realizada com sucesso!\n\n");
			Sleep(2000);
		break;
			
		case 6:
			//Quando realizar pesquisa e tiver sucesso retorna uma mensagem com letras verdes
			printf("\nO nome pesquisado encontra-se cadastrado\n\n");
		break;
			
		case 7:
			//Quando realizar pesquisa e não tiver sucesso retorna uma mensagem com letras vermelhas
			system("color b4");
			printf("\n\t\tO nome pesquisado nao encontra-se cadastrado\n\n");
			Sleep(2000);
		break;
		
		case 8:
			//Quando realizar uma venda
			system("cls");
			system("Color a0");
			printf("\n\tCompra realizada com sucesso!\n\tAgradecemos a preferencia volte sempre");
			Sleep(2000);
		break;
	}
}
//Fim do formato

//Login
void Login(){
	Formato(1);
	char login[10];
	int senha;
	
	system("cls");
	
	printf("Login: \n");
	fflush(stdin);
	gets(login);
	printf("Senha: \n");
	scanf("%d",&senha);
	
	if(strcmp(login,"gerente")==0 && senha==123){
		Menu_Gerente();
	}else if(strcmp(login,"func")==0 && senha==456){
		Menu_Funcionario();
	}else{
		Formato(2);
	}
	
	
}//Fim do login

//Menu do Gerente
void Menu_Gerente()
{
	int op, menu,result;
	
	do
	{
		Formato(1);
		system("Title Menu");
		printf("\n***************** Menu *****************\n");
		printf("\n[1] - Cadastrar\n[2] - Pesquisar\n[3] - Realizar Venda\n[4] - Relatorio\n[0] - Sair\n");
		scanf("%d",&op);
		
		switch(op)
		{
			case 1:
				menu = Menu_Secundario();
				if(menu == 1)
				{
					Cadastro_Caixa();	
				}
				else if(menu == 2)
				{
					Cadastro_Produto();
				}	
			break;
			
			case 2:
				menu = Menu_Secundario();
				if(menu == 1)
				{
					Pesquisar_Caixa();	
				}
				else if(menu == 2)
				{
					Pesquisar_Produto();
				}	
			break;
			
			case 3:
				Vendas();
			break;
			
			case 4:
				Menu_Relatorio();
			break;
							
			case 0:
				exit(0);
			break;
			
			default:
				Formato(2);
				Menu_Gerente();
			break;
		}
		
	}while(op!=0);
	
}
//Fim menu do gerente

void Menu_Funcionario(){
	int op, menu,result;
	
	do
	{
		Formato(1);
		system("Title Menu");
		printf("\n***************** Menu *****************\n");
		printf("\n[1] - Realizar Venda\n[0] - Sair\n");
		scanf("%d",&op);
		
		switch(op)
		{
			case 1:
				Vendas();	
			break;
							
			case 0:
				exit(0);
			break;
			
			default:
				Formato(2);
				Menu_Gerente();
			break;
		}
		
	}while(op!=0);
}//Fim Menu Funcionario

//Menu secundario retorna um valor para cada perfil do sistema (1 - Caixa; 2 - Produto)
int Menu_Secundario()
{
	int op;
	
	do
	{
		Formato(1);
		system("Title Menu");
		printf("\n***************** Menu *****************\n");
		printf("\n[1] - Caixa\n[2] - Produto\n[0] - Voltar\n");
		scanf("%d",&op);
		
		switch(op)
		{
			case 1:
				return 1;
			break;
			
			case 2:
				return 2;
			break;
			
			case 0:
				Menu_Gerente();
			break;
			
			default:
				Formato(2);
				Menu_Secundario();
			break;
		}
		
	}while(op!=0);
	
}
//Fim menu secundario

//Menu para controle de relatórios
void Menu_Relatorio()
{
	int op;
	
	do
	{
		Formato(1);
		system("Title Menu");
		printf("\n***************** Menu *****************\n");
		printf("\n[1] - Relatorio de Vendas\n[2] - Relatorio de Estoque\n[0] - Voltar\n");
		scanf("%d",&op);
		
		switch(op)
		{
			case 1:
				 Relatorio_Vendas();
				break;
			
			case 2:

				//Relatorio_Estoque();
				break;
				
			case 0:
				Menu_Gerente();
				break;
			
			default:
				Formato(2);
				Menu_Relatorio();
				break;
		}
		
	}while(op!=0);
}
//Fim menu relatorio

//Menu UD (Update e Delete)
int Menu_UD()
{
	int op;
	
	do
	{
		printf("\n[1] - Alterar\n[2] - Excluir\n[0] - Voltar\n");
		scanf("%d",&op);
		
		switch(op)
		{
			case 1:
				return 1;
			break;
			
			case 2:

				return 2;
			break;
				
			case 0:
				Menu_Gerente();
			break;
			
			default:
				Formato(2);
				Menu_Gerente();
			break;
		}
		
	}while(op!=0);
}
//Fim Menu UD (Alterar e Excluir)

//Metodos de Cadastro

//Cadastro de Caixa
void Cadastro_Caixa()
{
	Caixa caixa;
	
	Formato(4);
	system("Title Cadastro de Caixa");
	
	a_caixa = fopen("Caixa.txt","ab+");
	
	printf("\n***************** Cadastro de Caixa *****************");
	printf("\n------------- Dados -------------\n");
	printf("Nome: ");
	fflush(stdin);
	gets(caixa.nome);
	printf("\nMatricula: ");
	scanf("%d", &caixa.matricula);
	printf("\nTelefone: ");
	fflush(stdin);
	gets(caixa.telefone);
	printf("\n------------ Endereco -----------");
	printf("\nRua: ");
	fflush(stdin);
	gets(caixa.endereco.rua);
	printf("\nCasa: ");
	fflush(stdin);
	gets(caixa.endereco.casa);
	printf("\nBairro: ");
	fflush(stdin);
	gets(caixa.endereco.bairro);
	
	fwrite(&caixa, sizeof(Caixa), 1, a_caixa);
	
	fclose(a_caixa);
	
	Formato(5);
	
}
//Fim cadastro de Funcionario

//Cadastro de Produtos
void Cadastro_Produto()
{
	Produto produto;
	int qtd,i;
	
	Formato(4);
	system("Title Cadastro de Produto");
	
	a_produto = fopen("Produto.txt","ab+");
	
	printf("\n***************** Cadastro de Produto *****************\n");
	printf("Nome: ");
	fflush(stdin);
	gets(produto.nome_produto);
	printf("\nValor: R$ ");
	scanf("%f", &produto.preco);
	printf("\nQuantidade em estoque: ");
	scanf("%d", &produto.quantidade);
	printf("\nData de Validade: ");
	fflush(stdin);
	gets(produto.validade);
	printf("\nCodigo de barra: ");
	scanf("%d", &produto.cod_barra);
	
	fwrite(&produto,sizeof(Produto),1,a_produto);
	
	fclose(a_produto);
	
	Formato(5);
}
//Fim cadastro de produtos

//Metodos de Pesquisa

//Pesquisa de caixa por numero de matricula
void Pesquisar_Caixa()
{
	Caixa caixa;
	int matricula_pesq, ud;
	bool acesso = false;
	
	Formato(4);
	system("Title Pesquisa de Caixa");
	
	a_caixa = fopen("Caixa.txt", "rb");
	
	printf("\n***************** Pesquisa de Caixa *****************\n");
	printf("Pesquisar matricula: ");
	scanf("%d", &matricula_pesq);
	
	rewind(a_caixa);
	
	while(!feof(a_caixa))
	{
		fread(&caixa, sizeof(Caixa), 1, a_caixa);
		
		if(!feof(a_caixa))
		{
			if(matricula_pesq == caixa.matricula)
			{
				system("cls");
				printf("\n***************** Resultado da Pesquisa *****************");
				Formato(6);
				printf("------------- Dados -------------\n");
				printf("Nome: %s", caixa.nome);
				printf("\nMatricula: %d", caixa.matricula);
				printf("\nTelefone: %s", caixa.telefone);
				printf("\n------------ Endereco -----------");
				printf("\nRua: %s", caixa.endereco.rua);
				printf("\nCasa: %s", caixa.endereco.casa);
				printf("\nBairro: %s\n\n", caixa.endereco.bairro);
				
				ud = Menu_UD();
		
				if(ud == 1)
				{
					Alterar_Caixa(matricula_pesq);
				}
				else if(ud == 2)
				{
					Excluir_Caixa(matricula_pesq);
				}
		
				acesso = true;
				break;
			}
		}
	}
	
	if(acesso==false)
	{
		Formato(7);
	}
	
	fclose(a_caixa);
	
	system("pause");
}
//Fim da pesquisa de funcionario por matricula

//Pesquisa de produto por codigo de barra
void Pesquisar_Produto()
{
	Produto produto;
	int cod_pesq, ud;
	bool acesso = false;
	
	Formato(4);
	system("Title Pesquisa de Produto");
	
	a_produto = fopen("Produto.txt", "rb");
	
	printf("\n***************** Pesquisa de Produto *****************\n");
	printf("Pesquisar Codigo de barra do produto: ");
	scanf("%d", &cod_pesq);
	
	rewind(a_produto);
	
	while(!feof(a_produto))
	{
		fread(&produto, sizeof(Produto), 1, a_produto);
		
		if(!feof(a_produto))
		{
			if(cod_pesq == produto.cod_barra)
			{
				system("cls");
				printf("\n***************** Resultado da Pesquisa *****************");
				Formato(6);
				printf("------------- Dados -------------\n");
				printf("Nome do produto: %s", produto.nome_produto);
				printf("\nPreco: R$%.2f", produto.preco);
				printf("\nValidade: %s", produto.validade);
				printf("\nQuantidade do Produto em Estoque: %d", produto.quantidade);
				printf("\nCodigo de Barra: %d\n\n", produto.cod_barra);
				acesso = true;
				break;
			}
		}
	}
	
	if(acesso==false)
	{
		Formato(7);
	}
	else
	{
		ud = Menu_UD();
		
		if(ud == 1)
		{
			Alterar_Produto(cod_pesq);
		}
		else if(ud == 2)
		{
			Excluir_Produto(cod_pesq);
		}
		else if(ud == 0)
		{
			Menu_Gerente();
		}
	}
	
	fclose(a_produto);
	
	system("pause");
}
//Fim da pesquisa de produto por codigo de barra

//Metodos para alterar os dados

//Alterar dados do caixa
void Alterar_Caixa(int matricula)
{
	Caixa caixa;
	bool acesso = false;
	int cont=-1;
	
	Formato(4);
	system("Title Alterar Dados do Caixa");
	
	a_caixa = fopen("Caixa.txt", "rb+");
	
	rewind(a_caixa);
	
	while(!feof(a_caixa))
	{
		fread(&caixa, sizeof(Caixa), 1, a_caixa);
		
		if(!feof(a_caixa))
		{
			cont++;

			if(matricula == caixa.matricula)
			{
				system("cls");
				printf("\n***************** Alterar Dados do Caixa *****************\n");

				printf("\nNovo Nome: ");
				fflush(stdin);
				gets(caixa.nome);
				printf("\nNova Matricula: ");
				scanf("%d", &caixa.matricula);
				printf("\nNovo Telefone: ");
				fflush(stdin);
				gets(caixa.telefone);
				printf("\nNova Endereco\n");
				printf("\nRua: ");
				fflush(stdin);
				gets(caixa.endereco.rua);
				printf("\nCasa: ");
				fflush(stdin);
				gets(caixa.endereco.casa);
				printf("\nBairro: ");
				fflush(stdin);
				gets(caixa.endereco.bairro);
				
				fseek(a_caixa, cont*sizeof(Caixa), SEEK_SET);
				fwrite(&caixa, sizeof(Caixa), 1,  a_caixa);
				
				acesso = true;
				Formato(5);
				system("pause");
				break;
			}
		}
	}
	
	if(acesso == false)
	{
		Formato(3);
	}
	
	fclose(a_caixa);
	
	Menu_Gerente();
}
//Fim da alteração dados do Produto
void Alterar_Produto(int codigo)
{
	Produto produto;
	int cont=-1,op=0;
	bool acesso=false;
	
	Formato(4);
	a_produto = fopen("Produto.txt","rb+");
	
	rewind(a_produto);
	
	while(!feof(a_produto))
	{
		fread(&produto,sizeof(Produto),1,a_produto);
		
		if(!feof(a_produto))
		{
			cont++;
		
			if(codigo == produto.cod_barra)
			{			
				system("cls");
				printf("\n***************** Alterar Dados do Produto *****************\n");		
				
				printf("Nome do Produto: ");
				fflush(stdin);
				gets(produto.nome_produto);
				printf("\nPreco: ");
				scanf("%f",&produto.preco);
				printf("\nQuantidade: ");
				scanf("%d",&produto.quantidade);
				printf("\nValidade: ");
				fflush(stdin);
				gets(produto.validade);
				printf("\nCodigo de Barra: ");
				scanf("%d", &produto.cod_barra);		
				
				fseek(a_produto,cont*sizeof(Produto),SEEK_SET);
				fwrite(&produto,sizeof(Produto),1,a_produto);		
				
				acesso = true;
				Formato(5);				
				system("pause");
				break;
			}	              
		}
	}
			
	if(acesso==false)
	{
		Formato(3);
	}
	
	fclose(a_produto);
		
	Menu_Gerente();
}
//Fim da alteração de dados dos produtos cadastrados

//Metodo para excluir cadastro

//Excluir cadastro de funcionario
void Excluir_Caixa(int matricula)
{	
	Caixa caixa, *auxiliar;
	bool acesso = false;
	int cont = -1, i=0;
	Formato(4);
	
	a_caixa = fopen("Caixa.txt","rb");
	
	rewind(a_caixa);
	
	while(!feof(a_caixa))
	{
		fread(&caixa, sizeof(Caixa), 1, a_caixa);
		if(!feof(a_caixa))
		{
			cont++;
		}
	}
		
	auxiliar = (Caixa*) malloc(sizeof(Caixa)*cont);	
	
	system("Title Excluir Cadastro de Caixa");

	rewind(a_caixa);
	
	while(!feof(a_caixa))
	{
		fread(&caixa, sizeof(Caixa), 1, a_caixa);
		
		
		if(!feof(a_caixa))
		{
			if(matricula == caixa.matricula)
			{
				acesso = true;
			}
			else
			{
				
				strcpy(auxiliar[i].nome, caixa.nome);
				auxiliar[i].matricula = caixa.matricula;
				strcpy(auxiliar[i].telefone, caixa.telefone);
				strcpy(auxiliar[i].endereco.rua, caixa.endereco.rua);
				strcpy(auxiliar[i].endereco.casa, caixa.endereco.casa);
				strcpy(auxiliar[i].endereco.bairro, caixa.endereco.bairro);
				i++;
			}
		}
	}
	
	fclose(a_caixa);
	
	if(acesso == true)
	{
		cont = cont-1;
		
		a_caixa = fopen("Caixa.txt","wb");
		
		fwrite(auxiliar, sizeof(Caixa), cont, a_caixa);
		
		fclose(a_caixa);
		
		Formato(5);
	}
	else
	{
		Formato(3);
	}

	
	
}
//Fim excluir cadastro de funcionario

//Excluir cadastro de produto
void Excluir_Produto(int codigo)
{	
	Produto produto, *auxiliar;
	bool acesso = false;
	int cont = -1, i=0;
	Formato(4);
	
	a_produto = fopen("Produto.txt","rb");
	
	rewind(a_produto);
	
	while(!feof(a_produto))
	{
		fread(&produto, sizeof(Produto), 1, a_produto);
		if(!feof(a_produto))
		{
			cont++;
		}
	}
		
	auxiliar = (Produto*) malloc(sizeof(Produto)*cont);	
	
	system("Title Excluir Cadastro de Produto");
		
	rewind(a_produto);
	
	while(!feof(a_produto))
	{
		fread(&produto, sizeof(Produto), 1, a_produto);
		
		if(!feof(a_produto))
		{
			if(codigo == produto.cod_barra)
			{
				acesso = true;	
			}
			else
			{
				strcpy(auxiliar[i].nome_produto, produto.nome_produto);
				strcpy(auxiliar[i].validade, produto.validade);
				auxiliar[i].preco = produto.preco;
				auxiliar[i].quantidade = produto.quantidade;
				auxiliar[i].cod_barra = produto.cod_barra;
				i++;
			}
		}
	}
	
	fclose(a_produto);
	
	if(acesso==true)
	{
		cont = cont-1;
		
		a_produto = fopen("Produto.txt","wb");
		
		fwrite(auxiliar, sizeof(Produto), cont, a_produto);
		
		fclose(a_produto);
		
		Formato(5);
	}
	else
	{
		Formato(3);
	}
	
}
//Fim excluir cadastro de produto


void Vendas()
{	
	Venda venda;
	Produto produto;
	int op, cod_pesq, qtd, cont = -1;
	float total = 0, vpago, troco;
	bool estoque = false;
	
	system("Title Realizar Venda");
	
	a_produto = fopen("Produto.txt","rb+");
	a_venda = fopen("Venda.txt", "ab+");
	
	do
	{
		Formato(4);
		printf("\n***************** Realizar Venda *****************\n");
		printf("\nCodigo do produto: ");
		scanf("%d", &cod_pesq);
		
		rewind(a_produto);
	
		while(!feof(a_produto))
		{
			fread(&produto, sizeof(Produto), 1, a_produto);
			
			if(!feof(a_produto))
			{
				cont++;
				
				if(cod_pesq == produto.cod_barra)
				{
					do
					{
						system("cls");
						printf("\n***************** Realizar Venda *****************\n");
						printf("\nCodigo do produto: %d", produto.cod_barra);
						printf("\nNome do produto: %s", produto.nome_produto);
						printf("\nPreco: R$%.2f", produto.preco);
						printf("\nQuantidade do Produto em Estoque: %d", produto.quantidade);
						printf("\nQuantidade desejada: ");
						scanf("%d", &qtd);
					
						estoque = Estoque(qtd);
					}while(estoque == false);
					
					if(estoque == true)
					{
						venda.cod_barra = produto.cod_barra;
						strcpy(venda.nome_produto, produto.nome_produto);
						venda.quant = qtd;
						venda.vtotal = qtd * produto.preco;
						
						produto.quantidade = (produto.quantidade - qtd);
						
						total = (qtd * produto.preco) + total;
						
						fseek(a_produto,cont*sizeof(Produto),SEEK_SET);
						fwrite(&produto,sizeof(Produto),1,a_produto);
						fwrite(&venda, sizeof(Venda), 1, a_venda);
					}
					
					break;
				}
			}
		}
		
		printf("\nDeseja continuar comprando?\n");
		printf("[1] - Sim\n[0] - Nao\n");
		scanf("%d", &op);
			
	}while(op!=0);
	
	
	
	printf("\n****0************* Finalizar Venda *****************\n");
	printf("\nValor Total: R$%.2f", total);
	printf("\nValor Pago: R$");
	scanf("%f", &vpago);
	troco = vpago - total;
	printf("\nTroco: R$ %.2f\n\n", troco);
	system("pause");
	Formato(8);
	
	fclose(a_produto);
	fclose(a_venda);
}
//Fim Venda

//Verificação de disponibilidade do produto em estoque para venda
bool Estoque(int quantidade)
{
	Produto produto;
	bool acesso = false;
	
	a_produto = fopen("Produto.txt", "rb");
	
	rewind(a_produto);
	
	while(!feof(a_produto))
	{
		fread(&produto, sizeof(Produto), 1, a_produto);
		
		if(!feof(a_produto))
		{
			if(quantidade <= produto.quantidade)
			{
				acesso = true;
				return true;
			}
		}
	}
	
	if(acesso == false)
	{
		printf("\nQuantidade indisponivel no estoque\nFavor entrar com uma quantidade disponivel no estoque\n");
		Sleep(2000);
		return false;
	}
	
	fclose(a_produto);
	
}
//Fim da verificação de produtos disponiveis em estoque para venda



void Relatorio_Vendas()
{	
	Venda vendas;
	
	float total=0;
	Formato(4);
		
	a_venda=fopen("Vendas.txt","rb");
	
	printf("\n***************** Relatorio de Vendas *****************\n");
		
	rewind(a_venda);
	
	while(!feof(a_venda)){
		
		fread(&vendas,sizeof(Venda),1,a_venda);
		
		if(!feof(a_venda)){		
			
				total+= vendas.vtotal;
				printf("\n\nCliente:%s",vendas.nome_cliente);
				printf("\nProduto:%s",vendas.nome_produto);
				printf("\nValor Unitario:%.2f",vendas.produto.nome_produto);
				printf("\nQuantidade:%i",vendas.produto.quantidade);
				printf("\nValor Total:%.2f",vendas.vtotal);
				printf("\n\nFuncionario:%s",vendas.caixa.nome);
			
				printf("\n");
				system("Pause");						
		}
	}	
	fclose(a_venda);
	
	printf("Total das Vendas = %.2f",total);
	system("Pause");

}//Fim Relatorio Vendas

/*
void Relatorio_Estoque()
{	
	Produto prod;	
	Formato(4);
		
	a_produto=fopen("Estoque.txt","rb");
	
	printf("\n***************** Relatorio de Estoque *****************\n");		
	rewind(a_produto);
	
	while(!feof(a_produto)){
		
		fread(&prod,sizeof(Produto),1,a_produto);
		
		if(!feof(a_produto)){		
			
				printf("\nProduto:%s",prod.nome_produto);
				printf("\nValor Unitario:%.2f",prod.valor);
				printf("\nQuantidade:%i",prod.estoque);
				printf("\nValidade:%s",prod.validade);				
				printf("\n");
				system("Pause");						
		}
	}	
	fclose(a_produto);
	
}//Fim Relatorio Estoque
*/

