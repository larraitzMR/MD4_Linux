/******************************************************************************
  * \attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2021 STMicroelectronics</center></h2>
  *
  * Licensed under ST MYLIBERTY SOFTWARE LICENSE AGREEMENT (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        www.st.com/myliberty
  *
  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an "AS IS" BASIS,
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied,
  * AND SPECIFICALLY DISCLAIMING THE IMPLIED WARRANTIES OF MERCHANTABILITY,
  * FITNESS FOR A PARTICULAR PURPOSE, AND NON-INFRINGEMENT.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
******************************************************************************/

//
#if !defined __STUHFL_DL_ST25RU3993_EVAL_H
#define __STUHFL_DL_ST25RU3993_EVAL_H

#include "stuhfl.h"

#ifdef __cplusplus
extern "C"
{
#endif //__cplusplus

#pragma pack(push, 1)

/** parameters for command TUNER_TABLE_DEFAULT */
#define STUHFL_D_RESET_DEFAULT_ALL_FREQS 0

/** define to identify Cin cap of tuner. */
#define STUHFL_D_TUNER_CIN           0x01
/** define to identify Clen cap of tuner. */
#define STUHFL_D_TUNER_CLEN          0x02
/** define to identify Cout cap of tuner. */
#define STUHFL_D_TUNER_COUT          0x04

/** Definition of the frequencies maximum value */
#define STUHFL_D_FREQUENCY_MAX_VALUE 999000U
#define STUHFL_D_DEFAULT_FREQUENCY   865700U

typedef struct {
    uint8_t                             addr;   /**< I Param: Register address */
    uint8_t                             data;   /**< I/O Param: Register data */
} STUHFL_T_ST25RU3993_Register;
#define STUHFL_O_ST25RU3993_REGISTER_INIT()     {0, 0}

#define STUHFL_D_POWER_DOWN              0       /** value for #readerPowerDownMode. Activates power down mode. (EN low)*/
#define STUHFL_D_POWER_NORMAL            1       /** value for #readerPowerDownMode. Activates normal mode. (EN high, RF off, stdby 0)*/
#define STUHFL_D_POWER_NORMAL_RF         2       /** value for #readerPowerDownMode. Activates normal mode with rf field on. (EN high, RF off, stdby 0)*/
#define STUHFL_D_POWER_STANDBY           3       /** value for #readerPowerDownMode. Activates standby mode. (EN high, RF off, stdby 1)*/

#define STUHFL_D_RWD_CFG_ID_POWER_DOWN_MODE   0x00    /**< Reader configuration ID for Power down mode */
#define STUHFL_D_RWD_CFG_ID_EXTVCO            0x01    /**< Reader configuration ID for external voltage controlled oscilator */
#define STUHFL_D_RWD_CFG_ID_POWER_AMPLIFIER   0x02    /**< Reader configuration ID for power amplifier */
#define STUHFL_D_RWD_CFG_ID_INPUT             0x03    /**< Reader configuration ID for input */
#define STUHFL_D_RWD_CFG_ID_ANTENNA_SWITCH    0x04    /**< Reader configuration ID for antenna switch */
#define STUHFL_D_RWD_CFG_ID_TUNER             0x05    /**< Reader configuration ID for tuner */
#define STUHFL_D_RWD_CFG_ID_HARDWARE_ID_NUM   0x06    /**< Reader configuration ID for hardware ID */

#define STUHFL_D_INTERPOLATION_VALUES		  0x07U
#define STUHFL_D_ATT_PWR_TABLE_SIZE			  0x0CU

typedef struct {
    uint8_t                             id;     /**< I Param: Reader configuration ID */
    uint8_t                             value;  /**< I/O Param: Value of corresponding configuration */
} STUHFL_T_ST25RU3993_RwdConfig;
#define STUHFL_O_ST25RU3993_RWD_CONFIG_INIT()    {STUHFL_D_RWD_CFG_ID_POWER_DOWN_MODE, STUHFL_D_POWER_NORMAL}

typedef struct {
    uint8_t                             blf;        /**< I Param: Link Frequency for which filter value shall be applied */
    uint8_t                             coding;     /**< I Param: Coding for which filter value shall be applied */
    uint8_t                             value;      /**< I/O Param: RX filter value */
} STUHFL_T_ST25RU3993_RxFilter;
#define STUHFL_O_ST25RU3993_RX_FILTER_INIT()     {STUHFL_D_GEN2_BLF_256, STUHFL_D_GEN2_CODING_MILLER8, 0x34}

typedef struct {
    uint8_t                             blf;        /**< I Param: Link Frequency for which highPass/lowPass values shall be applied */
    uint8_t                             coding;     /**< I Param: Coding for which highPass/lowPass values shall be applied */
    uint8_t                             highPass;   /**< I/O Param: High pass filter value. Range [0..15]. Step size = 4% */
    uint8_t                             lowPass;    /**< I/O Param: Low pass filter value. Range [0..15]. Step size = 4% */
} STUHFL_T_ST25RU3993_FilterCalibration;
#define STUHFL_O_ST25RU3993_FILTER_CALIBRATION_INIT()    {STUHFL_D_GEN2_BLF_256, STUHFL_D_GEN2_CODING_MILLER8, 0x08, 0x08}

/* Set */
#define STUHFL_D_ANTENNA_POWER_MODE_ON               ((uint8_t)0x00)
#define STUHFL_D_ANTENNA_POWER_MODE_OFF              ((uint8_t)0xFF)
typedef struct {
    uint8_t                             mode;       /**< I/O Param: Antenna Power mode */
    uint16_t                            timeout;    /**< I/O Param: Timeout before settings will be applied */
    uint32_t                            frequency;  /**< I/O Param: Frequency to be used */
} STUHFL_T_ST25RU3993_AntennaPower;
#define STUHFL_O_ST25RU3993_ANTENNA_POWER_INIT()     {STUHFL_D_ANTENNA_POWER_MODE_OFF, 0, STUHFL_D_DEFAULT_FREQUENCY}

/* Get */
typedef struct {
    uint32_t                            frequency;  /**< I Param: Frequency for RSSI */
    uint8_t                             rssiLogI;   /**< O param: I parameter of logarithmic scaled RSSI */
    uint8_t                             rssiLogQ;   /**< O param: Q parameter of logarithmic scaled RSSI */
} STUHFL_T_ST25RU3993_FreqRssi;
#define STUHFL_O_ST25RU3993_FREQ_RSSI_INIT()     {STUHFL_D_DEFAULT_FREQUENCY, 0, 0}

/* Get */
typedef struct {
    uint32_t                            frequency;              /**< I Param: Frequency to be used for the measurement */
    bool                                applyTunerSetting;      /**< I Param: flag to apply tuner settings for frequency */
    int8_t                              reflectedI;             /**< O Param: Reflected I */
    int8_t                              reflectedQ;             /**< O Param: Reflected Q */
} STUHFL_T_ST25RU3993_FreqReflectedPowerInfo;
#define STUHFL_O_ST25RU3993_FREQ_REFLECTED_POWER_INFO_INIT()     {STUHFL_D_DEFAULT_FREQUENCY, false, 0, 0}

#define STUHFL_D_GEN2_TIMING_USE_DEFAULT_T4MIN        0       /**< T4 Min default value will be used (Gen2: 2*3*Tari: 75us @TARI_12_50). */
typedef struct {
    uint16_t                            T4Min;              /**< I/O Param: T4 minimum value in us. */
} STUHFL_T_ST25RU3993_Gen2_Timings;
#define STUHFL_O_ST25RU3993_GEN2_TIMINGS_INIT()         {STUHFL_D_GEN2_TIMING_USE_DEFAULT_T4MIN}

#define STUHFL_D_PROFILE_CUSTOM              0
#define STUHFL_D_PROFILE_EUROPE              1
#define STUHFL_D_PROFILE_USA                 2
#define STUHFL_D_PROFILE_JAPAN               3
#define STUHFL_D_PROFILE_CHINA               4
#define STUHFL_D_PROFILE_CHINA2              5
#define STUHFL_D_NUM_SAVED_PROFILES          6

#define STUHFL_D_PROFILE_NEWTUNING           0xFF

typedef struct/* STUHFL_DEPRECATED */STUHFL_S_ST25RU3993_Freq_Profile {
    uint8_t                             profile;    /**< I Param: Frequency profile */
} STUHFL_T_ST25RU3993_FreqProfile;
#define STUHFL_O_ST25RU3993_FREQ_PROFILE_INIT()     {STUHFL_D_PROFILE_EUROPE}

typedef struct/* STUHFL_DEPRECATED */STUHFL_S_ST25RU3993_Freq_Profile_Add2Custom {
    bool                                clearList;  /**< I Param: Flag to clear all tuning entries */
    uint32_t                            frequency;  /**< I Param: Frequency to append to custom profile */
} STUHFL_T_ST25RU3993_FreqProfileAddToCustom;
#define STUHFL_O_ST25RU3993_FREQ_PROFILE_ADD_TO_CUSTOM_INIT()    {true, STUHFL_D_DEFAULT_FREQUENCY}

/* Get */
typedef struct/* STUHFL_DEPRECATED */STUHFL_S_ST25RU3993_Freq_Profile_Info {
    uint8_t                             profile;        /**< O Param: Current used profile index */
    uint32_t                            minFrequency;   /**< O Param: Minimum frequency for profile */
    uint32_t                            maxFrequency;   /**< O Param: Maximum frequency for profile */
    uint8_t                             numFrequencies; /**< O Param: Number of frequency entries for profile */
} STUHFL_T_ST25RU3993_FreqProfileInfo;
#define STUHFL_O_ST25RU3993_FREQ_PROFILE_INFO_INIT()     {STUHFL_D_PROFILE_EUROPE, 865700, 867500, 4}

#define STUHFL_D_MAX_ANTENNA                     4U
#define STUHFL_D_MAX_FREQUENCY                   53U

typedef struct {
    uint8_t cin ;           /**< I/O Param: IN capacitance of tuning PI network */
    uint8_t clen;           /**< I/O Param: LEN capacitance of tuning PI network */
    uint8_t cout;           /**< I/O Param: OUT capacitance of tuning PI network */
} STUHFL_T_ST25RU3993_Caps;
#define STUHFL_O_ST25RU3993_CAPS_INIT()      {0, 0, 0}

typedef struct {
    uint32_t                            frequency;                  /**< I/O Param: Frequency to be used for channel item */
    STUHFL_T_ST25RU3993_Caps            caps;                       /**< I/O Param: Tuning capacitors for this frequency */
    uint8_t                             rfu1;                       /** rfu */
    uint8_t                             rfu2;                       /** rfu */
} STUHFL_T_ST25RU3993_ChannelItem;
#define STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT()      {STUHFL_D_DEFAULT_FREQUENCY, STUHFL_O_ST25RU3993_CAPS_INIT(), 0, 0}

typedef struct {
    uint8_t                             antenna;                    /**< I Param: Antenna to which the ChannelList belongs */
    bool                                persistent;                 /**< I Param: Set/Get channel list to/from persistent flash memory */
    uint8_t                             numFrequencies;             /**< I/O Param: Number of valid frequencies in the frequency data array*/
    uint8_t                             channelListIdx;             /**< I/O Param: Current itemList index in channel list */
    STUHFL_T_ST25RU3993_ChannelItem     itemList[STUHFL_D_MAX_FREQUENCY];        /**< I/O Param: Tuning capacitors for each frequency */
} STUHFL_T_ST25RU3993_ChannelList;
#define STUHFL_O_ST25RU3993_CHANNEL_LIST_INIT()   { STUHFL_D_ANTENNA_1, false, 1, 0,    \
                                                    {       \
                                                    STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), \
                                                    STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), \
                                                    STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), \
                                                    STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), \
                                                    STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), \
                                                    STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), \
                                                    STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), \
                                                    STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), \
                                                    STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), \
                                                    STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), \
                                                    STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT()  \
                                                    }}

