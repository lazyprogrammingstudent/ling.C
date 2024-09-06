#include "stdlib.h"
#include "time.h"
#include "abb.h"

typedef struct no t_no;
struct no{
    void* carga;
    t_no *sae;
    t_no *sad;
    t_no *tral;
};

t_no* criar_no(void* carga){
    t_no* novo = malloc(sizeof(t_no));
    novo->sae = NULL;
    novo->sad = NULL;
    novo->tral = NULL;
    novo->carga = carga;
    return novo;
}

struct abb{
    t_no *raiz;
    int tamanho;
    t_imprimir_abb imprimir;
    t_comparar_abb comparar;
};

t_abb* criar_abb(t_imprimir_abb imprimir, t_comparar_abb comparar){
    t_abb *abb = malloc(sizeof(t_abb));
    abb->comparar =comparar;
    abb->imprimir = imprimir;
    abb->raiz = NULL;
    abb->tamanho = 0;

    return abb;
}

static t_no* __inserir_abb(t_no* raiz, t_no* tral, t_no* novo, t_comparar_abb comparar){
    if (raiz == NULL){
        novo->tral = tral;
        return novo;
    }
    if (comparar(novo->carga, raiz->carga) < 0){ // sae
        raiz->sae = __inserir_abb(raiz->sae, raiz, novo, comparar);
    }else{ //sad
        raiz->sad = __inserir_abb(raiz->sad, raiz, novo, comparar);
    }
    return raiz;
}

void inserir_abb(t_abb *abb, void* carga){
    t_no* novo = criar_no(carga);
    abb->raiz = __inserir_abb(abb->raiz, NULL, novo, abb->comparar);
}

static void __imprimir_abb(t_no* raiz, t_imprimir_abb imprimir){
    if(raiz == NULL)
        return;

    __imprimir_abb(raiz->sae, imprimir);
    imprimir(raiz->carga);
    __imprimir_abb(raiz->sad, imprimir);
}

void imprimir_abb(t_abb* abb){
    __imprimir_abb(abb->raiz, abb->imprimir);
}

t_no* __buscar_abb(t_no* raiz, t_comparar_abb comparar, void* chave ){
    if (raiz == NULL){
        return NULL;
    }else if (comparar(raiz->carga, chave) == 0){
        return raiz;
    }else if (comparar(raiz->carga, chave) > 0) {
         raiz = __buscar_abb(raiz->sae, comparar, chave);
    }else{
         raiz = __buscar_abb(raiz->sad, comparar, chave);
    }
    return raiz;
}

void* buscar_abb(t_abb* abb, void* chave){
    t_no* raiz = __buscar_abb(abb->raiz, abb->comparar, chave);
    if (raiz!=NULL){
        return raiz->carga;
    }
    return NULL;
}
static void __trocar(t_no* c1, t_no* c2){
    void* aux = c1->carga;
    c1->carga = c2->carga;
    c2->carga = aux;
}

static void* __remover_abb(t_no* raiz, t_comparar_abb comparar, void* chave){
    if (raiz == NULL){
        return NULL;
    }else if (comparar(raiz->carga, chave) > 0) {
         raiz->sae = __remover_abb(raiz->sae, comparar, chave);
    }else if (comparar(raiz->carga, chave) < 0) {
         raiz->sad = __remover_abb(raiz->sad, comparar, chave);
    }else{ // remocao
        if ((raiz->sad == NULL) && (raiz->sae == NULL)){
            free(raiz->carga); // memory leak ??!!!
            free(raiz);
            return NULL;
        } else if((raiz->sad == NULL) && (raiz->sae != NULL)){
             raiz->sae->tral = raiz->tral;
             t_no* sae = raiz->sae;
             free(raiz->carga); // memory leak ??
             free(raiz);   
             return sae;
        }else if((raiz->sad != NULL) && (raiz->sae == NULL)){
            raiz->sad->tral = raiz->tral;
            t_no* sad = raiz->sad;
            free(raiz->carga); // memory leak!!??
            free(raiz);
            return sad;
        }else{
            t_no* cam = raiz->sae;
            while(cam->sad != NULL){
                cam = cam->sad;
            }
            __trocar(raiz, cam);
            raiz->sae = __remover_abb(raiz->sae, comparar, chave);
        }
    }
    return raiz;

}


void remover_abb(t_abb* abb, void* chave){

    abb->raiz = __remover_abb(abb->raiz, abb->comparar, chave);

    return;
}

// static void __podar_ab(t_no* raiz){
//     if (raiz == NULL){
//         return;
//     }
//     __podar_ab(raiz->sae);
//     __podar_ab(raiz->sad);
//     free(raiz->carga); // potencial memory leak
//     free(raiz);
//     return;
// }

// void podar_ab(t_ab* ab, void* chave){
//     t_no* raiz = __buscar_ab(ab->raiz,ab->comparar,chave);
//     if (raiz == NULL){ // não encontrou !
//         //
//         return; 
//     }else if (raiz->tral == NULL){ // toda árvore será podada!!
//         //
//         ab->raiz = NULL;
//     }else if (raiz->tral->sae == raiz){ // é descendente da esquerda?
//         raiz->tral->sae = NULL;
//     }else{                        // é descendente da direita?
//         raiz->tral->sad = NULL; 
//     }
//     ab->tamanho -= __tamanho_ab(raiz);
//     __podar_ab(raiz);
// }

// #define MAX(a,b) (a>b?a:b)
// static int __altura_ab(t_no* raiz){
//     if (raiz == NULL){
//         return -1;
//     }
//     return MAX(__altura_ab(raiz->sae), __altura_ab(raiz->sad))+1;
// }

// int altura_ab(t_ab *ab){
//     return __altura_ab(ab->raiz);
// }

// static int __tamanho_ab(t_no* raiz){
//     if (raiz == NULL){
//         return 0;
//     }
//     return (__tamanho_ab(raiz->sae)+__tamanho_ab(raiz->sad)+1) ;
// }

// int tamanho_ab(t_ab *ab){
//     return __tamanho_ab(ab->raiz);
// }


