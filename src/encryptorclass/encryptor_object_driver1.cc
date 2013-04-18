#include "encryptorclass/cls_encryptor_object_client.h"
#include "gtest/gtest.h"
#include "include/types.h"

using namespace librados;

int main(int argc, char *argv[])
{


  char buf[128]; 
  char buf1[128];
  char buf2[128]; 
  char *id = getenv("CEPH_CLIENT_ID");
  string pool_name = "cls_encryptor_object_pool";
  //printf("Program started...");
  librados::Rados rados;
  librados::IoCtx io_ctx;
  librados::ObjectWriteOperation* op = new librados::ObjectWriteOperation();
  initialize(&rados,&io_ctx,id,pool_name);
  string oid = "cls_encryptor_object_oid";
  bufferlist inbl, outbl, inbl1;
  strcpy(buf,"Test String");   
  inbl.append(buf, sizeof(buf));
  io_ctx.write(oid, inbl, sizeof(buf), 0);
  
  //Start timer
  //Read it out now!
  io_ctx.read(oid, outbl, sizeof(buf), 0);
  outbl.copy(0,sizeof(buf1),buf1);
  printf("Value read : %s\n", buf1);
  
  //Perform operation now
  

  //Remove the old object and then 
  //Store contents in new object with same object ID.
  io_ctx.remove(oid);  
  io_ctx.write(oid, inbl, sizeof(buf), 0);
  //End timer



  io_ctx.read(oid, outbl, sizeof(buf2), 0);
  outbl.copy(0,sizeof(buf2),buf2);
  printf("Value read after operation : %s\n", buf2);
  

  
  return 0;

}
