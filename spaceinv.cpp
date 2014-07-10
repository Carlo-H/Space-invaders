#include <winbgim.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <stdio.h>
#include <alloc.h>

//VARIABLES FICHEROS
FILE *fichero; //nombre: fichero
char CAD[8];
int N;
char VEC_N[3][4];         
int VEC_D[3]; 
char nombre[4];

//VARIABLES JUEGO
int FILS=20, COLS=28;
int Fnave=19, antF=0, Cnave=14, antC=0;
char in;
char Ain; //para recojer kbhits no deseados!.
char sentido='D';//controla el sentido de los invaders.
int puntuacion;
int iniciar=0;
int salir = 0;
int endall=0;
int nivel=0;
int random=900; // para aleatorio2
int ndisp=2; //para disparos mas rapidos, por cada nivel par.

//variables vidas
int HP = 4;
int VIDAS[4]={0,0,0,0}; // para poder dibujar vidas bonito

//variables para controlar el espacio
int M_IZQ=13, M_SUP = 60, TAM_C=30, TAM_F=25, PON_F=20, PON_C=20;

//variables para controlar la velocidad del juego
//para movimiento_invaders
float VMAX,VUNO=0.1,VDOS=0.0;
float VMAXC=4.5; // cambiar para cambiar la velocidad del grupo de invaders.
//para disparos_nave
float VMAX1=2.0,VUNO1=0.5,VDOS1=0.0;

//para movi_disp_inv
float VMAX2=2.0,VUNO2=0.1,VDOS2=0.0;

//mov laterales
float VMAX3=3.0,VUNO3=0.1,VDOS3=0.0;

//MATRICES
                 //0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 
int MAT[20][28]={  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //0
                   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //1
                   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //2
                   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //3
                   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //4
                   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //5
                   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //6
                   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //7
                   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //8
                   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //9
                   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //10
                   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //11
                   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //12
                   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //13
                   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //14
                   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //15
                   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //16
                   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //17
                   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //18
                   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };//19

                 //0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 
int MAT1[20][28]={ 0, 0, 0, 0, 0, 0, 0,-1, 0,-1, 0,-1, 0,-1, 0,-1, 0,-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //0
                   0, 0, 0, 0, 0, 0, 0,-2, 0,-2, 0,-2, 0,-2, 0,-2, 0,-2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //1
                   0, 0, 0, 0, 0, 0, 0,-3, 0,-3, 0,-3, 0,-3, 0,-3, 0,-3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //2
                   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //3
                   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //4
                   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //5
                   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //6
                   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //7
                   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //8
                   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //9
                   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //10
                   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //11
                   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //12
                   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //13
                   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //14
                   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //15
                   0, 0, 0, 6, 6, 6, 0, 0, 0, 6, 6, 6, 0, 0, 0, 0, 6, 6, 6, 0, 0, 0, 6, 6, 6, 0, 0, 0, //16
                   0, 0, 0, 6, 6, 6, 0, 0, 0, 6, 6, 6, 0, 0, 0, 0, 6, 6, 6, 0, 0, 0, 6, 6, 6, 0, 0, 0, //17
                   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //18
                   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };//19
                   
                   
//funciones                    //linea

int aleatorio();               //522
int aleatorio2();              //529
void disparosNave();           //699
void moviDispInv();            //783
void disparosInvaders();       //745
void nave(int C,int F);        //917
void invader(int C, int F);    //936
void invader2(int C, int F);   //987
void waitForLeftMouseClick();  //209
void inicio();                 //287
void situacionInv();           //775
void dibujarMatriz();          //536
void movimientoInvLaterales(); //823
void iniciarLaterales();       //810
void movimientoInvaders();     //853
void velocidadJuego();         //678
void mostrarPuntuaciones();    //370
void manual();                 //418
void bucleJuego();             //479
void escape();                 //251
void rellenarMatriz();         //239
void puntFinal();              //219
int contadorExtraInv();        //760
                               
void escribirFichero();        //1150
void leerFichero();            //1134
void nombreJugador();          //1087
void ordenarPuntuaciones();    //1044


int main()
{
    char CAD[40];
    leerFichero();
    srand((unsigned) time (NULL));
    initwindow(880,640); //open a 880x640 graphics window
    
    setwindowtitle("Space Invaders - Carlo Hartung");
    //menu
    while (endall==0){ // si endall es 1 sale
          if (HP==0){
             puntFinal(); // siempre que pierdas enseña la puntuacion obtenida
             iniciar=0;
          }
    while (iniciar == 0 and endall==0) inicio(); //bucle para no salir del menu de inicio
          
    while (HP>0 and salir == 0){
          //Pantalla siguiente 
          if (contadorExtraInv() == 0)
          bucleJuego();
          escape();
                 
          while (HP>0 and in != 27 and contadorExtraInv()>0){ // or -2 or -3
                while (!kbhit() and contadorExtraInv() > 0 and in != 27){   
                      movimientoInvaders();
                      disparosNave();
                      disparosInvaders();
                      iniciarLaterales();
                      movimientoInvLaterales();
                      situacionInv();
                      if (HP==0) in = 27;
                }
                /*
                // empieza test matriz, para ver los valores en la consola
                
                for (int F=0;F<FILS;F++){
                    for (int C=0;C<COLS;C++){
                         printf("%2i",MAT[F][C]);        
                        }
                        printf("\n");
                    }
                    printf("\n");
                   
               // final test 
               */
               if (HP>0 and contadorExtraInv() > 0)
               in = getch();
          
               if ((in == 'a' or in == 'A') and !(Cnave<1)){//mover nave a la izq.
                  antF=Fnave;
                  antC=Cnave;
                  Cnave=Cnave-1;
                  MAT[Fnave][Cnave]=1;
                  MAT[antF][antC]=0;
               }
           
               if ((in == 'd' or in == 'D') and !(Cnave>26)){//mover nave a la der.
                  antF=Fnave;
                  antC=Cnave;
                  Cnave=Cnave+1;
                  MAT[Fnave][Cnave]=1;
                  MAT[antF][antC]=0;
               }  
             
               if (in == 32){
                  MAT[Fnave-1][Cnave]=2; //disparo
               }
               dibujarMatriz();
                   
          }
    }
}
    cleardevice();
                
    // while(!kbhit());     // wait for user to press a key
    //waitForLeftMouseClick(); // use one or the other of these--not both

    closegraph();        //close graphics window
	return 0;
}

void waitForLeftMouseClick()
{
    clearmouseclick(WM_LBUTTONDOWN);
    const int DELAY = 50; // Milliseconds of delay between checks
    int x, y;
    while (!ismouseclick(WM_LBUTTONDOWN))
        delay(DELAY);
    getmouseclick(WM_LBUTTONDOWN, x, y);
}

