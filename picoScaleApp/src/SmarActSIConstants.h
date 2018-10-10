/**********************************************************************
* SmarAct Sensor Interface Constants
* Copyright (c) 2015 SmarAct GmbH
*
* File name: SmarActSIConstants.h
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

#ifndef SMARACT_SI_CONSTANTS_H
#define SMARACT_SI_CONSTANTS_H




#define SA_SI_TIMEOUT_INFINITE                          0xffffffff

#define SA_SI_DISABLED                                  0x00
#define SA_SI_ENABLED                                   0x01

#define SA_SI_STRING_MAX_LENGTH                         63


/***************/
/* ERROR CODES */
/***************/

#define SA_SI_OK                                        0x0000
#define SA_SI_UNKNOWN_COMMAND_ERROR                     0x0001
#define SA_SI_PACKET_SIZE_ERROR                         0x0002
#define SA_SI_TIMEOUT_ERROR                             0x0004
#define SA_SI_PROTOCOL_ERROR                            0x0005
#define SA_SI_BUFFER_UNDERFLOW_ERROR                    0x000c
#define SA_SI_BUFFER_OVERFLOW_ERROR                     0x000d
#define SA_SI_INVALID_PACKET_ERROR                      0x0010
#define SA_SI_INVALID_STREAM_PACKET_ERROR               0x0011
#define SA_SI_INVALID_PROPERTY_ERROR                    0x0012
#define SA_SI_INVALID_PARAMETER_ERROR                   0x0013
#define SA_SI_INVALID_CHANNEL_INDEX_ERROR               0x0014
#define SA_SI_INVALID_DSOURCE_INDEX_ERROR               0x0015
#define SA_SI_INVALID_DATA_TYPE_ERROR                   0x0016
#define SA_SI_PERMISSION_DENIED_ERROR                   0x001f
#define SA_SI_NO_DATA_SOURCES_ENABLED_ERROR             0x0020
#define SA_SI_STREAMING_ACTIVE_ERROR                    0x0021
#define SA_SI_DATA_SOURCE_NOT_STREAMABLE_ERROR          0x0022
#define SA_SI_UNKNOWN_DATA_OBJECT_ERROR                 0x0030
#define SA_SI_COMMAND_NOT_PROCESSABLE_ERROR             0x00ff

#define SA_SI_FEATURE_NOT_SUPPORTED_ERROR               0x7ffd
#define SA_SI_NOT_IMPLEMENTED_ERROR                     0x7ffe
#define SA_SI_OTHER_ERROR                               0x7fff


/**************/
/* DATA TYPES */
/**************/
#define SA_SI_INT8_DTYPE                                0x00
#define SA_SI_UINT8_DTYPE                               0x01
#define SA_SI_INT16_DTYPE                               0x02
#define SA_SI_UINT16_DTYPE                              0x03
#define SA_SI_INT32_DTYPE                               0x06
#define SA_SI_UINT32_DTYPE                              0x07
#define SA_SI_INT48_DTYPE                               0x0a
#define SA_SI_UINT48_DTYPE                              0x0b
#define SA_SI_INT64_DTYPE                               0x0e
#define SA_SI_UINT64_DTYPE                              0x0f
#define SA_SI_FLOAT32_DTYPE                             0x10
#define SA_SI_FLOAT64_DTYPE                             0x11
#define SA_SI_STRING_DTYPE                              0x12


/*******************/
/* BASE UNIT TYPES */
/*******************/

#define SA_SI_NO_UNIT                                   0x0000
#define SA_SI_PERCENT_UNIT                              0x0001
#define SA_SI_METRE_UNIT                                0x0002
#define SA_SI_DEGREE_UNIT                               0x0003
#define SA_SI_SECOND_UNIT                               0x0004
#define SA_SI_HERTZ_UNIT                                0x0005
#define SA_SI_KILOGRAM_UNIT                             0x0006
#define SA_SI_NEWTON_UNIT                               0x0007
#define SA_SI_WATT_UNIT                                 0x0008
#define SA_SI_JOULE_UNIT                                0x0009
#define SA_SI_VOLT_UNIT                                 0x000a
#define SA_SI_AMPERE_UNIT                               0x000b
#define SA_SI_OHM_UNIT                                  0x000c
#define SA_SI_PASCAL_UNIT                               0x000d
#define SA_SI_KELVIN_UNIT                               0x000e
#define SA_SI_DEGREE_CELSIUS_UNIT                       0x000f
#define SA_SI_SQUARE_METRE_UNIT                         0x0010
#define SA_SI_METRE_PER_SECOND_UNIT                     0x0011
#define SA_SI_METRE_PER_SQUARE_SECOND_UNIT              0x0012


/*********************/
/* DATA SOURCE TYPES */
/*********************/