#define STUHFL_O_ST25RU3993_CHANNEL_LIST_EUROPE_INIT()      {STUHFL_D_ANTENNA_1, false, 4, 0,    \
                                                                {       \
                                                                {866900,STUHFL_O_ST25RU3993_CAPS_INIT(),0,0}, {865700,STUHFL_O_ST25RU3993_CAPS_INIT(),0,0}, {866300,STUHFL_O_ST25RU3993_CAPS_INIT(),0,0}, {867500,STUHFL_O_ST25RU3993_CAPS_INIT(),0,0}, STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), \
                                                                STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), \
                                                                STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), \
                                                                STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), \
                                                                STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), \
                                                                STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), \
                                                                STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), \
                                                                STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), \
                                                                STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), \
                                                                STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), \
                                                                STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT()  \
                                                                }}

#define STUHFL_O_ST25RU3993_CHANNEL_LIST_USA_INIT()         {STUHFL_D_ANTENNA_1, false, 50, 0,    \
                                                                {       \
                                                                {902750,STUHFL_O_ST25RU3993_CAPS_INIT(),0,0}, {915250,STUHFL_O_ST25RU3993_CAPS_INIT(),0,0}, {903250,STUHFL_O_ST25RU3993_CAPS_INIT(),0,0}, {915750,STUHFL_O_ST25RU3993_CAPS_INIT(),0,0}, {903750,STUHFL_O_ST25RU3993_CAPS_INIT(),0,0}, \
                                                                {916250,STUHFL_O_ST25RU3993_CAPS_INIT(),0,0}, {904250,STUHFL_O_ST25RU3993_CAPS_INIT(),0,0}, {916750,STUHFL_O_ST25RU3993_CAPS_INIT(),0,0}, {904750,STUHFL_O_ST25RU3993_CAPS_INIT(),0,0}, {917250,STUHFL_O_ST25RU3993_CAPS_INIT(),0,0}, \
                                                                {905250,STUHFL_O_ST25RU3993_CAPS_INIT(),0,0}, {917750,STUHFL_O_ST25RU3993_CAPS_INIT(),0,0}, {905750,STUHFL_O_ST25RU3993_CAPS_INIT(),0,0}, {918250,STUHFL_O_ST25RU3993_CAPS_INIT(),0,0}, {906250,STUHFL_O_ST25RU3993_CAPS_INIT(),0,0}, \
                                                                {918750,STUHFL_O_ST25RU3993_CAPS_INIT(),0,0}, {906750,STUHFL_O_ST25RU3993_CAPS_INIT(),0,0}, {919250,STUHFL_O_ST25RU3993_CAPS_INIT(),0,0}, {907250,STUHFL_O_ST25RU3993_CAPS_INIT(),0,0}, {919750,STUHFL_O_ST25RU3993_CAPS_INIT(),0,0}, \
                                                                {907750,STUHFL_O_ST25RU3993_CAPS_INIT(),0,0}, {920250,STUHFL_O_ST25RU3993_CAPS_INIT(),0,0}, {908250,STUHFL_O_ST25RU3993_CAPS_INIT(),0,0}, {920750,STUHFL_O_ST25RU3993_CAPS_INIT(),0,0}, {908750,STUHFL_O_ST25RU3993_CAPS_INIT(),0,0}, \
                                                                {921250,STUHFL_O_ST25RU3993_CAPS_INIT(),0,0}, {909250,STUHFL_O_ST25RU3993_CAPS_INIT(),0,0}, {921750,STUHFL_O_ST25RU3993_CAPS_INIT(),0,0}, {909750,STUHFL_O_ST25RU3993_CAPS_INIT(),0,0}, {922250,STUHFL_O_ST25RU3993_CAPS_INIT(),0,0}, \
                                                                {910250,STUHFL_O_ST25RU3993_CAPS_INIT(),0,0}, {922750,STUHFL_O_ST25RU3993_CAPS_INIT(),0,0}, {910750,STUHFL_O_ST25RU3993_CAPS_INIT(),0,0}, {923250,STUHFL_O_ST25RU3993_CAPS_INIT(),0,0}, {911250,STUHFL_O_ST25RU3993_CAPS_INIT(),0,0}, \
                                                                {923750,STUHFL_O_ST25RU3993_CAPS_INIT(),0,0}, {911750,STUHFL_O_ST25RU3993_CAPS_INIT(),0,0}, {924250,STUHFL_O_ST25RU3993_CAPS_INIT(),0,0}, {912250,STUHFL_O_ST25RU3993_CAPS_INIT(),0,0}, {924750,STUHFL_O_ST25RU3993_CAPS_INIT(),0,0}, \
                                                                {912750,STUHFL_O_ST25RU3993_CAPS_INIT(),0,0}, {925250,STUHFL_O_ST25RU3993_CAPS_INIT(),0,0}, {913250,STUHFL_O_ST25RU3993_CAPS_INIT(),0,0}, {925750,STUHFL_O_ST25RU3993_CAPS_INIT(),0,0}, {913750,STUHFL_O_ST25RU3993_CAPS_INIT(),0,0}, \
                                                                {926250,STUHFL_O_ST25RU3993_CAPS_INIT(),0,0}, {914250,STUHFL_O_ST25RU3993_CAPS_INIT(),0,0}, {926750,STUHFL_O_ST25RU3993_CAPS_INIT(),0,0}, {914750,STUHFL_O_ST25RU3993_CAPS_INIT(),0,0}, {927250,STUHFL_O_ST25RU3993_CAPS_INIT(),0,0}, \
                                                                STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT()  \
                                                                }}