void puntFinal()
{//muestra la puntuacion obtenida
     char CAD[40];
     
     cleardevice();
     ordenarPuntuaciones();
     settextstyle(2,0,8);
     setcolor(WHITE);
     sprintf(CAD,"PUNTUACION   FINAL");
     outtextxy(270,240,CAD);
     sprintf(CAD,"Haz clic en qualquier lugar para seguir");
     outtextxy(150,350,CAD);
     setcolor(GREEN);
     settextstyle(1,0,4);
     sprintf(CAD,"%04i",puntuacion);
     outtextxy(380,280,CAD);
     waitForLeftMouseClick();
     escribirFichero();    
}

void rellenarMatriz()
{//copia MAT1 en MAT para inicializar el juego.
     for (int F=0;F<FILS;F++){
              for (int C=0;C<COLS;C++){
                  MAT[F][C]=MAT1[F][C];
              }
          }
     VUNO=0.1;
     VDOS=0.0;
     MAT[Fnave][Cnave]=1;    
}

void escape()
{//al pulsar esc, para salir o no de la partida actual, si es no, sigue la partida.
  if (in ==27){   
     cleardevice();
     settextstyle(2,0,10);
     setcolor(GREEN);
     outtextxy(150,50,"¿Quieres ir al menu principal?");
     settextstyle(2,0,7);

     outtextxy(370,160,"Si");
     line(360,150,400,150);
     line(360,190,400,190);
     line(360,150,360,190);
     line(400,150,400,190);
       
     outtextxy(468,160,"No");
     line(460,150,500,150);
     line(460,190,500,190);
     line(460,150,460,190);
     line(500,150,500,190);
       
     waitForLeftMouseClick();
       
     if (mousex() >=360 and mousex()<=400 and mousey()>=150 and mousey()<=190){
        puntFinal();
        salir=1;
        iniciar=0;

     }else{
          if (mousex() >=460 and mousex()<=500 and mousey()>=150 and mousey()<=190)
          in=0; 
     }
  }
     cleardevice();
}

void inicio() 
{//menu principal
     cleardevice();
     settextstyle(2,0,10);
     setcolor(GREEN);
     outtextxy(220,50,"SPACE   INVADERS");
     //comenzar
     settextstyle(2,0,7);
     outtextxy(380,160,"COMENZAR!");
     line(360,150,520,150);
     line(360,190,520,190);
     line(360,150,360,190);
     line(520,150,520,190);
     //puntuaciones
     outtextxy(365,260,"PUNTUACIONES");
     line(360,250,520,250);
     line(360,290,520,290);
     line(360,250,360,290);
     line(520,250,520,290);
     //manual
     outtextxy(400,360,"MANUAL");
     line(360,350,520,350);
     line(360,390,520,390);
     line(360,350,360,390);
     line(520,350,520,390);
     //salir
     outtextxy(410,460,"SALIR");
     line(360,450,520,450);
     line(360,490,520,490);
     line(360,450,360,490);
     line(520,450,520,490);
     
     setcolor(MAGENTA);
     invader2(10,5);
     setcolor(LIGHTGREEN);
     invader(20,5);
     setcolor(LIGHTGREEN);
     invader(6,14);
     setcolor(CYAN);
     invader2(14,20);
     setcolor(MAGENTA);
     invader2(18,12);
     
     settextstyle(3,0,1);
     setcolor(WHITE);
     outtextxy(740,550,"Carlo Hartung");
     outtextxy(770,580,"2013");
     waitForLeftMouseClick();

//clic en botones
     if (mousex() >=360 and mousex()<=520 and mousey()>=150 and mousey()<=190){
                   nombreJugador();
                   //inicializar variables de la partida. 
                   nivel=1;       
                   iniciar=1;
                   salir=0;
                   in = 0;
                   puntuacion=0;
                   HP=4;
                   rellenarMatriz();
                   VMAX=VMAXC; //velocidad grupo invaders
                   VUNO2=0.1; //velocidad disparos
                   random=900; //cantidad disparos
                   ndisp=2;   // velocidad disparos mas rapido por cada nivel par.
                   for (int V=0;V<4;V++)
                       VIDAS[V]=1;                                                                   
     }else{                                                     
           if (mousex() >=360 and mousex()<=520 and mousey()>=250 and mousey()<=290){
              mostrarPuntuaciones();                                                                    
           }else{                                                          
                 if (mousex() >=360 and mousex()<=520 and mousey()>=350 and mousey()<=390){ 
                    manual();
                 }else{                                                    
                       if (mousex() >=360 and mousex()<=520 and mousey()>=450 and mousey()<=490){
                          salir=1;
                          endall=1;
                       }
                 }    
           }
     }        
     cleardevice();  
}

void mostrarPuntuaciones()
{//menu de puntuaciones
     char CAD[40];
     cleardevice();
     settextstyle(2,0,10);
     setcolor(GREEN);
     outtextxy(260,50,"PUNTUACIONES");
     setcolor(WHITE);
     settextstyle(2,0,7);
     setcolor(YELLOW);
     outtextxy(340,120,"1.");
     setcolor(WHITE);
     outtextxy(340,160,"2.");
     outtextxy(340,200,"3.");
     
     setcolor(YELLOW);
     outtextxy(360,120,VEC_N[0]);
     setcolor(WHITE);
     outtextxy(360,160,VEC_N[1]);
     outtextxy(360,200,VEC_N[2]);
     
     setcolor(YELLOW);
     sprintf(CAD,"%04i",VEC_D[0]);
     outtextxy(460,120,CAD);
     setcolor(WHITE);
     sprintf(CAD,"%04i",VEC_D[1]);
     outtextxy(460,160,CAD);
     sprintf(CAD,"%04i",VEC_D[2]);
     outtextxy(460,200,CAD);
     
     setcolor(GREEN);
     settextstyle(2,0,7);
     outtextxy(710,560,"VOLVER");
     line(680,550,820,550);
     line(680,590,820,590);
     line(680,550,680,590);
     line(820,550,820,590);

     waitForLeftMouseClick();
     if (mousex() >=680 and mousex()<=820 and mousey()>=550 and mousey()<=590){
        inicio();
                                                                               
     }else{
         mostrarPuntuaciones();
     }
     cleardevice(); 
}

