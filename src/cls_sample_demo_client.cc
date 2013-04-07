#include "include/types.h"
#include "include/rados/librados.hpp"
#include "cls_sample_demo_client.h"

using namespace librados;

void cls_sample_demo_sample(){
 librados::ObjectWriteOperation* op = new librados::ObjectWriteOperation();
 bufferlist in;
 op->exec("cls_sample_demo","sample",in);
}
