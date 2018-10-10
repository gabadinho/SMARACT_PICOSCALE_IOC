/**********************************************************************
* SmarAct PicoScale API - extends the SmarAct Sensor Interface API
* Copyright (c) 2015 - 2017 SmarAct GmbH
*
* File name: SmarActSIConstants_PS.h
*
* THIS  SOFTWARE, DOCUMENTS, FILES AND INFORMATION ARE PROVIDED 'AS IS'
* WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING,
* BUT  NOT  LIMITED  TO,  THE  IMPLIED  WARRANTIES  OF MERCHANTABILITY,
* FITNESS FOR A PURPOSE, OR THE WARRANTY OF NON-INFRINGEMENT.
* THE  ENTIRE  RISK  ARISING OUT OF USE OR PERFORMANCE OF THIS SOFTWARE
* REMAINS WITH YOU.
* IN  NO  EVENT  SHALL  THE  SMARACT  GMBH  BE  LIABLE  FOR ANY DIRECT,
* INDIRECT, SPECIAL, INCIDENTAL, CONSEQUENTIAL OR OTHER DAMAGES ARISING
* OUT OF THE USE OR INABILITY TO USE THIS SOFTWARE.
**********************************************************************/

#ifndef SMARACT_SI_CONSTANTS_PS_H
#define SMARACT_SI_CONSTANTS_PS_H


/**************************************************************/
/* ERROR CODES                                                */
/**************************************************************/
#define SA_PS_REQUEST_DENIED_ERROR                              0x8000
#define SA_PS_INTERNAL_COMMUNICATION_ERROR                      0x8001
#define SA_PS_NO_FULL_ACCESS_ERROR                              0x8002
#define SA_PS_WORKING_DISTANCE_NOT_SET_ERROR                    0x8200

/**************************************************************/
/* EVENT TYPES                                                */
/**************************************************************/
#define SA_PS_FULL_ACCESS_CONNECTION_LOST_EVENT                 0x8000
#define SA_PS_BEAM_INTERRUPT_EVENT                              0x8010
#define SA_PS_OVERRANGE_EVENT                                   0x8011
#define SA_PS_OVERHEAT_EVENT                                    0x8012
#define SA_PS_CALC_SYS_DATA_INTERRUPT_EVENT                     0x8013
#define SA_PS_STABLE_STATE_CHANGED_EVENT                        0x8100
#define SA_PS_CHANNEL_ENABLED_STATE_CHANGED_EVENT               0x8101
#define SA_PS_CHANNEL_VALID_STATE_CHANGED_EVENT                 0x8102
#define SA_PS_PILOT_LASER_STATE_CHANGED_EVENT                   0x8103
#define SA_PS_ENV_SENSOR_STATE_CHANGED_EVENT                    0x8104
#define SA_PS_COUNTER_STATE_CHANGED_EVENT                       0x8105
#define SA_PS_CLOCK_GEN_STATE_CHANGED_EVENT                     0x8106
#define SA_PS_SIG_GEN_STATE_CHANGED_EVENT                       0x8107
#define SA_PS_BOB_CONNECT_STATE_CHANGED_EVENT                   0x8108
#define SA_PS_LVDS_LS_CONNECT_STATE_CHANGED_EVENT               0x8109
#define SA_PS_AF_ADJUSTMENT_PROGRESS_EVENT                      0x8a80
#define SA_PS_FILTER_SETTING_CHANGED_EVENT                      0x8a82
#define SA_PS_AF_CHANNEL_VALIDATION_PROGRESS_EVENT              0x8a83

/**************************************************************/
/* COMPONENT IDs                                              */
/**************************************************************/
#define SA_PS_POWER_SUPPLY_CID                                  0x8000
#define SA_PS_CPU_CID                                           0x8001
#define SA_PS_FPGA_CID                                          0x8002
#define SA_PS_IR_LASER_CID                                      0x8003
#define SA_PS_BOB_CID                                           0x8004
#define SA_PS_GPIO_ADC_CID                                      0x8100
#define SA_PS_WLS_ADC_CID                                       0x8110
#define SA_PS_WLS_PREAMP_CID                                    0x8112
#define SA_PS_CHANNEL_CID                                       0x8200
#define SA_PS_CHANNEL_PREAMP_CID                                0x8201
#define SA_PS_CHANNEL_SOMEGA_CID                                0x8202
#define SA_PS_CHANNEL_S2OMEGA_CID                               0x8203
#define SA_PS_CALC_SYS_CID                                      0x8210
#define SA_PS_ENV_SENSOR_CID                                    0x8310
#define SA_PS_COUNTER_CID                                       0x8400
                            

