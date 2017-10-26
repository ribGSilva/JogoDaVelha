#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#ifdef _WIN32
        #include <conio.h> 
        #include <windows.h>
    #else
        #include <sys/ioctl.h>
    #endif
	
static int WIDTH = 79;
static int HEIGTH = 24;
static int CHAR_X = 88;
static int CHAR_O = 79;
static const int BOOL_TRUE = 1;
static const int BOOL_FALSE = 0;
#define ESTADO_MENU_PRINCIPAL 0
#define ESTADO_JOGO_SINGLE 1
#define ESTADO_JOGO_VS 2
static int matriz[3][3] = {
    {-1,-1,-1},
    {-1,-1,-1},
    {-1,-1,-1}
};

struct COORD {
    int x;
    int y;
} ponteiro;

void getScreenSize(){
	#ifdef _WIN32
        HEIGTH =24;
	WIDTH = 79;
    #else
        struct winsize w;
	    ioctl(0, TIOCGWINSZ, &w);
	    
	    //HEIGTH = w.ws_row;
	    //WIDTH = w.ws_col;
	
		HEIGTH =19;
		WIDTH = 80;
    #endif
    
}

void showCursor(int show) {
	#ifdef _WIN32
    	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	    CONSOLE_CURSOR_INFO info;
	    info.dwSize = 10;  // 1-100
	    info.bVisible = FALSE;  // booleano
	    SetConsoleCursorInfo(consoleHandle, &info);
    #else
        #define CSI "\e["
	    if (show == BOOL_TRUE) {
	        fputs(CSI "?25h", stdout);
	    }
	    else {
	        fputs(CSI "?25l", stdout);
	    }
		#undef CSI
    #endif

}

void gotoxy(int x,int y) {
    printf("%c[%d;%df",0x1B,y,x);
}


void *thread_ponteiro_menu_principal(void *args) {
    int i, *running, tempo = 0;
    running = args;
    
    while (*running == BOOL_TRUE){
        if (tempo == 0){
        	gotoxy(0, 0);//top
		    putchar(201); //top left
		    for (i=1; i<WIDTH; i++){
		        putchar(205);
		    }
		    putchar(187	);//top right
		    
		    for (i=2; i<HEIGTH; i++)  // right and left
		    {
		        gotoxy(0, i); putchar(186);
		        gotoxy(WIDTH + 1, i); putchar(186);
		    }
		    
		    gotoxy(0, HEIGTH);//bottom
		    putchar(200); //bottom left
		    for (i=1; i<WIDTH; i++){
		        putchar(205);
		    }
		    putchar(188);//bottom right
        	
        	gotoxy(ponteiro.x, ponteiro.y);
            printf("%c %c %c %c %c %c %c", 196, 196, 196, 196, 196, 196, 196);
        } else {
        	gotoxy(0, 0);//top
		    for (i=0; i<=WIDTH; i++){
		        putchar(32);
		    }
		    
		    for (i=2; i<HEIGTH; i++)  // right and left
		    {
		        gotoxy(0, i); putchar(32);
		        gotoxy(WIDTH + 1, i); putchar(32);
		    }
		    
		    gotoxy(0, HEIGTH);//bottom
		    for (i=0; i<=WIDTH; i++){
		        putchar(32);
		    }
		    
		    gotoxy(ponteiro.x, ponteiro.y);
            printf(" %c %c %c %c %c %c ", 196, 196, 196, 196, 196, 196);
        }   
        
        gotoxy((WIDTH / 2) - 7, 0);
		printf("[JOGO DA VELHA]");
		    
		gotoxy((WIDTH / 2) - 20, HEIGTH);
		printf("[Copyright(C) 2017 Gabriel Ribeiro Silva]");

		gotoxy(2, 2); 
		printf("           ");
		gotoxy(2, 2);    

        fflush(stdout);
        
        sleep(1);

        tempo = (tempo + 1) % 2;
    }
    return 0;
}

