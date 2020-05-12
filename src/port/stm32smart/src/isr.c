// #include <stdint.h>
// #include <target.h>
// #include <libopencm3/stm32/exti.h>
// #include <libopencm3/stm32/gpio.h>
// #include <libopencm3/stm32/usart.h>
// #include <libopencm3/cm3/nvic.h>
// #include <gps.h>
// #include <libopencm3/usb/usbd.h>
// #include <libopencm3/stm32/st_usbfs.h>

// extern void sys_tick_isr_handler();
// extern void hal_exti_isr(uint32_t);
// extern void hal_usart_isr(uint32_t);

// //gps 
// extern void gps_handle_isr(uint16_t);

// void sys_tick_handler(void)
// {
//   sys_tick_isr_handler();
// }

// //encoder left 
// void exti9_5_isr(void)
// {
//   exti_reset_request(ENCODER_COUNTER_CLOCKWISE_DIRECTION_PIN);
//   hal_exti_isr(ENCODER_COUNTER_CLOCKWISE_DIRECTION_PIN);
// }

// void exti15_10_isr(void)
// {
//   exti_reset_request(ENCODER_CLOCKWISE_DIRECTION_PIN);
//   hal_exti_isr(ENCODER_CLOCKWISE_DIRECTION_PIN);
// }

// //encoder right 
// void exti0_isr(void)
// {
//   // exti_reset_request(ENCODER_CLOCKWISE_DIRECTION_PIN);
//   // hal_exti_isr(ENCODER_CLOCKWISE_DIRECTION_PIN);
// }

// //encoder push
// void exti4_isr(void)
// {
//   hal_exti_isr(ENCODER_BUTTON_PIN);
// }

// //gps
// void usart1_isr(void)
// {
//   hal_usart_isr(USART1);
// }

// //usb
// void usb_lp_can_rx0_isr(void)
// {
//   uint32_t tmp = GET_REG(USB_ISTR_REG);
// 	/* Enable RESET, SUSPEND, RESUME and CTR interrupts. */
//   int x = 123123;

//   if ((tmp & USB_CNTR_RESETM))
//   {
//     int x = 10;
//     USB_CLR_ISTR_RESET();
//   }
//   else if ((tmp & USB_CNTR_SUSPM))
//   {
//     int x = 10;
//     USB_CLR_ISTR_SUSP();
//   }
//     else if ((tmp & USB_CNTR_RESETM))
//   {
//     int x = 10;
//     USB_CLR_ISTR_RESET();
//   }
//     else if ((tmp & USB_CNTR_CTRM))
//   {
//     int x = 10;
//   }
// }