#include "stdio.h"
#include "stdlib.h"
#include "math.h"

//#include "ordena.h"

typedef int(*t_ordena_comparar)(void*, void*);

//void mostra_vetor(int* vetor[], int i, int j);

static void trocar(void* elems[], int i, int j){
    void* aux = elems[i];
    elems[i] = elems[j];
    elems[j] = aux;
}

static void desce_heap(void* elems[],int i, int ultima, t_ordena_comparar compara){
    // 2*i + 1
    // 2*i + 2
    int imaior = i;
    do{ 
        i = imaior;
        if (((2*i+1) <= ultima) && (compara(elems[i],elems[2*i+1])<0)){
            imaior = 2*i+1; 
        }
        if( ((2*i+2) <= ultima) && (compara(elems[imaior],elems[2*i+2])<0)){
            imaior = 2*i+2;
        }
        trocar(elems,i,imaior);
    } while( i!= imaior);

}

void construir_heap(void* elems[], int tamanho, t_ordena_comparar compara){
    int i = (int)floor ( (tamanho-1)/2 );
    while(i>=0){
        desce_heap(elems,i,tamanho-1,compara);
        i = i - 1;
    }
}



void heap_sort(void* elems[], int tamanho, t_ordena_comparar compara){
    construir_heap(elems,tamanho, compara);
    int ultima = tamanho-1;

    while(ultima >=1){
        trocar(elems,0,ultima);
        ultima = ultima-1;
        desce_heap(elems,0,ultima,compara);
    }
}

int particao(void* elems[], int lim_i, int lim_j, t_ordena_comparar compara ){
    int i_pivo = (lim_i + lim_j)/2;
    trocar(elems,i_pivo, lim_j);
    int i = lim_i;
    int j = lim_j - 1;
    do{
        while(compara(elems[i],elems[lim_j])<0){
            i++;
        }
        while((j>=0) && compara(elems[j],elems[lim_j])>0){
            j--;
        }
        if(i < j){
            trocar(elems,i,j);
        }

    }while(i<=j);

//    mostra_vetor(elems,lim_i,lim_j);
    
    trocar(elems,i,lim_j);
    
    return i;

}

static void qs(void* elems, int i, int j, t_ordena_comparar compara){
    if ((j-i) >= 1){
        int meio = particao(elems,i,j,compara);
    
        qs(elems,i,meio-1, compara);
        qs(elems,meio+1,j, compara);
    }

}

void quick_sort(void* elems[], int tamanho, t_ordena_comparar compara){
    qs(elems,0,tamanho-1,compara);
}

void intercalar(void* elems[], int lim_i, int meio, int lim_j, t_ordena_comparar compara){
    void* aux[lim_j-lim_i+1];
    int k = 0;
    int i=lim_i, j=meio+1;
    while((i<=meio) &&(j<=lim_j)){
        if (compara(elems[i],elems[j])<0){
            aux[k] = elems[i];
            i++;
        }else{
            aux[k] = elems[j];
            j++;
        }
        k++;
    }
    while(i<=meio){
        aux[k] = elems[i];
        i++;k++;
    }
    while(j<=lim_j){
        aux[k] = elems[j];
        j++;k++;
    }

    for(i=0;i<k;i++){
        elems[lim_i+i] = aux[i];
    }
}

void static ms(void* elems[], int i, int j, t_ordena_comparar compara){
    if ((j-i) >= 1){
        int meio = (i+j)/2;
        ms(elems,i,meio,compara);
        ms(elems,meio+1,j,compara);
        intercalar(elems, i, meio, j, compara);
    }
}

void merge_sort(void* elems[], int tamanho, t_ordena_comparar compara){
    ms(elems,0,tamanho-1,compara);
}


void mostra_vetor(int vetor[], int k, int tam){
    for(int i=k;i<tam;i++){
        printf("%d ", (vetor[i]) );
    }
    printf("\n");
}

int comparar_int(void* a, void *b){
    int* aa=a;
    int* bb=b;
    return (*aa - *bb);
}

void counting(int vetor[], int n, int k){
    int contagem[k+1]; // declara o vetor da contagem  (histograma)
    for(int i=0;i<=k;i++){ // inicialização
        contagem[i] = 0;
    }

    for(int i=0;i<n;i++){
        int j = vetor[i];
        contagem[j]++;
    }

    for(int i=1;i<=k;i++){
        contagem[i] = contagem[i] + contagem[i-1];
    }

    int aux[n], m=0;
    for(int i=n-1;i>=0;i--){
        
        int j = contagem[ vetor[i] ]-1;
        aux[j] = vetor[i];
        contagem[vetor[i]]--;
    }
    for(int i=0;i<n;i++){
        vetor[i] = aux[i];
    }


}

#define __pega_digito(x, i) (x/pow(10.0,i) - floor(x/pow(10.0,i)))*10

void radix_sort(int vetor[], int tam, int nro_digitos){
    int aux[tam];

    for (int d=1;d<=nro_digitos;d++){
        int contagem[]={0,0,0,0,0,0,0,0,0};

        for (int i=0;i<tam;i++){
            int dig = __pega_digito(vetor[i],d);
            contagem[dig]++;
            
        }
        for(int j=1;j<=9;j++){
            contagem[j] = contagem[j] + contagem[j-1];
        }

        for(int i=tam-1;i>=0;i--){
           int dig = __pega_digito(vetor[i],d);
           int k = contagem[dig]-1; // atenção
           aux[k] = vetor[i];
           contagem[dig]--;
        }

        for(int i=0;i<tam;i++){
            vetor[i] = aux[i];
        }
    }
}


int main(){
    int TAM = 10;
    // int vetor[TAM];
    // for(int i = 0;i<TAM;i++){
    //     vetor[i] = malloc(4);
    //     vetor[i] = rand() % 10;   
    // }
    
    int vetor[] = {17,21,17,13,32,10,14,11,20,19};  
    mostra_vetor(vetor,0, TAM);
//    merge_sort(vetor,TAM,comparar_int);
//    quick_sort(vetor,TAM,comparar_int);
//    heap_sort(vetor,TAM,comparar_int);
    
//    counting(vetor,TAM,10);
    radix_sort(vetor, TAM, 2);

    mostra_vetor(vetor,0, TAM);
}