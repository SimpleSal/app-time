/* -- SimpleSal: ssTEA, ssUI, and ssIO | (C) 2025, 2026 TruSoft Computing LLC |  All rights reserved. --
   This software is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
   This software is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
   ---------------------------------------------------------------------------------------------------
 *
 * app-time.ino               Arduino main program demonstrating Timer or Clock based on ssTEA.
 *
 ---------------------------------------------------------------------------------------------------- */
// =================================================================================================

// -------------------------------------------------------------------------------------------------
// SimpleSal has a software philosphy: everything that happens in life does NOT involve magic. All
// of the hallenges to portability have technical solutions in the build environment and software.
// -------------------------------------------------------------------------------------------------
// Software portability across build environments (compilers, memory maps, allocations) may be
// managed at the very highest level by separating Arduino, Linux, Windows, RTOS, barebones, etc.
// -------------------------------------------------------------------------------------------------
#define     HOST_ONEOF_hostOS_Is_Arduino

// -------------------------------------------------------------------------------------------------
// Each platform has a variety of memory types, control over what goes where is often in the C code.
// For example: removing "static" from the ReadOnly #define might move strings from Flash to RAM.
// (note: The strings arrive in Flash with the binary image; a copy is accessed by code in RAM.)
// -------------------------------------------------------------------------------------------------
#define     ReadOnly        static

// -------------------------------------------------------------------------------------------------
// Software portability across Time from the same human brain requires some words remain constant.
// A HOST build environment that defines boolean and Null can be quite cranky about a re-define.
// -------------------------------------------------------------------------------------------------
#define     HOST_ONEOF_ssHL_defines_boolean
#define     HOST_ONEOF_ssHL_defines_Null

// -------------------------------------------------------------------------------------------------
// The definition of the simplest configuration depends on the file the build tool finds and uses.
// -------------------------------------------------------------------------------------------------
// This SimpleSal App is meant to build with "ss_configuration.start" with extension changed to ".h".
// -------------------------------------------------------------------------------------------------
#define     SS_OPTIN_INCLUDE_SSTEA
#define     SS_ACCEPT_SIMPLEST_CONFIG

#include "ss_configuration.h"

// -------------------------------------------------------------------------------------------------
// Software portability across platforms requires operational levers built in that hide differences.
// The levers are defined in "mesa_min_dcl" and "mesa_min_def"; ssTEA uses micros() and Ascii.
// -------------------------------------------------------------------------------------------------
// This SimpleSal App is meant to build with "mesa_min_dcl.start" with extension changed to ".h".
// -------------------------------------------------------------------------------------------------
#include "mesa_min_dcl.h"

// -------------------------------------------------------------------------------------------------
// Using ssTEA data types, App data types for Events may be declared HERE.  ssTEA Event maintains
// data About the Event; ssTea refers to the App's data type when the Event is granted Agency.
// -------------------------------------------------------------------------------------------------
#include "SimpleSal\ssTEA\ssTEA_data_dcl.h"

typedef struct App_EventDataDesc_s
{
    int                 valueA;
    int                 valueB;
}   App_EventDataDesc_t,  *App_pEventDataDesc_t;

typedef App_EventDataDesc_t      App_EventData_t;       // referenced by ssTEA data type directly
typedef App_pEventDataDesc_t     App_pEventData_t;
#define App_pEventDataNull       ((App_pEventData_t) NULL)

// -------------------------------------------------------------------------------------------------
// Declarations of data types integrating App and ssTEA types, and functions with their parameters.
// -------------------------------------------------------------------------------------------------
#include "SimpleSal\ss_include_dcl.h"

// -------------------------------------------------------------------------------------------------
// The UI shared between the App and ssUI is simplified here by ssUI sending "app ..." input here.
// -------------------------------------------------------------------------------------------------
void        App_HeyProcessThis (pAsciiA_t  pReceivedInput);
pAsciiA_t   pBuildBanner = S("<mesa [P39] and App [time] init...>");

// -------------------------------------------------------------------------------------------------
// This SimpleSal App is meant to build with "mesa_min_def.start" with extension changed to ".h".
// -------------------------------------------------------------------------------------------------
#include "mesa_min_def.h"

