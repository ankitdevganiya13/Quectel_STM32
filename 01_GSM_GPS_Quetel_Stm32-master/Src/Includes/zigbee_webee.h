/**
 * @file       zigbee_webee.h
 * @copyright  Copyright (C) 2020 ThuanLe. All rights reserved.
 * @license    This project is released under the ThuanLe License.
 * @version    1.0.0
 * @date       2020-08-26
 * @author     Thuan Le
 * @brief      Driver support zigbee webee communication
 * @note       None
 * @example    None
 */

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __ZIGBEE_WEBEE_H
#define __ZIGBEE_WEBEE_H

/* Includes ----------------------------------------------------------- */
#include <stdint.h>
#include <stdbool.h>

/* Public defines ----------------------------------------------------- */
/* Public enumerate/structure ----------------------------------------- */
/**
 * @brief Zigbee status enum
 */
typedef enum
{
  ZIGBEE_OK,
  ZIGBEE_ERR_PARAM,
  ZIGBEE_ERR_UART
}
zigbee_status_t;

/**
 * @brief Zigbee role enum
 */
typedef enum
{
  COORDINATOR,
  ROUTER,
  END_DEVICE
}
zigbee_role_t;

/**
 * @brief Zigbee webee sensor struct
 */
typedef struct
{
  zigbee_role_t role;
  uint16_t      pan_id;
  uint16_t      local_muti_nb;
  uint8_t       channel;

  bool (*uart_send)(uint8_t *p_data, uint16_t len);
}
zigbee_t;

/* Public macros ------------------------------------------------------ */
/* Public variables --------------------------------------------------- */
/* Public function prototypes ----------------------------------------- */
/**
 * @brief         Zigbee init
 * @param[in]     <param_despcription>
 * @attention     <API attention note>
 * @return  
 */
zigbee_status_t zigbee_init(zigbee_t *me);

#endif // __ZIGBEE_WEBEE_H

/* End of file -------------------------------------------------------- */
