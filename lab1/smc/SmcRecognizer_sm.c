/*
 * ex: set ro:
 * DO NOT EDIT.
 * generated by smc (http://smc.sourceforge.net/)
 * from file : SmcRecognizer.sm
 */

#include "SmcRecognizer.h"
#include "sm_config.h"
#include "SmcRecognizer_sm.h"

#define getOwner(fsm) (fsm)->_owner

static void SmcRecognizerState_EOS(struct SmcRecognizerContext *const fsm)
{
    getState(fsm)->Default(fsm);
}

static void SmcRecognizerState_letter(struct SmcRecognizerContext *const fsm, char LET)
{
    getState(fsm)->Default(fsm);
}

static void SmcRecognizerState_reset(struct SmcRecognizerContext *const fsm)
{
    getState(fsm)->Default(fsm);
}

static void SmcRecognizerState_Default(struct SmcRecognizerContext *const fsm)
{
    State_Default(fsm);
}

#define MainMap_Error_letter SmcRecognizerState_letter
#define MainMap_Error_Default SmcRecognizerState_Default
#define MainMap_Start_Default SmcRecognizerState_Default
#define MainMap_Command_Default SmcRecognizerState_Default
#define MainMap_Blank_Default SmcRecognizerState_Default
#define MainMap_Key_Default SmcRecognizerState_Default
#define MainMap_DefaultState_letter SmcRecognizerState_letter

static void MainMap_DefaultState_reset(struct SmcRecognizerContext *const fsm)
{
    struct SmcRecognizer *ctxt = getOwner(fsm);

    clearState(fsm);
    SmcRecognizer_Incorrect(ctxt);
    setState(fsm, &MainMap_Start);

}
#define MainMap_Error_reset MainMap_DefaultState_reset
#define MainMap_Start_reset MainMap_DefaultState_reset
#define MainMap_Command_reset MainMap_DefaultState_reset
#define MainMap_Blank_reset MainMap_DefaultState_reset
#define MainMap_Key_reset MainMap_DefaultState_reset

static void MainMap_DefaultState_EOS(struct SmcRecognizerContext *const fsm)
{


}
#define MainMap_Error_EOS MainMap_DefaultState_EOS
#define MainMap_Start_EOS MainMap_DefaultState_EOS
#define MainMap_Command_EOS MainMap_DefaultState_EOS
#define MainMap_Blank_EOS MainMap_DefaultState_EOS

static void MainMap_DefaultState_Default(struct SmcRecognizerContext *const fsm)
{

    setState(fsm, &MainMap_Error);

}
#define MainMap_Error_Default MainMap_DefaultState_Default
#define MainMap_Start_Default MainMap_DefaultState_Default
#define MainMap_Command_Default MainMap_DefaultState_Default
#define MainMap_Blank_Default MainMap_DefaultState_Default
#define MainMap_Key_Default MainMap_DefaultState_Default

const struct SmcRecognizerState MainMap_Error = {
    MainMap_Error_EOS,
    MainMap_Error_letter,
    MainMap_Error_reset,
    MainMap_Error_Default,
    0
};
static void MainMap_Start_letter(struct SmcRecognizerContext *const fsm, char LET)
{

    if (ALNUM_DOT_SLASH) {
        /* No actions. */
        setState(fsm, &MainMap_Command);
    }
    else {
        MainMap_DefaultState_letter(fsm, LET);
    }

}

const struct SmcRecognizerState MainMap_Start = {
    MainMap_Start_EOS,
    MainMap_Start_letter,
    MainMap_Start_reset,
    MainMap_Start_Default,
    1
};
static void MainMap_Command_letter(struct SmcRecognizerContext *const fsm, char LET)
{

    if (ALNUM_DOT_SLASH) {
        /* No actions. */
    }
    else if (BLANK) {
        /* No actions. */
        setState(fsm, &MainMap_Blank);
    }    else {
        MainMap_DefaultState_letter(fsm, LET);
    }

}

const struct SmcRecognizerState MainMap_Command = {
    MainMap_Command_EOS,
    MainMap_Command_letter,
    MainMap_Command_reset,
    MainMap_Command_Default,
    2
};
static void MainMap_Blank_letter(struct SmcRecognizerContext *const fsm, char LET)
{

    if (BLANK) {
        /* No actions. */
    }
    else if (ALNUM) {
        /* No actions. */
        setState(fsm, &MainMap_Key);
    }    else {
        MainMap_DefaultState_letter(fsm, LET);
    }

}

const struct SmcRecognizerState MainMap_Blank = {
    MainMap_Blank_EOS,
    MainMap_Blank_letter,
    MainMap_Blank_reset,
    MainMap_Blank_Default,
    3
};
static void MainMap_Key_EOS(struct SmcRecognizerContext *const fsm)
{
    struct SmcRecognizer *ctxt = getOwner(fsm);
    const struct SmcRecognizerState* EndStateName = getState(fsm);

    clearState(fsm);
    SmcRecognizer_Correct(ctxt);
    setState(fsm, EndStateName);

}
static void MainMap_Key_letter(struct SmcRecognizerContext *const fsm, char LET)
{

    if (ALNUM) {
        /* No actions. */
    }
    else if (BLANK) {
        /* No actions. */
        setState(fsm, &MainMap_Blank);
    }    else {
        MainMap_DefaultState_letter(fsm, LET);
    }

}

const struct SmcRecognizerState MainMap_Key = {
    MainMap_Key_EOS,
    MainMap_Key_letter,
    MainMap_Key_reset,
    MainMap_Key_Default,
    4
};

#ifdef NO_SMCRECOGNIZER_SM_MACRO
void SmcRecognizerContext_Init(struct SmcRecognizerContext *const fsm, struct SmcRecognizer *const owner)
{
    FSM_INIT(fsm, &MainMap_Start);
    fsm->_owner = owner;
}

void SmcRecognizerContext_EOS(struct SmcRecognizerContext *const fsm)
{
    const struct SmcRecognizerState* state = getState(fsm);

    assert(state != NULL);
    setTransition(fsm, "EOS");
    state->EOS(fsm);
    setTransition(fsm, NULL);
}

void SmcRecognizerContext_letter(struct SmcRecognizerContext *const fsm, char LET)
{
    const struct SmcRecognizerState* state = getState(fsm);

    assert(state != NULL);
    setTransition(fsm, "letter");
    state->letter(fsm, LET);
    setTransition(fsm, NULL);
}

void SmcRecognizerContext_reset(struct SmcRecognizerContext *const fsm)
{
    const struct SmcRecognizerState* state = getState(fsm);

    assert(state != NULL);
    setTransition(fsm, "reset");
    state->reset(fsm);
    setTransition(fsm, NULL);
}
#endif

/*
 * Local variables:
 *  buffer-read-only: t
 * End:
 */