/**************************************************************/
/* WORKING DISTANCE                                           */
/**************************************************************/
/* Shrink Modes */
#define SA_PS_WORKING_DISTANCE_SHRINK_MODE_LEFT_RIGHT           0x00
#define SA_PS_WORKING_DISTANCE_SHRINK_MODE_LEFT                 0x01
#define SA_PS_WORKING_DISTANCE_SHRINK_MODE_RIGHT                0x02

/**************************************************************/
/* ENVIRONMENTAL MODULE                                       */
/**************************************************************/
/* Operation Modes */
#define SA_PS_ENV_OP_MODE_MANUAL                                0x00
#define SA_PS_ENV_OP_MODE_AUTOMATIC                             0x01
/* Values */
#define SA_PS_ENV_VALUE_TEMPERATURE                             0x00
#define SA_PS_ENV_VALUE_PRESSURE                                0x01
#define SA_PS_ENV_VALUE_HUMIDITY                                0x02

/**************************************************************/
/* GENERAL PURPOSE I/O                                        */
/**************************************************************/
/* DAC Sources */
#define SA_PS_GPIO_DAC_SOURCE_CONST                             0x00
#define SA_PS_GPIO_DAC_SOURCE_CALCULATION_SYSTEM                0x01
#define SA_PS_GPIO_DAC_SOURCE_SIGNAL_GENERATOR                  0x02
/* Digital Sources */
#define SA_PS_GPIO_DIG_SOURCE_CONST                             0x00
#define SA_PS_GPIO_DIG_SOURCE_TRIGGER                           0x01
#define SA_PS_GPIO_DIG_SOURCE_CLOCK_GENERATOR                   0x02

/**************************************************************/
/* TRIGGER SYSTEM                                             */
/**************************************************************/
/* Trigger Source Events */
#define SA_PS_TRIG_EVENT_NONE                                   0x00
#define SA_PS_TRIG_EVENT_SOFTWARE                               0x01
#define SA_PS_TRIG_EVENT_DATA_SOURCE_VALUE                      0x02
#define SA_PS_TRIG_EVENT_DATA_SOURCE_INCREMENT                  0x03
#define SA_PS_TRIG_EVENT_GPIO_TRIGGER                           0x04
#define SA_PS_TRIG_EVENT_EXTERNAL_TRIGGER                       0x05
#define SA_PS_TRIG_EVENT_INTERNAL                               0x06
/* Trigger Source Conditions */
#define SA_PS_TRIG_CONDITION_RISING                             0x00
#define SA_PS_TRIG_CONDITION_FALLING                            0x01
#define SA_PS_TRIG_CONDITION_EITHER                             0x02
#define SA_PS_TRIG_CONDITION_POSITIVE_LEVEL                     0x03
#define SA_PS_TRIG_CONDITION_NEGATIVE_LEVEL                     0x04
#define SA_PS_TRIG_CONDITION_POSITIVE_RANGE                     0x05
#define SA_PS_TRIG_CONDITION_NEGATIVE_RANGE                     0x06
/* Logic Operations */
#define SA_PS_LOGIC_OP_NONE                                     0x00
#define SA_PS_LOGIC_OP_OR                                       0x01
#define SA_PS_LOGIC_OP_NOR                                      0x02
#define SA_PS_LOGIC_OP_AND                                      0x03
#define SA_PS_LOGIC_OP_NAND                                     0x04
#define SA_PS_LOGIC_OP_XOR                                      0x05
#define SA_PS_LOGIC_OP_NXOR                                     0x06
/* Trigger Output Modes */
#define SA_PS_TRIGGER_OUTPUT_MODE_IMMEDIATE_NO_RESET            0x00
#define SA_PS_TRIGGER_OUTPUT_MODE_IMMEDIATE_RESET               0x01
#define SA_PS_TRIGGER_OUTPUT_MODE_DELAYED_NO_RESET              0x02
#define SA_PS_TRIGGER_OUTPUT_MODE_DELAYED_RESET                 0x03
/* Internal Events */
#define SA_PS_INTERNAL_EVENT_BEAM_INTERRUPT                     0x00
#define SA_PS_INTERNAL_EVENT_OVER_RANGE                         0x01