#define STUHFL_O_ST25RU3993_CHANNEL_LIST_JAPAN_INIT()       {STUHFL_D_ANTENNA_1, false, 9, 0,    \
                                                                {       \
                                                                {920500,STUHFL_O_ST25RU3993_CAPS_INIT(),0,0}, {920700,STUHFL_O_ST25RU3993_CAPS_INIT(),0,0}, {920900,STUHFL_O_ST25RU3993_CAPS_INIT(),0,0}, {921100,STUHFL_O_ST25RU3993_CAPS_INIT(),0,0}, {921300,STUHFL_O_ST25RU3993_CAPS_INIT(),0,0}, \
                                                                {921500,STUHFL_O_ST25RU3993_CAPS_INIT(),0,0}, {921700,STUHFL_O_ST25RU3993_CAPS_INIT(),0,0}, {921900,STUHFL_O_ST25RU3993_CAPS_INIT(),0,0}, {922100,STUHFL_O_ST25RU3993_CAPS_INIT(),0,0}, STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), \
                                                                STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), \
                                                                STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), \
                                                                STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), \
                                                                STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), \
                                                                STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), \
                                                                STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), \
                                                                STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), \
                                                                STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), \
                                                                STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), \
                                                                }}

#define STUHFL_O_ST25RU3993_CHANNEL_LIST_CHINA_INIT()       {STUHFL_D_ANTENNA_1, false, 16, 0,    \
                                                                {       \
                                                                {840625,STUHFL_O_ST25RU3993_CAPS_INIT(),0,0}, {840875,STUHFL_O_ST25RU3993_CAPS_INIT(),0,0}, {841125,STUHFL_O_ST25RU3993_CAPS_INIT(),0,0}, {841375,STUHFL_O_ST25RU3993_CAPS_INIT(),0,0}, {841625,STUHFL_O_ST25RU3993_CAPS_INIT(),0,0}, \
                                                                {841875,STUHFL_O_ST25RU3993_CAPS_INIT(),0,0}, {842125,STUHFL_O_ST25RU3993_CAPS_INIT(),0,0}, {842375,STUHFL_O_ST25RU3993_CAPS_INIT(),0,0}, {842625,STUHFL_O_ST25RU3993_CAPS_INIT(),0,0}, {842875,STUHFL_O_ST25RU3993_CAPS_INIT(),0,0}, \
                                                                {843125,STUHFL_O_ST25RU3993_CAPS_INIT(),0,0}, {843375,STUHFL_O_ST25RU3993_CAPS_INIT(),0,0}, {843625,STUHFL_O_ST25RU3993_CAPS_INIT(),0,0}, {843875,STUHFL_O_ST25RU3993_CAPS_INIT(),0,0}, {844125,STUHFL_O_ST25RU3993_CAPS_INIT(),0,0}, \
                                                                {844375,STUHFL_O_ST25RU3993_CAPS_INIT(),0,0}, STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(),                                                                     \
                                                                STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(),                                                                                      \
                                                                STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(),                                                                                      \
                                                                STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(),                                                                                      \
                                                                STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(),                                                                                      \
                                                                STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(),                                                                                      \
                                                                STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(),                                                                                      \
                                                                STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT()                                                                                                                                                                       \
                                                                }}

