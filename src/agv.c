#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "agv.h"

void agv_inicializa(agv_t *self, unsigned int id)
{
    /* TODO: Adicionar código nesta função se necessário! */
    self->id = id;
    self->cont_lampadas = 0;
    if (pthread_create(&self->thread, NULL, agv_executa, (void *) self) == 0) {
        plog("[AGV %u] Inicializado\n", self->id);
    }
    else {
        plog("[AGV %u] Erro ao inicializar AGV\n", self->id);
    }
}

void * agv_executa(void *arg)
{ 
    /* Recupera o argumento de entrada (agv_t). */
    /* agv_t *agv = (agv_t *) arg; */

    /* TODO: Implementar aqui o comportamento do AGV */
  
    pthread_exit(NULL);
}

void agv_posiciona(agv_t *self, bool reciclar)
{
    /* AGV se posiciona para que lâmpadas sejam colocadas no seu compartimento de carga. */
    if (!self->posicionado && self->cont_lampadas == 0) {
        self->reciclar = reciclar;
        self->posicionado = true;

        if (reciclar) {
            plog("[AGV %u] Posicionado para carregamento com lâmpadas para reciclagem\n", self->id);
        } else {
            plog("[AGV %u] Posicionado para carregamento com lâmpadas aprovadas no teste\n", self->id);
        }
    } else {
        plog("[AGV %u] Erro ao tentar posicionar AVG em uso\n", self->id);
    }
}

void agv_insere(agv_t *self, lampada_t *lampada)
{
    /* TODO: Inserir uma lâmpada no compartimento de carga do AGV. */
    plog("[AGV %u] Lâmpada inserida no compartimento de carga.\n", self->id);
}

void agv_transporta(agv_t *self)
{
    /* TODO: Transportar a carga de lâmpadas para o depósito */
    self->posicionado = false;
    self->cont_lampadas = 0;
    plog("[AGV %u] Lâmpadas transportadas para o depósito.\n", self->id);
}

void agv_finaliza(agv_t *self)
{
    /* TODO: Adicionar código aqui se necessário! */
    pthread_join(self->thread, NULL);
    plog("[AGV %u] Finalizado\n", self->id);
}

/* --------------------------------------------------------- */
/* ATENÇÃO: Não será necessário modificar as funções abaixo! */
/* --------------------------------------------------------- */