void limpaPonteiroJogo(){
    gotoxy(ponteiro.x, ponteiro.y);
    putchar(32); //top
    putchar(32);
    putchar(32);
        
    gotoxy(ponteiro.x, ponteiro.y + 1);//left
    putchar(32);
        
    gotoxy(ponteiro.x + 2, ponteiro.y + 1);//right
    putchar(32);
        
    gotoxy(ponteiro.x, ponteiro.y + 2);
    putchar(32); //bottom
    putchar(32);
    putchar(32);

	gotoxy(2, 2);
}
void *thread_ponteiro_jogo(void *args) {
    int i, *running, tempo = 0;
    running = args;
    
    while (*running == BOOL_TRUE){
        if (tempo == 0){
        	gotoxy(0, 0);//top
		    putchar(201); //top left
		    for (i=1; i<WIDTH; i++){
		        putchar(205);
		    }
		    putchar(187	);//top right
		    
		    for (i=2; i<HEIGTH; i++)  // right and left
		    {
		        gotoxy(0, i); putchar(186);
		        gotoxy(WIDTH + 1, i); putchar(186);
		    }
		    
		    gotoxy(0, HEIGTH);//bottom
		    putchar(200); //bottom left
		    for (i=1; i<WIDTH; i++){
		        putchar(205);
		    }
		    putchar(188);//bottom right
        	
        	
        	gotoxy(ponteiro.x, ponteiro.y);
            putchar(218); //top
            putchar(32);
            putchar(191);
            
            gotoxy(ponteiro.x, ponteiro.y + 1);//left
            putchar(32);
            
            gotoxy(ponteiro.x + 2, ponteiro.y + 1);//right
            putchar(32);
            
            gotoxy(ponteiro.x, ponteiro.y + 2);
            putchar(192); //bottom
            putchar(32);
            putchar(217);
            
        } else {
        	gotoxy(0, 0);//top
		    for (i=0; i<=WIDTH; i++){
		        putchar(32);
		    }
		    
		    for (i=2; i<HEIGTH; i++)  // right and left
		    {
		        gotoxy(0, i); putchar(32);
		        gotoxy(WIDTH + 1, i); putchar(32);
		    }
		    
		    gotoxy(0, HEIGTH);//bottom
		    for (i=0; i<=WIDTH; i++){
		        putchar(32);
		    }
		    
		    
		    gotoxy(ponteiro.x, ponteiro.y);
            putchar(32);//topo
            putchar(196);
            putchar(32);
            
            gotoxy(ponteiro.x, ponteiro.y + 1);//left
            putchar(179);
            
            gotoxy(ponteiro.x + 2, ponteiro.y + 1);//right
            putchar(179);
            
            gotoxy(ponteiro.x, ponteiro.y + 2);
            putchar(32); //bottom
            putchar(196);
            putchar(32);
        }
        
        
		gotoxy((WIDTH / 2) - 7, 0);
		printf("[JOGO DA VELHA]");
		    
		gotoxy((WIDTH / 2) - 20, HEIGTH);
		printf("[Copyright(C) 2017 Gabriel Ribeiro Silva]");

		gotoxy(2, 2);
		printf("           ");
		gotoxy(2, 2); 
        
        fflush(stdout);
        
        sleep(1);
        
        tempo = (tempo + 1) % 2;
    }
    return 0;
}

void moldura()
{
    int i;
    gotoxy(0, 0);//top
    putchar(201); //top left
    for (i=1; i<WIDTH; i++){
        putchar(205);
    }
    putchar(187	);//top right
    
    for (i=2; i<HEIGTH; i++)  // right and left
    {
        gotoxy(0, i); putchar(186);
        gotoxy(WIDTH + 1, i); putchar(186);
    }
    
    gotoxy(0, HEIGTH);//bottom
    putchar(200); //bottom left
    for (i=1; i<WIDTH; i++){
        putchar(205);
    }
    putchar(188);//bottom right
    
    gotoxy((WIDTH / 2) - 7, 0);
    printf("[JOGO DA VELHA]");
    
    gotoxy((WIDTH / 2) - 20, HEIGTH);
    printf("[Copyright(C) 2017 Gabriel Ribeiro Silva]");
    
    fflush(stdout);
}

void desenhaVez(int c){
    gotoxy(21, 4);
    printf("Vez do %c", c);

	gotoxy(2, 2);
}

