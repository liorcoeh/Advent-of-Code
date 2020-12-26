#ifndef DAY_14_H
#define DAY_14_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "special_tree.h"

#define MASK_ARRAY_SIZE (500)
#define MASK_LENGTH (36)

#define MEM_ARRAY_SIZE (560)

typedef struct MEMORY_INFO
{
    int key;
    size_t value;
    int mask_index;
} Mem;

typedef struct ADRESS_AND_VALUE
{
    size_t address;
    size_t value;
} AND;

/***************************** GENERAL FUNCTIONS ******************************/

void GettingInfo(char* file_name, int masks[MASK_ARRAY_SIZE][MASK_LENGTH], 
                            Mem mem[]);

void PrintInfo(int masks[MASK_ARRAY_SIZE][MASK_LENGTH], Mem mem[]);

/**************************** PART ONE FUNCTIONS ******************************/

/* The main function for part one - will give the answer */
size_t PartOneFunction(int masks[MASK_ARRAY_SIZE][MASK_LENGTH], Mem mem[]);

/* Turn the value into a binary (array) */
void NumToBinary(size_t value, int binary_arr[]);

/* Changing the value according to it's mask */
void ChangeValueWithMask(int mask[], size_t *value);

/* Turn the binary value (array) into a decimal num */
void BinaryToNum(size_t *value, int binary_arr[]);


/**************************** PART TWO FUNCTIONS ******************************/

/* The main function for part two - will give the answer */
size_t PartTwoFunction(int masks[MASK_ARRAY_SIZE][MASK_LENGTH],
                                                Mem mem[MEM_ARRAY_SIZE]);

void NewKeysFromBasekey(size_t mask[], size_t key, size_t keys_arr[]);

void KeyToBinary(size_t key, size_t binary_arr[]);

void BinaryKeyWithoutFloating(size_t binary_key[], size_t mask[]);

void BinaryToKey(size_t *key, size_t binary_arr[]);

size_t NumOfXInMask(size_t mask[]);

void NoDuplicates(size_t keys_arr[]);

void CombineTwoArrs(AND info[], size_t temp_keys_arr[], size_t value);

void ZerosToEnd(size_t keys[]);

void ZerosToEndInfo(AND info[]);

Tree* CreateSpeacialTree();

void DestroySpecialTree(Tree* tree);


#endif /* DAY_14_H */