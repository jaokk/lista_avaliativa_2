#include <stdio.h>
#include <string.h>

#define MAX_PROFESSORES 3
#define MAX_DISCIPLINAS 2
#define MAX_ESTUDANTES 15

typedef struct {
    char nome[50];
    int funcional;
    char titulacao[20];
} Professor;

typedef struct {
    char nome[50];
    int codigo;
    int carga_horaria;
    Professor professor_responsavel;
} Disciplina;

typedef struct {
    char nome[50];
    int matricula;
    int idade;
} Estudante;

void bubbleSort(Estudante estudantes[], int n) {
    int i, j;
    Estudante temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (estudantes[j].idade > estudantes[j + 1].idade) {
                temp = estudantes[j];
                estudantes[j] = estudantes[j + 1];
                estudantes[j + 1] = temp;
            }
        }
    }
}

int le_valida_idade() {
    int idade;
    printf("Digite a idade do estudante: ");
    scanf("%d", &idade);
    while (idade < 16 || idade > 26) {
        printf("Idade inválida! A idade deve estar entre 16 e 26. Digite novamente: ");
        scanf("%d", &idade);
    }
    return idade;
}

int main() {
    Professor professores[MAX_PROFESSORES];
    Disciplina disciplinas[MAX_DISCIPLINAS];
    Estudante estudantes[MAX_ESTUDANTES];


    printf("Cadastro de Professores:\n");
    for (int i = 0; i < MAX_PROFESSORES; i++) {
        printf("Professor %d:\n", i + 1);
        printf("Nome: ");
        scanf(" %[^\n]s", professores[i].nome);
        printf("Funcional: ");
        scanf("%d", &professores[i].funcional);
        printf("Titulação (especialista, mestre ou doutor): ");
        scanf(" %[^\n]s", professores[i].titulacao);
        printf("\n");
    }


    printf("Cadastro de Disciplinas:\n");
    for (int i = 0; i < MAX_DISCIPLINAS; i++) {
        printf("Materia %d:\n", i + 1);
        printf("Nome: ");
        scanf(" %[^\n]s", disciplinas[i].nome);
        printf("Código: ");
        scanf("%d", &disciplinas[i].codigo);
        printf("Carga Horária: ");
        scanf("%d", &disciplinas[i].carga_horaria);


        printf("Professor para essa materia:\n");
        for (int j = 0; j < MAX_PROFESSORES; j++) {
            printf("%d - %s\n", j + 1, professores[j].nome);
        }
        int opcao;
        printf("Escolha o ID do professor: ");
        scanf("%d", &opcao);
        disciplinas[i].professor_responsavel = professores[opcao - 1];

        printf("\n");
    }
  
    printf("Cadastro do estudantes:\n");
    int total_estudantes = 0;
    for (int i = 0; i < MAX_DISCIPLINAS; i++) {
        printf("Disciplina: %s\n", disciplinas[i].nome);
        int max_estudantes = 10; // Limite de 10 estudantes por disciplina
        if (total_estudantes + max_estudantes > MAX_ESTUDANTES) {
            max_estudantes = MAX_ESTUDANTES - total_estudantes;
        }
        printf("Numero maximo de estudantes: %d\n", max_estudantes);
        printf("Escreva o numero de estudantes que deseja cadastrar: ");
        int num_estudantes;
        scanf("%d", &num_estudantes);
        while (num_estudantes < 0 || num_estudantes > max_estudantes) {
            printf("Número inválido! Digite novamente: ");
            scanf("%d", &num_estudantes);
        }

        for (int j = 0; j < num_estudantes; j++) {
            printf("Estudante %d:\n", j + 1);
            printf("Nome: ");
            scanf(" %[^\n]s", estudantes[total_estudantes].nome);
            printf("Matrícula: ");
            scanf("%d", &estudantes[total_estudantes].matricula);
            estudantes[total_estudantes].idade = le_valida_idade();

            total_estudantes++;
        }

        printf("\n");
    }

    printf("Relatório dos alunos matriculados na primeira disciplina ordenados por idade:\n");
    printf("Código   Professor           Aluno              Idade\n");
    bubbleSort(estudantes, total_estudantes);
    for (int i = 0; i < total_estudantes; i++) {
        printf("%-8d %-20s %-18s %d\n", disciplinas[0].codigo, disciplinas[0].professor_responsavel.nome,
            estudantes[i].nome, estudantes[i].idade);
    }

    printf("\n");
  
    printf("Relatório dos alunos matriculados na segunda disciplina ordenados por idade (em ordem decrescente):\n");
    printf("Código   Professor           Aluno              Idade\n");
    bubbleSort(estudantes, total_estudantes);
    for (int i = total_estudantes - 1; i >= 0; i--) {
        printf("%-8d %-20s %-18s %d\n", disciplinas[1].codigo, disciplinas[1].professor_responsavel.nome,
            estudantes[i].nome, estudantes[i].idade);
    }

    return 0;
}