void manual()
{// manual para el usuario
     cleardevice();
     settextstyle(2,0,10);
     setcolor(GREEN);
     outtextxy(320,25,"MANUAL");
     settextstyle(2,0,7);
     outtextxy(710,560,"VOLVER");
     line(680,550,820,550);
     line(680,590,820,590);
     line(680,550,680,590);
     line(820,550,820,590);
     settextstyle(2,0,7);
     outtextxy(50,65,"CONTROLES :");
     setlinestyle(0,0,1);
     setcolor(GREEN);
     setfillstyle(SOLID_FILL,GREEN);
     nave(4,1);
     setcolor(WHITE);
     settextstyle(2,0,7);
     outtextxy(180,95,"<-- esta es tu nave");
     settextstyle(2,0,7);
     setcolor(GREEN);
     outtextxy(50,130,"TECLADO :");
     setcolor(WHITE);
     outtextxy(135,160,"a  <-- mover a la izquierda");
     outtextxy(135,180,"d  <-- mover a la derecha");
     outtextxy(135,200,"espacio  <-- disparar");
     outtextxy(135,220,"esc  <-- pausar o salir");
     setcolor(GREEN);
     outtextxy(50,250,"OBJETIVO :");
     setcolor(WHITE);
     outtextxy(135,280,"Debes eliminar al grupo principal de enemigos antes de que lleguen abajo.");
     outtextxy(135,300,"Cuidado con los enemigos rojos! Quitan 1 vida cuando llegan abajo");
     outtextxy(135,320,"Pasatelo bien y saca el maximo de puntos que puedas!");
     setcolor(GREEN);
     outtextxy(50,350,"PUNTOS :");
     setcolor(LIGHTGREEN);
     invader(4,13);
     setcolor(CYAN);
     invader2(4,15);
     setcolor(MAGENTA);
     invader(4,17);
     setcolor(RED);
     invader2(4,19);
     setcolor(WHITE);
     outtextxy(240,395,"25 puntos");
     outtextxy(240,440,"15 puntos");
     outtextxy(240,490,"10 puntos");
     outtextxy(240,540," 5 puntos");
     outtextxy(50,590,"¡Cuidado, cada nivel se mueven mas rapido, disparan mas y mas rapido!");

     waitForLeftMouseClick();
     if (mousex() >=680 and mousex()<=820 and mousey()>=550 and mousey()<=590) inicio();
                                                                              
     else
         manual();
          
     cleardevice();   
}

void bucleJuego()
{//funcion para que al final de una partida podamos seguir con la siguente o volver al menu de inicio
     if (contadorExtraInv() == 0 and HP>0){
       cleardevice();
       settextstyle(2,0,10);
       setcolor(GREEN);
       outtextxy(260,50,"¿Quieres seguir?");
       settextstyle(2,0,7);
       outtextxy(370,160,"Si");
       line(360,150,400,150);
       line(360,190,400,190);
       line(360,150,360,190);
       line(400,150,400,190);
       outtextxy(468,160,"No");
       line(460,150,500,150);
       line(460,190,500,190);
       line(460,150,460,190);
       line(500,150,500,190);
       waitForLeftMouseClick();
       if (mousex() >=360 and mousex()<=400 and mousey()>=150 and mousey()<=190){
          rellenarMatriz();
          nivel=nivel+1;
          if (VMAX > 1.5) VMAX = VMAX - 0.5;         
          if (random > 0) random=random-50;
          if (nivel == ndisp) {//velocidad de disparos mas rapido cada nivel par. (2,4,6,8...)
          VUNO2=VUNO2+0.1;
          ndisp=ndisp+2;           
          }
       }
       else{
            if (mousex() >=460 and mousex()<=500 and mousey()>=150 and mousey()<=190){
            puntFinal();
            salir=1;
            iniciar=0;
            }else{
                bucleJuego();
            }
       }
       while (kbhit()) Ain=getch();
       cleardevice();
     }  
}

int aleatorio()
{
    int A;
    A = (rand() % 999) + 1;
    return A;
}

int aleatorio2()
{
    int A;
    A = (rand() % random) + 1;
    return A;
}

void dibujarMatriz()
{//dibuja los elementos del juego donde corresponden.
     int F, C;
     char CAD[40];

     for (F=0;F<FILS;F++){
         for (C=0;C<COLS;C++){
             if (MAT[F][C] != 5){
                switch (MAT[F][C]){
                       case -1: //invader verde
                               if (C%2==0){//posicion1
                                  setcolor(LIGHTGREEN); 
                                  invader(C,F);
                               }else{//posicion2
                                      setcolor(LIGHTGREEN);  
                                      invader2(C,F);
                               } 
                               break;
                       case -2:
                               if (C%2==0){
                                  setcolor(CYAN); 
                                  invader(C,F);
                               }else{
                                      setcolor(CYAN);  
                                      invader2(C,F);
                               } 
                               break;
                       case -3:
                               if (C%2==0){
                                  setcolor(MAGENTA); 
                                  invader(C,F);
                               }else{
                                      setcolor(MAGENTA);  
                                      invader2(C,F);
                               } 
                               break;
                       case -4:
                               if (F%2==0){
                                  setcolor(RED); 
                                  invader(C,F);
                               }else{
                                      setcolor(RED);  
                                      invader2(C,F);
                               } 
                               break;
                       case 1: // nave
                               setlinestyle(0,0,1);
                               setcolor(GREEN);
                               setfillstyle(SOLID_FILL,GREEN);
                               nave(C,F);
                               break;
                       case 2: // disparos nave
                               setcolor(GREEN);
                               setlinestyle(0,0,2);
                               line(M_IZQ+PON_C+C*TAM_C,M_SUP+PON_F+F*TAM_F,M_IZQ+PON_C+C*TAM_C,M_SUP+PON_F+F*TAM_F-4);
                               break; 
                       case -5: // disparos invaders
                               setcolor(WHITE);
                               setlinestyle(2,0,2);
                               line(M_IZQ+PON_C+C*TAM_C,M_SUP+PON_F+F*TAM_F,M_IZQ+PON_C+C*TAM_C,M_SUP+PON_F+F*TAM_F-7);
                               break;
                       case 6: // muros
                               setfillstyle(8,BLUE);
                               setlinestyle(0,0,1);
                               bar((M_IZQ+PON_C+C*TAM_C)-14,(M_SUP+PON_F+F*TAM_F)-13,(M_IZQ+PON_C+C*TAM_C)+14,(M_SUP+PON_F+F*TAM_F)+11);
                               break;  
                       case 0: //borrar
                               setfillstyle(1,BLACK);
                               setlinestyle(0,0,1);
                               bar((M_IZQ+PON_C+C*TAM_C)-14,(M_SUP+PON_F+F*TAM_F)-13,(M_IZQ+PON_C+C*TAM_C)+14,(M_SUP+PON_F+F*TAM_F)+11);
                               break;
                            
                }
             }
         }
     }
     settextstyle(2,0,8);
     setcolor(WHITE);
     sprintf(CAD,"PUNTOS");
     outtextxy(M_IZQ*2,20,CAD);
     setcolor(GREEN);
     settextstyle(1,0,4);
     sprintf(CAD,"%04i",puntuacion);
     outtextxy(M_IZQ*15,16,CAD);
     settextstyle(2,0,8);
     setcolor(WHITE);
     sprintf(CAD,"MEJOR");
     outtextxy(M_IZQ*30,20,CAD);
     setcolor(GREEN);
     settextstyle(1,0,4);
     sprintf(CAD,"%04i",VEC_D[0]);
     outtextxy(M_IZQ*40,16,CAD);
     
     /*  numero de invaders
     settextstyle(1,0,1);
     sprintf(CAD,"%2i",contadorExtraInv());
     outtextxy(M_IZQ*40,575,CAD);
     */
     
     settextstyle(2,0,7);
     outtextxy(M_IZQ*40,575,"NIVEL");
     sprintf(CAD,"%2i",nivel);
     outtextxy(M_IZQ*45,575,CAD);
     
     //apartado de pintar vidas
     
     setcolor(WHITE);
     sprintf(CAD,"VIDAS");
     outtextxy(M_IZQ*1,575,CAD);
     switch (HP){
            case 0:
                 VIDAS[0]=0;
                 break;
            case 1:
                 VIDAS[1]=0;
                 break; 
            case 2:
                 VIDAS[2]=0;
                 break;
            case 3:
                 VIDAS[3]=0;
                 break;
     }
     for (int V=0;V<4;V++){
         switch (VIDAS[V]){
                case 1:
                     setcolor(GREEN);
                     setfillstyle(SOLID_FILL,GREEN);
                     nave(V+2,20);
                     break;
                case 0:
                     setcolor(BLACK);
                     setfillstyle(SOLID_FILL,BLACK);
                     nave(V+2,20);
                     break;       
         }      
     }
     setcolor(WHITE);
     setlinestyle(0,0,2);
     line(860,570,M_IZQ,570);
}