/**************************************************************/
/* DIGITAL DIFFERENTIAL INTERFACE                             */
/**************************************************************/
/* Modes */
#define SA_PS_DDI_MODE_QUADRATURE                               0x00
#define SA_PS_DDI_MODE_SERIAL_DATA                              0x01
/* Sources */
#define SA_PS_DDI_SOURCE_POSITION                               0x00
#define SA_PS_DDI_SOURCE_CALC_SYS                               0x01
/* Serial Clock Modes */
#define SA_PS_DDI_SERIAL_CLOCK_MODE_CPOL0_CPHA0                 0x00
#define SA_PS_DDI_SERIAL_CLOCK_MODE_CPOL0_CPHA1                 0x01
#define SA_PS_DDI_SERIAL_CLOCK_MODE_CPOL1_CPHA0                 0x02
#define SA_PS_DDI_SERIAL_CLOCK_MODE_CPOL1_CPHA1                 0x03
/* Serial Data Idle Polarities */
#define SA_PS_DDI_SERIAL_DATA_IDLE_POLARITY_LOW                 0x00
#define SA_PS_DDI_SERIAL_DATA_IDLE_POLARITY_HIGH                0x01

/**************************************************************/
/* CLOCK GENERATOR                                            */
/**************************************************************/
/* Modes */
#define SA_PS_CLK_GEN_MODE_DIRECT                               0x00
#define SA_PS_CLK_GEN_MODE_TRIGGERED                            0x01
/* States */
#define SA_PS_CLK_GEN_STATE_STOPPED                             0x00
#define SA_PS_CLK_GEN_STATE_ARMED                               0x01
#define SA_PS_CLK_GEN_STATE_RUNNING                             0x02

/**************************************************************/
/* STREAM GENERATOR                                           */
/**************************************************************/
/* Clock Sources */
#define SA_PS_SG_SOURCE_INTERNAL                                0x00
#define SA_PS_SG_SOURCE_TRIGGER                                 0x01

/**************************************************************/
/* COUNTER                                                    */
/**************************************************************/
/* Modes */
#define SA_PS_COUNTER_MODE_DIRECT                               0x00
#define SA_PS_COUNTER_MODE_TRIGGERED                            0x01
/* Sources */
#define SA_PS_COUNTER_SOURCE_INTERNAL                           0x00
#define SA_PS_COUNTER_SOURCE_TRIGGER                            0x01
/* States */
#define SA_PS_COUNTER_STATE_STOPPED                             0x00
#define SA_PS_COUNTER_STATE_ARMED                               0x01
#define SA_PS_COUNTER_STATE_RUNNING                             0x02

/**************************************************************/
/* POSITION CALCULATION                                       */
/**************************************************************/
/* Modes */
#define SA_PS_POS_CALC_MODE_DIRECT                              0x00
#define SA_PS_POS_CALC_MODE_TRIGGERED                           0x01
/* States */
#define SA_PS_POS_CALC_STATE_STOPPED                            0x00
#define SA_PS_POS_CALC_STATE_ARMED                              0x01
#define SA_PS_POS_CALC_STATE_RUNNING                            0x02

/**************************************************************/
/* CALCULATION SYSTEM                                         */
/**************************************************************/
/* Operands */
#define SA_PS_OPERAND_CONST                                     0x00
#define SA_PS_OPERAND_POSITION                                  0x01
#define SA_PS_OPERAND_ADC                                       0x02
#define SA_PS_OPERAND_ENV_VALUE                                 0x03
#define SA_PS_OPERAND_COUNTER                                   0x04
#define SA_PS_OPERAND_STAGE0                                    0x05
#define SA_PS_OPERAND_CALC_SYS                                  0x06
#define SA_PS_OPERAND_VELOCITY                                  0x07
#define SA_PS_OPERAND_ACCELERATION                              0x08
#define SA_PS_OPERAND_SIG_GEN                                   0x09
/* Operators */
#define SA_PS_OPERATOR_PLUS                                     0x00
#define SA_PS_OPERATOR_MINUS                                    0x01
#define SA_PS_OPERATOR_MULT                                     0x02
#define SA_PS_OPERATOR_DIV                                      0x03
#define SA_PS_OPERATOR_MAX                                      0x04
#define SA_PS_OPERATOR_MIN                                      0x05
/* Shapes */
#define SA_PS_CALC_SYS_SHAPE_NONE                               0x00
#define SA_PS_CALC_SYS_SHAPE_CUSTOM0                            0x80
#define SA_PS_CALC_SYS_SHAPE_CUSTOM1                            0x81
#define SA_PS_CALC_SYS_SHAPE_CUSTOM2                            0x82
#define SA_PS_CALC_SYS_SHAPE_CUSTOM3                            0x83

