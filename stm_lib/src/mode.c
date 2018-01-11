// #include "mode.h"
// #include "hd44780_driver.h"
// #include "match.h"
// #include "menu.h"
//
// uint8_t push_mode = 0;
//
// #define STM32F103C8T6 // STM32F103C8T6/STM32F103ZET6
// #define no_OUT_UART   // no_OUT_UART/OUT_UART
//
// void config_chanal_arm();
//
// void mode_jammers(double fraquent) {
//   lcd_clear();
//   lcd_set_xy(0, 0);
//   lcd_out_char("JAMMERS");
//   lcd_set_xy(0, 1);
//   lcd_out_char("WORK");
//
//   // double cyr_fraquent = 10000;
//   uint32_t registr_32_bit;
//   registr_32_bit = calc_registr(fraquent);
//   config_port_dds();
//   set_serial_mode();
//   send_data_serial_mode(registr_32_bit);
//   lcd_set_xy(0, 0);
//   lcd_out_char("Fraquent = ");
//   lcd_set_xy(0, 1);
//   lcd_out_number(fraquent);
//   while (!GPIO_ReadInputDataBit(PORT_CAP, CAP_MODE))
//     ;
// }
//
// void mode_broadbans(double broadbans) {
//   lcd_clear();
//   lcd_set_xy(0, 0);
//   lcd_out_char("BROADBANS");
//   lcd_set_xy(0, 1);
//   lcd_out_char("WORK");
//   while (!GPIO_ReadInputDataBit(PORT_CAP, CAP_MODE))
//     ;
// }
//
// void adjust() {
//   uint8_t push_up_down = 0;
//   uint8_t push_enter = 0;
//   uint8_t push_mode = 0;
//
//   lcd_clear();
//   lcd_set_xy(0, 0);
//   lcd_out_char("OPTIONS");
//   lcd_set_xy(0, 1);
//   lcd_out_char("PUSH CAP UP/DOWN");
//
//   while (push_mode == 0) {
//     push_up_down = 0;
//     push_enter = 0;
//
//     while (push_up_down == 0 && push_mode == 0) {
//       lcd_clear();
//       lcd_set_xy(0, 0);
//       lcd_out_char("FRAQUENT");
//       lcd_set_xy(0, 1);
//       if (push_enter == 1)
//         fraquent_global = fraquent_global + 500;
//       if (fraquent_global == 10000000)
//         fraquent_global = 1000;
//       lcd_out_number(fraquent_global);
//
//       while (1) {
//         push_enter = GPIO_ReadInputDataBit(PORT_CAP, CAP_ENTER);
//         if (push_enter == 1)
//           break;
//         delay_us(100);
//         push_up_down = GPIO_ReadInputDataBit(PORT_CAP, CAP_UP_DOWN);
//         if (push_up_down == 1)
//           break;
//         delay_us(100);
//         push_mode = GPIO_ReadInputDataBit(PORT_CAP, CAP_MODE);
//         delay_us(100);
//         if (push_mode == 1)
//           break;
//       }
//     }
//
//     push_up_down = 0;
//     push_enter = 0;
//
//     while (push_up_down == 0 && push_mode == 0) {
//       lcd_clear();
//       lcd_set_xy(0, 0);
//       lcd_out_char("BROADBANS");
//       lcd_set_xy(0, 1);
//       if (push_enter == 1)
//         broadbans = broadbans + 50;
//       if (broadbans == 10000000)
//         broadbans = 100000;
//       lcd_out_number(broadbans);
//
//       while (1) {
//         push_enter = GPIO_ReadInputDataBit(PORT_CAP, CAP_ENTER);
//         if (push_enter == 1)
//           break;
//         delay_us(100);
//         push_up_down = GPIO_ReadInputDataBit(PORT_CAP, CAP_UP_DOWN);
//         if (push_up_down == 1)
//           break;
//         delay_us(100);
//         push_mode = GPIO_ReadInputDataBit(PORT_CAP, CAP_MODE);
//         delay_us(100);
//         if (push_mode == 1)
//           break;
//       }
//     }
//
//     push_up_down = 0;
//     push_enter = 0;
//
//     while (push_up_down == 0 && push_mode == 0) {
//       lcd_clear();
//       lcd_set_xy(0, 0);
//       lcd_out_char("mux_set");
//       lcd_set_xy(0, 1);
//       if (push_enter == 1) {
//         if (mux_clobal == 0) {
//           mux_clobal = 1;
//         } else {
//           if (mux_clobal == 1) {
//             mux_clobal = 0;
//           }
//         }
//       }
//
//       if (mux_clobal == 0)
//         lcd_out_char("mux_off");
//       else
//         lcd_out_char("mux_on");
//       while (1) {
//         push_enter = GPIO_ReadInputDataBit(PORT_CAP, CAP_ENTER);
//         if (push_enter == 1)
//           break;
//         delay_us(100);
//         push_up_down = GPIO_ReadInputDataBit(PORT_CAP, CAP_UP_DOWN);
//         if (push_up_down == 1)
//           break;
//         delay_us(100);
//         push_mode = GPIO_ReadInputDataBit(PORT_CAP, CAP_MODE);
//         delay_us(100);
//         if (push_mode == 1)
//           break;
//       }
//     }
//   }
// }
