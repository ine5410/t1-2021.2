#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "config.h"
#include "esteira.h"
#include "robo.h"
#include "buffer.h"
#include "bancada.h"
#include "agv.h"
#include "controle_agvs.h"

config_t parse (int argc, char **argv)
{
    int c;

    /* Configuração padrão. */
    config_t config = { 
        100, /* Quantidade de lâmpadas.         */
        1,   /* Velocidade da esteira.          */
        16,  /* Capacidade do buffer.           */
        4,   /* Capacidade da bancada de teste. */
        12,  /* Capacidade de cada AGV.      */
        2    /* Quantidade de AGVs.             */
    };

    while ((c = getopt(argc, argv, "l:v:b:t:a:c:h")) != -1) {
        switch (c) {
            case 'l':
                if (atoi(optarg) < 0) {
                    printf("Erro: o número de lâmpadas precisa ser maior que zero.");
                    exit(0);
                }
                config.quantidade_lampadas = atoi(optarg);
                break;
            case 'v':
                if (atoi(optarg) < ESTEIRA_VEL_MIN || atoi(optarg) > ESTEIRA_VEL_MAX) {
                    printf("Erro: a velocidade da esteira precisa ser entre %d e %d.", ESTEIRA_VEL_MIN, ESTEIRA_VEL_MAX);
                    exit(0);
                }
                config.velocidade_esteira = atoi(optarg);
                break;
            case 'b':
                if (atoi(optarg) < 0) {
                    printf("Erro: a capacidade do buffer precisa ser maior que zero.");
                    exit(0);
                }
                config.capacidade_buffer = atoi(optarg);
                break;
            case 't':
                if (atoi(optarg) < 0) {
                    printf("Erro: a capacidade da bancada precisa ser maior que zero.");
                    exit(0);
                }
                config.capacidade_bancada = atoi(optarg);
                break;
            case 'a':
                if (atoi(optarg) < 2) {
                    printf("Erro: a quantidade de AGVs precisa ser maior que dois.");
                    exit(0);
                }
                config.quantidade_agvs = atoi(optarg);
                break;
            case 'c':
                if (atoi(optarg) < 0) {
                    printf("Erro: a capacidade de cada AGV precisa ser maior que zero.");
                    exit(0);
                }
                config.capacidade_agv = atoi(optarg);
                break;
            case 'h':
                printf("Usage: %s [OPÇÕES]\n\nOpções:\n", argv[0]);
                printf("  -l  Quantidade de lâmpadas (padrão: 100).\n");
                printf("  -v  Velocidade da esteira (padrão: 1).\n");
                printf("  -b  Capacidade do buffer (padrão: 16).\n");
                printf("  -t  Capacidade da bancada de teste (padrão: 4).\n");
                printf("  -a  Quantidade de AGVs (padrão: 2).\n");
                printf("  -c  Capacidade de cada AGV (padrão: 12).\n");
                printf("  -h  Imprime esta ajuda.\n");
            default:
                exit(1);
        }
    }

    return config;
}

/* --------------------------------------------------------- *
 *                                                           *
 *     ATENÇÃO: A FUNÇÃO MAIN NÃO PODERÁ SER ALTERADA!       *
 *                                                           *
 * --------------------------------------------------------- */

int main (int argc, char **argv)
{
    esteira_t esteira;
    buffer_t buffer;
    bancada_t bancada;
    robo_t robos[3];
    controle_agvs_t controle_agvs;

    /* Faz o parsing dos parâmetros de entrada. */
    config = parse(argc, argv);
    
    /* Imprime as informações da execução. */
    printf(BAR);
    printf("Total de lâmpadas             : %u\n", config.quantidade_lampadas);
    printf("Velocidade da esteira         : %u\n", config.velocidade_esteira);
    printf("Capacidade do buffer          : %u\n", config.capacidade_buffer);
    printf("Capacidade da bancada de teste: %u\n", config.capacidade_bancada);
    printf("Capacidade de cada AGV        : %u\n", config.capacidade_agv);
    printf("Número de AGVs                : %u\n", config.quantidade_agvs);
    printf(BAR);
    printf("\n");

    /* Inicializa o gerador de números aleatórios. */
    srand(time(NULL));
    
    /* Inicializa os recursos. */
    esteira_inicializa(&esteira);

    /* Inicializa o buffer. */    
    buffer_inicializa(&buffer);

    /* Inicializa a bancada de teste. */    
    bancada_inicializa(&bancada);

    /* Inicializa os AGVs. */
    controle_inicializa_agvs(&controle_agvs, config.quantidade_agvs);

    /* Inicializa os robôs. */
    robo_inicializa(&robos[0], 1, (void *) &esteira, ESTEIRA, (void *) &buffer, BUFFER);
    robo_inicializa(&robos[1], 2, (void *) &buffer, BUFFER, (void *) &bancada, BANCADA);
    robo_inicializa(&robos[2], 3, (void *) &bancada, BANCADA, (void *) &controle_agvs, AGVS);

    /* Finaliza tudo. */
    esteira_finaliza(&esteira);
    buffer_finaliza(&buffer);
    bancada_finaliza(&bancada);

    for (int i = 0; i < 3; i++)
        robo_finaliza(&robos[i]);

    controle_finaliza_agvs(&controle_agvs);

    return 0;
}