/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body\ 
  * @author         : �Ƽ̷� huangjifan
  * @date           : 2023-05-21
  * @description:   
  * �Զ�����ʵ���ۺ�ʵ������ۺ�
  * Integrated Code for Automatic Control Practical Comprehensive Experiment
  * @version        : 1.0.0
  ******************************************************************************
  * @detailed_description:
  * ������Ϊ�Զ�����ʵ���ۺ�ʵ������ۺϣ������˻��㡢ɨƵ����Ծ������ȹ���
  * 
  * ����˵����
  * 1. ������ʹ��MotorControlWorkbench������ɵ���������룬�汾Ϊ5.2.0
  * 2. ��������STM32CubeMX 6.1.0�汾�����ɣ�ʹ����HAL�⣬�汾Ϊ1.7.10
  * 3. ������ʹ����motorcontrol�⣬�汾��MotorControlWorkbenchȷ��
  * 4. ��������Keil MDK 5.37.0�汾�±���ͨ��
  * 
  * ����˵����
  * ������Ҫ���ܶ�������صı��������в����������ڿ��Ƴ����ִ�����̺͹��ܵĿ���
  * ������������Ҫ�������£�
  * 1. ���㣺find_home_flag             ���ڿ����Ƿ�ִ�л������
  * 2. ɨƵ��sweep_identification_flag  ���ڿ����Ƿ�ִ��ɨƵ��ʶ����
  * 3. ��Ծ��step_test_flag             ���ڿ����Ƿ�ִ�н�Ծ����
  * 4. ���棺follow_test_flag           ���ڿ����Ƿ�ִ��ɨƵ�������
  * ���ܵľ�����������ʵ��ָ����������
  * 
  * ����˵����
  * ��������Ϊinputģʽ������KEY1Ϊworkbench��Ĭ����ͣ��������Ϊ�ⲿ�ж�ģʽ
  * KEY2�������º󣬵�����㲻���жϣ�������ɺ��Զ�ֹͣ���㹦��
  * KEY3~5�������º�������Ӧ�Ĺ��ܣ��ٴΰ�����ֹͣ��Ӧ�Ĺ���
  * 1. ����KEY1������-PE0������-�����ͣ
  * 2. ����KEY2������-PE1������-�������
  * 3. ����KEY3������-PE2������-ɨƵ��ʶ
  * 4. ����KEY4������-PE3������-��Ծ����
  * 5. ����KEY5������-PE4������-ɨƵ����
  * ���Խ��RESET������λ��Ƭ��
  * 
  * ������˵����    ������ʹ��TIM3��Ϊ�������ļ��������������ļ�����ΧΪ0~65535
  *                ���ڼ����������������������Ѿ����˴�������Ҫ���⴦��
  *                ���Բ鿴Get_Encoder_Ruler_Count(void)������ʵ�֣����������ִ���ʽ����������ѡ��
  * 
  * ����˵����      ������ʹ��uart5��Ϊ����λ��ͨ�ŵĴ��ڣ�������Ϊ115200
  * 
  * debugģʽ˵���� ʹ�ò������� debug �����Ƿ���debugģʽ
  *                debugģʽ�»����һЩ������Ϣ��ע����matlab��ͨ�Ż���ڸ���
  * 
  * ������˵����    ��Ծ���ԡ�ɨƵ���ٹ�����Ҫʹ�ÿ�����
  *                ������ʹ������ɢ����Ŀ�����������ʵ����discrete_control_func()������
  *                ���Ը���ʹ�õĵ��ϵͳ��ʶ�������ƿ��������޸ĸú�����ʵ��
  ******************************************************************************
  * @detailed_description:
  * This code is the integrated code for the comprehensive experiment of automatic control practice, 
  * which includes functions such as return to zero, sweep, step, and follow
  * 
  * Environment description:
  * 1. This code uses MotorControlWorkbench software to generate motor drive code, version 5.2.0
  * 2. This code is generated under STM32CubeMX 6.1.0, using HAL library, version 1.7.10
  * 3. This code uses the motorcontrol library, the version is determined by MotorControlWorkbench
  * 4. This code is compiled through Keil MDK 5.37.0
  * 
  * Function description:
  * The main functions define related variables, among which boolean variables are used to control the execution flow of the program and the opening of functions
  * The main functions of each variable are as follows:
  * 1. Return to zero: find_home_flag is used to control whether to execute the return to zero operation
  * 2. Sweep: sweep_identification_flag is used to control whether to execute the sweep identification operation
  * 3. Step: step_test_flag is used to control whether to execute the step operation
  * 4. Follow: follow_test_flag is used to control whether to execute the sweep follow operation
  * The specific functions of the function, please refer to the experimental guide for understanding
  * 
  * Key description:
  * The key is set to input mode, where KEY1 is the workbench library default start/stop key, which is still external interrupt mode
  * After KEY2 is pressed, the motor cannot be interrupted by returning to zero, and the return to zero will stop automatically after completion
  * After KEY3~5 is pressed, the corresponding function is started, and then pressed again to stop the corresponding function
  * 1. KEY1: Pin-PE0, Function-Motor Start/Stop
  * 2. KEY2: Pin-PE1, Function-Motor Return to Zero
  * 3. KEY3: Pin-PE2, Function-Sweep Identification
  * 4. KEY4: Pin-PE3, Function-Step Test
  * 5. KEY5: Pin-PE4, Function-Sweep Follow
  * You can combine the RESET button to reset the microcontroller
  * 
  * Encoder description: This program uses TIM3 as the counter of the encoder, and the counter range is 0~65535
  * For the case of counter overflow, the program has been processed and no additional processing is required
  * You can check the implementation of the Get_Encoder_Ruler_Count(void) function, where there are two processing methods, you can choose
  * 
  * Serial port description: This program uses uart5 as the serial port for communication with the upper computer, and the baud rate is 115200
  * 
  * Debug mode description: Use the boolean variable debug to control whether to turn on the debug mode
  * Debug mode will output some debugging information, pay attention to the interference with matlab communication
  * 
  * Controller description: The step test and sweep tracking functions need to use the controller
  * This program uses the discretized controller, the specific implementation is in the discrete_control_func() function
  * According to the identification results of the motor system used, design the controller and modify the implementation of the function
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "motorcontrol.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
typedef struct
{
  unsigned int t_0;
  unsigned int t_01;
  float f0;
  float f1;
  float k;
  float p;
  float A;
}my_sweep_t;