void velocidadJuego()
{//controla la velocidad del juego, dependiendo del numero de invaders que hay en la matriz.
     switch (contadorExtraInv()){
            case 14:
                 VUNO=VUNO+0.1;
                 break;
            case 10:
                 VUNO=VUNO+0.05;
                 break;
            case 6:
                 VUNO=VUNO+0.05;
                 break;
            case 4:
                 VUNO=VUNO+0.05;
                 break;
            case 1:
                 VUNO=VUNO+0.1;
                 break;
     }
}

void disparosNave()
{//movimiento para los disparos de la nave y puntuaciones cuando se encuentra con un invader.
     int F, C;
     VDOS1=VDOS1+VUNO1;
     if (VDOS1>VMAX1){
        VDOS1=0.0;
        for (C=0;C<COLS;C++){
            for (F=0;F<19;F++){
                if (MAT[F+1][C]==2 and MAT[F][C]==0){
                   MAT[F][C]=2;
                   MAT[F+1][C]=0;           
                }
                if (MAT[F+1][C]==2 and MAT[F][C]==6) MAT[F+1][C]=0; //no romper muro!!
                
                if (MAT[F+1][C]==2 and MAT[F][C]!=0){
                   //puntuaciones
                   switch (MAT[F][C]){
                          case -1:
                                  puntuacion=puntuacion+25;
                                  velocidadJuego();
                                  break;
                          
                          case -2:
                                  puntuacion=puntuacion+15;
                                  velocidadJuego();
                                  break;
                          
                          case -3:
                                  puntuacion=puntuacion+10;
                                  velocidadJuego();
                                  break;
                          case -4:
                                  puntuacion=puntuacion+5;
                                  break;
                   } 
                         
                   if (MAT[F][C]!=-5) MAT[F][C]=0; // para que los disparos de la nave no ganen
                   MAT[F+1][C]=0;                    // a los disparos de los invaders
                   }
                   
                if (MAT[0][C]==2) MAT[F][C]=0;               
            }
        }
     }  
}

void disparosInvaders()
{//disparos que salen aleatoriamente. 
     int F,C;
     int n;
     for (C=COLS;C>0;C--){
         for (F=FILS;F>0;F--){
             n = aleatorio2();
             if ((MAT[F-1][C]==-1 or MAT[F-1][C]==-2 or MAT[F-1][C]==-3) and MAT[F][C]==0 and n==1){
             MAT[F][C]=-5;
             }
         }
     }
     moviDispInv();   
}

int contadorExtraInv()
{//cuenta el numero de invaders de la matriz.
   int F,C,c=0;
   for(F=0;F<FILS;F++){
      for(C=0;C<COLS;C++){
         if (MAT[F][C] == -1 or
             MAT[F][C] == -2 or
             MAT[F][C] == -3) {
             c++;
         }
      }
   }
   return c;
}

void situacionInv()
{// si llegan abajo del todo pierdes!
     int C;
     for (C=0;C<COLS;C++){
         if (MAT[19][C]==-1 or MAT[19][C]==-2 or MAT[19][C]==-3) HP=0;
     }
}
        
void moviDispInv()
{//movimiento para los disparos de los invaders.
     int F,C;

     VDOS2=VDOS2+VUNO2;
     if (VDOS2>VMAX2){
        VDOS2=0.0;
        for (C=27;C>0;C--){
            for (F=19;F>0;F--){
                if (MAT[F-1][C]==-5 and (MAT[F][C]==0 or MAT[F][C]==2)){
                   MAT[F][C]=-5;
                   MAT[F-1][C]=0;
                }
                if (MAT[F-1][C]==-5 and MAT[F][C]==6) {
                   MAT[F][C]=0;
                   MAT[F-1][C]=0; 
                }
                if (MAT[F-1][C]==-5 and MAT[F][C]==1) {
                   HP=HP-1;//si dan a la nave se resta 1 vida.
                   MAT[F-1][C]=0;                   
                }
           }
               if (MAT[19][C]==-5) MAT[19][C]=0;                  
        }
     } 
}

void iniciarLaterales()
{//saca invaders aleatoriamente de los laterales.
     int F1=0,C1=27,n;
     int F2=0,C2=0;
   
     n = aleatorio();
     if (n == 1) {
        MAT[F1][C1]=-4;            
     }else{
           if (n==5) MAT[F2][C2]=-4;
     }   
}

