// Síntese
//  Objetivo: Controlar a venda de ingresso, de diversos filmes e diferentes salas, da empresa CINEMAX; 
//  Entrada : Nome do filme, Quantidade de poltronas disponíveis na sala do filme, valor do ingresso, idade do interessado, benefício de meia entrada do interessado e número da poltrona
//            para reserva, cancelamento e/ou confirmação da compra.
//  Saída   : Mapa das poltronas da sala, valor total das vendas reservadas, nome do filme e mapa da sala com as poltronas marcadas corretamente como disponíveis, reservadas
//            e confirmadas (D, R e C) e valor total a ser pago nas vendas confirmadas.
#include<locale.h>
#include<stdlib.h>
#include<stdio.h>

#define CIAN "\x1b[1;36m"
#define YELLOW "\x1b[1;33m"
#define RED "\x1b[1;31m"
#define GREEN "\x1b[1;32m"
#define RESET "\x1b[0m"
char* leValidaFilme (char *filme){
	int comprimento;
	do{
		printf("Informe o nome do filme: ");
		fflush(stdin);
		gets(filme);
		comprimento=strlen(filme);
	}while(comprimento==0 || comprimento==1);
	return filme;
}

int leValidaCadeira (int qtdePoltronas){
	do{
		printf("Informe a quantidade de poltronas disponíveis: ");
		scanf("%i", &qtdePoltronas);
		if(qtdePoltronas<100 || qtdePoltronas>=500)
			puts("Quantidade de poltronas inválida!");
	}while(qtdePoltronas<100 || qtdePoltronas>=500);
	return qtdePoltronas;
}

float leValidaValor (float ingresso){
	do{
		printf("Informe o valor do ingresso: R$");
		scanf("%f", &ingresso);
		if(ingresso<=0)
			puts("Valor inválido!");
	}while(ingresso<=0);
	return ingresso;
}

int leValidaIdade (int idade){
	do{
		printf("\nInforme sua idade: ");
		scanf("%i", &idade);
		if(idade<=0)
			puts("Idade inválida!");
	}while(idade<=0);
	return idade;
}

char leValidaBeneficio (char bene){
	printf("Benefícios : E - estudante, P -pessoa com deficiência, I - idoso, D - doador de sangue, N - Não há benefício\n");
	do{
		printf("Informe, se houver, seu benefício: ");
		scanf("%s", &bene);
		if(bene!='E' && bene!='e' && bene!='P' && bene!='p' && bene!='I' && bene!='i' && bene!='D' && bene!='d' && bene!='N' && bene!='n')
			puts("Favor informar resposta válida!");
	}while(bene!='E' && bene!='e' && bene!='P' && bene!='p' && bene!='I' && bene!='i' && bene!='D' && bene!='d' && bene!='N' && bene!='n');
	return bene;
}

float calculaIngresso (char bene, int idade, float ingresso, float total){
		if(idade<=12 || bene=='E' || bene=='e' || bene=='p' || bene=='P' || bene=='I' || bene=='i' || bene=='D' || bene=='d'){
			total=(ingresso*50)/100;
		}else
		if(bene=='N' || bene=='n')
			total=ingresso;
	return total;
}

int leValidaReserva (int reservaC[], int controle, int qtdePoltronas){
	int rese,flag,i;
	do{
		flag=0;
		printf("Informe o número da poltrona que deseja para a %i° reserva: ",controle);
		scanf("%i", &rese);
		if(rese<1 || rese>qtdePoltronas)
			puts("Número da poltrona inválido!");	
		for(i=0; i<controle; i++){
			if(rese==reservaC[i])
				flag=1;
		}
		if(flag==1)
			puts("Poltrona já reservada! Escolha uma poltrona válida!");		
	}while((flag==1) || (rese<1 || rese>qtdePoltronas));
	return rese;
}

int cancelaPoltrona (char cadeiras[], int identificacao){
	printf("\nPara cancelar uma reserva digite o número da sua poltrona: ");
	scanf("%i", &identificacao);
	if(cadeiras[identificacao-1] == 'R'){
		cadeiras[identificacao-1] = 'D';
		puts(RED"\nSUA RESERVA FOI CANCELADA!\n"RESET);
	}else
		puts("A cadeira em questão não foi reservada ainda.");
	return identificacao;
}

int confirmaPoltrona (char cadeiras[], int identificacao){
	printf("\nPara confirmar uma reserva digite o número da sua poltrona: ");
	scanf("%i", &identificacao);
	if(cadeiras[identificacao-1] == 'R'){
		cadeiras[identificacao-1] = 'C';
		puts(CIAN"\nSUA RESERVA FOI CONFIRMADA!\n"RESET);
	}else
		puts("A cadeira em questão não foi reservada ainda!");
	return identificacao;
}