typedef struct 
{ 
  uint8_t start_flag; /*֡����ʼ��־*/
  uint8_t frame_len; /*֡�ĳ�����Ϣ*/ 
  uint8_t header_check; /*֡ͷ�����У��*/ 
  uint8_t data_buf[12]; /*���ݳ��ȣ�����ѡ��̶������ݳ���*/ 
  uint8_t frame_check; /*֡ͷ+���ݵ����У��,���ڽ��շ�У�����ݵ������*/ 
}frame_matlab_t; /*����֡�ṹ��*/

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define PI 3.14159265358979323846

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;
ADC_HandleTypeDef hadc2;

DAC_HandleTypeDef hdac;

TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim8;

UART_HandleTypeDef huart5;
UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */
// ��������ر���
// ��¼�����ǰλ��
int32_t ENCODER_RULER_TIM_PERIOD=0;
float pos=0;

// ����ֵ���жϵ���Ƿ񵽴���������
bool encoder_ruler_left_limit_flag=false;
bool encoder_ruler_right_limit_flag=false;
// ����λ�õı궨ֵ
float encoder_ruler_left_limit=0;
float encoder_ruler_right_limit=0;
// �м�λ�õı궨ֵ
float encoder_ruler_middle=0;
// ����ֵ���ж��Ƿ��Ѿ����������λ�õı궨
bool encoder_ruler_limit_calibrated=false;
// ����ֵ����������м�λ�õ�����
const float middle_limit=2;

// debugģʽ
bool debug = false;   // �ر�debugģʽ
// bool debug = true; // ��debugģʽ

// ========���ܿ��أ�����========
// ִ�л������
bool find_home_flag = false;
// ÿ�λ�������Ƿ����Ƚ��б궨
bool re_calibrate_flag = true;
// bool re_calibrate_flag = false;

// ========���ܿ��أ�ɨƵ========
// ɨƵ���Կ���
bool sweep_identification_flag = false;
// ɨƵ�Ƿ���Ҫ���³�ʼ��
bool sweep_reinit_flag = false;

// ========���ܿ��أ���Ծ========
// ��Ծ���Կ���
bool step_test_flag = false;
// ���������¶�Ӧ�������״�ִ�н�Ծ����
bool step_first_flag = true;

// ========���ܿ��أ�����========
// ɨƵ�������
bool follow_test_flag = false;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_ADC1_Init(void);
static void MX_ADC2_Init(void);
static void MX_DAC_Init(void);
static void MX_TIM2_Init(void);
static void MX_TIM3_Init(void);
static void MX_TIM8_Init(void);
static void MX_UART5_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_NVIC_Init(void);
/* USER CODE BEGIN PFP */
float Get_Encoder_Ruler_Count(void);

// [GENERAL] ����������������������������
// ����Ҫ���м��İ�����GPIO_Pin�����ذ����Ƿ���
bool single_key_detect(uint16_t GPIO_Pin)
{
  // ��������
  if(HAL_GPIO_ReadPin(GPIOE, GPIO_Pin) == GPIO_PIN_RESET)
  {
    // �������£��ȴ������ͷ�
    while(HAL_GPIO_ReadPin(GPIOE, GPIO_Pin) == GPIO_PIN_RESET);
    // �����ͷţ�����true
    return true;
  }
  // ����δ���£�����false
  else
  {
    return false;
  }
}

// [GENERAL] ����������
void keys_detect()
{
  // PE1�����ñ�ǩλGoHome
  // ������ΪPE1��find_home_flag��Ϊtrue
  if(single_key_detect(Go_Home_Pin))
  {
    MC_StartMotor1();
    find_home_flag = true;
    // ���±궨������
    if(re_calibrate_flag)
    {
      encoder_ruler_left_limit_flag=false;
      encoder_ruler_right_limit_flag=false;
      encoder_ruler_limit_calibrated=false;
    }
  }
  // ������ΪPE2��sweep_test_flag���з�ת
  // �������ɨƵ��ʶ����
  if(single_key_detect(Key_3_Pin))
  {
    MC_ProgramSpeedRampMotor1(0, 0);
    sweep_identification_flag = !sweep_identification_flag;
    // ���½���ɨƵ��ʼ��
    sweep_reinit_flag = true;
    // ֹͣɨƵʱ�������ֹͣ
    if(sweep_identification_flag==false)
    {
      MC_StopMotor1();
    }
    else
    {
      MC_StartMotor1();
    }
  }

  // ������ΪPE3��step_test_flag���з�ת
  // ������н�Ծ����
  if(single_key_detect(Key_4_Pin))
  {
    MC_StartMotor1();
    step_test_flag = !step_test_flag;
    // ��ǰһ�ֽ�Ծ���ԣ������״�ִ��
    step_first_flag = true;
    if(step_test_flag==false)
    {
      MC_StopMotor1();
    }
  }

  // ������ΪPE4��follow_test_flag���з�ת
  // �������ɨƵ�������
  if(single_key_detect(Key_5_Pin))
  {
    MC_ProgramSpeedRampMotor1(0, 0);
    MC_StartMotor1();
    follow_test_flag = !follow_test_flag;
    if(follow_test_flag==false)
    {
      MC_StopMotor1();
    }
  }
}

