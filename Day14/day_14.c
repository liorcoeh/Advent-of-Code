
#include "day_14.h"

/*******************************************************************************
****************************** GENERAL FUNCTIONS *******************************
*******************************************************************************/

void GettingInfo(char* file_name, int masks[MASK_ARRAY_SIZE][MASK_LENGTH],
                                Mem mem[])
{
    int mask_index = -1;
    size_t mem_index = 0;
    int i = 0;
    int j = 0;
    char c = 0;
    char buffer[10] = {0};
    char num[20] = {0};
    int counter = 0;
    int check = -1;

    FILE *fptr;

    if (NULL == (fptr = fopen(file_name, "r")))
    {
        // Program exits if file pointer returns NULL.
        printf("Error! opening file\n");
        exit (1);
    }

    while (EOF != (c = fgetc(fptr)))
    {
        if ('\n' == c)
        {
            if (2 == check)
            {
                mem[mem_index].value = atoi(num);
                ++mem_index;
                memset(num, 0, 20);
            }

            check = -1;
            counter = 0;
        }

        if ('a' == c)
        {
            check = 0;
            i = 0;
            ++mask_index;
        }
        else if ('[' == c)
        {
            check = 1;
            i = 0;
        }
        else if (']' == c)
        {
            mem[mem_index].mask_index = mask_index;
            mem[mem_index].key = atoi(num);
            memset(num, 0, 20);

            check = 2;
            i = 0;
        }

        ++counter;

        /* Getting the MASK info */
        if (0 == check && ('0' == c || '1' == c || 'X' == c))
        {
            switch (c)
            {
                case ('0'):
                {
                    masks[mask_index][i] = 0;
                    break;
                }
                case ('1'):
                {
                    masks[mask_index][i] = 1;
                    break;
                }
                default:
                {
                    masks[mask_index][i] = 2;
                    break;
                }
            }
            ++i;
        }

        /* Getting the first info (KEY) for MEM */
        else if (1 == check && ('0' <= c && '9' >= c))
        {
            *(num + i) = c;
            ++i;
        }

        /* Getting the second info (VALUE) for MEM */
        else if (2 == check && ('0' <= c && '9' >= c))
        {
            *(num + i) = c;
            ++i;
        }

    }

    mem[mem_index].value = atoi(num);

    fclose(fptr);
}


void PrintInfo(int masks[MASK_ARRAY_SIZE][MASK_LENGTH], Mem mem[])
{
    int mask_arr_index = 0;
    int mask_index = 0;
    int mem_index = 0;

    for (mask_arr_index = 0; mask_arr_index < 100; ++mask_arr_index)
    {
        for (mask_index = 0; mask_index < MASK_LENGTH; ++mask_index)
        {
            printf("%d", masks[mask_arr_index][mask_index]);
        }
        printf("\n");

        while (mem[mem_index].mask_index == mask_arr_index)
        {
            printf("Key = %d || Value = %ld\n", mem[mem_index].key, mem[mem_index].value);
            ++mem_index;
        }
    }
}


/*******************************************************************************
***************************** PART ONE FUNCTIONS *******************************
*******************************************************************************/

size_t PartOneFunction(int masks[MASK_ARRAY_SIZE][MASK_LENGTH], Mem mem[])
{
    int i = 0;
    int temp_key = 0;
    size_t temp_value = 0;
    size_t total_sum = 0;

    size_t arr[65387] = {0};

    for (i = 0; i < 464; ++i)
    {
        temp_key = mem[i].key;

        temp_value = mem[i].value;
        
        ChangeValueWithMask(masks[mem[i].mask_index], &temp_value);
        arr[temp_key] = temp_value;
    }

    for (i = 0; i < 65387; ++i)
    {
        total_sum += arr[i];
    }

    return (total_sum);
}

void ChangeValueWithMask(int mask[], size_t *value)
{
    int binary_arr[36] = {0};
    int i = 0;

    NumToBinary(*value, binary_arr);

    for (i = 0; i < 36; ++i)
    {
        if (0 == mask[i] || 1 == mask[i])
        {
            binary_arr[i] = mask[i];
        }
    }

    BinaryToNum(value, binary_arr);
}

