#include <stdio.h>
#include <string.h>

//sistema interno para endereço
struct endereco {
    char rua [50];
    int numero;
    char cidade [50];
};

struct funcionario {
    int matricula;
    char nome [50];
    int idade;
    float salario;
    struct endereco endereco; };//struct dentro de struct};
    
    int main (){
        struct funcionario f1;
        //Entrada de dados
        printf ("=== cadastro de funcionario ===\n");
        printf ("digite a matricula");
        scanf ("%d", &f1.matricula);
        
        
        getchar(); //limpa buffer do teclado
        
        printf("digite o nome completo.");
        fgets(f1.nome, 50, stdin);
        f1.nome[strcspn(f1.nome, "\n")] = 0; //remove \n
        printf("digite a idade");
        scanf("%d", &f1.idade);
        
        printf("digite o salario");
        scanf("%f", &f1.salario);
        
        getchar(); //limpar buffer
        
        printf("digite a rua");
        fgets(f1.endereco.rua, 50, stdin);
        f1.endereco.rua [strcspn(f1.endereco.rua, "\n")] = 0;
        
        printf("digite o numero");
        scanf("%d", &f1.endereco.numero);
        
        getchar(); //limpar buffer
        
        printf("digite a cidade");
        fgets(f1.endereco.cidade, 50, stdin);
        f1.endereco.cidade [strcspn(f1.endereco.cidade, "\n")] = 0;
        
        //saida  de dados
        
        printf("\n=== dados do funcionario cadastrado ===\n");
        printf("matricula: %d\n", f1.matricula);
        printf("nome: %s\n", f1.nome);
        printf("idade: %d\n", f1.idade);
        printf("salario: %.2f\n", f1.salario);
        printf("enedereco: %s, %d - %s\n", f1.endereco.rua,f1.endereco.numero,
        f1.endereco.cidade);
        
        return 0;
    }