#include <vector>
#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"
#include "LSH.h"
#include "ui.h"
#include "parse_files.h"
#include "search.h"
#include "curve_grid_lsh.h"

static FILE* temp_file = NULL;
using namespace std;

void test_DTW() {
   vector<Point> pointVec {(*new Point(vector<double> {-1,-1})),(*new Point(vector<double> {2,2}))};
   vector<Point> pointVec2 {(*new Point(vector<double> {3,3})),(*new Point(vector<double> {4,4}))};
   auto curv1 = new Curve(pointVec);
   auto curv2 = new Curve(pointVec2);
   auto dmetric = new DTW();
   CU_ASSERT(dmetric->dist(curv2,curv1) > 8 && dmetric->dist(curv2,curv1) < 9);
}

void test_ReadArgsCurves() {
    auto lsh = new LSH(new DTW());
    char *argv[]= {
        "progName",
        "-d", "input_lol",
        "-q", "query_lol",
        "-o", "output_lol",
        "-k_vec ", "1",
        "-L_grid", "888",
    };
    int argc = sizeof(argv)/sizeof(char*);
    readArgumentsLSHCurves(lsh,argc,argv);
    CU_ASSERT(lsh->getInputFilename() == "input_lol");
    CU_ASSERT(lsh->getQueryFilename() == "query_lol");
    CU_ASSERT(lsh->getOutputFilename() == "output_lol");
    CU_ASSERT(lsh->getNumOfFunctions() == 1);
    CU_ASSERT(lsh->getNumOfHashTables() == 888);
}

void test_ParseTestFile(LSH *lsh) {
    auto dataset = lsh->getDataset();
    CU_ASSERT(dataset->getMax() == 3);
    CU_ASSERT(dataset->getMin() == 2);
    CU_ASSERT(dataset->getDimension() == 2);
    CU_ASSERT(dataset->getSize() == 2);
    auto data = dataset->getData();
    auto curve1 = dynamic_cast<Curve *>(data.at(0));
    CU_ASSERT(curve1->getId() == "curve_id1");
    auto point11 = curve1->getPoint(0);
    auto expected = new Point(vector<double> {-43242.423,849.438});
    CU_ASSERT(*expected == point11);
    auto point12 = curve1->getPoint(1);
    expected = new Point(vector<double> {33,32.43});
    CU_ASSERT(*expected == point12);
    auto point13 = curve1->getPoint(2);
    expected = new Point(vector<double> {-787.432,-888});
    CU_ASSERT(*expected == point13);
    auto curve2 = dynamic_cast<Curve *>(data.at(1));
    CU_ASSERT(curve2->getId() == "2");
    auto point21 = curve2->getPoint(0);
    expected = new Point(vector<double> {4324,43242});
    CU_ASSERT(*expected == point21);
    auto point22 = curve2->getPoint(1);
    expected = new Point(vector<double> {988.4328,-48778});
    CU_ASSERT(*expected == point22);
}

void test_ParseCurves() {
    auto lsh = new LSH(new DTW());
    lsh->setInputFilename("../src/testdata/curves_loukas_small");
    lsh->setData(parseInputFileCurves(lsh->getInputFilename()));
    test_ParseTestFile(lsh);
    delete lsh;
    //----------------------
    lsh = new LSH(new DTW());
    lsh->setInputFilename("../src/testdata/trajectories_input");
    lsh->setData(parseInputFileCurves(lsh->getInputFilename()));
    CU_ASSERT(lsh->getDataset()->getSize() == 7401);
    delete lsh;
    //----------------------
    lsh = new LSH(new DTW());
    lsh->setQueryFilename("../src/testdata/trajectories_query");
    lsh->setData(parseQueryFileCurves(lsh->getQueryFilename()));
    CU_ASSERT(lsh->getDataset()->getSize() == 86);
    delete lsh;
    //----------------------
}

LSH *LoadInputLSHCurves(string inputFilename,string queryFilename) {
   auto lsh = new LSH(new DTW());
    lsh->setInputFilename(inputFilename);
    lsh->setData(parseInputFileCurves(lsh->getInputFilename()));
    lsh->setNumOfFunctions(4);
    lsh->setNumOfHashTables(5);
    auto dataset = lsh->getDataset();
    lsh->setHashTableStruct(new CurveHashTableStruct(lsh->getNumOfHashTables(), dataset->getSize(),lsh->getNumOfFunctions(),dataset->getDimension(),dataset->getMin(),dataset->getMax(),4000));
    auto curves = dataset->getData();
    for (auto & curve : curves)
        lsh->getHashTableStruct()->addToAllHashTables(curve);
    lsh->setQueryFilename(queryFilename);
    lsh->setQueryData(parseQueryFileCurves(lsh->getQueryFilename()));
   return lsh;
}

void test_File(string inputFilename,string queryFilename) {
   auto lsh = LoadInputLSHCurves(inputFilename,queryFilename);
   DoQueries(lsh);
}

void test_Files() {
   test_File("../src/testdata/trajectories_input","../src/testdata/trajectories_query");
}

int init_suite1(void)
{
   if (NULL == (temp_file = fopen("testPoinHasher.txt", "w+"))) {
      return -1;
   }
   else {
      return 0;
   }
}

/* The suite cleanup function.
 * Closes the temporary file used by the tests.
 * Returns zero on success, non-zero otherwise.
 */
int clean_suite1(void)
{
   if (0 != fclose(temp_file)) {
      return -1;
   }
   else {
      temp_file = NULL;
      return 0;
   }
}

int main(int argc,char *argv[]) {
   CU_pSuite pSuite = NULL;
   if (CUE_SUCCESS != CU_initialize_registry())
      return CU_get_error();
   pSuite = CU_add_suite("Suite_1", init_suite1, clean_suite1);
   if (NULL == pSuite) {
      CU_cleanup_registry();
      return CU_get_error();
   }
   if ((NULL == CU_add_test(pSuite, "test of read curve args",test_ReadArgsCurves)) ||
    (NULL == CU_add_test(pSuite, "test of read curve args",test_ParseCurves)) ||
    (NULL == CU_add_test(pSuite, "test of files - main test",test_Files)) ||
    (NULL == CU_add_test(pSuite, "test of read curve args",test_DTW))) 
         {
         CU_cleanup_registry();
      return CU_get_error();
   }
   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   CU_cleanup_registry();
   return CU_get_error();
}
