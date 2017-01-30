#include <stdio.h>	
#include "tree.h"
#include <string.h>
#include <stdlib.h>

void Insert(char *str){
	extern tree *root;
	tree *ptr;
	if(root == NULL){
		root = (tree *) malloc(sizeof(tree));
		strcpy(root->word, str);
		root->b4 = root->after = NULL;
		return ;
	}
	ptr = root;
	while(1){
		if(strcmp(str, ptr->word) < 0){
			if(ptr->b4 != NULL){
				ptr = ptr->b4;
				continue;
			}
			else{
				ptr->b4 = (tree *) malloc(sizeof(tree));
				ptr = ptr->b4;
				strcpy(ptr->word, str);
				ptr->b4 = ptr->after = NULL;
				return ;
			}
		}
		else if(strcmp(str, ptr->word) > 0){
			if(ptr->after != NULL){
				ptr = ptr->after;
				continue;
			}
			else{
				ptr->after = (tree *) malloc(sizeof(tree));
				ptr = ptr->after;
				strcpy(ptr->word, str);
				ptr->b4 = ptr->after = NULL;
				return ;
			}
		}
		else if(strcmp(str, ptr->word) == 0)
				return ;
	}
	return ;
}

void delete_node(tree *ptr, int dir){
	extern tree *root;
	tree *ptr1, *ptr2;
	if(dir == 0){
		ptr1 = ptr->b4;
		if(ptr1->b4 == NULL && ptr1->after == NULL){
			free(ptr1);
			ptr->b4 = NULL;
			return ;
		}
		if(ptr1->b4 == NULL){
			ptr->b4 = ptr1->after;
			free(ptr1);
			return ;
		}
		if(ptr1->after == NULL){
			ptr->b4 = ptr1->b4;
			free(ptr1);
			return ;
		}
		if(ptr1->b4 && ptr1->after){
			if(ptr1->after->b4 == NULL){
				ptr1->after->b4 = ptr1->b4;
				ptr->b4 = ptr1->after;
				return ;
			}
			ptr2 = ptr1->after;
			while(ptr2->b4->b4)
				ptr2 = ptr2->b4;
			strcpy(ptr1->word, ptr2->b4->word);
			delete_node(ptr2, 0);
			return ;
		}
	}
	if(dir == 1){
		ptr1 = ptr->after;
		if(ptr1->b4 == NULL && ptr1->after == NULL){
			free(ptr1);
			ptr->after = NULL;
			return ;
		}
		if(ptr1->b4 == NULL){
			ptr->after = ptr1->after;
			free(ptr1);
			return ;
		}
		if(ptr1->after == NULL){
			ptr->after = ptr1->b4;
			free(ptr1);
			return ;
		}
		if(ptr1->b4 && ptr1->after){
			if(ptr1->after->b4 == NULL){
				ptr1->after->b4 = ptr1->b4;
				ptr->after = ptr1->after;
				return ;
			}
			ptr2 = ptr1->after;
			while(ptr2->b4->b4)
				ptr2 = ptr2->b4;
			strcpy(ptr1->word, ptr2->b4->word);
			delete_node(ptr2, 0);
			return ;
		}
	}
}

void Delete(char *str){
	extern tree *root;
	tree *ptr, temp, *ptr1;
	strcpy(temp.word, "0\0");
	temp.b4 = NULL;
	temp.after = root;
	ptr = &temp;
	while(strcmp(str, ptr->word) != 0){
		if(strcmp(str, ptr->word) > 0 && ptr->after == NULL)
			break;
		if(strcmp(str, ptr->word) > 0 && strcmp(ptr->after->word, str) != 0){
			ptr = ptr->after;
			continue;
		}
		if(strcmp(str, ptr->word) > 0 && strcmp(ptr->after->word, str) == 0){
			delete_node(ptr, 1);
			break; 
		}
		if(strcmp(str, ptr->word) < 0 && ptr->b4 == NULL)
			break;
		if(strcmp(str, ptr->word) < 0 && strcmp(ptr->b4->word, str) != 0){
			ptr = ptr->b4;
			continue;
		}
		if(strcmp(str, ptr->word) < 0 && strcmp(ptr->b4->word, str) == 0){
			delete_node(ptr, 0);
			break; 
		}
	}
	root = temp.after;
	return ;
}