// [TASK-2]
// ������λ���źţ��жϵ���Ƿ񵽴�����
// ����PG1����Ϊ����λ��PG0����Ϊ����λ
void Judge_Limit_signal()
{
  // ����������
  if(HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_1)==GPIO_PIN_RESET)
  {
    encoder_ruler_left_limit_flag=true;
    // [DEBUG]
    if (debug)
      printf("Left Limit!\r\n");
  }
  // ��������Ҳ�
  else if(HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_0)==GPIO_PIN_RESET)
  {
    encoder_ruler_right_limit_flag=true;
    // [DEBUG]
    if (debug)
      printf("Right Limit!\r\n");
  }
}

// [TASK-2] Ѱ�����������λ�ã�����λ�ñ궨
void Calibrate_Encoder_Ruler_Limit()
{
  // ��û����ɵ��λ�ñ궨ʱ�����Ƶ��ת��
  while(!encoder_ruler_limit_calibrated)
  {
    // ��ȡ��ǰλ��
    pos=Get_Encoder_Ruler_Count();
    // ������λ���źţ��жϵ���Ƿ񵽴����࣬���±�־λ
    Judge_Limit_signal();
    // ������Ʒ���Ϊ�������һ���ٶȺͳ���ʱ��
    // �ȱ궨���λ�ã��ٱ궨�Ҳ�λ��
    if (!encoder_ruler_left_limit_flag)
    {
      MC_ProgramSpeedRampMotor1(50, 50);
      // ��¼����λ�õı궨ֵ
      encoder_ruler_left_limit=pos;
    }
    else if (!encoder_ruler_right_limit_flag)
    {
      MC_ProgramSpeedRampMotor1(-50, 50);
      // ��¼����λ�õı궨ֵ
      encoder_ruler_right_limit=pos;
    }
    else
    {
      // ����������ֹ࣬ͣ���
      MC_ProgramSpeedRampMotor1(0, 0);
      // �궨���
      encoder_ruler_limit_calibrated=true;
    }
  }
  // �����������λ�õı궨ֵ
  // [DEBUG]
  if (debug)
  {
    printf("Encoder Ruler Left Limit:%f\r\n",encoder_ruler_left_limit);
    printf("Encoder Ruler Right Limit:%f\r\n",encoder_ruler_right_limit);
    // ����궨���
    printf("Encoder Ruler Limit Calibrated!\r\n");
    // ����
    printf("\r\n");
  }
}

// [TASK-2] �����м�λ��
void Calibrate_Encoder_Ruler_Middle()
{
  // �����м�λ�õı궨ֵ
  encoder_ruler_middle=(encoder_ruler_left_limit+encoder_ruler_right_limit)/2;
  if(debug)
  {
    printf("Encoder Ruler Middle:%f\r\n",encoder_ruler_middle);
    // ����궨���
    printf("Encoder Ruler Middle Calibrated!\r\n");
  }
}

// [TASK-2] ���Ƶ���ٶȣ��������Ϊ���λ�ã��ݴ˼������ٶ�
void Control_Motor_Speed(float position)
{
  // [DEBUG]
  if (debug)
  {
    // ������λ��
    printf("Encoder Ruler Position:%f\r\n",position);
    // ����м�λ��
    printf("Encoder Ruler Middle:%f\r\n",encoder_ruler_middle);
    // ������λ�õ��м�λ�õľ���
    printf("Encoder Ruler Distance:%f\r\n",fabs(position-encoder_ruler_middle));
    // ����
    printf("\r\n");
  }

  // ���λ�����м�λ�õ�������Χ�ڣ�����ٶ���Ϊ0
  if (fabs(position-encoder_ruler_middle)<middle_limit)
  {
    // [DEBUG]
    if (debug)
      printf("STOP MOTOR \r\n");
    MC_ProgramSpeedRampMotor1(0, 0);
    MC_StopMotor1();

    // ��ǵ�������м�λ��
    find_home_flag = false;
  }
  // ���λ�����м�λ�õ�������Χ��
  else
  {
    // [DEBUG]
    if (debug)
      printf("MOTIVATE MOTOR \r\n");
    // �����λ�����м�λ�õ���࣬����ٶ�Ϊ��
    if (position<encoder_ruler_middle)
    {
      MC_ProgramSpeedRampMotor1(50, 10);
    }
    // �����λ�����м�λ�õ��Ҳ࣬����ٶ�Ϊ��
    else
    {
      MC_ProgramSpeedRampMotor1(-50, 10);
    }
  }
}

