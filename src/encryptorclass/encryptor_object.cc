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
#include <openssl/aes.h>

#include "include/types.h"
#include "objclass/objclass.h"


CLS_VER(1,0)
CLS_NAME(encryptor_object)

cls_handle_t h_class;

cls_method_handle_t h_sample;

int object_class_write(cls_method_context_t ctx, bufferlist* in, bufferlist *out)
{
   
   bufferlist::iterator iter = in->begin();
   string oid;
   ::decode(oid,iter);
   bufferlist bl,out1;
   bl.append(oid.c_str(),oid.length());
   cls_log(20,"About to write the following from object class : %s",oid.c_str()); 
   cls_cxx_write(ctx,0,bl.length(),&bl);
   cls_log(20,"Written data from object class : %s\n", oid.c_str());
   
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
  int DATA_SIZE = 1024;
  int bytes_read, bytes_written;
  //unsigned char indata[AES_BLOCK_SIZE];
  //unsigned char outdata[AES_BLOCK_SIZE];

  

  //Read from the object
  bufferlist::iterator iter = in->begin();
  //string oid;
  //::decode(oid,iter);
  ::decode(DATA_SIZE,iter); 
  cls_log(20,"Data_size decoded : %d",DATA_SIZE);
  unsigned char indata[DATA_SIZE];
  char outdata[DATA_SIZE];
  char outdata1[DATA_SIZE];
  char outdata2[DATA_SIZE]; 
  bufferlist out1(DATA_SIZE);   
  int length_read = cls_cxx_read(ctx,0,DATA_SIZE,&out1);


  //char outdata[DATA_SIZE];
  out1.copy(0,DATA_SIZE,outdata);
  cls_log(20,"Data read from object : %s\n with size : %d",outdata,sizeof(outdata));
  cls_cxx_remove(ctx);
  //Perform the operation here
  //int bytes_read, bytes_written;
  /* ckey and ivec are the two DATA_SIZE-bits keys necesary to
     en- and recrypt your data.  Note that ckey can be
     192 or 256 bits as well */
  unsigned char ckey[] = "keyforaesencryption";
  unsigned char ivec[] = "thisisyetanotherkey";
  
  /* data structure that contains the key itself */
  AES_KEY key;

  /* set the encryption key */
  AES_set_encrypt_key(ckey, DATA_SIZE, &key);

  /* set where on the DATA_SIZE bit encrypted block to begin encryption*/
  int num = 0;

  AES_cfb128_encrypt((unsigned char*)outdata, (unsigned char*)outdata1, DATA_SIZE, &key, ivec, &num, AES_ENCRYPT);



  //Write back into the object 
  //bufferlist::iterator iter1 = in->begin();
  //string oid;
  //::decode(oid,iter1);
  bufferlist bl;
  cls_log(20,"Encrypted data : %s\n",outdata1);

  bl.append(outdata1,DATA_SIZE);
  cls_log(20,"About to write from object class"); 
  return cls_cxx_write(ctx,0,DATA_SIZE,&bl);
  //return 0;

}

void __cls_init()
{
   cls_log(20,"Loaded encryptor_object class!");

   cls_register("encryptor_object", &h_class);
   //   cls_register_cxx_method(h_class, "sample", CLS_METHOD_RD | CLS_METHOD_WR, sample_method, &h_sample);
   cls_register_cxx_method(h_class, "object_class_write", CLS_METHOD_RD | CLS_METHOD_WR, object_class_write, &h_sample);
   cls_register_cxx_method(h_class, "object_class_read", CLS_METHOD_RD | CLS_METHOD_WR, object_class_read, &h_sample);
   cls_register_cxx_method(h_class, "object_class_level_encryption", CLS_METHOD_RD | CLS_METHOD_WR, object_class_level_encryption, &h_sample);
   return;
}


