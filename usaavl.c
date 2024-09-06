#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "avl.h"

typedef struct {
    int matricula;
    char curso[60];
    double cr;
    int ano_entrada;
} t_aluno;

void imprimir_aluno(t_aluno *al){
    if (al){
        printf("%d %s %.3lf %d\n", al->matricula, al->curso, al->cr, al->ano_entrada);
    }
}

int comparar_aluno(t_aluno* a1, t_aluno* a2){
    return (a1->matricula - a2->matricula);
}

t_aluno* criar_aluno(int matricula, char *curso, double cr, int ano_entrada){
    t_aluno* novo = malloc(sizeof(t_aluno));
    novo->matricula = matricula;
    strcpy(novo->curso, curso);
    novo->cr = cr;
    novo->ano_entrada = ano_entrada;

    return novo;
}

void destroy_aluno(t_aluno *al){
    //assert(al!=NULL);
    if (al)
        free(al);
}

int main(){
    t_aluno *calouro;
    int matricula, ano_entrada;
    char curso[60];
    double cr;
    t_avl* calouros = criar_avl(imprimir_aluno, comparar_aluno);

    scanf("%d", &matricula);
    while (matricula >0){
        scanf("%s", curso);
        scanf("%lf", &cr);
        scanf("%d", &ano_entrada);
        calouro = criar_aluno(matricula, curso, cr, ano_entrada);
        inserir_avl(calouros, calouro);
        scanf("%d", &matricula);
    }
    int cmd;
    scanf("%d", &cmd);
    while(cmd != -1){
        if (cmd == 1){ // cmd buscar
            scanf("%d", &matricula);
            t_aluno* buscado = buscar_avl(calouros, &matricula);
            imprimir_aluno(buscado);

        }else if(cmd == 2){ // remover
               scanf("%d", &matricula);
        //     t_aluno *desistente = remover_hash(calouros, matricula);
        //     imprimir_aluno(desistente);
        //     destroy_aluno(desistente);
        }else if(cmd == 3){ // cmd inserir
            scanf("%d", &matricula);
            scanf("%s", curso);
            scanf("%lf", &cr);
            scanf("%d", &ano_entrada);
            calouro = criar_aluno(matricula, curso, cr, ano_entrada);
            inserir_avl(calouros, calouro);
        }else if(cmd == 4){
            imprimir_avl(calouros);
        }
        scanf("%d", &cmd);
    }
}