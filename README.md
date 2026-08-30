# ESTER

simple C lib help with logging your project

## what it provide

ESTER is logging system for linux built directly on syscalls

ESTER use auto-type detect via {}

```C

int x = 50 ;
// no need to use formater as %d
ESTER_LOGF_WARN(project_name, "x is {}",x) ;

```
Most heavy work happen in compile-time via macros

this is my first lib so be fair i am not torvalds lol

## Usage

```C
#include "ester.h"

static const ester_logger_t project_name = {.name = "name"/* will be used as logfile */} ;

```

Example:


```C

// to store in file 
// it will create with the name you choosed
ESTER_LOGF_WARN(project_name, "Hello") ;

// display log on terminal
ESTER_LOG_WARN(project_name, "Hello") ;

// do both store log in file and print on terminal
ESTER_LOGM_WARN(project_name, "Hello") ;

// kill program and call ESTER_LOGM_WARN
ESTER_ABORT(project_name, "Hello") ;

```
