#include "include/types.h"
#include "include/rados/librados.hpp"
#include "cls_encryptor_object_client.h"
#include <openssl/aes.h>
//#include "gtest/gtest.h"

using namespace librados;

int initialize(librados::Rados* rados, librados::IoCtx* io_ctx,  char* id,std::string pool_name){

  int r = rados->init(id);
    if (r < 0)
      return r;
    r = rados->conf_read_file(NULL);
    if (r < 0)
      return r;
    r = rados->conf_parse_env(NULL);
    if (r < 0)
      return r;
    printf("Trying rados.connect()...\n");

    r = rados->connect();

    r = rados->pool_create(pool_name.c_str()); 
  
    if (r < 0)
      return r;
    printf("rados->connect() successful...about to call io_ctx_create()...\n");  
    r = rados->ioctx_create(pool_name.c_str(), *io_ctx);
    if (r < 0) {
      rados->shutdown();
      printf("Return from ioctx_create() is : %d\n",r ); 
      return r;
    }
    printf("Rados object obtained...\n");

    return r;
}


int encrypt_data_at_object_level(librados::ObjectWriteOperation* op, librados::IoCtx io_ctx,string oid,bufferlist in){
 
 bufferlist out;
 int DATA_SIZE = 0;
 long starttime = 0,endtime = 0;
 //op->exec("cls_object_class_test","object_class_write",in);
 int ret = 0;
 //io_ctx.exec(oid,"encryptor_object","object_class_write",in,out);
 //return 0;
 //return ret;
 //librados::ObjectReadOperation* op1;
 //::decode(oid,in);
 ::decode(DATA_SIZE,in);
 printf("Data_size : %d",DATA_SIZE);  
 bufferlist in1;
 //::encode(oid,in1);
 ::encode(DATA_SIZE,in1);
 //ret = io_ctx.exec(oid,"encryptor_object","object_class_read",in1,out);
 //object_class_level_encryption
 starttime = clock();
 ret = io_ctx.exec(oid,"encryptor_object","object_class_level_encryption",in1,out);
 printf("Total time from client : %ld",clock() - starttime);
 return ret;
}



