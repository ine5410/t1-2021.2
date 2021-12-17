#include <stdlib.h>
#include "buffer.h"

/* --------------------------------------------------------- */
/* ATENÇÃO: Não será necessário modificar as funções abaixo!  */
/* --------------------------------------------------------- */

void buffer_inicializa(buffer_t *self)
{
    /* TODO: Adicionar código nesta função se necessário! */
    
    self->quantidade = 0;
    self->slots = (lampada_t **) malloc(sizeof(lampada_t *) * config.capacidade_buffer);
}

void buffer_insere(buffer_t *self, lampada_t *lampada) 
{
    /* TODO: Adicionar código nesta função se necessário! */
    
    plog("[buffer] Lâmpada %u INSERIDA no BUFFER (slots ocupados = %u)\n", lampada->id, ++self->quantidade);
}

lampada_t * buffer_remove(buffer_t *self)
{
    /* TODO: Adicionar código nesta função se necessário! */
    
    /* !!! CÓDIGO TEMPORÁRIO !!! */
    lampada_t *lampada = self->slots[0];
    /* ------------------------- */

    plog("[buffer] Lâmpada %u REMOVIDA do BUFFER (slots ocupados = %u)\n", lampada->id, --self->quantidade);

    return(NULL);
}

void buffer_finaliza(buffer_t *self)
{
    /* TODO: Adicionar código nesta função se necessário! */

    free(self->slots);
}