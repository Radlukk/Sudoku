#include <stdio.h>

#define TRATTINO '-'
#define VUOTO '_'
#define SEPARATORE '|'
#define SPAZIO ' '
#define FISSO '*'
#define RIGHE 9
#define COLON 9
#define MAXLEN 81
#define TRATT_RIGA 9
#define NPIU 3
#define VERO 1
#define FALSO 0
#define ERRATA '0'
#define VALIDA '1'
#define CORRETTA '2'

int menu(void); /*FATTO	Berni*/
void avvia_nuova_partita(void); //FATTO
void riempi_matrice(char[], char [][COLON]); //FATTO
void inserisci(char [][COLON]); /* FATTO funzione che aggiunge valore */ /* raffo */
void cancella(char [][COLON], char [MAXLEN]); /* FATTO	raffo */
int verifica_validità(char [][COLON]); // Filo /* corretto da raffo */
void carica_e_verifica_sol(char [][COLON]); //FATTO   Giu /* coretto da raffo*/
void reset(char [][COLON]); /*FATTO		Berni */
void stampa_matrice(char [][COLON]);
int verificaOriginalità(char [], int, int); /* raffo */

int main(int argc, char * argv[]){
	
  char schema[MAXLEN + 1];
  char sudoku[RIGHE][COLONNE];
  char sol[MAXLEN + 1];
  int schema_valido;
  int istruzione;
  
  do{
    
  	printf("inserire lo schema della nuova partita\ninserire '_' per gli spazzi vuoti: ");
  	gets(schema);
  
  	riempi_matrice(schema, sudoku);
  
		schema_valido = verifica_validità(sudoku);
  }
  while(schema_valido == 0);
  
  stampa_matrice(sudoku);
  
	istruzione = menu();
  
  do{
    
  	if(istruzione == 1){ /*QUESTA è LA PRIMA ISTRUZIONE PER AVVIARE LA NUOVA PARTITA*/
       
  		printf("inserire lo schema della nuova partita\ninserire '_' per gli spazzi vuoti: ");
  		gets(schema);
  
    	riempi_matrice(schema, sudoku);
  
  		schema_valido = verifica_validità(sudoku);
  
    	if(schema_valido){
    		stampa_matrice(sudoku);
 			}
    }
  
  	if(istruzione == 2){ 
    	inserisci(sudoku);
  	}

		if(istruzione == 3){
      cancella(sudoku);
  	}
  
		if(istruzione == 4){
    	verifica_validità(sudoku);
  	}
	
  	if(istruzione == 5){
  	  carica_e_verifica_sol(sudoku);
  	}
    
  	if(istruzione == 6){
    	reset(sudoku);
  	}
    
    istruzione = menu();
  }
  while(istruzione);
  
		return 0;
}

int menu(){

  int azione;

  printf("Quale azione vuoi compiere?\n");
  printf("1- Avviare una nuova partita\n");
	printf("2- Inserire un valore\n");
  printf("3- Cancellare una valore\n");
  printf("4- Verificare la soluzione attuale\n");
  printf("5- Caricare una soluzione e verificarla\n");
  printf("6- Riavviare una partita attuale\n");
  printf("0- Uscire\n");
  scanf("%d" , &azione);

  return azione;
  }




void avvia_nuova_partita(void){
  char schemaIn[MAXLEN+1];
  gets("%s", schemaIn);
  if(verifica_validità(schemaIn))
}


void riempi_matrice(char stringa[], char mat[][COLON])
{
  int i, j, k;
  
  k=0;
  for(i=0; i < RIGHE; i++){
    for(j=0; j < COLON; j++){
      mat[i][j] = stringa[k];
      k++;
    }
  }  
}

void stampa_matrice(char mat[][COLON])
{
  int i, j, k, h, u;
  
  printf("+");
  for(k = 0; k < NPIU; k++){
  	for(h = 0; h < TRATT_RIGA; h++){
    printf("TRATTINO");
    }
    printf("+")
  }
  printf("\n");
  
  i=0;
  j=0;
  for(u=0; u < NPIU; u++){
  	printf("SEPARATORE");
 	 for(k = 0; k < NPIU; k++){
   	 printf("SPAZIO");
   	 if(mat[i][j] == VUOTO){
    	  printf("SPAZIO");
   	 } else{
      printf("%c", mat[i][j]);
   	 }
	  }
  }
  
  
  
}

