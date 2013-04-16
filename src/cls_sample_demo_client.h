#include "include/types.h"
#include "include/rados/librados.hpp"

using namespace librados;

int initialize(librados::Rados* rados, librados::IoCtx* io_ctx,  char* id,std::string pool_name);

//void cls_sample_demo_sample();

//int call_sample_demo_method(librados::ObjectWriteOperation* op);

int call_sample_demo_method(librados::ObjectWriteOperation* op, librados::IoCtx io_ctx,string oid,bufferlist in);

