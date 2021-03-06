/* HFeasy

Copyright (c) 2019 Luis Alves

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "hfeasy.h"

const hfat_cmd_t user_define_at_cmds_table[] = {
	{NULL,NULL,NULL,NULL}
};

void app_init(void)
{
	u_printf("app_init\r\n");
}

int USER_FUNC app_main(void)
{
	u_printf("sdk version(%s), app_main start time is %s %s\n",
						hfsys_get_sdk_version(), __DATE__, __TIME__);
	
	while(!hfnet_wifi_is_active())
		msleep(100);
	
	if (hfnet_start_assis(ASSIS_PORT) != HF_SUCCESS) {
		HF_Debug(DEBUG_WARN,"start assis fail\n");
	}
	
	if (hfnet_start_uart(HFTHREAD_PRIORITIES_LOW,(hfnet_callback_t) NULL) != HF_SUCCESS) {
		HF_Debug(DEBUG_WARN,"start uart fail!\n");
	}

	if (hfnet_start_httpd(HFTHREAD_PRIORITIES_MID) != HF_SUCCESS) {
		HF_Debug(DEBUG_WARN,"start httpd fail\n");
	}
	
	config_init();
	httpd_init();
	gpio_init();
	buzzer_init();
	timer_init();
	mqttcli_init();
		
	return 1;
}

