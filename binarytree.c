#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct TreeNode {
    char data;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

typedef struct Stack {
    int top;
    TreeNode* items[100];
} Stack;

Stack* createStack() {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->top = -1;
    return stack;
}

void push(Stack* stack, TreeNode* item) {
    if (stack->top >= 99) return;
    stack->items[++stack->top] = item;
}

TreeNode* pop(Stack* stack) {
    if (stack->top < 0) return NULL;
    return stack->items[stack->top--];
}

TreeNode* createNode(char data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

int isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^');
}

TreeNode* buildExpressionTree(char* postfix) {
    Stack* stack = createStack();
    TreeNode *node, *node1, *node2;

    for (int i = 0; postfix[i] != '\0'; i++) {
        char symbol = postfix[i];

        if (isalnum(symbol)) {
            node = createNode(symbol);
            push(stack, node);
        } 
        else if (isOperator(symbol)) {
            node = createNode(symbol);

            node2 = pop(stack);
            node1 = pop(stack);

            node->right = node2;
            node->left = node1;

            push(stack, node);
        }
    }
    
    node = pop(stack);
    free(stack);
    return node;
}

void inorderTraversal(TreeNode* root) {
    if (root) {
        if (isOperator(root->data)) {
            printf("(");
        }
        inorderTraversal(root->left);
        printf("%c", root->data);
        inorderTraversal(root->right);
        if (isOperator(root->data)) {
            printf(")");
        }
    }
}

int main() {
    char postfix[100];

    printf("Enter a postfix expression: ");
    fgets(postfix, sizeof(postfix), stdin);
    
    postfix[strcspn(postfix, "\n")] = 0;

    printf("\nPostfix Expression Entered: %s\n", postfix);
    
    TreeNode* root = buildExpressionTree(postfix);
    
    printf("Resulting Infix Expression: ");
    inorderTraversal(root);
    printf("\n");

    return 0;
}