#define STUHFL_O_ST25RU3993_CHANNEL_LIST_CHINA2_INIT()      {STUHFL_D_ANTENNA_1, false, 16, 0,    \
                                                                {       \
                                                                {920625,STUHFL_O_ST25RU3993_CAPS_INIT(),0,0}, {920875,STUHFL_O_ST25RU3993_CAPS_INIT(),0,0}, {921125,STUHFL_O_ST25RU3993_CAPS_INIT(),0,0}, {921375,STUHFL_O_ST25RU3993_CAPS_INIT(),0,0}, {921625,STUHFL_O_ST25RU3993_CAPS_INIT(),0,0}, \
                                                                {921875,STUHFL_O_ST25RU3993_CAPS_INIT(),0,0}, {922125,STUHFL_O_ST25RU3993_CAPS_INIT(),0,0}, {922375,STUHFL_O_ST25RU3993_CAPS_INIT(),0,0}, {922625,STUHFL_O_ST25RU3993_CAPS_INIT(),0,0}, {922875,STUHFL_O_ST25RU3993_CAPS_INIT(),0,0}, \
                                                                {923125,STUHFL_O_ST25RU3993_CAPS_INIT(),0,0}, {923375,STUHFL_O_ST25RU3993_CAPS_INIT(),0,0}, {923625,STUHFL_O_ST25RU3993_CAPS_INIT(),0,0}, {923875,STUHFL_O_ST25RU3993_CAPS_INIT(),0,0}, {924125,STUHFL_O_ST25RU3993_CAPS_INIT(),0,0}, \
                                                                {924375,STUHFL_O_ST25RU3993_CAPS_INIT(),0,0}, STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(),                                                                     \
                                                                STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(),                                                                                      \
                                                                STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(),                                                                                      \
                                                                STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(),                                                                                      \
                                                                STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(),                                                                                      \
                                                                STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(),                                                                                      \
                                                                STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(),                                                                                      \
                                                                STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT(), STUHFL_O_ST25RU3993_CHANNEL_ITEM_INIT()                                                                                                                                                                       \
                                                                }}

#define STUHFL_D_FREQUENCY_HOP_MODE_IGNORE_MIN   0   /**< Only the max sending time is considered */
#define STUHFL_D_FREQUENCY_HOP_MODE_POWER_SAFE   1   /**< Power off when minSendingTime is expired and wait until maxSendingTime before frequency is hopped */
#define STUHFL_D_FREQUENCY_HOP_MODE_FAST         2   /**< Perform hopping as soon minSendingTime is expired and continue with next hopping frequency*/
#define STUHFL_D_FREQUENCY_HOP_MODE_FAIR         3   /**< Perform hopping as described in "FAST" mode, but take care that all frequencies get time same time in total */
typedef struct {
    uint16_t                            maxSendingTime;         /**< I/O Param: Maximum sending time before frequency hopping is performed. Minimum allowed value: 40ms */
    uint16_t                            minSendingTime;         /**< I/O Param: Minimum sending time before frequency hopping is performed */
    uint8_t                             mode;                   /**< I/O Param: Hopping mode */
    uint8_t                             rfu;                    /**< rfu */
} STUHFL_T_ST25RU3993_FreqHop;
#define STUHFL_O_ST25RU3993_FREQ_HOP_INIT()      {400, 400, STUHFL_D_FREQUENCY_HOP_MODE_IGNORE_MIN, 0}

typedef struct {
    uint16_t                            listeningTime;      /**< I/O Param: Time for listing periode */
    uint16_t                            idleTime;           /**< I/O Param: Idle time for LBT */
    uint8_t                             rssiLogThreshold;   /**< I/O Param: RSSI threshold value */
    bool                                skipLBTcheck;       /**< I/O Param: Flag to wheter LBT check shall be skipped at all */
} STUHFL_T_ST25RU3993_FreqLBT;
#define STUHFL_O_ST25RU3993_FREQ_LBT_INIT()      {1, 0, 31, true}

/* Set */
#define STUHFL_D_CONTINUOUS_MODULATION_MODE_STATIC          0
#define STUHFL_D_CONTINUOUS_MODULATION_MODE_PSEUDO_RANDOM   1
#define STUHFL_D_CONTINUOUS_MODULATION_MODE_ETSI            2
#define STUHFL_D_CONTINUOUS_MODULATION_MODE_OFF             3
typedef struct {
    uint32_t                            frequency;      /**< I Param: Frequency to be used for continuous modulation */
    bool                                enable;         /**< I Param: Flag to enable or disable modulation */
    uint16_t                            maxSendingTime; /**< I Param: Maximum modulation time in ms. If zero the modulation will not stopped automatically. To stop a infite continuous modulation the command must be resend with enable flag set to false. */
    uint8_t                             mode;           /**< I Param: Modulation mode */
} STUHFL_T_ST25RU3993_FreqContinuousModulation;
#define STUHFL_O_ST25RU3993_FREQ_CONTINUOUS_MODULATION_INIT()        {STUHFL_D_DEFAULT_FREQUENCY, false, 0, STUHFL_D_CONTINUOUS_MODULATION_MODE_OFF}

/* TrExt defines */
#define STUHFL_D_TREXT_OFF      false   /**< do not send lead code */
#define STUHFL_D_TREXT_ON       true    /**< send lead code  */
/* Gen2 Tari */
#define STUHFL_D_GEN2_TARI_6_25          0 /**< set tari to  6.25 us */
#define STUHFL_D_GEN2_TARI_12_50         1 /**< set tari to 12.5  us */
#define STUHFL_D_GEN2_TARI_25_00         2 /**< set tari to 25    us */
/* Gen2 Backlink frequencies */
#define STUHFL_D_GEN2_BLF_40             0   /** <link frequency  40 kHz */
#define STUHFL_D_GEN2_BLF_160            6   /** <link frequency 160 kHz */
#define STUHFL_D_GEN2_BLF_213            8   /** <link frequency 213 kHz */
#define STUHFL_D_GEN2_BLF_256            9   /** <link frequency 256 kHz */
#define STUHFL_D_GEN2_BLF_320            12  /** <link frequency 320 kHz */
#define STUHFL_D_GEN2_BLF_640            15  /** <link frequency 640 kHz */
#define STUHFL_D_NB_GEN2_BLF             6