/**************************************************************/
/* SIGNAL GENERATOR                                           */
/**************************************************************/
/* Modes */
#define SA_PS_SIG_GEN_MODE_DIRECT                               0x00
#define SA_PS_SIG_GEN_MODE_TRIGGERED                            0x01
/* States */
#define SA_PS_SIG_GEN_STATE_STOPPED                             0x00
#define SA_PS_SIG_GEN_STATE_ARMED                               0x01
#define SA_PS_SIG_GEN_STATE_RUNNING                             0x02
/* Shape Selectors */
#define SA_PS_SIG_GEN_SHAPE_NONE                                0x00
#define SA_PS_SIG_GEN_SHAPE_SQUARE                              0x01
#define SA_PS_SIG_GEN_SHAPE_SIN                                 0x02
#define SA_PS_SIG_GEN_SHAPE_SAWTOOTH_P                          0x03
#define SA_PS_SIG_GEN_SHAPE_SAWTOOTH_N                          0x04
#define SA_PS_SIG_GEN_SHAPE_CUSTOM0                             0x80
#define SA_PS_SIG_GEN_SHAPE_CUSTOM1                             0x81
#define SA_PS_SIG_GEN_SHAPE_CUSTOM2                             0x82
#define SA_PS_SIG_GEN_SHAPE_CUSTOM3                             0x83
#define SA_PS_SIG_GEN_SHAPE_CUSTOM4                             0x84

/**************************************************************/
/* AUTO FUNCTIONS                                             */
/**************************************************************/
/* Adjustment States */
#define SA_PS_ADJUSTMENT_STATE_DISABLED                         0x00
#define SA_PS_ADJUSTMENT_STATE_MANUAL_ADJUST                    0x01
#define SA_PS_ADJUSTMENT_STATE_AUTO_ADJUST                      0x02
/* Channel Validation States */
#define SA_PS_CHANNEL_VALIDATION_STATE_DISABLED                 0x00
#define SA_PS_CHANNEL_VALIDATION_STATE_ENABLED                  0x01

/**************************************************************/
/* AUTO RESET MODES                                           */
/**************************************************************/
#define SA_PS_TRIGGER_AUTO_RESET_DISABLED                       0x00
#define SA_PS_TRIGGER_AUTO_RESET_ENABLED                        0x01
#define SA_PS_TRIGGER_AUTO_RESET_VALUE                          0x02

/**************************************************************/
/* DATA OBJECT NAMES                                          */
/**************************************************************/
#define SA_PS_SYSTEM_LOG_DATA_OBJECT                            "SystemLog"

