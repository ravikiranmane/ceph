#include "encryptorclass/cls_encryptor_object_client.h"
#include "gtest/gtest.h"
#include "include/types.h"
#include <openssl/aes.h>

using namespace librados;
int DATA_SIZE = 2097152;
int main(int argc, char *argv[])
{

  
  char buf[DATA_SIZE]; 
  char buf1[DATA_SIZE];
  char buf2[DATA_SIZE];
  long starttime = 0,totaltime = 0; 
  char *id = getenv("CEPH_CLIENT_ID");
  string pool_name = "cls_encryptor_object_pool";
  //printf("Program started...");
  librados::Rados rados;
  librados::IoCtx io_ctx;
  librados::ObjectWriteOperation* op = new librados::ObjectWriteOperation();
  initialize(&rados,&io_ctx,id,pool_name);
  string oid = "cls_encryptor_object_oid";
  bufferlist inbl, outbl, inbl1;
  //strcpy(buf,"Test String");   
  memset(buf,'a',DATA_SIZE);
  inbl.append(buf, sizeof(buf));
  ////printf("Value in buf : %s\nbuf size : %d\n", buf,sizeof(buf));
  //io_ctx.write(oid, inbl, sizeof(buf), 0);
  io_ctx.write(oid, inbl, DATA_SIZE, 0);
  //Start timer
  //Read it out now!
  //io_ctx.read(oid, outbl, sizeof(buf), 0);
  starttime = clock();
  io_ctx.read(oid, outbl, DATA_SIZE, 0);
  outbl.copy(0,DATA_SIZE,buf1);
  ////printf("Value read : %s\nbuf1 size : %d\n", buf1,sizeof(buf1));
  
  //Perform operation now -- the AES encryption part
  int bytes_read, bytes_written;
  //unsigned char indata[AES_BLOCK_SIZE];
  //unsigned char outdata[AES_BLOCK_SIZE];

  unsigned char indata[DATA_SIZE];
  unsigned char outdata[DATA_SIZE];


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

  //while (1) {
    //bytes_read = fread(indata, 1, AES_BLOCK_SIZE, buf1);
    
    //AES_cfbDATA_SIZE_encrypt(indata, outdata, bytes_read, &key, ivec, &num,
    //       AES_ENCRYPT);
    AES_cfb128_encrypt((unsigned char*)buf1, outdata, sizeof(buf1), &key, ivec, &num, AES_ENCRYPT);

    //bytes_written = fwrite(outdata, 1, bytes_read, ofp);
    //if (bytes_read < AES_BLOCK_SIZE)
  //break;
  //}
  // END of AES encryption  
  
  //Remove the old object and then 
  //Store contents in new object with same object ID.
  ////printf("Value encrypted : %s \n outdata size is : %d\n", outdata,sizeof(outdata));
  io_ctx.remove(oid);
  
  inbl1.append((const char*)outdata, sizeof(outdata));
  io_ctx.write(oid, inbl1, sizeof(outdata), 0);
  //End timer
  printf("Encrypted data written to the object");
  totaltime = clock();
  printf("Start time : %ld\n End time : %ld",starttime,totaltime);
  totaltime -= starttime;
  
  printf("Total time taken : %ld\n",totaltime);
  io_ctx.read(oid, outbl, sizeof(buf2), 0);
  outbl.copy(0,sizeof(buf2),buf2);
  ////printf("Value read after operation : %s\n", buf2);
   
  AES_cfb128_encrypt((unsigned char*)buf2, outdata, sizeof(buf2), &key, ivec, &num, AES_DECRYPT);
  
  ////printf("Value after decryption operation : %s\n with size %d\n", outdata,sizeof(outdata));
  
  return 0;

}
