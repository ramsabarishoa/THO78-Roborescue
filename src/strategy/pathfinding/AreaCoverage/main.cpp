#include <iostream>
#include "dimension.h"
#include "testcopter.h"
#include "arraymap.h"
#include "areacoveringalgorithm.h"
using namespace std;
void test(int i){
    Dimension Sightrange(3,3);
    Dimension coptersize(1,1);
    TestCopter copter(coptersize,Sightrange,1,1);
    ArrayMap* map = new ArrayMap(i);

    AreaCoveringAlgorithm alg(copter,map);
    alg.testCoverage();


}

int main(int argc, char *argv[])
{
    test(1);
    return 0;

}

