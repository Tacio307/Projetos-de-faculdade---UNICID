#include <stdio.h>
#include <string.h>
#include <ctype.h>

void gerarFibonacciMod26(int fibmod[], int n) {
    if (n <= 0) return;
    if (n == 1) { fibmod[0] = 1 % 26; return; }

    int a = 1, b = 1;
    fibmod[0] = a % 26;
    fibmod[1] = b % 26;
    for (int i = 2; i < n; i++) {
        int c = a + b;
        fibmod[i] = c % 26;   // só precisamos do %26
        a = b;
        b = c;
    }
}

int contarLetras(const char texto[]) {
    int count = 0;
    for (int i = 0; texto[i] != '\0'; i++)
        if (isalpha((unsigned char) texto[i]))
            count++;
    return count;
}

void criptografar(char texto[], int fibmod[]) {
    int pos = 0;
    for (int i = 0; texto[i] != '\0'; i++) {
        unsigned char ch = (unsigned char) texto[i];
        if (isalpha(ch)) {
            char base = isupper(ch) ? 'A' : 'a';
            int offset = fibmod[pos] % 26;
            texto[i] = (char)(( (ch - base + offset) % 26 ) + base);
            pos++;
        }
    }
}

void decriptografar(char texto[], int fibmod[]) {
    int pos = 0;
    for (int i = 0; texto[i] != '\0'; i++) {
        unsigned char ch = (unsigned char) texto[i];
        if (isalpha(ch)) {
            char base = isupper(ch) ? 'A' : 'a';
            int offset = fibmod[pos] % 26;
            texto[i] = (char)(( (ch - base - offset + 26) % 26 ) + base);
            pos++;
        }
    }
}

int main() {
    char texto[256];
    int fibmod[256];

    printf("Digite o texto: ");
    if (!fgets(texto, sizeof(texto), stdin)) return 0;
    texto[strcspn(texto, "\n")] = '\0';

    int letras = contarLetras(texto);
    if (letras == 0) {
        printf("Nenhuma letra encontrada.\n");
        return 0;
    }

    gerarFibonacciMod26(fibmod, letras);


    criptografar(texto, fibmod);
    printf("Texto criptografado: %s\n", texto);

    decriptografar(texto, fibmod);
    printf("Texto decriptografado: %s\n", texto);

    return 0;
}