void movimientoInvLaterales()
{//movimiento de los invaders que salen por los lados.
     int F, C=27,C2=0;
     VDOS3=VDOS3+VUNO3;
     if (VDOS3>VMAX3){
        VDOS3=0.0;
        for (F=19;F>=0;F--){//Der.
            if (MAT[F-1][C]==-4){
               MAT[F][C]=-4;
               MAT[F-1][C]=0;                     
            }    
        }
        for (F=19;F>=0;F--){//Izq.
            if (MAT[F-1][C2]==-4){
               MAT[F][C2]=-4;
               MAT[F-1][C2]=0;                     
            }    
        }
        //Cuando llegan abajo: 1 HP menos y desaparecen.
        if (MAT[19][0]==-4){
           HP=HP-1;
           MAT[19][0]=0;                    
        }
        if (MAT[19][27]==-4){
           HP=HP-1;
           MAT[19][27]=0;                    
        }
     }
}

void movimientoInvaders()
{//movimiento para el grupito general de invaders.
     int F=0, C, END=0;

     VDOS=VDOS+VUNO;
     if (VDOS>VMAX){
        VDOS=0.0;
        if (sentido=='D'){ //comienzan hacia el lado derecho.
           while (F<FILS and !END){ 
                 if (MAT[F][26]==-1 or MAT[F][26]==-2 or MAT[F][26]==-3)END=1;//END -> final de fila
                 F++;                      
                 }
           if (!END){
           for (F=19;F>=0;F--){
               for (C=27;C>=0;C--){ //mov. derecha
                   if (MAT[F][C-1]==-1 or MAT[F][C-1]==-2 or MAT[F][C-1]==-3){
                      MAT[F][C]= MAT[F][C-1];
                      MAT[F][C-1]=0;                 
                   }  
               }  
           } 
           }
           else{//cuando es END.
                sentido='I';
                for (C=0;C<COLS;C++){
                    for (F=19;F>=0;F--){//se mueven abajo.
                        if (MAT[F-1][C]==-1 or MAT[F-1][C]==-2 or MAT[F-1][C]==-3){
                           MAT[F][C]=MAT[F-1][C];
                           MAT[F-1][C]=0;
                        } 
                    }
                }
                }
     }else{ //sentido izq.
           while (F<FILS and !END){//END izq
                 if (MAT[F][1]==-1 or MAT[F][1]==-2 or MAT[F][1]==-3) END=1;
                 F++;
           }
           if (!END){
              for (F=0;F<FILS;F++){
                  for (C=0;C<COLS;C++){//mov. izq.
                      if (MAT[F][C+1]==-1 or MAT[F][C+1]==-2 or MAT[F][C+1]==-3){
                         MAT[F][C]=MAT[F][C+1];
                         MAT[F][C+1]=0;
                      }
                  }
              }      
           }
              else{
                   sentido='D'; //END izq, bajan y mov der.
                   for (C=0;C<COLS;C++){
                       for (F=19;F>=0;F--){
                           if (MAT[F-1][C]==-1 or MAT[F-1][C]==-2 or MAT[F-1][C]==-3){
                              MAT[F][C]=MAT[F-1][C];
                              MAT[F-1][C]=0;
                           } 
                       }
                   }
              }
           }    
     }
     dibujarMatriz();   
}

void nave(int C, int F)
{//dibujo de la nave
     int puntos[16]={
                      (M_IZQ+PON_C+C*TAM_C), (M_SUP+PON_F+F*TAM_F)-6,        //1
                      (M_IZQ+PON_C+C*TAM_C)+6, (M_SUP+PON_F+F*TAM_F),        //2
                      (M_IZQ+PON_C+C*TAM_C)+12, (M_SUP+PON_F+F*TAM_F),       //3
                      (M_IZQ+PON_C+C*TAM_C)+12, (M_SUP+PON_F+F*TAM_F)+10,    //4
                      (M_IZQ+PON_C+C*TAM_C)-12, (M_SUP+PON_F+F*TAM_F)+10,    //5
                      (M_IZQ+PON_C+C*TAM_C)-12, (M_SUP+PON_F+F*TAM_F),       //6
                      (M_IZQ+PON_C+C*TAM_C)-6, (M_SUP+PON_F+F*TAM_F),        //7
                      (M_IZQ+PON_C+C*TAM_C), (M_SUP+PON_F+F*TAM_F)-6         //8
                      };
        
         
     drawpoly(8,puntos);
     fillpoly(8,puntos);   
     
}

