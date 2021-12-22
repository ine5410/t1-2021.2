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
}

void bancada_insere(bancada_t *self, lampada_t *lampada) 
{
    /* TODO: Adicionar código nesta função se necessário! */

    plog("[bancada] Lâmpada %u INSERIDA na BANCADA DE TESTE (slots ocupados = %u)\n", lampada->id, ++self->slots_ocupados);
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

    /* !!! CÓDIGO TEMPORÁRIO: VOCÊ DEVERÁ ALTERAR !!! */
    lampada_t *lampada = &self->slots[0];
    /* ------------------------- */

    plog("[bancada] Lâmpada %u REMOVIDA na BANCADA DE TESTE (slots ocupados = %u)\n", lampada->id, --self->slots_ocupados);

    return(NULL);
}

void bancada_finaliza(bancada_t *self)
{
    /* TODO: Adicionar código nesta função se necessário! */

    printf("Estatísticas de lâmpadas: testadas = %u, aprovadas = %u, reprovadas = %d\n", self->total_testadas, self->total_aprovadas, self->total_reprovadas);

    free(self->slots);
}
