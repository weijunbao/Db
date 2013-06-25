#ifndef const_h
#define const_h

#define MAX_KEY_SIZE (30)					//ϵͳ֧�ֵ����key
#define MAX_VALUE_SIZE (4*1024)		//ϵͳ֧�ֵ����value
#define MAX_PAGE_NO  (2^32)				//���ҳ��
#define MAX_ROWS_PER_PAGE					//
#define MIN_ROWS_PER_PAGE (2)
#define MIN_VALUE_SIZE (10) //overflow ʱ��
#define MIN_DATA_ROW_SIZE (1+1+1+1)//һ����С��DataRow(key=1,value=1)ռ�õĿռ�

#define PAGE_FREE_SPACE (20)

#define DEFAULT_ROOT_PAGE_NO (1)	//Ĭ�ϵ�root page number
#define DEFAULT_PAGE_SIZE (4*1024)//Ĭ��ҳ��С
#define PAGE_NO_SIZE (4)					//PageNo �䵽��������ռ�Ŀռ�
#define PAGE_TYPE_SIZE (1)
#define DEFAULT_PAGE_FREE_SPACE (DEFAULT_PAGE_SIZE - PAGE_NO_SIZE*2 -PAGE_TYPE_SIZE)

#define DEFAULT_KEY_SIZE_DISK (1) //key �䵽������ռ�Ŀռ�

#define PAGE_OP_SPLIT 0x00
#define PAGE_OP_MERGE 0x01


#define BALANCE_LIMIT DEFAULT_PAGE_FREE_SPACE -20 //balance �ٽ��


enum ErrorMessage{
	MEMORY,
	READ_PAGE_ERROR,
	PAGE_TYPE_ERROR,
};
#define DEFAULT_PAGE_TEXT ("weijunbao")
#define DB_EXT (".db")
#define DB_NAME ("btree")
#endif