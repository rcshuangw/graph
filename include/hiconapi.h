#ifndef HICONAPI_H
#define HICONAPI_H


//图元类型
//#define TEMPLATE_TYPE_NORMAL  0x64 //普通类
//#define TEMPLATE_TYPE_MEASURE 0x65 //测点类
//#define TEMPLATE_TYPE_OTHER   0x66 //其他类

#define TEMPLATE_TYPE_NULL            0x00
#define TEMPLATE_TYPE_DIGITAL         0x01 //遥信
#define TEMPLATE_TYPE_ANALOGUE        0x02 //遥测
#define TEMPLATE_TYPE_RELAY           0x03 //遥控 TEMPLATE_TYPE_YK
#define TEMPLATE_TYPE_PLUSE           0x04 //遥脉
#define TEMPLATE_TYPE_TAP             0x05 // 档位
#define TEMPLATE_TYPE_LIGHT           0x06 //光字牌
#define TEMPLATE_TYPE_JDPAI           0x07 //接地牌
#define TEMPLATE_TYPE_CONTROL         0x08 //控制点
//#define TEMPLATE_TYPE_NORMAL            0x09 //普通图符
#define TEMPLATE_TYPE_TRANSFORMER2      0x0A //两卷变
#define TEMPLATE_TYPE_TRANSFORMER3      0x0B //三卷变
#define TEMPLATE_TYPE_GENERATOR         0x0C//发电机
#define TEMPLATE_TYPE_CAPACITOR         0x0D //电容器
#define TEMPLATE_TYPE_OTHERDEVICE       0x0E //其他设备(消弧线圈)
#define TEMPLATE_TYPE_PT                0x0F //电压互感器
#define TEMPLATE_TYPE_CT                0x10 //电流互感器
#define TEMPLATE_TYPE_ARRESTER          0x11 //避雷器
#define TEMPLATE_TYPE_REACTOR           0x12//容抗器
#define TEMPLATE_TYPE_OTHER             0x13 //其他
#define TEMPLATE_TYPE_MAX            0x14

//具体某一个图元
#define TEMPLATE_TYPE_CHILD 0x20




//定义设备类型元素
#define DEVICE_TYPE_ICONSYMBOL 500

//定义icon的元素的类型
#define OBJ_TYPE_NULL 1000
#define OBJ_TYPE_LINE 1001  //直线
#define OBJ_TYPE_RECTANGLE 1002 //矩形
#define OBJ_TYPE_SOLID_RECTANGLE 1003 //实矩形
#define OBJ_TYPE_ELLIPSE 1004 //椭圆
#define OBJ_TYPE_SOLID_ELLIPSE 1005 //实椭圆
#define OBJ_TYPE_ARC  1006//弧
#define OBJ_TYPE_PIE   1007//饼型


//定义绘制icon工具的类型
#define TOOL_TYPE_NULL  0
#define TOOL_TYPE_LINE  1
#define TOOL_TYPE_RECTANGLE 2
#define TOOL_TYPE_SOLID_RECT 3
#define TOOL_TYPE_ELLIPSE 4
#define TOOL_TYPE_SOLID_ELLIPSE 5
#define TOOL_TYPE_ARC 6
#define TOOL_TYPE_PIE 7


//定义绘制编辑状态
#define SELECTING_STATE 0x100
#define RESELECT_STATE 0x101
#define CREATE_STATE 0x102


#define LEFTMARGIN 10
#define TOPMARGIN 10
#define SYMBOLWIDTH 200
#define SYMBOLHEIGHT 200
#define BROWERWIDTH 100
#define BROWERHEIGHT 100

#define PI 3.14

enum DrawShape
{
    //Selection, //选择模式
    //enumMulSelection,

    //绘制对象
	No,
    Line,
    Rectangle,
    Ellipse,
    Arc,
    Polygon,
    Polyline,
    Circle,
    Text,
    Group,
    Container,
    Icon,
    TempContainer
};

//选择状态
enum SELECTMODE
{
    None,
    Select, //选择对象
    Move,   //移动对象
    Size,   //改变对象
};

//填充方向
#define DIRECT_NULL          0x00 //无方向
#define DIRECT_BOTTOM_TO_TOP 100 //由底到顶
#define DIRECT_TOP_TO_BOTTOM 101 //有顶到底
#define DIRECT_LEFT_TO_RIGHT 102 //由左到右
#define DIRECT_RIGHT_TO_LEFT 103 //由左到右
#define DIRECT_VER_TO_OUT    104 //垂直到外
#define DIRECT_HORi_TO_OUT   105 //水平向外
#define DIRECT_VER_TO_IN     106 //垂直向里
#define DIRECT_HORI_TO_IN    107 //垂直向里

//文字布局
#define LAYOUT_TEXT_NULL 00
#define LAYOUT_TEXT_FULL 01
#define LAYOUT_TEXT_VERTICAL 02
#define LAYOUT_TEXT_HORIZON 03

//数字小数点后缀 遥测图元
#define TEXT_NO_POINT    0x01 //无小数点
#define TEXT_ONE_POINT   0x02 //1位小数点
#define TEXT_TWO_POINT   0x03 //2位小数点
#define TEXT_THREE_POINT 0x04 //3位小数点


//画面操作方式
#define MODE_OPEN_GRAPH     0x01
#define MODE_OPERATOR_GRAPH 0x02
#define MODE_RELAY_CONTROL  0x03

//画面确认方式
#define COMFIRM_MODE_STATION 0x01
#define COMFIRM_MODE_GRAPH   0x02

//工具栏状态变化
#define SELECT_MODE_NO        00
#define SELECT_MODE_SINGLE    01
#define SELECT_MODE_2MULTIPLE 02
#define SELECT_MODE_MULTIPLE  03

//graphEditor中多选返回的对象
#define TYPE_SELECT_NONE     0x00 //没有选择到
#define TYPE_SELECT_SINGLE   0x01 //1个选择
#define TYPE_SELECT_MULTIPLE 0x02 //多个选择

//定义图元大小关系
enum IconSize
{
	EqualWidth, //等宽
	EqualHeight, //等高
	EqualComplete, //完全相等
	HEqualSpace, //横向等分间距
	VEqualSpace //纵向等分间距
};

//定义旋转方向
enum IconFlip
{
    LeftFlip90,
    RightFlip90,
    HorizonFlip,
    VerticalFlip,
};

#endif // ICONAPI_H