/**************************************************************/
/* HEAD TYPES                                                 */
/**************************************************************/
#define SA_PS_HEAD_TYPE_C01                                     0x0000
#define SA_PS_HEAD_TYPE_C02                                     0x0001
#define SA_PS_HEAD_TYPE_C03                                     0x0002
#define SA_PS_HEAD_TYPE_F01                                     0x0100
/**************************************************************/
/* PROPERTIES                                                 */
/**************************************************************/
/* System Properties */
#define SA_PS_SYS_FULL_ACCESS_CONNECTION_PROP                   0x8000
#define SA_PS_SYS_LVDS_LS_CONNECTED_PROP                        0x8012
#define SA_PS_SYS_PILOT_LASER_ACTIVE_PROP                       0x8020
#define SA_PS_SYS_IS_STABLE_PROP                                0x8030
#define SA_PS_SYS_WORKING_DISTANCE_MIN_PROP                     0x8040
#define SA_PS_SYS_WORKING_DISTANCE_MAX_PROP                     0x8041
#define SA_PS_SYS_WORKING_DISTANCE_ACTIVATE_PROP                0x8042
#define SA_PS_SYS_WORKING_DISTANCE_SHRINK_MODE_PROP             0x8043
#define SA_PS_SYS_NETWORK_CURRENT_IP_PROP                       0x8052
#define SA_PS_SYS_NETWORK_CONFIG_ACTIVATE_PROP                  0x8060
#define SA_PS_SYS_NETWORK_CONFIG_DHCP_PROP                      0x8061
#define SA_PS_SYS_NETWORK_CONFIG_IP_PROP                        0x8062
#define SA_PS_SYS_NETWORK_CONFIG_GATEWAY_PROP                   0x8063
#define SA_PS_SYS_NETWORK_CONFIG_NETMASK_PROP                   0x8064
#define SA_PS_SYS_NETWORK_CONFIG_NAMESERVER_PROP                0x8065
#define SA_PS_SYS_NETWORK_CONFIG_DOMAINNAME_PROP                0x8066
#define SA_PS_SYS_NETWORK_MAC_PROP                              0x8070
#define SA_PS_SYS_HEAD_TYPE_CATEGORY_COUNT_PROP                 0x8081
#define SA_PS_SYS_HEAD_TYPE_COUNT_PROP                          0x8082
#define SA_PS_SYS_HEAD_TYPE_CATEGORY_NAME_PROP                  0x8083
#define SA_PS_SYS_HEAD_TYPE_NAME_PROP                           0x8084
#define SA_PS_SYS_FIBERLENGTH_HEAD_PROP                         0x8090
#define SA_PS_SYS_FIBERLENGTH_EXTENSION_PROP                    0x8091
#define SA_PS_SYS_POSITION_ALL_CH_PROP                          0x80a0
#define SA_PS_SYS_CONFIGURATION_SAVE_PROP                       0x80c0
#define SA_PS_SYS_CONFIGURATION_LOAD_PROP                       0x80c1
#define SA_PS_SYS_CONFIGURATION_NAME_PROP                       0x80c2
#define SA_PS_SYS_CONFIGURATION_COUNT_PROP                      0x80c3
#define SA_PS_SYS_FILTER_CUTOFF_FREQUENCY_PROP                  0x80de
#define SA_PS_SYS_FILTER_RATE_PROP                              0x80df
#define SA_PS_SYS_BOOTLOADER_VERSION_PROP                       0x80e0
#define SA_PS_SYS_BOOTLOADER_VERSION_STRING_PROP                0x80e1
#define SA_PS_SYS_HARDWARE_VERSION_PROP                         0x80e2
#define SA_PS_SYS_HARDWARE_VERSION_STRING_PROP                  0x80e3
#define SA_PS_SYS_PRODUCT_VERSION_PROP                          0x80e4
#define SA_PS_SYS_PRODUCT_VERSION_STRING_PROP                   0x80e5
#define SA_PS_SYS_FEATURE_COUNT_PROP                            0x80f0
#define SA_PS_SYS_FEATURE_NAME_PROP                             0x80f1
#define SA_PS_SYS_FEATURE_TIME_PROP                             0x80f2
#define SA_PS_SYS_FEATURE_EVALUATE_PROP                         0x80f3
/* Channel Properties */
#define SA_PS_CH_ENABLED_PROP                                   0x8100
#define SA_PS_CH_IS_VALID_PROP                                  0x8101
#define SA_PS_CH_POSITION_PROP                                  0x8102
#define SA_PS_CH_SCALE_INVERSION_PROP                           0x8103
#define SA_PS_CH_DEAD_PATH_CORRECTION_ENABLED_PROP              0x8110
#define SA_PS_CH_DEAD_PATH_PROP                                 0x8111
#define SA_PS_CH_HEAD_TYPE_PROP                                 0x8112
#define SA_PS_CH_BEAM_INTERRUPT_TOLERANCE_PROP                  0x8113
#define SA_PS_CH_SIGNAL_CORRECTION_ENABLED_PROP                 0x8114
#define SA_PS_CH_POS_CALC_ENABLED_PROP                          0x8115
#define SA_PS_CH_POS_CALC_MODE_PROP                             0x8116
#define SA_PS_CH_POS_CALC_TRIGGER_CONDITION_PROP                0x8117
#define SA_PS_CH_POS_CALC_TRIGGER_INDEX_PROP                    0x8118
#define SA_PS_CH_POS_CALC_TRIGGER_AUTO_RESET_MODE_PROP          0x8119
#define SA_PS_CH_POS_CALC_STATE_PROP                            0x811a