void NumToBinary(size_t value, int binary_arr[])
{
    int i = 35;

    while (0 < value)
    {
        binary_arr[i] = value % 2;
        value /= 2;
        --i;
    }
}

void BinaryToNum(size_t *value, int binary_arr[])
{
    int i = 35;
    size_t base = 1;

    *value = 0;

    for (i = 35; i >= 0; --i)
    {
        (*value) += (binary_arr[i] * base);
        base *= 2;
    }
}


/*******************************************************************************
***************************** PART TWO FUNCTIONS *******************************
*******************************************************************************/

size_t PartTwoFunction(int masks[MASK_ARRAY_SIZE][MASK_LENGTH],
                                                Mem mem[MEM_ARRAY_SIZE])
{
    size_t total_sum = 0;
    int i = 0;
    int j = 0;
    int mask_index = 0;

    size_t mask[36] = {0};
    size_t base_key = 0;
    size_t value = 0;
    size_t keys_arr[512] = {0};

    AND info[100000] = {0};

    for (i = 462; i < 464; ++i)
    {
        base_key = mem[i].key;
        value = mem[i].value;
        if (mask_index != mem[i].mask_index)
        {
            ++mask_index;
        }

        for (j = 0; j < 36; ++j)
        {
            mask[j] = masks[mask_index][j];
        }

        for (j = 0; j < 512; ++j)
        {
            keys_arr[j] = 0;
        }

        NewKeysFromBasekey(mask, base_key, keys_arr);    

        NoDuplicates(keys_arr);

        CombineTwoArrs(info, keys_arr, value);
    }

    size_t min = 38342320700;
    size_t max = 0;

    for (i = 0; i < 100000; ++i)
    {
        if (0 == info[i].address)
        {
            break;
        }

        if (min > info[i].address)
        {
            min = info[i].address;
        }
        if (max < info[i].address)
        {
            max = info[i].address;
        }
        if (info[i].value != 0)
        {
            printf("%d) %ld||%ld\n", i, info[i].address, info[i].value);
        }
        total_sum += info[i].value;
    }

    printf("max = %ld. min = %ld\n", max, min);

    printf("%ld\n", total_sum);
    return (total_sum);
}

void NewKeysFromBasekey(size_t mask[], size_t key, size_t keys_arr[])
{
    Tree* the_tree = CreateSpeacialTree();
    size_t master_key[36] = {0};
    size_t binary_options[512][10] = {0};
    size_t new_binary_keys_arrs[512][36] = {0};
    size_t num_of_x = NumOfXInMask(mask);
    int index = 0;
    int i = 0;
    int j = 0;
    int sum = 0;
    size_t temp_key = 0;

    KeyToBinary(key, master_key);

    BinaryKeyWithoutFloating(master_key, mask);

    GetLevelBinary(the_tree, binary_options, &index, num_of_x);

    for (i = 0; i < 512; ++i)
    {
        if (0 < i)
        {
            sum = 0;
            for (j = 0; j < 10; ++j)
            {
                sum += binary_options[i][j];
            }
    
            if (0 == sum)
            {
                i = 513;
                break;
            }
        }

        j = 9;
        for (index = 0; index < 36; ++index)
        {
            if (2 == master_key[index])
            {
                new_binary_keys_arrs[i][index] = binary_options[i][j];
            }
            else
            {
                new_binary_keys_arrs[i][index] = master_key[index];
            }
            --j;
        }
    }

    for (i = 0; i < 512; ++i)
    {
        sum = 0;
        for (j = 0; j < 36; ++j)
        {
            sum += new_binary_keys_arrs[i][j];
        }

        if (0 == sum)
        {
            i = 513;
            break;
        }

        BinaryToKey(&temp_key, new_binary_keys_arrs[i]);

        keys_arr[i] = temp_key;
    }

    NoDuplicates(keys_arr);

    DestroySpecialTree(the_tree);
}

void KeyToBinary(size_t key, size_t binary_arr[])
{
    int i = 35;

    while (0 < key)
    {
        binary_arr[i] = key % 2;
        key /= 2;
        --i;
    }
}

