#ifndef __BANCADA_H__
#define __BANCADA_H__

    #include "config.h"
    #include "lampada.h"

    /*============================================================================*
     * DESCRIÇÃO: Representa uma bancada de teste.                                *
     *============================================================================*/

    /**
     * @brief Define os atributos da bancada de teste.
     */
    typedef struct {   
        unsigned int quantidade; /* Quantidade atual de lâmpadas na bancada de teste. */
        lampada_t *slots;        /* Array que armanazena as lâmpadas na bancada de teste. */
    } bancada_t;

    /*============================================================================*
     * Funções utilizadas em arquivos que incluem esse .h                         *
     *============================================================================*/

    /**
     * @brief Inicializa a bancada de teste.
     * 
     * @param self A bancada.
     */
    extern void bancada_inicializa(bancada_t *self);

    /**
     * @brief Insere uma lâmpada na bancada de teste.
     * 
     * @param self A bancada.
     * @param lampada A lâmpada a ser inserida na bancada.
     */
    extern void bancada_insere(bancada_t *self, lampada_t *lampada);

    /**
     * @brief Remove uma lâmpada da bancada de teste.
     * 
     * @param self A bancada.
     * @param lampada A lâmpada a ser removida da bancada.
     * @return Um ponteiro para a lâmpada removida.
     */
    extern lampada_t * bancada_remove(bancada_t *self);

    /**
     * @brief Finaliza a bancada de teste.
     * 
     * @param self A bancada.
     */
    extern void bancada_finaliza(bancada_t *self);

#endif /*__BANCADA_H__*/