/* Environmental Sensor Properties */
#define SA_PS_ENV_SENSOR_OPERATION_MODE_PROP                    0x8200
#define SA_PS_ENV_SENSOR_STATE_PROP                             0x8201
#define SA_PS_ENV_SENSOR_VERSION_PROP                           0x820e
#define SA_PS_ENV_SENSOR_VERSION_STRING_PROP                    0x820f
#define SA_PS_ENV_SENSOR_TEMPERATURE_PROP                       0x8210
#define SA_PS_ENV_SENSOR_PRESSURE_PROP                          0x8211
#define SA_PS_ENV_SENSOR_HUMIDITY_PROP                          0x8212
#define SA_PS_ENV_USER_TEMPERATURE_PROP                         0x8220
#define SA_PS_ENV_USER_PRESSURE_PROP                            0x8221
#define SA_PS_ENV_USER_HUMIDITY_PROP                            0x8222
/* GPIO Properties */
#define SA_PS_GPIO_DAC_COUNT_PROP                               0x8310
#define SA_PS_GPIO_DAC_BIT_WIDTH_PROP                           0x8311
#define SA_PS_GPIO_DAC_SAMPLE_RATE_PROP                         0x8312
#define SA_PS_GPIO_DAC_CONST_VALUE_PROP                         0x8313
#define SA_PS_GPIO_DAC_SOURCE_PROP                              0x8318
#define SA_PS_GPIO_DAC_CALC_SYS_INDEX_PROP                      0x8319
#define SA_PS_GPIO_DAC_SIG_GEN_INDEX_PROP                       0x831a
#define SA_PS_GPIO_DIGITAL_CONST_VALUE_PROP                     0x8320
#define SA_PS_GPIO_DIGITAL_DIRECTION_PROP                       0x8321
#define SA_PS_GPIO_DIGITAL_SOURCE_PROP                          0x8322
#define SA_PS_GPIO_DIGITAL_TRIGGER_INDEX_PROP                   0x8323
#define SA_PS_GPIO_DIGITAL_CLK_GEN_INDEX_PROP                   0x8324
/* Trigger System Properties */
#define SA_PS_TRIGGER_SOURCE_COUNT_PROP                         0x8400
#define SA_PS_TRIGGER_SOURCE_RESET_PROP                         0x8401
#define SA_PS_TRIGGER_SOURCE_EVENT_PROP                         0x8402
#define SA_PS_TRIGGER_SOURCE_INDEX0_PROP                        0x8403
#define SA_PS_TRIGGER_SOURCE_INDEX1_PROP                        0x8404
#define SA_PS_TRIGGER_SOURCE_CONDITION_PROP                     0x8405
#define SA_PS_TRIGGER_SOURCE_VALUE0_PROP                        0x8406
#define SA_PS_TRIGGER_SOURCE_VALUE1_PROP                        0x8407
#define SA_PS_TRIGGER_COUNT_PROP                                0x8410
#define SA_PS_TRIGGER_AND_MASK_PROP                             0x8411
#define SA_PS_TRIGGER_OR_MASK_PROP                              0x8412
#define SA_PS_TRIGGER_LOGIC_OPERATION_PROP                      0x8413
#define SA_PS_TRIGGER_OUTPUT_DELAY_PROP                         0x8414
#define SA_PS_TRIGGER_OUTPUT_MODE_PROP                          0x8415
#define SA_PS_TRIGGER_SOFT_TRIGGER_PROP                         0x8420
#define SA_PS_TRIGGER_SOURCE_STATE_PROP                         0x8430
#define SA_PS_TRIGGER_STATE_PROP                                0x8431
/* Digital Differential Interface Properties */
#define SA_PS_DDI_ENABLED_PROP                                  0x8500
#define SA_PS_DDI_MODE_PROP                                     0x8501
#define SA_PS_DDI_SOURCE_PROP                                   0x8502
#define SA_PS_DDI_QUAD_STEP_SIZE_PROP                           0x8510
#define SA_PS_DDI_QUAD_FREQUENCY_PROP                           0x8511
#define SA_PS_DDI_QUAD_AVAILABLE_FREQUENCIES_PROP               0x8512
#define SA_PS_DDI_SERIAL_CLOCK_MODE_PROP                        0x8520
#define SA_PS_DDI_SERIAL_CLOCK_FREQUENCY_PROP                   0x8521
#define SA_PS_DDI_SERIAL_CLOCK_PAUSE_DELAY_PROP                 0x8522
#define SA_PS_DDI_SERIAL_DATA_BITWIDTH_PROP                     0x8523
#define SA_PS_DDI_SERIAL_DATA_RESOLUTION_SHIFT_PROP             0x8524
#define SA_PS_DDI_SERIAL_DATA_IDLE_POLARITY_PROP                0x8525
/* Clock Generator Properties */
#define SA_PS_CLOCK_GENERATOR_ENABLE_SYNC_PROP                  0x8600
#define SA_PS_CLOCK_GENERATOR_DISABLE_SYNC_PROP                 0x8601
#define SA_PS_CLOCK_GENERATOR_ENABLED_PROP                      0x8610
#define SA_PS_CLOCK_GENERATOR_MODE_PROP                         0x8611
#define SA_PS_CLOCK_GENERATOR_FREQUENCY_PROP                    0x8612
#define SA_PS_CLOCK_GENERATOR_PHASE_PROP                        0x8613
#define SA_PS_CLOCK_GENERATOR_START_TRIGGER_INDEX_PROP          0x8614
#define SA_PS_CLOCK_GENERATOR_STOP_TRIGGER_INDEX_PROP           0x8615
#define SA_PS_CLOCK_GENERATOR_TRIGGER_AUTO_RESET_MODE_PROP      0x8616
#define SA_PS_CLOCK_GENERATOR_STATE_PROP                        0x8617
/* Stream Generator Properties */
#define SA_PS_SG_CLOCK_SOURCE_PROP                              0x8700
#define SA_PS_SG_CLOCK_TRIGGER_INDEX_PROP                       0x8701
#define SA_PS_SG_TRIGGER_START_INDEX_PROP                       0x8710
#define SA_PS_SG_TRIGGER_STOP_INDEX_PROP                        0x8711
#define SA_PS_SG_TRIGGER_POST_FRAME_COUNT_PROP                  0x8712
#define SA_PS_SG_TRIGGER_AUTO_RESET_MODE_PROP                   0x8713
/* Counter Properties */
#define SA_PS_COUNTER_ENABLE_SYNC_PROP                          0x8900
#define SA_PS_COUNTER_DISABLE_SYNC_PROP                         0x8901
#define SA_PS_COUNTER_ENABLED_PROP                              0x8910
#define SA_PS_COUNTER_MODE_PROP                                 0x8911
#define SA_PS_COUNTER_SOURCE_PROP                               0x8912
#define SA_PS_COUNTER_SOURCE_TRIGGER_INDEX_PROP                 0x8913
#define SA_PS_COUNTER_START_TRIGGER_INDEX_PROP                  0x8914
#define SA_PS_COUNTER_STOP_TRIGGER_INDEX_PROP                   0x8915
#define SA_PS_COUNTER_TRIGGER_AUTO_RESET_MODE_PROP              0x8916
#define SA_PS_COUNTER_STATE_PROP                                0x8917
#define SA_PS_COUNTER_START_VALUE_PROP                          0x8920
/* Calculation System Properties */
#define SA_PS_CALC_SYS_STAGE0_OPERAND_SELECT_PROP               0x8a00
#define SA_PS_CALC_SYS_STAGE0_CONST_PROP                        0x8a01
#define SA_PS_CALC_SYS_STAGE0_POS_INDEX_SELECT_PROP             0x8a02
#define SA_PS_CALC_SYS_STAGE0_ADC_INDEX_SELECT_PROP             0x8a03
#define SA_PS_CALC_SYS_STAGE0_ENV_VALUE_SELECT_PROP             0x8a04
#define SA_PS_CALC_SYS_STAGE0_COUNTER_INDEX_SELECT_PROP         0x8a05
#define SA_PS_CALC_SYS_STAGE0_OPERAND_INVERSION_PROP            0x8a06
#define SA_PS_CALC_SYS_STAGE0_VEL_INDEX_SELECT_PROP             0x8a07
#define SA_PS_CALC_SYS_STAGE0_ACC_INDEX_SELECT_PROP             0x8a08
#define SA_PS_CALC_SYS_STAGE0_OPERATOR_SELECT_PROP              0x8a10
#define SA_PS_CALC_SYS_STAGE0_SIG_GEN_INDEX_SELECT_PROP         0x8a11
#define SA_PS_CALC_SYS_STAGE1_OPERAND_SELECT_PROP               0x8a20
#define SA_PS_CALC_SYS_STAGE1_CONST_PROP                        0x8a21
#define SA_PS_CALC_SYS_STAGE1_CALC_SYS_INDEX_SELECT_PROP        0x8a22
#define SA_PS_CALC_SYS_STAGE1_OPERATOR_SELECT_PROP              0x8a30
#define SA_PS_CALC_SYS_SHAPE_ENABLED_PROP                       0x8a40
#define SA_PS_CALC_SYS_SHAPE_PROP                               0x8a41
#define SA_PS_CALC_SYS_OUTPUT_LABEL_PROP                        0x8a42
#define SA_PS_CALC_SYS_COUNT_PROP                               0x8a43

