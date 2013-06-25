#ifndef const_h
#define const_h

#define MAX_KEY_SIZE (30)					//系统支持的最大key
#define MAX_VALUE_SIZE (4*1024)		//系统支持的最大value
#define MAX_PAGE_NO  (2^32)				//最大页数
#define MAX_ROWS_PER_PAGE					//
#define MIN_ROWS_PER_PAGE (2)
#define MIN_VALUE_SIZE (10) //overflow 时用
#define MIN_DATA_ROW_SIZE (1+1+1+1)//一个最小的DataRow(key=1,value=1)占用的空间

#define PAGE_FREE_SPACE (20)

#define DEFAULT_ROOT_PAGE_NO (1)	//默认的root page number
#define DEFAULT_PAGE_SIZE (4*1024)//默认页大小
#define PAGE_NO_SIZE (4)					//PageNo 落到磁盘上所占的空间
#define PAGE_TYPE_SIZE (1)
#define DEFAULT_PAGE_FREE_SPACE (DEFAULT_PAGE_SIZE - PAGE_NO_SIZE*2 -PAGE_TYPE_SIZE)

#define DEFAULT_KEY_SIZE_DISK (1) //key 落到磁盘上占的空间

#define PAGE_OP_SPLIT 0x00
#define PAGE_OP_MERGE 0x01


#define BALANCE_LIMIT DEFAULT_PAGE_FREE_SPACE -20 //balance 临界点


enum ErrorMessage{
	MEMORY,
	READ_PAGE_ERROR,
	PAGE_TYPE_ERROR,
};
#define DEFAULT_PAGE_TEXT ("weijunbao")
#define DB_EXT (".db")
#define DB_NAME ("btree")
#endif