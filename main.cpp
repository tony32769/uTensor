#include "FATFileSystem.h"
#include "SDBlockDevice.h"
#include "mbed.h"
#include "stdio.h"
#include "uTensor_util.hpp"
#include "tensor.hpp"
#include "tensorIdxImporterTests.hpp"
#include "context.hpp"
#include "ArrayTests.hpp"
#include "MatrixTests.hpp"
#include "tensor_test.hpp"
#include "NnTests.hpp"
// #include "mlp_test.hpp"
#include "deep_mnist_mlp.hpp"
#include "context_test.hpp"
#include "MathTests.hpp"
#include "sdtest.hpp"
#include "vmtest.hpp"

Serial pc(USBTX, USBRX, 115200);
SDBlockDevice bd(MBED_CONF_APP_SD_MOSI, MBED_CONF_APP_SD_MISO,
                 MBED_CONF_APP_SD_CLK, MBED_CONF_APP_SD_CS);
FATFileSystem fs("fs");

int main(int argc, char** argv) {
  ON_ERR(bd.init(), "SDBlockDevice init ");
  ON_ERR(fs.mount(&bd), "Mounting the filesystem on \"/fs\". ");
  init_env();

  printf("Deep MLP on Mbed (Trained with Tensorflow)\r\n\r\n");
  printf("running deep-mlp...\r\n");

  int prediction = runMLP("/fs/testData/deep_mlp/import-Placeholder_0.idx");
  printf("prediction: %d\r\n\r\n\r\n\r\n", prediction);

  printf("IDX import:\r\n");
  idxImporterTest idxTest;
  idxTest.runAll();
  printf("IDX import result...\r\n");
  idxTest.printSummary();

  printf("vm: \r\n");
  vmTest vmtest;
  vmtest.runAll();
  printf("VM result...\r\n");
  vmtest.printSummary();

  printf("SDTensor test:\r\n");
  SDTensorTest sdtest;
  sdtest.runAll();
  printf("sd tensor result...\r\n");
  sdtest.printSummary();

  printf("tesnor test: \r\n");
  tensorTest tenT;
  tenT.runAll();
  printf("tensor result...\r\n");
  tenT.printSummary();

  printf("Context test: \r\n");
  contextTest ctxTest;
  ctxTest.runAll();
  printf("Context result...\r\n");
  ctxTest.printSummary();

  printf("Transformation test: \r\n");
  transTest tTest;
  tTest.runAll();
  printf("Transformation result...\r\n");
  tTest.printSummary();

  printf("Array test: \r\n");
  ArrayOpsTest arrayTests;
  arrayTests.runAll();
  printf("Array result...\r\n");
  arrayTests.printSummary();

  printf("Math: \r\n");
  MathOpsTest mathTests;
  mathTests.runAll();
  printf("Math result...\r\n");
  mathTests.printSummary();

  printf("running matrix test:\r\n");
  matrixOpsTest matrixTests;
  matrixTests.runAll();
  printf("running matrix result ...\r\n");
  matrixTests.printSummary();

  printf("NnOpS: \r\n");
  NnOpsTest nnTest;
  nnTest.runAll();
  printf("Nn Ops result...\r\n");
  nnTest.printSummary();


/*   printf("mlp test: \r\n");
  mlpTest mlpt;
   mlpt.runAll();
   printf("mlp result...\r\n");
   mlpt.printSummary();*/



  //In [24]: tf.get_default_graph().get_tensor_by_name("import/y_pred:0").eval(feed_dict={x: mnist.test.images[0:1]})
  //Out[24]: array([7])

  printf("\r\ndone...\r\n");

  ON_ERR(fs.unmount(), "fs unmount ");
  ON_ERR(bd.deinit(), "SDBlockDevice de-init ");
}
