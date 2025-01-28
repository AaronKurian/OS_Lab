#include <stdio.h>
#include <stdlib.h>

typedef struct Block 
{
    int blockSize;      // Size of the memory block
    int remainingSize;  // Remaining size of the block
    struct Block* next; // Pointer to the next block
} Block;

typedef struct Process 
{
    int processSize;    // Size of the process
} Process;

// Function to create a new block node
Block* createBlock(int blockSize) 
{
    Block* newBlock = (Block*)malloc(sizeof(Block));
    newBlock->blockSize = blockSize;
    newBlock->remainingSize = blockSize;
    newBlock->next = NULL;
    return newBlock;
}

// Function to allocate processes using First-Fit algorithm
void firstFit(Block* blockList, Process* processList, int blockSize, int processSize) 
{
    int allocation[processSize];
    for (int i = 0; i < processSize; i++) 
    {
        allocation[i] = -1;  // Initially mark all processes as unallocated
        Block* currentBlock = blockList;

        // Traverse the linked list to find the first block that can accommodate the process
        while (currentBlock != NULL) 
        {
            if (currentBlock->remainingSize >= processList[i].processSize) 
            {
                allocation[i] = currentBlock->blockSize; // Process allocated to this block
                currentBlock->remainingSize -= processList[i].processSize; // Reduce the block's remaining size
                break;
            }
            currentBlock = currentBlock->next; // Move to the next block
        }
    }

    // Print the results in a tabular format
    printf("\nFirst-Fit Allocation:\n");
    printf("-----------------------------------------------------------------\n");
    printf("| Process No. | Process Size | Block Size | Block Size Remaining |\n");
    printf("-----------------------------------------------------------------\n");

    // Print each process allocation in a tabular format
    for (int i = 0; i < processSize; i++) 
    {
        if (allocation[i] != -1) {
            printf("|     %d      |     %d      |     %d    |        %d           |\n", i + 1, processList[i].processSize, allocation[i], blockList->remainingSize);
        } 
        else 
        {
            printf("|     %d      |     %d      |    N/A   |        N/A          |\n", i + 1, processList[i].processSize);
        }
    }
    printf("-----------------------------------------------------------------\n");
}

int main() {
    int blockSize, processSize;

    // Input memory block details
    printf("Enter the number of memory blocks: ");
    scanf("%d", &blockSize);
    
    Block* blockList = NULL;
    Block* tempBlock = NULL;
    for (int i = 0; i < blockSize; i++) 
    {
        int blockMem;
        printf("Block %d size: ", i + 1);
        scanf("%d", &blockMem);

        // Create a new block and add it to the linked list
        Block* newBlock = createBlock(blockMem);
        if (blockList == NULL) 
        {
            blockList = newBlock; // First block becomes the head
        } 
        else 
        {
            tempBlock->next = newBlock; // Link the new block to the previous one
        }
        tempBlock = newBlock;
    }

    // Input process details
    printf("Enter the number of processes: ");
    scanf("%d", &processSize);

    Process processList[processSize];
    for (int i = 0; i < processSize; i++) 
    {
        printf("Process %d size: ", i + 1);
        scanf("%d", &processList[i].processSize);
    }

    // Perform the First-Fit allocation
    firstFit(blockList, processList, blockSize, processSize);

    return 0;
}

