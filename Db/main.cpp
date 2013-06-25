#include "vCode.h"
#include "commonType.h"
#include "HashSet.h"
#include "StringUtils.h"
#include <iostream>
#include <limits.h>
using namespace std;
//class test :
//	public IHashCode<int>{
//public:
//	test(){}
//	int getHashCode(void){
//		return 1;
//	}
//};
//#define TEST_SEARCH
//
//
void test(){
	int rv=11;
	int b[]={0x01020304,2,3};
	float a[]={1,3,5};
	cout << "-1" << (StringUtils::binarySearch<float>(a,-1,3,rv) ? "true" : "false") <<"	" <<rv << endl;
	cout << "1"  << (StringUtils::binarySearch<float>(a,1,3,rv) ? "true" : "false") <<"	" << rv << endl;
	cout << "3"  << (StringUtils::binarySearch<float>(a,3,3,rv) ? "true" : "false") <<"	" << rv << endl;
	cout << "5"  << (StringUtils::binarySearch<float>(a,5,3,rv) ? "true" : "false") <<"	" << rv << endl;
	cout << "7"  << (StringUtils::binarySearch<float>(a,7,3,rv) ? "true" : "false") <<"	" << rv <<endl;
	cout << "2"  << (StringUtils::binarySearch<float>(a,2,3,rv) ? "true" : "false") <<"	" << rv << endl;
	cout << "4"  << (StringUtils::binarySearch<float>(a,4,3,rv) ? "true" : "false") <<"	" << rv <<endl;
	cout << "0.5"  << (StringUtils::binarySearch<float>(a,0.5,3,rv) ? "true" : "false") <<"	" << rv <<endl;
	cout << "1.5"  << (StringUtils::binarySearch<float>(a,1.5,3,rv) ? "true" : "false") <<"	" << rv <<endl;
	cout << "1.6"  << (StringUtils::binarySearch<float>(a,1.6,3,rv) ? "true" : "false") <<"	" << rv <<endl;
	cout << rv <<endl;
}
//
//void testEndian(){
//  int x=1;
//  if (*(char *) &x ==1)
//      printf("Little endian!\n");
//  else
//		printf("Big endian!\n");
//}
////#define TEST_DBFILE
//#ifdef TEST_DBFILE
//#include "DbFile.h"
//void testDbFile(){
//	File* file=new CFile();
//	file->open("F:\\weijunbao\\a.txt");
//
//}
//#endif
//
////#define TEST_DIR
//#ifdef TEST_DIR
//#include "Directory.h"
//void testDir(){
//	Directory::createDirectory("F:\\weijunbao\\a.txt");
//}
//#endif
//
////#define TEST_LOGGER
//#ifdef TEST_LOGGER
//#include "Logger.h"
//#include "DbFile.h"
//void testLogger(){
//	File* file=new CFile();
//	Logger* log=new FileLogger("F:\\weijunbao\\log",file);
//	for(int i=0;i<1000;i++){
//		char buffer[65]={'\0'};
//		log->write("test log one  aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
//		itoa(i,buffer,10);
//		log->write(buffer);
//		log->write("\n");
//	}
//}
//#endif
//
////#define TEST_BYTEORDER
//#ifdef TEST_BYTEORDER
//#include "ByteOrder.h"
//void testByteOrder(){
//	ByteOrder::checkEndian();
//	cout << ByteOrder::IS_BIG_ENDIAN << endl;
//}
//#endif
int main(int argc, char *argv[])
{
	int i;
	//testDbFile();
	//testDir();
	//testLogger();
	test();
	//testEndian();

	//testByteOrder();
	
	cin >> i;
	/*test t;
	HashSet<test>* i=new HashSet<test>();
	i->add(t);*/
	return 1;
}