#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#include "config.h"
#include "robo.h"

void robo_inicializa(robo_t *self, unsigned int id, 
                     void *equipamento_esquerda, equipamento_t tipo_equipamento_esquerda,
                     void *equipamento_direita, equipamento_t tipo_equipamento_direita)
{
    /* TODO: Adicionar código nesta função se necessário! */
    
    self->id = id;
    self->equipamento_esquerda = equipamento_esquerda;
    self->tipo_equipamento_esquerda = tipo_equipamento_esquerda;
    self->equipamento_direita = equipamento_esquerda;
    self->tipo_equipamento_direita = tipo_equipamento_direita;

    if (pthread_create(&self->thread, NULL, robo_executa, (void *) self) == 0) {
        plog("[robô %u] Inicializado\n", self->id);
    }
    else {
        plog("[robô %u] Erro ao inicializar o robô\n", self->id);
    }
}

void * robo_executa(void *arg)
{
    /* TODO: Adicionar código nesta função se necessário! */
    
    /* Recupera o argumento de entrada (robo_t). */
    // robo_t *robo = (robo_t *) arg;

    pthread_exit(NULL);
}

lampada_t * robo_pega_lampada(robo_t *self)
{
    /* TODO: Adicionar código nesta função se necessário! */

    lampada_t *lampada = NULL;

    switch(self->tipo_equipamento_esquerda) {
        case ESTEIRA:
            lampada = esteira_remove((esteira_t *) self->equipamento_esquerda);
            plog("[robô %u] Lâmpada %u REMOVIDA da ESTEIRA\n", self->id, lampada->id);
            break;
        case BUFFER:
            lampada = buffer_remove((buffer_t *) self->equipamento_esquerda);
            plog("[robô %u] Lâmpada %u REMOVIDA do BUFFER\n", self->id, lampada->id);
            break;
        case BANCADA:
            lampada = bancada_remove((bancada_t *) self->equipamento_esquerda);
            plog("[robô %u] Lâmpada %u REMOVIDA da BANCADA\n", self->id, lampada->id);
            break;
        default:
            plog("[robô %u] Erro ao recuperar equipamento da esquerda\n", self->id);
    }
    
    return(lampada);
}

void robo_coloca_lampada(robo_t *self, lampada_t *lampada)
{
    controle_agvs_t * controle = NULL;
    agv_t *agv = NULL;
    
    /* TODO: Adicionar código nesta função se necessário! */

    switch(self->tipo_equipamento_direita) {
        case BUFFER:
            buffer_insere((buffer_t *) self->equipamento_direita, lampada);
            plog("[robô %u] Lâmpada %u INSERIDA no BUFFER\n", self->id, lampada->id);
            break;
        case BANCADA:
            bancada_insere((bancada_t *) self->equipamento_direita, lampada);
            plog("[robô %u] Lâmpada %u INSERIDA na BANCADA\n", self->id, lampada->id);
            break;
        case AGVS:
            controle = (controle_agvs_t *) self->equipamento_direita;
            if (lampada->resultado_teste == DESCONHECIDO) {
                /* Devolve lâmpada para bancada de teste */
                bancada_insere((bancada_t *) self->equipamento_esquerda, lampada);
                plog("[robô %u] Lâmpada %u DEVOLVIDA para a BANCADA\n", self->id, lampada->id);
                break;
            } else if (lampada->resultado_teste == APROVADA) {                
                agv = controle_retorna_agv(controle, false); // AGV com lâmpadas aprovadas 
            } else {                                         // Lâmpada reprovada no teste
                agv = controle_retorna_agv(controle, true);  // AGV com lâmpadas para reciclar
            }
            agv_insere(agv, lampada);
            plog("[robô %u] Lâmpada %u INSERIDA no AGV %u\n", self->id, lampada->id, agv->id);            
            break;
        default:
            plog("[robô %u] Erro ao recuperar equipamento da direita\n", self->id);
    }
}

void robo_finaliza(robo_t *self)
{
    /* TODO: Adicionar código nesta função se necessário! */
    
    pthread_join(self->thread, NULL);
    plog("[robô %u] Finalizado\n", self->id);
}
