#include <stdio.h>
#include <stdlib.h>

int num = 10;

struct data{
	
	int value;
	int color;
	data *parent; 
	data *left;  
	data *right;
}*root; 

data *newNode(int value){
	
	data *temp = (data*)malloc(sizeof(data));
	
	temp->value = value;
	temp->parent = NULL;
	temp->left = NULL;
	temp->right = NULL;
	temp->color = 1;
	return temp;
}

data *insert(data *curr, data *temp){
	
	if(!curr){
		return temp;
	}
	else{
		if(temp->value < curr->value){
			
			curr->left = insert(curr->left, temp);
			curr->left->parent = curr;
		}
		
		else if(temp->value > curr->value){
			
			curr->right = insert(curr->right, temp);
			curr->right->parent = curr;
		}
		return curr;
	}
}

void leftRotate(data *temp){
	
	data *tempRight = temp->right;
	temp->right = tempRight->left;
	
	if(temp->right){
		temp->right->parent = temp;
	}
	
	tempRight->parent = temp->parent;
	
	if(!temp->parent){
		root = tempRight;
	}
	
	else if(temp == temp->parent->left){
		temp->parent->left = tempRight;
	}
	
	else{
		temp->parent->right = tempRight;
	}
	
	tempRight->left = temp;
	temp->parent = tempRight;
} 

void rightRotate(data *temp){
	
	data *tempLeft = temp->left;
	temp->left = tempLeft->right;
	
	if(temp->left){
		temp->left->parent = temp;
	}
	
	tempLeft->parent = temp->parent;
	
	if(!temp->parent){
		root = tempLeft;
	}
	
	else if(temp == temp->parent->left){
		temp->parent->left = tempLeft;
	}
	
	else{
		temp->parent->right = tempLeft;
	}
	
	tempLeft->right = temp;
	temp->parent = tempLeft;
}

void balance (data *curr){
	
	while((curr != root) && ((!curr->color) && (curr->parent->color))){
		
		data *Parent = curr->parent;
		data *Grandparent = Parent->parent;
		
		if(Parent == Grandparent->left){
			
			data *Uncle = Grandparent->right;
			
			if(!Uncle && Uncle->color){
				Grandparent->color = 1;
				(Parent->color)--;
				(Uncle->color)--;
				curr = Grandparent;
			}
			
			else if(curr == Parent->right){
				leftRotate(Parent);
				curr = Parent;
				Parent = curr->parent;
			} 
			
			else{
				rightRotate(Grandparent);
				int temp = Parent->color;
				Parent->color = Grandparent->color;
				Grandparent->color = temp;
				curr = Parent;
			}
	}
	else {
		data *Uncle = Grandparent->left;
		
		if(!Uncle && Uncle->color){
			(Grandparent->color)++;
			(Parent->color)--;
			(Uncle->color)--;
			curr = Grandparent;
		}
		
		else if(curr = Parent->left){
			rightRotate(Parent);
			curr = Parent;
			Parent = curr->parent;
		}
		
		else{
			leftRotate(Grandparent);
			int temp = Parent->color;
			Parent->color = Grandparent->color;
			Grandparent->color = temp;
			curr = Parent;
		}
	}
} 
}

int count;
void Inorder(data *curr)
{
	if(curr){
	Inorder(curr->left);
		count++;
		
		if(count < num){
			
			printf("%d ", curr->value);
		}
		else
		{
			printf("%d\n", curr->value);
		}
		Inorder(curr->right);	
	}
}

int main(){
	
	int datas[num] = {41, 22, 5, 51, 48, 29, 18, 21, 45, 3};
	
	for(int i = 0; i < num; i++)
	{
		data *temp = newNode(datas[i]);
		
		root = insert (root, temp);
		
		balance(temp);
		root->color = 0;
	}
	
	count = 0;
	puts("Inorder Traversal of Created Tree");
	Inorder(root);
	
	return 0;
}
