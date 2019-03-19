#ifndef HNAMESPACE_H
#define HNAMESPACE_H
#include <QtGlobal>
#include <QFlags>

//环境变量
#define SYSENVIRONMENTVAR "wfsystem_dir"

//回调函数的参数类型
typedef unsigned int HWPARAM;
#if defined(WIN32) || defined(_WIN32)
#if defined(_WIN64)
    typedef qlonglong HLPARAM; //WIN32平台
#else
    typedef long HLPARAM;
#endif
#else
    typedef qlonglong HLPARAM; //统一64位平台
#endif

//权限属性定义
class HPrivis
{
public:
    //权限
    enum privi
    {
        PeopleManagerPrivi          = 0x00000001L, //人员权限管理
        ConfigureToolPrivi          = 0x00000002L, //五防组态
        GraphEditorPrivi            = 0x00000004L, //画面编辑
        SystemSetPrivi              = 0x00000008L, //系统设置
        ManualSetPrivi              = 0x00000010L, //人工设置
        GroupOnOffPrivi             = 0x00000020L, //间隔五防投退
        OperTicketBrowserPrivi      = 0x00000040L, //操作票浏览
        OperTicketEditorPrivi       = 0x00000080L, //操作票编辑
        OperTicketDeletePrivi       = 0x00000100L, //操作票删除
        OperTicketCancelPrivi       = 0x00000200,  //操作票取消
        OperTicketRunPrivi          = 0x00000400L, //操作票执行
        OperTicketGuardPrivi        = 0x00000800L, //操作票监护
        ModelTicketToRunPrivi       = 0x00001000L, //模板票转执行
        TempTicketToRunPrivi        = 0x00002000L, //临时票或者编辑票转执行
        WorkTicketManagerPrivi      = 0x00004000L, //操作票(工作票)管理
        WorkTicketModelManagerPrivi = 0x00008000L, //工作票(操作票)模板管理
        GiveOrderPrivi              = 0x00010000L, //下令人
        PrepareOrderPrivi           = 0x00020000L, //预令人
        DutyManagerPrivi            = 0x00040000L, //值班负责人
        DutyLeaderPrivi             = 0x00080000L, //值长
        PrintSetPrivi               = 0x00100000L, //打印设置
        SystemLoginPrivi            = 0x01000000L, //系统登录
        SystemExitPrivi             = 0x02000000L,  //系统退出

        AllPrivi  =  PeopleManagerPrivi | ConfigureToolPrivi | GraphEditorPrivi | SystemSetPrivi |  \
        ManualSetPrivi | GroupOnOffPrivi | OperTicketBrowserPrivi | OperTicketEditorPrivi | OperTicketDeletePrivi | \
        OperTicketCancelPrivi | OperTicketRunPrivi | OperTicketGuardPrivi | ModelTicketToRunPrivi | TempTicketToRunPrivi | \
        WorkTicketManagerPrivi | WorkTicketModelManagerPrivi | GiveOrderPrivi | PrepareOrderPrivi | PrintSetPrivi | \
        DutyManagerPrivi | DutyLeaderPrivi | SystemLoginPrivi | SystemExitPrivi,

        defaulPrivi = ConfigureToolPrivi | GraphEditorPrivi | SystemSetPrivi |  \
        ManualSetPrivi | GroupOnOffPrivi | OperTicketBrowserPrivi | OperTicketEditorPrivi | \
        WorkTicketManagerPrivi | WorkTicketModelManagerPrivi | SystemLoginPrivi | SystemExitPrivi

    };
    Q_DECLARE_FLAGS(privis,privi)
};
Q_DECLARE_OPERATORS_FOR_FLAGS(HPrivis::privis)

class HFlags
{
public:
    enum enableflag
    {
        //操作标志
        EnableAbs         = ((ushort)0x0001), //模拟量 绝对值
        EnableIne         = ((ushort)0x0001), //数字量 取反
        EnableSetpoint    = ((ushort)0x0002), //模拟量 遥调允许
        EnableRelay       = ((ushort)0x0002), //数字量 遥控允许
        EnableWarnning    = ((ushort)0x0004), //模拟量 越限告警
        EnableChange      = ((ushort)0x0004), //数字量 变位告警
        EnableSound       = ((ushort)0x0008), //语音告警
        EnableFormula     = ((ushort)0x0010), //计算点
        EnableRepair      = ((ushort)0x0020), //数字量 检修
        EnableScan        = ((ushort)0x0040), //扫描

        EnableAnalogue    = (EnableAbs | EnableSetpoint | EnableWarnning | EnableSound | EnableFormula | EnableScan),
        EnableDigital     = (EnableIne | EnableRelay | EnableChange | EnableSound | EnableRepair | EnableFormula | EnableScan),
    };
    Q_DECLARE_FLAGS(enableflags,enableflag)