// [TASK-3] 
// ��ʼ��һ��Ƶ������ʱ��ָ�����ӵ�����ɨƵ�źŵĽṹ��
// ���룺unsigned int t_0 ɨƵ��������ʼʱ�̣� ��λms
// ���룺unsigned int t_01 ��t0��t1��ʱ����, ��λms
// ���룺float f0 ʱ��t0��Ӧ��Ƶ�ʣ� ��λhz
// ���룺float f1 ʱ��t1��Ӧ��Ƶ�ʣ� ��λhz 
// ���룺float A ɨƵ�źŵķ�ֵ
// �����int 0 = �ɹ�����0
int init_my_sweep(my_sweep_t *sweep, unsigned int t_0, unsigned int t_01, float f0, float f1, float A) 
{ 
  if ((t_01 == 0) || (f0 <=0.0f) || (f1 <= 0.0f) || (f0 == f1) || (A == 0) || (!sweep)) 
  {
    //�Ƿ����
    return -1;
  }

  sweep->t_0 = t_0;
  sweep->t_01 = t_01;
  sweep->f0 = f0;
  sweep->f1 = f1;
  sweep->A = A;

  /* start add code here */ 
  /*����ָ�������ĵ���k��ע��ʱ��ĵ�λҪת��Ϊms*/ 
  sweep->k = exp(1.0 / (double)(sweep->t_01* 0.001) * log(sweep->f1 / sweep->f0));
  /*����ϵ��p, ע�ⵥλת��*/
  sweep->p = 2 * PI * sweep->f0 / log(sweep->k);
  /* end add code here */

  return 0; 
}

// [TASK-3] ���ݵ�ǰʱ�����Ƶ������ʱ��ָ�����ӵ�����ɨƵ�ź�
float run_my_sweep(my_sweep_t *sweep, unsigned int t_now)
{
  float t = 0.0f; //���ʱ�� t 
  float y = 0.0f; //ɨƵ�ź� 
  
  if (!sweep) 
  { 
    return 0.0f; /*�Ƿ����*/ 
  }
  
  if (t_now < sweep->t_0) 
  { 
    return 0.0f; /*ʱ�仹δ�õ�*/ 
  }
  
  t = (t_now - sweep->t_0) % sweep->t_01; /*ͨ���������ʵ�֣�������ɨƵ�Ĺ���*/
  t = t * 0.001f; /*����λת��Ϊ s*/
  
  /* start add your code here */
  y = sweep->A * sin(sweep->p * (pow(sweep->k, t) - 1));
  /* end add your code here */

  return y;
}

// [TASK-3] ����У���
uint8_t get_uint8_sum_check(uint8_t *data, int len) 
{ 
  int i = 0; 
  uint8_t sum = 0; 

  for (i = 0; i < len; i++) 
  {
    sum += data[i]; 
  }

  return sum; 
}

// [TASK-3] ��matlab��������������
void send_data_2_matlab(float data1, float data2, float data3)
{ 
  frame_matlab_t frame = {0};

  // int i = 0; /*���֡ͷ*/ 
  frame.start_flag = 0xAA; 
  frame.frame_len = sizeof(frame); 
  frame.header_check = get_uint8_sum_check((uint8_t *)&frame, 2); /*�������*/

  memcpy((uint8_t *)&frame.data_buf[0], (uint8_t *)&data1, 4); 
  memcpy((uint8_t *)&frame.data_buf[4], (uint8_t *)&data2, 4); 
  memcpy((uint8_t *)&frame.data_buf[8], (uint8_t *)&data3, 4); /*�����������ֵ,���ڽ��շ�У�����ݵ������*/ 
  
  frame.frame_check = get_uint8_sum_check((uint8_t *)&frame, frame.frame_len-1); /*ͨ�� ����5 ���͵����� */ 
  
  HAL_UART_Transmit(&huart5, (uint8_t *)&frame,frame.frame_len,0xffff);   
}

// [TASK-3] ʵ��ɨƵ��ʶ���ܣ��ù��ܽ���������main ������while(1)������
// bool is_reinit_sweep: �Ƿ���Ҫ���³�ʼ��ɨƵ�ź�
void run_sweep_identification(bool is_reinit_sweep)
{
  static my_sweep_t sweep = {0};
  int16_t sweep_input = 0;
  int16_t sweep_output = 0;
  uint32_t sys_tick = 0;
  static uint32_t init_flag = 0; 
  static uint32_t last_sys_tick = 0; 
  // ����Ҫ���³�ʼ��ɨƵ�ź�
  if (is_reinit_sweep == true) 
  { 
    init_flag = 0; 
  }

  // Ƶ����10s�ڣ���0.5hz�仯��10hz������Ϊ1500 digit current
  uint32_t t_period_ms = 10*1000; //10s 
  float f0 = 0.5; 
  float f1 = 10; 
  float Amp = 1500.0f; 
  
  float time = 0.0f;
  sys_tick = HAL_GetTick(); //��ȡ��ǰʱ�̣���λms 
  time = 0.001f * sys_tick; //��λs

  /*���������ʱ����ɹ����Ұ���K1����, �Ϳ�ʼִ��ɨƵ��ʶ���̣�
    ע��find_home_flag�ǻ���ɹ��ı�־λ����һ��ȫ�ֱ���,Ҫ���ⲿʵ�������־����*/
  // if ((find_home_flag == 1) && (MC_GetSTMStateMotor1() == RUN)) {
  if ((sweep_identification_flag == true) && (MC_GetSTMStateMotor1() == RUN)) 
  {
    // �����ǰʱ�̷����˱仯���������ÿms�������
    if (last_sys_tick != sys_tick)  
    {
      last_sys_tick = sys_tick;
      // ͨ�� % ��Ƶ�ʴ�1000hz���͵�100hz����ÿ10ms����һ�α仯
      if (sys_tick % 10 == 0) 
      {
          // ��ʼ��ɨƵ����
          if (init_flag == 0) 
          {
              init_my_sweep(&sweep, sys_tick, t_period_ms, f0, f1, Amp);
              printf("sweep-init:k=%.5f,p=%.5f\r\n", (float)sweep.k,
                     (float)sweep.p);
              init_flag = 1;
          }

          // ��ȡ����ɨƵ�ź�
          sweep_input = (int16_t)run_my_sweep(&sweep, sys_tick);

          // ������ɨƵ�ź����뵽 ST MC SDK�����ؿ���API��
          MC_ProgramTorqueRampMotor1(sweep_input, 0);  
          // ��ȡ˿�˵�ת����Ϣ����λΪ0.1hz
          sweep_output = MC_GetMecSpeedAverageMotor1(); 
          // ��ʱ�䣬input��output���͵�matlab
          send_data_2_matlab(time, (float)sweep_input, (float)sweep_output);
          // [DEBUG]
          if(debug)
            printf("sweep-input:%d,sweep-output:%d\r\n", sweep_input, sweep_output);
      }
    }
  }
}

