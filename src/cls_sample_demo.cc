/*## rados object classes
#libcls_sample_demo.so: cls_sample_demo.cc
#${CXX} -fPIC -shared -g -o libcls_sample_demo.so cls_sample_demo.cc
#BUILT_SOURCES += libcls_sample_demo.so
*/



#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#include <openssl/md5.h>
#include <openssl/sha.h>

#include "include/types.h"
#include "objclass/objclass.h"


CLS_VER(1,0)
CLS_NAME(sample_demo)

cls_handle_t h_class;

cls_method_handle_t h_sample;

int sample_method(cls_method_context_t ctx, bufferlist* in, bufferlist *out)
{
   bufferlist::iterator iter = in->begin();
   string oid;
   ::decode(oid,iter);
   cls_log(20,"%s - sample_demo:In Sample()",&oid[0]);
   return 0;
}


void __cls_init()
{
   cls_log(20,"Loaded sample_demo class!");

   cls_register("sample_demo", &h_class);
   cls_register_cxx_method(h_class, "sample", CLS_METHOD_RD, sample_method, &h_sample);

   return;
}

