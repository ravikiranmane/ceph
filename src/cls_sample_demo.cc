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
    
   //cls_log(20,"%s - sample_demo:In Sample()",&oid[0]);
   //if(cls_cxx_stat(ctx,NULL,NULL) == 0)
   //{
   //    cls_cxx_write_full(ctx,in);
   //    cls_log(20,"Child object already exist!");
   //    
   //}else{
   bufferlist bl,out1;
   bl.append(oid.c_str(),oid.length());
   cls_cxx_write(ctx,0,bl.length(),&bl);
   cls_log(20,"Written data from object class : %s\n", oid.c_str());
   //cls_cxx_read(ctx,0,bl.length(),&out1);
   //char outdata[128];
   //out1.copy(0,bl.length(),outdata);
   //cls_log(20,"Value of the object read from object class : %s\n", outdata);
   //}
   return 0;
}


void __cls_init()
{
   cls_log(20,"Loaded sample_demo class!");

   cls_register("sample_demo", &h_class);
   cls_register_cxx_method(h_class, "sample", CLS_METHOD_RD | CLS_METHOD_WR, sample_method, &h_sample);

   return;
}


