#include "stdlib.h"
#include "stdio.h"
#include "time.h"
#include "avl.h"

typedef struct no t_no;
struct no{ //folha
    void* carga;
    t_no *sae;
    t_no *sad;
    t_no *tral;
};

t_no* criar_no(void* carga){ //cria folha 
    t_no* novo = malloc(sizeof(t_no));
    novo->sae = NULL;
    novo->sad = NULL;
    novo->tral = NULL;
    novo->carga = carga;
    return novo;
}

struct avl{  //arvore
    t_no *raiz;
    int tamanho;
    t_imprimir_avl imprimir;
    t_comparar_avl comparar;
};

t_avl* criar_avl(t_imprimir_avl imprimir, t_comparar_avl comparar){
    t_avl *avl = malloc(sizeof(t_avl));
    avl->comparar = comparar;
    avl->imprimir = imprimir;
    avl->raiz = NULL;
    avl->tamanho = 0;

    return avl;
}

#define MAX(a,b) (a>b?a:b) //vai retornar o maior

static int __altura_avl(t_no* raiz){ //calcula o valor para cada raiz
    if (raiz == NULL){
        return -1;
    }
    return MAX(__altura_avl(raiz->sae), __altura_avl(raiz->sad))+1;
}

int altura_avl(t_avl *avl){ //retorna a altura da arvore inteira
    return __altura_avl(avl->raiz);
}

static t_no* __RSE(t_no* A, t_no* B){
    A->sad = B->sae;
    B->sae = A;
    // falta atualizar ancestral
    return B;
}

static t_no* __RSD(t_no* A, t_no* B){
    A->sae = B->sad;
    B->sad = A;
    // falta atualizar ancestral
    return B;
}

static int __calcular_fb(t_no* raiz){
    return __altura_avl(raiz->sad) - __altura_avl(raiz->sae);
}

static t_no* __inserir_avl(t_no* raiz, t_no* tral, t_no* novo, t_comparar_avl comparar){
    if (raiz == NULL){
        novo->tral = tral;
        return novo;
    }
    if (comparar(novo->carga, raiz->carga) < 0){ // sae
        raiz->sae = __inserir_avl(raiz->sae, raiz, novo, comparar);

        int fb = __calcular_fb(raiz);
        if(fb == -2){ // Peso SAE
            fb =  __calcular_fb(raiz->sae);
            if (fb == -1) { //RSD
                printf("RSD\n");
                raiz = __RSD(raiz, raiz->sae);
            } else { // RDE
                printf("RDE\n");
              t_no* aux = raiz->sae->sad;
              __RSE(raiz->sae, aux);
              raiz = __RSD(raiz, aux);  
            }
        }
    }else{ //sad
        raiz->sad = __inserir_avl(raiz->sad, raiz, novo, comparar);
        // Falta a operação.
        int fb = __calcular_fb(raiz);
        if (fb == +2){
            fb = __calcular_fb(raiz->sad);
            if (fb == +1){
                printf("RSE\n");
                raiz = __RSE(raiz, raiz->sad);
            }else{
                printf("RDD\n");
                t_no* aux = raiz->sad->sae;
                __RSD(raiz->sad, aux);
                raiz = __RSE(raiz, aux);
            }
        }
    }
    return raiz;
}

void inserir_avl(t_avl *avl, void* carga){
    t_no* novo = criar_no(carga);
    avl->raiz = __inserir_avl(avl->raiz, NULL, novo, avl->comparar);
}

static void __imprimir_avl(t_no* raiz, t_imprimir_avl imprimir){
    if(raiz == NULL)
        return;

    __imprimir_avl(raiz->sae, imprimir);
    imprimir(raiz->carga);
    __imprimir_avl(raiz->sad, imprimir);
}

void imprimir_avl(t_avl* avl){
    __imprimir_avl(avl->raiz, avl->imprimir);
}

t_no* __buscar_avl(t_no* raiz, t_comparar_avl comparar, void* chave ){
    if (raiz == NULL){
        return NULL;
    }else if (comparar(raiz->carga, chave) == 0){
        return raiz;
    }else if (comparar(raiz->carga, chave) > 0) {
         raiz = __buscar_avl(raiz->sae, comparar, chave);
    }else{
         raiz = __buscar_avl(raiz->sad, comparar, chave);
    }
    return raiz;
}

void* buscar_avl(t_avl* avl, void* chave){
    t_no* raiz = __buscar_avl(avl->raiz, avl->comparar, chave);
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

static void* __remover_avl(t_no* raiz, t_comparar_avl comparar, void* chave){
    if (raiz == NULL){
        return NULL;
    }else if (comparar(raiz->carga, chave) > 0) {
         raiz->sae = __remover_avl(raiz->sae, comparar, chave);
         // tratar FB

    }else if (comparar(raiz->carga, chave) < 0) {
         raiz->sad = __remover_avl(raiz->sad, comparar, chave);
         // tratar FB
         
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
            raiz->sae = __remover_avl(raiz->sae, comparar, chave);
        }
    }
    return raiz;

}


void remover_avl(t_avl* avl, void* chave){

    avl->raiz = __remover_avl(avl->raiz, avl->comparar, chave);

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


// static int __tamanho_ab(t_no* raiz){
//     if (raiz == NULL){
//         return 0;
//     }
//     return (__tamanho_ab(raiz->sae)+__tamanho_ab(raiz->sad)+1) ;
// }

// int tamanho_ab(t_ab *ab){
//     return __tamanho_ab(ab->raiz);
// }


