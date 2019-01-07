## INPUT
```
MSFT Microsoft Corporation
JAVA Sun Microsystems
REDH Red Hat Linux
APAC Apache Org
ZYMZZ Unisys Ops Check
IBM IBM Ltd.
ORCL Oracle Corporation
CSCO Cisco Systems, Inc.
GOOG Google Inc.
YHOO Yahoo! Inc.
NOVL Novell, Inc.
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
"MSFT"      ->  "Microsoft Corporation"
"JAVA"      ->   "Sun Microsystems", "OpenJDK"
"REDH"      ->   "Red Hat Linux"
"APAC"      ->   "Apache Org"
"ZYMZZ"     ->  "Unisys Ops Check" 
"IBM"       ->    "IBM Ltd."
"ORCL"      ->   "Oracle Corporation"
"CSCO"      ->   "Cisco Systems, Inc."
"GOOG"      ->   "Google Inc."
"YHOO"      ->   "Yahoo! Inc."
"NOVL"      ->   "Novell, Inc."
```