// [TASK-3] ���ƺ���ʵ��
// ======================================================
// ====   ���ݵ��ʵ�ʱ�ʶ�������ƿ�������������ɢ��   ====
// ======================================================
int discrete_control_func(int32_t u0, float e1, float e0)
{
  return (int)(-0.6667*u0 + 3000*e1 - 2200*e0);
}

// [TASK-3] ʵ�ֽ�Ծ���Ժ���������main��while(1)�н��н�Ծ����
void function_step_test(void)
{
  /*1.����ֲ������;�̬����*/
  static int32_t u1 = 0;
  static int32_t u0 = 0;
  static float e1 = 0;
  static float e0 = 0;
  uint32_t sys_tick = 0;
  float fdk = 0;
  float Amp = 20;
  static float ref = 0;

  /*2.��ʼ����Ŀ�����*/ 
  float time = 0.0f;
  sys_tick = HAL_GetTick();
  time = 0.001f * sys_tick;
  
  /*3.����step���Թ�����������*/
  // if ((find_home_flag==true)&&(MC_GetSTMStateMotor1()==RUN))
  if ((step_test_flag==true)&&(MC_GetSTMStateMotor1()==RUN))
  { 
    /*4.��Ƶ��ȷ����ǰtickΪ���������е�tick*/
    if (sys_tick % 10 == 0)
    { 
      if(step_first_flag == true)
      {
        /*5.��ȡ��դ�ߵĵ�ǰλ�� fdk (mm)*/ 
        fdk = Get_Encoder_Ruler_Count();

        /*6.ָ����Ծ�ľ���Ampͳһ����Ϊ20mm*/ 
        Amp = 20;

        /*7.һ���Լ��㵱ǰ�ο�ֵ ref = fdk+Amp*/ 
        ref = Amp + fdk;
        step_first_flag = false;
      }

      /*8.��ref��Ϊ���λ�ÿ�����������������ÿ�����*/ 
      e1 = ref - Get_Encoder_Ruler_Count();
      // u1 = (int)(-0.6667*u0 + 3000*e1 - 2200*e0);
      u1 = discrete_control_func(u0, e1, e0);
      
      // ����u1�ķ�Χ�����������
      if(u1 > 4997) u1 = 4997;
      if(u1 < -4997) u1 = -4997;
      // ͨ��ST MC SDK�����ؿ���API����u1��Ϊ���룬���Ƶ��
      MC_ProgramTorqueRampMotor1(u1, 0);
      // ����e0��u0
      e0 = e1;
      u0 = u1;
      fdk = Get_Encoder_Ruler_Count();

      /*9.ʹ�� send_data_2_matlab, ��ʱ�䣬ref, fdk���͵�matlab������ʾ*/ 
      send_data_2_matlab(time, (float)ref, (float)fdk);
    } 
    else 
    {
      /*10. do some thing if need*/ 
    }
  }
  else 
  {
    /*11. do some thing if need*/ 
    // [DEBUG]
    if(debug)
    {
      printf("Can't run step test, please check the condition!\r\n");
    }
  }
}

