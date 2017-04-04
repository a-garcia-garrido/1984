#include <stdio.h>
#include <stdlib.h>
#include <opencv2/core/core.hpp>
#include <opencv2/contrib/contrib.hpp>

using namespace std;
using namespace cv;

int
main (int argc, const char *argv[])
{
    Ptr<FaceRecognizer> model = createEigenFaceRecognizer();

    return EXIT_SUCCESS;
}
