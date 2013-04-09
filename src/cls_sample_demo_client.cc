#include "include/types.h"
#include "include/rados/librados.hpp"
#include "cls_sample_demo_client.h"
//#include "gtest/gtest.h"

using namespace librados;

int initialize(librados::Rados* rados, librados::IoCtx* io_ctx,  char* id,std::string pool_name){

  //printf("Program started...");
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


int call_sample_demo_method(librados::ObjectWriteOperation* op, librados::IoCtx io_ctx,string oid){

 bufferlist in,out;
 op->exec("cls_sample_demo","sample",in);
 //return io_ctx.exec(oid,op));
 return io_ctx.exec(oid,"sample_demo","sample",in,out); 
}



