#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct fruta {
  int codigo;
  char nome[30];
  int quantidade;
  float preco;
  struct fruta *next;
} Fruta;

Fruta *head = NULL;

void adicionar() {
  Fruta *f1 = (Fruta *)malloc(sizeof(Fruta));
  printf("Digite o código da fruta: ");
  scanf("%d", &f1->codigo);

  Fruta *temp = head;
  while (temp != NULL) {
    if (temp->codigo == f1->codigo) {
      printf("Código existente. Digite outro!\n");
      free(f1);
      return;
    }
    temp = temp->next;
  }

  printf("Digite o nome da fruta: ");
  scanf("%s", f1->nome);
  printf("Digite a quantidade de frutas: ");
  scanf("%d", &f1->quantidade);
  printf("Digite o preço da fruta: ");
  scanf("%f", &f1->preco);
  f1->next = head;
  head = f1;
  printf("Fruta cadastrada com sucesso!\n");
}

void listarFrutas() {
  Fruta *temp = head;
  while (temp != NULL) {
    printf("----------\nCódigo: %d \nNome: %s \nQuantidade: %d \nPreço: "
           "%.2f\n----------\n",
           temp->codigo, temp->nome, temp->quantidade, temp->preco);
    temp = temp->next;
  }
}

void buscar() {
  int codigo;
  printf("Digite o código da fruta: ");
  scanf("%d", &codigo);
  Fruta *temp = head;
  while (temp != NULL) {
    if (temp->codigo == codigo) {
      printf("Código: %d | Nome: %s | Quantidade: %d | Preço: %.2f\n",
             temp->codigo, temp->nome, temp->quantidade, temp->preco);
      return;
    }
    temp = temp->next;
  }
  printf("Fruta não encontrada!Tente de novo \n");
  Buscar();
}

void alterar() {
  int codigo;
  printf("Digite o código da fruta a ser alterada: ");
  scanf("%d", &codigo);
  Fruta *temp = head;
  while (temp != NULL) {
    if (temp->codigo == codigo) {
      printf("Digite o novo nome da fruta: ");
      scanf("%s", temp->nome);
      printf("Digite a nova quantidade de frutas: ");
      scanf("%d", &temp->quantidade);
      printf("Digite o novo preço da fruta: ");
      scanf("%f", &temp->preco);
      printf("Fruta alterada com sucesso!\n");
      return;
    }
    temp = temp->next;
  }
  printf("Fruta não encontrada! Tente novamente\n");
  alterar();
}

void excluir() {
  int codigo;
  printf("Digite o código da fruta a ser excluída: ");
  scanf("%d", &codigo);
  Fruta *temp = head;
  Fruta *prev = NULL;
  while (temp != NULL) {
    if (temp->codigo == codigo) {
      if (prev == NULL) {
        head = temp->next;
      } else {
        prev->next = temp->next;
      }
      free(temp);
      printf("Fruta excluída com sucesso!\n");
      return;
    }
    prev = temp;
    temp = temp->next;
  }
  printf("Fruta não encontrada!\n");
}



void vender() {
  int codigo_e, qty;
  FILE *file = fopen("vendas.txt", "a");
  printf("Digite o código da fruta a ser vendida: ");
  scanf("%d", &codigo_e);
  printf("Digite a quantidade a ser vendida: ");
  scanf("%d", &qty);
  Fruta *temp = head;
  while (temp != NULL) {
    if (temp->codigo == codigo_e) {
      if (temp->quantidade >= qty) {
        temp->quantidade -= qty;    
        if (file == NULL) {
          printf("Erro ao abrir arquivo de vendas!\n");
          return;
        }
        fprintf(file, "Código: %d | Quantidade: %d\n", codigo_e, qty);
        fclose(file);
        printf("Venda realizada com sucesso!\n");
      } else {
        printf("Quantidade insuficiente em estoque!\n");
      }
      return;
    }
    temp = temp->next;
  }
  printf("Fruta não encontrada!\n");
}

void imprimeMenu() {
  int e;
  do {
    printf("\n1. Cadastrar fruta\n2. Listar frutas\n3. Buscar fruta\n4. "
           "Alterar fruta\n5. Excluir fruta\n6. Vender fruta\n7. Sair\n");
    printf("Escolha uma opção: ");
    scanf("%d", &e);
    switch (e) {
    case 1:
      adicionar();
      break;
    case 2:
      listarFrutas();
      break;
    case 3:
      buscar();
      break;
    case 4:
      alterar();
      break;
    case 5:
      excluir();
      break;
    case 6:
      vender();
      break;
    case 7:
      printf("Saindo...\n");
      break;
    default:
      printf("Opção inválida!\n");
    }
  } while (e != 7);
}