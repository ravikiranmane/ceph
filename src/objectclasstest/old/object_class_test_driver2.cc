#include "objectclasstest/cls_object_class_test_client.h"
#include "gtest/gtest.h"
#include "include/types.h"

using namespace librados;

int main(int argc, char *argv[])
{
  //sample_demo sd = new sample_demo();
  char buf[128]; 
  char buf1[128];
  char buf2[128]; 
  char *id = getenv("CEPH_CLIENT_ID");
  string pool_name = "cls_object_class_pool";
  //printf("Program started...");
  librados::Rados rados;
  librados::IoCtx io_ctx;
  librados::ObjectWriteOperation* op = new librados::ObjectWriteOperation();
  initialize(&rados,&io_ctx,id,pool_name);
  string oid = "cls_object_class_test_oid";
  bufferlist inbl, outbl;
  bufferlist in,outbl2;
  
  ::encode(oid,in);
  printf("operate() returned : %d\n",encrypt_data_at_object_level(op,io_ctx,oid,in));
  
}
