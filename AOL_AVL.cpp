#include <stdio.h>
#include <stdlib.h> 

int num;
int count;

struct data{
	int value; 
	int height;
	data *left; 
	data *right;
}*root;

data *newNode(int value){
	
	data *temp = (data*)malloc(sizeof(data));
	
	temp->value = value;
	temp->left = NULL;
	temp->right = NULL;
	temp->height = 1;
	return temp;
}

int max(int a, int b){
	
	if(a >= b){
		return a;
	}
	
	else{
		return b;
	}
}

int height(data *curr){
	
	if(!curr){
		return 0;
	}
	
	else{
		return (1 + max(height(curr->left), height(curr->right)));
	}
}

int balance(data *curr){

	if(!curr){
		return 0;
	}
	
	else{
		return (height(curr->left) - height(curr->right));
	}
}

data *rightRotate(data *curr){
	
	data *leftChild = curr->left;
	data *leftChildRight = leftChild->right;
	
	leftChild->right = curr;
	curr->left = leftChildRight;
	
	leftChild->height = height(leftChild);
	curr->height = height(curr);
	
	return leftChild;
}

data *leftRotate(data *curr){
	
	data *rightChild = curr->right;
	data *rightChildLeft = rightChild->left;
	
	rightChild->left = curr;
	curr->right = rightChildLeft;
	
	rightChild->height = height(rightChild);
	curr->height = height(curr);
	
	return rightChild;
}

data *rebalancing(data *curr){
	
	curr->height = height(curr);
	int rebalance = balance(curr);
	
	if(rebalance > 1){
		
		if(balance(curr->left) >= 0){
			return rightRotate(curr);
		}
		
		else{
			curr->left = leftRotate(curr->left);
			return rightRotate(curr);
		}
	}
	
	else if(rebalance < -1){
		if(balance(curr->right) <= 0){
			return leftRotate(curr);
		}
		
		else{
			curr->right = rightRotate(curr->right);
			return leftRotate(curr);
		}
	}
	
	else{
		return curr;
	}
} 

data *Insert(data *curr, data *temp){
	
	if(!curr){
		num++;
		return temp;
	}
	
	else{
		if(curr->value > temp->value){
			curr->left = Insert(curr->left, temp);
		}
		
		else if(curr->value < temp->value){
			curr->right = Insert(curr->right, temp);
		}
		
		return rebalancing(curr);
	}
}

int countdel;
data *Delete (data *curr, int key){
	
		if(!curr){
		puts("Data not found");
		return curr;
	}
	
	else if(curr->value > key){
		curr->left = Delete(curr->left, key);
	}
	
	else if(curr->value < key){
		curr->right = Delete(curr->right, key);
	}
	
	else{
		
		if(!curr->left || !curr->right){
			data *temp;
			if(curr->left){
				temp = curr->left;
			}
			
			else{
				temp = curr->right;
			}
			
			if(!temp){
				temp = curr;
				curr = NULL;
			}
			
			else{
				*curr = *temp;
			}
			
			free(temp);
		}
		else{
			data *temp = curr->left;
			
			while(temp->right){
				temp = temp->right;
			}
			
			curr->value = temp->value;
			curr->left = Delete(curr->left, temp->value);
		}
		countdel++;
		
		if(countdel == 1){
			num--;
		
			puts("Data Found");
		}
		
		if(!curr){
			return NULL;
		}
		
		else{
			return rebalancing(curr);
		}
	}
} 

void Preorder(data *curr){
	
	if(curr){
		count++;
		if(count < num){
			printf("%d ", curr->value);
		}
		else
		{
			printf("%d", curr->value);
		}
		Preorder(curr->left);
		Preorder(curr->right);
	}
		
} 

void Inorder(data *curr){
	if(curr){
		
		Inorder(curr->left);
		count++;
		
		if(count < num){
			
			printf("%d ", curr->value);
		}
		else
		{
			printf("%d", curr->value);
		}
		Inorder(curr->right);
	}
}

void Postorder(data *curr){
	
	if(curr){
		
		Postorder(curr->left);
		Postorder(curr->right);
		count++;
		
		if(count < num){
			printf("%d ", curr->value);
		}
		
		else{
			printf("%d", curr->value);
		}
	}
}

int main(){
	
	int menu=1;
	while(menu){
		int choose;
		puts("1. Insertion");
		puts("2. Deletion");
		puts("3. Traversal");
		puts("4. Exit");
		
		do{
			printf("Choose: ");
			scanf("%d", &choose);
			getchar();
		}while((menu < 1) || (menu > 4));
		
		switch(choose){
			
			case 1: {
				
				int Ins;
				printf("Insert: ");
				
				scanf("%d", &Ins);
				getchar();
				
				root = Insert(root, newNode(Ins));
				
				puts("");
				
				break;
			} 
			
			case 2:{
				
				int del;
				printf("Delete: ");
				
				scanf("%d", &del);
				getchar();
				
				countdel =0;
				root = Delete(root, del);
				
				if(countdel){
					printf("Value %d was deleted\n", del);
				}
				
				puts("");
				
				break;
			}
			
			case 3:{
				
				count = 0;
				printf("Preorder: ");
				Preorder(root);
				puts("");
				
				count = 0;
				printf("Inorder: ");
				Inorder(root);
				puts("");
				
				count = 0;
				printf("Postorder: ");
				Postorder(root);
				puts("\n");

				break;
			}
			
			case 4:{
				
				puts("Thank You");
				
				menu--;
				
				break;
			}
		}
	}
	
	return 0;
}
