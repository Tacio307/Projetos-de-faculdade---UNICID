Este projeto em linguagem C é um exemplo prático de como utilizar **estruturas de dados** para organizar informações de forma eficiente. Em sua essência, o código simula um pequeno sistema de cadastro que permite armazenar e exibir dados de um funcionário, incluindo sua matrícula, nome, idade, salário e, de forma notável, seu endereço completo.

A funcionalidade do programa é baseada no uso de `structs`,(abreviação de estrutura) que agem como modelos para agrupar diferentes tipos de dados sob um único nome. O exemplo é particularmente interessante por demonstrar o conceito de **struct aninhada**, onde a `struct funcionario` contém outra `struct` chamada `endereco`. Essa abordagem é fundamental para modelar relações complexas e claras do mundo real, como a de um funcionário que "possui" um endereço.

Durante a execução, o programa interage com o usuário, solicitando cada dado do funcionário e do seu endereço. Ele gerencia a entrada de informações de texto e números de forma cuidadosa, garantindo que os dados sejam lidos corretamente. Ao final, todos os dados coletados são exibidos de maneira organizada, mostrando como as informações, antes isoladas, foram unidas em uma única representação lógica e coesa. Este código serve como uma excelente introdução à gestão de dados estruturados em C, sendo um ponto de partida valioso para o desenvolvimento de aplicações mais complexas.

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