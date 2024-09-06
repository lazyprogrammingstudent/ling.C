typedef void(*t_imprimir_abb)(void* carga);
typedef int(*t_comparar_abb)(void* c1, void*c2);
typedef struct abb t_abb;
t_abb* criar_abb(t_imprimir_abb imprimir, t_comparar_abb comparar);
void inserir_abb(t_abb *abb, void* carga);
void imprimir_abb(t_abb *abb);
void* buscar_abb(t_abb* abb, void* chave);