void telaJogo(){
    
    gotoxy(20, 7); putchar(32); putchar(32); putchar(32); putchar(179); putchar(32); putchar(32); putchar(32); putchar(179); putchar(32); putchar(32); putchar(32);
    
    gotoxy(20, 8); putchar(32); putchar(32); putchar(32); putchar(179); putchar(32); putchar(32); putchar(32); putchar(179); putchar(32); putchar(32); putchar(32);
    
    gotoxy(20, 9); putchar(32); putchar(32); putchar(32); putchar(179); putchar(32); putchar(32); putchar(32); putchar(179); putchar(32); putchar(32); putchar(32);
    
    gotoxy(20, 10); putchar(196); putchar(196); putchar(196); putchar(197); putchar(196); putchar(196); putchar(196); putchar(197); putchar(196); putchar(196); putchar(196);
    
    gotoxy(20, 11); putchar(32); putchar(32); putchar(32); putchar(179); putchar(32); putchar(32); putchar(32); putchar(179); putchar(32); putchar(32); putchar(32);
    
    gotoxy(20, 12); putchar(32); putchar(32); putchar(32); putchar(179); putchar(32); putchar(32); putchar(32); putchar(179); putchar(32); putchar(32); putchar(32);
    
    gotoxy(20, 13); putchar(32); putchar(32); putchar(32); putchar(179); putchar(32); putchar(32); putchar(32); putchar(179); putchar(32); putchar(32); putchar(32);
    
    gotoxy(20, 14); putchar(196); putchar(196); putchar(196); putchar(197); putchar(196); putchar(196); putchar(196); putchar(197); putchar(196); putchar(196); putchar(196);
    
    gotoxy(20, 15); putchar(32); putchar(32); putchar(32); putchar(179); putchar(32); putchar(32); putchar(32); putchar(179); putchar(32); putchar(32); putchar(32);
    
    gotoxy(20, 16); putchar(32); putchar(32); putchar(32); putchar(179); putchar(32); putchar(32); putchar(32); putchar(179); putchar(32); putchar(32); putchar(32);
    
     gotoxy(20, 17); putchar(32); putchar(32); putchar(32); putchar(179); putchar(32); putchar(32); putchar(32); putchar(179); putchar(32); putchar(32); putchar(32);
    
    
    gotoxy(48, 5);
    printf("COMANDOS DO JOGO");
    gotoxy (47, 7);
    printf("q -> menu principal");
    gotoxy (39, 8);
    printf("setas direcionais ou wasd -> mover");
    gotoxy (44, 9);
    printf("enter -> fazer jogada");
    
    fflush(stdout);
    
}

void desenhaPlacar(int x, int o, int v){
    gotoxy(6, 7);
    printf("X|O|V");
    gotoxy(6, 8);
    putchar(196); putchar(197); putchar(196); putchar(197); putchar(196);
    gotoxy(6, 9);
    printf("%d|%d|%d", x, o, v);
    gotoxy(6, 10);
    printf(" | | ");
    
    fflush(stdout);
}

int verificaVelha(){
    int i, o;
    for (i = 0; i < 3; i ++)
        for (o = 0; o < 3; o++)
            if (matriz[i][o] != CHAR_X && matriz[i][o] != CHAR_O)
                return BOOL_FALSE;
    
    return BOOL_TRUE;
}

void limpaMatriz(){
    int i, o;
    for (i = 0; i < 3; i ++)
        for (o = 0; o < 3; o++)
            matriz[i][o] = -1;
}

void desenhaJogadaMaquina(int i, int j){
    int col, lin;
    switch (j) {
        case 0:
            col = 8;
            break;
        case 1:
            col = 12;
            break;
        case 2:
            col = 16;
            break;
            
        default:
            break;
    }
    switch (i) {
        case 0:
            lin = 21;
            break;
        case 1:
            lin = 25;
            break;
        case 2:
            lin = 29;
            break;
            
        default:
            break;
    }
    
    gotoxy(lin, col);
    printf("%c", CHAR_O);

	gotoxy(2, 2);
    fflush(stdout);
}

