#include <string>
#include "HashTableStruct.h"
#include "Dataset.h"

using namespace std;

int powModulo(int base,int exp,int div);
bool file_exists(const char* filename);
bool is_number(string  str);

void test_print_hashtable(HashTableStruct *hashTableStruct);
void test_print_data(DatasetPoints *data);
void test_print_query_data(QueryDatasetPoints *data);