// [TASK-3] ʵ��һ��ɨƵ���Ժ���������main��while(1)�н���ɨƵ������ԣ���֤wλ�ñջ�����
void function_follow_test(void)
{ 
  /*1.����ֲ������;�̬����*/
  static int32_t u1 = 0;
  static int32_t u0 = 0;
  static float e1 = 0;
  static float e0 = 0;
  uint32_t sys_tick = 0;
  float fdk;
  static float ref = 0;
  
  /*2.��ʼ����Ŀ�����*/
  float time = 0.0f;
  sys_tick = HAL_GetTick();
  time = 0.001f * sys_tick;
  
  /*3.��ʼ����������źŷ�������ֵΪ20mm, Ƶ����10s�ڴ�1hz�仯��2hz*/
  //10s 1hz->2hz
  static float w = 1*2*3.1415;
  float Amp = 20;

  /*4.����ɨƵ������Թ�����������*/
  // if ((find_home_flag==1)&&(MC_GetSTMStateMotor1()==RUN)) 
  if ((follow_test_flag)&&(MC_GetSTMStateMotor1()==RUN)) 
  { 
    /*5.��Ƶ��ȷ����ǰtickΪ���������е�tick*/
    if (sys_tick % 10 == 0) 
    { 
      /*6.��ȡ��դ�ߵĵ�ǰλ�� fdk (mm)*/
      fdk = Get_Encoder_Ruler_Count();
      
      /*7.ÿ��tick����ȡ���µ�ɨƵ�ź��������Ϊ��ǰ�ο�ֵ ref = sweep(now)*/
      ref = Amp*sin(w*time);
      
      /*8.��ref��Ϊ���λ�ÿ�����������������ÿ�����*/
      e1 = ref - fdk;
      // u1 = (int)(-0.6667*u0 + 3000*e1 - 2200*e0);
      u1 = discrete_control_func(u0, e1, e0);

      // ����u1�ķ�Χ�����������
      if(u1 > 4997) u1 = 4997;
      if(u1 < -4997) u1 = -4997;
      // ͨ��ST MC SDK�����ؿ���API����u1��Ϊ���룬���Ƶ��
      MC_ProgramTorqueRampMotor1(u1, 0);
      // ����e0��u0
      e0 = e1;
      u0 = u1;
      fdk = Get_Encoder_Ruler_Count();
      /*9.ʹ�� send_data_2_matlab, ��ʱ�䣬ref, fdk���͵�matlab������ʾ*/ 
      send_data_2_matlab(time, (float)ref, (float)fdk);
    }
    else
    { 
      /*10. do some thing if need*/
    } 
  } 
  else 
  {
    /*11. do some thing if need*/ 
    // [DEBUG]
    if(debug)
    {
      printf("Can't run follow test, please check the condition!\r\n");
    }
  } 
}

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_ADC1_Init();
  MX_ADC2_Init();
  MX_DAC_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_TIM8_Init();
  MX_UART5_Init();
  MX_USART1_UART_Init();
  MX_MotorControl_Init();

  /* Initialize interrupts */
  MX_NVIC_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_ALL); 
	MC_AlignEncoderMotor1();
  HAL_Delay(100);

  // �������
  MC_StartMotor1();
  
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    // �������
    keys_detect();
    // ��ȡ��ǰλ��
    pos=Get_Encoder_Ruler_Count();
    
    // �������
    if (find_home_flag==true)
    {
      // ���λ�ñ궨
      Calibrate_Encoder_Ruler_Limit();
      // �����м�λ��
      Calibrate_Encoder_Ruler_Middle();
      // ���Ƶ���ٶȣ�ʹ�õ������
      Control_Motor_Speed(pos);
    }
    // ����ɨƵ��ʶ
    if(sweep_identification_flag==true)
    {
      run_sweep_identification(sweep_reinit_flag);
      sweep_reinit_flag = false;
    }
    // ���н�Ծ����
    if(step_test_flag==true)
    {
      function_step_test();
    }
    // ����ɨƵ�������
    if(follow_test_flag==true)
    {
      function_follow_test();
    }
	  // printf("%.3f \r\n",pos);

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
  /** Enables the Clock Security System
  */
  HAL_RCC_EnableCSS();
}

/**
  * @brief NVIC Configuration.
  * @retval None
  */
