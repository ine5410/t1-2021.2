#include <stdlib.h>
#include "bancada.h"

void bancada_inicializa(bancada_t *self)
{
    /* TODO: Adicionar código nesta função se necessário! */

    self->slots_ocupados = 0;
    self->total_testadas = 0;
    self->total_aprovadas = 0;
    self->total_reprovadas = 0;
    self->slots = (lampada_t *) malloc(sizeof(lampada_t) * config.capacidade_bancada);

    plog("[bancada] Inicializada\n");
}

void bancada_insere(bancada_t *self, lampada_t *lampada) 
{
    /* TODO: Adicionar código nesta função se necessário! */

    /* Incrementa a quantidade de slots ocupados na bancada. */
    self->slots_ocupados++;
}

bool bancada_testa(bancada_t *self, lampada_t *lampada)
{
    /* TODO: Adicionar código nesta função se necessário! */

    /* Simula um tempo aleatório de teste da lâmpada. NÃO REMOVER! */
    msleep(rand() % config.tempo_max_teste);

    self->total_testadas++;

    /* Testa se a lâmpada possui algum defeito. */
    if (lampada->bulbo == FALHA || lampada->luz == FALHA || lampada->marca == FALHA || lampada->rosca == FALHA) {
        lampada->resultado_teste = REPROVADA;
        self->total_reprovadas++;
        plog("[bancada] Resultado do teste da lâmpada %u: REPROVADA!\n", lampada->id);
        return false;
    }

    self->total_aprovadas++;
    lampada->resultado_teste = APROVADA;
    plog("[bancada] Resultado do teste da lâmpada %u: APROVADA!\n", lampada->id);
    return true;
}

lampada_t * bancada_remove(bancada_t *self)
{
    /* TODO: Adicionar código nesta função se necessário! */

    /* Decrementa a quantidade de slots ocupados na bancada. */
    self->slots_ocupados--;

    return(NULL);
}

void bancada_finaliza(bancada_t *self)
{
    /* TODO: Adicionar código nesta função se necessário! */

    free(self->slots);
    plog("[bancada] Finalizada\n");
}

void bancada_imprime_resultados(bancada_t *self) 
{
    printf("\n");
    printf(BAR);
    printf("RESULTADOS DA SIMULAÇÃO\n");
    printf(BAR);
    printf("Lâmpadas testadas  : %u\nLâmpadas aprovadas : %u\nLâmpadas reprovadas: %d\n", self->total_testadas, self->total_aprovadas, self->total_reprovadas);
    printf(BAR);
    printf("\n");
}