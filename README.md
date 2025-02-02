# libtitanium
libTitanium(libTi) is a library that overrides the uname() syscall in order to return fake info

## Why titanium?
No real reason, I made libTi for fun and I didn't want to name it something like libfakeuname, since it'd be too obvious.

## Usage

```bash
export LD_PRELOAD=/path/to/libtitanium.so

uname -a
```

OR 

```bash
LD_PRELOAD=/path/to/libtitanium.so uname -a
```
