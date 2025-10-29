#include <stdio.h>
#define TABLE_SIZE 10

int hashTable[TABLE_SIZE];
int deletedFlag = -2;  

void initTable() {
    for (int i = 0; i < TABLE_SIZE; i++)
        hashTable[i] = -1;
}

int hashFunction(int key) {
    return key % TABLE_SIZE;
}

void insert(int key) {
    int index = hashFunction(key);
    int originalIndex = index;

    while (hashTable[index] != -1 && hashTable[index] != deletedFlag) {
        index = (index + 1) % TABLE_SIZE;
        if (index == originalIndex) {
            printf("Hash table full, cannot insert %d\n", key);
            return;
        }
    }

    hashTable[index] = key;
    printf("Inserted %d at index %d\n", key, index);
}

int search(int key) {
    int index = hashFunction(key);
    int originalIndex = index;

    while (hashTable[index] != -1) {
        if (hashTable[index] == key)
            return index;
        index = (index + 1) % TABLE_SIZE;
        if (index == originalIndex)
            break;
    }
    return -1;
}

void delete(int key) {
    int index = search(key);
    if (index == -1) {
        printf("Key %d not found, cannot delete\n", key);
        return;
    }
    hashTable[index] = deletedFlag;
    printf("Key %d deleted from index %d\n", key, index);
}

void printTable() {
    printf("Hash Table:\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (hashTable[i] == -1)
            printf("%d: NULL\n", i);
        else if (hashTable[i] == deletedFlag)
            printf("%d: DELETED\n", i);
        else
            printf("%d: %d\n", i, hashTable[i]);
    }
}

int main() {
    int choice, key;

    initTable();

    while (1) {
        printf("\nChoose operation: 1-Insert, 2-Search, 3-Delete, 4-Print, 0-Exit\n");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter key to insert: ");
                scanf("%d", &key);
                insert(key);
                break;

            case 2: {
                printf("Enter key to search: ");
                scanf("%d", &key);
                int idx = search(key);
                if (idx != -1)
                    printf("Key %d found at index %d\n", key, idx);
                else
                    printf("Key %d not found\n", key);
                break;
            }

            case 3:
                printf("Enter key to delete: ");
                scanf("%d", &key);
                delete(key);
                break;

            case 4:
                printTable();
                break;

            case 0:
                return 0;

            default:
                printf("Invalid choice\n");
        }
    }
}