static void MX_NVIC_Init(void)
{
  /* ADC_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(ADC_IRQn, 2, 0);
  HAL_NVIC_EnableIRQ(ADC_IRQn);
  /* TIM8_UP_TIM13_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(TIM8_UP_TIM13_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(TIM8_UP_TIM13_IRQn);
  /* TIM8_BRK_TIM12_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(TIM8_BRK_TIM12_IRQn, 4, 1);
  HAL_NVIC_EnableIRQ(TIM8_BRK_TIM12_IRQn);
  /* TIM2_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(TIM2_IRQn, 3, 0);
  HAL_NVIC_EnableIRQ(TIM2_IRQn);
  /* USART1_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(USART1_IRQn, 3, 1);
  HAL_NVIC_EnableIRQ(USART1_IRQn);
  /* EXTI0_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_InjectionConfTypeDef sConfigInjected = {0};
  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */
  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.ScanConvMode = ENABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_LEFT;
  hadc1.Init.NbrOfConversion = 2;
  hadc1.Init.DMAContinuousRequests = DISABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configures for the selected ADC injected channel its corresponding rank in the sequencer and its sample time
  */
  sConfigInjected.InjectedChannel = ADC_CHANNEL_6;
  sConfigInjected.InjectedRank = 1;
  sConfigInjected.InjectedNbrOfConversion = 3;
  sConfigInjected.InjectedSamplingTime = ADC_SAMPLETIME_3CYCLES;
  sConfigInjected.ExternalTrigInjecConvEdge = ADC_EXTERNALTRIGINJECCONVEDGE_RISING;
  sConfigInjected.ExternalTrigInjecConv = ADC_EXTERNALTRIGINJECCONV_T8_CC4;
  sConfigInjected.AutoInjectedConv = DISABLE;
  sConfigInjected.InjectedDiscontinuousConvMode = ENABLE;
  sConfigInjected.InjectedOffset = 0;
  if (HAL_ADCEx_InjectedConfigChannel(&hadc1, &sConfigInjected) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configures for the selected ADC injected channel its corresponding rank in the sequencer and its sample time
  */
  sConfigInjected.InjectedChannel = ADC_CHANNEL_8;
  if (HAL_ADCEx_InjectedConfigChannel(&hadc1, &sConfigInjected) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configures for the selected ADC injected channel its corresponding rank in the sequencer and its sample time
  */
  sConfigInjected.InjectedChannel = ADC_CHANNEL_9;
  if (HAL_ADCEx_InjectedConfigChannel(&hadc1, &sConfigInjected) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_10;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_56CYCLES;
  sConfig.Offset = 0;

  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_13;
  sConfig.Rank = 2;
  sConfig.SamplingTime = ADC_SAMPLETIME_28CYCLES;
  sConfig.Offset = 0;

  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

/**
  * @brief ADC2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC2_Init(void)
{

  /* USER CODE BEGIN ADC2_Init 0 */

  /* USER CODE END ADC2_Init 0 */

  ADC_InjectionConfTypeDef sConfigInjected = {0};
  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC2_Init 1 */

  /* USER CODE END ADC2_Init 1 */
  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
  */
  hadc2.Instance = ADC2;
  hadc2.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
  hadc2.Init.Resolution = ADC_RESOLUTION_12B;
  hadc2.Init.ScanConvMode = ENABLE;
  hadc2.Init.ContinuousConvMode = DISABLE;
  hadc2.Init.DiscontinuousConvMode = DISABLE;
  hadc2.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc2.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc2.Init.DataAlign = ADC_DATAALIGN_LEFT;
  hadc2.Init.NbrOfConversion = 1;
  hadc2.Init.DMAContinuousRequests = DISABLE;
  hadc2.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  if (HAL_ADC_Init(&hadc2) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configures for the selected ADC injected channel its corresponding rank in the sequencer and its sample time
  */
  sConfigInjected.InjectedChannel = ADC_CHANNEL_6;
  sConfigInjected.InjectedRank = 1;
  sConfigInjected.InjectedNbrOfConversion = 3;
  sConfigInjected.InjectedSamplingTime = ADC_SAMPLETIME_3CYCLES;
  sConfigInjected.ExternalTrigInjecConvEdge = ADC_EXTERNALTRIGINJECCONVEDGE_RISING;
  sConfigInjected.ExternalTrigInjecConv = ADC_EXTERNALTRIGINJECCONV_T8_CC4;
  sConfigInjected.AutoInjectedConv = DISABLE;
  sConfigInjected.InjectedDiscontinuousConvMode = ENABLE;
  sConfigInjected.InjectedOffset = 0;
  if (HAL_ADCEx_InjectedConfigChannel(&hadc2, &sConfigInjected) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configures for the selected ADC injected channel its corresponding rank in the sequencer and its sample time
  */
  sConfigInjected.InjectedChannel = ADC_CHANNEL_8;
  if (HAL_ADCEx_InjectedConfigChannel(&hadc2, &sConfigInjected) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configures for the selected ADC injected channel its corresponding rank in the sequencer and its sample time
  */
  sConfigInjected.InjectedChannel = ADC_CHANNEL_9;
  if (HAL_ADCEx_InjectedConfigChannel(&hadc2, &sConfigInjected) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_6;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc2, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC2_Init 2 */

  /* USER CODE END ADC2_Init 2 */

}

/**
  * @brief DAC Initialization Function
  * @param None
  * @retval None
  */
static void MX_DAC_Init(void)
{

  /* USER CODE BEGIN DAC_Init 0 */

  /* USER CODE END DAC_Init 0 */

  DAC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN DAC_Init 1 */

  /* USER CODE END DAC_Init 1 */
  /** DAC Initialization
  */
  hdac.Instance = DAC;
  if (HAL_DAC_Init(&hdac) != HAL_OK)
  {
    Error_Handler();
  }
  /** DAC channel OUT1 config
  */
  sConfig.DAC_Trigger = DAC_TRIGGER_SOFTWARE;
  sConfig.DAC_OutputBuffer = DAC_OUTPUTBUFFER_DISABLE;
  if (HAL_DAC_ConfigChannel(&hdac, &sConfig, DAC_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /** DAC channel OUT2 config
  */
  if (HAL_DAC_ConfigChannel(&hdac, &sConfig, DAC_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN DAC_Init 2 */

  /* USER CODE END DAC_Init 2 */

}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_Encoder_InitTypeDef sConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 0;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = M1_PULSE_NBR;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  sConfig.EncoderMode = TIM_ENCODERMODE_TI12;
  sConfig.IC1Polarity = TIM_ICPOLARITY_RISING;
  sConfig.IC1Selection = TIM_ICSELECTION_DIRECTTI;
  sConfig.IC1Prescaler = TIM_ICPSC_DIV1;
  sConfig.IC1Filter = M1_ENC_IC_FILTER;
  sConfig.IC2Polarity = TIM_ICPOLARITY_RISING;
  sConfig.IC2Selection = TIM_ICSELECTION_DIRECTTI;
  sConfig.IC2Prescaler = TIM_ICPSC_DIV1;
  sConfig.IC2Filter = M1_ENC_IC_FILTER;
  if (HAL_TIM_Encoder_Init(&htim2, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_Encoder_InitTypeDef sConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 0;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 0xFFFF;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  sConfig.EncoderMode = TIM_ENCODERMODE_TI12;
  sConfig.IC1Polarity = TIM_ICPOLARITY_RISING;
  sConfig.IC1Selection = TIM_ICSELECTION_DIRECTTI;
  sConfig.IC1Prescaler = TIM_ICPSC_DIV1;
  sConfig.IC1Filter = 0;
  sConfig.IC2Polarity = TIM_ICPOLARITY_RISING;
  sConfig.IC2Selection = TIM_ICSELECTION_DIRECTTI;
  sConfig.IC2Prescaler = TIM_ICPSC_DIV1;
  sConfig.IC2Filter = 0;
  if (HAL_TIM_Encoder_Init(&htim3, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */
  __HAL_TIM_CLEAR_IT(&htim3, TIM_IT_UPDATE);
  __HAL_TIM_URS_ENABLE(&htim3);
  __HAL_TIM_ENABLE_IT(&htim3, TIM_IT_UPDATE);
  /* USER CODE END TIM3_Init 2 */

}

/**
  * @brief TIM8 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM8_Init(void)
{

  /* USER CODE BEGIN TIM8_Init 0 */

  /* USER CODE END TIM8_Init 0 */

  TIM_SlaveConfigTypeDef sSlaveConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};
  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

  /* USER CODE BEGIN TIM8_Init 1 */

  /* USER CODE END TIM8_Init 1 */
  htim8.Instance = TIM8;
  htim8.Init.Prescaler = ((TIM_CLOCK_DIVIDER) - 1);
  htim8.Init.CounterMode = TIM_COUNTERMODE_CENTERALIGNED1;
  htim8.Init.Period = ((PWM_PERIOD_CYCLES) / 2);
  htim8.Init.ClockDivision = TIM_CLOCKDIVISION_DIV2;
  htim8.Init.RepetitionCounter = (REP_COUNTER);
  htim8.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim8) != HAL_OK)
  {
    Error_Handler();
  }
  sSlaveConfig.SlaveMode = TIM_SLAVEMODE_TRIGGER;
  sSlaveConfig.InputTrigger = TIM_TS_ITR1;
  if (HAL_TIM_SlaveConfigSynchro(&htim8, &sSlaveConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim8, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
  if (HAL_TIM_PWM_ConfigChannel(&htim8, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim8, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim8, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM2;
  sConfigOC.Pulse = (((PWM_PERIOD_CYCLES) / 2) - (HTMIN));
  if (HAL_TIM_PWM_ConfigChannel(&htim8, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
  {
    Error_Handler();
  }
  sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_ENABLE;
  sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_ENABLE;
  sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_1;
  sBreakDeadTimeConfig.DeadTime = ((DEAD_TIME_COUNTS) / 2);
  sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
  sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_LOW;
  sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
  if (HAL_TIMEx_ConfigBreakDeadTime(&htim8, &sBreakDeadTimeConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM8_Init 2 */

  /* USER CODE END TIM8_Init 2 */
  HAL_TIM_MspPostInit(&htim8);

}

/**
  * @brief UART5 Initialization Function
  * @param None
  * @retval None
  */
static void MX_UART5_Init(void)
{

  /* USER CODE BEGIN UART5_Init 0 */

  /* USER CODE END UART5_Init 0 */

  /* USER CODE BEGIN UART5_Init 1 */

  /* USER CODE END UART5_Init 1 */
  huart5.Instance = UART5;
  huart5.Init.BaudRate = 115200;
  huart5.Init.WordLength = UART_WORDLENGTH_8B;
  huart5.Init.StopBits = UART_STOPBITS_1;
  huart5.Init.Parity = UART_PARITY_NONE;
  huart5.Init.Mode = UART_MODE_TX_RX;
  huart5.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart5.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart5) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN UART5_Init 2 */

  /* USER CODE END UART5_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOI_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();

  /*Configure GPIO pins : Key_4_Pin Key_3_Pin Go_Home_Pin Key_5_Pin */
  GPIO_InitStruct.Pin = Key_4_Pin|Key_3_Pin|Go_Home_Pin|Key_5_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pin : Start_Stop_Pin */
  GPIO_InitStruct.Pin = Start_Stop_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(Start_Stop_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : LIM_P_Pin LIM_N_Pin */
  GPIO_InitStruct.Pin = LIM_P_Pin|LIM_N_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

// // GPIO�ⲿ�жϻص�����
// void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
// {
// }

// ��ʼ�ϵ�ʱ���λ��Ϊ0����������ò�ͬ���ű�ʾ
// �������ԣ���������������ϵ��˶���Χ���ᳬ������
float Get_Encoder_Ruler_Count(void)
{
  // ʹ��int32_t���ͣ�����ʵ�ʼ���ֵΪ16λ��Valueʼ��Ϊ����
	int32_t Value = __HAL_TIM_GET_COUNTER(&htim3);
  
  float CaptureNumber=0;
	float ruler_pos=0.0f;

  // 16λ���ķ�Χλ0~65535������ֵ����32768ʱ��˵������ֵ�������Ҫ��ȥ65536
  CaptureNumber = (Value > 32768) ? (Value - 65536) : (Value);
  // ���������ת������λΪmm
	ruler_pos = (float)(CaptureNumber*0.005f);

  // [DEBUG]
  if(debug)
  {
    printf("Value:%d\r\n",Value);
    printf("ruler_pos:%f\r\n",ruler_pos);
  }

	return ruler_pos;
  // ʵ��ʹ��int16_t����ʱ��������ȷ��ʾ����
  // ����Ҫ���ж��⴦�����ǲ�����ˣ���д��ע�������
  // int16_t test_value = __HAL_TIM_GET_COUNTER(&htim3);
  // printf("test_value:%d\r\n",test_value);
  // ruler_pos = (float)(test_value*0.005f);
  // return ruler_pos;
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
