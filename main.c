#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

int numero_vueltas, numero_caballos, metros_meta, MetrosTotal;

struct Caballo {
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
  mvprintw(y,x," %c",caba->id);//posiciona e imprime el competidor h
  refresh();												//refresca los cambion en la pantalla
  usleep(100000/10);								//duerme por 1/4 de segundo
  if((rand() % 2)) x++;		    		//avanza una posicion con probabilidad 0.5
  return x;
}

int main() {
	Caballo cab1, cab2, cab3, cab4, cab5, cab6, cab7;

	printf("CARRERA DE CABALLOS\n");

    printf("Ingresa el número de caballos (entre 2 y 7): ");
    scanf("%d", &numero_caballos);

	while(numero_caballos < 2 || numero_caballos > 7){
        printf("Debe ser un número entre 2 y 7: ");
        scanf("%d", &numero_caballos);
	}

	printf("Ingresa el número de vueltas (entre 1 y 4): ");
	scanf("%d", &numero_vueltas);

	while(numero_vueltas < 1 || numero_vueltas > 4){
        printf("Debe ser un número entre 1 y 4: ");
        scanf("%d \n", &numero_vueltas);
	}

	printf("\nIngresa el número de metros de la pista (30, 40, 50 y 60)\n");
	printf("Debe ingresar uno de los valores entre paréntesis: ");
	scanf("%d", &metros_meta);

	while(metros_meta != 30 && metros_meta != 40 && metros_meta != 50 && metros_meta != 60){
        printf("Debe ingresar uno de los siguientes valores (30, 40, 50, 60): ");
        scanf("%d", &metros_meta);
	}

	printf("\n*********************\n");
	printf("Número de caballos: %d \n", numero_caballos);
	printf("Número de vueltas: %d \n", numero_vueltas);
	printf("Metros pista: %d \n", metros_meta);
	printf("*********************\n\n");

    for(int i = 1; i<numero_caballos; i++){
        if(i == 1 ){
            cab1.id=1
            cab1.carril=1;
            cab1.caballo='A';
            cab1.pos=1;
        }else if(i == 2 ){
            cab2.id=2
            cab2.carril=3;
            cab2.caballo='B';
            cab2.pos=1;
        }else if(i == 3 ){
            cab3.id=3
            cab3.carril=5;
            cab3.caballo='C';
            cab3.pos=1;
        }else if(i == 4 ){
            cab4.id=4
            cab4.carril=7;
            cab4.caballo='D';
            cab4.pos=1;
        }else if(i == 5 ){
            cab5.id=5
            cab5.carril=9;
            cab5.caballo='E';
            cab5.pos=1;
        }else if(i == 6 ){
            cab6.id=6
            cab6.carril=11;
            cab6.caballo='F';
            cab6.pos=1;
        }else if(i == 7 ){
            cab7.id=7
            cab7.carril=13;
            cab7.caballo='G';
            cab7.pos=1;
        }
    }

    for(int i = 1; i<numero_vueltas + 1; i++){

        while (x<metros_meta && cab1.pos<metros_meta && cab2.pos<metros_meta ){



            cab1.pos=funcionCab(&cab1);
            cab2.pos=funcionCab(&cab2);
        }

    }

	pthread_t hilos[numero_caballos];
	struct Caballo caballos[numero_caballos];
	long c, d;

	for(c = 0; c < numero_caballos; c++) {
		caballos[c].id = c+1;
		pthread_create(&hilos[c], NULL, crear_caballo, (void *) &caballos[c]);
	}

	for(c = 0; c < numero_caballos; c++)
		pthread_join(hilos[c], NULL);
	int y, z;
	for(y = 0; y < numero_caballos; y++) {
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
		printf("El caballo %ld llegó en el puesto %d \n", caballos[y].id, y+1);
	}

	printf("\n*****************************\n");
	printf("GRACIAS POR PARTICIPAR!!!!!\n");
	printf("*****************************\n\n");

	pthread_exit(NULL);
	return 0;
}