main(){
	setlocale(LC_ALL, "Portuguese");
	int qtdeCadeiras,idadeUsuario,indice,reserva[501],indice2,qtde,id,identificacao,k;
	float valorIngresso,valor,valorTotal,valorTotal2;
	char beneficio,continuar,letra,cadeiras[501],resposta,film[50];
	
	valorIngresso=leValidaValor(valorIngresso);
	do{
		indice=1;
		indice2=0;
		qtde=0;
		id=1;
		film[50]=leValidaFilme(film);
		qtdeCadeiras=leValidaCadeira(qtdeCadeiras);
		system("cls");
		k=1;
		
		for(indice2=0;indice2<qtdeCadeiras;indice2++){
			cadeiras[indice2]='D';
			printf(" %4i-["GREEN" %c "RESET"] ", k++, cadeiras[indice2]); 
		}
		
		puts("");	
		valorTotal=0;
		do{
			idadeUsuario=leValidaIdade(idadeUsuario);
			if(idadeUsuario>12)
				beneficio=leValidaBeneficio(beneficio);	
					
			reserva[indice]=leValidaReserva(reserva,indice,qtdeCadeiras);
			cadeiras[reserva[indice]-1]='R';
			
			system("cls");
			k=1;
			for(indice2=0; indice2<qtdeCadeiras; indice2++){
				if(cadeiras[indice2]=='R'){
					printf(" %4i-["RED" %c "RESET"] ", k++, cadeiras[indice2]); 
			}else
				if(cadeiras[indice2]=='D')
					printf(" %4i-["GREEN" %c "RESET"] ", k++, cadeiras[indice2]); 
			}
			
			printf("\nDigite s para reservar mais uma poltrona: ");
			scanf("%s", &continuar);
			indice++;
			qtde++;
			id=id+1;
			valor=calculaIngresso(beneficio,idadeUsuario,valorIngresso,valor);
			valorTotal=valorTotal+valor;
		}while(indice<qtdeCadeiras && continuar=='s' || continuar=='S');
		
		k=1;
		system("cls");
		printf("\nO valor total de vendas reservadas é = R$%.2f \n",valorTotal);
		printf("Digite s se desejar cancelar alguma reserva: ");
		scanf("%s", &continuar);
		
		if(continuar=='s' || continuar=='S'){
			do{
				system("cls");
				k=1;	
				for(indice2=0; indice2<qtdeCadeiras; indice2++){
					if(cadeiras[indice2]=='R'){
						printf(" %4i-["RED" %c "RESET"] ", k++, cadeiras[indice2]); 
					}else
					if(cadeiras[indice2]=='D')
						printf(" %4i-["GREEN" %c "RESET"] ", k++, cadeiras[indice2]); 
				}
				
				cancelaPoltrona(cadeiras,id);
				printf("Digite s para cancelar outra poltrona: ");
				scanf("%s", &continuar);	
			}while(continuar=='s' || continuar=='S');
		}
		
		system("cls");
		printf("\nDigite s se desejar confirmar alguma reserva: ");
		scanf("%s", &continuar);
		valorTotal2=0;
		if(continuar=='s' || continuar=='S'){
			do{
				system("cls");
				k=1;
				for(indice2=0;indice2<qtdeCadeiras;indice2++){
					if(cadeiras[indice2]=='R'){
						printf(" %4i-["RED" %c "RESET"] ", k++, cadeiras[indice2]); 
					}else
					if(cadeiras[indice2]=='D'){
						printf(" %4i-["GREEN" %c "RESET"] ", k++, cadeiras[indice2]); 
					}else
						printf(" %4i-["CIAN" %c "RESET"] ", k++, cadeiras[indice2]); 
				}
				
				confirmaPoltrona(cadeiras,id);
				printf("Digite s para confirmar outra poltrona: ");
				scanf("%s", &continuar);
				valorTotal2=valorTotal2+valor;
			}while(continuar=='s' || continuar=='S');
		}
		
		system("cls");
		printf("Filme: %s\n", film);
		k=1;
		for(indice2=0;indice2<qtdeCadeiras;indice2++){
			if(cadeiras[indice2]=='R'){
				printf(" %4i-["RED" %c "RESET"] ", k++, cadeiras[indice2]); 
		}else
			if(cadeiras[indice2]=='D'){
				printf(" %4i-["GREEN" %c "RESET"] ", k++, cadeiras[indice2]); 
		}else
				printf(" %4i-["CIAN" %c "RESET"] ", k++, cadeiras[indice2]); 
		}
		
		printf("\nValor Total a ser pago: %.2f", valorTotal2);
		puts("");
		printf("Aperte qualquer tecla");
		getch();
		system("cls");
		printf("Deseja realizar a venda de ingresos de outro filme: ");
		scanf("%s", &continuar);
	}while(continuar=='s' || continuar=='S');
}