void BinaryKeyWithoutFloating(size_t binary_key[], size_t mask[])
{
    int i = 0;

    for (i = 0; i < 36; ++i)
    {
        if ((1 == mask[i]) || (2 == mask[i]))
        {
            binary_key[i] = mask[i];
        }
    }
}

void BinaryToKey(size_t *key, size_t binary_arr[])
{
    int i = 35;
    size_t base = 1;

    *key = 0;

    for (i = 35; i >= 0; --i)
    {
        (*key) += (binary_arr[i] * base);
        base *= 2;
    }
}

size_t NumOfXInMask(size_t mask[])
{
    size_t num_of_x = 0;
    int i = 0;

    for (i = 0; i < 36; ++i)
    {
        if (2 == mask[i])
        {
            ++num_of_x;
        }
    }

    return (num_of_x);
}

void NoDuplicates(size_t keys_arr[])
{
    int i = 0;
    int j = 0;
    size_t count = 0;

    for (i = 0; i < 512; ++i)
    {
        if (0 != keys_arr[i])
        {
            for (j = i + 1; j < 512; ++j)
            {
                if (keys_arr[j] == keys_arr[i])
                {
                    keys_arr[j] = 0;
                }
            }
        }
    }

    for (i = 0; i < 512; ++i)
    {
        if (0 < keys_arr[i])
        {
            keys_arr[count] = keys_arr[i];
            ++count;
        }
    }

    while (count < 512)
    {
        keys_arr[count] = 0;
        ++count;
    }
}

void CombineTwoArrs(AND info[], size_t temp_keys_arr[], size_t value)
{
    int i = 0;
    int j = 0;
    int index = 0;

    for (i = 0; i < 100000; ++i)
    {
        if (0 == info[i].address)
        {
            index = i;
            break;
        }

        j = 0;

        while (0 != temp_keys_arr[j])
        {
            if (info[i].address == temp_keys_arr[j])
            {
                info[i].value = value;
                temp_keys_arr[j] = 0;
            }
            ++j;
        }
    }

    ZerosToEnd(temp_keys_arr);
    // for (j = 0; j < 512; ++j)
    //     {
    //         if (0 == temp_keys_arr[j])
    //         {
    //             break;
    //         }
    //         printf("%ld\n", temp_keys_arr[j]);
    //     }
    //     printf("\n\n");


    // for (i = 0; i < 512; ++i)
    // {
    //     if (0 == temp_keys_arr[i])
    //     {
    //         break;
    //     }
    //     printf("%ld\n", temp_keys_arr[i]);
    // }
    // printf("\n\n");

    j = 0;
    for (i = 0; i < 100000; ++i)
    {
        if (0 == temp_keys_arr[j])
        {
            break;
        }
        if (0 == info[i].address)
        {
            info[i].address = temp_keys_arr[j];
            info[i].value = value;
            ++j;
            //printf("%ld ====\n", info[i].address);
        }
    }

    ZerosToEndInfo(info);
}

void ZerosToEnd(size_t keys[])
{
    size_t count = 0;
    int i = 0;

    for (i = 0; i < 512; ++i)
    {
        if (0 < keys[i])
        {
            keys[count] = keys[i];
            ++count;
        }
    }

    while (count < 512)
    {
        keys[count] = 0;
        ++count;
    }
}

void ZerosToEndInfo(AND info[])
{
    size_t count = 0;
    int i = 0;

    for (i = 0; i < 100000; ++i)
    {
        if (0 < info[i].address)
        {
            info[count].address = info[i].address;
            info[count].value = info[i].value;
            ++count;
        }
    }

    while (count < 100000)
    {
        info[count].address = 0;
        info[count].value = 0;
        ++count;
    }
}

Tree* CreateSpeacialTree()
{
    int i = 0;
    Tree* tree = TreeCreate();

    for (i = 0; i < 10; ++i)
    {
        TreeInsert(tree);
    }

    return (tree);
}

void DestroySpecialTree(Tree* tree)
{
    TreeDestroy(tree);
}