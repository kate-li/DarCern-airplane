/**
  ******************************************************************************
  * @file    CePackage.h
  * @author  Creelinks Application Team
  * @version V1.0.0
  * @date    2017-03-26
  * @brief   适用于CePackage模块的驱动头文件,用于数据的打包拆包操作
  ******************************************************************************
  * @attention
  *
  *1)添加额外参数量，直接CePackageSend和CePackageRecv中添加即可，系统自动计算结构体长度
  *2)添加的变量一定为int32，否则会出现无法预测的故障
  *
  * <h2><center>&copy; COPYRIGHT 2016 Darcern</center></h2>
  ******************************************************************************
  */
#ifndef __CE_PACKAGE_H__
#define __CE_PACKAGE_H__
#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus
#include "Creelinks.h"

#define  CE_PACKAGE_PACK_SIZE   32                  /*!< 蓝牙，wifi等数据传输模块发送一次包的长度，建议32byte，因为NRF24L01+发送一次包长度就是32个字节*/

#define CE_PACKAGE_SEND_BUF_SIZE (CE_PACKAGE_PACK_SIZE * ((sizeof(CePackageSend)/sizeof(int32))*4/(CE_PACKAGE_PACK_SIZE-4) + (((sizeof(CePackageSend)/sizeof(int32))*4)%(CE_PACKAGE_PACK_SIZE-4) == 0 ?0:1)))   /*!< 根据发送结构体中的参数个数和包头等信息，计算出发送缓存长度*/
#define CE_PACKAGE_RECV_BUF_SIZE (CE_PACKAGE_PACK_SIZE * ((sizeof(CePackageRecv)/sizeof(int32))*4/(CE_PACKAGE_PACK_SIZE-4) + (((sizeof(CePackageRecv)/sizeof(int32))*4)%(CE_PACKAGE_PACK_SIZE-4) == 0 ?0:1)))   /*!< 根据接收结构体中的参数个数和包头等信息，计算出接收缓存长度*/

/**
  * @brief  结构体，需要发送给控制端的数据
  */
typedef struct 
{
    /*V2.0版本*******************************/
    int32 pitchByFilter;            /*!< 将加速度和角速度直接解算出的姿态角进行融合后，最终获得的姿态角Pitch*/
    int32 rollByFilter;             /*!< 将加速度和角速度直接解算出的姿态角进行融合后，最终获得的姿态角Roll*/
    int32 yawByFilter;              /*!< 将加速度和角速度直接解算出的姿态角进行融合后，最终获得的姿态角Yaw*/

    int32 temperature;              /*!< 温度值*/
    int32 altitude;                 /*!< 海拔高度*/
    int32 batVoltage;               /*!< 当前电池的电压值，示经过DC-DC电路，直接对锂电池进行测量*/

    int32 accelerator;              /*!< 无人机当前油门强度0~1000，遥控器油门经过阻尼处理后的结果*/    
    int32 pressure;                 /*!< 气压值*/

    int32 driverPower0;             /*!< 四个电机当前的驱动强度，0~1000*/
    int32 driverPower1;
    int32 driverPower2;
    int32 driverPower3;

    int32 accX;                     /*!< 未滤波的当前加速度数据*/
    int32 accXByFilter;             /*!< 经过滤波后的加速度数据，可使用地面站观察滤波效果*/    
    int32 accY;
    int32 accYByFilter;        
    int32 accZ;
    int32 accZByFilter;            
    int32 gyrX;                     /*!< 未滤波的当前角速度数据*/
    int32 gyrXByFilter;             /*!< 经过校正后的加速度数据，可使用地面站观察滤波效果*/    
    int32 gyrY;
    int32 gyrYByFilter;            
    int32 gyrZ;
    int32 gyrZByFilter;        

    int32 pitchByAcc;               /*!< 由加速度直接解算出的姿态角Pitch*/
    int32 pitchByGyr;               /*!< 由角速度直接解算出的姿态角Pitch*/
    int32 rollByAcc;                /*!< 由加速度直接解算出的姿态角Roll*/
    int32 rollByGyr;                /*!< 由角速度直接解算出的姿态角Roll*/
    int32 yawByAcc;                 /*!< 由加速度直接解算出的姿态角Yaw*/
    int32 yawByGyr;                 /*!< 由角速度直接解算出的姿态角Yaw*/
    /*V3.0版本*******************************/

}CePackageSend;

typedef struct 
{
    int32 leftX;                    /*!< 摇控器/控制器左摇杆X值，－1000~+1000*/
    int32 leftY;                    /*!< 摇控器/控制器左摇杆Y值，－1000~+1000*/
    int32 rightX;                   /*!< 摇控器/控制器右摇杆X值，－1000~+1000*/
    int32 rightY;                   /*!< 摇控器/控制器右摇杆Y值，－1000~+1000*/

    int32 status;                   /*!< 状态控制，每个bit含义见此文件宏定义*/               

    int32 outPitchP;                /*!< 通过地面站点调整无人机PID参数时，发送的参数*/
    int32 outPitchI;
    int32 outPitchD;
    int32 inPitchP;
    int32 inPitchI;
    int32 inPitchD;

    int32 outRollP;
    int32 outRollI;
    int32 outRollD;
    int32 inRollP;
    int32 inRollI;
    int32 inRollD;

    int32 outYawP;
    int32 outYawI;
    int32 outYawD;
    int32 inYawP;
    int32 inYawI;
    int32 inYawD;

    int32 yijieK1;                   /*!< 通过地面站点调整无人机滤波参数时，发送的参数*/
    int32 erjieK2;

    int32 imuKp;
    int32 imuKi;

    int32 filterR_angle;
    int32 filterQ_angle;
    int32 filterQ_gyro;

    int32 driverPower0Zero;         /*!< 用于校准四个电机*/
    int32 driverPower1Zero;
    int32 driverPower2Zero;
    int32 driverPower3Zero;

    int32 altKp;
    int32 altKi;
    int32 altKd;
    int32 altBase;

    int32 zeroPitch;
    int32 zeroRoll;
    int32 zeroYaw;
}CePackageRecv;

/*
 *CePackage操作对像
 */
typedef struct
{

    CE_STATUS   (*initial)(void);                                   /*!< @brief cePackageSend模块初始化，对结构体中的数据进行清0操作*/


    uint8*      (*dealSend)(void);                                  /*!< @brief 对cePackageSend结构体进行打包，反回打包后可直接发送byte数组
                                                                         @param cePackageSend:CePackageSend属性对象指针
                                                                         @return 打包后可直接发送的byte数组，长度为CE_PACKAGE_SEND_BUF_SIZE*/

    CE_STATUS   (*dealRecv)( uint8* recvBuf,uint16 recvCount); /*!< 
                                                                         @brief 对recvBuf中的数据进行拆包解析处理，解析后的结果更新到结构体cePackageRecv
                                                                         @param cePackageRecv:CePackageRecv属性对象指针
                                                                         @param recvBuf:接收数据缓存地址
                                                                         @param recvCount:接收数据缓存长度
                                                                         @return 返回CE_STATUS_SUCCESS则解析成功，否则失败*/

}CePackageOp;
/*
 *CePackage操作对象实例
 */
extern const CePackageOp cePackageOp;
extern CePackageSend cePackageSend;
extern CePackageRecv cePackageRecv;
#ifdef __cplusplus
 }
#endif //__cplusplus
#endif //__CE_PACKAGEH__

