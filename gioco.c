#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

#define LNG 20

int score = 0;
typedef struct apple
{
    int x, y;
    char corpo;
} apple;

typedef struct tail
{
    int x, y;
    char corpo;
} tail;

typedef struct snake
{
    int x, y;
    char corpo;
    tail coda[100];
} snake;

void inizializza_schermo(char a[][LNG])
{

    for (int i = 0; i < LNG; i++)
    {
        for (int j = 0; j < LNG; j++)
        {
            a[i][j] = ' ';
        }
    }

    for (int i = 0; i < LNG; i++)
    {
        a[i][0] = '|';
        a[i][LNG - 1] = '|';
    }

    for (int i = 0; i < LNG; i++)
    {
        a[0][i] = '-';
        a[LNG - 1][i] = '-';
    }
}

void posiziona_mela(apple *x)
{
    x->x = ((rand() % 18) + 1);
    x->y = ((rand() % 18) + 1);
}

int overlapping(apple mela, snake serpente)
{
    if (mela.x == serpente.x && mela.y == serpente.y)
        return 1;

    return 0;
}

void movimento_coda(char x, snake *serpente, int lng, char schermo[][LNG])
{
    if(score > 0){
        for(int i = lng-1; i > -1; i--){
            
            if((i) == 0){
                serpente->coda[i].x = serpente->x;
                serpente->coda[i].y = serpente->y;
                schermo[serpente->coda[i].x][serpente->coda[i].y] = 'o';
            }else{
                serpente->coda[i].x = serpente->coda[i-1].x;
                serpente->coda[i].y = serpente->coda[i-1].y;
                schermo[serpente->coda[i].x][serpente->coda[i].y] = 'o';
            }
        }
    }
 
}
void movimento_testa(char x, snake* serpente){
    switch (x)
    {
    case 'w':
        serpente->x--;
        break;
    case 's':
        serpente->x++;
        break;
    case 'a':
        serpente->y--;
        break;
    case 'd':
        serpente->y++;
        break;
    } 
}

int controllo_bordi(char x, snake serpente, char schermo[][LNG])
{
    switch (x)
    {
    case 'w':
        if(schermo[serpente.x-1][serpente.y] == '-' || schermo[serpente.x-1][serpente.y] == '|' || schermo[serpente.x-1][serpente.y] == 'o' )
        	return 0;
        else
            return 1;
    case 's':
        if(schermo[serpente.x+1][serpente.y] == '-' || schermo[serpente.x+1][serpente.y] == '|' || schermo[serpente.x+1][serpente.y] == 'o' )
        	return 0;
        else
            return 1;
    case 'a':
    	if(schermo[serpente.x][serpente.y-1] == '-' || schermo[serpente.x][serpente.y-1] == '|' || schermo[serpente.x][serpente.y-1] == 'o' )
        	return 0;
        else
            return 1;
    case 'd':
        if(schermo[serpente.x][serpente.y+1] == '-' || schermo[serpente.x][serpente.y+1] == '|' || schermo[serpente.x][serpente.y+1] == 'o' )
        	return 0;
        else
            return 1;
    } 
}

void stampa_schermo(char x[][LNG], snake serpente, apple mela, int lng)
{
    x[serpente.x][serpente.y] = serpente.corpo;
    x[mela.x][mela.y] = mela.corpo;

    for (int i = 0; i < LNG; i++)
    {
        for (int j = 0; j < LNG; j++)
        {
            printf("%c", x[i][j]);
        }
        printf("\n");
    }

    printf("\n\nPUNTEGGIO : %d", score);
}
void cancella(char a[][LNG], int x, int y)
{
    a[x][y] = ' ';
}

void coda(snake* serpente, char schermo[][LNG], int *lng)
{
    if (*lng == 0)
    {
        serpente->coda[*lng].corpo = 'o';
        serpente->coda[*lng].x = serpente->x;
        serpente->coda[*lng].y = serpente->y;

        schermo[serpente->coda[*lng].x][serpente->coda[*lng].y] = serpente->coda[*lng].corpo;
        
    }
    else if (*lng > 0)
    {
        serpente->coda[*lng].corpo = 'o';
        serpente->coda[*lng].x = serpente->coda[*lng - 1].x;
        serpente->coda[*lng].y = serpente->coda[*lng - 1].y;

        schermo[serpente->coda[*lng].x][serpente->coda[*lng].y] = serpente->coda[*lng].corpo;
        
    }
}


int main(void)
{

    srand(time(NULL));

    char schermo[LNG][LNG];
    inizializza_schermo(schermo);

    snake serpente;
    serpente.corpo = 'O';
    serpente.x = LNG / 2;
    serpente.y = LNG / 2;

    apple mela;
    mela.corpo = 'M';
    posiziona_mela(&mela);

    int lngCoda = 0;
    char input = 'd';

    while (input != 'x')
    {
        if (kbhit())
        {
            char tmp_input = getch();
            if( (input == 'd' && tmp_input != 'a') || (input == 'a' && tmp_input != 'd') || (input == 'w' && tmp_input != 's') || (input == 's' && tmp_input != 'w'))
                input = tmp_input;
        }
		
		
			
        system("cls");

        if (overlapping(mela, serpente) == 1)
        {
            score+=10;
            cancella(schermo, mela.x, mela.y);
            posiziona_mela(&mela);
            coda(&serpente, schermo, &lngCoda);
            lngCoda++;
        }
        
        movimento_coda(input, &serpente, lngCoda, schermo);
		if(controllo_bordi(input, serpente, schermo) == 0)
			break;
        movimento_testa(input, &serpente);
        
        stampa_schermo(schermo, serpente, mela, lngCoda);
        cancella(schermo, serpente.x, serpente.y);
        if(score > 0){
            for(int i = 0; i <lngCoda; i++ ){
                cancella(schermo, serpente.coda[i].x, serpente.coda[i].y );
            }
        }
        
        Sleep(100);
    }

    system("pause");
    return 0;
}