#define SA_SI_ANALOG_RAW_DSOURCE                        0x0000
#define SA_SI_SIN_RAW_DSOURCE                           0x0001
#define SA_SI_COS_RAW_DSOURCE                           0x0002
#define SA_SI_SIN_QUALITY_DSOURCE                       0x0003
#define SA_SI_COS_QUALITY_DSOURCE                       0x0004
#define SA_SI_SIN_CORRECTED_DSOURCE                     0x0005
#define SA_SI_COS_CORRECTED_DSOURCE                     0x0006
#define SA_SI_POSITION_DSOURCE                          0x0008
#define SA_SI_STATUS_DSOURCE                            0x0009
#define SA_SI_TEMPERATURE_DSOURCE                       0x000a
#define SA_SI_HUMIDITY_DSOURCE                          0x000b
#define SA_SI_PRESSURE_DSOURCE                          0x000c
#define SA_SI_VELOCITY_DSOURCE                          0x000d
#define SA_SI_ACCELERATION_DSOURCE                      0x000e
#define SA_SI_COUNTER_DSOURCE                           0x000f
#define SA_SI_GENERIC_DSOURCE                           0x0010
#define SA_SI_AMPLITUDE_DSOURCE                         0x0011
#define SA_SI_FREQUENCY_DSOURCE                         0x0012
#define SA_SI_PHASE_DSOURCE                             0x0013
#define SA_SI_RADIUS_DSOURCE                            0x0014
#define SA_SI_ANGLE_DSOURCE                             0x0015


/*********************/
/* COMPRESSION MODES */
/*********************/

#define SA_SI_NO_COMPRESSION_MODE                       0x0000
#define SA_SI_LOWER16ABS_COMPRESSION_MODE               0x0002


/***************/
/* EVENT TYPES */
/***************/

#define SA_SI_STREAM_ABORTED_EVENT                      0x0001


/*******************/
/* STREAMING MODES */
/*******************/

#define SA_SI_NO_STREAMING                              0x00
#define SA_SI_DIRECT_STREAMING                          0x01
#define SA_SI_TRIGGERED_STREAMING                       0x02


/**************/
/* OPEN MODES */
/**************/

#define SA_SI_READ_MODE                                 0x01
#define SA_SI_WRITE_MODE                                0x02


/**********************/
/* CONNECTION OPTIONS */
/**********************/

#define SA_SI_CRC_MODE_OPTION                           0x0001


/*******************************/
/* STREAM STOPPED REASON CODES */
/*******************************/

#define SA_SI_STOPPED_BY_USER                           0x0001
#define SA_SI_STOPPED_BY_TRIGGER                        0x0002
#define SA_SI_STOPPED_BY_BUFFER_OVERFLOW                0x00f1


/**************/
/* PROPERTIES */
/**************/

/* device properties */
#define SA_SI_PROTOCOL_VERSION_PROP                     0x0000
#define SA_SI_PROTOCOL_VERSION_STRING_PROP              0x0001
#define SA_SI_DEVICE_TYPE_PROP                          0x0002
#define SA_SI_DEVICE_ID_PROP                            0x0003
#define SA_SI_DEVICE_SERIAL_NUMBER_PROP                 0x0003
#define SA_SI_DEVICE_NAME_PROP                          0x0004
#define SA_SI_NUMBER_OF_FIRMWARE_VERSIONS_PROP          0x0005
#define SA_SI_FIRMWARE_VERSION_PROP                     0x0006
#define SA_SI_FIRMWARE_VERSION_STRING_PROP              0x0007
#define SA_SI_MAX_DATA_OBJECT_CHUNK_SIZE_PROP           0x0008

#define SA_SI_NUMBER_OF_CHANNELS_PROP                   0x0011

#define SA_SI_MAX_FRAME_RATE_PROP                       0x0020
#define SA_SI_FRAME_RATE_PROP                           0x0021
#define SA_SI_MAX_FRAME_AGGREGATION_PROP                0x0022
#define SA_SI_FRAME_AGGREGATION_PROP                    0x0023
#define SA_SI_FRAME_INDEX_ENABLED_PROP                  0x0024
#define SA_SI_PRECISE_FRAME_RATE_PROP                   0x0025

#define SA_SI_EVENT_NOTIFICATION_ENABLED_PROP           0x0030

#define SA_SI_STREAMING_ACTIVE_PROP                     0x0040
#define SA_SI_STREAMING_MODE_PROP                       0x0041

/* channel properties */
#define SA_SI_NUMBER_OF_DATA_SOURCES_PROP               0x1001
#define SA_SI_CHANNEL_NAME_PROP                         0x1002

/* data source properties */
#define SA_SI_DATA_SOURCE_TYPE_PROP                     0x2001
#define SA_SI_DATA_TYPE_PROP                            0x2002
#define SA_SI_AVAILABLE_COMPRESSION_MODES_PROP          0x2003
#define SA_SI_COMPRESSION_MODE_PROP                     0x2004
#define SA_SI_STREAMING_ENABLED_PROP                    0x2005
#define SA_SI_BASE_UNIT_PROP                            0x2006
#define SA_SI_BASE_RESOLUTION_PROP                      0x2007
#define SA_SI_RESOLUTION_SHIFT_PROP                     0x2008
#define SA_SI_DATA_SOURCE_NAME_PROP                     0x2009
#define SA_SI_IS_STREAMABLE_PROP                        0x200a
#define SA_SI_COMPONENT_ID_PROP                         0x200b
#define SA_SI_COMPONENT_INDEX_PROP                      0x200c

#endif /* SMARACT_SI_CONSTANTS_H */

