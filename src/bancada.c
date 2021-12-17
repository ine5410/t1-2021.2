#include <stdlib.h>
#include "bancada.h"

/* --------------------------------------------------------- */
/* ATENÇÃO: Não será necessário modificar as funções abaixo!  */
/* --------------------------------------------------------- */

void bancada_inicializa(bancada_t *self)
{
    /* TODO: Adicionar código nesta função se necessário! */

    self->quantidade = 0;
    self->slots = (lampada_t *) malloc(sizeof(lampada_t) * config.capacidade_bancada);
}

void bancada_insere(bancada_t *self, lampada_t *lampada) 
{
    /* TODO: Adicionar código nesta função se necessário! */

    plog("[bancada] Lâmpada %u INSERIDA na BANCADA DE TESTE (slots ocupados = %u)\n", lampada->id, ++self->quantidade);
}

lampada_t * bancada_remove(bancada_t *self)
{
    /* TODO: Adicionar código nesta função se necessário! */

    /* !!! CÓDIGO TEMPORÁRIO !!! */
    lampada_t *lampada = &self->slots[0];
    /* ------------------------- */

    plog("[bancada] Lâmpada %u REMOVIDA na BANCADA DE TESTE (slots ocupados = %u)\n", lampada->id, --self->quantidade);

    return(NULL);
}

void bancada_finaliza(bancada_t *self)
{
    /* TODO: Adicionar código nesta função se necessário! */

    free(self->slots);
}