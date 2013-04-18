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
CLS_NAME(cls_object_class_test)

cls_handle_t h_class;

cls_method_handle_t h_sample;

int object_class_write(cls_method_context_t ctx, bufferlist* in, bufferlist *out)
{
   cls_log(20,"Written data from object class"); 
   /*bufferlist::iterator iter = in->begin();
   string oid;
   ::decode(oid,iter);
   bufferlist bl,out1;
   bl.append(oid.c_str(),oid.length());
   cls_cxx_write(ctx,0,bl.length(),&bl);
   cls_log(20,"Written data from object class : %s\n", oid.c_str());
   */
   return 0;
}

int object_class_read(cls_method_context_t ctx, bufferlist* in, bufferlist *out)
{
   bufferlist::iterator iter = in->begin();
   
   string oid;
   ::decode(oid,iter);
   bufferlist out1(oid.length());   
   int length_read = cls_cxx_read(ctx,0,oid.length(),&out1);
   char outdata[128];
   out1.copy(0,oid.length(),outdata);
   cls_log(20,"Value of the object read from object class : %s\n", outdata);
   return 0;
}

int object_class_level_encryption(cls_method_context_t ctx, bufferlist* in, bufferlist *out)
{

  return 0;

}

void __cls_init()
{
   cls_log(20,"Loaded cls_object_class_test class!");

   cls_register("cls_object_class_test", &h_class);
   //   cls_register_cxx_method(h_class, "sample", CLS_METHOD_RD | CLS_METHOD_WR, sample_method, &h_sample);
   cls_register_cxx_method(h_class, "object_class_write", CLS_METHOD_RD | CLS_METHOD_WR, object_class_write, &h_sample);
   cls_register_cxx_method(h_class, "object_class_read", CLS_METHOD_RD, object_class_read, &h_sample);
   cls_register_cxx_method(h_class, "object_class_level_encryption", CLS_METHOD_RD | CLS_METHOD_WR, object_class_level_encryption, &h_sample);
   return;
}


