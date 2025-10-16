#include <stdio.h>
#include <math.h>  // Para usar sqrt()

int main() {
    float num1, num2, resultado;
    int opcao;

    // Entrada de dados
    printf("Digite o primeiro numero: ");
    scanf("%f", &num1);
    printf("Digite o segundo numero: ");
    scanf("%f", &num2);

    // Menu de operações
    printf("\nEscolha uma operacao:\n");
    printf("1 - Adicao\n");                            //Soma de +
    printf("2 - Subtracao\n");                         //Soma de -
    printf("3 - Multiplicacao\n");                     //Soma de x
    printf("4 - Divisao\n");                           //Soma de ÷
    printf("5 - Porcentagem\n");                       //Soma de %
    printf("6 - Raiz quadrada do primeiro numero digitado\n");  //Soma de √
    //Para a soma da raiz quadrada "√" , so vai ser somado o primeiro numero pedido que for digitado

    // Escolha do usuário
    printf("Escolha uma operacao (1-6): ");
    scanf("%d", &opcao);

    // Estrutura switch/case
    switch (opcao) {
        case 1:
            resultado = num1 + num2;
            printf("\nResultado: %.2f + %.2f = %.2f\n", num1, num2, resultado);
            break;
        case 2:
            resultado = num1 - num2;
            printf("\nResultado: %.2f - %.2f = %.2f\n", num1, num2, resultado);
            break;
        case 3:
            resultado = num1 * num2;
            printf("\nResultado: %.2f * %.2f = %.2f\n", num1, num2, resultado);
            break;
        case 4:
            if (num2 != 0) {
                resultado = num1 / num2;
                printf("\nResultado: %.2f / %.2f = %.2f\n", num1, num2, resultado);
            } else {
                printf("\nErro: divisao por zero nao e permitida.\n");
            }
            break;
        case 5:
            resultado = (num1 / 100) * num2;
            printf("\nResultado: %.2f%% de %.2f = %.2f\n", num1, num2, resultado);
            break;
        case 6:
            if (num1 >= 0) {
                resultado = sqrt(num1);
                printf("\nResultado: raiz quadrada de %.2f = %.2f\n", num1, resultado);
            } else {
                printf("\nErro: nao existe raiz quadrada real de numero negativo.\n");
            }
            break;
        default:
            printf("Opcao invalida.\n");
    }

    return 0;
}