// -------------------------------------------------------------------------------------------------
// Because the App co-exists with ssTEA and ssUI, some form of semaphore FSM is used to permit use.
// Verbosity initializes the ssUI FSM generating extensive run-time Ascii text info to "Say it!".
// -------------------------------------------------------------------------------------------------
#define  ssUI_Default_LED_RO_state          mesa_RO_state_App
#define  ssUI_Default_LED_RO_substate       mesa_RO_substate_none
#define  ssUI_Default_Ascii_RO_state        mesa_RO_state_App
#define  ssUI_Default_Ascii_RO_substate     mesa_RO_substate_none
#define  ssUI_Default_Matrix_RO_state       mesa_RO_state_App
#define  ssUI_Default_Matrix_RO_substate    mesa_RO_substate_none

#define  ssUI_Default_Verbosity             true

// -------------------------------------------------------------------------------------------------
// Allocations of data and definition of functions with parameters, as declared by ss_include_dcl.h
// -------------------------------------------------------------------------------------------------
#include "SimpleSal\ss_include_def.h"

// -------------------------------------------------------------------------------------------------
// The interfaces to the mesa, ssTEA and ssUI are now fully referenceable by App software.
// -------------------------------------------------------------------------------------------------

// =================================================================================================
// -------------------------------------------------------------------------------------------------
// This SimpleSal App either builds into a display, as Time occurs, of a counting-up Clock; or,
// of a counting-up Timer.  The output must correlate to the display device: An Arduino IDE Serial
// display user will see the time displayed in a long line off the screen; clearing the buffer
// rapidly will show Time occurring.  Other terminal programs are more configurable.  A display of
// the Time on a new line each time in this App shows how often the App loop function is running.
// Higher baud rates increase the ability to display and so the App loop gets to run more often.
// The value of displaying a Clock versus a Timer is based on the human's comparison to true Time.
// -------------------------------------------------------------------------------------------------
// #define APP_ONEOF_CLOCK_OR_TIMER_IS_TIMER
#define APP_ONEOF_CLOCK_OR_TIMER_IS_CLOCK

// =================================================================================================
// -------------------------------------------------------------------------------------------------
// This is the compiler trick used to allow the adopter of SimpleSal to keep their functions as they
// exist, with the names they have in the original Arduino App.  The alternative is to rename the
// original functions from "setup" to "App_setup" (and loop -> App_loop) with an editor in the file;
// the second step in that alternative is to instantiate ssTEAsetup/ssTEAloop here as setup/loop.
// -------------------------------------------------------------------------------------------------
#define setup   App_setup

void setup (void)       // the App's original setup function, ssTEA calls as App_setup.
{
    // this content was in the App's original setup function, copied here before adding SimpleSal
    /* original App */

    // this content added to the App's original setup function, co-existence has a price.
    mesa_Ascii_RO_state     = mesa_RO_state_App;
    mesa_Ascii_RO_substate  = mesa_RO_substate_none;

    mesa_uiOp_deviceInitialize ();

    mesa_uiOp_emit_newline ();
    mesa_uiOp_emit_newline ();
    mesa_uiOp_emit_newline ();
    mesa_uiOp_emit_qAsciiA ("original App setup complete...");
    mesa_uiOp_emit_newline ();

    mesa_gCtOf_1usThis1ms  = 0;
    mesa_gCtOf_1msThis100ms = 0;
    mesa_gCtOf_1msThisCycle = 0;
    mesa_gCtOf_1msFreeRunning = 0;

}   // setup            // the App's original setup function

#undef setup            // don't forget to forget #define

// the ssHL compiler has seen and compiled "App_setup", and has not yet seen anything called "setup".

// =================================================================================================
// #define TERMINAL_PROGRAM_CANT_HANDLE_JUST_CR

#define loop    App_loop
int count_them = 0;

void loop (void)        // (the App's original loop function, ssTEA calls as App_loop)
{
    // ---------------------------------------------------------------------------------------------
    // The mesa counters reference ssT counters established by ssTEA_loop before calling App_loop.
    // ---------------------------------------------------------------------------------------------
    mesa_gCtOf_1usThis1ms += ssT_us_gLoop1toLoop2;          // calculated in Loop2 by ssTEA_loop

    if (mesa_gCtOf_1usThis1ms <= SST_USECS_PER_MSEC)
    {
        return;
    }
    mesa_gCtOf_1usThis1ms = 0;

    // ---------------------------------------------------------------------------------------------
    // We accumulated the number of microseconds calculated by ssTEA each time ssTEA loop executes.
    // ---------------------------------------------------------------------------------------------
    mesa_gCtOf_1msThisCycle++;
    if (mesa_gCtOf_1msThisCycle >= 100)     // 100 millis out of one second; one second is 1000 millis
    {
        mesa_gCtOf_1msThisCycle = 0;
        mesa_uiOp_emit_1 (Ascii_CR);

#ifdef TERMINAL_PROGRAM_CANT_HANDLE_JUST_CR
        mesa_uiOp_emit_1 (Ascii_LF);
#endif // TERMINAL_PROGRAM_CANT_HANDLE_JUST_CR

        ss_uiOp_emit_Space (10);            // how long does it take Ascii to send all? < 100 millis?
        ss_uiOp_Show_Time (ssT_gpTime_Current, lfN);
    }   // timeout occured
}   // loop             // the App's original loop function, known as "App_loop"

