# Reproduce the bug reported as #5164

The following steps causes an assertion failure.

## disable

Disable the fix in src/hotspot/share/gc/shared/c1/cardTableBarrierSetC1.cpp.
```
- #if 1
+ #if 0
```

## configure options
--with-jvm-variants=server --with-debug-level=fastdebug --with-native-debug-symbols=internal --with-extra-cflags='-march=native -DSUPPORT_BARRIER_ON_PRIMITIVES'

## .hotspotrc

```
+UseSerialGC
TieredStopAtLevel=1
ErrorFile=error.log
+UnlockDiagnosticVMOptions
+UnlockExperimentalVMOptions
+ReduceSignalUsage
-VerifyDependencies
```

## command line 

```
build/linux-x86_64-server-fastdebug/jdk/bin/java -Xbatch -Xcomp -jar dacapo-9.12-MR1-bach.jar xalan
```

Dacapo can is downloaded from https://sourceforge.net/projects/dacapobench/files/9.12-bach-MR1/
