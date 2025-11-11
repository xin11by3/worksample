#include "LinkedList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

void insert_word(Node **head, const char *word){
  Node *curr = *head;
  while (curr != NULL){
    if(strcmp(curr->word, word)==0){
      curr->freq++;
      return;
    }
    curr = curr->next;
  }

  Node *new_node =(Node *)malloc(sizeof(Node));
  if(!new_node){
    perror("malloc failed");
    exit(1);
  }

  new_node->word = strdup(word);
  new_node->freq = 1;
  new_node->next = *head;
  *head = new_node;
}

Node *make_linkedlist(const char *filename){
  FILE *fp = fopen(filename, "r");
  if(!fp){
    perror("open file failed");
    return NULL;
  }

  char buf[256];
  Node *head = NULL;

  while(fgets(buf,sizeof(buf),fp)){
    buf[strcspn(buf,"\r\n")] = '\0';
    if(buf[0] == '\0') continue;
    insert_word(&head, buf);
  }

  fclose(fp);
  return head;
}

//find the word

Node *length_search(Node **head, int length){
  if(length <= 0){
    return NULL;
  }
  Node *list = NULL;
  Node *curr = *head;
  while(curr != NULL){
    if((int)strlen(curr->word) == length){
      Node *new_node = (Node *)malloc(sizeof(Node));
      new_node->word = strdup(curr->word);
      new_node->freq = curr->freq;
      new_node->next = list;
      list = new_node;
    }
    curr = curr->next;
  }
  return list;
}

Node *compare(Node *a, Node *b){
  if(a->freq > b->freq) return a;
  if(a->freq < b->freq) return b;
  if(strcmp(a->word, b->word) <= 0) return a;
  return b;
}

void splitList(Node *head, Node **front, Node **back){
  if(head == NULL || head->next == NULL){
    *front = head;
    *back = NULL;
    return;
  }
  Node *slow = head;
  Node *fast = head->next;
  while(fast != NULL && fast->next != NULL){
      slow = slow->next;
      fast = fast->next->next;
  }

  *front = head;
  *back = slow->next;
  slow->next = NULL;
}
Node *merge(Node *a, Node *b){
  if(a == NULL) return b;
  if(b == NULL) return a;
  Node *result = NULL;
  if(a->freq > b->freq || (a->freq == b->freq && strcmp(a->word, b->word) < 0)){
    result = a;
    result->next = merge(a->next, b);
  }
  else{
    result = b;
    result->next = merge(a, b->next);
  }
  return result;
}
Node *mergeSort(Node *head){
  if(head == NULL || head->next == NULL) return head;
  Node *a;
  Node *b;
  splitList(head, &a, &b);
  a = mergeSort(a);
  b = mergeSort(b);

  return merge(a, b);
}
const char *get_by_rank(Node *head, int k){
  int idx = 0;
  Node *curr = head;
  while(curr != NULL){
    if (idx == k) return curr->word;
    curr = curr->next;
    idx++;
  }
  return "-";
}
void free_list(Node *head){
  Node *curr = head;
  while (curr != NULL){
    Node *temp = curr;
    curr = curr->next;
    free(temp->word);
    free(temp);
  }
}
