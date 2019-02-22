## INPUT
```
MSFT MicrosoftCorporation
JAVA SunMicrosystems
REDH RedHatLinux
APAC ApacheOrg
ZYMZZ UnisysOpsCheck
IBM IBMLtd.
ORCL OracleCorporation
CSCO CiscoSystems,Inc.
GOOG GoogleInc.
YHOO Yahoo!Inc.
NOVL Novell,Inc.
JAVA Oracle
JAVA OpenJDK
```

## Delete
```
JAVA Oracle
```

## HashKey Function
```cpp
unsigned long hash(const char *str)
{
   unsigned long hash = 5381;
   int c;

   while (c = *str++)
   {
      hash = (((hash << 5) + hash) + c) % MAX_TABLE;
   }

   return hash % MAX_TABLE;
}
```


## OUTPUT
```
"MSFT"      ->  "MicrosoftCorporation"
"JAVA"      ->  "SunMicrosystems", "OpenJDK"
"REDH"      ->  "RedHatLinux"
"APAC"      ->  "ApacheOrg"
"ZYMZZ"     ->  "UnisysOpsCheck"
"IBM"       ->  "IBMLtd."
"ORCL"      ->  "OracleCorporation"
"CSCO"      ->  "CiscoSystems,Inc."
"GOOG"      ->  "GoogleInc."
"YHOO"      ->  "Yahoo!Inc."
"NOVL"      ->  "Novell,Inc."
```
