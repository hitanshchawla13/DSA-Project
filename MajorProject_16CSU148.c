//
//  main.c
//  MajorProject_16csu148
//
//  Created by Hitansh Chawla
//  Copyright © 1939 Saka Hitansh Chawla. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#define MAX 50


struct Node
{
    char data;
    
    unsigned isEndOfString: 1;
    
    struct Node *left, *eq, *right;
};


struct Node* newNode(char data)
{
    struct Node* temp = (struct Node*) malloc(sizeof( struct Node ));
    temp->data = data;
    temp->isEndOfString = 0;
    temp->left = temp->eq = temp->right = NULL;
    return temp;
}


void insert(struct Node** root, char *word)
{
    if (!(*root))
        *root = newNode(*word);
    
    if ((*word) < (*root)->data)
        insert(&( (*root)->left ), word);
    
    
    else if ((*word) > (*root)->data)
        insert(&( (*root)->right ), word);
    
    
    else
    {
        if (*(word+1))
            insert(&( (*root)->eq ), word+1);
        
        
        else
            (*root)->isEndOfString = 1;
    }
}


void traverseTSTUtil(struct Node* root, char* buffer, int depth)
{
    if (root)
    {
        traverseTSTUtil(root->left, buffer, depth);
        
        
        buffer[depth] = root->data;
        if (root->isEndOfString)
        {
            buffer[depth+1] = '\0';
            printf( "%s\n", buffer);
        }
        
        
        traverseTSTUtil(root->eq, buffer, depth + 1);
        
        
        traverseTSTUtil(root->right, buffer, depth);
    }
}

void traverseTST(struct Node* root)
{
    char buffer[MAX];
    traverseTSTUtil(root, buffer, 0);
}


int searchTST(struct Node *root, char *word)
{
    if (!root)
        return 0;
    
    if (*word < (root)->data)
        return searchTST(root->left, word);
    
    else if (*word > (root)->data)
        return searchTST(root->right, word);
    
    else
    {
        if (*(word+1) == '\0')
            return root->isEndOfString;
        
        return searchTST(root->eq, word+1);
    }
}

int main()
{
    struct Node *root = NULL;
    
    insert(&root, "Hitansh");
    insert(&root, "hit");
    insert(&root, "hard");
    insert(&root, "beware");
    
    printf("Following is traversal of ternary search tree\n");
    traverseTST(root);
    
    printf("\nFollowing are search results for Hitansh, you and love respectively\n");
    searchTST(root, "Hitansh")? printf("Found\n"): printf("Not Found\n");
    searchTST(root, "you")?   printf("Found\n"): printf("Not Found\n");
    searchTST(root, "love")?  printf("Found\n"): printf("Not Found\n");
    
    return 0;
}
