#include <iostream>
using namespace std;

#define MAX 5

struct Fila {
    int ini;
    int fim;
    float nos[MAX];
};

Fila* init() {
    Fila *f = new Fila;
    f->ini = 0;
    f->fim = 0;
    return f;
}

int isEmpty(Fila *f) {
    return (f->ini == f->fim);
}

int incrementa(int i) {
    return (i == MAX ? 0 : ++i);
}

int enqueue(Fila *f, float v) {
    int podeEnfileirar = (incrementa(f->fim) != f->ini);
    if (podeEnfileirar) {
        f->nos[f->fim] = v;
        f->fim = incrementa(f->fim);
    }
    return podeEnfileirar;
}

float dequeue(Fila *f) {
    float ret;
    if (isEmpty(f)) {
        ret = -1;
    } else {
        ret = f->nos[f->ini];
        f->ini = incrementa(f->ini);
    }
    return ret;
}

int count(Fila *f) {
    int qtde = 0;
    int i = f->ini;
    while (i != f->fim) {
        qtde++;
        i = incrementa(i);
    }
    return qtde;
}

void print(Fila *f) {
    int i = f->ini;
    cout << "- Qtde de elementos: " << count(f) << endl;
    while (i != f->fim) {
        cout << f->nos[i] << endl;
        i = incrementa(i);
    }
    cout << "---------------" << endl;
}

void freeFila(Fila * f) {
    delete f;
}

int main() {
    Fila* senhasGeradas = init();
    Fila* senhasAtendidas = init();
    int opcao;
    int senhaAtual = 1;

    do {
        cout << "Selecione uma opcao:" << endl;
        cout << "0. Sair" << endl;
        cout << "1. Gerar senha" << endl;
        cout << "2. Realizar atendimento" << endl;
        cout << "Senhas aguardando atendimento: " << count(senhasGeradas) << endl << endl;
        cin >> opcao;

        switch (opcao) {
            case 0:
                if (!isEmpty(senhasGeradas)) {
                    cout << "Ainda há senhas aguardando atendimento. Não é possível sair." << endl;
                    opcao = -1; // Mantém o loop ativo
                } else {
                    cout << "Quantidade de senhas atendidas: " << count(senhasAtendidas) << endl;
                }
                break;
            case 1:
                if (enqueue(senhasGeradas, senhaAtual)) {
                    cout << "Senha gerada: " << senhaAtual << endl;
                    senhaAtual++;
                } else {
                    cout << "Fila de senhas geradas está cheia. Não é possível gerar mais senhas." << endl;
                }
                break;
            case 2:
                if (!isEmpty(senhasGeradas)) {
                    float senhaAtendida = dequeue(senhasGeradas);
                    enqueue(senhasAtendidas, senhaAtendida);
                    cout << "Senha atendida: " << senhaAtendida << endl;
                } else {
                    cout << "Não há senhas para atender." << endl;
                }
                break;
            default:
                cout << "Opcao invalida. Tente novamente." << endl;
                break;
        }

    } while (opcao != 0);

    freeFila(senhasGeradas);
    freeFila(senhasAtendidas);
    return 0;
}