void maquinaJoga(){
	//char da maquina 'O'

    int cont = 0, i, o;
    
    for (i = 0; i<3; i++){//verifica vitoria nas linhas
        cont = 0;
        for (o = 0; o < 3; o++){
            if (matriz[i][o] == CHAR_X) break;
            if (matriz[i][o] == CHAR_O) cont++;
        }
        
        if (cont == 2)
            for (o = 0; o < 3; o++)
                if (matriz[i][o] == -1) {
                    matriz[i][o] = CHAR_O;
                    desenhaJogadaMaquina(i, o);
                    return;
                }
    }
    
    for (i = 0; i<3; i++){//verifica vitoria nas colunas
        cont = 0;
        for (o = 0; o < 3; o++){
            if (matriz[o][i] == CHAR_X) break;
            if (matriz[o][i] == CHAR_O) cont++;
        }
        
        if (cont == 2)
            for (o = 0; o < 3; o++)
                if (matriz[o][i] == -1) {
                    matriz[o][i] = CHAR_O;
                    desenhaJogadaMaquina(o, i);
                    return;
                }
    }
    
    cont = 0;
    for (i = 0; i < 3; i++){ //vitoria na diagonal
        if (matriz[i][i] == CHAR_X) break;
        if (matriz[i][i] == CHAR_O) cont++;
    }
    if (cont == 2)
        for (i = 0; i<3; i++)
            if (matriz[i][i] == -1) {
                matriz[i][i] = CHAR_O;
                desenhaJogadaMaquina(i, i);
                return;
            }
    
        
    cont = 0;
    for (i = 0, o = 2; i < 3; i++, o--){ //vitoria na diagonal secundaria
        if (matriz[i][o] == CHAR_X) break;
        if (matriz[i][o] == CHAR_O) cont++;
    }
    if (cont == 2)
        for (i = 0, o = 2; i < 3; i++, o--)
            if (matriz[i][o] == -1) {
                matriz[i][o] = CHAR_O;
                desenhaJogadaMaquina(i, o);
                return;
            }
    
    for (i = 0; i<3; i++){//verifica vitoria inimiga nas linhas
        cont = 0;
        for (o = 0; o < 3; o++){
            if (matriz[i][o] == CHAR_O) break;
            if (matriz[i][o] == CHAR_X) cont++;
        }
        
        if (cont == 2){
            for (o = 0; o < 3; o++)
                if (matriz[i][o] == -1) {
                    matriz[i][o] = CHAR_O;
                    desenhaJogadaMaquina(i, o);
                    return;
                }
        }
    }
    
    for (i = 0; i<3; i++){//verifica vitoria inimiga nas colunas
        cont = 0;
        for (o = 0; o < 3; o++){
            if (matriz[o][i] == CHAR_O) break;
            if (matriz[o][i] == CHAR_X) cont++;
        }
        
        if (cont == 2){
            for (o = 0; o < 3; o++)
                if (matriz[o][i] == -1) {
                    matriz[o][i] = CHAR_O;
                    desenhaJogadaMaquina(o, i);
                    return;
                }
        }
    }
    
    cont = 0;
    for (i = 0; i < 3; i++){ //vitoria inimiga na diagonal
        if (matriz[i][i] == CHAR_O) break;
        if (matriz[i][i] == CHAR_X) cont++;
    }
    if (cont == 2)
        for (i = 0; i<3; i++)
            if (matriz[i][i] == -1) {
                matriz[i][i] = CHAR_O;
                desenhaJogadaMaquina(i, i);
                return;
            }
    
    cont = 0;
    for (i = 0, o = 2; i < 3; i++, o--){ //vitoria inimiga na diagonal secundaria
        if (matriz[i][o] == CHAR_O) break;
        if (matriz[i][o] == CHAR_X) cont++;
    }
    if (cont == 2)
        for (i = 0, o = 2; i < 3; i++, o--)
            if (matriz[i][o] == -1) {
                matriz[i][o] = CHAR_O;
                desenhaJogadaMaquina(i, o);
                return;
            }
    
    if (matriz[1][1] == -1){//faz a 1 jogada, no meio se tiver vazio
        matriz[1][1] = CHAR_O;
        desenhaJogadaMaquina(1, 1);
        return;
    }

	int jogadasX = 0, jogadasO = 0;

	for (i = 0; i < 3; i++){
		for (o = 0; o < 3; o++){
			if (matriz[i][o] == CHAR_X) jogadasX++;
			else if (matriz[i][o] == CHAR_O) jogadasO++;
		}
	}

	switch(jogadasX){
		case 1: 
			if (matriz[1][1] == CHAR_X){//caso meio livre, coloca no meio
				matriz[2][0] = CHAR_O;
        		desenhaJogadaMaquina(2, 0); 
				return;
			}
			if (matriz[0][0] == CHAR_X || matriz[1][0] == CHAR_X){//faz a segunda jogada dependendo da jogada do usuario
				matriz[2][0] = CHAR_O;
        		desenhaJogadaMaquina(2, 0); 
				return;
			}
			if (matriz[2][0] == CHAR_X || matriz[2][1] == CHAR_X){//faz a segunda jogada dependendo da jogada do usuario
				matriz[2][2] = CHAR_O;
        		desenhaJogadaMaquina(2, 2); 
				return;
			}
			if (matriz[2][2] == CHAR_X || matriz[1][2] == CHAR_X){//faz a segunda jogada dependendo da jogada do usuario
				matriz[0][2] = CHAR_O;
        		desenhaJogadaMaquina(0, 2); 
				return;
			}
			if (matriz[0][2] == CHAR_X || matriz[0][1] == CHAR_X){//faz a segunda jogada dependendo da jogada do usuario
				matriz[0][0] = CHAR_O;
        		desenhaJogadaMaquina(0, 0); 
				return;
			}
			break;
		case 2:
			if (jogadasO == 2){ // maquina comecou
				if (matriz[0][0] == CHAR_X || matriz[2][1] == CHAR_X){
					matriz[0][2] = CHAR_O;
		    		desenhaJogadaMaquina(0, 2); 
					return;
				}
				if (matriz[2][0] == CHAR_X || matriz[2][1] == CHAR_X){
					matriz[0][0] = CHAR_O;
		    		desenhaJogadaMaquina(0, 0);
					return;
				}
				if (matriz[2][2] == CHAR_X || matriz[1][2] == CHAR_X){
					matriz[2][0] = CHAR_O;
		    		desenhaJogadaMaquina(2, 0); 
					return;
				}
				if (matriz[0][2] == CHAR_X || matriz[0][1] == CHAR_X){
					matriz[2][2] = CHAR_O;
		    		desenhaJogadaMaquina(2, 2); 
					return;
				}
			} else {// usuario comecou
				if (matriz[0][0] == CHAR_X && matriz[2][2] == CHAR_X ){// x o x na diagonal
					matriz[1][0] = CHAR_O;
					desenhaJogadaMaquina(1, 0); 
					return;
				}
				if (matriz[2][0] == CHAR_X && matriz[0][2] == CHAR_X ){// x o x na diagonal secundaria
					matriz[1][0] = CHAR_O;
					desenhaJogadaMaquina(1, 0); 
					return;
				}
				if (matriz[0][1] == CHAR_X && matriz[1][0] == CHAR_X ){// l no canto
					matriz[0][0] = CHAR_O;
					desenhaJogadaMaquina(0, 0); 
					return;
				}
				if (matriz[2][1] == CHAR_X && matriz[1][2] == CHAR_X ){// l na lateral
					matriz[2][2] = CHAR_O;
					desenhaJogadaMaquina(2, 2); 
					return;
				}
				if (matriz[0][1] == CHAR_X && matriz[1][2] == CHAR_X ){// l na lateral
					matriz[0][2] = CHAR_O;
					desenhaJogadaMaquina(0, 2); 
					return;
				}
				if (matriz[1][0] == CHAR_X && matriz[2][1] == CHAR_X ){// l na lateral
					matriz[2][0] = CHAR_O;
					desenhaJogadaMaquina(2, 0); 
					return;
				}	
			}
			break;
		case 3: 
			if ((matriz[2][1] == CHAR_X && matriz[1][2] == CHAR_X ) ||
				(matriz[0][1] == CHAR_X && matriz[1][2] == CHAR_X ) ||
				(matriz[1][0] == CHAR_X && matriz[2][1] == CHAR_X ) ||
				(matriz[0][1] == CHAR_X && matriz[1][0] == CHAR_X )){// caso acontece o l, ele tenta ganhar na diagonal
				
				if (matriz[0][1] == CHAR_X && matriz[1][0] == CHAR_X && matriz[2][0] == -1){
					matriz[2][0] = CHAR_O;
					desenhaJogadaMaquina(2, 0); 
					return;
				}
				if (matriz[2][1] == CHAR_X && matriz[1][2] == CHAR_X && matriz[2][0] == -1){
					matriz[2][0] = CHAR_O;
					desenhaJogadaMaquina(2, 0); 
					return;
				}
				if (matriz[0][1] == CHAR_X && matriz[1][2] == CHAR_X && matriz[0][0] == -1){
					matriz[0][0] = CHAR_O;
					desenhaJogadaMaquina(0, 0); 
					return;
				}
				if (matriz[1][0] == CHAR_X && matriz[2][1] == CHAR_X && matriz[0][0] == -1){
					matriz[0][0] = CHAR_O;
					desenhaJogadaMaquina(0, 0); 
					return;
				}
			}
	}

	for (i = 0; i < 3; i++){//jogada aleatoria
		for (o = 0; o < 3; o++){
			if (matriz[i][o] == -1){ 
				matriz[i][o] = CHAR_O;
        		desenhaJogadaMaquina(i, o); 
				return;
			}
		}
	}
}

