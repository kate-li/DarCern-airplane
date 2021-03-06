/**
  ******************************************************************************
  * @file    Ce8Segx8.h
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-01-06
  * @brief   适用于Ce8Segx8模块的驱动头文件
  ******************************************************************************
  * @attention
  *
  *1)
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#ifndef __CE_8SEG_X8_H__
#define __CE_8SEG_X8_H__
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
#include "Creelinks.h"
#define __CE_8SEG_X8_VERSION__ 1                                        /*!< 此驱动文件的版本号*/
#define __CE_8SEG_X8_NEED_CREELINKS_VERSION__ 1                         /*!< 需要Creelinks平台库的最低版本*/
#if (__CE_CREELINKS_VERSION__ < __CE_8SEG_X8_NEED_CREELINKS_VERSION__)  /*!< 检查Creelinks平台库的版本是否满足要求*/
#error "驱动文件Ce8Segx8.h需要高于1.0以上版本的Creelink库，请登陆www.creelinks.com下载最新版本的Creelinks库。"
#else
/*
 *Ce8Segx8属性对像
 */
typedef struct
{
    CeTg        ceTg;                                                   /*!< 模块使用到的Tg资源属性对象*/
    uint8       showValBit[8];                                          /*!< 数码管的状态数组*/
    uint8       nowBit;                                                 /*!< 当前刷新的码段*/
}Ce8Segx8;
/*
 *Ce8Segx8操作对像
 */
typedef struct
{
    CE_STATUS   (*initialByGpio)(Ce8Segx8* ce8Segx8,CE_RESOURCE ceGpio0,CE_RESOURCE ceGpio1, CE_RESOURCE ceGpio2);/*!<
                                                                             @brief Ce8Segx8模块使用三个Gpio口来完成初始化
                                                                             @param ce8Segx8:Ce8Segx8属性对象指针
                                                                             @param ceGpio0:Ce8Segx8模块使用的第一个Gpio口资源号
                                                                             @param ceGpio1:Ce8Segx8模块使用的第二个Gpio口资源号
                                                                             @param ceGpio2:Ce8Segx8模块使用的第三个Gpio口资源号*/


    CE_STATUS   (*initialByTg)(Ce8Segx8* ce8Segx8, CE_RESOURCE ceTg);   /*!< @brief Ce8Segx8模块使用Tg来完成初始化
                                                                             @param ce8Segx8:Ce8Segx8属性对象指针
                                                                             @param ceTg:Ce8Segx8模块使用的资源号*/

    void        (*setOn)(Ce8Segx8* ce8Segx8);                           /*!< @brief 使模块处于开启显示状态
                                                                             @param ce8Segx8:Ce8Segx8属性对象指针*/

    void        (*setVal)(Ce8Segx8* ce8Segx8, fp32 val);                /*!< @brief 显示数值
                                                                             @param ce8Segx8:Ce8Segx8属性对象指针
                                                                             @param val:需要显示的值*/

    void        (*setChars)(Ce8Segx8* ce8Segx8, char* msg);             /*!< @brief 显示字符串
                                                                             @param ce8Segx8:Ce8Segx8属性对象指针
                                                                             @param msg:需要显示的字符串*/

    void        (*setOff)(Ce8Segx8* ce8Segx8);                          /*!< @brief 使模块处于关闭显示状态
                                                                             @param ce8Segx8:Ce8Segx8属性对象指针*/

}Ce8Segx8Op;
/*
 *Ce8Segx8操作对象实例
 */
extern const Ce8Segx8Op ce8Segx8Op;

#endif //(__CE_CREELINKS_VERSION__ < __CE_8SEG_X8_NEED_CREELINKS_VERSION__)
#ifdef __cplusplus
 }
#endif //__cplusplus
#endif //__CE_8SEG_X8_H__
/**
******************************************************************************
* @brief  使用流程及示例程序(基于前后台非操作系统环境) 
* @function 以0.1增加显示数值
******************************************************************************
#include "Creelinks.h"
#include "Ce8Segx8.h"
fp32 i=0;
Ce8Segx8 mySeg;                                 //定义Ce8Segx8属性对象
int main(void)
{
    ceSystemOp.initial();                       //Creelinks环境初始化
    ceDebugOp.initial(R9Uart);                  //通过Uart串口输出Debug信息到上位机
    //TODO:请在此处插入模块初始化等操作
    ce8Segx8Op.initialByTg(&mySeg, R2TI2c);     //使用资源号R2TI2c初始化mySeg
    ce8Segx8Op.setOn(&mySeg);                   //开始显示
    while (1)
    {
        ceTaskOp.mainTask();                    //Creelinks环境主循环任务，请保证此函数能够被周期调用
        //TODO:请在此处插入用户操
        ce8Segx8Op.setVal(&mySeg, i);           //设置需要显示的值
        i += 0.1;
        ceSystemOp.delayMs(100);
    };
}
******************************************************************************
*/
