/* -- SimpleSal: ssTEA, ssUI, and ssIO | Copyright (C) 2025, 2026 TruSoft Computing LLC |  All rights reserved. --
   This software is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
   This software is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
   ---------------------------------------------------------------------------------------------------
 *
 * app-time.ino         Arduino application demonstrating Timer or Clock based on ssTEA.
 *
 * 2026/10/16   Demo Arduino SimpleSal App released as "app-time.ino" by TruSoft Computing LLC.
 * 2025/08/06   special version appeared as the star of first videos published at SimpleSal substack.
 * 2024/05/27   created superset FSM Demo Application as basis for ssTEA and SimpleSal dev/test.
 ---------------------------------------------------------------------------------------------------- */
// =================================================================================================
// -------------------------------------------------------------------------------------------------
// The "mesas_min_*.*" files have content affected by build-time choices made before including.
// -------------------------------------------------------------------------------------------------
// ssTEA, ssUI, and the App all depend on the Serial port
// -------------------------------------------------------------------------------------------------
#define     THIS_BUILDS_BAUD_RATE  (38400)

#define     MESA_OPTIN_RANDOM_NUMBERS

// #define MESA_ONEOF_CONTROL_INIT_BUILDTIME
#define MESA_ONEOF_CONTROL_INIT_RUNTIME

// -------------------------------------------------------------------------------------------------
// The file ".\SimpleSal\mesas_vocabulary.start" contains very specific words used by SimpleSal,
// the definition of the words does not have to be done by the SimpleSal file, it can be done here.
// -------------------------------------------------------------------------------------------------
// SimpleSal App "app-events" briefly describes these few settings; "app-fsmDemo" fully describes.
// -------------------------------------------------------------------------------------------------
#define     HOST_ONEOF_hostOS_Is_Arduino
#define     HOST_ONEOF_ssHL_defines_boolean
#define     HOST_ONEOF_ssHL_defines_Null

#define     ReadOnly        static

// -------------------------------------------------------------------------------------------------
// define which functionality within the MIN definition should be included, before including this.
// -------------------------------------------------------------------------------------------------
#include ".\SimpleSal\mesas_min_dcl.h"

// -------------------------------------------------------------------------------------------------
// Arduino picked some words years ago, there is no reason we can't create a meaningful word to use.
// Virtual (ssIO) and new tech in chipset pins may create additional mutually exclusive attributes.
// For example, the value of the output when a pin is "tri-stated" may be decided by the circuit.
// -------------------------------------------------------------------------------------------------
typedef enum PinMode_e
{
    mesaPinMode_INPUT_NOPULLUP = INPUT,
    mesaPinMode_INPUT_PULLEDUP = INPUT_PULLUP,
    mesaPinMode_OUTPUT = OUTPUT
}   PinMode_t;

// =================================================================================================
// -------------------------------------------------------------------------------------------------
// The definition of the simplest configuration depends on the file the build tool finds and uses.
// -------------------------------------------------------------------------------------------------
// This SimpleSal App is meant to build with "ss_configuration.start" with extension changed to ".h".
// -------------------------------------------------------------------------------------------------
#define     SS_OPTIN_INCLUDE_SSTEA
#define     SS_ACCEPT_SIMPLEST_CONFIG

#include ".\SimpleSal\ss_configuration.h"

// -------------------------------------------------------------------------------------------------
// Using ssTEA data types, App data types for Events may be declared HERE.  ssTEA Event maintains
// data About the Event; ssTEA refers to the App's data type when the Event is granted Agency.
// -------------------------------------------------------------------------------------------------
#include ".\SimpleSal\ssTEA\ssTEA_data_dcl.h"

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
#include ".\SimpleSal\ss_include_dcl.h"

// -------------------------------------------------------------------------------------------------
// the definition of the words does not have to be done by the SimpleSal file, it can be done here.
// -------------------------------------------------------------------------------------------------
#define mesa_ONEOF_Default_LED_RO_owner             RO_owner_Anybody
#define mesa_ONEOF_Default_LED_RO_active            RO_active_classic
#define mesa_ONEOF_Default_Ascii_RO_owner           RO_owner_Anybody
#define mesa_ONEOF_Default_Ascii_RO_active          RO_active_AllOfUIs
#define mesa_ONEOF_Default_LED_Matrix_RO_owner      RO_owner_Anybody
#define mesa_ONEOF_Default_LED_Matrix_RO_active     RO_active_classic

// -------------------------------------------------------------------------------------------------
// This SimpleSal App is meant to build with "mesas_min_def.start" with extension changed to ".h".
// -------------------------------------------------------------------------------------------------
// To override the default content in "mesas_min_def.h", #define the value before including file.
// -------------------------------------------------------------------------------------------------
#include ".\SimpleSal\mesas_min_def.h"

