/**
  ******************************************************************************
  * @file           main.h
  * @brief          Main program header file
  ******************************************************************************
  *
  * <h2><center>&copy; COPYRIGHT(c) 2020 STMicroelectronics</center></h2>
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

#if !defined __MAIN_H
#define __MAIN_H

//
#ifdef __cplusplus
extern "C"
{
#endif //__cplusplus


    int getSocketState();

    // --------------------------------------------------------------------------
    // screen logging
    void log2Screen(bool clearScreen, bool flush, const char* format, ...);
    void logInventory(STUHFL_T_ActionCycleData data);

    // Utilities
    void setupGen2Config(bool singleTag, bool freqHopping, int antenna);

    // Showcase: EVAL API module

    // Showcase: Inventories runner
    void InventoryRunner(uint32_t rounds, bool singleTag);

    // Showcase basic functionality
    // 
    // Showcase: logging

    // Playground 


#ifdef __cplusplus
}
#endif //__cplusplus

#endif //__MAIN_H
#pragma once