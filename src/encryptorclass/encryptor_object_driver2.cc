#include "encryptorclass/cls_encryptor_object_client.h"
#include "gtest/gtest.h"
#include "include/types.h"

using namespace librados;

int main(int argc, char *argv[])
{
  //sample_demo sd = new sample_demo();
  int DATA_SIZE = 2097152;
  //int DATA_SIZE = 1048576;
  //int DATA_SIZE = 1572864;
  char buf[DATA_SIZE]; 
  char buf1[DATA_SIZE];
  char buf2[DATA_SIZE]; 
  long starttime = 0, totaltime = 0;
  bufferlist inbl, outbl;
  char *id = getenv("CEPH_CLIENT_ID");
  string pool_name = "cls_encryptor_object_pool";
  
  //printf("Program started...");
  librados::Rados rados;
  librados::IoCtx io_ctx;
  librados::ObjectWriteOperation* op = new librados::ObjectWriteOperation();
  initialize(&rados,&io_ctx,id,pool_name);
  string oid = "cls_encryptor_object_oid";
  memset(buf,'a',DATA_SIZE);
  inbl.append(buf, sizeof(buf));
  ////printf("Value in buf : %s\nbuf size : %d\n", buf,sizeof(buf));
  //io_ctx.write(oid, inbl, sizeof(buf), 0);
  io_ctx.write(oid, inbl, DATA_SIZE, 0);
  
  bufferlist in,outbl2;
 
  //::encode(oid,in);
  ::encode(DATA_SIZE,in);
  //starttime = clock();  
  printf("exec() returned : %d\n",encrypt_data_at_object_level(op,io_ctx,oid,in));
  totaltime = clock() - starttime;
  //printf("Total time : %ld", totaltime);  
}
