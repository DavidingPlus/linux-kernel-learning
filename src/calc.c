#include <linux/export.h>

#include "calc.h"


int add(int a, int b) { return a + b; }

int sub(int a, int b) { return a - b; }


EXPORT_SYMBOL(add);
EXPORT_SYMBOL(sub);