/* Gen2 Rx coding */
#define STUHFL_D_GEN2_CODING_FM0            0 /** <FM0 coding for rx      */
#define STUHFL_D_GEN2_CODING_MILLER2        1 /** <MILLER2 coding for rx */
#define STUHFL_D_GEN2_CODING_MILLER4        2 /** <MILLER4 coding for rx */
#define STUHFL_D_GEN2_CODING_MILLER8        3 /** <MILLER8 coding for rx */
#define STUHFL_D_NB_GEN2_CODING             4

typedef struct {
    uint8_t tari;       /**< I/O Param: Tari setting */
    uint8_t blf;        /**< I/O Param: backscatter link frequency factor: STUHFL_D_GEN2_BLF_40, ... */
    uint8_t coding;     /**< I/O Param: Coding: STUHFL_D_GEN2_CODING_FM0, ... */
    bool    trext;      /**< I/O Param: Usage of short or long preamble: true if the preamble is long, i.e. with pilot tone */
} STUHFL_T_ST25RU3993_Gen2_ProtocolCfg;
#define STUHFL_O_ST25RU3993_GEN2_PROTOCOL_CFG_INIT()         {STUHFL_D_GEN2_TARI_25_00, STUHFL_D_GEN2_BLF_256, STUHFL_D_GEN2_CODING_MILLER8, STUHFL_D_TREXT_ON}

#define STUHFL_D_GB29768_BLF_64      0   /**< link frequency 64 kHz */
#define STUHFL_D_GB29768_BLF_137     1   /**< link frequency 137 kHz */
#define STUHFL_D_GB29768_BLF_174     2   /**< link frequency 174 kHz */
#define STUHFL_D_GB29768_BLF_320     3   /**< link frequency 320 kHz */
#define STUHFL_D_GB29768_BLF_128     4   /**< link frequency 128 kHz */
#define STUHFL_D_GB29768_BLF_274     5   /**< link frequency 274 kHz */
#define STUHFL_D_GB29768_BLF_349     6   /**< link frequency 349 kHz */
#define STUHFL_D_GB29768_BLF_640     7   /**< link frequency 640 kHz */
#define STUHFL_D_NB_GB29768_BLF      8

/* Rx coding values */
#define STUHFL_D_GB29768_CODING_FM0     0   /**< FM coding for rx      */
#define STUHFL_D_GB29768_CODING_MILLER2 1   /**< MILLER2 coding for rx */
#define STUHFL_D_GB29768_CODING_MILLER4 2   /**< MILLER4 coding for rx */
#define STUHFL_D_GB29768_CODING_MILLER8 3   /**< MILLER8 coding for rx */
#define STUHFL_D_NB_GB29768_CODING      4

/* Tc (TPP coding interval) */
#define STUHFL_D_GB29768_TC_6_25     0
#define STUHFL_D_GB29768_TC_12_5     1

typedef struct {
    bool    trext;       /**< I/O Param: Usage of short or long preamble: true if the lead code is sent, false otherwise */
    uint8_t blf;         /**< I/O Param: backscatter link frequency factor */
    uint8_t coding;      /**< I/O Param: Coding: STUHFL_D_GB29768_CODING_FM0, STUHFL_D_GB29768_CODING_MILLER2, ... */
    uint8_t tc;          /**< I/O Param: Refernce time of forward link: STUHFL_D_GB29768_TC_12_5, STUHFL_D_GB29768_TC_6_25 */
} STUHFL_T_ST25RU3993_Gb29768_ProtocolCfg;
#define STUHFL_O_ST25RU3993_GB29768_PROTOCOL_CFG_INIT()      {STUHFL_D_TREXT_ON, STUHFL_D_GB29768_BLF_320, STUHFL_D_GB29768_CODING_MILLER2, STUHFL_D_GB29768_TC_12_5}

#define STUHFL_D_ANTENNA_1      0
#define STUHFL_D_ANTENNA_2      1
#define STUHFL_D_ANTENNA_3      2
#define STUHFL_D_ANTENNA_4      3
#define STUHFL_D_ANTENNA_ALT    0xFF
typedef struct {
    int8_t      txOutputLevel;                  /**< I/O Param: Tx output level. See Modulator control register 3 for further info. Range [0db..-19db] .. -0,-1,-2,-3,-4,-5,-6,-7,-8,-9,-10,-11,-12,-13,-14,-15,-16,-17,-18,-19 */
    int8_t      rxSensitivity;                  /**< I/O Param: Rx sensitivity level. Range [-17dB..+19dB] .. -17,-14,-11,-9,-8,-6,-5,-3,-2,0,1,3,4,6,7,9,10,13,16,19 */
    uint8_t     usedAntenna;                    /**< I/O Param: Antenna to be used */
    uint16_t    alternateAntennaInterval;       /**< I/O Param: Time in ms for alternating the antennas when alternating mode is used */
    uint8_t     rfu;                            /**< rfu */
} STUHFL_T_ST25RU3993_TxRxCfg;
#define STUHFL_O_ST25RU3993_TXRX_CFG_INIT()      {-2, 3, STUHFL_D_ANTENNA_1, 1, 3}

typedef struct {
    bool external;                           /**< I/O Param: Force usage of external power amplifier. If 'false' internal PA is used */
} STUHFL_T_ST25RU3993_PowerAmplifierCfg;
#define STUHFL_O_ST25RU3993_POWER_AMPLIFIER_CFG_INIT()       {true}

/* Gen2 Session */
#define STUHFL_D_GEN2_SESSION_S0         0x00
#define STUHFL_D_GEN2_SESSION_S1         0x01
#define STUHFL_D_GEN2_SESSION_S2         0x02
#define STUHFL_D_GEN2_SESSION_S3         0x03

/* Gen2 Target */
#define STUHFL_D_GEN2_TARGET_A           0
#define STUHFL_D_GEN2_TARGET_B           1

#define STUHFL_D_NB_C_VALUES            16U

/** Definition of the maximum number of the gen2 Q Value, standard allows up to 15 */
#define STUHFL_D_GEN2_MAXQ                15U

