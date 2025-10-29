#include <stdio.h>
#include <stdlib.h>

typedef struct Block {
    size_t size;
    int free;
    struct Block* next;
    struct Block* prev;
    void* ptr;
} Block;

Block* head = NULL;

Block* create_block(size_t size) {
    Block* block = (Block*)malloc(sizeof(Block));
    block->size = size;
    block->free = 0;
    block->next = NULL;
    block->prev = NULL;
    block->ptr = malloc(size);
    return block;
}

void add_block(Block* block) {
    if (!head) {
        head = block;
    } else {
        Block* current = head;
        while (current->next) {
            current = current->next;
        }
        current->next = block;
        block->prev = current;
    }
}

void* my_malloc(size_t size) {
    Block* current = head;
    while (current) {
        if (current->free && current->size >= size) {
            current->free = 0;
            return current->ptr;
        }
        current = current->next;
    }
    Block* new_block = create_block(size);
    add_block(new_block);
    return new_block->ptr;
}

void my_free(void* ptr) {
    Block* current = head;
    while (current) {
        if (current->ptr == ptr) {
            current->free = 1;
            return;
        }
        current = current->next;
    }
    printf("Pointer not found.\n");
}

void garbage_collect() {
    Block* current = head;
    while (current) {
        Block* next = current->next;
        if (current->free) {
            free(current->ptr);
            if (current->prev)
                current->prev->next = current->next;
            if (current->next)
                current->next->prev = current->prev;
            if (current == head)
                head = current->next;
            free(current);
        }
        current = next;
    }
}

void print_blocks() {
    Block* current = head;
    printf("\nMemory Blocks:\n");
    int i = 1;
    while (current) {
        printf("%d. Address: %p, Size: %zu, Free: %s\n", i, current->ptr, current->size, current->free ? "Yes" : "No");
        current = current->next;
        i++;
    }
    printf("\n");
}

void* get_pointer_by_index(int index) {
    Block* current = head;
    int i = 1;
    while (current) {
        if (i == index) {
            return current->ptr;
        }
        current = current->next;
        i++;
    }
    return NULL;
}

int main() {
    int choice;
    size_t size;
    int index;
    void* ptr;

    while (1) {
        printf("1. Allocate memory\n");
        printf("2. Free memory\n");
        printf("3. Garbage collect\n");
        printf("4. Show memory blocks\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter size to allocate: ");
                scanf("%zu", &size);
                ptr = my_malloc(size);
                printf("Memory allocated at %p\n", ptr);
                break;

            case 2:
                print_blocks();
                printf("Enter block number to free: ");
                scanf("%d", &index);
                ptr = get_pointer_by_index(index);
                if (ptr) {
                    my_free(ptr);
                    printf("Memory block %d freed.\n", index);
                } else {
                    printf("Invalid block number.\n");
                }
                break;

            case 3:
                garbage_collect();
                printf("Garbage collection complete.\n");
                break;

            case 4:
                print_blocks();
                break;

            case 5:
                printf("Exiting...\n");
                return 0;

            default:
                printf("Invalid choice, try again.\n");
        }
    }
    return 0;
}