    enum resultflag
    {
       //结果标志
       ResultManual       = ((ushort)0x0001), //人工置数
       ResultAck          = ((ushort)0x0002), //确认
       ResultWarningHI    = ((ushort)0x0004), //模拟量 越上限
       ResultWarningLO    = ((ushort)0x0008), //数字量 越下线
       ResultStop         = ((ushort)0x00010), //无效值
       ResultChange       = ((ushort)0x0004), //数字量 正常变位
       ResultAccident     = ((ushort)0x0008) //数字量 事故变位
    };
    Q_DECLARE_FLAGS(resultflags,resultflag)
};
Q_DECLARE_OPERATORS_FOR_FLAGS(HFlags::enableflags)
Q_DECLARE_OPERATORS_FOR_FLAGS(HFlags::resultflags)


class HVarFlags
{
public:
    //权限
    enum varflag
    {
        VarNoFlag        =  0x01,
        //任务
        varStName			= 1,	//厂站名称
        varSheetNo			= 2,	//操作票号
        varSheetTitle			= 3,	//操作票标题
        varSheetDescribe                = 4,	//任务描述
        varOrderNo      	        = 5,	//调度指令号
        varSheetType		        = 6,	//操作票类型(模板票、预开票)
        varTaskType 		        = 7,	//任务类型(送电、停电，其它)
        varOpStepNum			= 8,	//操作总步数
        varSheetPageNum			= 9,	//页数
        varSheetPageNo			= 10,	//页号
        varPrintInput		        = 11,	//打印输入
        varSheetPrevPage	        = 12,	//接上页
        varSheetNextPage		= 13,	//接下页
        //人
        varOperator    		        = 20,	//操作人
        varGuardian			= 21,	//监护人
        //FRONT_TYPE_ORDER			= 22,	//下令人
        //FRONT_TYPE_PREORDER		= 23,	//预令人
        //FRONT_TYPE_DUTY   		= 24,	//值班责任人
        //FRONT_TYPE_DUTYLEADER		= 25,	//值长
        varEditor   		        = 26,	//操作票生成（保存）人
        //时间
        varStartTime		        = 40,	//操作开始时间,不用
        //FRONT_TYPE_ORDERTIME		= 41,	//下令时间
        //FRONT_TYPE_PREORDERTIME	= 42,	//预令时间
        varSheetStepTime	        = 43,	//每步操作时间
        varSheetMakeTime		= 44,	//操作票生成时间
        varNowTime			= 45,	//当前时间
        varSheetEneTime			= 46,	//操作结束时间,不用
        varSheetStepHour		= 47,	//每步操作时间(时)
        varSheetStepMin		        = 48,	//每步操作时间(分)
        //内容
        varSheetStepNo			= 60,	//操作序号
        varSheetStep			= 61,	//操作项目
        varSheetRemark			= 62,   //操作备注
        varSheetStepType		= 63,	//操作类型(分操作、合操作、提示操作)
        varSheetLockType                = 64,   //锁类型
        varLockNO	                = 65,   //锁号
        varOperatTeamNo			= 66,	//班次
        varStateChange		        = 67,	//状态转换
        varLastSheetNo		        = 68,	//上接票号
        varNextSheetNo		        = 69,	//下接票号
        varSheetEndDesc		        = 70,	//结束语
        varBitmap			= 71,
        varTextEdit			= 72,
        varDeivceState			= 73,
        varSheetOperatrNo               = 74,
        varRunningNo                    = 75,
        varDate                         = 76,
    };
    Q_DECLARE_FLAGS(varflags,varflag)
};
Q_DECLARE_OPERATORS_FOR_FLAGS(HVarFlags::varflags)
/*


//标志
#define ENABLE_ABS         ((ushort)0x0001) //模拟量 绝对值
#define ENABLE_INE         ((ushort)0x0001) //数字量 取反
#define ENABLE_SETPOINT    ((ushort)0x0002) //模拟量 遥调允许
#define ENABLE_RELAY       ((ushort)0x0002) //数字量 遥控允许
#define ENABLE_WARNING     ((ushort)0x0004) //模拟量 越限告警
#define ENABLE_CHANGE      ((ushort)0x0004) //数字量 变位告警
#define ENABLE_SOUND       ((ushort)0x0008) //语音告警
#define ENABLE_FORMULA     ((ushort)0x0010) //计算点
#define ENABLE_REPAIR      ((ushort)0x0020) //数字量 检修
#define ENABLE_SCAN        ((ushort)0x0040) //扫描

#define ENABLE_ANALOGUE  (ENABLE_ABS | ENABLE_SETPOINT | ENABLE_WARNING | ENABLE_SOUND | ENABLE_FORMULA | ENABLE_SCAN)
#define ENABLE_DIGITAL   (ENABLE_INE | ENABLE_RELAY | ENABLE_CHANGE | ENABLE_SOUND | ENABLE_REPAIR | ENABLE_FORMULA | ENABLE_SCAN)

//结果
#define RESULT_MANUAL      ((ushort)0x0001) //人工置数
#define RESULT_ACK         ((ushort)0x0002) //确认
#define ENABLE_WARNINGHI   ((ushort)0x0004) //模拟量 越上限
#define ENABLE_WARNINGLO   ((ushort)0x0008) //数字量 越下线
#define ENABLE_STOP        ((ushort)0x00010) //无效值
#define RESULT_CHANGE      ((ushort)0x0004) //数字量 正常变位
#define ENABLE_ACCIDENT    ((ushort)0x0008) //数字量 事故变位
*/
#endif
