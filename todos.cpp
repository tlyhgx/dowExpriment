





//TODO:历史数据浏览时，滚轮缩放根据数据量调整大小


//TODO:程序打开时，先跳出确认窗口，保证正常读取modbus
//TODO:工作状态不能自己给定，要从PLC读取，若此时设置停止时，必须要从PLC读取到已停止的状态
//TODO:退出时，先输出停止系统，再延时，--退出，好像有问题，最好要确认停止后再退出,退出时，用了WLILE,如果再点击会有问题

//TODO:初始化，采集的数据先初始化，这样3个温度使用5温度时，其它两个就可以为零

//TODO:重新创建数据库，若数据库不存在，则重新建立，并创建新表单，设置默认数据

//TODO:要有开始动作，才报警
//TODO:工作中和未工作用返回的值确定,到底要不要这样处理？

//NOTE:所有设置都放到dowInit
//FIXME:退出时，记得把modbus断开
//TODO:后期要谁登录，直接记录谁的名字，而不是主界面还要记录

//TODO:数据量太大时，怎么清理

//TODO:参数如果不合适，则提醒范围


