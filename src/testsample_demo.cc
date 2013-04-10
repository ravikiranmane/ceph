#include "cls_sample_demo_client.h"
#include "gtest/gtest.h"
#include "include/types.h"

using namespace librados;

int main(int argc, char *argv[])
{
  //sample_demo sd = new sample_demo();
  char buf[128]; 
  char buf1[128]; 
  char *id = getenv("CEPH_CLIENT_ID");
  string pool_name = "sample_demo_pool";
  //printf("Program started...");
  librados::Rados rados;
  librados::IoCtx io_ctx;
  librados::ObjectWriteOperation* op = new librados::ObjectWriteOperation();
  /*
   int r = rados.init(id);
    if (r < 0)
      return r;
    r = rados.conf_read_file(NULL);
    if (r < 0)
      return r;
    r = rados.conf_parse_env(NULL);
    if (r < 0)
      return r;
    printf("Trying rados.connect()...");

    r = rados.connect();

    r = rados.pool_create(pool_name.c_str()); 
    //printf("About to create pool...");
    //create_one_pool_pp(pool_name, rados);
    //printf("Pool created...");
    if (r < 0)
      return r;
    printf("rados.connect() successful...about to call io_ctx_create()...");  
    r = rados.ioctx_create(pool_name.c_str(), io_ctx);
    if (r < 0) {
      rados.shutdown();
      printf("Return from ioctx_create() is : %d",r ); 
      return r;
    }
  printf("Rados object obtained...");
  */
  //char *id = getenv("CEPH_CLIENT_ID");
  //string pool_name = "sample_demo_pool";
  //cls_sample_demo_client c;
  initialize(&rados,&io_ctx,id,pool_name);
  string oid = "sample_demo_read_write_test";
  bufferlist inbl, outbl;
  
  /*
  // copyup of 0-len nonexistent object should create new 0-len object
  ioctx.remove(oid);
  ASSERT_EQ(0, copyup(&ioctx, oid, inbl));
  uint64_t size;
  ASSERT_EQ(0, ioctx.stat(oid, &size, NULL));
  ASSERT_EQ(0U, size);
  
  // create some random data to write

  size_t l = 55555;
  char *b = random_buf(l);
  inbl.append(b, l);
  delete b;
  ASSERT_EQ(l, inbl.length());

  // copyup to nonexistent object should create new object
  ioctx.remove(oid);
  ASSERT_EQ(-ENOENT, ioctx.remove(oid));
  ASSERT_EQ(0, copyup(&ioctx, oid, inbl));
  // and its contents should match
  */
  
  strcpy(buf,"Test String");   
  //memset(buf, 0xcc, sizeof(buf));
  printf("Writing : %s",buf);
  //bufferlist bl;
  inbl.append(buf, sizeof(buf));
  //ASSERT_EQ((int)sizeof(buf), io_ctx.write(oid, inbl, sizeof(buf), 0));
  io_ctx.write(oid, inbl, sizeof(buf), 0);
  //ASSERT_EQ((size_t)sizeof(buf), (size_t)io_ctx.read(oid, outbl, sizeof(buf), 0));
  io_ctx.read(oid, outbl, sizeof(buf), 0);
  printf("Read from object!\n");
  //ASSERT_TRUE(outbl.contents_equal(inbl));
  

  //////////////////////////////////////////////
  outbl.contents_equal(inbl);
  std::string s;
  ////////////////////////////////////////////// 
  //bufferlist::iterator out = outbl.begin();
  
  //////////////////////////////////////////////
  outbl.copy(0,sizeof(buf1),buf1);
  printf("Value read : %s\n", buf1);
  //////////////////////////////////////////////
  // now send different data, but with a preexisting object
  //bufferlist inbl2;
  //b = random_buf(l);
  //inbl2.append(b, l);
  //delete b;
  //ASSERT_EQ(l, inbl2.length());
  
  // should still succeed
  //ASSERT_EQ(0, copyup(&ioctx, oid, inbl));
  //ASSERT_EQ(l, (size_t)ioctx.read(oid, outbl, l, 0));
  // but contents should not have changed
  //ASSERT_FALSE(outbl.contents_equal(inbl2));
  //ASSERT_TRUE(outbl.contents_equal(inbl));
  bufferlist in;
  //strcpy(buf,oid);   
  //in.append(buf, sizeof(buf));
  ::encode(oid,in);
  printf("operate() returned : %d\n",call_sample_demo_method(op,io_ctx,oid,in));
 
  
  //ASSERT_EQ(0, io_ctx.remove(oid));
  io_ctx.remove(oid);
  io_ctx.close();

  //librados::ObjectWriteOperation *op = new_op();
  //cls_sample_demo_sample();

  //sample_demo sd = new sample_demo();
  //printf("Method returned : %d",sd.sample);
  
  return 0;
}