void invader(int C, int F)
{//dibujo de invader en la primera posicion
     setlinestyle(0,0,1);
     line((M_IZQ+PON_C+C*TAM_C)+4,(M_SUP+PON_F+F*TAM_F)-10,(M_IZQ+PON_C+C*TAM_C)+6,(M_SUP+PON_F+F*TAM_F)-10);
     line((M_IZQ+PON_C+C*TAM_C)+4,(M_SUP+PON_F+F*TAM_F)-9,(M_IZQ+PON_C+C*TAM_C)+6,(M_SUP+PON_F+F*TAM_F)-9);
     line((M_IZQ+PON_C+C*TAM_C)+2,(M_SUP+PON_F+F*TAM_F)-7,(M_IZQ+PON_C+C*TAM_C)+4,(M_SUP+PON_F+F*TAM_F)-7);
     line((M_IZQ+PON_C+C*TAM_C)+2,(M_SUP+PON_F+F*TAM_F)-8,(M_IZQ+PON_C+C*TAM_C)+4,(M_SUP+PON_F+F*TAM_F)-8);
     
     line((M_IZQ+PON_C+C*TAM_C)-8,(M_SUP+PON_F+F*TAM_F)-10,(M_IZQ+PON_C+C*TAM_C)-6,(M_SUP+PON_F+F*TAM_F)-10);
     line((M_IZQ+PON_C+C*TAM_C)-8,(M_SUP+PON_F+F*TAM_F)-9,(M_IZQ+PON_C+C*TAM_C)-6,(M_SUP+PON_F+F*TAM_F)-9);
     line((M_IZQ+PON_C+C*TAM_C)-6,(M_SUP+PON_F+F*TAM_F)-7,(M_IZQ+PON_C+C*TAM_C)-4,(M_SUP+PON_F+F*TAM_F)-7);
     line((M_IZQ+PON_C+C*TAM_C)-6,(M_SUP+PON_F+F*TAM_F)-8,(M_IZQ+PON_C+C*TAM_C)-4,(M_SUP+PON_F+F*TAM_F)-8);
     
     line((M_IZQ+PON_C+C*TAM_C)-8,(M_SUP+PON_F+F*TAM_F)-6,(M_IZQ+PON_C+C*TAM_C)+6,(M_SUP+PON_F+F*TAM_F)-6);
     line((M_IZQ+PON_C+C*TAM_C)-8,(M_SUP+PON_F+F*TAM_F)-5,(M_IZQ+PON_C+C*TAM_C)+6,(M_SUP+PON_F+F*TAM_F)-5);
     
     line((M_IZQ+PON_C+C*TAM_C)-10,(M_SUP+PON_F+F*TAM_F)-4,(M_IZQ+PON_C+C*TAM_C)-6,(M_SUP+PON_F+F*TAM_F)-4);
     line((M_IZQ+PON_C+C*TAM_C)-10,(M_SUP+PON_F+F*TAM_F)-3,(M_IZQ+PON_C+C*TAM_C)-6,(M_SUP+PON_F+F*TAM_F)-3);
     line((M_IZQ+PON_C+C*TAM_C)-4,(M_SUP+PON_F+F*TAM_F)-4,(M_IZQ+PON_C+C*TAM_C)+2,(M_SUP+PON_F+F*TAM_F)-4);
     line((M_IZQ+PON_C+C*TAM_C)-4,(M_SUP+PON_F+F*TAM_F)-3,(M_IZQ+PON_C+C*TAM_C)+2,(M_SUP+PON_F+F*TAM_F)-3);
     line((M_IZQ+PON_C+C*TAM_C)+4,(M_SUP+PON_F+F*TAM_F)-4,(M_IZQ+PON_C+C*TAM_C)+8,(M_SUP+PON_F+F*TAM_F)-4);
     line((M_IZQ+PON_C+C*TAM_C)+4,(M_SUP+PON_F+F*TAM_F)-3,(M_IZQ+PON_C+C*TAM_C)+8,(M_SUP+PON_F+F*TAM_F)-3);
     

     line((M_IZQ+PON_C+C*TAM_C)-12,(M_SUP+PON_F+F*TAM_F)-2,(M_IZQ+PON_C+C*TAM_C)+10,(M_SUP+PON_F+F*TAM_F)-2);
     line((M_IZQ+PON_C+C*TAM_C)-12,(M_SUP+PON_F+F*TAM_F)-1,(M_IZQ+PON_C+C*TAM_C)+10,(M_SUP+PON_F+F*TAM_F)-1);
     line((M_IZQ+PON_C+C*TAM_C)-14,(M_SUP+PON_F+F*TAM_F),(M_IZQ+PON_C+C*TAM_C)+12,(M_SUP+PON_F+F*TAM_F));
     line((M_IZQ+PON_C+C*TAM_C)-14,(M_SUP+PON_F+F*TAM_F)+1,(M_IZQ+PON_C+C*TAM_C)+12,(M_SUP+PON_F+F*TAM_F)+1);
     
     line((M_IZQ+PON_C+C*TAM_C)-14,(M_SUP+PON_F+F*TAM_F)+2,(M_IZQ+PON_C+C*TAM_C)-12,(M_SUP+PON_F+F*TAM_F)+2);
     line((M_IZQ+PON_C+C*TAM_C)-14,(M_SUP+PON_F+F*TAM_F)+3,(M_IZQ+PON_C+C*TAM_C)-12,(M_SUP+PON_F+F*TAM_F)+3);
     line((M_IZQ+PON_C+C*TAM_C)-14,(M_SUP+PON_F+F*TAM_F)+4,(M_IZQ+PON_C+C*TAM_C)-12,(M_SUP+PON_F+F*TAM_F)+4);
     
     line((M_IZQ+PON_C+C*TAM_C)+10,(M_SUP+PON_F+F*TAM_F)+2,(M_IZQ+PON_C+C*TAM_C)+12,(M_SUP+PON_F+F*TAM_F)+2);
     line((M_IZQ+PON_C+C*TAM_C)+10,(M_SUP+PON_F+F*TAM_F)+3,(M_IZQ+PON_C+C*TAM_C)+12,(M_SUP+PON_F+F*TAM_F)+3);
     line((M_IZQ+PON_C+C*TAM_C)+10,(M_SUP+PON_F+F*TAM_F)+4,(M_IZQ+PON_C+C*TAM_C)+12,(M_SUP+PON_F+F*TAM_F)+4);
     
     line((M_IZQ+PON_C+C*TAM_C)-8,(M_SUP+PON_F+F*TAM_F)+2,(M_IZQ+PON_C+C*TAM_C)+6,(M_SUP+PON_F+F*TAM_F)+2);
     
     line((M_IZQ+PON_C+C*TAM_C)-8,(M_SUP+PON_F+F*TAM_F)+3,(M_IZQ+PON_C+C*TAM_C)-6,(M_SUP+PON_F+F*TAM_F)+3);
     line((M_IZQ+PON_C+C*TAM_C)-8,(M_SUP+PON_F+F*TAM_F)+4,(M_IZQ+PON_C+C*TAM_C)-6,(M_SUP+PON_F+F*TAM_F)+4);
     line((M_IZQ+PON_C+C*TAM_C)+4,(M_SUP+PON_F+F*TAM_F)+4,(M_IZQ+PON_C+C*TAM_C)+6,(M_SUP+PON_F+F*TAM_F)+4);
     line((M_IZQ+PON_C+C*TAM_C)+4,(M_SUP+PON_F+F*TAM_F)+3,(M_IZQ+PON_C+C*TAM_C)+6,(M_SUP+PON_F+F*TAM_F)+3);
     
     line((M_IZQ+PON_C+C*TAM_C)-6,(M_SUP+PON_F+F*TAM_F)+5,(M_IZQ+PON_C+C*TAM_C)-2,(M_SUP+PON_F+F*TAM_F)+5);
     line((M_IZQ+PON_C+C*TAM_C)-6,(M_SUP+PON_F+F*TAM_F)+6,(M_IZQ+PON_C+C*TAM_C)-2,(M_SUP+PON_F+F*TAM_F)+6);
     line((M_IZQ+PON_C+C*TAM_C)+2,(M_SUP+PON_F+F*TAM_F)+6,(M_IZQ+PON_C+C*TAM_C)+6,(M_SUP+PON_F+F*TAM_F)+6);
     line((M_IZQ+PON_C+C*TAM_C)+2,(M_SUP+PON_F+F*TAM_F)+5,(M_IZQ+PON_C+C*TAM_C)+6,(M_SUP+PON_F+F*TAM_F)+5);

}