#undef  loop            // don't forget to forget #define

// the ssHL compiler has seen and compiled "App_loop", and has not yet seen anything called "loop".

// =================================================================================================
#define ssTEA_setup  setup

#define APP_BUFFER_ALLOC  (50)

void ssTEA_setup (void) // the one called by Arduino Host OS Api using the name "setup"
{
    AsciiA_t    localBuff[APP_BUFFER_ALLOC];

    // ---------------------------------------------------------------------------------------------
    // Call the original App's "setup", which was renamed to "App_setup" when the compiler found it.
    // This is software written without ssTEA so it may continue to execute before ssTEA is launched.
    // ---------------------------------------------------------------------------------------------
    mesa_uiOp_emit_pAsciiA (pBuildBanner);
    App_setup ();

    ssTEA_InitState ();         // does not modify ssTEA_control.Time or ssTEA_control.Agency

    ssUI_InitState ();          // the UI consists of input and output

    if (ssT_stampOp_TimeOfBuild_AsciiToTime (localBuff))
    {
        mesa_uiOp_emit_qAsciiA ("Time built:");
        ss_uiOp_Show_Time (ssT_gpTime_Built, lfY);
    }

#ifdef APP_ONEOF_CLOCK_OR_TIMER_IS_TIMER
    ss_uiOp_qBanner (lfN, "Timer App co-existing with ssTEA...", lfY);
#endif  // APP_ONEOF_CLOCK_OR_TIMER_IS_CLOCK

#ifdef APP_ONEOF_CLOCK_OR_TIMER_IS_CLOCK
    ssT_mathOp_P1getsP2 (ssT_gpTime_Current, ssT_gpTime_Built);
    ss_uiOp_qBanner (lfN, "Clock App co-existing with ssTEA...", lfY);
#endif  // APP_ONEOF_CLOCK_OR_TIMER_IS_CLOCK

    ssTEA_control.Time_state = ssTEA_state_running;
    ssTEA_control.Agency_state = ssTEA_state_running;

    ss_uiOp_Show_ssTime_state ();
    ss_uiOp_Show_ssAgency_state ();

    mesa_uiOp_emit_newline ();
    mesa_uiOp_emit_newline ();
    mesa_uiOp_emit_newline ();

} // ssTEA_setup        // the one called by Arduino Host OS Api using the name "setup"

#undef ssTEA_setup      // don't forget to forget #define

// the ssHL compiler has seen and compiled "App_setup" and "setup"

// =================================================================================================
// "App_loop" is the original Arduino App's "loop" function, which will now be granted agency
// by ssTEA's "loop".  This was done by a #define trick in this file: rename the original App "loop"
// to "App_loop" and rename "ssTEA_loop" to "loop".  The result is the linker sees two functions:
// "App_loop" and "loop".  Instructions may be found elsewhere describing how to modify Original App.
// =================================================================================================
// This function should be usable as-is and used as-is if possible.  This is the central point of
// Time within ssTEA when Agency granted by the Host OS has been intercepted, and Agency is granted
// to ssTEA to manage Events, and then Agency is granted to the App to do whatever it does so well.
// =================================================================================================
#undef loop
#define ssTEA_loop loop

void ssTEA_loop (void)
{
    ssTEA_Time_MathEntry ();

    ssTEA_Agency_Root (ssT_us_gLoop1toLoop2, ssT_ms_gLoop1toLoop2);

    ssTEA_Time_MathExit ();

    App_loop ();

} // ssTEA_loop

#undef ssTEA_loop       // don't forget to forget #define

// the ssHL compiler has seen and compiled "App_loop" and "loop"

// end of file: app-time.ino



