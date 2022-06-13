/*######################### Descripción del proyecto: #########################
#   Programa en C que simula una carrera de caballos.
#   Descipción:
#    - Se creará un programa que simule una carrera de caballos con avance aleatorio.
#    - Código desarrollado mediante metodología de programación modular, con el objetivo de reutilizar bibliotecas de funciones y/o métodos.
#    - Versión: 0.1 (Prueba y demostración)
#
#   Autores:
#       - José Avilán (https://github.com/JoseAvilan)
#       - Nicolas Aburto (https://github.com/NicolasAburto)
#       - Franco Avilés (https://github.com/FrancoAv1)
#
#   Licencia:
#       - Junio 2022. Apache 2.0.
#
###########################################################################################################*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <ncurses.h> 						//bibliotecas manejo de pantalla
#include <time.h>

int numero_vueltas, numero_caballos, metros_meta, MetrosTotal;

typedef struct {
	long id;
	char nombre;
	int pos;
	int carril;
} Caballo;

/*void *crear_caballo(void *d);
int vueltas(struct Caballo *c);

void *crear_caballo(void *d) {

    struct Caballo *caballo;
	caballo = (struct Caballo *) d;

	caballo->demora = vueltas(caballo);
}

int vueltas(struct Caballo *c) {
	int i, cuenta = 0, PasosCaballo = 0;

	for(i = 1; i < numero_vueltas+1; i++) {
		int s = (rand() % 5)+1;
		printf("Caballo: %ld - Vuelta: %d - Descansa %d segundos\n", c->id, i, s);
		sleep(s);
		cuenta += s;

		while(PasosCaballo < (metros_meta*i)){
            PasosCaballo += (rand() % 10)+1;
		}

	}
	printf("\nPasos caballo %ld= %d", c->id, PasosCaballo);
	return cuenta;
}*/

int funcionCab(Caballo *caba){
  int x=caba->pos,y=caba->carril;		    //para posicionamiento de pantalla
  mvprintw(y,x," %c",caba->nombre);//posiciona e imprime el competidor h
  refresh();												//refresca los cambion en la pantalla
  usleep(100000/10);								//duerme por 1/4 de segundo
  if((rand() % 2)) x++;		    		//avanza una posicion con probabilidad 0.5
  return x;
}

int main() {
    int x=1,y=15,x1=1,x2=1;		    							//para posicionamiento de pantalla

	Caballo cab1, cab2, cab3, cab4, cab5, cab6, cab7;



	printf("CARRERA DE CABALLOS\n");


    printf("Ingresa el numero de caballos (entre 2 y 7): ");
    scanf("%d", &numero_caballos);

	while(numero_caballos < 2 || numero_caballos > 7){
        printf("Debe ser un numero entre 2 y 7: ");
        scanf("%d", &numero_caballos);
	}

	printf("Ingresa el numero de vueltas (entre 1 y 4): ");
	scanf("%d", &numero_vueltas);

	while(numero_vueltas < 1 || numero_vueltas > 4){
        printf("Debe ser un numero entre 1 y 4: ");
        scanf("%d \n", &numero_vueltas);
	}

	printf("\nIngresa el numero de metros de la pista (30, 40, 50 y 60)\n");
	printf("Debe ingresar uno de los valores entre parÃ©ntesis: ");
	scanf("%d", &metros_meta);

	while(metros_meta != 30 && metros_meta != 40 && metros_meta != 50 && metros_meta != 60){
        printf("Debe ingresar uno de los siguientes valores (30, 40, 50, 60): ");
        scanf("%d", &metros_meta);
	}

	printf("\n*********************\n");
	printf("Numero de caballos: %d \n", numero_caballos);
	printf("Numero de vueltas: %d \n", numero_vueltas);
	printf("Metros pista: %d \n", metros_meta);
	printf("*********************\n\n");

    initscr();										//inicializa la pantalla para ncurses
	curs_set(0);									//elimina el cursor
	erase();											//limpia pantalla
	refresh();										//refresca los cambion en la pantalla
	srand(time(NULL));						//inicializa semilla de la funcion random



            cab1.id=1;
            cab1.carril=1;
            cab1.nombre='A';
            cab1.pos=1;
            cab2.id=2;
            cab2.carril=3;
            cab2.nombre='B';
            cab2.pos=1;
            cab3.id=3;
            cab3.carril=5;
            cab3.nombre='C';
            cab3.pos=1;
            cab4.id=4;
            cab4.carril=7;
            cab4.nombre='D';
            cab4.pos=1;
            cab5.id=5;
            cab5.carril=9;
            cab5.nombre='E';
            cab5.pos=1;
            cab6.id=6;
            cab6.carril=11;
            cab6.nombre='F';
            cab6.pos=1;
            cab7.id=7;
            cab7.carril=13;
            cab7.nombre='G';
            cab7.pos=1;



    for(int i = 1; i<numero_vueltas + 1; i++){
        while (x<metros_meta && cab1.pos<metros_meta && cab2.pos<metros_meta && cab3.pos<metros_meta
         && cab4.pos<metros_meta && cab5.pos<metros_meta && cab6.pos<metros_meta && cab7.pos<metros_meta){
            cab1.pos=funcionCab(&cab1);
            cab2.pos=funcionCab(&cab2);
            cab3.pos=funcionCab(&cab3);
            cab4.pos=funcionCab(&cab4);
            cab5.pos=funcionCab(&cab5);
            cab6.pos=funcionCab(&cab6);
            cab7.pos=funcionCab(&cab7);
        }
    }

	/*pthread_t hilos[numero_caballos];
	struct Caballo caballos[numero_caballos];
	long c, d;*/
/*
	for(c = 0; c < numero_caballos; c++) {
		caballos[c].id = c+1;
		pthread_create(&hilos[c], NULL, crear_caballo, (void *) &caballos[c]);
	}*/

	/*for(c = 0; c < numero_caballos; c++)
		pthread_join(hilos[c], NULL);
	int y, z;*/
	/*for(y = 0; y < numero_caballos; y++) {
		for(z = 0; z < numero_caballos; z++) {
			if(caballos[y].demora < caballos[z].demora) {
				int id = caballos[y].id;
				int demora = caballos[y].demora;
				caballos[y].id = caballos[z].id;
				caballos[y].demora = caballos[z].demora;

				caballos[z].id = id;
				caballos[z].demora = demora;
			}
		}
	}
    printf("\n\n");
	for(y = 0; y < numero_caballos; y++) {
		printf("El caballo %ld llegÃ³ en el puesto %d \n", caballos[y].id, y+1);
	}*/
    refresh();
	printf("\n\n");
	printf("GRACIAS POR PARTICIPAR!!!!!\n");
	printf("\n\n");


	getch(); 										//espera que se ingrese cualquier tecla para salir
	endwin();										//cierra la pantalla de ncurses

	pthread_exit(NULL);
	return 0;
}