void invader2(int C, int F)
{//dibujo de la segunda posicion del invader.
     setlinestyle(0,0,1);
     line((M_IZQ+PON_C+C*TAM_C)+4,(M_SUP+PON_F+F*TAM_F)-10,(M_IZQ+PON_C+C*TAM_C)+6,(M_SUP+PON_F+F*TAM_F)-10);
     line((M_IZQ+PON_C+C*TAM_C)+4,(M_SUP+PON_F+F*TAM_F)-9,(M_IZQ+PON_C+C*TAM_C)+6,(M_SUP+PON_F+F*TAM_F)-9);
     line((M_IZQ+PON_C+C*TAM_C)+2,(M_SUP+PON_F+F*TAM_F)-8,(M_IZQ+PON_C+C*TAM_C)+4,(M_SUP+PON_F+F*TAM_F)-8);
     line((M_IZQ+PON_C+C*TAM_C)+2,(M_SUP+PON_F+F*TAM_F)-7,(M_IZQ+PON_C+C*TAM_C)+4,(M_SUP+PON_F+F*TAM_F)-7);
     
     line((M_IZQ+PON_C+C*TAM_C)-8,(M_SUP+PON_F+F*TAM_F)-10,(M_IZQ+PON_C+C*TAM_C)-6,(M_SUP+PON_F+F*TAM_F)-10);
     line((M_IZQ+PON_C+C*TAM_C)-8,(M_SUP+PON_F+F*TAM_F)-9,(M_IZQ+PON_C+C*TAM_C)-6,(M_SUP+PON_F+F*TAM_F)-9);
     line((M_IZQ+PON_C+C*TAM_C)-6,(M_SUP+PON_F+F*TAM_F)-8,(M_IZQ+PON_C+C*TAM_C)-4,(M_SUP+PON_F+F*TAM_F)-8);
     line((M_IZQ+PON_C+C*TAM_C)-6,(M_SUP+PON_F+F*TAM_F)-7,(M_IZQ+PON_C+C*TAM_C)-4,(M_SUP+PON_F+F*TAM_F)-7);
     
     line((M_IZQ+PON_C+C*TAM_C)-8,(M_SUP+PON_F+F*TAM_F)-6,(M_IZQ+PON_C+C*TAM_C)+6,(M_SUP+PON_F+F*TAM_F)-6);
     line((M_IZQ+PON_C+C*TAM_C)-8,(M_SUP+PON_F+F*TAM_F)-5,(M_IZQ+PON_C+C*TAM_C)+6,(M_SUP+PON_F+F*TAM_F)-5);
     
     line((M_IZQ+PON_C+C*TAM_C)-10,(M_SUP+PON_F+F*TAM_F)-4,(M_IZQ+PON_C+C*TAM_C)-6,(M_SUP+PON_F+F*TAM_F)-4);
     line((M_IZQ+PON_C+C*TAM_C)-10,(M_SUP+PON_F+F*TAM_F)-3,(M_IZQ+PON_C+C*TAM_C)-6,(M_SUP+PON_F+F*TAM_F)-3);
     line((M_IZQ+PON_C+C*TAM_C)-4,(M_SUP+PON_F+F*TAM_F)-4,(M_IZQ+PON_C+C*TAM_C)+2,(M_SUP+PON_F+F*TAM_F)-4);
     line((M_IZQ+PON_C+C*TAM_C)-4,(M_SUP+PON_F+F*TAM_F)-3,(M_IZQ+PON_C+C*TAM_C)+2,(M_SUP+PON_F+F*TAM_F)-3);
     line((M_IZQ+PON_C+C*TAM_C)+4,(M_SUP+PON_F+F*TAM_F)-4,(M_IZQ+PON_C+C*TAM_C)+8,(M_SUP+PON_F+F*TAM_F)-4);
     line((M_IZQ+PON_C+C*TAM_C)+4,(M_SUP+PON_F+F*TAM_F)-3,(M_IZQ+PON_C+C*TAM_C)+8,(M_SUP+PON_F+F*TAM_F)-3);
     
     
     line((M_IZQ+PON_C+C*TAM_C)-12,(M_SUP+PON_F+F*TAM_F)-2,(M_IZQ+PON_C+C*TAM_C)+10,(M_SUP+PON_F+F*TAM_F)-2);
     line((M_IZQ+PON_C+C*TAM_C)-14,(M_SUP+PON_F+F*TAM_F),(M_IZQ+PON_C+C*TAM_C)+12,(M_SUP+PON_F+F*TAM_F));
     line((M_IZQ+PON_C+C*TAM_C)-14,(M_SUP+PON_F+F*TAM_F)-1,(M_IZQ+PON_C+C*TAM_C)+12,(M_SUP+PON_F+F*TAM_F)-1);
     
     line((M_IZQ+PON_C+C*TAM_C)-14,(M_SUP+PON_F+F*TAM_F)-2,(M_IZQ+PON_C+C*TAM_C)-12,(M_SUP+PON_F+F*TAM_F)-2);
     line((M_IZQ+PON_C+C*TAM_C)-14,(M_SUP+PON_F+F*TAM_F)-3,(M_IZQ+PON_C+C*TAM_C)-12,(M_SUP+PON_F+F*TAM_F)-3);
     line((M_IZQ+PON_C+C*TAM_C)-14,(M_SUP+PON_F+F*TAM_F)-4,(M_IZQ+PON_C+C*TAM_C)-12,(M_SUP+PON_F+F*TAM_F)-4);
     line((M_IZQ+PON_C+C*TAM_C)-14,(M_SUP+PON_F+F*TAM_F)-5,(M_IZQ+PON_C+C*TAM_C)-12,(M_SUP+PON_F+F*TAM_F)-5);
     line((M_IZQ+PON_C+C*TAM_C)-14,(M_SUP+PON_F+F*TAM_F)-6,(M_IZQ+PON_C+C*TAM_C)-12,(M_SUP+PON_F+F*TAM_F)-6);
     
     line((M_IZQ+PON_C+C*TAM_C)+10,(M_SUP+PON_F+F*TAM_F)-2,(M_IZQ+PON_C+C*TAM_C)+12,(M_SUP+PON_F+F*TAM_F)-2);
     line((M_IZQ+PON_C+C*TAM_C)+10,(M_SUP+PON_F+F*TAM_F)-3,(M_IZQ+PON_C+C*TAM_C)+12,(M_SUP+PON_F+F*TAM_F)-3);
     line((M_IZQ+PON_C+C*TAM_C)+10,(M_SUP+PON_F+F*TAM_F)-4,(M_IZQ+PON_C+C*TAM_C)+12,(M_SUP+PON_F+F*TAM_F)-4);
     line((M_IZQ+PON_C+C*TAM_C)+10,(M_SUP+PON_F+F*TAM_F)-5,(M_IZQ+PON_C+C*TAM_C)+12,(M_SUP+PON_F+F*TAM_F)-5);
     line((M_IZQ+PON_C+C*TAM_C)+10,(M_SUP+PON_F+F*TAM_F)-6,(M_IZQ+PON_C+C*TAM_C)+12,(M_SUP+PON_F+F*TAM_F)-6);
     
     line((M_IZQ+PON_C+C*TAM_C)-8,(M_SUP+PON_F+F*TAM_F)+1,(M_IZQ+PON_C+C*TAM_C)+6,(M_SUP+PON_F+F*TAM_F)+1);
     line((M_IZQ+PON_C+C*TAM_C)-8,(M_SUP+PON_F+F*TAM_F)+2,(M_IZQ+PON_C+C*TAM_C)+6,(M_SUP+PON_F+F*TAM_F)+2);
     
     line((M_IZQ+PON_C+C*TAM_C)-8,(M_SUP+PON_F+F*TAM_F)+4,(M_IZQ+PON_C+C*TAM_C)-6,(M_SUP+PON_F+F*TAM_F)+4);
     line((M_IZQ+PON_C+C*TAM_C)-8,(M_SUP+PON_F+F*TAM_F)+3,(M_IZQ+PON_C+C*TAM_C)-6,(M_SUP+PON_F+F*TAM_F)+3);
     line((M_IZQ+PON_C+C*TAM_C)+4,(M_SUP+PON_F+F*TAM_F)+4,(M_IZQ+PON_C+C*TAM_C)+6,(M_SUP+PON_F+F*TAM_F)+4);
     line((M_IZQ+PON_C+C*TAM_C)+4,(M_SUP+PON_F+F*TAM_F)+3,(M_IZQ+PON_C+C*TAM_C)+6,(M_SUP+PON_F+F*TAM_F)+3);
     
     line((M_IZQ+PON_C+C*TAM_C)-10,(M_SUP+PON_F+F*TAM_F)+6,(M_IZQ+PON_C+C*TAM_C)-8,(M_SUP+PON_F+F*TAM_F)+6);
     line((M_IZQ+PON_C+C*TAM_C)-10,(M_SUP+PON_F+F*TAM_F)+5,(M_IZQ+PON_C+C*TAM_C)-8,(M_SUP+PON_F+F*TAM_F)+5);
     line((M_IZQ+PON_C+C*TAM_C)+6,(M_SUP+PON_F+F*TAM_F)+6,(M_IZQ+PON_C+C*TAM_C)+8,(M_SUP+PON_F+F*TAM_F)+6);
     line((M_IZQ+PON_C+C*TAM_C)+6,(M_SUP+PON_F+F*TAM_F)+5,(M_IZQ+PON_C+C*TAM_C)+8,(M_SUP+PON_F+F*TAM_F)+5);

}

