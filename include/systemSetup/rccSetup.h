#ifndef RCCSETUP_H
#define RCCSETUP_H
#include "stm32f4xx.h"
#include "IO.h"

#include <stdbool.h>
#include <assert.h>

#define RCC_CFGR_RESET_VALUE (0)
/*
 * This enum contains all possible errors in the rcc setup
 */
typedef enum {
                RCC_SETUP_SUCCESS = 0,
                ERROR_POWER_INTERFACE_SETUP_FAILED,
                ERROR_HSI_ENABLE_FAILED,
                ERROR_RESET_CFGR,
                ERROR_HSE_DISABLE_FAILED,
                ERROR_CSS_DISABLE_FAILED,
                ERROR_PLL_DISABLE_FAILED
             } rcc_setup_error_t;


/*
 * TODO: add doxygen comments
 */
rcc_setup_error_t rccSetup(ioAddress *rcc_apb1lpenr_address, ioAddress *pwr_cr_address,
         ioAddress *rcc_cr_address, ioAddress *rcc_cfgr_address, uint32_t clock,
         uint32_t voltage_scaling_output_selection);

/**
 * @brief This function is used to enable the power interface
 * @param rcc_apb1lpenr_address
 * @return A type of error during setup or success
 */
rcc_setup_error_t __enablePowerInterface(ioAddress *rcc_apb1lpenr_address);
/* TODO: potentially add a disablePowerInterface function here for symmetry */

/**
 * @brief This function enables the internal clock (HSI)
 * @param rcc_cr address
 * @ return A type of error during setup or success
 */
rcc_setup_error_t __enableHSI(ioAddress *rcc_cr_address);

/**
 * @brief Reset the CFGR register in the RCC block
 * @param rcc_cfgr_address
 * @return A type of error during setup or success
 */
rcc_setup_error_t __resetCFGRReg(ioAddress *rcc_cfgr_address);

/**
 * @brief Disable HSE
 * @param rcc_cr_address
 * @return A type of error during setup or success
 */
rcc_setup_error_t __disableHSE(ioAddress *rcc_cr_address);

/**
 * @brief Disable CSS
 * @param rcc_cr_address
 * @return A type of error during setup or success
 */
rcc_setup_error_t __disableCSS(ioAddress *rcc_cr_address);

/**
 * @brief Disable PLL
 * @param rcc_cr_address
 * @return A type of error during setup or success
 */
rcc_setup_error_t __disablePLL(ioAddress *rcc_cr_address);
#endif /* RCCSETUP_H */