/* Automatic tuning */
typedef struct {
    uint16_t    interval;                   /**< I/O Param: Auto tuning check interval (in inventory rounds)*/
    uint8_t     level;                      /**< I/O Param: Deviation of (I^2+Q^2) to trigger retuning */
    uint8_t     algorithm;                  /**< I/O Param: Algorithm used for automatic (re)tuning.  */
    bool        falsePositiveDetection;     /**< I/O Param: Do false Positive Detection check */
} STUHFL_T_ST25RU3993_AutoTuning;
#define STUHFL_O_ST25RU3993_AUTO_TUNING_INIT()       {7, 20, STUHFL_D_TUNING_ALGO_FAST, false}

/* Adaptive sensitivity */
typedef struct {
    uint16_t    interval;   /**< I/O Param: Adaptive sensitivity interval (in inventory rounds)*/
    bool        enable;      /**< I/O Param: Flag to enable automatic sensitivity adjustment */
} STUHFL_T_ST25RU3993_AdaptiveSensitivity;
#define STUHFL_O_ST25RU3993_ADAPTIVE_SENSITIVITY_INIT()      {5, false}

/* Gen2 inventory info */
typedef struct {
    bool        fast;                           /**< I/O Param: Fast Inventory enabling. If set to false normal inventory round will be performed, if set to true fast inventory rounds will be performed.*/
    bool        autoAck;                        /**< I/O Param: Automatic Ack enabling. If set to false inventory round commands will be triggered by the FW, otherwise the autoACK feature of the reader will be used which sends the required Gen2 commands automatically.*/
    bool        readTID;                        /**< I/O Param: read TID enabling.  If set to true an read of the TID will be performed in inventory rounds.*/
} STUHFL_T_ST25RU3993_Gen2_InventoryOption;
#define STUHFL_O_ST25RU3993_GEN2_INVENTORY_OPTION_INIT()       {true, false, false}

/* Gen2 Anticollision */
#define STUHFL_D_USE_QUERY_ADJUST_NIC       0x10
#define STUHFL_D_SINGLE_ADJUST              0x20
#define STUHFL_D_USE_CEIL_FLOOR             0x40
#define STUHFL_D_RESET_Q_AFTER_ROUND        0x80

typedef struct {
    bool        adaptiveQ;                      /**< I/O Param: Flag to enable automatic Q adaptation */
    uint8_t     startQ;                         /**< I/O Param: Q starting value */
    uint8_t     minQ;                           /**< I/O Param: Minimum value that Q could reach */
    uint8_t     maxQ;                           /**< I/O Param: Maximum value that Q could reach. If value exceeds 15 it is truncated to 15. */
    uint8_t     options;                        /**< I/O Param: Q algorithm options. Bitfield to define additional anticollision options (STUHFL_D_USE_QUERY_ADJUST_NIC, STUHFL_D_SINGLE_ADJUST, STUHFL_D_USE_CEIL_FLOOR, STUHFL_D_RESET_Q_AFTER_ROUND) */
    uint8_t     C1[STUHFL_D_NB_C_VALUES];               /**< I/O Param: Q algorithm C1 values for each Q */
    uint8_t     C2[STUHFL_D_NB_C_VALUES];               /**< I/O Param: Q algorithm C2 values for each Q */
} STUHFL_T_ST25RU3993_Gen2_Anticollision;
#define STUHFL_O_ST25RU3993_GEN2_ANTICOLLISION_INIT()        {true, 4, 0, STUHFL_D_GEN2_MAXQ, 0, \
                                                               {15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15}, \
                                                               {35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35}, \
                                                              }
/* Query params */
typedef struct {
    uint8_t     sel;                            /**< I/O Param: QUERY command Sel field */
    uint8_t     session;                        /**< I/O Param: Query session information: STUHFL_D_GEN2_SESSION_S0, ... */
    uint8_t     target;                         /**< I/O Param: QUERY target field */
    bool        toggleTarget;                   /**< I/O Param: Toggle between Target A and B */
    bool        targetDepletionMode;            /**< I/O Param: If set to true and the target shall be toggled in inventory an additional inventory round before the target is toggled will be executed. This gives "weak" transponders an additional chance to reply. */
} STUHFL_T_ST25RU3993_Gen2_QueryParams;
#define STUHFL_O_ST25RU3993_GEN2_QUERY_PARAMS_INIT()         {0, STUHFL_D_GEN2_SESSION_S0, STUHFL_D_GEN2_TARGET_A, false, false}

typedef struct {
    STUHFL_T_ST25RU3993_Gen2_InventoryOption    inventoryOption;
    STUHFL_T_ST25RU3993_Gen2_Anticollision      antiCollision;
    STUHFL_T_ST25RU3993_AutoTuning              autoTuning;
    STUHFL_T_ST25RU3993_Gen2_QueryParams        queryParams;
    STUHFL_T_ST25RU3993_AdaptiveSensitivity     adaptiveSensitivity;
} STUHFL_T_ST25RU3993_Gen2_InventoryCfg;
#define STUHFL_O_ST25RU3993_GEN2_INVENTORY_CFG_INIT()        { STUHFL_O_ST25RU3993_GEN2_INVENTORY_OPTION_INIT(),\
                                                                 STUHFL_O_ST25RU3993_GEN2_ANTICOLLISION_INIT(),\
                                                                 STUHFL_O_ST25RU3993_AUTO_TUNING_INIT(),\
                                                                 STUHFL_O_ST25RU3993_GEN2_QUERY_PARAMS_INIT(),\
                                                                 STUHFL_O_ST25RU3993_ADAPTIVE_SENSITIVITY_INIT()\
                                                              }

/* condition field */
#define STUHFL_D_GB29768_CONDITION_ALL   0x00    /**< all tags participate */
#define STUHFL_D_GB29768_CONDITION_FLAG1 0x01    /**< all tags with matching flag 1 */
#define STUHFL_D_GB29768_CONDITION_FLAG0 0x02    /**< all tags with matching flag 0 */

/* Session field */
#define STUHFL_D_GB29768_SESSION_S0  0x00
#define STUHFL_D_GB29768_SESSION_S1  0x01
#define STUHFL_D_GB29768_SESSION_S2  0x02
#define STUHFL_D_GB29768_SESSION_S3  0x03

/* Target */
#define STUHFL_D_GB29768_TARGET_0    0
#define STUHFL_D_GB29768_TARGET_1    1

