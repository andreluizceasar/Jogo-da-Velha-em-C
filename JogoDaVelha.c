#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//struct que vai ficar dentro de Players
struct Results{
	int wins;
	int losses;
};

//definicao de modelo struct para guardar nomes e estatisticas
struct Players{
	char nome[35];
	struct Results scores;
};

//pede o nome dos jogadores
struct Players nomes(int num){
	struct Players jogador[2];
	//se o numero recebido pelo parametro for 1, o nome do jogador 1 vai ser lido	
	if(num==1){
		printf("Nome jogador 1 (x): ");
		fgets(jogador[0].nome,35,stdin);	
		jogador[0].scores.wins = 0;
		jogador[0].scores.losses = 0;
		return jogador[0]; 
	}
	//se o numero recebido pelo parametro for 2, o nome do jogador 2 vai ser lido
	if(num==2){
		printf("Nome jogador 2 (o): ");
		fgets(jogador[1].nome,35,stdin);
		jogador[1].scores.wins = 0;  //iguala a zero as vitorias e derotas
		jogador[1].scores.losses = 0;
		return jogador[1];
	}
}

//imprime a quantidade de tracos desejada
void dash(int quant){
	int i;
	for(i=0;i<quant;i++){
		printf("-");
	}
}

//mostra o tabuleiro 
void imprime_tab(char mtx[][3]){
	//limpa a tela
	system("cls");
	int i,j;
	
	printf("    1   2   3\n\n");
	for(i=0;i<3;i++){	
		printf("%d  ",i+1);
		printf(" %c | %c | %c ",mtx[i][0],mtx[i][1],mtx[i][2]);
		printf("\n   ");
		if(i<2){dash(11);}
		printf("\n");
	}
}

//zera o tabuleiro no inicio do jogo
void zera_tab(char mtx[][3]){
	int i,j;
	for(i=0;i<3;i++){
		for(j=0;j<3;j++){
			mtx[i][j] = ' ';
		}
	}
}

//verifica se alguem venceu a partida
int score(char mtx[][3],struct Players *jog){
	int i;
	for(i=0;i<3;i++){
		//verificar linhas
		if(mtx[i][0]=='x' && mtx[i][1]=='x' && mtx[i][2]=='x'){
			jog[0].scores.wins++;
			jog[1].scores.losses++;
			printf("Jogador 1 venceu!!");
			return 1;
		}
		if(mtx[i][0]=='o' && mtx[i][1]=='o' && mtx[i][2]=='o'){
			jog[1].scores.wins++;
			jog[0].scores.losses++;
			printf("Jogador 2 venceu!!");
			return 1;
		}
		//verificar colunas
		if(mtx[0][i]=='x' && mtx[1][i]=='x' && mtx[2][i]=='x'){
			jog[0].scores.wins++;
			jog[1].scores.losses++;
			printf("Jogador 1 venceu!!");
			return 1;
		}
		if(mtx[0][i]=='o' && mtx[1][i]=='o' && mtx[2][i]=='o'){
			jog[1].scores.wins++;
			jog[0].scores.losses++;
			printf("Jogador 2 venceu!!");
			return 1;
		}
		if(i==0){ //verificar diagonais 
			if(mtx[0][0]=='x' && mtx[1][1]=='x' && mtx[2][2]=='x'){
				jog[0].scores.wins++;
				jog[1].scores.losses++;
				printf("Jogador 1 venceu!!");
				return 1;
			}		
			if(mtx[0][0]=='o' && mtx[1][1]=='o' && mtx[2][2]=='o'){
				jog[1].scores.wins++;
				jog[0].scores.losses++;
				printf("Jogador 2 venceu!!");
				return 1;
			}
			if(mtx[0][2]=='x' && mtx[1][1]=='x' && mtx[2][0]=='x'){
				jog[0].scores.wins++;
				jog[1].scores.losses++;
				printf("Jogador 1 venceu!!");
				return 1;
			}		
			if(mtx[0][2]=='o' && mtx[1][1]=='o' && mtx[2][0]=='o'){
				jog[1].scores.wins++;
				jog[0].scores.losses++;
				printf("Jogador 2 venceu!!");
				return 1;
			}
		}
	}
	return 0;		
}

//função que pede e valida as jogadas
void game(char mtx[][3],struct Players *jog,int alt){
	int linha,coluna;
	int i,n,end;
	char x_o[2] = {'x','o'};
	
	imprime_tab(mtx);
	
	for(i=0;i<9;i++){
		//se i for par é impresso jogador 1 
		//se i for impar é impresso jogador 2
		//é sempre alternado quem começa
		if(alt%2==0){
			if(i%2==0){n=0;}else{n=1;} 	
		}else{
			if(i%2==0){n=1;}else{n=0;} 
		}
				
		printf("\nJogador %d (%c):",n+1,x_o[n]);
		printf("\n Linha: ");
		scanf("%d",&linha);
		
		printf(" Coluna: ");
		scanf("%d",&coluna);
		
		//se a posicao ja estiver ocupada ou o numero for fora do tabuleiro
		//o jogador repete a jogada
		if(mtx[linha-1][coluna-1]!= ' ' || linha>3 || coluna>3 || linha<1 || coluna<1){
			i--;
		}else{
			mtx[linha-1][coluna-1] = x_o[n];
		}
		
		//sempre que ocorre uma mudanca no tabuleiro ele e reimpresso
		imprime_tab(mtx);
		
		//vitoria so é checada a partir da quarta jogada
		if(i>3){
			end = score(mtx,jog);			
			if(end == 1){
				break;
			}
		}
		if(i==8){
			printf("Empate!!");
		}
	}
}

//imprime as estatisticas ao fim
void print_stats(struct Players *jog){
		int i;
		char x_o[2] = {'x','o'};
		printf("\n\nEstatisticas: ");
		
		for(i=0;i<2;i++){
			printf("\n\nJogador %d (%c):",i+1,x_o[i]);
			printf("\n Nome: %s",jog[i].nome);
			printf(" Vitorias: %d",jog[i].scores.wins);
			printf("\n Derotas: %d",jog[i].scores.losses);
		}
}

int main(){
	char mtx[3][3];
	
	struct Players jogadores[2];
	
	jogadores[0] = nomes(1);
	jogadores[1] = nomes(2);
	
	char rep = 's';
	int alt = 0;
	
	while(rep == 's'){
		zera_tab(mtx);
		
		game(mtx,jogadores,alt);
		
		print_stats(jogadores);
		
		getchar();
		
		printf("\n\nJogar novamente? (s/n)");
		scanf("%c",&rep);
		
		alt++;
	}
	
	return 0;
}
