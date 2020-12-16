#ifndef _DATO_INCLUDED
    #define _DATO_INCLUDED

    #define MAXST 10

    typedef void * data_t;
    typedef struct item* Item;
    typedef char *Key;

    void STInitializeCallback(void (* show)(Item), Item (* itemScan)(void), Key (* keyScan)(void));
    Item ITEMcreate(char *key, data_t value);
    Item ITEMscan();
    void ITEMshow(Item data);
    int ITEMcheckvoid(Item data);
    Item ITEMsetvoid();
    Key KEYscan();
    int KEYcompare(Key k1, Key k2);
    Key KEYget(Item data);
    data_t ITEMGetValue(Item i);
#endif