/* Query params */
typedef struct {
    uint8_t     condition;                      /**< I/O Param: QUERY command condition field */
    uint8_t     session;                        /**< I/O Param: Query session information: STUHFL_D_GB29768_SESSION_S0, ... */
    uint8_t     target;                         /**< I/O Param: QUERY target field */
    bool        toggleTarget;                   /**< I/O Param: Toggle between Target 0 and 1 */
    bool        targetDepletionMode;            /**< I/O Param: If set to true and the target shall be toggled in inventory an additional inventory round before the target is toggled will be executed. This gives "weak" transponders an additional chance to reply. */
} STUHFL_T_ST25RU3993_Gb29768_QueryParams;
#define STUHFL_O_ST25RU3993_GB29768_QUERY_PARAMS_INIT()      {STUHFL_D_GB29768_CONDITION_ALL, STUHFL_D_GB29768_SESSION_S0, STUHFL_D_GB29768_TARGET_0, true, false}

/* Gen2 anticollision */
typedef struct {
    uint16_t    endThreshold;                   /**< I/O Param: GBT anticollision end threshold parameter.*/
    uint16_t    ccnThreshold;                   /**< I/O Param: GBT anticollision CCN threshold parameter.*/
    uint16_t    cinThreshold;                   /**< I/O Param: GBT anticollision CIN threshold parameter.*/
} STUHFL_T_ST25RU3993_Gb29768_Anticollision;
#define STUHFL_O_ST25RU3993_GB29768_ANTICOLLISION_INIT()         {2, 3, 4}

/* Gen2 inventory info */
typedef struct {
    bool        readTID;                        /**< I/O Param: read TID enabling.  If set to true, a read of the TID will be performed in inventory rounds.*/
} STUHFL_T_ST25RU3993_Gb29768_InventoryOption;
#define STUHFL_O_ST25RU3993_GB29768_INVENTORY_OPTION_INIT()        {false}

typedef struct {
    STUHFL_T_ST25RU3993_AutoTuning                  autoTuning;
    STUHFL_T_ST25RU3993_AdaptiveSensitivity         adaptiveSensitivity;
    STUHFL_T_ST25RU3993_Gb29768_QueryParams         queryParams;
    STUHFL_T_ST25RU3993_Gb29768_Anticollision       antiCollision;
    STUHFL_T_ST25RU3993_Gb29768_InventoryOption     inventoryOption;
} STUHFL_T_ST25RU3993_Gb29768_InventoryCfg;
#define STUHFL_O_ST25RU3993_GB29768_INVENTORY_CFG_INIT()     { STUHFL_O_ST25RU3993_AUTO_TUNING_INIT(),\
                                                               STUHFL_O_ST25RU3993_ADAPTIVE_SENSITIVITY_INIT(),\
                                                               STUHFL_O_ST25RU3993_GB29768_QUERY_PARAMS_INIT(),\
                                                               STUHFL_O_ST25RU3993_GB29768_ANTICOLLISION_INIT(),\
                                                               STUHFL_O_ST25RU3993_GB29768_INVENTORY_OPTION_INIT()\
                                                              }


// --------------------------------------------------------------------------
/*  */
typedef struct/* STUHFL_DEPRECATED */STUHFL_S_ST25RU3993_TuningTableEntry {
    uint8_t     entry;                                  /**< I Param: table entry, when set to 0xFF the entry will be appended to the end of the table */
    uint32_t    freq;                                   /**< I/O Param: Frequency for when this entry shall be applied */
    uint8_t     applyCapValues[STUHFL_D_MAX_ANTENNA];   /**< I Param: flag to specify if cap values should be applied for antenna */
    uint8_t     cin[STUHFL_D_MAX_ANTENNA];       /**< I/O Param: IN capacitance of tuning PI network */
    uint8_t     clen[STUHFL_D_MAX_ANTENNA];      /**< I/O Param: LEN capacitance of tuning PI network */
    uint8_t     cout[STUHFL_D_MAX_ANTENNA];      /**< I/O Param: OUT capacitance of tuning PI network */
    uint16_t    IQ[STUHFL_D_MAX_ANTENNA];        /**< I/O Param: IQ value for this entry */
} STUHFL_T_ST25RU3993_TuningTableEntry;
#define STUHFL_O_ST25RU3993_TUNING_TABLE_ENTRY_INIT()        {0, STUHFL_D_DEFAULT_FREQUENCY, {false, false, false, false}, {0,0,0,0}, {0,0,0,0}, {0,0,0,0}, {0xFFFF,0xFFFF,0xFFFF,0xFFFF}}

/*  */
typedef struct/* STUHFL_DEPRECATED */STUHFL_S_ST25RU3993_TunerTableSet {
    uint8_t     profile;    /**< I Param: Profile identifier */
    uint32_t    freq;       /**< I Param: Frequency */
} STUHFL_T_ST25RU3993_TunerTableSet;
#define STUHFL_O_ST25RU3993_TUNER_TABLE_SET_INIT()       {STUHFL_D_PROFILE_EUROPE, STUHFL_D_RESET_DEFAULT_ALL_FREQS}

/* Get/Set */
typedef struct/* STUHFL_DEPRECATED */STUHFL_S_ST25RU3993_Tuning {
    uint8_t antenna;    /**< I Param: Antenna on which tuning settings apply */
    uint8_t cin;        /**< I/O Param: Measured IN capacitance of tuning PI network */
    uint8_t clen;       /**< I/O Param: Measured LEN capacitance of tuning PI network */
    uint8_t cout;       /**< I/O Param: Measured OUT capacitance of tuning PI network */
} STUHFL_T_ST25RU3993_Tuning;
#define STUHFL_O_ST25RU3993_TUNING_INIT()        {STUHFL_D_ANTENNA_1, 0, 0, 0}

/*  */
typedef struct/* STUHFL_DEPRECATED */STUHFL_S_ST25RU3993_TuningTableInfo {
    uint8_t profile;                    /**< I Param: profile ID where number of entries should be replied */
    uint8_t numEntries;                 /**< O Param: number of entries for requested profile */
} STUHFL_T_ST25RU3993_TuningTableInfo;
#define STUHFL_O_ST25RU3993_TUNING_TABLE_INFO_INIT()         {STUHFL_D_PROFILE_EUROPE, 4}

/* Get/Set */
typedef struct {
    uint8_t                     antenna;        /**< I Param: Antenna on which tuning settings apply */
    uint8_t                     channelListIdx; /**< I Param: Related channel list entry */
    STUHFL_T_ST25RU3993_Caps    caps;           /**< I/O Param: Tuning caps at antenna */
} STUHFL_T_ST25RU3993_TuningCaps;
#define STUHFL_O_ST25RU3993_TUNING_CAPS_INIT()       {STUHFL_D_ANTENNA_1, 0, STUHFL_O_ST25RU3993_CAPS_INIT()}

/* Get */
typedef struct {
	double					AMPL_temp; /* Power Amplifier temperature */
	double 					CPU_temp;  /* CPU temperature */
	double 					RFID_temp; /* RFID temperature */
}STUHFL_T_ST25RU3993_Temperature;

