typedef void(*t_imprimir_avl)(void* carga);
typedef int(*t_comparar_avl)(void* c1, void*c2);
typedef struct avl t_avl;
t_avl* criar_avl(t_imprimir_avl imprimir, t_comparar_avl comparar);
void inserir_avl(t_avl *avl, void* carga);
void imprimir_avl(t_avl *avl);
void* buscar_avl(t_avl* avl, void* chave);