// -------------------------------------------------------------------------------------------------
// Because the App co-exists with ssTEA/ssUI, a semaphore FSM is used to gate access based on owner.
// Verbosity initializes the ssUI FSM generating extensive run-time Ascii text info to "Say it!".
// -------------------------------------------------------------------------------------------------
#define  ssUI_ONEOF_Default_LED_RO_owner            mesa_ONEOF_Default_LED_RO_owner
#define  ssUI_ONEOF_Default_LED_RO_active           mesa_ONEOF_Default_LED_RO_active
#define  ssUI_ONEOF_Default_Ascii_RO_owner          mesa_ONEOF_Default_Ascii_RO_owner
#define  ssUI_ONEOF_Default_Ascii_RO_active         mesa_ONEOF_Default_Ascii_RO_active
#define  ssUI_ONEOF_Default_LED_Matrix_RO_owner     mesa_ONEOF_Default_LED_Matrix_RO_owner
#define  ssUI_ONEOF_Default_LED_Matrix_RO_active    mesa_ONEOF_Default_LED_Matrix_RO_active

#define YES_BE_VERBOSE                              true
#define DONT_BE_VERBOSE                             (!YES_BE_VERBOSE)

#define ssUI_ONEOF_Default_Verbosity                YES_BE_VERBOSE

// -------------------------------------------------------------------------------------------------
// The UI shared between the App and ssUI is simplified here by ssUI sending "app ..." input here.
// -------------------------------------------------------------------------------------------------
void    App_Select_UI (pAscii_t pInputSaysApp)  {  /* null implementation but exists */ }
void    App_HeyProcessThis (pAsciiA_t  pReceivedInput);

// -------------------------------------------------------------------------------------------------
// Allocations of data and definition of functions with parameters, as declared by ss_include_dcl.h
// -------------------------------------------------------------------------------------------------
#include ".\SimpleSal\ss_include_def.h"

// -------------------------------------------------------------------------------------------------
// The interfaces to the mesa, ssTEA and ssUI are now fully visible in the App's namespace.
// -------------------------------------------------------------------------------------------------

pAsciiA_t   pBuildBanner = S("<mesa [UnoR4Wifi] and App [time] init...>");

// -------------------------------------------------------------------------------------------------
// Original App using classic Timekeeping Models
// -------------------------------------------------------------------------------------------------
// The word "classic" is used to mean "a good solution at a time, before code space exceeded 8K".
// -------------------------------------------------------------------------------------------------
// This is a basic implementation of a counter-based Timekeeping model.  This model uses only the
// 32-bits of knowledge that an amount of Time has passed.  Knowledge, or perception, of the actual
// passage of time allows a Time-based Agency model based on "when": when 1ms has gone by, when 1
// second has elapsed, etc.  Layers are built at each subunit; variables to track counters blow up.
// -------------------------------------------------------------------------------------------------
// The "time-since" calculation is performed at the highest precision value available, e.g., the
// number of microseconds.  That number is added to the count of microseconds this milliseconds,
// taking into account the valid range of such a number.  The math carry operation extends the range
// of the Time that can be expressed: count the number of seconds in a day and then increment days.
// -------------------------------------------------------------------------------------------------
// The "invention" at the core of ssTEA is a data type and the math operations on data of that type.
// -------------------------------------------------------------------------------------------------
// The Classic Timekeeping implementation allows any software to use these Timekeeping variables.
// In the "loop" function, something knows how to determine whether one millisecond has passed since
// the last time the loop did something.  The FSM event (e.g., the count of microseconds reaching a
// value that means a millisecond has occurred) marks the passage of time by incrementing a counter.
// -------------------------------------------------------------------------------------------------
unsigned long int   mesa_gCtOf_1usThis1ms;    // # of microsecond periods this 1 millisecond period
unsigned long int   mesa_gCtOf_1msThis100ms;  // # of millisecond periods this 100 millisecond period
unsigned long int   mesa_gCtOf_100msThis1sc;  // # of 100 millisecond periods this 1 second period
unsigned long int   mesa_gCtOf_1msThisCycle;  // # of millisecond periods this X millisecond period

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
// Modification to original Arduino App followed edit process described by "simplesal.substack.com".
// -------------------------------------------------------------------------------------------------
// This is the compiler trick used to allow the adopter of SimpleSal to keep their functions as they
// exist, with the names they have in the original Arduino App.  The alternative is to rename the
// original functions from "setup" to "App_setup" (and loop -> App_loop) with an editor in the file;
// the second step in that alternative is to instantiate ssTEAsetup/ssTEAloop here as setup/loop.
// -------------------------------------------------------------------------------------------------
#define setup   App_setup

void setup (void)   // the App's original setup function, compiler sees and ssTEA calls as App_setup.
{
    // this content was in the App's original setup function, copied here before adding SimpleSal
    mesa_uiOp_deviceInitialize ();

#ifdef  MESA_ONEOF_CONTROL_INIT_RUNTIME
    mesa_gCtOf_1usThis1ms  = 0;
    mesa_gCtOf_1msThis100ms = 0;
    mesa_gCtOf_1msThisCycle = 0;
    mesa_gCtOf_1msFreeRunning = 0;
#endif // MESA_ONEOF_CONTROL_INIT_RUNTIME

    mesa_uiOp_emit_newline ();
    mesa_uiOp_emit_pAsciiA (pBuildBanner);
    mesa_uiOp_emit_newline ();
    mesa_uiOp_emit_qAsciiA ("original App setup complete...");
    mesa_uiOp_emit_newline ();

}   // setup            // the App's original setup function

