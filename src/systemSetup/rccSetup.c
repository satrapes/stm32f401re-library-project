//#include <stdint.h>
#include "rccSetup.h"
#include "utils.h"
//int global_uninit;
//int global_init = 0;
//static int global_static_uninit;
//static int global_static_init = 0;

//static uint8_t select

rcc_setup_error_t rccSetup(ioAddress *rcc_apb1lpenr_address, ioAddress *pwr_cr_address,
        ioAddress *rcc_cr_address, ioAddress *rcc_cfgr_address, uint32_t clock,
        uint32_t voltage_scaling_output_selection)
{
    rcc_setup_error_t result;

    /* Reset RCC clock configuration to the default reset state */
    /* Enable internal clock (HSI) */
    result = __enableHSI(rcc_cr_address);

    /* Reset RCC_CFGR */
    result = __resetCFGRReg(rcc_cfgr_address);

    /* Enable power interface */
    result = __enablePowerInterface(rcc_apb1lpenr_address);

    /* Check output and fail early */
    if (result != RCC_SETUP_SUCCESS)
    {
        return result;
    }
    /* TODO: Figure out how to deal with asserts. Maybe have a DEBUG and a RELEASE build but to do
     *       that I first have to convert my makefiles into eclipse projects. */
    /* Assert result is different than any power interface setup error */
    assert(result != ERROR_POWER_INTERFACE_SETUP_FAILED);

    /* Wait until HSI is ready */
    while ((IO_Read(rcc_cr_address) & RCC_CR_HSIRDY) == 0);

    /* TODO: Adding an assert that uses an IO_Read would mess the code so not sure what to do */
    return result;
}

rcc_setup_error_t __enablePowerInterface(ioAddress *rcc_apb1lpenr_address)
{
    /* TODO: I should add a clock variable it is already in the rccSetup */
    bool result;

    result = __setBitMask(rcc_apb1lpenr_address, RCC_APB1LPENR_PWRLPEN);
    /*TODO: potential bug in the OR this can be non zero if any other bit than the one currently
     *      examined is non zero
     */
    if (result)
    {
        return ERROR_POWER_INTERFACE_SETUP_FAILED;
    } else
    {
        return RCC_SETUP_SUCCESS;
    }
}

rcc_setup_error_t __enableHSI(ioAddress *rcc_cr_address)
{
    /* TODO: add disable HSI for symmetry */
    bool result;

    result = __setBitMask(rcc_cr_address, RCC_CR_HSION);

    if (result)
    {
        return ERROR_HSI_ENABLE_FAILED;
    } else
    {
        return RCC_SETUP_SUCCESS;
    }
}

rcc_setup_error_t __resetCFGRReg(ioAddress *rcc_cfgr_address)
{
    IO_Write(rcc_cfgr_address, RCC_CFGR_RESET_VALUE);
    if (IO_Read(rcc_cfgr_address))
    {
        return ERROR_RESET_CFGR;
    } else
    {
        return RCC_SETUP_SUCCESS;
    }
}

rcc_setup_error_t __disableHSE(ioAddress *rcc_cr_address)
{
    /* TODO: add enable HSE for symmetry */
    bool result;

    result = __clearBitMask(rcc_cr_address, RCC_CR_HSEON);

    if (result)
    {
        return ERROR_HSE_DISABLE_FAILED;
    } else
    {
        return RCC_SETUP_SUCCESS;
    }
}

rcc_setup_error_t __disableCSS(ioAddress *rcc_cr_address)
{
    /* TODO: add enable HSE for symmetry */
    bool result;

    result = __clearBitMask(rcc_cr_address, RCC_CR_CSSON);

    if (result)
    {
        return ERROR_CSS_DISABLE_FAILED;
    } else
    {
        return RCC_SETUP_SUCCESS;
    }
}

rcc_setup_error_t __disablePLL(ioAddress *rcc_cr_address)
{
    /* TODO: add enable HSE for symmetry */
    bool result;

    result = __clearBitMask(rcc_cr_address, RCC_CR_PLLON);

    if (result)
    {
        return ERROR_PLL_DISABLE_FAILED;
    } else
    {
        return RCC_SETUP_SUCCESS;
    }
}