/* Get */
typedef struct {
    float RF_PwrDetected; /* Power Amplifier temperature */
}STUHFL_T_ST25RU3993_RF_PwrDetected_V;

/* Get */
typedef struct {
    float RF_PwrDetected_V; /* Power Amplifier */
    float RF_PwrDetected_dBm; /* Power Amplifier in dBm*/
}STUHFL_T_ST25RU3993_RF_PwrDetected;

/* Get/Set */
typedef struct {
	float Attenuator_Voltage; /* Power Amplifier temperature */
}STUHFL_T_ST25RU3993_Attenuator;

/* Get/Set */
typedef struct {
	uint8_t antenna1; /* Enable STUHFL_D_ANTENNA_POWER_MODE_ON/Disable STUHFL_D_ANTENNA_POWER_MODE_OFF*/
	uint8_t antenna2; /* Enable STUHFL_D_ANTENNA_POWER_MODE_ON/Disable STUHFL_D_ANTENNA_POWER_MODE_OFF*/
	uint8_t antenna3; /* Enable STUHFL_D_ANTENNA_POWER_MODE_ON/Disable STUHFL_D_ANTENNA_POWER_MODE_OFF*/
	uint8_t antenna4; /* Enable STUHFL_D_ANTENNA_POWER_MODE_ON/Disable STUHFL_D_ANTENNA_POWER_MODE_OFF*/
}STUHFL_T_ST25RU3993_AntennaSequence; /* Antenna sequence for the alternate mode */
#define STUHFL_O_ST25RU3993_ANTENNA_SEQUENCE_INIT()         {STUHFL_D_ANTENNA_POWER_MODE_ON,STUHFL_D_ANTENNA_POWER_MODE_OFF,STUHFL_D_ANTENNA_POWER_MODE_OFF,STUHFL_D_ANTENNA_POWER_MODE_OFF}


/* Get/Set */
typedef struct {
    float pwrDetectedV[STUHFL_D_INTERPOLATION_VALUES]; /* Power Amplifier */
    float pwrDetectedVdBm[STUHFL_D_INTERPOLATION_VALUES]; /* Power Amplifier in dBm*/
}STUHFL_T_ST25RU3993_RF_PwrDetectedCalibration;

/* Set */
typedef struct
{
    uint8_t enable; /* Enable the rf detector calibrator */
    int8_t txOutputLevel; /* The output level of the reader */
}STUHFL_T_ST25RU3993_RF_DetectorCalibrationEnable;

/* Get */
typedef struct
{
    uint8_t state; /* Enable the rf detector calibrator */
}STUHFL_T_ST25RU3993_RF_AttenuationPowerCalibrationState;

/* Get/Set */
typedef struct {
    float attenuation[STUHFL_D_ATT_PWR_TABLE_SIZE]; /* Power Amplifier */
    float pwr_max[STUHFL_D_ATT_PWR_TABLE_SIZE]; /* Power Amplifier in dBm*/
    float pwr_min[STUHFL_D_ATT_PWR_TABLE_SIZE]; /* Power Amplifier in dBm*/
}STUHFL_T_ST25RU3993_RF_AttenuationPowerDetectedTables;

/**< Tune algorithm definitions */
#define STUHFL_D_TUNING_ALGO_NONE        0
#define STUHFL_D_TUNING_ALGO_FAST        1   /**< Simple automatic tuning function.This function tries to find an optimized tuner setting(minimal reflected power). The function starts at the current tuner setting and modifies the tuner caps until a setting with a minimum of reflected power is found.When changing the tuner further leads to an increase of reflected power the algorithm stops. Note that, although the algorithm has been optimized to not immediately stop at local minima of reflected power, it still might not find the tuner setting with the lowest reflected power.The algorithm of tunerMultiHillClimb() is probably producing better results, but it is slower. */
#define STUHFL_D_TUNING_ALGO_SLOW        2   /**< Sophisticated automatic tuning function.This function tries to find an optimized tuner setting(minimal reflected power). The function splits the 3 - dimensional tuner - setting - space(axis are Cin, Clen and Cout) into segments and searches in each segment(by using tunerOneHillClimb()) for its local minimum of reflected power. The tuner setting(point in tuner - setting - space) which has the lowest reflected power is returned in parameter res. This function has a much higher probability to find the tuner setting with the lowest reflected power than tunerOneHillClimb() but on the other hand takes much longer. */
#define STUHFL_D_TUNING_ALGO_MEDIUM      3   /**< Enhanced Sophisticated automatic tuning function.This function tries to find an optimized tuner setting(minimal reflected power). The function splits the 3 - dimensional tuner - setting - space(axis are Cin, Clen and Cout) into segments and get reflected power for each of them.A tunerOneHillClimb() is then run on the 3 segments with minimum of reflected power. The tuner setting(point in tuner - setting - space) which has the lowest reflected power is then returned in parameter res. This function has a much higher probability to find the tuner setting with the lowest reflected power than tunerOneHillClimb() and is faster than tunerMultiHillClimb(). */

#define STUHFL_D_TUNING_ALGO_ENABLE_FPD  0x80    /**<STUHFL_DEPRECATED: Enable False Positive Detection during tuning algorithm.*/

/* */
typedef struct/* STUHFL_DEPRECATED */STUHFL_S_ST25RU3993_Tune {
    uint8_t algo;                   /**< I Param: Used algorithm for tuning. */
} STUHFL_T_ST25RU3993_Tune;
#define STUHFL_O_ST25RU3993_TUNE_INIT()      {STUHFL_D_TUNING_ALGO_MEDIUM}

typedef struct {
    bool                            falsePositiveDetection;     /**< I Param: Do false Positive Detection check */
    bool                            persistent;                 /**< I Param: Save tuning results to flash */
    uint8_t                         channelListIdx;             /**< I Param: Index of channel list frequency aimed to be tuned (Nota: unused if tuneAll enabled) */
    uint8_t                         antenna;                    /**< I Param: Antenna for which the channel list shall be used */
    uint8_t                         algorithm;                  /**< I Param: Used algorithm for tuning. */
    bool                            tuneAll;                    /**< I Param: Tune all freqs at once. */
} STUHFL_T_ST25RU3993_TuneCfg;
#define STUHFL_O_ST25RU3993_TUNE_CFG_INIT()      {true, false, 0, STUHFL_D_ANTENNA_1, STUHFL_D_TUNING_ALGO_MEDIUM, false}

#pragma pack(pop)

#ifdef __cplusplus
}
#endif //__cplusplus

#endif // __STUHFL_DL_ST25RU3993_EVAL_H
