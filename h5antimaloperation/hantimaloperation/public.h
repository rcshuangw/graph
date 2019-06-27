#ifndef PUBLIC_H
#define PUBLIC_H
//操作票类型
#define OPSHEET_TYPE_NULL             0
#define OPSHEET_TYPE_TEMP		      1
#define OPSHEET_TYPE_MOBAN      	  2
#define OPSHEET_TYPE_YUKAI	      	  3
#define OPSHEET_TYPE_ZUOFEI	      	  4
#define OPSHEET_TYPE_WANCHENG	      5
#define OPSHEET_TYPE_GUIDANG 	      6
#define OPSHEET_TYPE_MEASURE 	      7

//操作任务类型
#define TASK_TYPE_TINGDIAN          0
#define TASK_TYPE_SONGDIAN     		1
#define TASK_TYPE_JIANXIU	      	2
#define TASK_TYPE_QITA              3

//操作框类型
#define OPEN_TYPE_NULL	            0
#define OPEN_TYPE_EDIT	            1
#define OPEN_TYPE_BROWSE	        2
#define OPEN_TYPE_PREVIEW      		3
#define OPEN_TYPE_REF      			4
#define OPEN_TYPE_REPORT   			5
#define OPEN_TYPE_EXECUTE  			6

//操作票保存类型
#define SAVE_TYPE_NEW		        0
#define SAVE_TYPE_TEMP		        1
#define SAVE_TYPE_MOBAN		        2
#define SAVE_TYPE_SAVEAS	        3
#define SAVE_TYPE_YUKAI		        4
#define SAVE_TYPE_NEWYUKAI          5
#define SAVE_TYPE_MEASURE	        6

//操作票状态
#define OPTAB_STATE_NULL			0
#define OPTAB_STATE_EDIT			1
#define OPTAB_STATE_PREVIEW			2
#define OPTAB_STATE_EXECUTE			3
//mod
#define OPTAB_STATE_SAVED			4

#endif // PUBLIC_H