//ficheros

void ordenarPuntuaciones()
{//ordena las puntuaciones mediante el sistema de la burbuja.
     int OR =0;
     int AUX;
     char auxs[1][4];
     while (!OR){
           OR=1;
           for (N=0;N<2;N++){
               if (VEC_D[N]<VEC_D[N+1]){
                  AUX=VEC_D[N];
                  VEC_D[N]=VEC_D[N+1];
                  VEC_D[N+1]=AUX;
                                     
                  strcpy(auxs[1],VEC_N[N]);
                  strcpy(VEC_N[N],VEC_N[N+1]);
                  strcpy(VEC_N[N+1],auxs[1]);
                  OR=0;
               }
           }                                
     }
     
     if (puntuacion > VEC_D[0]){            // aqui si es igual no lo pone 1. porque se ha obtenido mas tarde que el primero :)
        VEC_D[2]=VEC_D[1];           
        strcpy(VEC_N[2],VEC_N[1]);  
        VEC_D[1]=VEC_D[0];           
        strcpy(VEC_N[1],VEC_N[0]);             
        VEC_D[0]=puntuacion;
        strcpy(VEC_N[0],nombre);             
        }else{
             if (puntuacion >= VEC_D[1]){
                VEC_D[2]=VEC_D[1];           
                strcpy(VEC_N[2],VEC_N[1]);
                VEC_D[1]=puntuacion;
                strcpy(VEC_N[1],nombre);
             }else{
                   if (puntuacion >= VEC_D[2]){
                      VEC_D[2]=puntuacion;
                      strcpy(VEC_N[2],nombre);
                   }
             }
       } 
}

void nombreJugador()
{//funcion para obtener el nombre del jugador
     char CAD[40];
     char CAR=0;
     int n=0;
     
     while (kbhit()) Ain=getch(); //guarda caracteres no deseados.
     cleardevice();
     settextstyle(2,0,10);
     setcolor(GREEN);
     outtextxy(220,50,"SPACE   INVADERS");
     setcolor(MAGENTA);
     invader2(7,4);
     setcolor(LIGHTBLUE);
     invader(22,6);
     setcolor(LIGHTGREEN);
     invader(6,14);
     
     settextstyle(3,0,1);
     setcolor(WHITE);
     outtextxy(350,200,"ESCRIBE TU NOMBRE");
     outtextxy(350,230,"(MAXIMO 3 LETRAS)");
     while (n<=2){
           CAR=getch();
           nombre[n]=CAR;
           sprintf(CAD,"%c",CAR);
           settextstyle(2,0,8);
           setcolor(RED);
           outtextxy(400+(n*25),260,CAD);
           n++;
     }
     sleep(200);
     setcolor(GREEN);
     settextstyle(3,0,1);
     outtextxy(350,300,"ESPERA UN MOMENTO");
     sleep(1000);
     outtextxy(563,300,".");
     sleep(1000);
     outtextxy(567,300,".");
     sleep(1000);
     outtextxy(571,300,".");
     sleep(1000);
     outtextxy(574,300,".");
     sleep(1000);
     while (kbhit()) Ain=getch();
}    

void leerFichero()
{
     fichero = fopen("punts.txt","r");
     if (fichero == NULL) printf("ERROR FICHERO\n");
     else {
          N = 0;
          do{
             fscanf(fichero,"%s",VEC_N[N]);
             fscanf(fichero,"%s",CAD); 
             VEC_D[N] = atoi(CAD);
             N++;
          }while(!feof(fichero));       
       }
       fclose(fichero);  
}

void escribirFichero()
{ 
     fichero = fopen("punts.txt","w");
     if (fichero == NULL) printf("ERROR FICHERO\n");
     else {
          for (N=0;N<=2;N++){
              fputs(VEC_N[N],fichero);
              fputc('\15',fichero);
              itoa(VEC_D[N],CAD,10);
              fputs(CAD,fichero);
              fputc('\15',fichero);
              fputc('\12',fichero);  
            }
       }
       fclose(fichero);
}