void inserisci(char sudoku[][COLON]){
  
  int i, j;
  int num;
  
	printf("dove vuoi inserire il nuovo numero\n"); 
  printf("riga: ");
  scanf("%d", &i);
  printf("colonna: ");
  scanf("%d", &j);
  
  if(sudoku[i - 1][j - 1] == VUOTO){
	  printf("nuovo valore: ");
  	scanf("%d", &num);
    if(num >= 1 && num <= 9){
      sudoku[i - 1][j - 1] = num;
    }
    else
      printf("valore invalido\n");
  }
  else
    printf("posizione invlida\n");
  
  stampa_matrice(sudoku);
}

void cancella(char sudoku[][COLON], char schema[]){
 
  int i, j;
  
	printf("dove vuoi cancellare il vecchio numero\n"); 
  printf("riga: ");
  scanf("%d", &i);
  printf("colonna: ");
  scanf("%d", &j);
  
  if(verificaOriginalità(schema, i, j) == 1)
		sudoku[i - 1][j - 1] = VUOTO;
  
  stampa_matrice(sudoku);  
}

int verifica_validita(char sol[][COLON]){
	int  i, j, k, h, m;
  int flag;
  int tmp;

  flag = 2;

    /* CONTROLLO LE RIGHE */
    for(i=0; i<RIGHE && flag; i++){
      for(j=0; j<COLON; j++){
        tmp = sol[i][j];
        for(k=0; k<COLON; k++){
          if(tmp == sol[i][k] && k!=j) /* qui mancava la condizione se finiva nella stessa casella */
            flag = 0;
        }
      }
    }  
	
  /*CONTROLLO LE COLONNE*/
  for(j=0; j<COLON && flag; j++){
    for(i=0; i<RIGHE; i++){ /*indentature sbagliate e parantesi assenti */
      tmp = sol[i][j];
      for(k=0; k<RIGHE; k++){
        if(tmp == sol[k][j] && k!=j)
          flag = 0;
      }
    }
  }

 /*CONTROLLO I QUADRATI*/
	/*PER CONTROLLARE UN QUADRATO*/
  for(k=0; k<dim && flag; k+=3)   /* dim??? */
    for(i=k; i<k+3 && flag; i++)  /* avevi messo i < k+2 che è insufficiente per valutare tutto il quadrato 3x3 */
      for(j=k; j<k+3; j++)
        tmp = sol[i][j];
          for(h=k; h<k+3 && flag; h++)
            for(m=k; m<k+3 && flag; m++)
              if(tmp == sol[h][m] && (h != i && m != j)) /* indentatura sbagliata e condizioni insufficienti */
                flag=0;
      
  /*CONTROLLO SE é COMPLETA*/
  if(flag==2){
    for(i=0; i<RIGHE && flag == 2; i++){
      for(j=0; j<COLON && flag == 2; j++){
        if(sol[i][j] == VUOTO) /* mancano delle condizioni */
          flag=1;
      }
    }
  }

if(flag==1)
  printf("il sudoku è valido ma incoleto\n");

if(flag==0)
  printf("il sudoku è incorretto\n");
    
return flag;

}

void carica_e_verifica_sol(char sol[][COLON]){  /* qualcuno ha messo int ma non ha detto cosa restituisce la funzione */

  /* char sol_matrice[MAX_LEN+1];    (questo codice non ha letteralmente senso)
  gets("%s", sol_matrice);
  riempi_matrice(sol_matrice); */

  if(verifica_validita(sol)  == ERRATA){
    printf("La soluzione inserita è errata\n"); /* hai messo print e non printf + manca \n*/
  }
  else if(verifica_validita(sol) == VALIDA){
    printf("La soluzione inserita è valida, ma incompleta\n");
  }
  else {
    printf("La soluzione inserita è corretta\n");
  }
}

void reset(char schema, char sudoku[][COLON]){ /* mancavano delle variabili alla funziove vedi: schema */

  riempi_matrice(schema, sudoku);

  stampa_matrice(sudoku);
}

void esci(void){
  
  
}
int verificaOriginalità(char schema[], int i, int j){

	char ver[RIGHE][CLON];
  
  riempi_matrice(schema, ver);
  
  if(ver[i][j] != VUOTO)
    return 0;
    
  return 1;
}
