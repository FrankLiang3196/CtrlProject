#ifndef USB7660_H
#define USB7660_H

#ifdef USB7KCTRANS_EXPORTS
#define ZT_API __declspec(dllexport)
#else
#define ZT_API __declspec(dllimport)
#endif

//定义错误号
#define ZT_SUCCESS 0  //无错误
#define ERR_PARAMETER1 1 //参数1错
#define ERR_PARAMETER2 2 //参数2错
#define ERR_PARAMETER3 3 //参数3错
#define ERR_PARAMETER4 4 //参数4错
#define ERR_PARAMETER5 5 //参数5错
#define ERR_PARAMETER6 6 //参数6错
#define ERR_PARAMETER7 7 //参数7错
#define ERR_PARAMETER8 8 //参数8错
#define ERR_PARAMETER9 9 //参数9错
#define ERR_PARAMETER10 10 //参数10错
#define ERR_PARAMETER11 11 //参数11错
#define ERR_PARAMETER12 12 //参数12错
#define ERR_PARAMETER13 13 //参数13错
#define ERR_PARAMETER14 14 //参数14错
#define ERR_PARAMETER15 15 //参数15错
#define ERR_PARAMETER16 16 //参数16错
#define ERR_PARAMETER17 17 //参数17错
#define ERR_PARAMETER18 18 //参数18错
#define ERR_PARAMETER19 19 //参数19错
#define ERR_PARAMETER20 20 //参数20错
#define ERR_PARAMETER_BASEADDR 21 //针对ISA卡，板卡基地址超出范围，基地址应该为0x100至0x3F0之间未被系统占用的地址
#define ERR_PARAMETER_CARDNO 22 //针对PCI卡，板卡索引号超出范围，这版驱动中板卡索引号默认从1开始
#define ERR_PARAMETER_CHMODE 23 //通道方式参数错误，通道方式超出范围，一般只有0--3共4种方式
#define ERR_PARAMETER_CH 24 //通道号参数错误，通道号超出范围
#define ERR_PARAMETER_CHIP 25 //芯片号参数错误，芯片号超出范围
#define ERR_PARAMETER_PORT 26 //口号参数错误，口号超出范围
#define ERR_PARAMETER_AI_RANGE 27 //AD量程参数错，此卡不支持这种AD输入量程
#define ERR_PARAMETER_AI_AMP 28 //AD增益参数错
#define ERR_PARAMETER_AI_STARTMODE 29 //AD启动方式参数错
#define ERR_PARAMETER_AO_RANGE 30 //DA量程参数错，此卡不支持这种DA输出量程
#define ERR_PARAMETER_ADFREQ 31 //AD采集频率(或AD分频系数)参数错
#define ERR_PARAMETER_IRQ 32 //与中断相关参数错，可能是此卡不支持这种中断方式或中断号
#define ERR_PARAMETER_NULL_POINTER 33 //空指针错。原因：缓冲区首地址为空或者用户传入的参数导致引用到空指针
#define ERR_AD_OVERTIME 34 //AD超时。对于ISA卡，出错原因可能是：未插卡或IO地址与板卡上设置不匹配。当用定时启动AD或外触发启动AD时，一般不应检查AD是否超时
#define ERR_OPEN_DEVICE 35 //打开设备失败，对于PCI卡，出错原因可能是：未插卡或未装驱动，或dll与sys版本不一致
#define ERR_CLOSE_DEVICE 36 //关闭设备失败
#define ERR_TIMING 37 //定时未到或外触发脉冲未到
#define ERR_IOADDR_DA_OVERTIME 38 //带光隔DA写过程超时
#define ERR_OPEN_IRQ 39 //打开中断出错
#define ERR_FUNC_CANNT_RUN 40 //此函数不能在这台计算机上运行
#define ERR_ASYNC_FUNC_FAILED 41 //异步函数调用失败
#define ERR_FUNC_OPERATE 42 //在当前的卡的设置状态下，不应该调用此函数
#define ERR_EXCHANGE_DATA 43 //与底层驱动之间交换数据出错
#define ERR_CANT_FIND_FIRST_CH 44 //无法找到第一个通道的标志位

