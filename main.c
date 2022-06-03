#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

int numero_vueltas, numero_caballos;

struct Caballo {
	long id;
	int demora;
} Caballo;

void *crear_caballo(void *d);
int vueltas(struct Caballo *c);

void *crear_caballo(void *d) {
	clock_t inicio, fin;
	double segundos;
	inicio = clock();

	struct Caballo *caballo;
	caballo = (struct Caballo *) d;

	int i;
	caballo->demora = vueltas(caballo);

	fin = clock();
	segundos = (double)(fin - inicio) / CLOCKS_PER_SEC;
	//printf("***El hilo del caballo %ld tardó %f segundos***\n", caballo->id, segundos);
}

int vueltas(struct Caballo *c) {
	int i, cuenta = 0;
	for(i = 1; i < numero_vueltas+1; i++) {
		int s = (rand() % 5)+1;
		printf("Caballo: %ld - Vuelta: %d - Descansa %d segundos\n", c->id, i, s);
		sleep(s);
		cuenta += s;
	}
	return cuenta;
}

int main() {
	srand(time(NULL));
	printf("CARRERA DE CABALLOS\n");

    printf("Ingresa el número de caballos (entre 2 y 7): ");
    scanf("%d", &numero_caballos);

	while(numero_caballos < 2 || numero_caballos > 7){
        printf("Debe ser un número entre 2 y 7: ");
        scanf("%d", &numero_caballos);
	}

	printf("Ingresa el numero de vueltas (entre 1 y 4): ");
	scanf("%d", &numero_vueltas);

	while(numero_vueltas < 1 || numero_vueltas > 4){
        printf("Debe ser un número entre 1 y 4: ");
        scanf("%d \n", &numero_vueltas);
	}

	printf("*********************\n");
	printf("Número de caballos: %d \n", numero_caballos);
	printf("Número de vueltas: %d \n", numero_vueltas);
	printf("*********************\n");

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

	for(y = 0; y < numero_caballos; y++) {
		printf("El caballo %ld llegó en el puesto %d \n", caballos[y].id, y+1);
	}

	pthread_exit(NULL);
	return 0;
}