//retorna o valor do char que ganhou, ou retorna -1 caso nao tenha ganhador
int verificaGanhador(){
    if (matriz[0][0] == matriz[0][1] && // horizontal
        matriz[0][1] == matriz[0][2]){
        return matriz[0][0];
    }
    if (matriz[1][0] == matriz[1][1] &&
        matriz[1][1] == matriz[1][2]){
        return matriz[1][0];
    }
    if (matriz[2][0] == matriz[2][1] &&
        matriz[2][1] == matriz[2][2]){
        return matriz[2][0];
    }
    
    if (matriz[0][0] == matriz[1][0] && //vertical
        matriz[1][0] == matriz[2][0]){
        return matriz[0][0];
    }
    if (matriz[0][1] == matriz[1][1] &&
        matriz[1][1] == matriz[2][1]){
        return matriz[0][1];
    }
    if (matriz[0][2] == matriz[1][2] &&
        matriz[1][2] == matriz[2][2]){
        return matriz[0][2];
    }
    
    if (matriz[0][0] == matriz[1][1] && //diagonal
        matriz[1][1] == matriz[2][2]){
        return matriz[1][1];
    }
    if (matriz[2][0] == matriz[1][1] &&
        matriz[1][1] == matriz[0][2]){
        return matriz[1][1];
    }
    
    return -1;
}