extern "C" 
{
ZT_API  long _stdcall ZT7660_GetCardCount();
//函数功能：返回当前可使用的设备数量，注意这个函数必须在打开设备之前调用
//
//入口参数：
//返回值： 大于等于0  当前可使用设备数量
//         -1  表失败，已经调用过ZT7660_OpenDevice函数

ZT_API long _stdcall ZT7660_OpenDevice(unsigned long cardNO);
//函数名称：ZT7660_OpenDevice
//函数功能：打开设备。必须在调用其他函数之前调用。
//          放在程序初始化时调用比较恰当，只调用一次即可
//入口参数：
//          cardNO：模块号，默认从 1 开始
//                    如果系统中只用了一个USB模块，令这个参数为1就行了
//返回值：  0  表成功
//         -1  表失败，应该进一步调用 ZT7660_GetLastErr 判断出错原因
ZT_API long _stdcall ZT7660_CloseDevice(unsigned long cardNO);
//函数名称：ZT7660_CloseDevice
//函数功能：关闭指定的设备
//
//入口参数：
//          cardNO：模块号，默认从 1 开始
//                    如果系统中只用了一个USB模块，令这个参数为1就行了
//返回值：  0  表成功
//         -1  表失败，应该进一步调用 ZT7660_GetLastErr 判断出错原因
ZT_API unsigned long _stdcall ZT7660_GetLastErr();
//函数名称：ZT7660_GetLastErr
//函数功能：得到当前错误号。如果错误号为0表示无错误
//返回值：错误代码，错误代码含义请看宏定义
ZT_API void _stdcall ZT7660_ClearLastErr();
//函数名称：ZT7660_ClearLastErr
//函数功能：清除错误号。
//          注意：一旦产生错误，为了使函数重新正常执行，必须清除错误号
//返回值：无
ZT_API void _stdcall ZT7660_SetBaseNO(unsigned long baseNO);
//函数名称：ZT7660_SetBaseNO
//函数功能：设置板卡索引号(cardNO)，芯片号(chipNO)，口号(portNO)和通道号(chNO)，
//          总之带“NO”后缀的参数是从0开始还是从1开始。默认为从1开始
//          建议不要调用这个函数
//入口参数：
//          baseNO：只能设为0或1
//返回值：无
ZT_API long _stdcall ZT7660_GetBaseNO();
//函数名称：ZT7660_GetBaseNO
//函数功能：返回当前板卡索引号(cardNO)，芯片号(chipNO)，口号(portNO)和通道号(chNO)，
//          总之带“NO”后缀的参数是从0开始还是从1开始。默认为从1开始
//返回值：返回0  表从0开始
//        返回1  表从1开始
ZT_API long _stdcall ZT7660_AIonce(unsigned long cardNO,
                                   unsigned long chMode,
                                   unsigned long chNO,
                                   unsigned long AIrange,
                                   unsigned long AIAmp,
                                   unsigned long ADstartMode,
                                   unsigned long ADfreq,
                                   unsigned long ABflag,
                                   unsigned long ch1Flag,
                                   unsigned long ADctrlWord,
                                   unsigned long ADoverTime);
//函数名称：ZT7660_AIonce
//函数功能：对指定通道进行单次数据采集。不需要先调用 ZT7660_AIinit
//
//入口参数：
//          cardNO：模块号，默认从 1 开始。有关这个参数的详细说明，请参考 ZT7660_OpenDevice 函数
//          chMode：通道方式
//                    0 = 表示单端，固定单通道方式
//                    2 = 表示双端，固定单通道方式
//            chNO：通道号
//                    当chMode = 0 时，为通道号(1--48)
//                    当chMode = 2 时，为通道号(1--24)
//         AIrange：选择对采集到的AD原码值做何种变换，应该与AD采集量程(一般需跳线)相匹配：
//                    AIrange = 0，表示返回原码值，所有卡都有这种方式。
//                                 对于12位的卡返回 0~4095 之间的值
//                                 对于16位的卡返回 0~65535 之间的值
//                    AIrange = 1，表示把原码值转化为 0 -- 5000mV 之间的值，如果此卡没有这种量程，不应选这种方式
//                    AIrange = 2，表示把原码值转化为 0 -- 10000mV 之间的值，如果此卡没有这种量程，不应选这种方式
//                    AIrange = 5，表示把原码值转化为 -5000 -- 5000mV 之间的值，如果此卡没有这种量程，不应选这种方式
//           AIAmp：程控增益系数(0～2)。
//                    0 = 1倍增益(无增益)；1 = 10倍增益；2 = 100倍增益
//     ADstartMode：保留。保持此参数为0
//          ADfreq：保留。保持此参数为0
//          ABflag：设置模块为A型(12bit)还是B型(16bit)
//                    0 = A型；1 = B型
//         ch1Flag：保留。保持此参数为0
//      ADctrlWord：一般保持此参数为0。
//                    若此参数不为0，函数将直接用这个参数的值初始化AD，而对其他影响AD方式的参数，
//                    例如chMode、AIrange、AIAmp、ABflag、ch1Flag的值不予考虑。
//                    此参数的说明请参考说明书中对 usb7660AI 函数的lCode参数的说明。
//      ADoverTime：保留。保持这个参数为0
//返回值： 不等于 -1，表采集到的AD结果
//             -1   ，当 ZT7660_GetLastErr 返回值等于 0 时，表AD结果
//                    当 ZT7660_GetLastErr 返回值小于 0 时，表失败
ZT_API long _stdcall ZT7660_AIinit(unsigned long cardNO,
                                   unsigned long chMode,
                                   unsigned long chNO,
                                   unsigned long AIrange,
                                   unsigned long AIAmp,
                                   unsigned long ADstartMode,
                                   unsigned long ADfreq,
                                   unsigned long ABflag,
                                   unsigned long ch1Flag,
                                   unsigned long ADctrlWord,
                                   unsigned long ADoverTime);
//函数名称：ZT7660_AIinit
//函数功能：初始化AD
//
//入口参数：
//          cardNO：模块号，默认从 1 开始。有关这个参数的详细说明，请参考 ZT7660_OpenDevice 函数
//          chMode：通道方式
//                    0 = 表示单端，固定单通道方式
//                    1 = 表示单端，多通道扫描方式
//                    2 = 表示双端，固定单通道方式
//                    3 = 表示双端，多通道扫描方式
//            chNO：通道号或多通道循环输出中止通道号
//                    当chMode = 0 时，为通道号(1--48)
//                    当chMode = 1 时，为多通道循环采集中止通道号(1--48)，例如设为2表示，采集的顺序为：通道1,通道2,通道1,通道2......
//                    当chMode = 2 时，为通道号(1--24)
//                    当chMode = 3 时，为多通道循环采集中止通道号(1--24)，例如设为2表示，采集的顺序为：通道1,通道2,通道1,通道2......
//         AIrange：选择对采集到的AD原码值做何种变换，应该与AD采集量程(一般需跳线)相匹配：
//                    AIrange = 0，表示返回原码值，所有卡都有这种方式。
//                                 对于12位的卡返回 0~4095 之间的值
//                                 对于16位的卡返回 0~65535 之间的值
//                    AIrange = 1，表示把原码值转化为 0 -- 5000mV 之间的值，如果此卡没有这种量程，不应选这种方式
//                    AIrange = 2，表示把原码值转化为 0 -- 10000mV 之间的值，如果此卡没有这种量程，不应选这种方式
//                    AIrange = 5，表示把原码值转化为 -5000 -- 5000mV 之间的值，如果此卡没有这种量程，不应选这种方式
//           AIAmp：程控增益系数(0～2)。
//                    0 = 1倍增益(无增益)；1 = 10倍增益；2 = 100倍增益
//     ADstartMode：保留。保持此参数为0
//          ADfreq：指定AD总采样频率
//                    对于USB-7660型, 共有0~4档可供选择：
//                      0 = 1KHz；1 = 10KHz；2 = 25KHz；3 = 50KHz；4 = 75KHz
//                    对于USB-7660A型, 共有0~6档可供选择：
//                      0 = 1KHz；1 = 10KHz；2 = 25KHz；3 = 50KHz；4 = 100KHz；5 = 250KHz；6 = 500KHz
//                    对于USB-7660B型, 共有0~5档可供选择：
//                      0 = 1KHz；1 = 5KHz；2 = 10KHz；3 = 25KHz；4 = 50KHz；5 = 100KHz
//                    注： 这里所设置的是AD总采样频率，如果设置频率为100KHz，
//                         对于1个通道来说，这个通道的采样频率确实为 100KHz；
//                         对于2个通道来说，每个通道的采样频率变为  50KHz；
//                         对于4个通道来说，每个通道的采样频率变为  25KHz；
//                         注意：用户可以通过所选的总采样频率与通道数搭配，得到更接近自己需要的采样频率
//          ABflag：设置模块为A型(12bit)还是B型(16bit)
//                    0 = A型；1 = B型
//         ch1Flag：对于B型(16bit)模块，设置是否返回通道1标志
//      ADctrlWord：一般保持此参数为0。
//                    若此参数不为0，函数将直接用这个参数的值初始化AD，而对其他影响AD方式的参数，
//                    例如chMode、AIAmp、ADstartMode、ADfreq、ABflag、ch1Flag的值不予考虑。
//                    此参数的说明请参考说明书中对 usb7660AIInit 函数的lCode参数的说明。
//      ADoverTime：保留。保持这个参数为0
//返回值：  0  表成功
//         -1  表失败，应该进一步调用 ZT7660_GetLastErr 判断出错原因
ZT_API long _stdcall ZT7660_FifoStatus(unsigned long cardNO);
//函数名称：
//函数功能：读取采集模块上硬件缓冲区(FIFO)的状态
//
//入口参数：
//          cardNO：模块号，默认从 1 开始。有关这个参数的详细说明，请参考 ZT7660_OpenDevice 函数
//
//返回值：  0  表空
//          1  有数未半满
//          3  半满未全满
//          7  全满
//         -1  表失败，应该进一步调用 ZT7660_GetLastErr 判断出错原因
ZT_API long _stdcall ZT7660_ADstop(unsigned long cardNO);
//函数名称：
//函数功能：停止批量采集。采集的硬件时钟停止，不再往FIFO里放数
//
//入口参数：
//          cardNO：模块号，默认从 1 开始。有关这个参数的详细说明，请参考 ZT7660_OpenDevice 函数
//
//返回值：  0  表成功
//         -1  表失败，应该进一步调用 ZT7660_GetLastErr 判断出错原因
ZT_API long _stdcall ZT7660_ClearFifo(unsigned long cardNO);
//函数名称：
//函数功能：清空模块上硬件缓冲区(FIFO)
//
//入口参数：
//          cardNO：模块号，默认从 1 开始。有关这个参数的详细说明，请参考 ZT7660_OpenDevice 函数
//
//返回值：  0  表成功
//         -1  表失败，应该进一步调用 ZT7660_GetLastErr 判断出错原因
ZT_API long _stdcall ZT7660_GetSFifoDataCnt(unsigned long cardNO);
//函数名称：ZT7660_GetSFifoDataCnt
//函数功能：得到驱动缓冲区中数据个数
//
//入口参数：
//          cardNO：模块号，默认从 1 开始。有关这个参数的详细说明，请参考 ZT7660_OpenDevice 函数
//
//返回值：  0  表成功
//         -1  表失败，应该进一步调用 ZT7660_GetLastErr 判断出错原因
ZT_API long _stdcall ZT7660_AIFifo(unsigned long cardNO,
                                   unsigned long packetBytesSize,
                                   unsigned long wantReadCount,
                                   short *pResultArr);
//函数名称：
//函数功能：成批读取AD数据。
//          注意：在调用这个函数之前，应该确保已经调用过 ZT7660_AIinit 函数进行了正确的初始化
//                这个函数已被 ZT7660_AIFifoEx 取代，在此处只处于兼容目的提供此函数。
//入口参数：
//          cardNO：模块号，默认从 1 开始。有关这个参数的详细说明，请参考 ZT7660_OpenDevice 函数
// packetBytesSize：包的大小(字节尺寸)，必须是512的倍数
//   wantReadCount：用户希望读出的数据个数，必须是通道的整数倍，且不能超过用户缓冲区的实际大小
//      pResultArr：用户必须申请一个至少含有 wantReadCount 个 short 型元素的缓冲区，
//                    用于存放采集结果，而 pResultArr 是这个缓冲区的首地址。
//                    
//返回值： 大于等于0  表缓冲区中读到的有效数据的个数
//             -1     表失败，应该进一步调用 ZT7660_GetLastErr 判断出错原因
ZT_API long _stdcall ZT7660_AIFifoEx(unsigned long cardNO,
                                   unsigned long wantReadCount,
                                   short *pResultArr);
//函数功能：成批读取AD数据。
//          注意：在调用这个函数之前，应该确保已经调用过 ZT7660_AIinit 函数进行了正确的初始化
//                并且这个函数不能够和ZT7660_AIFifoCode同时使用，也就是在调用ZT7660_AIinit后，
//                只能固定使用一个函数读取数据。
//入口参数：
//          cardNO：模块号，默认从 1 开始。有关这个参数的详细说明，请参考 ZT7660_OpenDevice 函数
//   wantReadCount：用户希望读出的数据个数，必须是通道的整数倍，且不能超过用户缓冲区的实际大小
//      pResultArr：用户必须申请一个至少含有 wantReadCount 个 short 型元素的缓冲区，
//                    用于存放采集结果，而 pResultArr 是这个缓冲区的首地址。
//                    
//返回值： 大于等于0  表缓冲区中读到的有效数据的个数
//             -1     表失败，应该进一步调用 ZT7660_GetLastErr 判断出错原因
ZT_API long _stdcall ZT7660_AIFifoCode(unsigned long cardNO,
                                       unsigned long wantReadCount,
                                       unsigned short *pResultArr);
//函数功能：成批读取AD源码值。
//          注意：在调用这个函数之前，应该确保已经调用过 ZT7660_AIinit 函数进行了正确的初始化,
//                并且这个函数不能够和ZT7660_AIFifoEx同时使用，也就是在调用ZT7660_AIinit后，
//                只能固定使用一个函数读取数据。
//入口参数：
//          cardNO：模块号，默认从 1 开始。有关这个参数的详细说明，请参考 ZT7660_OpenDevice 函数
//   wantReadCount：用户希望读出的数据个数，必须是通道的整数倍，且不能超过用户缓冲区的实际大小
//出口参数：
//      pResultArr：用户必须申请一个至少含有 wantReadCount 个 unsigned short 型元素的缓冲区，
//                    用于存放采集结果，而 pResultArr 是这个缓冲区的首地址。
//                    
//返回值： 大于等于0  表缓冲区中读到的有效数据的个数
//             -1     表失败，应该进一步调用 ZT7660_GetLastErr 判断出错原因

ZT_API long _stdcall ZT7660_CTStart(unsigned long cardNO,
                                     unsigned long chNO,
                                     unsigned long CTMode,
                                     unsigned long CTinitVal);
//函数名称：
//函数功能：设置指定8253/8254芯片的指定通道的工作方式及计数通道初值
//          注意：从硬件的角度来说，只有当计数脉冲到来时，计数器初值才会被装入
//入口参数：
//          cardNO：模块号，默认从 1 开始。有关这个参数的详细说明，请参考 ZT7660_OpenDevice 函数
//            chNO：通道号：1--3
//          CTMode：通道工作方式：0-5(工作方式只从0开始)
//       CTinitVal：计数通道的初值(0--65535)
//返回值：  0  表成功
//         -1  表失败，应该进一步调用 ZT7660_GetLastErr 判断出错原因
ZT_API long _stdcall ZT7660_CTRead(unsigned long cardNO,
                                    unsigned long chNO,
                                    unsigned long lockBeforeRead);
//函数名称：
//函数功能：读取指定8253/8254芯片的指定计数通道的当前值(减法计数器)
//          此函数不影响计数器的继续计数
//入口参数：
//          cardNO：模块号，默认从 1 开始。有关这个参数的详细说明，请参考 ZT7660_OpenDevice 函数
//            chNO：通道号：1--3
//  lockBeforeRead：保留。设为0即可
//
//返回值：  返回计数器当前值
//          若返回 -1 表示函数调用失败，应该进一步调用 ZT7660_GetLastErr 函数查找出错原因
ZT_API long _stdcall ZT7660_CTStop(unsigned long cardNO,
                                    unsigned long chNO);
//函数名称：
//函数功能：停止指定8253/8254芯片的指定通道工作
//入口参数：
//          cardNO：模块号，默认从 1 开始。有关这个参数的详细说明，请参考 ZT7660_OpenDevice 函数
//            chNO：通道号：1--3
//
//返回值：  0  表成功
//         -1  表失败，应该进一步调用 ZT7660_GetLastErr 判断出错原因
ZT_API long _stdcall ZT7660_CTStopEx(unsigned long cardNO,
                                      unsigned long chNO,
				 	                  unsigned long CTMode);
//函数名称：ZT7660_CTStopEx
//函数功能：停止指定8253/8254芯片的指定通道工作
//入口参数：
//          cardNO：模块号，默认从 1 开始。有关这个参数的详细说明，请参考 ZT7660_OpenDevice 函数
//            chNO：通道号：1--3
//          CTMode：工作方式：0--5
//
//返回值：  0  表成功
//         -1  表失败，应该进一步调用 ZT7660_GetLastErr 判断出错原因


ZT_API long _stdcall ZT7660_DIBit(unsigned long cardNO, unsigned long chNO);
//函数名称：
//函数功能：得到指定通道的开关量输入状态
//入口参数：
//          cardNO：模块号，默认从 1 开始。有关这个参数的详细说明，请参考 ZT7660_OpenDevice 函数
//            chNO：通道号：1--16
//返回值：
//          0 表示低电平
//          1 表示高电平
//         -1 表示调用出错，应该进一步调用 ZT7660_GetLastErr 函数判断出错原因
ZT_API long _stdcall ZT7660_DIAll(unsigned long cardNO);
//函数名称：
//函数功能：得到所有通道的开关量输入状态。
//入口参数：
//          cardNO：模块号，默认从 1 开始。有关这个参数的详细说明，请参考 ZT7660_OpenDevice 函数
//返回值：
//             0     表示所有通道的开关量输入状态为低电平
//           0xFFFF  表示所有通道的开关量输入状态为高电平
//            -1     表示调用出错，应该进一步调用 ZT7660_GetLastErr 函数判断出错原因
ZT_API long _stdcall ZT7660_DOBit(unsigned long cardNO,
							  	   unsigned long chNO,
							 	   unsigned long nState);
//函数名称：
//函数功能：指定某通道的开关量输出状态
//入口参数：
//             cardNO：模块号，默认从 1 开始。有关这个参数的详细说明，请参考 ZT7660_OpenDevice 函数
//               chNO：通道号：1--16
//             nState：指定某通道的开关量输出状态：
//                       nState =    0    ，指定输出低电平
//                       nState = 1(或非0)，指定输出高电平
//返回值：  
//           0      表示成功
//          -1      表示调用出错，应该进一步调用 ZT7660_GetLastErr 函数判断出错原因
ZT_API long _stdcall ZT7660_DOAll(unsigned long cardNO, unsigned long nStateAll);
//函数名称：
//函数功能：指定所有通道的开关量输出状态。
//入口参数：
//          cardNO：模块号，默认从 1 开始。有关这个参数的详细说明，请参考 ZT7660_OpenDevice 函数
//       nStateAll：指定所有通道的开关量输出状态：
//                    nStateAll =   0 ，指定所有通道输出低电平
//                    nStateAll = 0xFFFF，指定所有通道输出高电平
//返回值：   0      表示成功
//          -1      表示调用出错，应该进一步调用 ZT7660_GetLastErr 函数判断出错原因
ZT_API long _stdcall ZT7660N_DIBit(unsigned long cardNO, unsigned long chNO);
//函数名称：ZT7660N_DIBit
//函数功能：得到指定通道的开关量输入状态
//            注意：此函数只针对型号中带N的模块，例如：7660N、7660AN、7660BN等，
//                  型号中带N表示开关量输入输出带光隔
//入口参数：
//          cardNO：模块号，默认从 1 开始。有关这个参数的详细说明，请参考 ZT7660_OpenDevice 函数
//            chNO：通道号：1--16
//返回值：
//          0 表示低电平
//          1 表示高电平
//         -1 表示调用出错，应该进一步调用 ZT7660_GetLastErr 函数判断出错原因
ZT_API long _stdcall ZT7660N_DIAll(unsigned long cardNO);
//函数名称：ZT7660N_DIAll
//函数功能：得到所有通道的开关量输入状态。
//            注意：此函数只针对型号中带N的模块，例如：7660N、7660AN、7660BN等，
//                  型号中带N表示开关量输入输出带光隔
//入口参数：
//          cardNO：模块号，默认从 1 开始。有关这个参数的详细说明，请参考 ZT7660_OpenDevice 函数
//返回值：
//             0     表示所有通道的开关量输入状态为低电平
//           0xFFFF  表示所有通道的开关量输入状态为高电平
//            -1     表示调用出错，应该进一步调用 ZT7660_GetLastErr 函数判断出错原因
ZT_API long _stdcall ZT7660N_DOBit(unsigned long cardNO,
							  	   unsigned long chNO,
							 	   unsigned long nState);
//函数名称：ZT7660N_DOBit
//函数功能：指定某通道的开关量输出状态
//            注意：此函数只针对型号中带N的模块，例如：7660N、7660AN、7660BN等，
//                  型号中带N表示开关量输入输出带光隔
//入口参数：
//          cardNO：模块号，默认从 1 开始。有关这个参数的详细说明，请参考 ZT7660_OpenDevice 函数
//            chNO：通道号：1--16
//          nState：指定某通道的开关量输出状态：
//                    nState =    0    ，指定输出低电平
//                    nState = 1(或非0)，指定输出高电平
//返回值：  
//           0      表示成功
//          -1      表示调用出错，应该进一步调用 ZT7660_GetLastErr 函数判断出错原因
ZT_API long _stdcall ZT7660N_DOAll(unsigned long cardNO, unsigned long nStateAll);
//函数名称：ZT7660N_DOAll
//函数功能：指定所有通道的开关量输出状态。
//            注意：此函数只针对型号中带N的模块，例如：7660N、7660AN、7660BN等，
//                  型号中带N表示开关量输入输出带光隔
//入口参数：
//          cardNO：模块号，默认从 1 开始。有关这个参数的详细说明，请参考 ZT7660_OpenDevice 函数
//       nStateAll：指定所有通道的开关量输出状态：
//                    nStateAll =   0 ，指定所有通道输出低电平
//                    nStateAll = 0xFFFF，指定所有通道输出高电平
//返回值：   0      表示成功
//          -1      表示调用出错，应该进一步调用 ZT7660_GetLastErr 函数判断出错原因
ZT_API long _stdcall ZT7660_AOonce(unsigned long cardNO,
                                    unsigned long chNO,
                                    unsigned long AORange,
                                    long nValue);
//函数名称：
//函数功能：指定某通道模拟量输出一次
//入口参数：
//          cardNO：模块号，默认从 1 开始。有关这个参数的详细说明，请参考 ZT7660_OpenDevice 函数
//            chNO：通道号1--4(通道号默认从1开始)
//         AORange：函数根据这个参数把nValue转化为对应的原码值(0-4095)
//                    之所以要转化，是因为向板卡的相应寄存器写入DA值时，必须是原码值。
//                    为了节省转化的时间，建议用户直接把 nValue 设为原码值。
//                    注意：用户选择的输出范围还必须与硬件跳线相一致!
//                    
//                    AORange = 0，表示 nValue 已经是原码值，不需要转化
//                    AORange = 1，表示 nValue 是 0 -- 5000mV 之间的值，需要转化为原码值
//                                  如果此卡没有这种输出范围，不应选这种方式
//                    AORange = 2，表示 nValue 是 0 -- 10000mV 之间的值，需要转化为原码值
//                                  如果此卡没有这种输出范围，不应选这种方式
//                    AORange = 5，表示 nValue 是 -5000 -- 5000mV 之间的值，需要转化为原码值
//                                  如果此卡没有这种输出范围，不应选这种方式
//                    AORange = 6，表示 nValue 是 -10000 -- 10000mV 之间的值，需要转化为原码值
//                                  如果此卡没有这种输出范围，不应选这种方式
//                    AORange = 10，表示 nValue 是 0 -- 20000uA 之间的值，需要转化为原码值
//                                  如果此卡没有这种输出范围，不应选这种方式
//                    AORange = 11，表示 nValue 是 4000 -- 20000uA 之间的值，需要转化为原码值
//                                  如果此卡没有这种输出范围，不应选这种方式
//          nValue：要输出的值，例如当AORange = 1时，nValue=3000 表示输出3V
//
//返回值：  0  表成功
//         -1  表失败，应该进一步调用 ZT7660_GetLastErr 判断出错原因
ZT_API long _stdcall ZT7660_TransArr(short *pInArr,
									 short *pOutArr,
									 unsigned long dataType,
									 unsigned long chCnt,
									 unsigned long cntPerCh);
//为了在labview中使用方便，加此功能
//dataType = 0，表float ，暂不支持
//dataType = 1，表short

ZT_API long _stdcall CalcEffiVal(short *pInArr,
								 unsigned long chCnt,
                                 unsigned long dataCntPerCh,
								 short *pOutArr);
//函数功能：软件启动AD，采一批数。也需要先调用 ZT7660_AIinit
//入口参数：
//             cardNO：板卡号默认从 1 开始，有关这个参数的详细说明，请参考 ZT7660_OpenDevice 函数
//         pResultArr：用户必须申请一个至少含有 wantReadCount 个 short 型元素的缓冲区，
//                     用于存放采集结果，而 pResultArr 是这个缓冲区的首地址。
//      wantReadCount：用户希望读出的数据个数，必须>0，且不能超过用户缓冲区的实际大小
//                    
//返回值：  大于等于0  表读到的有效数据的个数
//         -1  表失败，应该进一步调用 ZT7660_GetLastErr 判断出错原因

ZT_API long _stdcall ZT7660_SetABFlag(unsigned long cardNO, 
									  unsigned long ABflag );
//函数功能：设置模块为A型(12bit)还是B型(16bit)
//
//入口参数：
//          cardNO：模块号，默认从 1 开始。有关这个参数的详细说明，请参考 ZT7660_OpenDevice 函数
//          ABflag：设置模块为A型(12bit)还是B型(16bit)
//                    0 = A型；1 = B型
//返回值： 大于等于0  表示成功
//         -1  表失败，应该进一步调用 ZT7660_GetLastErr 判断出错原因

ZT_API long _stdcall ZT7660_ADGetMask( unsigned long cardNO, unsigned long abFlag );
//函数功能：返回屏蔽位
//
//入口参数：
//          cardNO：模块号，默认从 1 开始。有关这个参数的详细说明，请参考 ZT7660_OpenDevice 函数
//          ABflag：设置模块为A型(12bit)还是B型(16bit)
//                    0 = A型；1 = B型
//返回值： 大于等于0  表示成功
//         -1  表失败，应该进一步调用 ZT7660_GetLastErr 判断出错原因

ZT_API long _stdcall ZT7660_ADGetMaxCode( unsigned long cardNO, 
                                          unsigned long chNo,
                                          unsigned long rangeInx,
                                          unsigned long abFlag);
//函数功能：返回最大源码值
//
//入口参数：
//          cardNO：模块号，默认从 1 开始。有关这个参数的详细说明，请参考 ZT7660_OpenDevice 函数
//           lChNo：保留，设成0即可
//        lChRange：保留，设成0即可
//          abFlag：指明是A型还是B型，
//                  0,表示A型12位
//                  1,表示B型16位
//返回值： 大于等于0  最大源码值
//         -1  表失败，应该进一步调用 ZT7660_GetLastErr 判断出错原因

ZT_API long _stdcall ZT7660_ADGetMinCode( unsigned long lCardNo,
                                          unsigned long chNo,
                                          unsigned long rangeInx,
                                          unsigned long abFlag);
//函数功能：返回最小源码值
//
//入口参数：
//          cardNO：模块号，默认从 1 开始。有关这个参数的详细说明，请参考 ZT7660_OpenDevice 函数
//           lChNo：保留，设成0即可
//        lChRange：保留，设成0即可
//          abFlag：指明是A型还是B型，
//                  0,表示A型12位
//                  1,表示B型16位
//返回值： 大于等于0  最小源码值
//         -1  表失败，应该进一步调用 ZT7660_GetLastErr 判断出错原因

ZT_API double _stdcall ZT7660_ADGetMaxValue(unsigned long cardNO,
                                            unsigned long chNo,
                                            unsigned long rangeInx,
                                            unsigned long abFlag);
//函数功能：返回指定范围的最大值
//入口参数：
//          cardNO：保留，这里可以是任意值
//            chNo：保留，这里可以使任意值
//        rangeInx：模拟量范围0~11，在这个范围之外的数值将返回源码最大值
//          abFlag：指明是A型还是B型，
//                  0,表示A型12位，这样当rangeInx为0时返回的最大值是4095
//                  1,表示B型16位，这样当rangeInx为0时返回的最大值是65535
//                    
//返回值：指定范围的最大数值

ZT_API double _stdcall ZT7660_ADGetMinValue(unsigned long cardNO,
											unsigned long chNo,
											unsigned long rangeInx,
											unsigned long abFlag);
//函数功能：返回指定范围的最大最小值
//入口参数：
//          cardNO：保留，这里可以是任意值
//            chNo：保留，这里可以使任意值
//        rangeInx：模拟量范围0~11，在这个范围之外的数值将返回源码最小值
//          abFlag：保留，这里可以使任意值
//返回值：指定范围的最小数值

ZT_API long _stdcall ZT7660_DAGetMaxCode( unsigned long cardNO, 
										 unsigned long chNo,
										 unsigned long rangeInx);
//函数功能：返回最大源码值
//
//入口参数：
//          cardNO：模块号，默认从 1 开始。有关这个参数的详细说明，请参考 ZT7660_OpenDevice 函数
//           lChNo：保留，设成0即可
//        lChRange：保留，设成0即可
//          abFlag：指明是A型还是B型，
//                  0,表示A型12位
//                  1,表示B型16位
//返回值： 大于等于0  最大源码值
//         -1  表失败，应该进一步调用 ZT7660_GetLastErr 判断出错原因

ZT_API long _stdcall ZT7660_DAGetMinCode( unsigned long lCardNo,
										 unsigned long chNo,
										 unsigned long rangeInx);
//函数功能：返回最小源码值
//
//入口参数：
//          cardNO：模块号，默认从 1 开始。有关这个参数的详细说明，请参考 ZT7660_OpenDevice 函数
//           lChNo：保留，设成0即可
//        lChRange：保留，设成0即可
//          abFlag：指明是A型还是B型，
//                  0,表示A型12位
//                  1,表示B型16位
//返回值： 大于等于0  最大源码值
//         -1  表失败，应该进一步调用 ZT7660_GetLastErr 判断出错原因

ZT_API double _stdcall ZT7660_DAGetMaxValue(unsigned long cardNO,
                                            unsigned long chNo,
                                            unsigned long rangeInx);
//函数功能：返回指定范围的最大值
//入口参数：
//          cardNO：保留，这里可以是任意值
//            chNo：保留，这里可以使任意值
//        rangeInx：模拟量范围0~11，在这个范围之外的数值将返回源码最大值
//          abFlag：指明是A型还是B型，
//                  0,表示A型12位，这样当rangeInx为0时返回的最大值是4095
//                  1,表示B型16位，这样当rangeInx为0时返回的最大值是65535
//                    
//返回值：指定范围的最大数值

ZT_API double _stdcall ZT7660_DAGetMinValue(unsigned long cardNO,
											unsigned long chNo,
											unsigned long rangeInx);
//函数功能：返回指定范围的最大最小值
//入口参数：
//          cardNO：保留，这里可以是任意值
//            chNo：保留，这里可以使任意值
//        rangeInx：模拟量范围0~11，在这个范围之外的数值将返回源码最小值
//          abFlag：保留，这里可以使任意值
//返回值：指定范围的最小数值

ZT_API long _stdcall ZT7660_GetName( long lCardNo, TCHAR* tcName );


ZT_API long _stdcall ZT7660_FreRead(unsigned long cardNO,
                                     unsigned long *freDataArr);
//函数名称：
//函数功能：读3路计数器当前测频值
//入口参数：
//          cardNO：模块号，默认从 1 开始。有关这个参数的详细说明，请参考 ZT7660_OpenDevice 函数
//      freDataArr：存放3路计数器当前测频值的地址指针
//
//返回值：  0  表成功
//         -1  表失败，应该进一步调用 ZT7660_GetLastErr 判断出错原因



}
#endif

