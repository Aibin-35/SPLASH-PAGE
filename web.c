#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    char url[100];
    struct Node* prev;
    struct Node* next;
};

struct Node* current = NULL;

void freeForwardHistory(struct Node* node) {
    if (node == NULL) {
        return;
    }
    freeForwardHistory(node->next);
    free(node);
}

void visitNewPage(const char* url) {
    if (current != NULL && current->next != NULL) {
        freeForwardHistory(current->next);
    }

    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }
    strcpy(newNode->url, url);

    newNode->prev = current;
    newNode->next = NULL;

    if (current != NULL) {
        current->next = newNode;
    }

    current = newNode;
    printf("Visited: %s\n", current->url);
}

void goBack() {
    if (current == NULL || current->prev == NULL) {
        printf("Cannot go back.\n");
    } else {
        current = current->prev;
        printf("Moved back to: %s\n", current->url);
    }
}

void goForward() {
    if (current == NULL || current->next == NULL) {
        printf("Cannot go forward.\n");
    } else {
        current = current->next;
        printf("Moved forward to: %s\n", current->url);
    }
}

void displayCurrentPage() {
    if (current == NULL) {
        printf("No page visited yet.\n");
    } else {
        printf("Current Page: %s\n", current->url);
    }
}

void displayMenu() {
    printf("\n--- Browser Navigation Menu ---\n");
    printf("1. Visit New Page\n");
    printf("2. Go Back\n");
    printf("3. Go Forward\n");
    printf("4. Display Current Page\n");
    printf("5. Exit\n");
    printf("-----------------------------\n");
    printf("Enter your choice: ");
}

int main() {
    int choice;
    char url[100];

    while (1) {
        displayMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter URL to visit: ");
                scanf("%s", url);
                visitNewPage(url);
                break;
            case 2:
                goBack();
                break;
            case 3:
                goForward();
                break;
            case 4:
                displayCurrentPage();
                break;
            case 5:
                printf("Exiting Browser Simulation.\n");
                while(current != NULL && current->prev != NULL) {
                    current = current->prev;
                }
                freeForwardHistory(current);
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
