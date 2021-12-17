#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#include "config.h"
#include "esteira.h"

void esteira_inicializa(esteira_t *self)
{
    /* TODO: Adicionar código nesta função se necessário! */

    self->tipo = ESTEIRA;
    self->lampadas_produzidas = 0;
    self->lampadas_consumidas = 0;
    self->lampadas = (lampada_t *) malloc(sizeof(lampada_t) * config.quantidade_lampadas);

    if (pthread_create(&self->thread, NULL, esteira_executa, (void *) self) == 0) {
        plog("[esteira] Inicializada\n");
    }
    else {
        plog("[esteira] Erro ao inicializar esteira\n");
    }
}

void esteira_insere(esteira_t *self) 
{
    /* TODO: Adicionar código nesta função se necessário! */
    
    lampada_inicializa(&(self->lampadas[self->lampadas_produzidas]), self->lampadas_produzidas, rand() % 2, rand() % 2, rand() % 2, rand() % 2);
    plog("[esteira] Lâmpada %u INSERIDA na esteira (bulbo = %u, luz = %u, rosca = %u, marca = %u)\n", self->lampadas_produzidas, self->lampadas[self->lampadas_produzidas].bulbo, 
        self->lampadas[self->lampadas_produzidas].luz, self->lampadas[self->lampadas_produzidas].rosca, self->lampadas[self->lampadas_produzidas].marca);
    self->lampadas_produzidas++;
}

lampada_t * esteira_remove(esteira_t *self)
{
    return(&self->lampadas[self->lampadas_consumidas++]);
}

void esteira_finaliza(esteira_t *self)
{
    /* TODO: Adicionar código nesta função se necessário! */
    
    pthread_join(self->thread, NULL);
    free(self->lampadas);
    plog("[esteira] Finalizada\n");
}

/* --------------------------------------------------------- */
/* ATENÇÃO: Não será necessário modificar as funções abaixo!  */
/* --------------------------------------------------------- */

void * esteira_executa(void *arg)
{
    /* Recupera o argumento de entrada (esteira_t). */
    esteira_t *esteira = (esteira_t *) arg;

    /* Produz config.total_lampadas lâmpadas. */
    for (int i = 0; i < config.quantidade_lampadas; i++) {
        esteira_insere(esteira);
        msleep((ESTEIRA_VEL_MAX + 1 - config.velocidade_esteira) * ESTEIRA_VEL_TEMPO);
    }

    pthread_exit(NULL);
}
