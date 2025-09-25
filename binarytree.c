#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// Defines the structure for a node in the expression tree
typedef struct TreeNode {
    char data;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

// Defines the stack structure to hold TreeNode pointers
typedef struct Stack {
    int top;
    TreeNode* items[100]; // Stack of TreeNode pointers
} Stack;

// Creates and initializes a stack
Stack* createStack() {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->top = -1;
    return stack;
}

// Pushes a tree node onto the stack
void push(Stack* stack, TreeNode* item) {
    if (stack->top >= 99) return; // Stack overflow
    stack->items[++stack->top] = item;
}

// Pops a tree node from the stack
TreeNode* pop(Stack* stack) {
    if (stack->top < 0) return NULL; // Stack underflow
    return stack->items[stack->top--];
}

// Creates a new tree node
TreeNode* createNode(char data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Checks if a character is an operator
int isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^');
}

/**
 * Builds an expression tree from a given postfix expression.
 * @param postfix The null-terminated string containing the postfix expression.
 * @return A pointer to the root of the newly created expression tree.
 */
TreeNode* buildExpressionTree(char* postfix) {
    Stack* stack = createStack();
    TreeNode *node, *node1, *node2;

    // 1. Read the postfix expression from left to right
    for (int i = 0; postfix[i] != '\0'; i++) {
        char symbol = postfix[i];

        // 2. If the symbol is an operand, create a node and push it
        if (isalnum(symbol)) {
            node = createNode(symbol);
            push(stack, node);
        } 
        // 3. If the symbol is an operator
        else if (isOperator(symbol)) {
            // Create a node for the operator
            node = createNode(symbol);

            // Pop two operands from the stack
            node2 = pop(stack); // The first pop is the right child
            node1 = pop(stack); // The second pop is the left child

            // Set them as children of the operator node
            node->right = node2;
            node->left = node1;

            // Push the new subtree back to the stack
            push(stack, node);
        }
    }

    // 4. The final item on the stack is the root of the tree
    node = pop(stack);
    free(stack); // Free the stack memory
    return node;
}

// Performs an inorder traversal to display the infix expression
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

// Main function to drive the program
int main() {
    char postfix1[] = "ab+c*d-";
    printf("Postfix Expression: %s\n", postfix1);
    
    TreeNode* root1 = buildExpressionTree(postfix1);
    
    printf("Infix Expression (from tree): ");
    inorderTraversal(root1);
    printf("\n\n");

    char postfix2[] = "ABC*+D/";
    printf("Postfix Expression: %s\n", postfix2);

    TreeNode* root2 = buildExpressionTree(postfix2);

    printf("Infix Expression (from tree): ");
    inorderTraversal(root2);
    printf("\n");

    return 0;
}