#undef setup            // don't forget to forget #define

// the ssHL compiler has seen and compiled "App_setup", and has not yet seen anything called "setup".

// =================================================================================================
// -------------------------------------------------------------------------------------------------
// The Arduino IDE does not accept just CR, while other terminal progams will act on CR by itself.
// Not sending the LF causes the Arduino IDE to go linear infinitely, a clear screen resets the
// display.  The challenge is to clear the screen before the program has a chance to display twice.
// Not sending the LF will cause some terminal Apps to display over and over in the same place.
// Sending the LF will cause most terminal Apps and the Arduino IDE to display at the screen bottom.
// -------------------------------------------------------------------------------------------------
// #define APP_OPTIN_ADD_LF_TO_CR

// -------------------------------------------------------------------------------------------------
// Modification to original Arduino App followed edit process described by "simplesal.substack.com".
// -------------------------------------------------------------------------------------------------
// This is the compiler trick used to allow the adopter of SimpleSal to keep their functions as they
// exist, with the names they have in the original Arduino App.  The alternative is to rename the
// original functions from "setup" to "App_setup" (and loop -> App_loop) with an editor in the file;
// the second step in that alternative is to instantiate ssTEAsetup/ssTEAloop here as setup/loop.
// -------------------------------------------------------------------------------------------------
#define loop    App_loop

void loop (void)    // the App's original loop function, compiler sees and ssTEA calls as App_loop.
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

#ifdef APP_OPTIN_ADD_LF_TO_CR
        mesa_uiOp_emit_1 (Ascii_LF);
#endif // APP_OPTIN_ADD_LF_TO_CR

        ss_uiOp_emit_Space (10);            // how long does it take Ascii to send all? < 100 millis?
        ss_uiOp_Show_Time (ssT_gpTime_Current, lfN);
    }   // timeout occured
}   // loop             // the App's original loop function, known as "App_loop"

#undef  loop            // don't forget to forget #define

// the ssHL compiler has seen and compiled "App_loop", and has not yet seen anything called "loop".

// =================================================================================================
#define ssTEA_setup  setup

#define APP_BUFFER_ALLOC  (50)

void ssTEA_setup (void)     // ssTEA's setup function, compiler sees and Host OS calls as setup
{
    AsciiA_t    localBuff[APP_BUFFER_ALLOC];

    // ---------------------------------------------------------------------------------------------
    // Call the original App's "setup", which was renamed to "App_setup" when the compiler found it.
    // This is software written without ssTEA so it may continue to execute before ssTEA is launched.
    // ---------------------------------------------------------------------------------------------
    App_setup ();                   // ssTEA initialization occurs within a context the App creates

    ssTEA_InitState ();             // does not modify ssTEA_control.Time or ssTEA_control.Agency

    ssUI_InitState ();              // the UI consists of input and output using the Serial device

    if (ssT_stampOp_TimeOfBuild_AsciiToTime (localBuff))
    {
        mesa_uiOp_emit_qAsciiA ("Time built:");
        ss_uiOp_Show_Time (ssT_gpTime_Built, lfY);
    }

#ifdef APP_ONEOF_CLOCK_OR_TIMER_IS_TIMER
    ss_uiOp_emit_qBanner (lfN, "Timer App co-existing with ssTEA...", lfY);
#endif  // APP_ONEOF_CLOCK_OR_TIMER_IS_CLOCK

#ifdef APP_ONEOF_CLOCK_OR_TIMER_IS_CLOCK
    ssT_mathOp_P1getsP2 (ssT_gpTime_Current, ssT_gpTime_Built);
    ss_uiOp_emit_qBanner (lfN, "Clock App co-existing with ssTEA...", lfY);
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
// "App_loop" and "loop".  Modifications used the edit process described: "simplesal.substack.com".
// =================================================================================================
// This function should be usable as-is and used as-is if possible.  This is the central point of
// Time within ssTEA when Agency granted by the Host OS has been intercepted, and Agency is granted
// to ssTEA to manage Events, and then Agency is granted to the App to do whatever it does so well.
// =================================================================================================
#undef loop
#define ssTEA_loop loop

void ssTEA_loop (void)      // ssTEA's loop function, compiler sees and Host OS calls as loop
{
    ssTEA_Time_MathEntry ();

    ssTEA_Agency_Root (ssT_us_gLoop1toLoop2, ssT_ms_gLoop1toLoop2);

    ssTEA_Time_MathExit ();

    App_loop ();            // user's original App loop function renamed by compiler trick above

} // ssTEA_loop

#undef ssTEA_loop       // don't forget to forget #define

// the ssHL compiler has seen and compiled "App_loop" and "loop"

// end of file: app-time.ino



