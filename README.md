# ESTER

simple C lib help with logging your project

## Usage

```C
#include "ester.h"

static const ester_logger_t project_name = {.name = "name you choose"} ;

```

Example:


```C

// to store in file 
// it will create with the name you choosed
ESTER_LOGF_WARN(project_name, "Hello") ;

// display log on terminal
ESTER_LOG_WARN(project_name, "Hello") ;

```
