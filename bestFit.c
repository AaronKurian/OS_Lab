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

// Function to allocate processes using Best-Fit algorithm
void bestFit(Block* blockList, Process* processList, int blockSize, int processSize) 
{
    int allocation[processSize];
    for (int i = 0; i < processSize; i++) 
    {
        allocation[i] = -1;  // Initially mark all processes as unallocated
        Block* currentBlock = blockList;
        Block* bestBlock = NULL;

        // Traverse the linked list to find the block with the best fit (smallest remaining size that fits)
        while (currentBlock != NULL) 
        {
            if (currentBlock->remainingSize >= processList[i].processSize) 
            {
                if (bestBlock == NULL || currentBlock->remainingSize < bestBlock->remainingSize) 
                {
                    bestBlock = currentBlock;
                }
            }
            currentBlock = currentBlock->next;
        }

        // Allocate the process to the best-fit block
        if (bestBlock != NULL) 
        {
            allocation[i] = bestBlock->blockSize;
            bestBlock->remainingSize -= processList[i].processSize;
        }
    }

    // Print the results in a tabular format
    printf("\nBest-Fit Allocation:\n");
    printf("---------------------------------------------------------------\n");
    printf("| Process No. | Process Size | Block Size | Block Size Remaining |\n");
    printf("---------------------------------------------------------------\n");

    // Print each process allocation in a tabular format
    for (int i = 0; i < processSize; i++) 
    {
        Block* currentBlock = blockList;
        int allocated = 0;

        while (currentBlock != NULL) 
        {
            // If block was allocated to process
            if (currentBlock->blockSize == allocation[i]) 
            {
                printf("|     %d      |     %d      |     %d    |        %d          |\n", i + 1, processList[i].processSize, currentBlock->blockSize, currentBlock->remainingSize);
                allocated = 1;
                break;
            }
            currentBlock = currentBlock->next;
        }

        if (allocated == 0) 
        {
            printf("|     %d      |     %d      |    N/A   |        N/A          |\n", i + 1, processList[i].processSize);
        }
    }
    printf("---------------------------------------------------------------\n");
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

    // Perform the Best-Fit allocation
    bestFit(blockList, processList, blockSize, processSize);

    return 0;
}

