#include "include/types.h"
#include "include/rados/librados.hpp"

using namespace librados;

int initialize(librados::Rados* rados, librados::IoCtx* io_ctx,  char* id,std::string pool_name);

int encrypt_data_at_object_level(librados::ObjectWriteOperation* op, librados::IoCtx io_ctx,string oid,bufferlist in);

