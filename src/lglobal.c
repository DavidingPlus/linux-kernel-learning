#include <linux/module.h>


int helloInitData __initdata = -114514;

const char *helloExitData __exitdata = "foo";

char *helloInitParam = "gee";

int helloExitParam[2] = {-10086, 10086};

int helloExitParamSize = sizeof(helloExitParam) / sizeof(int);


module_param(helloInitParam, charp, S_IRUGO);
module_param_array(helloExitParam, int, &helloExitParamSize, S_IRUGO);