void telaPrincipal(){
    
    gotoxy((WIDTH / 2) - 11, 6);
    printf("ESCOLHA O MODO DE JOGO");
    
    gotoxy((WIDTH / 2) - 6, 13);
    printf("JOGADOR SOLO");
    
    gotoxy((WIDTH / 2) - 1, 16);
    printf("VS");
    
    gotoxy((WIDTH / 2) - 2, 19);
    printf("SAIR");
    
    fflush(stdout);
}

void printaGanhador(int ganhador){
    gotoxy (50, 13);
    printf("FIM DE JOGO");
    gotoxy(46, 15);
    printf("O jogador '%c' ganhou", ganhador);
    
    gotoxy(38, 17);
    printf("pressione 'enter' para jogar novamente");
    gotoxy(40, 18);
    printf("pressione 'q' para voltar ao menu");
}

void printaVelha(){
    gotoxy (50, 13);
    printf("DEU VELHA");
    
    gotoxy(38, 17);
    printf("pressione 'enter' para jogar novamente");
    gotoxy(40, 18);
    printf("pressione 'q' para voltar ao menu");
}

void clearScreen(){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

int main() {
    int running, run_thread_menu = BOOL_TRUE, run_thread_jogo = BOOL_FALSE, currentI = 0, currentJ = 0, tecla = 0;
    int estado = ESTADO_MENU_PRINCIPAL, vezDoX = BOOL_TRUE, xInicia = BOOL_TRUE;
    int ganhador, fimRodada = BOOL_FALSE, pontosX = 0, pontosO = 0, velhas = 0;
    
    //desligo o cursor
    showCursor(BOOL_FALSE);
    
    //pego tamanho da tela
    getScreenSize();
    
    //limpo o console
    clearScreen();
    
    //cria moldura
    //moldura();
    
    //tela principal
    telaPrincipal();
    
    ponteiro.x = (WIDTH / 2) - 6;
    ponteiro.y = 14;
    
    pthread_t thread_ponteiro;
    
    running = BOOL_TRUE;

    pthread_create(&thread_ponteiro, NULL , thread_ponteiro_menu_principal, (void *)&run_thread_menu);
    
    while (running == BOOL_TRUE) {
    	#ifdef _WIN32
        	tecla = getch();
	    #else 
	        system("/bin/stty raw");
        	tecla = getchar() - '0';
	    #endif
	    
	    //printf("aaaaa %d", tecla);
        
        //printf("%d", tecla);
        //system("/bin/stty cooked");

		gotoxy(2 , 2);
        printf("                  ");
        gotoxy(2 , 2);
	
        switch (estado) {
            case ESTADO_MENU_PRINCIPAL:
                if ((tecla == 71 || tecla == 17 || tecla == 72) && ponteiro.y != 14){ // aperta pra cima
                    ponteiro.y = ponteiro.y - 3;
					gotoxy(ponteiro.x , ponteiro.y + 3);
                    printf("                  ");
					gotoxy(2 , 2);

                } else if ((tecla == 67 || tecla == 18 || tecla == 80) && ponteiro.y != 20){ // aperta pra baixo
                	ponteiro.y = ponteiro.y + 3;
                    gotoxy(ponteiro.x , ponteiro.y - 3);
                    printf("                  ");
					gotoxy(2 , 2);

                } else if (tecla == 10 || tecla == 13 || tecla == -35){
                    if (ponteiro.y == 14){// single
                        run_thread_menu = BOOL_FALSE;
                        pthread_cancel(thread_ponteiro);//paro o ponteiro
                        ponteiro.x = 20;//reseto ponteiro
                        ponteiro.y = 7;
                        estado = ESTADO_JOGO_SINGLE;//mudo estado do jogo
                        clearScreen();//limpo a tela
                        //moldura();//adiciono a moudura
                        telaJogo();//crio a tela jogo
                        limpaMatriz();
                        pontosX = 0;
                        pontosO = 0;
                        velhas = 0;
                        currentI = 0;
                        currentJ = 0;
                        desenhaPlacar(pontosX, pontosO, velhas); //desenha placar
                        if (vezDoX == BOOL_FALSE){
                            vezDoX = BOOL_TRUE;
                            maquinaJoga();
                        } else {
                        	vezDoX = BOOL_FALSE;
						}
                        run_thread_jogo = BOOL_TRUE;
                        pthread_create(&thread_ponteiro, NULL , thread_ponteiro_jogo, (void *)&run_thread_jogo);//inicio thread de ponteiro de jogo
                    } else if (ponteiro.y == 17){ // vs
                        run_thread_menu = BOOL_FALSE;
                        pthread_cancel(thread_ponteiro);//paro o ponteiro
                        ponteiro.x = 20;//reseto ponteiro
                        ponteiro.y = 7;
                        estado = ESTADO_JOGO_VS;//mudo estado do jogo
                        clearScreen();//limpo a tela
                        //moldura();//adiciono a moudura
                        telaJogo();//crio a tela jogo
                        limpaMatriz();
                        pontosX = 0;
                        pontosO = 0;
                        velhas = 0;
                        currentI = 0;
                        currentJ = 0;
                        desenhaPlacar(pontosX, pontosO, velhas); //desenha placar
                        if (vezDoX == BOOL_FALSE){
                            vezDoX = BOOL_TRUE;
                            maquinaJoga();
                        } else {
                        	vezDoX = BOOL_FALSE;
						}
                        run_thread_jogo = BOOL_TRUE;
                        pthread_create(&thread_ponteiro, NULL , thread_ponteiro_jogo, (void *)&run_thread_jogo);//inicio thread de ponteiro de jogo
                    } else if (ponteiro.y == 20){ // sair
                        running = BOOL_FALSE;
                        clearScreen();
                    }
                }
                break;
            case ESTADO_JOGO_VS:
                if (fimRodada == BOOL_FALSE){
                    if ((tecla == 71 || tecla == 17|| tecla == 72) && ponteiro.y != 7){ // aperta pra cima
                        limpaPonteiroJogo();
                        ponteiro.y = ponteiro.y - 4;
                        currentJ--;
                    } else if ((tecla == 67 || tecla == 18 || tecla == 80) && ponteiro.y != 15){ // aperta pra baixo
                        limpaPonteiroJogo();
                        ponteiro.y = ponteiro.y + 4;
                        currentJ++;
                    } else if ((tecla == 49 || tecla == 20 || tecla == 75) && ponteiro.x != 20){ // aperta pra esquerda
                        limpaPonteiroJogo();
                        ponteiro.x = ponteiro.x - 4;
                        currentI--;
                    } else if ((tecla == 52 || tecla == 19 || tecla == 77) && ponteiro.x != 28){ // aperta pra direita
                        limpaPonteiroJogo();
                        ponteiro.x = ponteiro.x + 4;
                        currentI++;
                    } else if (tecla == 113 || tecla == 81 || tecla == 65) {// q para sair
                        estado = ESTADO_MENU_PRINCIPAL;
                        run_thread_jogo = BOOL_FALSE;
                        pthread_cancel(thread_ponteiro);
                        clearScreen();//limpo a tela
                        //moldura();//adiciono a moudura
                        telaPrincipal();
                        ponteiro.x = (WIDTH / 2) - 6;
                        ponteiro.y = 14;
                        run_thread_menu = BOOL_TRUE;
                        pthread_create(&thread_ponteiro, NULL , thread_ponteiro_menu_principal, (void *)&run_thread_menu);
                    } else if ((tecla == 10 || tecla == 13 || tecla == -35) && matriz[currentI][currentJ] == -1){
                        gotoxy(ponteiro.x + 1, ponteiro.y + 1);
                        if (vezDoX == BOOL_TRUE){
                            putchar(CHAR_X);
                            vezDoX = BOOL_FALSE;
                            matriz[currentI][currentJ] = CHAR_X;
                        }else{
                            putchar(CHAR_O);
                            vezDoX = BOOL_TRUE;
                            matriz[currentI][currentJ] = CHAR_O;
                        }
                        
                        ganhador = verificaGanhador();
                        if (ganhador != -1){
                            if (ganhador == CHAR_O)
                                pontosO++;
                            else
                                pontosX++;
                            printaGanhador(ganhador);
                            fimRodada = BOOL_TRUE;
                        }else if (verificaVelha() == BOOL_TRUE){
                                fimRodada = BOOL_TRUE;
                                velhas++;
                                printaVelha();
                        } else if (vezDoX == BOOL_TRUE)
                            desenhaVez(CHAR_X);
                        else
                            desenhaVez(CHAR_O);
                    }
                } else {
                    if (tecla == 10 || tecla == 13 || tecla == -35){ // jogar novamente
                        clearScreen();//limpo a tela
                        //moldura();//adiciono a moudura
                        telaJogo();//crio a tela jogo
                        desenhaPlacar(pontosX, pontosO, velhas);//desenha placar
                        if (vezDoX == BOOL_TRUE)
                            desenhaVez(CHAR_X);
                        else
                            desenhaVez(CHAR_O);
                        fimRodada = BOOL_FALSE;
                        limpaMatriz();
                    } else if (tecla == 113 || tecla == 81 || tecla == 65) {// q para sair
                        estado = ESTADO_MENU_PRINCIPAL;
                        run_thread_jogo = BOOL_FALSE;
                        pthread_cancel(thread_ponteiro);
                        clearScreen();//limpo a tela
                        //moldura();//adiciono a moudura
                        telaPrincipal();
                        ponteiro.x = (WIDTH / 2) - 6;
                        ponteiro.y = 14;
                        run_thread_menu = BOOL_TRUE;
                        pthread_create(&thread_ponteiro, NULL , thread_ponteiro_menu_principal, (void *)&run_thread_menu);
                    }
                }
                break;
            case ESTADO_JOGO_SINGLE:
                if (fimRodada == BOOL_FALSE){
                    if ((tecla == 71 || tecla == 17 || tecla == 72) && ponteiro.y != 7){ // aperta pra cima
                        limpaPonteiroJogo();
                        ponteiro.y = ponteiro.y - 4;
                        currentJ--;
                    } else if ((tecla == 67 || tecla == 18 || tecla == 80) && ponteiro.y != 15){ // aperta pra baixo
                        limpaPonteiroJogo();
                        ponteiro.y = ponteiro.y + 4;
                        currentJ++;
                    } else if ((tecla == 49 || tecla == 20  || tecla == 75) && ponteiro.x != 20){ // aperta pra esquerda
                        limpaPonteiroJogo();
                        ponteiro.x = ponteiro.x - 4;
                        currentI--;
                    } else if ((tecla == 52 || tecla == 19 || tecla == 77) && ponteiro.x != 28){ // aperta pra direita
                        limpaPonteiroJogo();
                        ponteiro.x = ponteiro.x + 4;
                        currentI++;
                    } else if (tecla == 113 || tecla == 81 || tecla == 65) {// q para sair
                        estado = ESTADO_MENU_PRINCIPAL;
                        run_thread_jogo = BOOL_FALSE;
                        pthread_cancel(thread_ponteiro);
                        clearScreen();//limpo a tela
                        //moldura();//adiciono a moudura
                        telaPrincipal();
                        ponteiro.x = (WIDTH / 2) - 6;
                        ponteiro.y = 14;
                        run_thread_menu = BOOL_TRUE;
                        pthread_create(&thread_ponteiro, NULL , thread_ponteiro_menu_principal, (void *)&run_thread_menu);
                    } else if ((tecla == 10 || tecla == 13 || tecla == -35) && matriz[currentI][currentJ] == -1){//faz jogada
                        gotoxy(ponteiro.x + 1, ponteiro.y + 1);
                        
                        putchar(CHAR_X);
                        matriz[currentI][currentJ] = CHAR_X;
                        
                        ganhador = verificaGanhador();
                        if (ganhador != -1){
                            if (ganhador == CHAR_O)
                                pontosO++;
                            else
                                pontosX++;
                            printaGanhador(ganhador);
                            fimRodada = BOOL_TRUE;
                        }else if (verificaVelha() == BOOL_TRUE){
                            fimRodada = BOOL_TRUE;
                            velhas++;
                            printaVelha();
                        } else {
                            maquinaJoga();
                            
                            ganhador = verificaGanhador();
                            if (ganhador != -1){
                                if (ganhador == CHAR_O)
                                    pontosO++;
                                else
                                    pontosX++;
                                printaGanhador(ganhador);
                                fimRodada = BOOL_TRUE;
                            }else if (verificaVelha() == BOOL_TRUE){
                                fimRodada = BOOL_TRUE;
                                velhas++;
                                printaVelha();
                            }
                        }
                    }
                } else {
                    if (tecla == 10 || tecla == 13 || tecla == -35){ // jogar novamente
                        clearScreen();//limpo a tela
                        fimRodada = BOOL_FALSE;
                        limpaMatriz();
                        //moldura();//adiciono a moudura
                        telaJogo();//crio a tela jogo
                        desenhaPlacar(pontosX, pontosO, velhas);//desenha placar
                        if (vezDoX == BOOL_FALSE){
                            vezDoX = BOOL_TRUE;
                            maquinaJoga();
                        } else {
                        	vezDoX = BOOL_FALSE;
						}
                    } else if (tecla == 113 || tecla == 81 || tecla == 65) {// q para sair
                        estado = ESTADO_MENU_PRINCIPAL;
                        run_thread_jogo = BOOL_FALSE;
                        pthread_cancel(thread_ponteiro);
                        clearScreen();//limpo a tela
                        //moldura();//adiciono a moudura
                        telaPrincipal();
                        ponteiro.x = (WIDTH / 2) - 6;
                        ponteiro.y = 14;
                        run_thread_menu = BOOL_TRUE;
                        pthread_create(&thread_ponteiro, NULL , thread_ponteiro_menu_principal, (void *)&run_thread_menu);
                    }
                }
                break;
            default:
                break;
        }
        
    }
    
	return 0;
}
