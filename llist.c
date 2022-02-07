#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include "llist.h"

int main (int argc, char *argv[]){
	if(argc <= 1){
		printf("Invalid Syntaxxx");
	}
	int pos = 0;
	char* parsed_arr[128];
	while (argv[pos] != NULL){
		parsed_arr[pos] = argv[pos];
		pos++;
	}
	parsed_arr[pos] = NULL;
	
	int pos2 = 1;
	struct node *head = NULL;

	while(parsed_arr[pos2] != NULL){
		if(strcmp(parsed_arr[pos2],"ih")==0){
			if(atoi(parsed_arr[pos2+1])==0){
				printf("Invalid linked list command: ih [insert number]\n");
				exit(0);
			}else{
				int value = atoi(parsed_arr[pos2+1]);
				struct node *temp = node_alloc(value);
				llist_insert_head(&head, temp);
				pos2+=1;
			}
		}else if(strcmp(parsed_arr[pos2],"it")==0){
			if(atoi(parsed_arr[pos2+1])==0){
				printf("Invalid linked list command: it [insert number]\n");
				exit(0);
			}else{
				int value = atoi(parsed_arr[pos2+1]);
				struct node* temp = node_alloc(value);
				llist_insert_tail(&head, temp);
				pos2+=1;
			}
			
		}else if(strcmp(parsed_arr[pos2],"dh")==0){
			llist_delete_head(&head);
			pos2+=1;
		}else if(strcmp(parsed_arr[pos2],"p")==0){
			llist_print(head);
			pos2+=1;
		}else if(strcmp(parsed_arr[pos2],"f")==0){
			llist_free(&head);
			pos2+=1;
		}else{
			pos2+=1;
		}
	}
}

void llist_insert_head(struct node **head, struct node *n){
	if (*head == NULL){
		*head = n;
	}else{
		struct node* temp = *head;
		*head = n;
		(*head)->next = temp;

	}
}

struct node *llist_delete_head(struct node **head){
	if(*head == NULL){
		return NULL;
	}else{
		struct node* temp = *head;
		*head = (*head)->next;
		return temp;
	}
}

void llist_insert_tail(struct node **head, struct node *n){
	if (*head == NULL){
		*head = n;
	}else{
		struct node* temp = *head;
		while(temp->next != NULL){
			temp = temp->next;
		}
		temp->next = n;

	}
}

void llist_print(struct node *head){
	if(head == NULL){
		printf("[empty]\n");
	}else{
		struct node* temp = head;
		while (temp->next != NULL){
			printf("%d -> ", temp->value);
			temp = temp->next;
		}
		printf("%d\n", temp->value);
	}
}

void llist_free(struct node **head){
	if(*head != NULL){
		struct node* temp = *head;
		struct node* temp_free = NULL;
		while(temp->next != NULL){
			temp_free = temp;
			temp = temp->next;
			node_free(temp_free);
		}
		node_free(*head);
		head = NULL;
	}
}

struct node *node_alloc(int value){
	struct node* temp = (struct node*)malloc(sizeof(struct node));
	temp->value = value;
	temp->next = NULL;
	return temp;
}

void node_free(struct node *n){
	free(n);
}