/* Signal Generator Properties */
#define SA_PS_SIGNAL_GENERATOR_ENABLE_SYNC_PROP                 0x8b00
#define SA_PS_SIGNAL_GENERATOR_DISABLE_SYNC_PROP                0x8b01
#define SA_PS_SIGNAL_GENERATOR_ENABLED_PROP                     0x8b02
#define SA_PS_SIGNAL_GENERATOR_FREQUENCY_PROP                   0x8b03
#define SA_PS_SIGNAL_GENERATOR_AMPLITUDE_PROP                   0x8b04
#define SA_PS_SIGNAL_GENERATOR_OFFSET_PROP                      0x8b05
#define SA_PS_SIGNAL_GENERATOR_PHASE_PROP                       0x8b06
#define SA_PS_SIGNAL_GENERATOR_SHAPE_PROP                       0x8b08
#define SA_PS_SIGNAL_GENERATOR_MODE_PROP                        0x8b09
#define SA_PS_SIGNAL_GENERATOR_START_TRIGGER_INDEX_PROP         0x8b0a
#define SA_PS_SIGNAL_GENERATOR_STOP_TRIGGER_INDEX_PROP          0x8b0b
#define SA_PS_SIGNAL_GENERATOR_TRIGGER_AUTO_RESET_MODE_PROP     0x8b0c
#define SA_PS_SIGNAL_GENERATOR_STATE_PROP                       0x8b0d
/* Break-Out-Box Properties */
#define SA_PS_BOB_DEVICE_SERIAL_NUMBER_PROP                     0x8c00
#define SA_PS_BOB_HARDWARE_VERSION_PROP                         0x8c02
#define SA_PS_BOB_HARDWARE_VERSION_STRING_PROP                  0x8c03
#define SA_PS_BOB_FIRMWARE_VERSION_PROP                         0x8c04
#define SA_PS_BOB_FIRMWARE_VERSION_STRING_PROP                  0x8c05
/* Auto Function Properties */
#define SA_PS_AF_ADJUSTMENT_STATE_PROP                          0x9010
#define SA_PS_AF_ADJUSTMENT_PROGRESS_PROP                       0x9011
#define SA_PS_AF_ADJUSTMENT_SIGNAL_CONTROL_ACTIVE_PROP          0x9012
#define SA_PS_AF_ADJUSTMENT_AUTOSTART_AUTOADJUST_ACTIVE_PROP    0x9013
#define SA_PS_AF_ADJUSTMENT_RESULT_SAVE_PROP                    0x901a
#define SA_PS_AF_ADJUSTMENT_RESULT_LOAD_PROP                    0x901b
#define SA_PS_AF_ADJUSTMENT_RESULT_NAME_PROP                    0x901c
#define SA_PS_AF_ADJUSTMENT_RESULT_COUNT_PROP                   0x901d

#define SA_PS_AF_CHANNEL_VALIDATION_STATE_PROP                  0x9040

#endif /* SMARACT_SI_CONSTANTS_PS_H */
